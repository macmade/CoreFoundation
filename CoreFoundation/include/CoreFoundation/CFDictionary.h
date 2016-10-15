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
 * @header      CFDictionary.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  CFDictionary and its derived mutable type, CFMutableDictionary,
 *              manage associations of key-value pairs. CFDictionary creates
 *              static dictionaries where you set the key-value pairs when first
 *              creating a dictionary and cannot modify them afterward;
 *              CFMutableDictionary creates dynamic dictionaries where you can
 *              add or delete key-value pairs at any time, and the dictionary
 *              automatically allocates memory as needed.
 *              A key-value pair within a dictionary is called an entry. Each
 *              entry consists of one object that represents the key and a
 *              second object that is that key's value. Within a dictionary,
 *              the keys are unique. That is, no two keys in a single dictionary
 *              are equal (as determined by the equal callback). Internally,
 *              a dictionary uses a hash table to organize its storage and to
 *              provide rapid access to a value given the corresponding key.
 *              Keys for a CFDictionary may be of any C type, however note that
 *              if you want to convert a CFPropertyList to XML, any dictionary's
 *              keys must be CFString objects.
 *              You create static dictionaries using either the
 *              CFDictionaryCreate or CFDictionaryCreateCopy function. Key-value
 *              pairs are passed as parameters to CFDictionaryCreate. When
 *              adding key-value pairs to a dictionary, the keys and values are
 *              not copied—they are retained so they are not invalidated before
 *              the dictionary is deallocated.
 *              CFDictionary provides functions for querying the values of a
 *              dictionary. The function CFDictionaryGetCount returns the number
 *              of key-value pairs in a dictionary; the
 *              CFDictionaryContainsValue function checks if a value is in a
 *              dictionary; and CFDictionaryGetKeysAndValues returns a C array
 *              containing all the values and a C array containing all the keys
 *              in a dictionary.
 *              The CFDictionaryApplyFunction function lets you apply a function
 *              to all key-value pairs in a dictionary.
 *              CFDictionary is "toll-free bridged" with its Cocoa Foundation
 *              counterpart, NSDictionary. This means that the Core Foundation
 *              type is interchangeable in function or method calls with the
 *              bridged Foundation object. Therefore, in a method where you see
 *              an NSDictionary * parameter, you can pass in a CFDictionaryRef,
 *              and in a function where you see a CFDictionaryRef parameter, you
 *              can pass in an NSDictionary instance. This also applies to
 *              concrete subclasses of NSDictionary. See Toll-Free Bridged Types
 *              for more information on toll-free bridging.
 */

#ifndef CORE_FOUNDATION_CF_DICTIONARY_H
#define CORE_FOUNDATION_CF_DICTIONARY_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFString.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFDictionaryRef
 * @abstract    A reference to an immutable dictionary object.
 */
typedef const struct CFDictionary * CFDictionaryRef;

/*!
 * @typedef     CFDictionaryApplierFunction
 * @abstract    Prototype of a callback function that may be applied to every
 *              key-value pair in a dictionary.
 * @param       key         The key associated with the current key-value pair.
 * @param       value       The value associated with the current key-value
 *                          pair.
 * @param       context     The program-defined context parameter given to the
 *                          apply function.
 * @discussion  This callback is passed to the CFDictionaryApplyFunction
 *              function which iterates over the key-value pairs in a dictionary
 *              and applies the behavior defined in the applier function to each
 *              key-value pair in a dictionary.
 */
typedef void ( * CFDictionaryApplierFunction )( const void * key, const void * value, void * context );

/*!
 * @typedef     CFDictionaryCopyDescriptionCallBack
 * @abstract    Prototype of a callback function used to get a description of a value or key in a dictionary.
 * @param       value   The value to be described.
 * @result      A text description of value.
 * @discussion  This callback is passed to CFDictionaryCreate in a
 *              CFDictionaryKeyCallBacks structure or
 *              CFDictionaryValueCallBacks. This callback is used by the
 *              CFCopyDescription function.
 */
typedef CFStringRef ( * CFDictionaryCopyDescriptionCallBack )( const void * value );

/*!
 * @typedef     CFDictionaryEqualCallBack
 * @abstract    Prototype of a callback function used to determine if two values
 *              or keys in a dictionary are equal.
 * @param       value1  A value in the dictionary.
 * @param       value2	Another value in the dictionary.
 * @discussion  This callback is passed to CFDictionaryCreate in a
 *              CFDictionaryKeyCallBacks and CFDictionaryValueCallBacks
 *              structure.
 */
