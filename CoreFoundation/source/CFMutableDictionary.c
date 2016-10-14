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
 * @file        CFMutableDictionary.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFDictionary.h>
#include <stdlib.h>

CFMutableDictionaryRef CFDictionaryCreateMutable( CFAllocatorRef allocator, CFIndex capacity, const CFDictionaryKeyCallBacks * keyCallBacks, const CFDictionaryValueCallBacks * valueCallBacks )
{
    struct CFDictionary * o;
    
    o = ( struct CFDictionary * )CFRuntimeCreateInstance( allocator, CFDictionaryTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    capacity  = ( capacity > 0 ) ? capacity : CF_DICTIONARY_DEFAULT_CAPACITY;
    o->_items = CFAllocatorAllocate( allocator, capacity * ( CFIndex )sizeof( struct CFDictionaryItem * ), 0 );
    
    if( o->_items == NULL )
    {
        CFRelease( o );
        
        return NULL;
    }
    
    o->_mutable = true;
    o->_size    = capacity;
    
    if( keyCallBacks )
    {
        o->_keyCallbacks = *( keyCallBacks );
    }
    
    if( valueCallBacks )
    {
        o->_valueCallbacks = *( valueCallBacks );
    }
    
    return o;
}

CFMutableDictionaryRef CFDictionaryCreateMutableCopy( CFAllocatorRef allocator, CFIndex capacity, CFDictionaryRef theDict )
{
    CFMutableDictionaryRef    o;
    CFIndex                   i;
    struct CFDictionaryItem * item;
    
    if( theDict == NULL )
    {
        return NULL;
    }
    
    capacity = ( capacity < theDict->_size ) ? theDict->_size : capacity;
    
    o = CFDictionaryCreateMutable( allocator, capacity, &( theDict->_keyCallbacks ), &( theDict->_valueCallbacks ) );
    
    for( i = 0; i < theDict->_size; i++ )
    {
        item = theDict->_items[ i ];
        
        while( item )
        {
            CFDictionaryInsert( o, item->key, item->value, false );
            
            item = item->next;
        }
    }
    
    return o;
}

void CFDictionaryAddValue( CFMutableDictionaryRef theDict, const void * key, const void * value )
{
    struct CFDictionaryItem * item;
    
    if( theDict == NULL )
    {
        return;
    }
    
    CFDictionaryAssertMutable( theDict );
    
    item = CFDictionaryGetItem( theDict, key );
    
    if( item == NULL )
    {
        CFDictionaryInsert( theDict, key, value, true );
    }
}

void CFDictionaryRemoveAllValues( CFMutableDictionaryRef theDict )
{
    CFIndex                   i;
    struct CFDictionaryItem * item;
    struct CFDictionaryItem * del;
    CFAllocatorRef            alloc;
    
    if( theDict == NULL || theDict->_items == NULL )
    {
        return;
    }
    
    CFDictionaryAssertMutable( theDict );
    
    alloc = CFGetAllocator( theDict );
    
    for( i = 0; i < theDict->_size; i++ )
    {
        item                 = theDict->_items[ i ];
        theDict->_items[ i ] = NULL;
        
        while( item )
        {
            del  = item;
            item = item->next;
            
            if( theDict->_keyCallbacks.release )
            {
                theDict->_keyCallbacks.release( alloc, del->key );
            }
            
            if( theDict->_valueCallbacks.release )
            {
                theDict->_valueCallbacks.release( alloc, del->value );
            }
            
            CFAllocatorDeallocate( alloc, del );
            
            theDict->_count--;
        }
    }
}

void CFDictionaryRemoveValue( CFMutableDictionaryRef theDict, const void * key )
{
    CFHashCode                h;
    struct CFDictionaryItem * item;
    struct CFDictionaryItem * prev;
    CFAllocatorRef            alloc;
    
    if( theDict == NULL || theDict->_items == NULL )
    {
        return;
    }
    
    CFDictionaryAssertMutable( theDict );
    
    if( theDict->_keyCallbacks.hash )
    {
        h = theDict->_keyCallbacks.hash( key );
    }
    else
    {
        h = ( uint64_t )key;
    }
    
    h     = h % ( CFHashCode )( theDict->_size );
    item  = theDict->_items[ h ];
    alloc = CFGetAllocator( theDict );
    prev  = NULL;
    
    while( item )
    {
        if( theDict->_keyCallbacks.equal == NULL && key != item->key )
        {
            prev = item;
            item = item->next;
            
            continue;
        }
        else if( key != item->key && theDict->_keyCallbacks.equal( key, item->key ) == false )
        {
            prev = item;
            item = item->next;
            
            continue;
        }
        
        if( prev == NULL )
        {
            theDict->_items[ h ] = item->next;
        }
        else
        {
            prev->next = item->next;
        }
        
        if( theDict->_keyCallbacks.release )
        {
            theDict->_keyCallbacks.release( alloc, item->key );
        }
        
        if( theDict->_valueCallbacks.release )
        {
            theDict->_valueCallbacks.release( alloc, item->value );
        }
        
        CFAllocatorDeallocate( alloc, item );
        
        theDict->_count--;
        
        break;
    }
}

void CFDictionaryReplaceValue( CFMutableDictionaryRef theDict, const void * key, const void * value )
{
    struct CFDictionaryItem * item;
    CFAllocatorRef            alloc;
    
    if( theDict == NULL )
    {
        return;
    }
    
    CFDictionaryAssertMutable( theDict );
    
    item = CFDictionaryGetItem( theDict, key );
    
    if( item == NULL )
    {
        return;
    }
    
    alloc = CFGetAllocator( theDict );
    
    if( theDict->_valueCallbacks.release )
    {
        theDict->_valueCallbacks.release( alloc, item->value );
    }
    
    if( theDict->_valueCallbacks.retain )
    {
        item->value = theDict->_valueCallbacks.retain( alloc, value );
    }
    else
    {
        item->value = value;
    }
}

void CFDictionarySetValue( CFMutableDictionaryRef theDict, const void * key, const void * value )
{
    struct CFDictionaryItem * item;
    CFAllocatorRef            alloc;
    
    if( theDict == NULL )
    {
        return;
    }
    
    CFDictionaryAssertMutable( theDict );
    
    item = CFDictionaryGetItem( theDict, key );
    
    if( item == NULL )
    {
        CFDictionaryInsert( theDict, key, value, true );
        
        return;
    }
    
    alloc = CFGetAllocator( theDict );
    
    if( theDict->_valueCallbacks.release )
    {
        theDict->_valueCallbacks.release( alloc, item->value );
    }
    
    if( theDict->_valueCallbacks.retain )
    {
        item->value = theDict->_valueCallbacks.retain( alloc, value );
    }
    else
    {
        item->value = value;
    }
}
