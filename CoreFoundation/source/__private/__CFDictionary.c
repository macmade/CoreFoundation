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
 * @file        CFDictionary.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/__CFDictionary.h>

CFTypeID       CFDictionaryTypeID = 0;
CFRuntimeClass CFDictionaryClass  =
{
    "CFDictionary",
    sizeof( struct CFDictionary ),
    NULL,
    ( void ( * )( CFTypeRef ) )CFDictionaryDestruct,
    NULL,
    ( bool ( * )( CFTypeRef, CFTypeRef ) )CFDictionaryEquals,
    ( CFStringRef ( * )( CFTypeRef ) )CFDictionaryCopyDescription
};

void CFDictionaryInitialize( void )
{
    CFDictionaryTypeID = CFRuntimeRegisterClass( &CFDictionaryClass );
}

void CFDictionaryDestruct( CFDictionaryRef d )
{
    CFAllocatorRef            alloc;
    struct CFDictionaryItem * item;
    struct CFDictionaryItem * del;
    CFIndex                   i;
    
    alloc =CFGetAllocator( d );
    
    if( d->_items == NULL )
    {
        return;
    }
    
    for( i = 0; i < d->_size; i++ )
    {
        item = d->_items[ i ];
        
        while( item )
        {
            del  = item;
            item = item->next;
            
            if( d->_keyCallbacks.release )
            {
                d->_keyCallbacks.release( alloc, del->key );
            }
            
            if( d->_valueCallbacks.release )
            {
                d->_valueCallbacks.release( alloc, del->value );
            }
            
            CFAllocatorDeallocate( alloc, del );
        }
    }
    
    CFAllocatorDeallocate( alloc, d->_items );
}

#include <stdio.h>

bool CFDictionaryEquals( CFDictionaryRef d1, CFDictionaryRef d2 )
{
    CFIndex                   i;
    CFIndex                   j;
    struct CFDictionaryItem * item1;
    struct CFDictionaryItem * item2;
    bool                      found;
    
    if( d1->_items == NULL || d2->_items == NULL )
    {
        return false;
    }
    
    if( d1->_count != d2->_count )
    {
        return false;
    }
    
    for( i = 0; i < d1->_size; i++ )
    {
        item1 = d1->_items[ i ];
        
        while( item1 )
        {
            found = false;
            
            for( j = 0; j < d2->_size; j++ )
            {
                item2 = d2->_items[ j ];
                
                while( item2 )
                {
                    if( d1->_keyCallbacks.equal == NULL && item1->key != item2->key )
                    {
                        item2 = item2->next;
                        
                        continue;
                    }
                    else if( item1->key != item2->key && d1->_keyCallbacks.equal( item1->key, item2->key ) == false )
                    {
                        item2 = item2->next;
                        
                        continue;
                    }
                    
                    if( d1->_valueCallbacks.equal == NULL && item1->value != item2->value )
                    {
                        item2 = item2->next;
                        
                        continue;
                    }
                    else if( item1->value != item2->value && d1->_valueCallbacks.equal( item1->value, item2->value ) == false )
                    {
                        item2 = item2->next;
                        
                        continue;
                    }
                    
                    found = true;
                    
                    break;
                }
                
                if( found )
                {
                    break;
                }
            }
            
            if( found == false )
            {
                return false;
            }
            
            item1 = item1->next;
        }
    }
    
    return true;
}