typedef Boolean ( * CFDictionaryEqualCallBack )( const void * value1, const void * value2 );

/*!
 * @typedef     CFDictionaryHashCallBack
 * @abstract    Prototype of a callback function invoked to compute a hash code
 *              for a key. Hash codes are used when key-value pairs are
 *              accessed, added, or removed from a collection.
 * @param       value   The value used to compute the hash code.
 * @result      An integer that can be used as a table address in a hash table
 *              structure.
 * @discussion  This callback is passed to CFDictionaryCreate in a
 *              CFDictionaryKeyCallBacks structure.
 */
typedef CFHashCode ( * CFDictionaryHashCallBack )( const void * value );

/*!
 * @typedef     CFDictionaryReleaseCallBack
 * @abstract    Prototype of a callback function used to release a key-value
 *              pair before it's removed from a dictionary.
 * @param       allocator   The dictionary's allocator.
 * @param       value       The value being removed from the dictionary.
 */
typedef void ( * CFDictionaryReleaseCallBack )( CFAllocatorRef allocator, const void * value );

/*!
 * @typedef     CFDictionaryRetainCallBack
 * @abstract    Prototype of a callback function used to retain a value or key
 *              being added to a dictionary.
 * @param       allocator   The dictionary's allocator.
 * @param       value       The value being added to the dictionary.
 * @result      The value or key to store in the dictionary, which is usually
 *              the value parameter passed to this callback, but may be a
 *              different value if a different value should be stored in the
 *              collection.
 * @discussion  This callback is passed to CFDictionaryCreate in a
 *              CFDictionaryKeyCallBacks and CFDictionaryValueCallBacks
 *              structure.
 */
typedef const void * ( * CFDictionaryRetainCallBack )( CFAllocatorRef allocator, const void * value );

/*!
 * @typedef     CFDictionaryKeyCallBacks
 * @abstract    This structure contains the callbacks used to retain, release,
 *              describe, and compare the keys in a dictionary.
 * @field       version             The version number of this structure. If not
 *                                  one of the defined version numbers for this
 *                                  opaque type, the behavior is undefined. The
 *                                  current version of this structure is 0.
 * @field       retain              The callback used to retain each key as they
 *                                  are added to the collection. This callback
 *                                  returns the value to use as the key in the
 *                                  dictionary, which is usually the value
 *                                  parameter passed to this callback, but may
 *                                  be a different value if a different value
 *                                  should be used as the key. If NULL, keys are
 *                                  not retained. See CFDictionaryRetainCallBack
 *                                  for a descriptions of this function's
 *                                  parameters.
 * @field       release             The callback used to release keys as they
 *                                  are removed from the dictionary. If NULL,
 *                                  keys are not released. See
 *                                  CFDictionaryReleaseCallBack for a
 *                                  description of this callback.
 * @field       copyDescription     The callback used to create a descriptive
 *                                  string representation of each key in the
 *                                  dictionary. If NULL, the collection will
 *                                  create a simple description of each key.
 *                                  See CFDictionaryCopyDescriptionCallBack for
 *                                  a description of this callback.
 * @field       equal               The callback used to compare keys in the
 *                                  dictionary for equality. If NULL, the
 *                                  collection will use pointer equality to
 *                                  compare keys in the collection. See
 *                                  CFDictionaryEqualCallBack for a description
 *                                  of this callback.
 * @field       hash                The callback used to compute a hash code for
 *                                  keys as they are used to access, add, or
 *                                  remove values in the dictionary. If NULL,
 *                                  the collection computes a hash code by
 *                                  converting the pointer value to an integer.
 *                                  See CFDictionaryHashCallBack for a
 *                                  description of this callback.
 */
typedef struct
{
    CFIndex                             version;
    CFDictionaryRetainCallBack          retain;
    CFDictionaryReleaseCallBack         release;
    CFDictionaryCopyDescriptionCallBack copyDescription;
    CFDictionaryEqualCallBack           equal;
    CFDictionaryHashCallBack            hash;
}
CFDictionaryKeyCallBacks;

