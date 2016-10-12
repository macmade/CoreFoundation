/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 Jean-David Gadina - www-xs-labs.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        CFAllocator.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>
#include <CoreFoundation/__private/CFThreading.h>
#include <stdlib.h>
#include <string.h>

struct CFAllocator
{
    CFRuntimeBase       _base;
    CFAllocatorContext  _context;
};

static void  * CFAllocatorSystemDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
static void  * CFAllocatorSystemDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
static void    CFAllocatorSystemDefaultDeallocateCallBack( void * ptr, void * info );

static void  * CFAllocatorNullAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
static void  * CFAllocatorNullReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
static void    CFAllocatorNullDeallocateCallBack( void * ptr, void * info );
static CFIndex CFAllocatorNullPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info );

static void        CFAllocatorDestruct( CFAllocatorRef allocator );
static CFStringRef CFAllocatorCopyDescription( CFAllocatorRef allocator );

static CFTypeID CFAllocatorTypeID      = 0;
static CFRuntimeClass CFAllocatorClass =
{
    "CFAllocator",
    sizeof( struct CFAllocator ),
    NULL,
    ( void ( * )( CFTypeRef ) )CFAllocatorDestruct,
    NULL,
    NULL,
    ( CFStringRef ( * )( CFTypeRef ) )CFAllocatorCopyDescription,
};

static struct CFAllocator CFAllocatorSystemDefault;
static struct CFAllocator CFAllocatorMalloc;
static struct CFAllocator CFAllocatorMallocZone;
static struct CFAllocator CFAllocatorNull;

const CFAllocatorRef kCFAllocatorDefault        = NULL;
const CFAllocatorRef kCFAllocatorSystemDefault  = ( const CFAllocatorRef )( &CFAllocatorSystemDefault );
const CFAllocatorRef kCFAllocatorMalloc         = ( const CFAllocatorRef )( &CFAllocatorMalloc );
const CFAllocatorRef kCFAllocatorMallocZone     = ( const CFAllocatorRef )( &CFAllocatorMallocZone );
const CFAllocatorRef kCFAllocatorNull           = ( const CFAllocatorRef )( &CFAllocatorNull );
const CFAllocatorRef kCFAllocatorUseContext     = ( const CFAllocatorRef )( -1 );

static CFThreadingKey CFAllocatorDefaultKey; 

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFThreadingKeyCreate( &CFAllocatorDefaultKey );
    
    CFAllocatorTypeID = CFRuntimeRegisterClass( &CFAllocatorClass );
    
    CFRuntimeInitStaticInstance( &CFAllocatorSystemDefault, CFAllocatorTypeID );
    CFRuntimeInitStaticInstance( &CFAllocatorMalloc,        CFAllocatorTypeID );
    CFRuntimeInitStaticInstance( &CFAllocatorMallocZone,    CFAllocatorTypeID );
    CFRuntimeInitStaticInstance( &CFAllocatorNull,          CFAllocatorTypeID );
    
    CFAllocatorSystemDefault._context.allocate      = CFAllocatorSystemDefaultAllocateCallBack;
    CFAllocatorSystemDefault._context.deallocate    = CFAllocatorSystemDefaultDeallocateCallBack;
    CFAllocatorSystemDefault._context.reallocate    = CFAllocatorSystemDefaultReallocateCallBack;
    
    CFAllocatorMalloc._context.allocate     = CFAllocatorSystemDefaultAllocateCallBack;
    CFAllocatorMalloc._context.deallocate   = CFAllocatorSystemDefaultDeallocateCallBack;
    CFAllocatorMalloc._context.reallocate   = CFAllocatorSystemDefaultReallocateCallBack;
    
    CFAllocatorMallocZone._context.allocate     = CFAllocatorSystemDefaultAllocateCallBack;
    CFAllocatorMallocZone._context.deallocate   = CFAllocatorSystemDefaultDeallocateCallBack;
    CFAllocatorMallocZone._context.reallocate   = CFAllocatorSystemDefaultReallocateCallBack;
    
    CFAllocatorNull._context.allocate       = CFAllocatorNullAllocateCallBack;
    CFAllocatorNull._context.deallocate     = CFAllocatorNullDeallocateCallBack;
    CFAllocatorNull._context.preferredSize  = CFAllocatorNullPreferredSizeCallBack;
    CFAllocatorNull._context.reallocate     = CFAllocatorNullReallocateCallBack;
}

static void CFAllocatorDestruct( CFAllocatorRef allocator )
{
    if( allocator->_context.release )
    {
        allocator->_context.release( allocator->_context.info );
    }
}

