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
 * @header      CFNumber.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION_CF_NUMBER_H
#define CORE_FOUNDATION_CF_NUMBER_H

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFNumberRef
 * @abstract    A reference to a CFNumber object.
 * @discussion  CFNumber encapsulates C scalar (numeric) types. It provides
 *              functions for setting and accessing the value as any basic C
 *              type. It also provides a compare function to determine the
 *              ordering of two CFNumber objects. CFNumber objects are used to
 *              wrap numerical values for use in Core Foundation property lists
 *              and collections.
 *              CFNumber objects are not intended as a replacement for C scalar
 *              values and should not be used in APIs or implementations where
 *              scalar values are more appropriate and efficient.
 *              Note: in order to improve performance, some commonly-used
 *              numbers (such as 0 and 1) are uniqued. You should not expect
 *              that allocating multiple CFNumber instances will necessarily
 *              result in distinct objects.
 *              CFNumber is “toll-free bridged” with its Cocoa Foundation
 *              counterpart, NSNumber. This means that the Core Foundation type
 *              is interchangeable in function or method calls with the bridged
 *              Foundation object. Therefore, in a method where you see an
 *              NSNumber * parameter, you can pass in a CFNumberRef, and in a
 *              function where you see a CFNumberRef parameter, you can pass in
 *              an NSNumber instance. This fact also applies to concrete
 *              subclasses of NSNumber. See Toll-Free Bridged Types for more
 *              information on toll-free bridging.
 */
typedef const struct CFNumber * CFNumberRef;

/*!
 * @constant    kCFNumberNaN
 * @abstract    "Not a Number." This value is often the result of an invalid
 *              operation, such as the square-root of a negative number.
 */
CF_EXPORT const CFNumberRef kCFNumberNaN;

/*!
 * @constant    kCFNumberNegativeInfinity
 * @abstract    Designates a negative infinity value.
 */
CF_EXPORT const CFNumberRef kCFNumberNegativeInfinity;

/*!
 * @constant    kCFNumberPositiveInfinity
 * @abstract    Designates a positive infinity value.
 */
CF_EXPORT const CFNumberRef kCFNumberPositiveInfinity;

/*!
 * @typedef     CFNumberType
 * @abstract    Flags used by CFNumber to indicate the data type of a value.
 * @constant    kCFNumberSInt8Type      Eight-bit, signed integer. The SInt8
 *                                      data type is defined in MacTypes.h.
 * @constant    kCFNumberSInt16Type     Sixteen-bit, signed integer. The SInt16
 *                                      data type is defined in MacTypes.h.
 * @constant    kCFNumberSInt32Type     Thirty-two-bit, signed integer. The
 *                                      SInt32 data type is defined in
 *                                      MacTypes.h.
 * @constant    kCFNumberSInt64Type     Sixty-four-bit, signed integer. The
 *                                      SInt64 data type is defined in
 *                                      MacTypes.h.
 * @constant    kCFNumberFloat32Type    Thirty-two-bit real. The Float32 data
 *                                      type is defined in MacTypes.h.
 * @constant    kCFNumberFloat64Type    Sixty-four-bit real. The Float64 data
 *                                      type is defined in MacTypes.h and
 *                                      conforms to the 64-bit IEEE 754
 *                                      standard.
 * @constant    kCFNumberCharType       Basic C char type.
 * @constant    kCFNumberShortType      Basic C short type.
 * @constant    kCFNumberIntType        Basic C int type.
 * @constant    kCFNumberLongType       Basic C long type.
 * @constant    kCFNumberLongLongType   Basic C long long type.
 * @constant    kCFNumberFloatType      Basic C float type.
 * @constant    kCFNumberDoubleType     Basic C double type.
 * @constant    kCFNumberCFIndexType    CFIndex value.
 * @constant    kCFNumberNSIntegerType  NSInteger value.
 * @constant    kCFNumberCGFloatType    CGFloat value.
 * @constant    kCFNumberMaxType        Same as kCFNumberCGFloatType.
 * @discussion  The type specified in the call to CFNumberCreate is not
 *              necessarily preserved when creating a new CFNumber object.
 *              A CFNumber object uses whatever internal storage type the
 *              creation function deems appropriate. Use the CFNumberGetType
 *              function to find out what type the CFNumber object used to store
 *              your value.
 */
typedef enum
{
    kCFNumberSInt8Type      = 1,
    kCFNumberSInt16Type     = 2,
    kCFNumberSInt32Type     = 3,
    kCFNumberSInt64Type     = 4,
    kCFNumberFloat32Type    = 5,
    kCFNumberFloat64Type    = 6,
    kCFNumberCharType       = 7,
    kCFNumberShortType      = 8,
    kCFNumberIntType        = 9,
    kCFNumberLongType       = 10,
    kCFNumberLongLongType   = 11,
    kCFNumberFloatType      = 12,
    kCFNumberDoubleType     = 13,
    kCFNumberCFIndexType    = 14,
    kCFNumberNSIntegerType  = 15,
    kCFNumberCGFloatType    = 16,
    kCFNumberMaxType        = 16
}
CFNumberType;

