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
 * @header      CFData.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  CFData and its derived mutable type, CFMutableData, provide
 *              support for data objects, object-oriented wrappers for byte
 *              buffers. Data objects let simple allocated buffers (that is,
 *              data with no embedded pointers) take on the behavior of Core
 *              Foundation objects. CFData creates static data objects, and
 *              CFMutableData creates dynamic data objects. Data objects are
 *              typically used for raw data storage.
 *              You use the CFDataCreate and CFDataCreateCopy functions to
 *              create static data objects. These functions make a new copy of
 *              the supplied data. To create a data object that uses the
 *              supplied buffer instead of making a separate copy, use the
 *              CFDataCreateWithBytesNoCopy function. You use the CFDataGetBytes
 *              function to retrieve the bytes and the CFDataGetLength function
 *              to get the length of the bytes.
 *              CFData is "toll-free bridged" with its Cocoa Foundation
 *              counterpart, NSData. What this means is that the Core Foundation
 *              type is interchangeable in function or method calls with the
 *              bridged Foundation object. In other words, in a method where you
 *              see an NSData * parameter, you can pass in a CFDataRef, and in
 *              a function where you see a CFDataRef parameter, you can pass in
 *              an NSData instance. This also applies to concrete subclasses of
 *              NSData. See Toll-Free Bridged Types for more information on
 *              toll-free bridging.
 */

#ifndef CORE_FOUNDATION_CF_DATA_H
#define CORE_FOUNDATION_CF_DATA_H

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFDataRef
 * @abstract    A reference to an immutable CFData object.
 */
typedef const struct CFData * CFDataRef;

/*!
 * @typedef     CFDataSearchFlags
 * @abstract    A CFOptionFlags type for specifying options for searching.
 * @constant    kCFDataSearchBackwards  Performs searching from the end of the
 *                                      range toward the beginning.
 * @constant    kCFDataSearchAnchored   Performs searching only on bytes at the
 *                                      beginning or, if kCFDataSearchBackwards
 *                                      is also specified, at the end of the
 *                                      search range. No match at the beginning
 *                                      or end means nothing is found, even if a
 *                                      matching sequence of bytes occurs
 *                                      elsewhere in the data object.
 */
typedef enum
{
    kCFDataSearchBackwards = 1UL << 0,
    kCFDataSearchAnchored  = 1UL << 1
}
CFDataSearchFlags;

/*!
 * @function    CFDataGetTypeID
 * @abstract    Returns the type identifier for the CFData opaque type.
 * @result      The type identifier for the CFData opaque type.
 * @discussion  CFMutableData objects have the same type identifier as CFData
 *              objects.
 */
CF_EXPORT CFTypeID CFDataGetTypeID( void );

/*!
 * @function    CFDataCreate
 * @abstract    Creates an immutable CFData object using data copied from a
 *              specified byte buffer.
 * @param       allocator   The allocator to use to allocate memory for the new
 *                          object. Pass NULL or kCFAllocatorDefault to use the
 *                          current default allocator.
 * @param       bytes       A pointer to the byte buffer that contains the raw
 *                          data to be copied into theData.
 * @param       length      The number of bytes in the buffer (bytes).
 * @result      A new CFData object, or NULL if there was a problem creating
 *              the object. Ownership follows the Create Rule.
 * @discussion  You must supply a count of the bytes in the buffer. This
 *              function always copies the bytes in the provided buffer into
 *              internal storage.
 */
CF_EXPORT CFDataRef CFDataCreate( CFAllocatorRef allocator, const UInt8 * bytes, CFIndex length );

/*!
 * @function    CFDataCreateCopy
 * @abstract    Creates an immutable copy of a CFData object.
 * @param       allocator   The allocator to use to allocate memory for the new
 *                          object. Pass NULL or kCFAllocatorDefault to use the
 *                          current default allocator.
 * @param       theData     The CFData object to copy.
 * @result      An immutable copy of theData, or NULL if there was a problem
 *              creating the object. Ownership follows the Create Rule.
 * @discussion  The resulting object has the same byte contents as the original
 *              object, but it is always immutable. If the specified allocator
 *              and the allocator of the original object are the same, and the
 *              string is already immutable, this function may simply increment
 *              the retain count without making a true copy. To the caller,
 *              however, the resulting object is a true immutable copy, except
 *              the operation was more efficient.
 *              Use this function when you need to pass a CFData object into
 *              another function by value (not reference).
 */