/*!
 * @typedef     CFDictionaryValueCallBacks
 * @abstract    This structure contains the callbacks used to retain, release,
 *              describe, and compare the values in a dictionary.
 * @field       version             The version number of this structure. If not
 *                                  one of the defined version numbers for this
 *                                  opaque type, the behavior is undefined.
 *                                  The current version of this structure is 0.   
 * @field       retain              The callback used to retain each value as
 *                                  they are added to the collection. This
 *                                  callback returns the value to use as the
 *                                  value in the dictionary, which is usually
 *                                  the value parameter passed to this callback,
 *                                  but may be a different value if a different
 *                                  value should be used as the value. If NULL,
 *                                  values are not retained. See
 *                                  CFDictionaryRetainCallBack for a
 *                                  descriptions of this function's parameters.
 * @field       release             The callback used to release values as they
 *                                  are removed from the dictionary. If NULL,
 *                                  values are not released. See
 *                                  CFDictionaryReleaseCallBack for a
 *                                  description of this callback.
 * @field       copyDescription     The callback used to create a descriptive
 *                                  string representation of each value in the
 *                                  dictionary. If NULL, the collection will
 *                                  create a simple description of each value.
 *                                  See CFDictionaryCopyDescriptionCallBack for
 *                                  a description of this callback.
 * @field       equal               The callback used to compare values in the
 *                                  dictionary for equality. If NULL, the
 *                                  collection will use pointer equality to
 *                                  compare values in the collection. See
 *                                  CFDictionaryEqualCallBack for a description
 *                                  of this callback.
 */
typedef struct
{
    CFIndex                             version;
    CFDictionaryRetainCallBack          retain;
    CFDictionaryReleaseCallBack         release;
    CFDictionaryCopyDescriptionCallBack copyDescription;
    CFDictionaryEqualCallBack           equal;
}
CFDictionaryValueCallBacks;

/*!
 * @constant    kCFCopyStringDictionaryKeyCallBacks
 * @abstract    Predefined CFDictionaryKeyCallBacks structure containing a set
 *              of callbacks appropriate for use when the keys of a CFDictionary
 *              are all CFString objects, which may be mutable and need to be
 *              copied in order to serve as constant keys for the values in the
 *              dictionary.
 * @discussion  You typically use a pointer to this constant when creating a new
 *              dictionary.
 *              Important: for performance reasons, the default
 *              kCFCopyStringDictionaryKeyCallBacks behavior uses CFEqual which
 *              does not normalize the strings. This means that, for example, it
 *              does not consider CFStrings to be equal when they are the same
 *              but one is in pre-composed form (say, originating from a UTF-16
 *              text file) and the other in decomposed form (say, originating
 *              from a file name). In cases where you use strings from different
 *              sources, you may want to pre-normalize the keys or else use a
 *              different set of functions to perform the comparison.
 */
CF_EXPORT const CFDictionaryKeyCallBacks kCFCopyStringDictionaryKeyCallBacks;

/*!
 * @constant    kCFCopyStringDictionaryKeyCallBacks
 * @abstract    Predefined CFDictionaryKeyCallBacks structure containing a set
 *              of callbacks appropriate for use when the keys of a CFDictionary
 *              are all CFType-derived objects.
 * @discussion  The retain callback is CFRetain, the release callback is
 *              CFRelease, the copy callback is CFCopyDescription, the equal
 *              callback is CFEqual. Therefore, if you use a pointer to this
 *              constant when creating the dictionary, keys are automatically
 *              retained when added to the collection, and released when removed
 *              from the collection.
 */
CF_EXPORT const CFDictionaryKeyCallBacks kCFTypeDictionaryKeyCallBacks;

/*!
 * @constant    kCFCopyStringDictionaryKeyCallBacks
 * @abstract    Predefined CFDictionaryValueCallBacks structure containing a set
 *              of callbacks appropriate for use when the values in a
 *              CFDictionary are all CFType-derived objects.
 * @discussion  The retain callback is CFRetain, the release callback is
 *              CFRelease, the copy callback is CFCopyDescription, and the equal
 *              callback is CFEqual. Therefore, if you use a pointer to this
 *              constant when creating the dictionary, values are automatically
 *              retained when added to the collection, and released when removed
 *              from the collection.
 */
CF_EXPORT const CFDictionaryValueCallBacks kCFTypeDictionaryValueCallBacks;

