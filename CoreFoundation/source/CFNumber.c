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
#include <CoreFoundation/__private/__CFNumber.h>
#include <CoreFoundation/__private/__CFRuntime.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

CFTypeID CFNumberGetTypeID( void )
{
    return CFNumberTypeID;
}

CFNumberRef CFNumberCreate( CFAllocatorRef allocator, CFNumberType type, const void * valuePtr )
{
    struct CFNumber * o;
    
    if( valuePtr == NULL )
    {
        return NULL;
    }
    
    o = ( struct CFNumber * )CFRuntimeCreateInstance( allocator, CFNumberTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    ( void )type;
    
    return o;
}

CFIndex CFNumberGetByteSize( CFNumberRef number )
{
    if( number == NULL )
    {
        return 0;
    }
    
    return 0;
}

CFNumberType CFNumberGetType( CFNumberRef number )
{
    if( number == NULL )
    {
        return kCFNumberSInt8Type;
    }
    
    return kCFNumberSInt8Type;
}

Boolean CFNumberGetValue( CFNumberRef number, CFNumberType type, void * valuePtr )
{
    if( number == NULL || valuePtr == NULL )
    {
        return false;
    }
    
    ( void )number;
    ( void )type;
    ( void )valuePtr;
    
    return false;
}

Boolean CFNumberIsFloatType( CFNumberRef number )
{
    if( number == NULL )
    {
        return false;
    }
    
    return false;
}

CFComparisonResult CFNumberCompare( CFNumberRef number, CFNumberRef otherNumber, void * context )
{
    ( void )number;
    ( void )otherNumber;
    ( void )context;
    
    return kCFCompareEqualTo;
}
