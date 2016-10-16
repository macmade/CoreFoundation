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

#include <CoreFoundation/__private/__CFUUID.h>

CFTypeID       CFUUIDTypeID = 0;
CFRuntimeClass CFUUIDClass  =
{
    "CFUUID",
    sizeof( struct CFUUID ),
    NULL,
    NULL,
    ( CFHashCode ( * )( CFTypeRef ) )CFUUIDHash,
    ( bool ( * )( CFTypeRef, CFTypeRef ) )CFUUIDEquals,
    ( CFStringRef ( * )( CFTypeRef ) )CFUUIDCopyDescription
};

CFUUIDBytes CFUUIDNullBytes = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void CFUUIDInitialize( void )
{
    CFUUIDTypeID = CFRuntimeRegisterClass( &CFUUIDClass );
}

CF_EXPORT CFHashCode CFUUIDHash( CFUUIDRef u )
{
    CFIndex    i;
    CFHashCode h;
    UInt8      b[ 16 ];
    
    h       = 0;
    b[  0 ] = u->_bytes.byte0;
    b[  1 ] = u->_bytes.byte1;
    b[  2 ] = u->_bytes.byte2;
    b[  3 ] = u->_bytes.byte3;
    b[  4 ] = u->_bytes.byte4;
    b[  5 ] = u->_bytes.byte5;
    b[  6 ] = u->_bytes.byte6;
    b[  7 ] = u->_bytes.byte7;
    b[  8 ] = u->_bytes.byte8;
    b[  9 ] = u->_bytes.byte9;
    b[ 10 ] = u->_bytes.byte10;
    b[ 11 ] = u->_bytes.byte11;
    b[ 12 ] = u->_bytes.byte12;
    b[ 13 ] = u->_bytes.byte13;
    b[ 14 ] = u->_bytes.byte14;
    b[ 15 ] = u->_bytes.byte15;
    
    for( i = 0; i < 16; i++ )
    {
        h = h * 31 + b[ i ];
    }
    
    return h;
}

CF_EXPORT bool CFUUIDEquals( CFUUIDRef u1, CFUUIDRef u2 )
{
    if
    (
           u1->_bytes.byte0  == u2->_bytes.byte0
        && u1->_bytes.byte1  == u2->_bytes.byte1
        && u1->_bytes.byte2  == u2->_bytes.byte2
        && u1->_bytes.byte3  == u2->_bytes.byte3
        && u1->_bytes.byte4  == u2->_bytes.byte4
        && u1->_bytes.byte5  == u2->_bytes.byte5
        && u1->_bytes.byte6  == u2->_bytes.byte6
        && u1->_bytes.byte7  == u2->_bytes.byte7
        && u1->_bytes.byte8  == u2->_bytes.byte8
        && u1->_bytes.byte9  == u2->_bytes.byte9
        && u1->_bytes.byte10 == u2->_bytes.byte10
        && u1->_bytes.byte11 == u2->_bytes.byte11
        && u1->_bytes.byte12 == u2->_bytes.byte12
        && u1->_bytes.byte13 == u2->_bytes.byte13
        && u1->_bytes.byte14 == u2->_bytes.byte14
        && u1->_bytes.byte15 == u2->_bytes.byte15
    )
    {
        return true;
    }
    
    return false;
}

CF_EXPORT CFStringRef CFUUIDCopyDescription( CFUUIDRef u )
{
    return CFUUIDCreateString( NULL, u );
}


UInt8 CFUUIDByteFromHexChar( char * s )
{
    char x[ 3 ];
    
    x[ 0 ] = s[ 0 ];
    x[ 1 ] = s[ 1 ];
    x[ 2 ] = 0;
    
    return ( UInt8 )strtoul( x, NULL, 16 );
}
