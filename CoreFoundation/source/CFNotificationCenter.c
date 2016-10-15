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
 * @file        CFNotificationCenter.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFNotificationCenter.h>
#include <stdlib.h>

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFNotificationCenterTypeID = CFRuntimeRegisterClass( &CFNotificationCenterClass );
}

CFTypeID CFNotificationCenterGetTypeID( void )
{
    return CFNotificationCenterTypeID;
}

CFNotificationCenterRef CFNotificationCenterGetDarwinNotifyCenter( void )
{
    return NULL;
}

CFNotificationCenterRef CFNotificationCenterGetDistributedCenter( void )
{
    return NULL;
}

CFNotificationCenterRef CFNotificationCenterGetLocalCenter( void )
{
    return NULL;
}

void CFNotificationCenterPostNotification( CFNotificationCenterRef center, CFNotificationName name, const void * object, CFDictionaryRef userInfo, Boolean deliverImmediately )
{
    ( void )center;
    ( void )name;
    ( void )object;
    ( void )userInfo;
    ( void )deliverImmediately;
}

void CFNotificationCenterPostNotificationWithOptions( CFNotificationCenterRef center, CFNotificationName name, const void * object, CFDictionaryRef userInfo, CFOptionFlags options )
{
    ( void )center;
    ( void )name;
    ( void )object;
    ( void )userInfo;
    ( void )options;
}

void CFNotificationCenterAddObserver( CFNotificationCenterRef center, const void * observer, CFNotificationCallback callBack, CFStringRef name, const void * object, CFNotificationSuspensionBehavior suspensionBehavior )
{
    ( void )center;
    ( void )observer;
    ( void )callBack;
    ( void )name;
    ( void )object;
    ( void )suspensionBehavior;
}

void CFNotificationCenterRemoveEveryObserver( CFNotificationCenterRef center, const void * observer )
{
    ( void )center;
    ( void )observer;
}

void CFNotificationCenterRemoveObserver( CFNotificationCenterRef center, const void * observer, CFNotificationName name, const void * object )
{
    ( void )center;
    ( void )observer;
    ( void )name;
    ( void )object;
}
