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
 * @header      CFNotificationCenter.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_NOTIFICATION_CENTER_H
#define CORE_FOUNDATION___PRIVATE_CF_NOTIFICATION_CENTER_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>
#include <CoreFoundation/__private/CFSpinLock.h>

CF_EXTERN_C_BEGIN

struct CFNotificationCenter
{
    CFRuntimeBase _base;
};

CF_EXPORT void CFNotificationCenterInitialize( void );

CF_EXPORT CFTypeID       CFNotificationCenterTypeID;
CF_EXPORT CFRuntimeClass CFNotificationCenterClass;

CF_EXPORT CFSpinLock CFNotificationCenterLocalLock;
CF_EXPORT CFSpinLock CFNotificationCenterDarwinLock;
CF_EXPORT CFSpinLock CFNotificationCenterDistributedLock;

CF_EXPORT CFNotificationCenterRef CFNotificationCenterLocal;
CF_EXPORT CFNotificationCenterRef CFNotificationCenterDarwin;
CF_EXPORT CFNotificationCenterRef CFNotificationCenterDistributed;

CF_EXPORT CFNotificationCenterRef CFNotificationCenterCreate( CFAllocatorRef alloc );
CF_EXPORT CFStringRef             CFNotificationCenterCopyDescription( CFNotificationCenterRef center );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_NOTIFICATION_CENTER_H */
