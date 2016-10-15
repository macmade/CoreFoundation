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
 * @header      CFSocket.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_SOCKET_H
#define CORE_FOUNDATION___PRIVATE_CF_SOCKET_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/__CFRuntime.h>

CF_EXTERN_C_BEGIN

struct CFSocket
{
    CFRuntimeBase _base;
};

CF_EXPORT void CFSocketInitialize( void );

CF_EXPORT CFTypeID       CFSocketTypeID;
CF_EXPORT CFRuntimeClass CFSocketClass;

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_SOCKET_H */
