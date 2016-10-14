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
 * @header      CFMutableDictionary.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  CFMutableDictionary manages dynamic dictionaries. The basic
 *              interface for managing dictionaries is provided by CFDictionary.
 *              CFMutableDictionary adds functions to modify the contents of a
 *              dictionary.
 *              You create a mutable dictionary object using either the
 *              CFDictionaryCreateMutable or CFDictionaryCreateMutableCopy
 *              function. You can add key-value pairs using the
 *              CFDictionaryAddValue and CFDictionarySetValue functions.
 *              When adding key-value pairs to a dictionary, the keys and values
 *              are not copied—they are retained so they are not invalidated
 *              before the dictionary is deallocated. You can remove key-value
 *              pairs using the CFDictionaryRemoveValue function. When removing
 *              key-value pairs from a dictionary, the keys and values are
 *              released.
 *              CFMutableDictionary is "toll-free bridged" with its Cocoa
 *              Foundation counterpart, NSMutableDictionary. What this means is
 *              that the Core Foundation type is interchangeable in function or
 *              method calls with the bridged Foundation object. This means that
 *              in a method where you see an NSMutableDictionary * parameter,
 *              you can pass in a CFMutableDictionaryRef, and in a function
 *              where you see a CFMutableDictionaryRef parameter, you can pass
 *              in an NSMutableDictionary instance. This also applies to
 *              concrete subclasses of NSMutableDictionary. See Toll-Free
 *              Bridged Types for more information on toll-free bridging.
 */

#ifndef CORE_FOUNDATION_CF_MUTABLE_DICTIONARY_H
#define CORE_FOUNDATION_CF_MUTABLE_DICTIONARY_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFDictionary.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFMutableDictionaryRef
 * @abstract    A reference to a mutable dictionary object.
 */
typedef struct CFDictionary * CFMutableDictionaryRef;

/*!
 * @function    CFDictionaryCreateMutable
 * @abstract    Creates a new mutable dictionary.
 * @param       allocator       The allocator to use to allocate memory for the
 *                              new dictionary and its storage for key-value
 *                              pairs. Pass NULL or kCFAllocatorDefault to use
 *                              the current default allocator.
 * @param       capacity        The maximum number of key-value pairs that can
 *                              be contained by the new dictionary. The
 *                              dictionary starts empty and can grow to this
 *                              number of key-value pairs (and it can have
 *                              less).
 *                              Pass 0 to specify that the maximum capacity is
 *                              not limited. The value must not be negative.
 * @param       keyCallBacks    A pointer to a CFDictionaryKeyCallBacks
 *                              structure initialized with the callbacks to use
 *                              to retain, release, describe, and compare keys
 *                              in the dictionary. A copy of the contents of the
 *                              callbacks structure is made, so that a pointer
 *                              to a structure on the stack can be passed in or
 *                              can be reused for multiple collection creations.
 *                              This value may be NULL, which is treated as a
 *                              valid structure of version 0 with all fields
 *                              NULL. Otherwise, if any of the fields are not
 *                              valid pointers to functions of the correct type,
 *                              or this value is not a valid pointer to a
 *                              CFDictionaryKeyCallBacks structure, the behavior
 *                              is undefined. If any of the keys put into the
 *                              collection is not one understood by one of the
 *                              callback functions, the behavior when that
 *                              callback function is used is undefined.
 *                              If the dictionary will contain only CFType
 *                              objects, then pass a pointer to
 *                              kCFTypeDictionaryKeyCallBacks as this parameter
 *                              to use the default callback functions.
 * @param       valueCallBacks  A pointer to a CFDictionaryValueCallBacks
 *                              structure initialized with the callbacks to use
 *                              to retain, release, describe, and compare values
 *                              in the dictionary. A copy of the contents of the
 *                              callbacks structure is made, so that a pointer
 *                              to a structure on the stack can be passed in or
 *                              can be reused for multiple collection creations.
 *                              This value may be NULL, which is treated as a
 *                              valid structure of version 0 with all fields
 *                              NULL. Otherwise, if any of the fields are not
 *                              valid pointers to functions of the correct type,
 *                              or this value is not a valid pointer to a
 *                              CFDictionaryValueCallBacks structure, the
 *                              behavior is undefined. If any value put into
 *                              the collection is not one understood by one of
 *                              the callback functions, the behavior when that
 *                              callback function is used is undefined.
 *                              If the dictionary will contain CFType objects
 *                              only, then pass a pointer to
 *                              kCFTypeDictionaryValueCallBacks as this
 *                              parameter to use the default callback functions.
 * @result      A new dictionary, or NULL if there was a problem creating the
 *              object. Ownership follows the Create Rule.
 */
CF_EXPORT CFMutableDictionaryRef CFDictionaryCreateMutable( CFAllocatorRef allocator, CFIndex capacity, const CFDictionaryKeyCallBacks * keyCallBacks, const CFDictionaryValueCallBacks * valueCallBacks );

