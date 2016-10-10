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
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct CFAllocator
{
    CFRuntimeBase       _base;
    CFAllocatorContext  _context;
};

/* Callbacks for kCFAllocatorSystemDefault */
static const void * CFAllocatorSystemDefaultRetainCallBack( const void * info );
static void         CFAllocatorSystemDefaultReleaseCallBack( const void * info );
static CFStringRef  CFAllocatorSystemDefaultCopyDescriptionCallBack( const void * info );
static void       * CFAllocatorSystemDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
static void       * CFAllocatorSystemDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
static void         CFAllocatorSystemDefaultDeallocateCallBack( void * ptr, void * info );
static CFIndex      CFAllocatorSystemDefaultPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info );

/* Callbacks for kCFAllocatorMalloc */
static const void * CFAllocatorMallocRetainCallBack( const void * info );
static void         CFAllocatorMallocReleaseCallBack( const void * info );
static CFStringRef  CFAllocatorMallocCopyDescriptionCallBack( const void * info );
static void       * CFAllocatorMallocAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
static void       * CFAllocatorMallocReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
static void         CFAllocatorMallocDeallocateCallBack( void * ptr, void * info );
static CFIndex      CFAllocatorMallocPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info );

/* Callbacks for CFAllocatorMallocZone */
static const void * CFAllocatorMallocZoneRetainCallBack( const void * info );
static void         CFAllocatorMallocZoneReleaseCallBack( const void * info );
static CFStringRef  CFAllocatorMallocZoneCopyDescriptionCallBack( const void * info );
static void       * CFAllocatorMallocZoneAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
static void       * CFAllocatorMallocZoneReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
static void         CFAllocatorMallocZoneDeallocateCallBack( void * ptr, void * info );
static CFIndex      CFAllocatorMallocZonePreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info );

/* Callbacks for CFAllocatorNull */
static const void * CFAllocatorNullRetainCallBack( const void * info );
static void         CFAllocatorNullReleaseCallBack( const void * info );
static CFStringRef  CFAllocatorNullCopyDescriptionCallBack( const void * info );
static void       * CFAllocatorNullAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
static void       * CFAllocatorNullReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
static void         CFAllocatorNullDeallocateCallBack( void * ptr, void * info );
static CFIndex      CFAllocatorNullPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info );

static CFTypeID CFAllocatorTypeID      = 0;
static CFRuntimeClass CFAllocatorClass =
{
    "CFAllocator",
    sizeof( struct CFAllocator ),
    NULL,
    NULL,
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

static pthread_key_t CFAllocatorDefaultKey; 

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    pthread_key_create( &CFAllocatorDefaultKey, NULL );
    
    CFAllocatorTypeID = _CFRuntimeRegisterClass( &CFAllocatorClass );
    
    _CFRuntimeInitStaticInstance( &CFAllocatorSystemDefault, CFAllocatorTypeID );
    _CFRuntimeInitStaticInstance( &CFAllocatorMalloc,        CFAllocatorTypeID );
    _CFRuntimeInitStaticInstance( &CFAllocatorMallocZone,    CFAllocatorTypeID );
    _CFRuntimeInitStaticInstance( &CFAllocatorNull,          CFAllocatorTypeID );
    
    CFAllocatorSystemDefault._context.allocate        = CFAllocatorSystemDefaultAllocateCallBack;
    CFAllocatorSystemDefault._context.copyDescription = CFAllocatorSystemDefaultCopyDescriptionCallBack;
    CFAllocatorSystemDefault._context.deallocate      = CFAllocatorSystemDefaultDeallocateCallBack;
    CFAllocatorSystemDefault._context.preferredSize   = CFAllocatorSystemDefaultPreferredSizeCallBack;
    CFAllocatorSystemDefault._context.reallocate      = CFAllocatorSystemDefaultReallocateCallBack;
    CFAllocatorSystemDefault._context.release         = CFAllocatorSystemDefaultReleaseCallBack;
    CFAllocatorSystemDefault._context.retain          = CFAllocatorSystemDefaultRetainCallBack;
    
    CFAllocatorMalloc._context.allocate        = CFAllocatorMallocAllocateCallBack;
    CFAllocatorMalloc._context.copyDescription = CFAllocatorMallocCopyDescriptionCallBack;
    CFAllocatorMalloc._context.deallocate      = CFAllocatorMallocDeallocateCallBack;
    CFAllocatorMalloc._context.preferredSize   = CFAllocatorMallocPreferredSizeCallBack;
    CFAllocatorMalloc._context.reallocate      = CFAllocatorMallocReallocateCallBack;
    CFAllocatorMalloc._context.release         = CFAllocatorMallocReleaseCallBack;
    CFAllocatorMalloc._context.retain          = CFAllocatorMallocRetainCallBack;
    
    CFAllocatorMallocZone._context.allocate        = CFAllocatorMallocZoneAllocateCallBack;
    CFAllocatorMallocZone._context.copyDescription = CFAllocatorMallocZoneCopyDescriptionCallBack;
    CFAllocatorMallocZone._context.deallocate      = CFAllocatorMallocZoneDeallocateCallBack;
    CFAllocatorMallocZone._context.preferredSize   = CFAllocatorMallocZonePreferredSizeCallBack;
    CFAllocatorMallocZone._context.reallocate      = CFAllocatorMallocZoneReallocateCallBack;
    CFAllocatorMallocZone._context.release         = CFAllocatorMallocZoneReleaseCallBack;
    CFAllocatorMallocZone._context.retain          = CFAllocatorMallocZoneRetainCallBack;
    
    CFAllocatorNull._context.allocate        = CFAllocatorNullAllocateCallBack;
    CFAllocatorNull._context.copyDescription = CFAllocatorNullCopyDescriptionCallBack;
    CFAllocatorNull._context.deallocate      = CFAllocatorNullDeallocateCallBack;
    CFAllocatorNull._context.preferredSize   = CFAllocatorNullPreferredSizeCallBack;
    CFAllocatorNull._context.reallocate      = CFAllocatorNullReallocateCallBack;
    CFAllocatorNull._context.release         = CFAllocatorNullReleaseCallBack;
    CFAllocatorNull._context.retain          = CFAllocatorNullRetainCallBack;
}