CFStringRef CFDictionaryCopyDescription( CFDictionaryRef d )
{
    CFMutableStringRef        s;
    CFIndex                   i;
    struct CFDictionaryItem * item;
    CFStringRef               k;
    CFStringRef               v;
    
    s = CFStringCreateMutable( NULL, 0 );
    
    if( s == NULL )
    {
        return NULL;
    }
    
    CFStringAppendFormat
    (
        s,
        NULL,
        CFSTR( "{ count = %lu, capacity = %lu, type = %s }" ),
        d->_count,
        d->_size,
        ( d->_mutable ) ? "mutable" : "immutable"
    );
    
    if( d->_count == 0 )
    {
        return s;
    }
    
    CFStringAppendCString( s, "\n{\n", kCFStringEncodingASCII );
    
    for( i = 0; i < d->_size; i++ )
    {
        item = d->_items[ i ];
        
        while( item )
        {
            k = NULL;
            v = NULL;
            
            if( d->_keyCallbacks.copyDescription )
            {
                k = d->_keyCallbacks.copyDescription( item->key );
            }
            
            if( d->_valueCallbacks.copyDescription )
            {
                v = d->_valueCallbacks.copyDescription( item->value );
            }
            
            if( k == NULL )
            {
                k = CFStringCreateWithFormat( NULL, NULL, CFSTR( "0x%lu" ), item->key );
            }
            
            if( v == NULL )
            {
                v = CFStringCreateWithFormat( NULL, NULL, CFSTR( "0x%lu" ), item->value );
            }
            
            if( k && v )
            {
                CFStringAppendCString( s, "    ", kCFStringEncodingASCII );
                CFStringAppend( s, k );
                CFStringAppendCString( s, " = ", kCFStringEncodingASCII );
                CFStringAppend( s, v );
                CFStringAppendCString( s, "\n", kCFStringEncodingASCII );
            }
            
            if( k )
            {
                CFRelease( k );
            }
            
            if( v )
            {
                CFRelease( v );
            }
            
            item = item->next;
        }
    }
    
    CFStringAppendCString( s, "}", kCFStringEncodingASCII );
    
    return s;
}

const void * CFDictionaryCallbackRetain( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    return CFRetain( value );
}

void CFDictionaryCallbackRelease( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    CFRelease( value );
}

struct CFDictionaryItem * CFDictionaryGetItem( CFDictionaryRef d, const void * key )
{
    CFHashCode                h;
    struct CFDictionaryItem * item;
    
    if( d == NULL || d->_items == NULL )
    {
        return false;
    }
    
    if( d->_keyCallbacks.hash )
    {
        h = d->_keyCallbacks.hash( key );
    }
    else
    {
        h = ( uint64_t )key;
    }
    
    h    = h % ( CFHashCode )( d->_size );
    item = d->_items[ h ];
    
    while( item )
    {
        if( key == item->key )
        {
            return item;
        }
        
        if( d->_keyCallbacks.equal && d->_keyCallbacks.equal( key, item->key ) )
        {
            return item;
        }
        
        item = item->next;
    }
    
    return NULL;
}

bool CFDictionaryInsert( struct CFDictionary * d, const void * key, const void * value, bool expandIfNeeded )
{
    struct CFDictionaryItem * item;
    CFHashCode                h;
    CFAllocatorRef            alloc;
    
    if( d == NULL || d->_items == NULL )
    {
        return false;
    }
    
    alloc = CFGetAllocator( d );
    item  = CFDictionaryGetItem( d, key );
    
    if( item )
    {
        if( d->_valueCallbacks.release )
        {
            d->_valueCallbacks.release( alloc, item->value );
        }
        
        if( d->_valueCallbacks.retain )
        {
            item->value = d->_valueCallbacks.retain( alloc, value );
        }
        else
        {
            item->value = value;
        }
        
        return true;
    }
    
    item = CFAllocatorAllocate( alloc, sizeof( struct CFDictionaryItem ), 0 );
    
    if( item == NULL )
    {
        return false;
    }
    
    if( d->_keyCallbacks.retain )
    {
        item->key = d->_keyCallbacks.retain( alloc, key );
    }
    else
    {
        item->key = key;
    }
    
    if( d->_valueCallbacks.retain )
    {
        item->value = d->_valueCallbacks.retain( alloc, value );
    }
    else
    {
        item->value = value;
    }
    
    if( d->_keyCallbacks.hash )
    {
        h = d->_keyCallbacks.hash( key );
    }
    else
    {
        h = ( uint64_t )key;
    }
    
    h = h % ( CFHashCode )( d->_size );
    
    item->next     = d->_items[ h ];
    d->_items[ h ] = item;
    
    d->_count++;
    
    if( expandIfNeeded && d->_count >= d->_size * CF_DICTIONARY_MAX_LOAD_FACTOR )
    {
        CFDictionaryResize( d, d->_size * CF_DICTIONARY_GROWTH_FACTOR );
    }
    
    return true;
}