/*!
 * @function    CFNumberGetTypeID
 * @abstract    Returns the type identifier for the CFNumber opaque type.
 * @result      The type identifier for the CFNumber opaque type.
 */
CF_EXPORT CFTypeID CFNumberGetTypeID( void );

/*!
 * @function    CFNumberCreate
 * @abstract    Creates a CFNumber object using a specified value.
 * @param       allocator   The allocator to use to allocate memory for the new
 *              object. Pass NULL or kCFAllocatorDefault to use the default
 *              allocator.
 * @param       type        A constant that specifies the data type of the
 *                          value to convert. See CFNumberType for a list of
 *                          possible values.
 * @param       valuePtr    A pointer to the value for the returned number
 *                          object.
 * @result      A new number with the value specified by valuePtr. Ownership
 *              follows The Create Rule.
 * @discussion  The type parameter is not necessarily preserved when creating
 *              a new CFNumber object. The CFNumber object will be created using
 *              whatever internal storage type the creation function deems
 *              appropriate. Use the function CFNumberGetType to find out what
 *              type the CFNumber object used to store your value.
 */
CF_EXPORT CFNumberRef CFNumberCreate( CFAllocatorRef allocator, CFNumberType type, const void * valuePtr );

/*!
 * @function    CFNumberGetByteSize
 * @abstract    Returns the number of bytes used by a CFNumber object to store
 *              its value.
 * @param       number  The CFNumber object to examine.
 * @result      The size in bytes of the value contained in number.
 * @discussion  Because a CFNumber object might store a value using a type
 *              different from that of the original value with which it was
 *              created, this function may return a size different from the size
 *              of the original value's type.
 */
CF_EXPORT CFIndex CFNumberGetByteSize( CFNumberRef number );

/*!
 * @function    CFNumberGetType
 * @abstract    Returns the type used by a CFNumber object to store its value.
 * @param       number  The CFNumber object to examine.
 * @result      A constant that indicates the data type of the value contained
 *              in number. See CFNumberType for a list of possible values.
 * @discussion  The type specified in the call to CFNumberCreate is not
 *              necessarily preserved when a new CFNumber object is created—it
 *              uses whatever internal storage type the creation function deems
 *              appropriate.
 */
CF_EXPORT CFNumberType CFNumberGetType( CFNumberRef number );

/*!
 * @function    CFNumberGetValue
 * @abstract    Obtains the value of a CFNumber object cast to a specified type.
 * @param       number      The CFNumber object to examine.
 * @param       type        A constant that specifies the data type to return.
 *                          See CFNumberType for a list of possible values.
 * @param       valuePtr    On return, contains the value of number.
 * @result      true if the operation was successful, otherwise false.
 * @discussion  If the argument type differs from the return type, and the
 *              conversion is lossy or the return value is out of range, then
 *              this function passes back an approximate value in valuePtr and
 *              returns false.
 */
CF_EXPORT Boolean CFNumberGetValue( CFNumberRef number, CFNumberType type, void * valuePtr );

/*!
 * @function    CFNumberCompare
 * @abstract    Compares two CFNumber objects and returns a comparison result.
 * @param       number      The CFNumber object to examine.
 * @result      true if number's value is one of the defined floating point
 *              types, otherwise false. The valid floating point types are
 *              listed in CFNumberType.
 */
CF_EXPORT Boolean CFNumberIsFloatType( CFNumberRef number );

/*!
 * @function    CFNumberIsFloatType
 * @abstract    Determines whether a CFNumber object contains a value stored as
 *              one of the defined floating point types.
 * @param       number          The first CFNumber object to compare.
 * @param       otherNumber     The second CFNumber object to compare.
 * @param       context         Pass NULL.
 * @result      A CFComparisonResult constant that indicates whether number is
 *              equal to, less than, or greater than otherNumber.
 * @discussion  When comparing two CFNumber objects using this function, one or
 *              both objects can represent a special-case number such as signed
 *              0, signed infinity, or NaN.
 *              The following rules apply:
 *                  - Negative 0 compares less than positive 0.
 *                  - Positive infinity compares greater than everything except
 *                    itself, to which it compares equal.
 *                  - Negative infinity compares less than everything except
 *                    itself, to which it compares equal.
 *                  - If both numbers are NaN, then they compare equal.
 *                  - If only one of the numbers is NaN, then the NaN compares
 *                    greater than the other number if it is negative, and
 *                    smaller than the other number if it is positive.
 */
CF_EXPORT CFComparisonResult CFNumberCompare( CFNumberRef number, CFNumberRef otherNumber, void * context );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_NUMBER_H */
