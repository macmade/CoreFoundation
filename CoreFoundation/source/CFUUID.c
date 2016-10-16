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
#include <string.h>
#include <stdio.h>

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
    #ifdef _WIN32
    
    UUID        u;
    char      * str;
    CFStringRef s;
    CFUUIDRef   o;

    memset( &u, 0, sizeof( UUID ) );
    
    if( UuidCreate( &u ) != RPC_S_OK )
    {
        return NULL;
    }

    if( UuidToStringA( &u, &str ) != RPC_S_OK )
    {
        return NULL;
    }
    
    s = CFStringCreateWithCString( NULL, str, kCFStringEncodingASCII );
    
    RpcStringFreeA( &str );
    
    if( s == NULL )
    {
        return NULL;
    }
    
    o = CFUUIDCreateFromString( NULL, s );
    
    CFRelease( s );

    return o;

    #else
    
    uuid_t    u;
    CFUUIDRef o;

    memset( u, 0, sizeof( uuid_t ) );
    uuid_generate( u );
    
    o = CFUUIDGetConstantUUIDWithBytes
    (
        alloc,
        u[  0 ],
        u[  1 ],
        u[  2 ],
        u[  3 ],
        u[  4 ],
        u[  5 ],
        u[  6 ],
        u[  7 ],
        u[  8 ],
        u[  9 ],
        u[ 10 ],
        u[ 11 ],
        u[ 12 ],
        u[ 13 ],
        u[ 14 ],
        u[ 15 ]
    );

    return ( o ) ? CFRetain( o ) : NULL;

    #endif
}

CFUUIDRef CFUUIDCreateFromString( CFAllocatorRef alloc, CFStringRef uuidStr )
{
    char      buf[ 37 ];
    CFUUIDRef o;
    
    if( uuidStr == NULL || CFStringGetLength( uuidStr ) != 36 )
    {
        return NULL;
    }
    
    if( CFStringGetCString( uuidStr, buf, sizeof( buf ), kCFStringEncodingASCII ) == false )
    {
        return NULL;
    }
    
    if
    (
           buf[  8 ] != '-'
        || buf[ 13 ] != '-'
        || buf[ 18 ] != '-'
        || buf[ 23 ] != '-'
    )
    {
        return NULL;
    }
    
    o = CFUUIDGetConstantUUIDWithBytes
    (
        alloc,
        CFUUIDByteFromHexChar( &( buf[  0 ] ) ),
        CFUUIDByteFromHexChar( &( buf[  2 ] ) ),
        CFUUIDByteFromHexChar( &( buf[  4 ] ) ),
        CFUUIDByteFromHexChar( &( buf[  6 ] ) ),
        CFUUIDByteFromHexChar( &( buf[  9 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 11 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 14 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 16 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 19 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 21 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 24 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 26 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 28 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 30 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 32 ] ) ),
        CFUUIDByteFromHexChar( &( buf[ 34 ] ) )
    );
    
    return ( o ) ? CFRetain( o ) : NULL;
}

CFUUIDRef CFUUIDCreateFromUUIDBytes( CFAllocatorRef alloc, CFUUIDBytes bytes )
{
    CFUUIDRef o;
    
    o = CFUUIDGetConstantUUIDWithBytes
    (
        alloc,
        bytes.byte0,
        bytes.byte1,
        bytes.byte2,
        bytes.byte3,
        bytes.byte4,
        bytes.byte5,
        bytes.byte6,
        bytes.byte7,
        bytes.byte8,
        bytes.byte9,
        bytes.byte10,
        bytes.byte11,
        bytes.byte12,
        bytes.byte13,
        bytes.byte14,
        bytes.byte15
    );
    
    return ( o ) ? CFRetain( o ) : NULL;
}

CFUUIDRef CFUUIDCreateWithBytes( CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15 )
{
    CFUUIDRef o;
    
    o = CFUUIDGetConstantUUIDWithBytes
    (
        alloc,
        byte0,
        byte1,
        byte2,
        byte3,
        byte4,
        byte5,
        byte6,
        byte7,
        byte8,
        byte9,
        byte10,
        byte11,
        byte12,
        byte13,
        byte14,
        byte15
    );
    
    return ( o ) ? CFRetain( o ) : NULL;
}

CFStringRef CFUUIDCreateString( CFAllocatorRef alloc, CFUUIDRef uuid )
{
    if( uuid == NULL )
    {
        return NULL;
    }
    
    return CFStringCreateWithFormat
    (
        alloc,
        NULL,
        CFSTR( "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X" ),
        uuid->_bytes.byte0,
        uuid->_bytes.byte1,
        uuid->_bytes.byte2,
        uuid->_bytes.byte3,
        uuid->_bytes.byte4,
        uuid->_bytes.byte5,
        uuid->_bytes.byte6,
        uuid->_bytes.byte7,
        uuid->_bytes.byte8,
        uuid->_bytes.byte9,
        uuid->_bytes.byte10,
        uuid->_bytes.byte11,
        uuid->_bytes.byte12,
        uuid->_bytes.byte13,
        uuid->_bytes.byte14,
        uuid->_bytes.byte15
    );
}

CFUUIDRef CFUUIDGetConstantUUIDWithBytes( CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15 )
{
    struct CFUUID * o;
    
    o = ( struct CFUUID * )CFRuntimeCreateInstance( alloc, CFUUIDTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    o->_bytes.byte0  = byte0;
    o->_bytes.byte1  = byte1;
    o->_bytes.byte2  = byte2;
    o->_bytes.byte3  = byte3;
    o->_bytes.byte4  = byte4;
    o->_bytes.byte5  = byte5;
    o->_bytes.byte6  = byte6;
    o->_bytes.byte7  = byte7;
    o->_bytes.byte8  = byte8;
    o->_bytes.byte8  = byte9;
    o->_bytes.byte10 = byte10;
    o->_bytes.byte11 = byte11;
    o->_bytes.byte12 = byte12;
    o->_bytes.byte13 = byte13;
    o->_bytes.byte14 = byte14;
    o->_bytes.byte15 = byte15;
    
    return o;
}

CFUUIDBytes CFUUIDGetUUIDBytes( CFUUIDRef uuid )
{
    if( uuid == NULL )
    {
        return CFUUIDNullBytes;
    }
    
    return uuid->_bytes;
}
