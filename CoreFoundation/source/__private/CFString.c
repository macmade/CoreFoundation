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
 * @file        CFString.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/CFString.h>

CFTypeID       CFStringTypeID = 0;
CFRuntimeClass CFStringClass  =
{
    "CFString",
    sizeof( struct CFString ),
    NULL,
    ( void ( * )( CFTypeRef ) )CFStringDestruct,
    NULL,
    NULL,
    ( CFStringRef ( * )( CFTypeRef ) )CFStringCopyDescription
};

void CFStringDestruct( CFStringRef str )
{
    if( str->_cStr )
    {
        CFAllocatorDeallocate( str->_deallocator, ( void * )( str->_cStr ) );
    }
    
    if( str->_deallocator )
    {
        CFRelease( str->_deallocator );
    }
}

CFStringRef CFStringCopyDescription( CFStringRef str )
{
    return CFStringCreateWithFormat
    (
        NULL,
        NULL,
        CFStringCreateWithCStringNoCopy( NULL, "%s", kCFStringEncodingUTF8, kCFAllocatorNull ),
        ( str->_cStr ) ? str->_cStr : "(null)"
    );
}