CF_EXPORT CFDataRef CFDataCreateCopy( CFAllocatorRef allocator, CFDataRef theData );

/*!
 * @function    CFDataCreateWithBytesNoCopy
 * @abstract    Creates an immutable CFData object from an external
 *              (client-owned) byte buffer.
 * @param       allocator           The allocator to use to allocate memory for
 *                                  the new object. Pass NULL or
 *                                  kCFAllocatorDefault to use the current
 *                                  default allocator.
 * @param       bytes               A pointer to the byte buffer to be used as
 *                                  the backing store of the CFData object.
 * @param       length              The number of bytes in the buffer bytes.
 * @param       bytesDeallocator    The allocator to use to deallocate the
 *                                  external buffer when the CFData object is
 *                                  deallocated. If the default allocator is
 *                                  suitable for this purpose, pass NULL or
 *                                  kCFAllocatorDefault. If you do not want the
 *                                  created CFData object to deallocate the
 *                                  buffer (that is, you assume responsibility
 *                                  for freeing it yourself), pass
 *                                  kCFAllocatorNull.
 * @result      A new CFData object, or NULL if there was a problem creating the
 *              object. On a NULL return, the bytes buffer is left intact.
 *              Ownership follows the Create Rule.
 * @discussion  This function creates an immutable CFData object from a buffer
 *              of unstructured bytes. Unless the situation warrants otherwise,
 *              the created object does not copy the external buffer to internal
 *              storage but instead uses the buffer as its backing store.
 *              However, you should never count on the object using the external
 *              buffer since it could copy the buffer to internal storage or
 *              might even dump the buffer altogether and use alternative means
 *              for storing the bytes.
 */
CF_EXPORT CFDataRef CFDataCreateWithBytesNoCopy( CFAllocatorRef allocator, const UInt8 * bytes, CFIndex length, CFAllocatorRef bytesDeallocator );

/*!
 * @function    CFDataGetBytePtr
 * @abstract    Returns a read-only pointer to the bytes of a CFData object.
 * @param       theData     The CFData object to examine.
 * @result      A read-only pointer to the bytes associated with theData.
 * @discussion  This function is guaranteed to return a pointer to a CFData
 *              object's internal bytes. CFData, unlike CFString, does not hide
 *              its internal storage.
 */
CF_EXPORT const UInt8 * CFDataGetBytePtr( CFDataRef theData );

/*!
 * @function    CFDataGetBytes
 * @abstract    Copies the byte contents of a CFData object to an external
 *              buffer.
 * @param       theData     The CFData object to examine.
 * @param       range       The range of bytes in theData to get. To get all of
 *                          the contents, pass
 *                          CFRangeMake( 0,CFDataGetLength( theData ) ).
 * @param       buffer      A pointer to the byte buffer of length range.length
 *                          that is allocated on the stack or heap. On return,
 *                          the buffer contains the requested range of bytes.
 */
CF_EXPORT void CFDataGetBytes( CFDataRef theData, CFRange range, UInt8 * buffer );

/*!
 * @function    CFDataGetLength
 * @abstract    Returns the number of bytes contained by a CFData object.
 *              buffer.
 * @param       theData     The CFData object to examine.
 * @result      An index that specifies the number of bytes in theData.
 */
CF_EXPORT CFIndex CFDataGetLength( CFDataRef theData );

/*!
 * @function    CFDataFind
 * @abstract    Finds and returns the range within a data object of the first
 *              occurrence of the given data, within a given range, subject to
 *              any given options.
 * @param       theData         The data object within which to search.
 * @param       dataToFind      The data to find. Must not be NULL.
 * @param       searchRange     The range within theData to be searched.
 * @param       compareOptions  A bit mask specifying search options. The
 *                              CFDataSearchFlags options can be specified
 *                              singly or combined with the C bitwise OR
 *                              operator
 * @result      The range representing the location and length of dataToFind
 *              within searchRange, modulo the options in compareOptions.
 *              The range returned is relative to the start of the searched
 *              data, not the passed-in search range. Returns { kCFNotFound, 0 }
 *              if dataToFind is not found.
 */
CF_EXPORT CFRange CFDataFind( CFDataRef theData, CFDataRef dataToFind, CFRange searchRange, CFDataSearchFlags compareOptions );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_DATA_H */
