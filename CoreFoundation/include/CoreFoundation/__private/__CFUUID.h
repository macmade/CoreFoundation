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
 * @header      CFUUID.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_UUID_H
#define CORE_FOUNDATION___PRIVATE_CF_UUID_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/__CFRuntime.h>
#include <CoreFoundation/__private/__CFSpinLock.h>

CF_EXTERN_C_BEGIN

struct CFUUID
{
    CFRuntimeBase _base;
    CFUUIDBytes   _bytes;
};

struct CFUUIDList
{
    struct CFUUIDList * next;
    CFUUIDRef           uuid;
};

CF_EXPORT void CFUUIDInitialize( void );

CF_EXPORT CFTypeID       CFUUIDTypeID;
CF_EXPORT CFRuntimeClass CFUUIDClass;

CF_EXPORT CFSpinLock          CFUUIDsLock;
CF_EXPORT struct CFUUIDList * CFUUIDs;
CF_EXPORT CFUUIDBytes         CFUUIDNullBytes;

CF_EXPORT void        CFUUIDDestruct( CFUUIDRef u );
CF_EXPORT CFHashCode  CFUUIDHash( CFUUIDRef u );
CF_EXPORT bool        CFUUIDEquals( CFUUIDRef u1, CFUUIDRef u2 );
CF_EXPORT CFStringRef CFUUIDCopyDescription( CFUUIDRef u );
CF_EXPORT UInt8       CFUUIDByteFromHexChar( char * s );
CF_EXPORT CFUUIDRef   CFUUIDGetOrCreate( CFAllocatorRef alloc, CFUUIDBytes bytes, bool returnRetainedIfExist );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_UUID_H */
