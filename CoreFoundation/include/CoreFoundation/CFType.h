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
 * @header      CFType.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION_CF_TYPE_H
#define CORE_FOUNDATION_CF_TYPE_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/MacTypes.h>
#include <stdint.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFTypeID
 * @abstract    A type for unique, constant integer values that identify
 *              particular Core Foundation opaque types.
 * @discussion  Defines a type identifier in Core Foundation. A type ID is an
 *              integer that identifies the opaque type to which a Core
 *              Foundation object "belongs." You use type IDs in various
 *              contexts, such as when you are operating on heterogeneous
 *              collections. Core Foundation provides programmatic interfaces
 *              for obtaining and evaluating type IDs.
 *              Because the value for a type ID can change from release to
 *              release, your code should not rely on stored or hard-coded type
 *              IDs nor should it hard-code any observed properties of a type ID
 *              (such as, for example, it being a small integer).
 */
typedef uint64_t CFTypeID;

/*!
 * @typedef     CFHashCode
 * @abstract    A type for hash codes returned by the CFHash function.
 */
typedef uint64_t CFHashCode;

/*!
 * @typedef     CFTypeRef
 * @abstract    An untyped "generic" reference to any Core Foundation object.
 * @discussion  The CFTypeRef type is the base type defined in Core Foundation.
 *              It is used as the type and return value in several polymorphic
 *              functions. It is a generic object reference that acts as a
 *              placeholder for other true Core Foundation objects.
 */
typedef const void * CFTypeRef;

#include <CoreFoundation/CFString.h>

/*!
 * @function    CFGetAllocator
 * @abstract    Returns the allocator used to allocate a Core Foundation object.
 * @param       obj     The CFType object to examine.
 * @result      The allocator used to allocate memory for obj.
 * @discussion  When you are creating a Core Foundation object sometimes you
 *              want to ensure that the block of memory allocated for the object
 *              is from the same allocator used for another object. One way to
 *              do this is to reuse the allocator assigned to an existing Core
 *              Foundation object when you call a "creation" function.
 */
CF_EXPORT CFAllocatorRef CFGetAllocator( CFTypeRef obj );

/*!
 * @function    CFGetRetainCount
 * @abstract    Returns the reference count of a Core Foundation object.
 * @param       obj     The CFType object to examine.
 * @result      A number representing the reference count of obj.
 * @discussion  You increment the reference count using the CFRetain function,
 *              and decrement the reference count using the CFRelease function.
 *              This function may useful for debugging memory leaks. You
 *              normally do not use this function, otherwise.
 */
CF_EXPORT CFIndex CFGetRetainCount( CFTypeRef obj );

/*!
 * @function    CFMakeCollectable
 * @abstract    Makes a newly-allocated Core Foundation object eligible for
 *              garbage collection.
 * @param       obj     A CFType object to make collectable.
 *                      This value must not be NULL.
 * @result      obj.
 * @discussion  If cf is NULL, this will cause a runtime error and your
 *              application will crash.
 */
CF_EXPORT CFTypeRef CFMakeCollectable( CFTypeRef obj );

/*!
 * @function    CFRetain
 * @abstract    Retains a Core Foundation object.
 * @param       obj     A CFType object to retain. This value must not be NULL.
 * @result      The input value, obj.
 * @discussion  You should retain a Core Foundation object when you receive it
 *              from elsewhere (that is, you did not create or copy it) and you
 *              want it to persist. If you retain a Core Foundation object you
 *              are responsible for releasing it.
 *              If obj is NULL, this will cause a runtime error and your
 *              application will crash.
 */
CF_EXPORT CFTypeRef CFRetain( CFTypeRef obj );

/*!
 * @function    CFRelease
 * @abstract    Releases a Core Foundation object.
 * @param       obj     A CFType object to release. This value must not be NULL.
 * @discussion  If the retain count of cf becomes zero the memory allocated to
 *              the object is deallocated and the object is destroyed. If you
 *              create, copy, or explicitly retain (see the CFRetain function)
 *              a Core Foundation object, you are responsible for releasing it
 *              when you no longer need it.
 *              If obj is NULL, this will cause a runtime error and your
 *              application will crash.
 */
CF_EXPORT void CFRelease( CFTypeRef obj );

