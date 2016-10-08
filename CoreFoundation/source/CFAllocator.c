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

typedef struct
{
    CFRuntimeBase       _base;
    CFAllocatorContext  _context;
}
CFAllocator;

static const void * CFAllocatorDefaultRetainCallBack( const void * info );
static void         CFAllocatorDefaultReleaseCallBack( const void * info );
static CFStringRef  CFAllocatorDefaultCopyDescriptionCallBack( const void * info );
static void       * CFAllocatorDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
static void       * CFAllocatorDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
static void         CFAllocatorDefaultDeallocateCallBack( void * ptr, void * info );
static CFIndex      CFAllocatorDefaultPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info );

static CFTypeID CFAllocatorTypeID = 0;

static CFRuntimeClass CFAllocatorClass =
{
    "CFAllocator",
    sizeof( CFAllocator ),
    NULL,
    NULL,
};

static CFAllocator CFAllocatorDefault;

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFAllocatorTypeID = _CFRuntimeRegisterClass( &CFAllocatorClass );
    
    _CFRuntimeInitStaticInstance( &CFAllocatorDefault, CFAllocatorTypeID );
    
    CFAllocatorDefault._context.allocate        = CFAllocatorDefaultAllocateCallBack;
    CFAllocatorDefault._context.copyDescription = CFAllocatorDefaultCopyDescriptionCallBack;
    CFAllocatorDefault._context.deallocate      = CFAllocatorDefaultDeallocateCallBack;
    CFAllocatorDefault._context.preferredSize   = CFAllocatorDefaultPreferredSizeCallBack;
    CFAllocatorDefault._context.reallocate      = CFAllocatorDefaultReallocateCallBack;
    CFAllocatorDefault._context.release         = CFAllocatorDefaultReleaseCallBack;
    CFAllocatorDefault._context.retain          = CFAllocatorDefaultRetainCallBack;
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
    ( void )allocator;
    ( void )size;
    ( void )hint;
    
    return NULL;
}

void CFAllocatorDeallocate( CFAllocatorRef allocator, void * ptr )
{
    ( void )allocator;
    ( void )ptr;
}

CFIndex CFAllocatorGetPreferredSizeForSize( CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint )
{
    ( void )allocator;
    ( void )size;
    ( void )hint;
    
    return 0;
}

void * CFAllocatorReallocate( CFAllocatorRef allocator, void * ptr, CFIndex newsize, CFOptionFlags hint )
{
    ( void )allocator;
    ( void )ptr;
    ( void )newsize;
    ( void )hint;
    
    return NULL;
}

CFAllocatorRef CFAllocatorGetDefault( void )
{
    return NULL;
}

void CFAllocatorSetDefault( CFAllocatorRef allocator )
{
    ( void )allocator;
}

void CFAllocatorGetContext( CFAllocatorRef allocator, CFAllocatorContext * context )
{
    ( void )allocator;
    ( void )context;
}

static const void * CFAllocatorDefaultRetainCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void CFAllocatorDefaultReleaseCallBack( const void * info )
{
    ( void )info;
}

static CFStringRef CFAllocatorDefaultCopyDescriptionCallBack( const void * info )
{
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info )
{
    ( void )allocSize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void * CFAllocatorDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info )
{
    ( void )ptr;
    ( void )newsize;
    ( void )hint;
    ( void )info;
    
    return NULL;
}

static void CFAllocatorDefaultDeallocateCallBack( void * ptr, void * info )
{
    ( void )ptr;
    ( void )info;
}

static CFIndex CFAllocatorDefaultPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info )
{
    ( void )size;
    ( void )hint;
    ( void )info;
    
    return 0;
}
