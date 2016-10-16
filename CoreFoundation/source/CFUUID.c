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
 * @file        CFUUID.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/__CFUUID.h>

#ifdef _WIN32
#include <Rpc.h>
#else
#include <uuid/uuid.h>
#endif

CFTypeID CFUUIDGetTypeID( void )
{
    return CFUUIDTypeID;
}

CFUUIDRef CFUUIDCreate( CFAllocatorRef alloc )
{
    ( void )alloc;
    
    return NULL;
}

CFUUIDRef CFUUIDCreateFromString( CFAllocatorRef alloc, CFStringRef uuidStr )
{
    ( void )alloc;
    ( void )uuidStr;
    
    return NULL;
}

CFUUIDRef CFUUIDCreateFromUUIDBytes( CFAllocatorRef alloc, CFUUIDBytes bytes )
{
    ( void )alloc;
    ( void )bytes;
    
    return NULL;
}

CFUUIDRef CFUUIDCreateWithBytes( CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15 )
{
    ( void )alloc;
    ( void )alloc;
    ( void )byte0;
    ( void )byte1;
    ( void )byte2;
    ( void )byte3;
    ( void )byte4;
    ( void )byte5;
    ( void )byte6;
    ( void )byte7;
    ( void )byte8;
    ( void )byte9;
    ( void )byte10;
    ( void )byte11;
    ( void )byte12;
    ( void )byte13;
    ( void )byte14;
    ( void )byte15;
    
    return NULL;
}

CFStringRef CFUUIDCreateString( CFAllocatorRef alloc, CFUUIDRef uuid )
{
    if( uuid == NULL )
    {
        return NULL;
    }
    
    ( void )alloc;
    
    return NULL;
}

CFUUIDRef CFUUIDGetConstantUUIDWithBytes( CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15 )
{
    ( void )alloc;
    ( void )byte0;
    ( void )byte1;
    ( void )byte2;
    ( void )byte3;
    ( void )byte4;
    ( void )byte5;
    ( void )byte6;
    ( void )byte7;
    ( void )byte8;
    ( void )byte9;
    ( void )byte10;
    ( void )byte11;
    ( void )byte12;
    ( void )byte13;
    ( void )byte14;
    ( void )byte15;
    
    return NULL;
}

CFUUIDBytes CFUUIDGetUUIDBytes( CFUUIDRef uuid )
{
    if( uuid == NULL )
    {
        return CFUUIDNullBytes;
    }
    
    return uuid->_bytes;
}