/*!
 * @function    CFDictionaryGetTypeID
 * @abstract    Returns the type identifier for the CFDictionary opaque type.
 * @result      The type identifier for the CFDictionary opaque type.
 *              CFMutableDictionary objects have the same type identifier as
 *              CFDictionary objects.
 */
CF_EXPORT CFTypeID CFDictionaryGetTypeID( void );

/*!
 * @function    CFDictionaryCreate
 * @abstract    Creates an immutable dictionary containing the specified
 *              key-value pairs.
 * @param       allocator       The allocator to use to allocate memory for the
 *                              new dictionary. Pass NULL or kCFAllocatorDefault
 *                              to use the current default allocator.
 * @param       keys            A C array of the pointer-sized keys to be in the
 *                              new dictionary. This value may be NULL if the
 *                              numValues parameter is 0. This C array is not
 *                              changed or freed by this function. The value
 *                              must be a valid pointer to a C array of at least
 *                              numValues pointers.
 * @param       values          A C array of the pointer-sized values to be in
 *                              the new dictionary. This value may be NULL if
 *                              the numValues parameter is 0. This C array is
 *                              not changed or freed by this function. The value
 *                              must be a valid pointer to a C array of at least
 *                              numValues elements.
 * @param       numValues       The number of key-value pairs to copy from the
 *                              keys and values C arrays into the new
 *                              dictionary. This number will be the count of the
 *                              dictionary; it must be non-negative and less
 *                              than or equal to the actual number of keys or
 *                              values.
 * @param       keyCallBacks    A pointer to a CFDictionaryKeyCallBacks
 *                              structure initialized with the callbacks to use
 *                              to retain, release, describe, and compare keys
 *                              in the dictionary. A copy of the contents of the
 *                              callbacks structure is made, so that a pointer
 *                              to a structure on the stack can be passed in or
 *                              can be reused for multiple collection creations.
 *                              This value may be NULL, which is treated as if a
 *                              valid structure of version 0 with all fields
 *                              NULL had been passed in. Otherwise, if any of
 *                              the fields are not valid pointers to functions
 *                              of the correct type, or this parameter is not a
 *                              valid pointer to a CFDictionaryKeyCallBacks
 *                              structure, the behavior is undefined. If any of
 *                              the keys put into the collection is not one
 *                              understood by one of the callback functions the
 *                              behavior when that callback function is used
 *                              is undefined.
 *                              If the collection will contain CFType objects
 *                              only, then pass a pointer to
 *                              kCFTypeDictionaryKeyCallBacks as this parameter
 *                              to use the default callback functions.
 * @param       valueCallBacks  A pointer to a CFDictionaryValueCallBacks
 *                              structure initialized with the callbacks to use
 *                              to retain, release, describe, and compare values
 *                              in the dictionary. A copy of the contents of the
 *                              callbacks structure is made, so that a pointer
 *                              to a structure on the stack can be passed in or
 *                              can be reused for multiple collection creations.
 *                              This value may be NULL, which is treated as if a
 *                              valid structure of version 0 with all fields
 *                              NULL had been passed in. Otherwise, if any of
 *                              the fields are not valid pointers to functions
 *                              of the correct type, or this parameter is not a
 *                              valid pointer to a CFDictionaryValueCallBacks
 *                              structure, the behavior is undefined. If any
 *                              value put into the collection is not one
 *                              understood by one of the callback functions the
 *                              behavior when that callback function is used is
 *                              undefined.
 *                              If the collection will contain CFType objects
 *                              only, then pass a pointer to
 *                              kCFTypeDictionaryValueCallBacks as this
 *                              parameter to use the default callback functions.
 * @result      A new dictionary, or NULL if there was a problem creating the
 *              object. Ownership follows the Create Rule.
 */
CF_EXPORT CFDictionaryRef CFDictionaryCreate( CFAllocatorRef allocator, const void ** keys, const void ** values, CFIndex numValues, const CFDictionaryKeyCallBacks * keyCallBacks, const CFDictionaryValueCallBacks * valueCallBacks );

