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
 * @header      CFDictionary.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_DICTIONARY_H
#define CORE_FOUNDATION___PRIVATE_CF_DICTIONARY_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>

CF_EXTERN_C_BEGIN

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

CF_EXPORT void        CFDictionaryDestruct( CFDictionaryRef d );
CF_EXPORT bool        CFDictionaryEquals( CFDictionaryRef d1, CFDictionaryRef d2 );
CF_EXPORT CFStringRef CFDictionaryCopyDescription( CFDictionaryRef d );

CF_EXPORT void CFDictionaryInitialize( void );

CF_EXPORT CFTypeID       CFDictionaryTypeID;
CF_EXPORT CFRuntimeClass CFDictionaryClass;

CF_EXPORT const void              * CFDictionaryCallbackRetain( CFAllocatorRef allocator, const void * value );
CF_EXPORT       void                CFDictionaryCallbackRelease( CFAllocatorRef allocator, const void * value );
CF_EXPORT struct CFDictionaryItem * CFDictionaryGetItem( CFDictionaryRef d, const void * key );
CF_EXPORT bool                      CFDictionaryInsert( struct CFDictionary * d, const void * key, const void * value, bool expandIfNeeded );
CF_EXPORT void                      CFDictionaryResize( CFDictionaryRef d, CFIndex size );
CF_EXPORT void                      CFDictionarySwap( CFDictionaryRef d1, CFDictionaryRef d2 );
CF_EXPORT void                      CFDictionaryAssertMutable( CFDictionaryRef d );

#define CF_DICTIONARY_MAX_LOAD_FACTOR   (  1 )
#define CF_DICTIONARY_GROWTH_FACTOR     (  2 )
#define CF_DICTIONARY_DEFAULT_CAPACITY  ( 32 )

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_DICTIONARY_H */
