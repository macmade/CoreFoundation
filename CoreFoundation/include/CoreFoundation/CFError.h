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
 * @header      CFError.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  A CFError object encapsulates more rich and extensible error
 *              information than is possible using only an error code or error
 *              string. The core attributes of a CFError object are an error
 *              domain (represented by a string), a domain-specific error code,
 *              and a "user info" dictionary containing application-specific
 *              information. Errors are required to have a domain and an error
 *              code within that domain. Several well-known domains are defined
 *              corresponding to Mach, POSIX, and OSStatus errors.
 *              The optional "user info" dictionary may provide additional
 *              information that might be useful for the interpretation and
 *              reporting of the error, including a human-readable description
 *              for the error. The "user info" dictionary sometimes includes
 *              another CFError object that represents an error in a subsystem
 *              underlying the error represented by the containing CFError
 *              object. This underlying error object may provide more specific
 *              information about the cause of the error.
 *              In general, a method should signal an error condition by
 *              returning, for example, false or NULL rather than by the simple
 *              presence of an error object. The method can then optionally
 *              return an CFError object by reference, in order to further
 *              describe the error.
 *              CFError is toll-free bridged to NSError in the Foundation
 *              framework.
 */

#ifndef CORE_FOUNDATION_CF_ERROR_H
#define CORE_FOUNDATION_CF_ERROR_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFString.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFErrorRef
 * @abstract    A reference to a CFError object.
 */
typedef const struct CFError * CFErrorRef;

/*!
 * @typedef     CFErrorDomain
 */
typedef CFStringRef CFErrorDomain;

/*!
 * @function    CFErrorGetTypeID
 * @abstract    Returns the type identifier for the CFError opaque type.
 * @result      The type identifier for the CFError opaque type.
 */
CF_EXPORT CFTypeID CFErrorGetTypeID( void );

/*!
 * @function    CFErrorCreate
 * @abstract    Creates a new CFError object.
 * @param       allocator   The allocator to use to allocate memory for the new
 *                          object. Pass NULL or kCFAllocatorDefault to use the
 *                          current default allocator.
 * @param       domain      A CFString that identifies the error domain. If this
 *                          reference is NULL or is otherwise not a valid
 *                          CFString, the behavior is undefined.
 * @param       code        A CFIndex that identifies the error code. The code
 *                          is interpreted within the context of the error
 *                          domain.
 * @param       userInfo    A CFDictionary created with
 *                          kCFCopyStringDictionaryKeyCallBacks and
 *                          kCFTypeDictionaryValueCallBacks. The dictionary is
 *                          copied with CFDictionaryCreateCopy. If you do not
 *                          want the userInfo dictionary, you can pass NULL,
 *                          in which case an empty dictionary will be assigned.
 * @result      A new CFError object. Ownership follows the The Create Rule.
 */
CF_EXPORT CFErrorRef CFErrorCreate( CFAllocatorRef allocator, CFErrorDomain domain, CFIndex code, CFDictionaryRef userInfo );

/*!
 * @function    CFErrorCreateWithUserInfoKeysAndValues
 * @abstract    Creates a new CFError object using given keys and values to
 *              create the user info dictionary.
 * @param       allocator           The allocator to use to allocate memory for
 *                                  the new object. Pass NULL or
 *                                  kCFAllocatorDefault to use the current
 *                                  default allocator.
 * @param       domain              A CFString that identifies the error domain.
 *                                  If this reference is NULL or is otherwise
 *                                  not a valid CFString, the behavior is
 *                                  undefined.
 * @param       code                A CFIndex that identifies the error code.
 *                                  The code is interpreted within the context
 *                                  of the error domain.
 * @param       userInfoKeys        An array of numUserInfoValues CFStrings used
 *                                  as keys in creating the userInfo dictionary.
 *                                  The value of this parameter can be NULL if
 *                                  numUserInfoValues is 0.
 * @param       userInfoValues      An array of numUserInfoValues CF types used
 *                                  as values in creating the userInfo
 *                                  dictionary. The value of this parameter can
 *                                  be NULL if numUserInfoValues is 0.
 * @param       numUserInfoValues   The number of keys and values in the
 *                                  userInfoKeys and userInfoValues arrays.
 * @result      A new CFError object. Ownership follows the The Create Rule.
 */
