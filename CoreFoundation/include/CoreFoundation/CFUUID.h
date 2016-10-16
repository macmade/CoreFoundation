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
 * @discussion  CFUUID objects are used by plug-ins to uniquely identify types,
 *              interfaces, and factories. When creating a new type, host 
 *              developers must generate UUIDs to identify the type as well as
 *              its interfaces and factories.
 *              UUIDs (Universally Unique Identifiers), also known as GUIDs
 *              (Globally Unique Identifiers) or IIDs (Interface Identifiers),
 *              are 128-bit values designed to be unique.
 *              The standard format for UUIDs represented in ASCII is a string
 *              punctuated by hyphens, for example
 *              68753A44-4D6F-1226-9C60-0050E4C00067. The hex representation
 *              looks, as you might expect, like a list of numerical values
 *              preceded by 0x. For example, 0x68, 0x75, 0x3A, 0x44, 0x4D, 0x6F,
 *              0x12, 0x26, 0x9C, 0x60, 0x00, 0x50, 0xE4, 0xC0, 0x00, 0x67.
 *              To use a UUID, you create it and then copy the resulting
 *              strings into your header and C language source files. Because a
 *              UUID is expressed as an array of bytes, there are no endianness
 *              considerations for different platforms.
 *              You can create a CFUUID object using any one of the
 *              CFUUIDCreate... functions. Use the
 *              CFUUIDGetConstantUUIDWithBytes function if you want to declare
 *              a UUID constant in a #define statement. You can get the raw
 *              bytes of an existing CFUUID object using the
 *              CFUUIDGetUUIDBytes function.
 */

#ifndef CORE_FOUNDATION_CF_UUID_H
#define CORE_FOUNDATION_CF_UUID_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFUUIDRef
 * @abstract    A reference to a CFUUID object.
 */
typedef const struct CFUUID * CFUUIDRef;

/*!
 * @typedef     CFUUIDBytes
 * @abstract    A 128-bit struct that represents a UUID as raw bytes.
 * @constant    byte0   The first byte.
 * @constant    byte1   The second byte.
 * @constant    byte2   The third byte.
 * @constant    byte3   The fourth byte.
 * @constant    byte4   The fifth byte.
 * @constant    byte5   The sixth byte.
 * @constant    byte6   The seventh byte.
 * @constant    byte7   The eighth byte.
 * @constant    byte8   The ninth byte.
 * @constant    byte9   The tenth byte.
 * @constant    byte10  The eleventh byte.
 * @constant    byte11  The twelfth byte.
 * @constant    byte12  The thirteenth byte.
 * @constant    byte13  The fourteenth byte.
 * @constant    byte14  The fifteenth byte.
 * @constant    byte15  The sixteenth byte.
 * @discussion  This structure can be obtained from a CFUUID object using the
 *              CFUUIDGetUUIDBytes function. This structure can be passed to
 *              functions that expect a raw UUID.
 */
typedef struct
{
    UInt8 byte0;
    UInt8 byte1;
    UInt8 byte2;
    UInt8 byte3;
    UInt8 byte4;
    UInt8 byte5;
    UInt8 byte6;
    UInt8 byte7;
    UInt8 byte8;
    UInt8 byte9;
    UInt8 byte10;
    UInt8 byte11;
    UInt8 byte12;
    UInt8 byte13;
    UInt8 byte14;
    UInt8 byte15;
}
CFUUIDBytes;

/*!
 * @function    CFUUIDGetTypeID
 * @abstract    Returns the type identifier for all CFUUID objects.
 * @result      The type identifier for the CFUUID opaque type.
 */
CF_EXPORT CFTypeID CFUUIDGetTypeID( void );

/*!
 * @function    CFUUIDCreate
 * @abstract    Creates a Universally Unique Identifier (UUID) object.
 * @param       alloc   The allocator to use to allocate memory for the new
 *                      CFUUID object. Pass NULL or kCFAllocatorDefault to use
 *                      the current default allocator.
 * @result      A new CFUUID object. Ownership follows the Create Rule.
 */
CF_EXPORT CFUUIDRef CFUUIDCreate( CFAllocatorRef alloc );

/*!
 * @function    CFUUIDCreateFromString
 * @abstract    Creates a CFUUID object for a specified string.
 * @param       alloc       The allocator to use to allocate memory for the new
 *                          CFUUID object. Pass NULL or kCFAllocatorDefault to
 *                          use the current default allocator.
 * @param       uuidStr     A string containing a UUID. The standard format for
 *                          UUIDs represented in ASCII is a string punctuated by
 *                          hyphens, for example
 *                          68753A44-4D6F-1226-9C60-0050E4C00067.
 * @result      A new CFUUID object, or if a CFUUID object of the same value
 *              already exists, the existing instance with its reference count
 *              incremented. Ownership follows the Create Rule.
 */
