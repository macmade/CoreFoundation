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
#include <CoreFoundation/__private/CFRuntime.h>
#include <string.h>

struct CFDictionaryItem
{
    struct CFDictionaryItem * next;
    const void              * key;
    const void              * value;
};

struct CFDictionary
{
    CFRuntimeBase              _base;
    CFIndex                    _size;
    CFIndex                    _count;
    CFDictionaryKeyCallBacks   _keyCallbacks;
    CFDictionaryValueCallBacks _valueCallbacks;
    struct CFDictionaryItem ** _items;
    bool                       _mutable;
};

static void CFAllocatorDestruct( CFDictionaryRef d );
static CFStringRef CFDictionaryCopyDescription( CFDictionaryRef str );

static CFTypeID CFDictionaryTypeID      = 0;
static CFRuntimeClass CFDictionaryClass =
{
    "CFDictionary",
    sizeof( struct CFDictionary ),
    NULL,
    ( void ( * )( CFTypeRef ) )CFAllocatorDestruct,
    NULL,
    NULL,
    ( CFStringRef ( * )( CFTypeRef ) )CFDictionaryCopyDescription
};

static const void              * CFDictionaryCallbackRetain( CFAllocatorRef allocator, const void * value );
static       void                CFDictionaryCallbackRelease( CFAllocatorRef allocator, const void * value );
static struct CFDictionaryItem * CFDictionaryGetItem( CFDictionaryRef d, const void * key );
static bool                      CFDictionaryInsert( struct CFDictionary * d, const void * key, const void * value, bool expandIfNeeded );
static void                      CFDictionaryResize( CFDictionaryRef d, CFIndex size );
static void                      CFDictionarySwap( CFDictionaryRef d1, CFDictionaryRef d2 );

#define CF_DICTIONARY_MAX_LOAD_FACTOR   ( 1 )
#define CF_DICTIONARY_GROWTH_FACTOR     ( 2 )

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFDictionaryTypeID = CFRuntimeRegisterClass( &CFDictionaryClass );
}

static void CFAllocatorDestruct( CFDictionaryRef d )
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

static CFStringRef CFDictionaryCopyDescription( CFDictionaryRef d )
{
    return CFStringCreateWithFormat
    (
        NULL,
        NULL,
        CFStringCreateWithCStringNoCopy( NULL, "{ count = %lu, capacity = %lu, type = %s }", kCFStringEncodingUTF8, kCFAllocatorNull ),
        d->_count,
        d->_size,
        ( d->_mutable ) ? "mutable" : "immutable"
    );
}

static const void * CFDictionaryCallbackRetain( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    return CFRetain( value );
}

static void CFDictionaryCallbackRelease( CFAllocatorRef allocator, const void * value )
{
    ( void )allocator;
    
    CFRelease( value );
}

static struct CFDictionaryItem * CFDictionaryGetItem( CFDictionaryRef d, const void * key )
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

static bool CFDictionaryInsert( struct CFDictionary * d, const void * key, const void * value, bool expandIfNeeded )
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

static void CFDictionaryResize( CFDictionaryRef d, CFIndex size )
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

static void CFDictionarySwap( CFDictionaryRef d1, CFDictionaryRef d2 )
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

CFTypeID CFDictionaryGetTypeID( void )
{
    return CFDictionaryTypeID;
}

CFDictionaryRef CFDictionaryCreate( CFAllocatorRef allocator, const void ** keys, const void ** values, CFIndex numValues, const CFDictionaryKeyCallBacks * keyCallBacks, const CFDictionaryValueCallBacks * valueCallBacks )
{
    struct CFDictionary * o;
    CFIndex               i;
    
    o = ( struct CFDictionary * )CFRuntimeCreateInstance( allocator, CFDictionaryTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    o->_items = CFAllocatorAllocate( allocator, ( numValues ) ? numValues * ( CFIndex )sizeof( struct CFDictionaryItem * ) : sizeof( struct CFDictionaryItem * ), 0 );
    
    if( o->_items == NULL )
    {
        CFRelease( o );
        
        return NULL;
    }
    
    o->_size = numValues;
    
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
    
    o->_size            = theDict->_size;
    o->_count           = theDict->_count;
    o->_keyCallbacks    = theDict->_keyCallbacks;
    o->_valueCallbacks  = theDict->_valueCallbacks;
    o->_items           = CFAllocatorAllocate( allocator, o->_size * ( CFIndex )sizeof( struct CFDictionaryItem * ), 0 );
    
    memcpy( o->_items, theDict->_items, ( size_t )( o->_size ) );
    
    if( o->_keyCallbacks.retain || o->_valueCallbacks.retain )
    {
        for( i = 0; i < o->_size; i++ )
        {
            item = o->_items[ i ];
            
            while( item )
            {
                if( o->_keyCallbacks.retain )
                {
                    item->key = o->_keyCallbacks.retain( allocator, item->key );
                }
                
                if( o->_valueCallbacks.retain )
                {
                    item->value = o->_keyCallbacks.retain( allocator, item->value );
                }
                
                item = item->next;
            }
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
