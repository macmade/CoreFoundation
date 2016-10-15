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
#include <CoreFoundation/__private/__CFData.h>
#include <CoreFoundation/__private/__CFRuntime.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

CFTypeID CFDataGetTypeID( void )
{
    return CFDataTypeID;
}

CFDataRef CFDataCreate( CFAllocatorRef allocator, const UInt8 * bytes, CFIndex length )
{
    struct CFData * o;
    UInt8         * buf;
    
    if( bytes == NULL || length == 0 )
    {
        return NULL;
    }
    
    o = ( struct CFData * )CFRuntimeCreateInstance( allocator, CFDataTypeID );
    
    if( o )
    {
        buf = CFAllocatorAllocate( allocator, length, 0 );
        
        if( buf == NULL )
        {
            CFRelease( o );
            CFRuntimeAbortWithOutOfMemoryError();
            
            return NULL;
        }
        
        memcpy( buf, bytes, ( size_t )length );
        
        o->_bytes       = buf;
        o->_length      = length;
        o->_deallocator = ( allocator ) ? CFRetain( allocator ) : NULL;
    }
    
    return o;
}

CFDataRef CFDataCreateCopy( CFAllocatorRef allocator, CFDataRef theData )
{
    if( theData == NULL )
    {
        return NULL;
    }
    
    return CFDataCreate( allocator, theData->_bytes, theData->_length );
}

CFDataRef CFDataCreateWithBytesNoCopy( CFAllocatorRef allocator, const UInt8 * bytes, CFIndex length, CFAllocatorRef bytesDeallocator )
{
    struct CFData * o;
    
    if( bytes == NULL || length == 0 )
    {
        return NULL;
    }
    
    o = ( struct CFData * )CFRuntimeCreateInstance( allocator, CFDataTypeID );
    
    if( o )
    {
        o->_bytes       = bytes;
        o->_length      = length;
        o->_deallocator = ( bytesDeallocator ) ? CFRetain( bytesDeallocator ) : NULL;
    }
    
    return o;
}

const UInt8 * CFDataGetBytePtr( CFDataRef theData )
{
    if( theData == NULL )
    {
        return NULL;
    }
    
    return theData->_bytes;
}

void CFDataGetBytes( CFDataRef theData, CFRange range, UInt8 * buffer )
{
    if( theData == NULL || buffer == NULL || range.length == 0 )
    {
        return;
    }
}

CFIndex CFDataGetLength( CFDataRef theData )
{
    if( theData == NULL )
    {
        return 0;
    }
    
    return theData->_length;
}

CFRange CFDataFind( CFDataRef theData, CFDataRef dataToFind, CFRange searchRange, CFDataSearchFlags compareOptions )
{
    ( void )theData;
    ( void )dataToFind;
    ( void )searchRange;
    ( void )compareOptions;
    
    return CFRangeMake( kCFNotFound, 0 );
}
