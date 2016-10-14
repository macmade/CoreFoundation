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

CFTypeID       CFAllocatorTypeID = 0;
CFRuntimeClass CFAllocatorClass  =
{
    "CFAllocator",
    sizeof( struct CFAllocator ),
    NULL,
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

void CFAllocatorDestruct( CFAllocatorRef allocator )
{
    if( allocator->_context.release )
    {
        allocator->_context.release( allocator->_context.info );
    }
}

CFStringRef CFAllocatorCopyDescription( CFAllocatorRef allocator )
{
    return CFStringCreateWithFormat
    (
        NULL,
        NULL,
        CFStringCreateWithCStringNoCopy( NULL, "{ info = 0x%lu }", kCFStringEncodingUTF8, kCFAllocatorNull ),
        allocator->_context.info
    );
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