CF_EXPORT CFErrorRef CFErrorCreateWithUserInfoKeysAndValues( CFAllocatorRef allocator, CFErrorDomain domain, CFIndex code, const void * const * userInfoKeys, const void * const * userInfoValues, CFIndex numUserInfoValues );

/*!
 * @function    CFErrorGetDomain
 * @abstract    Returns the error domain for a given CFError.
 * @param       err     The error to examine. If this is not a valid CFError,
 *                      the behavior is undefined.
 * @result      The error domain for err. Ownership follows the The Get Rule.
 */
CF_EXPORT CFErrorDomain CFErrorGetDomain( CFErrorRef err );

/*!
 * @function    CFErrorGetCode
 * @abstract    Returns the error code for a given CFError.
 * @param       err     The error to examine. If this is not a valid CFError,
 *                      the behavior is undefined.
 * @result      The error code of err.
 * @discussion  Note that this function returns the error code for the specified
 *              CFError, not an error return for the current call.
 */
CF_EXPORT CFIndex CFErrorGetCode( CFErrorRef err );

/*!
 * @function    CFErrorCopyUserInfo
 * @abstract    Returns the user info dictionary for a given CFError.
 * @param       err     The error to examine. If this is not a valid CFError,
 *                      the behavior is undefined.
 * @result      A dictionary containing the same keys and values as in the
 *              userInfo dictionary err was created with. Returns an empty
 *              dictionary if NULL was supplied to the create function.
 *              Ownership follows the Create Rule.
 */
CF_EXPORT CFDictionaryRef CFErrorCopyUserInfo( CFErrorRef err );

/*!
 * @function    CFErrorCopyDescription
 * @abstract    Returns a human-presentable description for a given error.
 * @param       err     The CFError to examine. If this is not a valid CFError,
 *                      the behavior is undefined.
 * @result      A localized, human-presentable description of err. This function
 *              never returns NULL. Ownership follows the Create Rule.
 * @discussion  This is a complete sentence or two which says what failed and
 *              why it failed. The structure of the description depends on the
 *              details provided in the user info dictionary. The rules for
 *              computing the return value are as follows:
 *              -   If the value in the user info dictionary for
 *                  kCFErrorLocalizedDescriptionKey is not NULL, returns that
 *                  value as-is.
 *              -   If the value in the user info dictionary for
 *                  kCFErrorLocalizedFailureReasonKey is not NULL, generate an
 *                  error from that.
 *                  The description is something like: "Operation could not be
 *                  completed. " + kCFErrorLocalizedFailureReasonKey
 *              -   Generate as good a user-presentable string as possible from
 *                  kCFErrorDescriptionKey, the domain, and code.
 *                  The description is something like like: "Operation could not
 *                  be completed. Error domain/code occurred. " or "Operation
 *                  could not be completed. " + kCFErrorDescriptionKey +
 *                  " (Error domain/code)"
 *              Toll-free bridged instances of NSError might provide additional
 *              behaviors for manufacturing a description string.
 *              You should not depend on the exact contents or format of the
 *              returned string, as it might change in different releases of the
 *              operating system.
 *              When you create a CFError, you should try to make sure the
 *              return value is human-presentable and localized by providing
 *              a value for kCFErrorLocalizedDescriptionKey in the user info
 *              dictionary.
 */
CF_EXPORT CFStringRef CFErrorCopyDescription( CFErrorRef err );

/*!
 * @function    CFErrorCopyFailureReason
 * @abstract    Returns a human-presentable failure reason for a given error.
 * @param       err     The CFError to examine. If this is not a valid CFError,
 *                      the behavior is undefined.
 * @result      A localized, human-presentable failure reason for err, or NULL
 *              if no user-presentable string is available. Ownership follows
 *              the Create Rule.
 * @discussion  The failure reason is a complete sentence which describes why
 *              the operation failed. In many cases this will be just the
 *              "because" part of the description (but as a complete sentence,
 *              which makes localization easier). For example, an error
 *              description "Could not save file 'Letter' in folder 'Documents'
 *              because the volume 'MyDisk' doesn't have enough space." might
 *              have a corresponding failure reason, "The volume 'MyDisk'
 *              doesn't have enough space."
 *              By default, this function looks for a value for the
 *              kCFErrorLocalizedFailureReasonKey key in the user info
 *              dictionary. Toll-free bridged instances of NSError might provide
 *              additional behaviors for manufacturing this value.
 *              When you create a CFError, you should try to make sure the
 *              return value is human-presentable and localized by providing a
 *              value for kCFErrorLocalizedFailureReasonKey in the user info
 *              dictionary.
 */