/*!
 * @function    CFDictionaryCreateCopy
 * @abstract    Creates and returns a new immutable dictionary with the
 *              key-value pairs of another dictionary.
 * @param       allocator   The allocator to use to allocate memory for the new
 *                          dictionary. Pass NULL or kCFAllocatorDefault to use
 *                          the current default allocator.
 * @param       theDict     The dictionary to copy. The keys and values from the
 *                          dictionary are copied as pointers into the new
 *                          dictionary. However, the keys and values are also
 *                          retained by the new dictionary. The count of the new
 *                          dictionary is the same as the count of theDict. The
 *                          new dictionary uses the same callbacks as theDict.
 * @result      A new dictionary that contains the same key-value pairs as
 *              theDict, or NULL if there was a problem creating the object.
 *              Ownership follows the Create Rule.
 */
CF_EXPORT CFDictionaryRef CFDictionaryCreateCopy( CFAllocatorRef allocator, CFDictionaryRef theDict );

/*!
 * @function    CFDictionaryContainsKey
 * @abstract    Returns a Boolean value that indicates whether a given key is in
 *              a dictionary.
 * @param       theDict     The dictionary to examine.
 * @param       key         The key for which to find matches in theDict. The
 *                          key hash and equal callbacks provided when the
 *                          dictionary was created, are used to compare. If the
 *                          hash callback is NULL, key is treated as a pointer
 *                          and converted to an integer. If the equal callback
 *                          is NULL, pointer equality (in C, ==) is used.
 *                          If key, or any of the keys in the dictionary, is not
 *                          understood by the equal callback, the behavior is
 *                          undefined.
 * @result      true if key is in the dictionary, otherwise false.
 */
CF_EXPORT Boolean CFDictionaryContainsKey( CFDictionaryRef theDict, const void * key );

/*!
 * @function    CFDictionaryContainsValue
 * @abstract    Returns a Boolean value that indicates whether a given value is
 *              in a dictionary.
 * @param       theDict     The dictionary to examine.
 * @param       value       The value for which to find matches in theDict.
 *                          The value equal callback provided when the
 *                          dictionary was created is used to compare. If the
 *                          equal callback was NULL, pointer equality
 *                          (in C, ==) is used. If value, or any other value in
 *                          the dictionary, is not understood by the equal
 *                          callback, the behavior is undefined.
 * @result      true if value is in the dictionary, otherwise false.
 */
CF_EXPORT Boolean CFDictionaryContainsValue( CFDictionaryRef theDict, const void * value );

/*!
 * @function    CFDictionaryGetCount
 * @abstract    Returns the number of key-value pairs in a dictionary.
 * @param       theDict     The dictionary to examine.
 * @result      The number of number of key-value pairs in theDict.
 */
CF_EXPORT CFIndex CFDictionaryGetCount( CFDictionaryRef theDict );

/*!
 * @function    CFDictionaryGetCountOfKey
 * @abstract    Returns the number of times a key occurs in a dictionary.
 * @param       theDict     The dictionary to examine.
 * @param       key         The key for which to find matches in theDict.
 *                          The key hash and equal callbacks provided when the
 *                          dictionary was created are used to compare. If the
 *                          hash callback was NULL, the key is treated as a
 *                          pointer and converted to an integer. If the equal
 *                          callback was NULL, pointer equality (in C, ==) is
 *                          used. If key, or any of the keys in the dictionary,
 *                          is not understood by the equal callback,
 *                          the behavior is undefined.
 * @result      Returns 1 if a matching key is used by the dictionary, otherwise 0.
 */
CF_EXPORT CFIndex CFDictionaryGetCountOfKey( CFDictionaryRef theDict, const void * key );

/*!
 * @function    CFDictionaryGetCountOfValue
 * @abstract    Counts the number of times a given value occurs in the dictionary.
 * @param       theDict     The dictionary to examine.
 * @param       value       The value for which to find matches in theDict.
 *                          The value equal callback provided when the
 *                          dictionary was created is used to compare. If the
 *                          equal callback was NULL, pointer equality (in C, ==)
 *                          is used. If value, or any other value in the
 *                          dictionary, is not understood by the equal callback,
 *                          the behavior is undefined.
 * @result      The number of times the value occurs in theDict.
 */
CF_EXPORT CFIndex CFDictionaryGetCountOfValue( CFDictionaryRef theDict, const void * value );

