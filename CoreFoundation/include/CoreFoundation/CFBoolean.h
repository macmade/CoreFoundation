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
 * @header      CFBoolean.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  CFBoolean objects are used to wrap boolean values for use in
 *              Core Foundation property lists and collection types.
 */

#ifndef CORE_FOUNDATION_CF_BOOLEAN_H
#define CORE_FOUNDATION_CF_BOOLEAN_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/MacTypes.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFBooleanRef
 * @abstract    A reference to a CFBoolean object.
 * @discussion  CFBoolean objects are used to wrap boolean values for use in
 *              Core Foundation property lists and collection types.
 */
typedef const struct CFBoolean * CFBooleanRef;

/*!
 * @constant    kCFBooleanTrue
 * @abstract    Boolean true value.
 */
CF_EXPORT const CFBooleanRef kCFBooleanTrue;

/*!
 * @constant    kCFBooleanFalse
 * @abstract    Boolean false value.
 */
CF_EXPORT const CFBooleanRef kCFBooleanFalse;

/*!
 * @function    CFBooleanGetTypeID
 * @abstract    Returns the Core Foundation type identifier for the CFBoolean
 *              opaque type.
 * @result      The Core Foundation type identifier for CFBoolean opaque type.
 */
CF_EXPORT CFTypeID CFBooleanGetTypeID( void );

/*!
 * @function    CFBooleanGetValue
 * @abstract    Returns the value of a CFBoolean object as a standard C type
 *              Boolean.
 * @param       boolean     The boolean to examine.
 * @result      The value of boolean.
 */
CF_EXPORT Boolean CFBooleanGetValue( CFBooleanRef boolean );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_BOOLEAN_H */