CF_EXPORT CFStringRef CFErrorCopyFailureReason( CFErrorRef err );

/*!
 * @function    CFErrorCopyRecoverySuggestion
 * @abstract    Returns a human presentable recovery suggestion for a given
 *              error.
 * @param       err    The CFError to examine. If this is not a valid CFError,
 *                      the behavior is undefined.
 * @result      A localized, human-presentable recovery suggestion for err, or
 *              NULL if no user-presentable string is available. Ownership
 *              follows the Create Rule.
 * @discussion  This is the string that can be displayed as the "informative"
 *              (or "secondary") message on an alert panel. For example, an
 *              error description "Could not save file 'Letter' in folder
 *              'Documents' because the volume 'MyDisk' doesn't have enough
 *              space." might have a corresponding recovery suggestion,
 *              "Remove some files from the volume and try again."
 *              By default, this function looks for a value for the
 *              kCFErrorLocalizedRecoverySuggestionKey key in the user info
 *              dictionary. Toll-free bridged instances of NSError might
 *              provide additional behaviors for manufacturing this value.
 *              When you create a CFError, you should try to make sure the
 *              return value is human-presentable and localized by providing a
 *              value for kCFErrorLocalizedRecoverySuggestionKey in the user
 *              info dictionary.
 */
CF_EXPORT CFStringRef CFErrorCopyRecoverySuggestion( CFErrorRef err );

/*!
 * @constant    kCFErrorDomainPOSIX
 * @abstract    A constant that specified the POSIX domain.
 */
CF_EXPORT const CFErrorDomain kCFErrorDomainPOSIX;

/*!
 * @constant    kCFErrorDomainOSStatus
 * @abstract    A constant that specified the OS domain.
 */
CF_EXPORT const CFErrorDomain kCFErrorDomainOSStatus;

/*!
 * @constant    kCFErrorDomainMach
 * @abstract    A constant that specified the Mach domain.
 */
CF_EXPORT const CFErrorDomain kCFErrorDomainMach;

/*!
 * @constant    kCFErrorDomainCocoa
 * @abstract    A constant that specified the Cocoa domain.
 */
CF_EXPORT const CFErrorDomain kCFErrorDomainCocoa;

/*!
 * @constant    kCFErrorLocalizedDescriptionKey
 * @abstract    Key to identify the end user-presentable description in the
 *              userInfo dictionary.
 */
CF_EXPORT const CFStringRef kCFErrorLocalizedDescriptionKey;

/*!
 * @constant    kCFErrorLocalizedFailureReasonKey
 * @abstract    Key to identify the end user-presentable failure reason in the
 *              userInfo dictionary.
 */
CF_EXPORT const CFStringRef kCFErrorLocalizedFailureReasonKey;

/*!
 * @constant    kCFErrorLocalizedRecoverySuggestionKey
 * @abstract    Key to identify the end user-presentable recovery suggestion in
 *              the userInfo dictionary.
 */
CF_EXPORT const CFStringRef kCFErrorLocalizedRecoverySuggestionKey;

/*!
 * @constant    kCFErrorDescriptionKey
 * @abstract    Key to identify the description in the userInfo dictionary.
 */
CF_EXPORT const CFStringRef kCFErrorDescriptionKey;

/*!
 * @constant    kCFErrorUnderlyingErrorKey
 * @abstract    Key to identify the underlying error in the userInfo dictionary.
 */
CF_EXPORT const CFStringRef kCFErrorUnderlyingErrorKey;

/*!
 * @constant    kCFErrorURLKey
 * @abstract    Key to identify associated URL in the userInfo dictionary.
 */
CF_EXPORT const CFStringRef kCFErrorURLKey;

/*!
 * @constant    kCFErrorFilePathKey
 * @abstract    Key to identify associated file path in the userInfo dictionary.
 */
CF_EXPORT const CFStringRef kCFErrorFilePathKey;

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_ERROR_H */
