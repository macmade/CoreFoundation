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

#include <CoreFoundation/__private/__CFAllocator.h>
#include <CoreFoundation/__private/__CFArray.h>
#include <CoreFoundation/__private/__CFAttributedString.h>
#include <CoreFoundation/__private/__CFBag.h>
#include <CoreFoundation/__private/__CFBinaryHeap.h>
#include <CoreFoundation/__private/__CFBitVector.h>
#include <CoreFoundation/__private/__CFBoolean.h>
#include <CoreFoundation/__private/__CFBundle.h>
#include <CoreFoundation/__private/__CFCalendar.h>
#include <CoreFoundation/__private/__CFCharacterSet.h>
#include <CoreFoundation/__private/__CFData.h>
#include <CoreFoundation/__private/__CFDate.h>
#include <CoreFoundation/__private/__CFDateFormatter.h>
#include <CoreFoundation/__private/__CFDictionary.h>
#include <CoreFoundation/__private/__CFError.h>
#include <CoreFoundation/__private/__CFFileDescriptor.h>
#include <CoreFoundation/__private/__CFLocale.h>
#include <CoreFoundation/__private/__CFMachPort.h>
#include <CoreFoundation/__private/__CFMessagePort.h>
#include <CoreFoundation/__private/__CFNotificationCenter.h>
#include <CoreFoundation/__private/__CFNull.h>
#include <CoreFoundation/__private/__CFNumber.h>
#include <CoreFoundation/__private/__CFNumberFormatter.h>
#include <CoreFoundation/__private/__CFPlugIn.h>
#include <CoreFoundation/__private/__CFPlugInInstance.h>
#include <CoreFoundation/__private/__CFPreferences.h>
#include <CoreFoundation/__private/__CFPropertyList.h>
#include <CoreFoundation/__private/__CFReadStream.h>
#include <CoreFoundation/__private/__CFRunLoop.h>
#include <CoreFoundation/__private/__CFRunLoopObserver.h>
#include <CoreFoundation/__private/__CFRunLoopSource.h>
#include <CoreFoundation/__private/__CFRunLoopTimer.h>
#include <CoreFoundation/__private/__CFSet.h>
#include <CoreFoundation/__private/__CFSocket.h>
#include <CoreFoundation/__private/__CFString.h>
#include <CoreFoundation/__private/__CFStringTokenizer.h>
#include <CoreFoundation/__private/__CFTimeZone.h>
#include <CoreFoundation/__private/__CFTree.h>
#include <CoreFoundation/__private/__CFURL.h>
#include <CoreFoundation/__private/__CFUserNotification.h>
#include <CoreFoundation/__private/__CFUUID.h>
#include <CoreFoundation/__private/__CFWriteStream.h>
#include <CoreFoundation/__private/__CFXMLNode.h>
#include <CoreFoundation/__private/__CFXMLParser.h>
#include <CoreFoundation/__private/__CFXMLTree.h>

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
