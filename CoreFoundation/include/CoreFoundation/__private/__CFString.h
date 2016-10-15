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
 * @header      CFString.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_STRING_H
#define CORE_FOUNDATION___PRIVATE_CF_STRING_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/__CFRuntime.h>
#include <CoreFoundation/__private/__CFSpinLock.h>

CF_EXTERN_C_BEGIN

struct CFString
{
    CFRuntimeBase    _base;
    char           * _cStr;
    CFIndex          _length;
    CFIndex          _capacity;
    CFStringEncoding _encoding;
    CFAllocatorRef   _allocator;
    bool             _mutable;
};

CF_EXPORT void        CFStringDestruct( CFStringRef str );
CF_EXPORT CFHashCode  CFStringHash( CFStringRef str );
CF_EXPORT bool        CFStringEquals( CFStringRef s1, CFStringRef s2 );
CF_EXPORT CFStringRef CFStringCopyDescription( CFStringRef str );

CF_EXPORT void CFStringAssertMutable( CFStringRef str );

CF_EXPORT void CFStringInitialize( void );

CF_EXPORT CFTypeID       CFStringTypeID;
CF_EXPORT CFRuntimeClass CFStringClass;

#define CF_STRING_DEFAULT_CAPACITY  ( 1024 )

CF_EXPORT CFSpinLock    CFStringConstantStringsLock;
CF_EXPORT CFIndex       CFStringConstantStringsCapacity;
CF_EXPORT CFStringRef * CFStringConstantStrings;

#define CF_STRING_CONST_DECL( _name_, _cp_ )    \
    const struct CFString _name_ ## _S =        \
    {                                           \
        {                                       \
            ( uintptr_t )&CFStringClass,        \
            -1,                                 \
            NULL                                \
        },                                      \
        _cp_,                                   \
        sizeof( _cp_ ) - 1,                     \
        sizeof( _cp_ ),                         \
        kCFStringEncodingASCII,                 \
        NULL,                                   \
        false                                   \
    };                                          \
    const CFStringRef _name_ = &_name_ ## _S

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_STRING_H */
