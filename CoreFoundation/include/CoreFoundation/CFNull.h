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
 * @header      CFNull.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  The CFNull opaque type defines a unique object used to represent
 *              null values in collection objects (which don't allow NULL
 *              values). CFNull objects are neither created nor destroyed.
 *              Instead, a single CFNull constant object—kCFNull—is defined and
 *              is used wherever a null value is needed.
 */

#ifndef CORE_FOUNDATION_CF_NULL_H
#define CORE_FOUNDATION_CF_NULL_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFNullRef
 * @abstract    A reference to a CFNull object.
 */
typedef const struct CFNull * CFNullRef;

/*!
 * @constant    kCFNull
 * @abstract    The singleton CFNull object.
 */
CF_EXPORT const CFNullRef kCFNull;

/*!
 * @function    CFNullGetTypeID
 * @abstract    Returns the type identifier for the CFNull opaque type.
 * @result      The type identifier for the CFNull opaque type.
 */
CF_EXPORT CFTypeID CFNullGetTypeID( void );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_NULL_H */
