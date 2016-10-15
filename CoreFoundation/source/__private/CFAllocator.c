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

#include <CoreFoundation/__private/CFAllocator.h>
#include <string.h>
#include <stdio.h>

CFTypeID       CFAllocatorTypeID = 0;
CFRuntimeClass CFAllocatorClass  =
{
    "CFAllocator",
    sizeof( struct CFAllocator ),
    ( void ( * )( CFTypeRef ) )CFAllocatorConstruct,
    ( void ( * )( CFTypeRef ) )CFAllocatorDestruct,
    NULL,
    NULL,
    ( CFStringRef ( * )( CFTypeRef ) )CFAllocatorCopyDescription
};

struct CFAllocator CFAllocatorSystemDefault;
struct CFAllocator CFAllocatorMalloc;
struct CFAllocator CFAllocatorMallocZone;
struct CFAllocator CFAllocatorNull;

const CFAllocatorRef kCFAllocatorDefault        = NULL;
const CFAllocatorRef kCFAllocatorSystemDefault  = ( const CFAllocatorRef )( &CFAllocatorSystemDefault );
const CFAllocatorRef kCFAllocatorMalloc         = ( const CFAllocatorRef )( &CFAllocatorMalloc );
const CFAllocatorRef kCFAllocatorMallocZone     = ( const CFAllocatorRef )( &CFAllocatorMallocZone );
const CFAllocatorRef kCFAllocatorNull           = ( const CFAllocatorRef )( &CFAllocatorNull );
const CFAllocatorRef kCFAllocatorUseContext     = ( const CFAllocatorRef )( -1 );

CFThreadingKey CFAllocatorDefaultKey;

void CFAllocatorConstruct( CFAllocatorRef allocator )
{
    #if defined( CF_ALLOCATOR_DEBUG ) && CF_ALLOCATOR_DEBUG == 1
    
    struct CFAllocator * a;
    
    a = ( struct CFAllocator * )allocator;
    
    a->_registry     = calloc( sizeof( CFAllocatorRegistry ), 1024 );
    a->_registrySize = 1024;
    
    #else
    
    ( void )allocator;
    
    #endif
}

void CFAllocatorDestruct( CFAllocatorRef allocator )
{
    CFAllocatorRegistry * registry;
    CFIndex               registrySize;
    struct CFAllocator  * a;
    CFIndex               i;
    CFIndex               n;
    
    a = ( struct CFAllocator * )allocator;
    
    if( a->_registry == NULL )
    {
        return;
    }
    
    CFSpinLockLock( &( a->_registryLock ) );
    
    registry         = a->_registry;
    registrySize     = a->_registrySize;
    a->_registry     = NULL;
    a->_registrySize = 0;
    
    CFSpinLockUnlock( &( a->_registryLock ) );
    
    n = 0;
    
    for( i = 0; i < registrySize; i++ )
    {
        if( registry[ i ].ptr )
        {
            if( registry[ i ].hint == 1 && CFRuntimeIsConstantObject( registry[ i ].ptr ) )
            {
                continue;
            }
            
            n++;
        }
    }
    
    if( n )
    {
        CFAllocatorDebugReportLeaks( allocator, registry, registrySize );
    }
    
    free( a->_registry );
    
    if( allocator->_context.release )
    {
        allocator->_context.release( allocator->_context.info );
    }
}

CFStringRef CFAllocatorCopyDescription( CFAllocatorRef allocator )
{
    const char * name;
    
    if( allocator == kCFAllocatorSystemDefault )
    {
        name = " kCFAllocatorSystemDefault";
    }
    else if( allocator == kCFAllocatorMalloc )
    {
        name = " kCFAllocatorMalloc";
    }
    else if( allocator == kCFAllocatorMallocZone )
    {
        name = " kCFAllocatorMallocZone";
    }
    else if( allocator == kCFAllocatorNull )
    {
        name = " kCFAllocatorNull";
    }
    else
    {
        name = "";
    }
    
    return CFStringCreateWithFormat
    (
        NULL,
        NULL,
        CFSTR( "{ info = 0x%lu }%s" ),
        allocator->_context.info,
        name
    );
}

void CFAllocatorDebugRegisterAlloc( CFAllocatorRef allocator, const void * ptr, CFOptionFlags hint )
{
    struct CFAllocator * a;
    CFIndex              i;
    
    a = ( struct CFAllocator * )allocator;
    
    if( a->_registry == NULL || ptr == NULL )
    {
        return;
    }
    
    CFSpinLockLock( &( a->_registryLock ) );
    
    add:
        
        for( i = 0; i < a->_registrySize; i++ )
        {
            if( a->_registry[ i ].ptr == NULL )
            {
                a->_registry[ i ].ptr  = ptr;
                a->_registry[ i ].hint = hint;
                
                CFSpinLockUnlock( &( a->_registryLock ) );
                
                return;
            }
        }
        
        a->_registry = realloc( a->_registry, 2 * ( size_t )( a->_registrySize ) * sizeof( void * ) );
        
        memset( a->_registry + a->_registrySize, 0, a->_registrySize );
        
        a->_registrySize *= 2;
        
        if( a->_registry == NULL )
        {
            CFSpinLockUnlock( &( a->_registryLock ) );
            
            return;
        }
        
        goto add;
}

