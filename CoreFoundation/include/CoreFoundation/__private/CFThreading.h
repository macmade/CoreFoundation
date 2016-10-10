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
 * @header      CFThreading.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION_CF___PRIVATE_THREADING_H
#define CORE_FOUNDATION_CF___PRIVATE_THREADING_H

#include <CoreFoundation/CFBase.h>
#include <stdbool.h>

CF_EXTERN_C_BEGIN

#ifdef _WIN32

#include <Windows.h>

typedef DWORD CFThreadingKey;

#else

#include <pthread.h>

typedef pthread_key_t CFThreadingKey;

#endif

CF_EXPORT bool   CFThreadingKeyCreate( CFThreadingKey * key );
CF_EXPORT void * CFThreadingGetSpecific( CFThreadingKey key );
CF_EXPORT bool   CFThreadingSetSpecific( CFThreadingKey key, const void * value );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF___PRIVATE_THREADING_H */
