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
 * @file        Foo.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include "Foo.h"
#include <CoreFoundation/__private/__CFRuntime.h>

struct Foo
{
    CFRuntimeBase _base;
    CFStringRef   _str;
};

static CFTypeID FooTypeID = 0;

static void FooDestruct( FooRef foo );

CFRuntimeClass FooClass  =
{
    "Foo",
    sizeof( struct Foo ),
    NULL,
    ( void ( * )( CFTypeRef ) )FooDestruct,
    NULL,
    NULL,
    NULL
};

#ifdef _WIN32

#pragma section( ".CRT$XCU", read )

static void __cdecl init( void );
__declspec( allocate( ".CRT$XCU" ) ) void( __cdecl * init_ )( void ) = init;
static void __cdecl init( void )

#else

static void init( void ) __attribute__( ( constructor ) );
static void init( void )

#endif

{
    FooTypeID = CFRuntimeRegisterClass( &FooClass );
}

static void FooDestruct( FooRef foo )
{
    CFRelease( foo->_str );
}

CFTypeID FooGetTypeID( void )
{
    return FooTypeID;
}

FooRef FooCreate( CFAllocatorRef alloc, CFStringRef str )
{
    struct Foo * foo;
    
    foo = ( struct Foo * )CFRuntimeCreateInstance( alloc, FooTypeID );
    
    if( foo )
    {
        foo->_str = CFRetain( str );
    }
    
    return foo;
}

CFStringRef FooGetString( FooRef foo )
{
    return ( foo ) ? foo->_str : NULL;
}
