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
    ( void ( * )( CFTypeRef ) )CFUUIDDestruct,
    ( CFHashCode ( * )( CFTypeRef ) )CFUUIDHash,
    ( bool ( * )( CFTypeRef, CFTypeRef ) )CFUUIDEquals,
    ( CFStringRef ( * )( CFTypeRef ) )CFUUIDCopyDescription
};

CFSpinLock          CFUUIDsLock     = 0;
struct CFUUIDList * CFUUIDs         = NULL;
CFUUIDBytes         CFUUIDNullBytes = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void CFUUIDInitialize( void )
{
    CFUUIDTypeID = CFRuntimeRegisterClass( &CFUUIDClass );
}

void CFUUIDDestruct( CFUUIDRef u )
{
    struct CFUUIDList * list;
    struct CFUUIDList * prev;
    
    CFSpinLockLock( &CFUUIDsLock );
    
    if( CFUUIDs == NULL )
    {
        return;
    }
    
    list = CFUUIDs;
    prev = NULL;
    
    while( list )
    {
        if( u == list->uuid )
        {
            if( prev == NULL )
            {
                CFUUIDs = list->next;
            }
            else
            {
                prev->next = list->next;
            }
            
            free( list );
            
            break;
        }
        
        prev = list;
        list = list->next;
    }
    
    CFSpinLockUnlock( &CFUUIDsLock );
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

CFUUIDRef CFUUIDGetOrCreate( CFAllocatorRef alloc, CFUUIDBytes bytes, bool returnRetainedIfExist )
{
    struct CFUUIDList * item;
    struct CFUUIDList * list;
    struct CFUUID     * o;
    
    o = ( struct CFUUID * )CFRuntimeCreateInstance( alloc, CFUUIDTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    o->_bytes = bytes;
    item      = calloc( sizeof( struct CFUUIDList ), 1 );
    
    if( item == NULL )
    {
        CFRelease( o );
        
        return NULL;
    }
    
    item->uuid = o;
    
    CFSpinLockLock( &CFUUIDsLock );
    
    if( CFUUIDs == NULL )
    {
        CFUUIDs = item;
        
        CFSpinLockUnlock( &CFUUIDsLock );
        
        return o;
    }
    
    list = CFUUIDs;
    
    while( list )
    {
        if( CFEqual( o, list->uuid ) )
        {
            CFRelease( o );
            free( item );
            CFSpinLockUnlock( &CFUUIDsLock );
            
            CFShow( list->uuid );
            
            return ( returnRetainedIfExist ) ? CFRetain( list->uuid ) : list->uuid;
        }
        
        list = list->next;
    }
    
    item->next = CFUUIDs;
    CFUUIDs    = item;
    
    CFSpinLockUnlock( &CFUUIDsLock );
    
    return o;
}