CFTypeID CFAllocatorGetTypeID( void )
{
    return CFAllocatorTypeID;
}

CFAllocatorRef CFAllocatorCreate( CFAllocatorRef allocator, CFAllocatorContext * context )
{
    ( void )allocator;
    ( void )context;
    
    return NULL;
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
    
    current = pthread_getspecific( CFAllocatorDefaultKey );
    
    return ( current == NULL ) ? kCFAllocatorSystemDefault : current;
}

void CFAllocatorSetDefault( CFAllocatorRef allocator )
{
    CFAllocatorRef current;
    
    current = pthread_getspecific( CFAllocatorDefaultKey );
    
    if( current )
    {
        CFRelease( current );
    }
    
    if( allocator )
    {
        CFRetain( allocator );
    }
    
    pthread_setspecific( CFAllocatorDefaultKey, allocator );
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

static const void * CFAllocatorSystemDefaultRetainCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void CFAllocatorSystemDefaultReleaseCallBack( const void * info )
{
    ( void )info;
}

static CFStringRef CFAllocatorSystemDefaultCopyDescriptionCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorSystemDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )allocSize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorSystemDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )ptr;
    ( void )newsize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void CFAllocatorSystemDefaultDeallocateCallBack( void * ptr, void * info )
{
    ( void )ptr;
    ( void )info;
}

static CFIndex CFAllocatorSystemDefaultPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info )
{
    ( void )size;
    ( void )hint;
    ( void )info;
    
    return 0;
}

static const void * CFAllocatorMallocRetainCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void CFAllocatorMallocReleaseCallBack( const void * info )
{
    ( void )info;
}

static CFStringRef CFAllocatorMallocCopyDescriptionCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorMallocAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )allocSize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorMallocReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )ptr;
    ( void )newsize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void CFAllocatorMallocDeallocateCallBack( void * ptr, void * info )
{
    ( void )ptr;
    ( void )info;
}

static CFIndex CFAllocatorMallocPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info )
{
    ( void )size;
    ( void )hint;
    ( void )info;
    
    return 0;
}

static const void * CFAllocatorMallocZoneRetainCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void CFAllocatorMallocZoneReleaseCallBack( const void * info )
{
    ( void )info;
}

static CFStringRef CFAllocatorMallocZoneCopyDescriptionCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorMallocZoneAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )allocSize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorMallocZoneReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )ptr;
    ( void )newsize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void CFAllocatorMallocZoneDeallocateCallBack( void * ptr, void * info )
{
    ( void )ptr;
    ( void )info;
}

static CFIndex CFAllocatorMallocZonePreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info )
{
    ( void )size;
    ( void )hint;
    ( void )info;
    
    return 0;
}

static const void * CFAllocatorNullRetainCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void CFAllocatorNullReleaseCallBack( const void * info )
{
    ( void )info;
}

static CFStringRef CFAllocatorNullCopyDescriptionCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
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
