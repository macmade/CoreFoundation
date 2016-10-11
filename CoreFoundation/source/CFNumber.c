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
 * @file        CFNumber.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>
#include <stdlib.h>

struct CFNumber
{
    CFRuntimeBase _base;
};

static CFTypeID CFNumberTypeID      = 0;
static CFRuntimeClass CFNumberClass =
{
    "CFNumber",
    sizeof( struct CFNumber ),
    NULL,
    NULL
};

static struct CFNumber CFNumberNaN;
static struct CFNumber CFNumberNegativeInfinity;
static struct CFNumber CFNumberPositiveInfinity;

const CFNumberRef kCFNumberNaN              = ( const CFNumberRef )( &CFNumberNaN );
const CFNumberRef kCFNumberNegativeInfinity = ( const CFNumberRef )( &CFNumberNegativeInfinity );
const CFNumberRef kCFNumberPositiveInfinity = ( const CFNumberRef )( &CFNumberPositiveInfinity );

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFNumberTypeID = CFRuntimeRegisterClass( &CFNumberClass );
    
    CFRuntimeInitStaticInstance( &CFNumberNaN,              CFNumberTypeID );
    CFRuntimeInitStaticInstance( &CFNumberNegativeInfinity, CFNumberTypeID );
    CFRuntimeInitStaticInstance( &CFNumberPositiveInfinity, CFNumberTypeID );
}

CFTypeID CFNumberGetTypeID( void )
{
    return 0;
}

CFNumberRef CFNumberCreate( CFAllocatorRef allocator, CFNumberType type, const void * valuePtr )
{
    ( void )allocator;
    ( void )type;
    ( void )valuePtr;
    
    return NULL;
}

CFIndex CFNumberGetByteSize( CFNumberRef number )
{
    ( void )number;
    
    return 0;
}

CFNumberType CFNumberGetType( CFNumberRef number )
{
    ( void )number;
    
    return kCFNumberSInt8Type;
}

Boolean CFNumberGetValue( CFNumberRef number, CFNumberType type, void * valuePtr )
{
    ( void )number;
    ( void )type;
    ( void )valuePtr;
    
    return false;
}

Boolean CFNumberIsFloatType( CFNumberRef number )
{
    ( void )number;
    
    return false;
}

CFComparisonResult CFNumberCompare( CFNumberRef number, CFNumberRef otherNumber, void * context )
{
    ( void )number;
    ( void )otherNumber;
    ( void )context;
    
    return kCFCompareEqualTo;
}