/*!
 * @function    CFDictionaryCreateMutableCopy
 * @abstract    Creates a new mutable dictionary with the key-value pairs from
 *              another dictionary.
 * @param       allocator   The allocator to use to allocate memory for the new
 *                          dictionary and its storage for key-value pairs. Pass
 *                          NULL or kCFAllocatorDefault to use the current
 *                          default allocator.
 * @param       capacity    The maximum number of key-value pairs that can be
 *                          contained by the new dictionary. The dictionary
 *                          starts with the same number of key-value pairs as
 *                          theDict and can grow to this number of values
 *                          (and it can have less).
 *                          Pass 0 to specify that the maximum capacity is not
 *                          limited. If non-0, capacity must be greater than or
 *                          equal to the count of theDict.
 * @param       theDict     The dictionary to copy. The keys and values from the
 *                          dictionary are copied as pointers into the new
 *                          dictionary, not that which the values point to
 *                          (if anything). The keys and values are also retained
 *                          by the new dictionary. The count of the new
 *                          dictionary is the same as the count of theDict.
 *                          The new dictionary uses the same callbacks as
 *                          theDict.
 * @result      A new dictionary that contains the same values as theDict.
                Ownership follows the Create Rule.
 */
CF_EXPORT CFMutableDictionaryRef CFDictionaryCreateMutableCopy( CFAllocatorRef allocator, CFIndex capacity, CFDictionaryRef theDict );

/*!
 * @function    CFDictionaryAddValue
 * @abstract    Adds a key-value pair to a dictionary if the specified key is
 *              not already present.
 * @param       theDict     The dictionary to modify. If the dictionary is a
 *                          fixed-capacity dictionary and it is full before this
 *                          operation, the behavior is undefined.
 * @param       key         The key for the value to add to the dictionary—a
 *                          CFType object or a pointer value. The key is
 *                          retained by the dictionary using the retain
 *                          callback provided when the dictionary was created,
 *                          so must be of the type expected by the callback.
 *                          If a key which matches key is already present in
 *                          the dictionary, this function does nothing
 *                          ("add if absent").
 * @param       value       A CFType object or a pointer value to add to the
 *                          dictionary. The value is retained by the dictionary
 *                          using the retain callback provided when the
 *                          dictionary was created, so must be of the type
 *                          expected by the callback.
 */
CF_EXPORT void CFDictionaryAddValue( CFMutableDictionaryRef theDict, const void * key, const void * value );

/*!
 * @function    CFDictionaryRemoveAllValues
 * @abstract    Removes all the key-value pairs from a dictionary, making it
 *              empty.
 * @param       theDict     The dictionary to modify.
 */
CF_EXPORT void CFDictionaryRemoveAllValues( CFMutableDictionaryRef theDict );

/*!
 * @function    CFDictionaryRemoveValue
 * @abstract    Removes a key-value pair.
 * @param       theDict     The dictionary to modify.
 * @param       key         The key of the value to remove from theDict. If a
 *                          key which matches key is present in theDict,
 *                          the key-value pair is removed from the dictionary,
 *                          otherwise this function does nothing
 *                          ("remove if present").
 */
CF_EXPORT void CFDictionaryRemoveValue( CFMutableDictionaryRef theDict, const void * key );

/*!
 * @function    CFDictionaryReplaceValue
 * @abstract    Replaces a value corresponding to a given key.
 * @param       theDict     The dictionary to modify.
 * @param       key         The key of the value to replace in theDict. If a key
 *                          which matches key is present in the dictionary, the
 *                          value is changed to the value, otherwise this
 *                          function does nothing ("replace if present").
 * @param       value       The new value for key. The value object is retained
 *                          by theDict using the retain callback provided when
 *                          theDict was created, and the old value is released.
 *                          value must be of the type expected by the retain and
 *                          release callbacks.
 */
CF_EXPORT void CFDictionaryReplaceValue( CFMutableDictionaryRef theDict, const void * key, const void * value );

/*!
 * @function    CFDictionarySetValue
 * @abstract    Sets the value corresponding to a given key.
 * @param       theDict     The dictionary to modify. If this parameter is a
 *                          fixed-capacity dictionary and it is full before this
 *                          operation, and the key does not exist in the
 *                          dictionary, the behavior is undefined.
 * @param       key         The key of the value to set in theDict. If a key
 *                          which matches key is already present in the
 *                          dictionary, only the value for the key is changed
 *                          ("add if absent, replace if present"). If no key
 *                          matches key, the key-value pair is added to the
 *                          dictionary.
 *                          If a key-value pair is added, both key and value are
 *                          retained by the dictionary, using the retain
 *                          callback provided when theDict was created. key must
 *                          be of the type expected by the key retain callback.
 * @param       value       The value to add to or replace in theDict. value is
 *                          retained using the value retain callback provided
 *                          when theDict was created, and the previous value if
 *                          any is released. value must be of the type expected
 *                          by the retain and release callbacks.
 */
CF_EXPORT void CFDictionarySetValue( CFMutableDictionaryRef theDict, const void * key, const void * value );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_MUTABLE_DICTIONARY_H */
