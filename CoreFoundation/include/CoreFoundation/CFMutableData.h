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
 * @header      CFMutableData.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  CFMutableData manages dynamic binary data. The basic interface
 *              for managing binary data is provided by CFData. CFMutableData
 *              adds functions to modify the contents of a binary data object.
 *              You create a mutable data object using either the
 *              CFDataCreateMutable or CFDataCreateMutableCopy function.
 *              Bytes are added to a data object with the CFDataAppendBytes
 *              function. Bytes are removed from a data object with the
 *              CFDataDeleteBytes function.
 *              Important: many of the CFMutableData functions take a CFIndex
 *              length or capacity argument. You must not pass a negative number
 *              for such values—this may introduce a security risk.
 *              CFMutableData is "toll-free bridged" with its Cocoa Foundation
 *              counterpart, NSMutableData. What this means is that the Core
 *              Foundation type is interchangeable in function or method calls
 *              with the bridged Foundation object. In other words, in a method
 *              where you see an NSMutableData * parameter, you can pass in a
 *              CFMutableDataRef, and in a function where you see a
 *              CFMutableDataRef parameter, you can pass in an NSMutableData
 *              instance. This also applies to concrete subclasses of
 *              NSMutableData. See Toll-Free Bridged Types for more information
 *              on toll-free bridging.
 */

#ifndef CORE_FOUNDATION_CF_MUTABLE_DATA_H
#define CORE_FOUNDATION_CF_MUTABLE_DATA_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFData.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFMutableDataRef
 * @abstract    A reference to a CFMutableData object.
 */
typedef struct CFData * CFMutableDataRef;

/*!
 * @function    CFDataCreateMutable
 * @abstract    Creates an empty CFMutableData object.
 * @param       allocator   The CFAllocator object to be used to allocate memory
 *                          for the new object. Pass NULL or kCFAllocatorDefault
 *                          to use the current default allocator.
 * @param       capacity    The maximum number of bytes that the CFData object
 *                          can contain. The CFData object starts empty and can
 *                          grow to contain this number of values (and it can
 *                          have less).
 *                          Pass 0 to specify that the maximum capacity is not
 *                          limited. The value must not be negative.
 * @result      A CFMutableData object or NULL if there was a problem creating
 *              the object. Ownership follows the Create Rule.
 * @discussion  This function creates an empty (that is, content-less)
 *              CFMutableData object. You can add raw data to this object with
 *              the CFDataAppendBytes function, and thereafter you can replace
 *              and delete characters with the appropriate CFMutableData
 *              functions. If the capacity parameter is greater than 0, any 
 *              attempt to add characters beyond this limit can result in
 *              undefined behavior.
 */
CF_EXPORT CFMutableDataRef CFDataCreateMutable( CFAllocatorRef allocator, CFIndex capacity );

/*!
 * @function    CFDataCreateMutableCopy
 * @abstract    Creates a CFMutableData object by copying another CFData object.
 * @param       allocator   The CFAllocator object to be used to allocate memory
 *                          for the new object. Pass NULL or kCFAllocatorDefault
 *                          to use the current default allocator.
 * @param       capacity    The maximum number of bytes that the CFData object
 *                          can contain. The CFData object starts with the same
 *                          length as the original object, and can grow to
 *                          contain this number of bytes.
 *                          Pass 0 to specify that the maximum capacity is not
 *                          limited. If non-0, capacity must be greater than or
 *                          equal to the length of theData.
 * @param       theData     The CFData object to be copied.
 * @result      A CFMutableData object that has the same contents as the
 *              original object. Returns NULL if there was a problem copying the
 *              object. Ownership follows the Create Rule.
 */
CF_EXPORT CFMutableDataRef CFDataCreateMutableCopy( CFAllocatorRef allocator, CFIndex capacity, CFDataRef theData );

/*!
 * @function    CFDataGetMutableBytePtr
 * @abstract    Returns a pointer to a mutable byte buffer of a CFMutableData
 *              object.
 * @param       theData     A CFMutableData object. If you pass an immutable
 *                          CFData object, the behavior is not defined.
 * @result      A pointer to the bytes associated with theData.
 * @discussion  If the length of theData’s data is not zero, this function is
 *              guaranteed to return a pointer to a CFMutableData object's
 *              internal bytes. If the length of theData’s data is zero, this
 *              function may or may not return NULL dependent upon many factors
 *              related to how the object was created (moreover, in this case
 *              the function result might change between different releases and
 *              on different platforms).
 */
CF_EXPORT UInt8 * CFDataGetMutableBytePtr( CFMutableDataRef theData );

/*!
 * @function    CFDataAppendBytes
 * @abstract    Appends the bytes from a byte buffer to the contents of a CFData
 *              object.
 * @param       theData     A CFMutableData object. If you pass an immutable
 *                          CFData object, the behavior is not defined.
 * @param       bytes       A pointer to the buffer of bytes to be added to
 *                          theData.
 * @param       length      The number of bytes in the byte buffer bytes.
 */
CF_EXPORT void CFDataAppendBytes( CFMutableDataRef theData, const UInt8 * bytes, CFIndex length );

/*!
 * @function    CFDataDeleteBytes
 * @abstract    Deletes the bytes in a CFMutableData object within a specified
 *              range.
 * @param       theData     A CFMutableData object. If you pass an immutable
 *                          CFData object, the behavior is not defined.
 * @param       range       The range of bytes (that is, the starting byte and
 *                          the number of bytes from that point) to delete from
 *                          theData's byte buffer.
 */
CF_EXPORT void CFDataDeleteBytes( CFMutableDataRef theData, CFRange range );

/*!
 * @function    CFDataReplaceBytes
 * @abstract    Replaces those bytes in a CFMutableData object that fall within
 *              a specified range with other bytes.
 * @param       theData     A CFMutableData object. If you pass an immutable
 *                          CFData object, the behavior is not defined.
 * @param       range       The range of bytes (that is, the starting byte and
 *                          the number of bytes from that point) to delete from
 *                          theData's byte buffer.
 * @param       newBytes    A pointer to the buffer containing the replacement
 *                          bytes.
 * @param       newLength   The number of bytes in the byte buffer newBytes.
 */
CF_EXPORT void CFDataReplaceBytes( CFMutableDataRef theData, CFRange range, const UInt8 * newBytes, CFIndex newLength );

/*!
 * @function    CFDataIncreaseLength
 * @abstract    Increases the length of a CFMutableData object's internal byte
 *              buffer, zero-filling the extension to the buffer.
 * @param       theData         A CFMutableData object. If you pass an immutable
 *                              CFData object, the behavior is not defined.
 * @param       extraLength     The number of bytes by which to increase the
 *                              byte buffer.
 * @discussion  This function increases the length of a CFMutableData object's
 *              underlying byte buffer to a new size, initializing the new bytes
 *              to 0.
 */
CF_EXPORT void CFDataIncreaseLength( CFMutableDataRef theData, CFIndex extraLength );

/*!
 * @function    CFDataSetLength
 * @abstract    Resets the length of a CFMutableData object's internal byte
 *              buffer.
 * @param       theData     A CFMutableData object. If you pass an immutable
 *                          CFData object, the behavior is not defined.
 * @param       length      The new size of theData's byte buffer.
 * @discussion  This function resets the length of a CFMutableData object's
 *              underlying byte buffer to a new size. If that size is less than
 *              the current size, it truncates the excess bytes. If that size is
 *              greater than the current size, it zero-fills the extension to
 *              the byte buffer.
 */
CF_EXPORT void CFDataSetLength( CFMutableDataRef theData, CFIndex length );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_MUTABLE_DATA_H */