CF_EXPORT CFUUIDRef CFUUIDCreateFromString( CFAllocatorRef alloc, CFStringRef uuidStr );

/*!
 * @function    CFUUIDCreateFromUUIDBytes
 * @abstract    Creates a CFUUID object from raw UUID bytes.
 * @param       alloc   The allocator to use to allocate memory for the new
 *                      CFUUID object. Pass NULL or kCFAllocatorDefault to use
 *                      the current default allocator.
 * @param       bytes   Raw UUID bytes to use to create the CFUUID object.
 * @result      A new CFUUID object. Ownership follows the Create Rule.
 */
CF_EXPORT CFUUIDRef CFUUIDCreateFromUUIDBytes( CFAllocatorRef alloc, CFUUIDBytes bytes );

/*!
 * @function    CFUUIDCreateWithBytes
 * @abstract    Creates a CFUUID object from raw UUID bytes.
 * @param       alloc   The allocator to use to allocate memory for the new CFUUID object. Pass NULL or kCFAllocatorDefault to use the current default allocator.
 * @param       byte0	Raw byte number 0.
 * @param       byte1	Raw byte number 1.
 * @param       byte2	Raw byte number 2.
 * @param       byte3	Raw byte number 3.
 * @param       byte4	Raw byte number 4.
 * @param       byte5	Raw byte number 5.
 * @param       byte6	Raw byte number 6.
 * @param       byte7	Raw byte number 7.
 * @param       byte8	Raw byte number 8.
 * @param       byte9	Raw byte number 9.
 * @param       byte10	Raw byte number 10.
 * @param       byte11	Raw byte number 11.
 * @param       byte12	Raw byte number 12.
 * @param       byte13	Raw byte number 13.
 * @param       byte14	Raw byte number 14.
 * @param       byte15	Raw byte number 15.
 * @result      A new CFUUID object, or, if a CFUUID object of the same value
 *              already exists, the existing instance with its reference count
 *              incremented. Ownership follows the Create Rule.
 */
CF_EXPORT CFUUIDRef CFUUIDCreateWithBytes( CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15 );

/*!
 * @function    CFUUIDCreateString
 * @abstract    Returns the string representation of a specified CFUUID object.
 * @param       alloc   The allocator to use to allocate memory for the new
 *                      string. Pass NULL or kCFAllocatorDefault to use the
 *                      current default allocator.
 * @param       uuid    The CFUUID object whose string representation to obtain.
 * @result      The string representation of uuid. Ownership follows the
 *              Create Rule.
 */
CF_EXPORT CFStringRef CFUUIDCreateString( CFAllocatorRef alloc, CFUUIDRef uuid );

/*!
 * @function    CFUUIDGetConstantUUIDWithBytes
 * @abstract    Returns a CFUUID object from raw UUID bytes.
 * @param       alloc   The allocator to use to allocate memory for the new
 *                      CFUUID object. Pass NULL or kCFAllocatorDefault to use
 *                      the current default allocator.
 * @param       byte0	Raw byte number 0.
 * @param       byte1	Raw byte number 1.
 * @param       byte2	Raw byte number 2.
 * @param       byte3	Raw byte number 3.
 * @param       byte4	Raw byte number 4.
 * @param       byte5	Raw byte number 5.
 * @param       byte6	Raw byte number 6.
 * @param       byte7	Raw byte number 7.
 * @param       byte8	Raw byte number 8.
 * @param       byte9	Raw byte number 9.
 * @param       byte10	Raw byte number 10.
 * @param       byte11	Raw byte number 11.
 * @param       byte12	Raw byte number 12.
 * @param       byte13	Raw byte number 13.
 * @param       byte14	Raw byte number 14.
 * @param       byte15	Raw byte number 15.
 * @result      A CFUUID object. Ownership follows the Get Rule.
 * @discussion  This function can be used in headers to declare a UUID constant
 *              with #define.
 */
CF_EXPORT CFUUIDRef CFUUIDGetConstantUUIDWithBytes( CFAllocatorRef alloc, UInt8 byte0, UInt8 byte1, UInt8 byte2, UInt8 byte3, UInt8 byte4, UInt8 byte5, UInt8 byte6, UInt8 byte7, UInt8 byte8, UInt8 byte9, UInt8 byte10, UInt8 byte11, UInt8 byte12, UInt8 byte13, UInt8 byte14, UInt8 byte15 );

/*!
 * @function    CFUUIDGetUUIDBytes
 * @result      Returns the value of a UUID object as raw bytes.
 * @param       uuid    The CFUUID object to examine.
 * @result      The value of uuid represented as raw bytes.
 */
CF_EXPORT CFUUIDBytes CFUUIDGetUUIDBytes( CFUUIDRef uuid );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_UUID_H */
