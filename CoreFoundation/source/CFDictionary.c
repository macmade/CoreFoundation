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

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFDictionary.h>
#include <CoreFoundation/__private/CFRuntime.h>
#include <string.h>

CFTypeID CFDictionaryGetTypeID( void )
{
    return CFDictionaryTypeID;
}

CFDictionaryRef CFDictionaryCreate( CFAllocatorRef allocator, const void ** keys, const void ** values, CFIndex numValues, const CFDictionaryKeyCallBacks * keyCallBacks, const CFDictionaryValueCallBacks * valueCallBacks )
{
    struct CFDictionary * o;
    CFIndex               i;
    CFIndex               capacity;
    
    o = ( struct CFDictionary * )CFRuntimeCreateInstance( allocator, CFDictionaryTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    capacity  = ( numValues > 0 ) ? numValues : 1;
    o->_items = CFAllocatorAllocate( allocator, capacity * ( CFIndex )sizeof( struct CFDictionaryItem * ), 0 );
    
    if( o->_items == NULL )
    {
        CFRelease( o );
        
        return NULL;
    }
    
    o->_size = capacity;
    
    if( keyCallBacks )
    {
        o->_keyCallbacks = *( keyCallBacks );
    }
    
    if( valueCallBacks )
    {
        o->_valueCallbacks = *( valueCallBacks );
    }
    
    for( i = 0; i < numValues; i++ )
    {
        if( CFDictionaryInsert( o, keys[ i ], values[ i ], false ) == false )
        {
            CFRelease( o );
            
            return NULL;
        }
    }
    
    return o;
}

CFDictionaryRef CFDictionaryCreateCopy( CFAllocatorRef allocator, CFDictionaryRef theDict )
{
    struct CFDictionary     * o;
    struct CFDictionaryItem * item;
    CFIndex                   i;
    
    if( theDict == NULL )
    {
        return NULL;
    }
    
    o = ( struct CFDictionary * )CFRuntimeCreateInstance( allocator, CFDictionaryTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    o->_items = CFAllocatorAllocate( allocator, theDict->_size * ( CFIndex )sizeof( struct CFDictionaryItem * ), 0 );
    
    if( o->_items == NULL )
    {
        CFRelease( o );
        
        return NULL;
    }
    
    o->_size            = theDict->_size;
    o->_keyCallbacks    = theDict->_keyCallbacks;
    o->_valueCallbacks  = theDict->_valueCallbacks;
    
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

Boolean CFDictionaryContainsKey( CFDictionaryRef theDict, const void * key )
{
    if( theDict == NULL )
    {
        return false;
    }
    
    return CFDictionaryGetItem( theDict, key ) != NULL;
}

Boolean CFDictionaryContainsValue( CFDictionaryRef theDict, const void * value )
{
    CFIndex                   i;
    struct CFDictionaryItem * item;
    
    if( theDict == NULL || theDict->_items == NULL )
    {
        return false;
    }
    
    for( i = 0; i < theDict->_size; i++ )
    {
        item = theDict->_items[ i ];
        
        while( item )
        {
            if( item->value == value )
            {
                return true;
            }
            else if( theDict->_valueCallbacks.equal && theDict->_valueCallbacks.equal( value, item->value ) )
            {
                return true;
            }
            
            item = item->next;
        }
    }
    
    return false;
}

CFIndex CFDictionaryGetCount( CFDictionaryRef theDict )
{
    if( theDict == NULL )
    {
        return 0;
    }
    
    return theDict->_count;
}

CFIndex CFDictionaryGetCountOfKey( CFDictionaryRef theDict, const void * key )
{
    if( theDict == NULL )
    {
        return 0;
    }
    
    return ( CFDictionaryContainsKey( theDict, key ) ) ? 1 : 0;
}

CFIndex CFDictionaryGetCountOfValue( CFDictionaryRef theDict, const void * value )
{
    CFIndex                   i;
    CFIndex                   c;
    struct CFDictionaryItem * item;
    
    if( theDict == NULL || theDict->_items == NULL )
    {
        return 0;
    }
    
    c = 0;
    
    for( i = 0; i < theDict->_size; i++ )
    {
        item = theDict->_items[ i ];
        
        while( item )
        {
            if( item->value == value )
            {
                c++;
            }
            else if( theDict->_valueCallbacks.equal && theDict->_valueCallbacks.equal( value, item->value ) )
            {
                c++;
            }
            
            item = item->next;
        }
    }
    
    return c;
}

void CFDictionaryGetKeysAndValues( CFDictionaryRef theDict, const void ** keys, const void ** values )
{
    CFIndex                   i;
    CFIndex                   c;
    struct CFDictionaryItem * item;
    
    if( theDict == NULL || theDict->_items == NULL )
    {
        return;
    }
    
    c = 0;
    
    for( i = 0; i < theDict->_size; i++ )
    {
        item = theDict->_items[ i ];
        
        while( item )
        {
            if( keys )
            {
                keys[ c ] = item->key;
            }
            
            if( values )
            {
                values[ c ] = item->value;
            }
            
            item = item->next;
            
            c++;
        }
    }
}

const void * CFDictionaryGetValue( CFDictionaryRef theDict, const void * key )
{
    struct CFDictionaryItem * item;
    
    if( theDict == NULL )
    {
        return NULL;
    }
    
    item = CFDictionaryGetItem( theDict, key );
    
    return ( item ) ? item->value : NULL;
}

Boolean CFDictionaryGetValueIfPresent( CFDictionaryRef theDict, const void * key, const void ** value )
{
    struct CFDictionaryItem * item;
    
    if( theDict == NULL )
    {
        return false;
    }
    
    item = CFDictionaryGetItem( theDict, key );
    
    if( item == NULL )
    {
        return false;
    }
    
    if( value )
    {
        *( value ) = item->value;
    }
    
    return true;
}

void CFDictionaryApplyFunction( CFDictionaryRef theDict, CFDictionaryApplierFunction applier, void * context )
{
    CFIndex                   i;
    struct CFDictionaryItem * item;
    
    if( theDict == NULL || theDict->_items == NULL || applier == NULL )
    {
        return;
    }
    
    for( i = 0; i < theDict->_size; i++ )
    {
        item = theDict->_items[ i ];
        
        while( item )
        {
            applier( item->key, item->value, context );
            
            item = item->next;
        }
    }
}
