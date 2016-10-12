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
 * @file        CFData.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>

struct CFData
{
    CFRuntimeBase _base;
};

static CFStringRef CFDataCopyDescription( CFDataRef Data );

static CFTypeID CFDataTypeID      = 0;
static CFRuntimeClass CFDataClass =
{
    "CFData",
    sizeof( struct CFData ),
    NULL,
    NULL,
    NULL,
    NULL,
    ( CFStringRef ( * )( CFTypeRef ) )CFDataCopyDescription
};

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFDataTypeID = CFRuntimeRegisterClass( &CFDataClass );
}

static CFStringRef CFDataCopyDescription( CFDataRef data )
{
    ( void )data;
    
    return NULL;
}

CFTypeID CFDataGetTypeID( void )
{
    return CFDataTypeID;
}

CFDataRef CFDataCreate( CFAllocatorRef allocator, const UInt8 * bytes, CFIndex length )
{
    ( void )allocator;
    ( void )bytes;
    ( void )length;
    
    return NULL;
}

CFDataRef CFDataCreateCopy( CFAllocatorRef allocator, CFDataRef theData )
{
    ( void )allocator;
    ( void )theData;
    
    return NULL;
}

CFDataRef CFDataCreateWithBytesNoCopy( CFAllocatorRef allocator, const UInt8 * bytes, CFIndex length, CFAllocatorRef bytesDeallocator )
{
    ( void )allocator;
    ( void )bytes;
    ( void )length;
    ( void )bytesDeallocator;
    
    return NULL;
}

const UInt8 * CFDataGetBytePtr( CFDataRef theData )
{
    ( void )theData;
    
    return NULL;
}

void CFDataGetBytes( CFDataRef theData, CFRange range, UInt8 * buffer )
{
    ( void )theData;
    ( void )range;
    ( void )buffer;
}

CFIndex CFDataGetLength( CFDataRef theData )
{
    ( void )theData;
    
    return 0;
}

CFRange CFDataFind( CFDataRef theData, CFDataRef dataToFind, CFRange searchRange, CFDataSearchFlags compareOptions )
{
    ( void )theData;
    ( void )dataToFind;
    ( void )searchRange;
    ( void )compareOptions;
    
    return CFRangeMake( 0, 0 );
}