static CFStringRef CFAllocatorCopyDescription( CFAllocatorRef allocator )
{
    ( void )allocator;
    
    return CFStringCreateWithFormat
    (
        NULL,
        NULL,
        CFStringCreateWithCStringNoCopy( NULL, "{ info = 0x%lu }", kCFStringEncodingUTF8, kCFAllocatorNull ),
        allocator->_context.info
    );
}

CFTypeID CFAllocatorGetTypeID( void )
{
    return CFAllocatorTypeID;
}

CFAllocatorRef CFAllocatorCreate( CFAllocatorRef allocator, CFAllocatorContext * context )
{
    struct CFAllocator * o;
    
    if( allocator == kCFAllocatorUseContext )
    {
        if( context == NULL || context->allocate == NULL )
        {
            return NULL;
        }
        
        o = context->allocate( CFRuntimeGetInstanceSize( CFAllocatorTypeID ), 0, context->info );
        
        CFRuntimeInitInstance( o, CFAllocatorTypeID, o );
    }
    else
    {
        o = ( struct CFAllocator * )CFRuntimeCreateInstance( allocator, CFAllocatorTypeID );
    }
    
    if( context )
    {
        o->_context = *( context );
        
        if( o->_context.retain )
        {
            o->_context.info = ( void * )( o->_context.retain( o->_context.info ) );
        }
    }
    
    return o;
}

void * CFAllocatorAllocate( CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint )
{
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( allocator != NULL && allocator->_context.allocate != NULL )
    {
        return allocator->_context.allocate( size, hint, allocator->_context.info );
    }
    
    return NULL;
}

void CFAllocatorDeallocate( CFAllocatorRef allocator, void * ptr )
{
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( allocator != NULL && allocator->_context.deallocate != NULL )
    {
        allocator->_context.deallocate( ptr, allocator->_context.info );
    }
}

CFIndex CFAllocatorGetPreferredSizeForSize( CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint )
{
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( allocator != NULL && allocator->_context.preferredSize != NULL )
    {
        return allocator->_context.preferredSize( size, hint, allocator->_context.info );
    }
    
    return size;
}

void * CFAllocatorReallocate( CFAllocatorRef allocator, void * ptr, CFIndex newsize, CFOptionFlags hint )
{
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( ptr == NULL )
    {
        return ( newsize > 0 ) ? CFAllocatorAllocate( allocator, newsize, hint ) : NULL;
    }
    
    if( newsize == 0 )
    {
        CFAllocatorDeallocate( allocator, ptr );
        
        return NULL;
    }
    
    if( allocator != NULL && allocator->_context.reallocate != NULL )
    {
        return allocator->_context.reallocate( ptr, newsize, hint, allocator->_context.info );
    }
    
    return NULL;
}

CFAllocatorRef CFAllocatorGetDefault( void )
{
    CFAllocatorRef current;
    
    current = CFThreadingGetSpecific( CFAllocatorDefaultKey );
    
    return ( current == NULL ) ? kCFAllocatorSystemDefault : current;
}

void CFAllocatorSetDefault( CFAllocatorRef allocator )
{
    CFAllocatorRef current;
    
    current = CFThreadingGetSpecific( CFAllocatorDefaultKey );
    
    if( current )
    {
        CFRelease( current );
    }
    
    if( allocator )
    {
        CFRetain( allocator );
    }
    
    CFThreadingSetSpecific( CFAllocatorDefaultKey, allocator );
}

void CFAllocatorGetContext( CFAllocatorRef allocator, CFAllocatorContext * context )
{
    if( allocator == NULL )
    {
        if( context != NULL )
        {
            memset( context, 0, sizeof( CFAllocatorContext ) );
        }
    }
    else if( context != NULL )
    {
        *( context ) = allocator->_context;
    }
}

static void * CFAllocatorSystemDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )hint;
    ( void )info;
    
    if( allocSize <= 0 )
    {
        return NULL;
    }
    
    return calloc( ( size_t )allocSize, 1 );
}

static void * CFAllocatorSystemDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )hint;
    ( void )info;
    
    return realloc( ptr, ( size_t )newsize );
}

static void CFAllocatorSystemDefaultDeallocateCallBack( void * ptr, void * info )
{
    ( void )info;
    
    free( ptr );
}

static void * CFAllocatorNullAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )allocSize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorNullReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )ptr;
    ( void )newsize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void CFAllocatorNullDeallocateCallBack( void * ptr, void * info )
{
    ( void )ptr;
    ( void )info;
}

static CFIndex CFAllocatorNullPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info )
{
    ( void )size;
    ( void )hint;
    ( void )info;
    
    return 0;
}