/*!
 * @function    CFDictionaryGetKeysAndValues
 * @abstract    Fills two buffers with the keys and values from a dictionary.
 * @param       theDict     The dictionary to examine.
 * @param       keys        A C array of pointer-sized values that, on return,
 *                          is filled with keys from the theDict. The keys and
 *                          values C arrays are parallel to each other (that is,
 *                          the items at the same indices form a key-value pair
 *                          from the dictionary). This value must be a valid
 *                          pointer to a C array of the appropriate type and
 *                          size (that is, a size equal to the count of
 *                          theDict), or NULL if the keys are not required.
 *                          If the keys are Core Foundation objects, ownership
 *                          follows the Get Rule.
 * @param       values      A C array of pointer-sized values that, on return,
 *                          is filled with values from the theDict. The keys and
 *                          values C arrays are parallel to each other (that is,
 *                          the items at the same indices form a key-value pair
 *                          from the dictionary). This value must be a valid
 *                          pointer to a C array of the appropriate type and
 *                          size (that is, a size equal to the count of
 *                          theDict), or NULL if the values are not required.
 *                          If the values are Core Foundation objects, ownership
 *                          follows the Get Rule.
 */
CF_EXPORT void CFDictionaryGetKeysAndValues( CFDictionaryRef theDict, const void ** keys, const void ** values );

/*!
 * @function    CFDictionaryGetValue
 * @abstract    Returns the value associated with a given key.
 * @param       theDict     The dictionary to examine.
 * @param       key         The key for which to find a match in theDict.
 *                          The key hash and equal callbacks provided when the
 *                          dictionary was created are used to compare. If the
 *                          hash callback was NULL, the key is treated as a
 *                          pointer and converted to an integer. If the equal
 *                          callback was NULL, pointer equality (in C, ==) is
 *                          used. If key, or any of the keys in theDict, is not
 *                          understood by the equal callback, the behavior is
 *                          undefined.
 * @result      The value associated with key in theDict, or NULL if no
 *              key-value pair matching key exists. Since NULL is also a valid
 *              value in some dictionaries, use CFDictionaryGetValueIfPresent to
 *              distinguish between a value that is not found, and a NULL value.
 *              If the value is a Core Foundation object, ownership follows the
 *              Get Rule.
 */
CF_EXPORT const void * CFDictionaryGetValue( CFDictionaryRef theDict, const void * key );

/*!
 * @function    CFDictionaryGetValueIfPresent
 * @abstract    Returns a Boolean value that indicates whether a given value for
 *              a given key is in a dictionary, and returns that value
 *              indirectly if it exists.
 * @param       theDict     The dictionary to examine.
 * @param       key         The key for which to find a match in theDict.
 *                          The key hash and equal callbacks provided when the
 *                          dictionary was created are used to compare. If the
 *                          hash callback was NULL, key is treated as a pointer
 *                          and converted to an integer. If the equal callback
 *                          was NULL, pointer equality (in C, ==) is used.
 *                          If key, or any of the keys in theDict, is not
 *                          understood by the equal callback, the behavior is
 *                          undefined.
 * @param       value       A pointer to memory which, on return, is filled with
 *                          the pointer-sized value if a matching key is found.
 *                          If no key match is found, the contents of the
 *                          storage pointed to by this parameter are undefined.
 *                          This value may be NULL, in which case the value from
 *                          the dictionary is not returned (but the return value
 *                          of this function still indicates whether or not the
 *                          key-value pair was present). If the value is a Core
 *                          Foundation object, ownership follows the Get Rule.
 * @result      true if a matching key was found, otherwise false.
 */
CF_EXPORT Boolean CFDictionaryGetValueIfPresent( CFDictionaryRef theDict, const void * key, const void ** value );

/*!
 * @function    CFDictionaryApplyFunction
 * @abstract    Calls a function once for each key-value pair in a dictionary.
 * @param       theDict     The dictionary to operate upon.
 * @param       applier     The callback function to call once for each
 *                          key-value pair in theDict. If this parameter is not
 *                          a pointer to a function of the correct prototype,
 *                          the behavior is undefined. If there are keys or
 *                          values which the applier function does not expect or
 *                          cannot properly apply to, the behavior is undefined.
 * @param       context     A pointer-sized program-defined value, which is
 *                          passed as the third parameter to the applier
 *                          function, but is otherwise unused by this function.
 *                          The value must be appropriate for the applier
 *                          function.
 * @discussion  If this function iterates over a mutable collection, it is
 *              unsafe for the applier function to change the contents of the
 *              collection.
 */
CF_EXPORT void CFDictionaryApplyFunction( CFDictionaryRef theDict, CFDictionaryApplierFunction applier, void * context );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_DICTIONARY_H */
