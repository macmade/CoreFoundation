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

#include <CoreFoundation/__private/CFData.h>
#include <string.h>
#include <stdio.h>

CFTypeID       CFDataTypeID = 0;
CFRuntimeClass CFDataClass  =
{
    "CFData",
    sizeof( struct CFData ),
    NULL,
    ( void ( * )( CFTypeRef ) )CFDataDestruct,
    ( CFHashCode ( * )( CFTypeRef ) )CFDataHash,
    ( bool ( * )( CFTypeRef, CFTypeRef ) )CFDataEquals,
    ( CFStringRef ( * )( CFTypeRef ) )CFDataCopyDescription
};

void CFDataDestruct( CFDataRef data )
{
    if( data->_bytes )
    {
        CFAllocatorDeallocate( data->_deallocator, ( void * )( data->_bytes ) );
    }
    
    if( data->_deallocator )
    {
        CFRelease( data->_deallocator );
    }
}

CFHashCode CFDataHash( CFDataRef data )
{
    CFIndex               i;
    CFHashCode            h;
    const unsigned char * cp;
    
    if( data->_bytes == NULL )
    {
        return ( CFHashCode )data;
    }
    
    h  = 0;
    cp = data->_bytes;
    
    for( i = 0; i < data->_length; i++ )
    {
        h = h * 31 + *( cp++ );
    }
    
    return h;
}

bool CFDataEquals( CFDataRef d1, CFDataRef d2 )
{
    if( d1->_bytes == NULL || d2->_bytes == NULL )
    {
        return false;
    }
    
    if( d1->_bytes == d2->_bytes )
    {
        return true;
    }
    
    if( d1->_length != d2->_length )
    {
        return false;
    }
    
    return memcmp( d1->_bytes, d2->_bytes, ( size_t )( d1->_length ) ) == 0;
}

CFStringRef CFDataCopyDescription( CFDataRef data )
{
    CFIndex i;
    char    buf[ 41 ];
    UInt8   b;
    bool    partial;
    
    if( data->_bytes == NULL || data->_length == 0 )
    {
        return NULL;
    }
    
    memset( buf, 0, sizeof( buf ) );
    
    partial = false;
    
    for( i = 0; i < data->_length; i++ )
    {
        if( i == ( sizeof( buf ) - 1 ) / 2 )
        {
            partial = true;
            
            break;
        }
        
        b = *( data->_bytes + i );
        
        sprintf( buf + ( i * 2 ), "%02x", ( unsigned int )b );
    }
    
    if( partial )
    {
        return CFStringCreateWithFormat
        (
            NULL,
            NULL,
            CFSTR( "{ length = %li, type = %s, bytes = 0x%s ... }" ),
            ( long )( data->_length ),
            ( data->_mutable ) ? "mutable" : "immutable",
            buf
        );
    }
    
    return CFStringCreateWithFormat
    (
        NULL,
        NULL,
        CFSTR( "{ length = %li, bytes = 0x%s }" ),
        ( long )( data->_length ),
        buf
    );
}
