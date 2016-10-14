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
 * @typedef     CFComparisonResult
 * @abstract    Constants returned by comparison functions, indicating whether
 *              a value is equal to, less than, or greater than another value.
 * @constant    kCFCompareLessThan      Returned by a comparison function if the
 *                                      first value is less than the second
 *                                      value.
 * @constant    kCFCompareEqualTo       Returned by a comparison function if the
 *                                      first value is equal to the second
 *                                      value.
 * @constant    kCFCompareGreaterThan   Returned by a comparison function if the
 *                                      first value is greater than the second
 *                                      value.
 */
typedef enum
{
    kCFCompareLessThan      = -1L,
    kCFCompareEqualTo       = 0,
    kCFCompareGreaterThan   = 1
}
CFComparisonResult;

/*!
 * @constant    kCFNotFound
 * @abstract    A constant that indicates that a search operation did not
 *              succeed in locating the target value.
 */
CF_EXPORT const CFIndex kCFNotFound;

/*!
 * @typedef     CFComparisonResult
 * @abstract    Callback function that compares two values. You provide a
 *              pointer to this callback in certain Core Foundation sorting
 *              functions.
 * @param       val1        The first value to compare.
 * @param       val2        The second value to compare.
 * @param       context     An untyped pointer to the context of the evaluation.
 *                          The meaning of this value and its use are defined by
 *                          each comparator function. This value is usually
 *                          passed to a sort function, such as
 *                          CFArraySortValues, which then passes it, unchanged,
 *                          to the comparator function.
 * @result      A CFComparisonResult value that indicates whether the val1 is
 *              equal to, less than, or greater than val2. See
 *              CFComparisonResult for a list of possible values.
 * @discussion  If you need to sort the elements in a collection using special
 *              criteria, you can implement a comparator function with the
 *              signature defined by this prototype. You pass a pointer to this
 *              function in one of the “sort” functions, such as CFArray's
 *              CFArraySortValues.
 *              You can also pass pointers to standard Core Foundation
 *              comparator functions such as CFStringCompare and CFDateCompare.
 */
typedef CFComparisonResult ( * CFComparatorFunction )( const void * val1, const void * val2, void * context );

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

/*!
 * @function    CFRangeMake
 * @abstract    Declares and initializes a CFRange structure.
 * @param       location    The starting location of the range.
 * @param       length      The length of the range.
 * @result      An initialized structure of type CFRange.
 */
CF_EXPORT CFRange CFRangeMake( CFIndex location, CFIndex length );

/*!
 * @constant    kCFCoreFoundationVersionNumber
 * @discussion  The current version of the Core Foundation framework. Compare
 *              this value to the values in Framework Version Numbers. Although
 *              this variable was added to the CFBase.h header file in OS X
 *              v10.1, it was available and can be used in OS X v10.0.
 */
CF_EXPORT double kCFCoreFoundationVersionNumber;



CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_BASE_H */
