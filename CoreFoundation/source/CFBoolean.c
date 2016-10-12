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
 * @file        CFBoolean.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>

struct CFBoolean
{
    CFRuntimeBase _base;
};

static CFStringRef CFBooleanCopyDescription( CFBooleanRef boolean );

static CFTypeID CFBooleanTypeID      = 0;
static CFRuntimeClass CFBooleanClass =
{
    "CFBoolean",
    sizeof( struct CFBoolean ),
    NULL,
    NULL,
    NULL,
    NULL,
    ( CFStringRef ( * )( CFTypeRef ) )CFBooleanCopyDescription
};

static struct CFBoolean CFBooleanTrue;
static struct CFBoolean CFBooleanFalse;

const CFBooleanRef kCFBooleanTrue  = ( const CFBooleanRef )( &CFBooleanTrue );
const CFBooleanRef kCFBooleanFalse = ( const CFBooleanRef )( &CFBooleanFalse );

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFBooleanTypeID = CFRuntimeRegisterClass( &CFBooleanClass );
    
    CFRuntimeInitStaticInstance( &CFBooleanTrue, CFBooleanTypeID );
    CFRuntimeInitStaticInstance( &CFBooleanFalse, CFBooleanTypeID );
}

static CFStringRef CFBooleanCopyDescription( CFBooleanRef boolean )
{
    if( boolean == kCFBooleanTrue )
    {
        return CFStringCreateWithCStringNoCopy( NULL, "true", kCFStringEncodingUTF8, kCFAllocatorNull );
    }
    
    return CFStringCreateWithCStringNoCopy( NULL, "false", kCFStringEncodingUTF8, kCFAllocatorNull );
}

CFTypeID CFBooleanGetTypeID( void )
{
    return CFBooleanTypeID;
}

Boolean CFBooleanGetValue( CFBooleanRef boolean )
{
    return ( boolean == kCFBooleanTrue ) ? true : false;
}
