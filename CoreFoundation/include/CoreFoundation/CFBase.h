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
 * @header      CFBase.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION_CF_BASE_H
#define CORE_FOUNDATION_CF_BASE_H

/*!
 * @define      CF_EXTERN_C_BEGIN
 * @abstract    Extern "C" start / C++ compatibility
 */
#ifdef __cplusplus
#define CF_EXTERN_C_BEGIN   extern "C" {
#else
#define CF_EXTERN_C_BEGIN
#endif

/*!
 * @define      CF_EXTERN_C_END
 * @abstract    Extern "C" end / C++ compatibility
 */
#ifdef __cplusplus
#define CF_EXTERN_C_END     }
#else
#define CF_EXTERN_C_END
#endif

CF_EXTERN_C_BEGIN

#if defined( TARGET_OS_WIN32 ) && TARGET_OS_WIN32

/*!
 * @define      CF_EXPORT
 * @abstract    Definition for exported symbols
 */
#if defined( CF_BUILDING_CF ) && defined( __cplusplus )
#define CF_EXPORT   extern "C" __declspec( dllexport )
#elif defined(CF_BUILDING_CF) && !defined( __cplusplus )
#define CF_EXPORT   extern __declspec( dllexport )
#elif defined( __cplusplus )
#define CF_EXPORT   extern "C" __declspec( dllimport )
#else
#define CF_EXPORT   extern __declspec( dllimport )
#endif

#else

/*!
 * @define      CF_EXPORT
 * @abstract    Definition for exported symbols
 */
#define CF_EXPORT   extern

#endif

/*!
 * @typedef     CFTypeID
 * @abstract    A type for unique, constant integer values that identify
 *              particular Core Foundation opaque types.
 * @discussion  Defines a type identifier in Core Foundation. A type ID is an
 *              integer that identifies the opaque type to which a Core
 *              Foundation object “belongs.” You use type IDs in various
 *              contexts, such as when you are operating on heterogeneous
 *              collections. Core Foundation provides programmatic interfaces
 *              for obtaining and evaluating type IDs.
 *              Because the value for a type ID can change from release to
 *              release, your code should not rely on stored or hard-coded type
 *              IDs nor should it hard-code any observed properties of a type ID
 *              (such as, for example, it being a small integer).
 */
#ifdef __LLP64__
typedef unsigned long long CFTypeID;
#else
typedef unsigned long CFTypeID;
#endif

/*!
 * @typedef     CFIndex
 * @abstract    An integer type used throughout Core Foundation in several
 *              programmatic roles: as an array index and for count, size, and
 *              length parameters and return values.
 * @discussion  Core Foundation types as CFIndex all parameters and return
 *              values that might grow over time as the processor's address size
 *              changes. On architectures where pointer sizes are a different
 *              size (say, 64 bits) CFIndex might be declared to be also
 *              64 bits, independent of the size of int.
 *              If you type your own variables that interact with Core
 *              Foundation as CFIndex, your code will have a higher degree of
 *              source compatibility in the future.
 */
#ifdef __LLP64__
typedef signed long long CFIndex;
#else
typedef signed long CFIndex;
#endif

/*!
 * @typedef     CFOptionFlags
 * @abstract    A bitfield used for passing special allocation and other
 *              requests into Core Foundation functions.
 * @discussion  The flag bits are specific to particular opaque types and
 *              functions in Core Foundation.
 */
#ifdef __LLP64__
typedef unsigned long long CFOptionFlags;
#else
typedef unsigned long CFOptionFlags;
#endif

/*!
 * @typedef     CFHashCode
 * @abstract    A type for hash codes returned by the CFHash function.
 */
#ifdef __LLP64__
typedef unsigned long long CFHashCode;
#else
typedef unsigned long CFHashCode;
#endif

/*!
 * @typedef     CFRange
 * @abstract    A structure representing a range of sequential items in a
 *              container, such as characters in a buffer or elements in a
 *              collection.
 * @field       location    An integer representing the starting location of the
 *                          range. For type compatibility with the rest of the
 *                          system, LONG_MAX is the maximum value you should use
 *                          for location.
 * @field       length      An integer representing the number of items in the
 *                          range. For type compatibility with the rest of the
 *                          system, LONG_MAX is the maximum value you should use
 *                          for length.
 */
typedef struct
{
    CFIndex location;
    CFIndex length;
}
CFRange;

CF_EXPORT CFRange CFRangeMake( CFIndex location, CFIndex length );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_BASE_H */
