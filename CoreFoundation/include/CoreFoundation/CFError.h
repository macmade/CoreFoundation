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
 *              for the error. The “user info” dictionary sometimes includes
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

CF_EXTERN_C_BEGIN



CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_ERROR_H */