/*!
 * @function    CFEqual
 * @abstract    Determines whether two Core Foundation objects are considered
 *              equal.
 * @param       obj1    A CFType object to compare to obj2.
 * @param       obj2    A CFType object to compare to obj1.
 * @result      true if cf1 and cf2 are of the same type and considered equal,
 *              otherwise false.
 * @discussion  Equality is something specific to each Core Foundation opaque
 *              type. For example, two CFNumber objects are equal if the numeric
 *              values they represent are equal. Two CFString objects are equal
 *              if they represent identical sequences of characters, regardless
 *              of encoding.
 */
CF_EXPORT Boolean CFEqual( CFTypeRef obj1, CFTypeRef obj2 );

/*!
 * @function    CFHash
 * @abstract    Returns a code that can be used to identify an object in a
 *              hashing structure.
 * @param       obj     A CFType object to examine.
 * @result      An integer of type CFHashCode that represents a hashing value
 *              for obj.
 * @discussion  Two objects that are equal (as determined by the CFEqual
 *              function) have the same hashing value. However, the converse
 *              is not true: two objects with the same hashing value might not
 *              be equal. That is, hashing values are not necessarily unique.
 *              The hashing value for an object might change from release to
 *              release or from platform to platform.
 */
CF_EXPORT CFHashCode CFHash( CFTypeRef obj );

/*!
 * @function    CFCopyDescription
 * @abstract    Returns a textual description of a Core Foundation object.
 * @param       obj     The CFType object (a generic reference of type
 *                      CFTypeRef) from which to derive a description.
 * @result      A string that contains a description of obj. Ownership follows
 *              the Create Rule..
 * @discussion  The nature of the description differs by object. For example,
 *              a description of a CFArray object would include descriptions of
 *              each of the elements in the collection.
 *              You can use this function for debugging Core Foundation objects
 *              in your code.
 *              Note, however, that the description for a given object may be
 *              different in different releases of the operating system. Do not
 *              create dependencies in your code on the content or format of the
 *              information returned by this function.
 */
CF_EXPORT CFStringRef CFCopyDescription( CFTypeRef obj );

/*!
 * @function    CFCopyTypeIDDescription
 * @abstract    Returns a textual description of a Core Foundation type, as
 *              identified by its type ID, which can be used when debugging.
 * @param       typeID  An integer of type CFTypeID that uniquely identifies a
 *              Core Foundation opaque type.
 * @result      A string containing a type description. Ownership follows the
 *              Create Rule.
 * @discussion  You can use this function for debugging Core Foundation objects
 *              in your code. Note, however, that the description for a given
 *              object may be different in different releases of the operating
 *              system. Do not create dependencies in your code on the content
 *              or format of the information returned by this function.
 */
CF_EXPORT CFStringRef CFCopyTypeIDDescription( CFTypeID typeID );

/*!
 * @function    CFGetTypeID
 * @abstract    Returns the unique identifier of an opaque type to which a Core
 *              Foundation object belongs.
 * @param       obj     The CFType object to examine.
 * @result      A value of type CFTypeID that identifies the opaque type of
 *              obj.
 * @discussion  This function returns a value that uniquely identifies the
 *              opaque type of any Core Foundation object. You can compare this
 *              value with the known CFTypeID identifier obtained with a
 *              "GetTypeID" function specific to a type, for example
 *              CFDateGetTypeID. These values might change from release to
 *              release or platform to platform.
 */
CF_EXPORT CFTypeID CFGetTypeID( CFTypeRef obj );

/*!
 * @function    CFShow
 * @abstract    Prints a description of a Core Foundation object to stderr.
 * @param       obj     A Core Foundation object derived from CFType. If obj is
 *                      not a Core Foundation object, an assertion is raised.
 * @discussion  The output is printed to the standard I/O standard error
 *              (stderr).
 *              This function is useful as a debugging aid for Core Foundation
 *              objects. Because these objects are based on opaque types, it is
 *              difficult to examine their contents directly. However, the
 *              opaque types implement description function callbacks that
 *              return descriptions of their objects. This function invokes
 *              these callbacks.
 */
CF_EXPORT void CFShow( CFTypeRef obj );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_TYPE_H */