void CFAllocatorDebugRegisterRealloc( CFAllocatorRef allocator, const void * oldPtr, const void * newPtr )
{
    struct CFAllocator * a;
    CFIndex              i;
    
    a = ( struct CFAllocator * )allocator;
    
    if( a->_registry == NULL || oldPtr == NULL || newPtr == NULL )
    {
        return;
    }
    
    CFSpinLockLock( &( a->_registryLock ) );
    
    for( i = 0; i < a->_registrySize; i++ )
    {
        if( a->_registry[ i ].ptr == oldPtr )
        {
            a->_registry[ i ].ptr = newPtr;
            
            break;
        }
    }
    
    CFSpinLockUnlock( &( a->_registryLock ) );
}

void CFAllocatorDebugRegisterFree( CFAllocatorRef allocator, const void * ptr )
{
    struct CFAllocator * a;
    CFIndex              i;
    
    a = ( struct CFAllocator * )allocator;
    
    if( a->_registry == NULL || ptr == NULL )
    {
        return;
    }
    
    CFSpinLockLock( &( a->_registryLock ) );
    
    for( i = 0; i < a->_registrySize; i++ )
    {
        if( a->_registry[ i ].ptr == ptr )
        {
            a->_registry[ i ].ptr  = NULL;
            a->_registry[ i ].hint = 0;
            
            break;
        }
    }
    
    CFSpinLockUnlock( &( a->_registryLock ) );
}

void CFAllocatorDebugReportLeaks( CFAllocatorRef allocator, CFAllocatorRegistry * registry, CFIndex registrySize )
{
    struct CFAllocator * a;
    CFIndex              n;
    CFIndex              i;
    CFStringRef          description;
    char               * buf;
    
    a = ( struct CFAllocator * )allocator;
    
    if( registry == NULL || registrySize == 0 )
    {
        return;
    }
    
    description = CFCopyDescription( allocator );
    
    if( description == NULL )
    {
        return;
    }
    
    buf = calloc( ( size_t )CFStringGetLength( description ) + 1, 1 );
    
    if( buf == NULL || CFStringGetCString( description, buf , CFStringGetLength( description ) + 1, kCFStringEncodingASCII ) == false )
    {
        CFRelease( description );
        free( buf );
        
        return;
    }
    
    n = 0;
    
    for( i = 0; i < registrySize; i++ )
    {
        if( registry[ i ].ptr != NULL )
        {
            if( registry[ i ].hint == 1 && CFRuntimeIsConstantObject( registry[ i ].ptr ) )
            {
                continue;
            }
            
            n++;
        }
    }
    
    fprintf
    (
        stderr,
        "\n"
        "*** CoreFoundation - WARNING\n"
        "*** Deleting an instance of CFAllocator while allocations are still active.\n"
        "*** Leaking memory.\n"
        "\n"
        "- Allocator:       %s\n"
        "- Active records:  %li\n"
        "- Records:\n"
        "{\n",
        buf,
        n
    );
    
    CFRelease( description );
    free( buf );
    
    description = NULL;
    buf         = NULL;
    
    n = 0;
    
    for( i = 0; i < registrySize; i++ )
    {
        if( registry[ i ].ptr == NULL )
        {
            continue;
        }
        
        if( registry[ i ].hint == 1 && CFRuntimeIsConstantObject( registry[ i ].ptr ) )
        {
            continue;
        }
        
        if( registry[ i ].hint == 1 )
        {
            description = CFCopyDescription( registry[ i ].ptr );
            
            if( description != NULL )
            {
                buf = calloc( ( size_t )CFStringGetLength( description ) + 1, 1 );
            }
            
            if( buf == NULL || CFStringGetCString( description, buf, CFStringGetLength( description ) + 1, kCFStringEncodingASCII ) == false )
            {
                CFRelease( description );
                free( buf );
                
                description = NULL;
                buf         = NULL;
            }
        }
        
        if( buf )
        {
            fprintf( stderr, "    %li. %s\n", ++n, buf );
            
            CFRelease( description );
            free( buf );
            
            description = NULL;
            buf         = NULL;
        }
        else
        {
            fprintf( stderr, "    %li. 0x%lx\n", ++n, ( unsigned long )( registry[ i ].ptr ) );
        }
    }
    
    fprintf( stderr, "}\n\n" );
}

void CFAllocatorExit( void )
{
    CFAllocatorDestruct( &CFAllocatorSystemDefault );
    CFAllocatorDestruct( &CFAllocatorMalloc );
    CFAllocatorDestruct( &CFAllocatorMallocZone );
    CFAllocatorDestruct( &CFAllocatorNull );
}

void * CFAllocatorSystemDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )hint;
    ( void )info;
    
    if( allocSize <= 0 )
    {
        return NULL;
    }
    
    return calloc( ( size_t )allocSize, 1 );
}

void * CFAllocatorSystemDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )hint;
    ( void )info;
    
    return realloc( ptr, ( size_t )newsize );
}

void CFAllocatorSystemDefaultDeallocateCallBack( void * ptr, void * info )
{
    ( void )info;
    
    free( ptr );
}

void * CFAllocatorNullAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )allocSize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

void * CFAllocatorNullReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )ptr;
    ( void )newsize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

void CFAllocatorNullDeallocateCallBack( void * ptr, void * info )
{
    ( void )ptr;
    ( void )info;
}

CFIndex CFAllocatorNullPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info )
{
    ( void )size;
    ( void )hint;
    ( void )info;
    
    return 0;
}