void CFDictionaryResize( CFDictionaryRef d, CFIndex size )
{
    CFAllocatorRef             alloc;
    struct CFDictionary      * d2;
    CFDictionaryKeyCallBacks   kCallbacks;
    CFDictionaryValueCallBacks vCallbacks;
    CFIndex                    i;
    struct CFDictionaryItem  * item;
    
    if( d == NULL )
    {
        return;
    }
    
    alloc = CFGetAllocator( d );
    d2    = ( struct CFDictionary * )CFRuntimeCreateInstance( alloc, CFDictionaryTypeID );
    
    if( d2 == NULL )
    {
        return;
    }
    
    d2->_items = CFAllocatorAllocate( alloc, ( size ) ? size * ( CFIndex )sizeof( struct CFDictionaryItem * ) : sizeof( struct CFDictionaryItem * ), 0 );
    
    if( d2->_items == NULL )
    {
        CFRelease( d2 );
        
        return;
    }
    
    d2->_size                  = size;
    d2->_keyCallbacks          = d->_keyCallbacks;
    d2->_valueCallbacks        = d->_valueCallbacks;
    kCallbacks                 = d2->_keyCallbacks;
    vCallbacks                 = d2->_valueCallbacks;
    d2->_keyCallbacks.retain   = NULL;
    d2->_valueCallbacks.retain = NULL;
    
    for( i = 0; i < d->_size; i++ )
    {
        item = d->_items[ i ];
        
        while( item )
        {
            CFDictionaryInsert( d2, item->key, item->value, false );
            
            item = item->next;
        }
    }
    
    d2->_keyCallbacks   = kCallbacks;
    d2->_valueCallbacks = vCallbacks;
    
    ( ( struct CFDictionary * )d )->_keyCallbacks.release   = NULL;
    ( ( struct CFDictionary * )d )->_valueCallbacks.release = NULL;
    
    CFDictionarySwap( d, d2 );
    CFRelease( d2 );
}

void CFDictionarySwap( CFDictionaryRef d1, CFDictionaryRef d2 )
{
    struct CFDictionary   tmp;
    struct CFDictionary * p1;
    struct CFDictionary * p2;
    
    if( d1 == NULL || d2 == NULL )
    {
        return;
    }
    
    p1 = ( struct CFDictionary * )d1;
    p2 = ( struct CFDictionary * )d2;
    
    tmp     = *( p1 );
    *( p1 ) = *( p2 );
    *( p2 ) = tmp;
}

void CFDictionaryAssertMutable( CFDictionaryRef d )
{
    if( d == NULL )
    {
        return;
    }
    
    if( d->_mutable == false )
    {
        CFRuntimeAbortWithError( "<CFDictionary 0x%lu> is not mutable", ( unsigned long )d );
    }
}

const CFDictionaryKeyCallBacks kCFCopyStringDictionaryKeyCallBacks =
{
    0,
    ( const void * ( * )( CFAllocatorRef, const void * ) )CFStringCreateCopy,
    CFDictionaryCallbackRelease,
    CFCopyDescription,
    CFEqual,
    CFHash
};

const CFDictionaryKeyCallBacks kCFTypeDictionaryKeyCallBacks =
{
    0,
    CFDictionaryCallbackRetain,
    CFDictionaryCallbackRelease,
    CFCopyDescription,
    CFEqual,
    CFHash
};

const CFDictionaryValueCallBacks kCFTypeDictionaryValueCallBacks =
{
    0,
    CFDictionaryCallbackRetain,
    CFDictionaryCallbackRelease,
    CFCopyDescription,
    CFEqual
};
