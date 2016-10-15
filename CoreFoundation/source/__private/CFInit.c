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
 * @file        CFFileDescriptor.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/CFAllocator.h>
#include <CoreFoundation/__private/CFArray.h>
#include <CoreFoundation/__private/CFAttributedString.h>
#include <CoreFoundation/__private/CFBag.h>
#include <CoreFoundation/__private/CFBinaryHeap.h>
#include <CoreFoundation/__private/CFBitVector.h>
#include <CoreFoundation/__private/CFBoolean.h>
#include <CoreFoundation/__private/CFBundle.h>
#include <CoreFoundation/__private/CFCalendar.h>
#include <CoreFoundation/__private/CFCharacterSet.h>
#include <CoreFoundation/__private/CFData.h>
#include <CoreFoundation/__private/CFDate.h>
#include <CoreFoundation/__private/CFDateFormatter.h>
#include <CoreFoundation/__private/CFDictionary.h>
#include <CoreFoundation/__private/CFError.h>
#include <CoreFoundation/__private/CFFileDescriptor.h>
#include <CoreFoundation/__private/CFLocale.h>
#include <CoreFoundation/__private/CFMachPort.h>
#include <CoreFoundation/__private/CFMessagePort.h>
#include <CoreFoundation/__private/CFNotificationCenter.h>
#include <CoreFoundation/__private/CFNull.h>
#include <CoreFoundation/__private/CFNumber.h>
#include <CoreFoundation/__private/CFNumberFormatter.h>
#include <CoreFoundation/__private/CFPlugIn.h>
#include <CoreFoundation/__private/CFPlugInInstance.h>
#include <CoreFoundation/__private/CFPreferences.h>
#include <CoreFoundation/__private/CFPropertyList.h>
#include <CoreFoundation/__private/CFReadStream.h>
#include <CoreFoundation/__private/CFRunLoop.h>
#include <CoreFoundation/__private/CFRunLoopObserver.h>
#include <CoreFoundation/__private/CFRunLoopSource.h>
#include <CoreFoundation/__private/CFRunLoopTimer.h>
#include <CoreFoundation/__private/CFSet.h>
#include <CoreFoundation/__private/CFSocket.h>
#include <CoreFoundation/__private/CFString.h>
#include <CoreFoundation/__private/CFStringTokenizer.h>
#include <CoreFoundation/__private/CFTimeZone.h>
#include <CoreFoundation/__private/CFTree.h>
#include <CoreFoundation/__private/CFURL.h>
#include <CoreFoundation/__private/CFUserNotification.h>
#include <CoreFoundation/__private/CFUUID.h>
#include <CoreFoundation/__private/CFWriteStream.h>
#include <CoreFoundation/__private/CFXMLNode.h>
#include <CoreFoundation/__private/CFXMLParser.h>
#include <CoreFoundation/__private/CFXMLTree.h>

#ifdef _WIN32

#pragma section( ".CRT$XCU", read )
    
static void __cdecl init( void );								
__declspec( allocate( ".CRT$XCU" ) ) void ( __cdecl * init_ )( void ) = init;
static void __cdecl init( void )

#else

static void init( void ) __attribute__( ( constructor ) );
static void init( void )

#endif

{
    CFAllocatorInitialize();
    CFArrayInitialize();
    CFAttributedStringInitialize();
    CFBagInitialize();
    CFBinaryHeapInitialize();
    CFBitVectorInitialize();
    CFBooleanInitialize();
    CFBundleInitialize();
    CFCalendarInitialize();
    CFCharacterSetInitialize();
    CFDataInitialize();
    CFDateInitialize();
    CFDateFormatterInitialize();
    CFDictionaryInitialize();
    CFErrorInitialize();
    CFFileDescriptorInitialize();
    CFLocaleInitialize();
    CFMachPortInitialize();
    CFMessagePortInitialize();
    CFNotificationCenterInitialize();
    CFNullInitialize();
    CFNumberInitialize();
    CFNumberFormatterInitialize();
    CFPlugInInitialize();
    CFPlugInInstanceInitialize();
    CFPreferencesInitialize();
    CFPropertyListInitialize();
    CFReadStreamInitialize();
    CFRunLoopInitialize();
    CFRunLoopObserverInitialize();
    CFRunLoopSourceInitialize();
    CFRunLoopTimerInitialize();
    CFSetInitialize();
    CFSocketInitialize();
    CFStringInitialize();
    CFStringTokenizerInitialize();
    CFTimeZoneInitialize();
    CFTreeInitialize();
    CFURLInitialize();
    CFUserNotificationInitialize();
    CFUUIDInitialize();
    CFWriteStreamInitialize();
    CFXMLNodeInitialize();
    CFXMLParserInitialize();
    CFXMLTreeInitialize();
}
