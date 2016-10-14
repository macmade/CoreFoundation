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
 * @header      CFAtomic.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_ATOMIC_H
#define CORE_FOUNDATION___PRIVATE_CF_ATOMIC_H

#include <CoreFoundation/CFBase.h>
#include <stdint.h>
#include <stdbool.h>

CF_EXTERN_C_BEGIN

CFIndex CFAtomicIncrement( volatile CFIndex * value );
int32_t CFAtomicIncrement32( volatile int32_t * value );
int64_t CFAtomicIncrement64( volatile int64_t * value );

CFIndex CFAtomicDecrement( volatile CFIndex * value );
int32_t CFAtomicDecrement32( volatile int32_t * value );
int64_t CFAtomicDecrement64( volatile int64_t * value );

bool CFAtomicCompareAndSwap( CFIndex oldValue, CFIndex newValue, volatile CFIndex * value );
bool CFAtomicCompareAndSwap32( int32_t oldValue, int32_t newValue, volatile int32_t * value );
bool CFAtomicCompareAndSwap64( int64_t oldValue, int64_t newValue, volatile int64_t * value );
bool CFAtomicCompareAndSwapPointer( void * oldValue, void * newValue, void * volatile * value );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_ATOMIC_H */
