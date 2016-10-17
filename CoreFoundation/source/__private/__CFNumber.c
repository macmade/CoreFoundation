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

#include <CoreFoundation/__private/__CFNumber.h>

CFTypeID        CFNumberTypeID = 0;
CFRuntimeClass CFNumberClass   =
{
    "CFNumber",
    sizeof( struct CFNumber ),
    NULL,
    NULL,
    ( CFHashCode ( * )( CFTypeRef ) )CFNumberHash,
    ( bool ( * )( CFTypeRef, CFTypeRef ) )CFNumberEquals,
    ( CFStringRef ( * )( CFTypeRef ) )CFNumberCopyDescription
};

struct CFNumber CFNumberNaN;
struct CFNumber CFNumberNegativeInfinity;
struct CFNumber CFNumberPositiveInfinity;

const CFNumberRef kCFNumberNaN              = ( const CFNumberRef )( &CFNumberNaN );
const CFNumberRef kCFNumberNegativeInfinity = ( const CFNumberRef )( &CFNumberNegativeInfinity );
const CFNumberRef kCFNumberPositiveInfinity = ( const CFNumberRef )( &CFNumberPositiveInfinity );

void CFNumberInitialize( void )
{
    CFNumberTypeID = CFRuntimeRegisterClass( &CFNumberClass );
    
    CFRuntimeInitStaticInstance( &CFNumberNaN,              CFNumberTypeID );
    CFRuntimeInitStaticInstance( &CFNumberNegativeInfinity, CFNumberTypeID );
    CFRuntimeInitStaticInstance( &CFNumberPositiveInfinity, CFNumberTypeID );
}

CFHashCode CFNumberHash( CFNumberRef n )
{
    ( void )n;
    
    return 0;
}

bool CFNumberEquals( CFNumberRef n1, CFNumberRef n2 )
{
    ( void )n1;
    ( void )n2;
    
    return false;
}

CFStringRef CFNumberCopyDescription( CFNumberRef n )
{
    ( void )n;
    
    return NULL;
}
