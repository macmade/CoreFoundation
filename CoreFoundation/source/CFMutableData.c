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
 * @file        CFMutableData.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <stdlib.h>

CFMutableDataRef CFDataCreateMutable( CFAllocatorRef allocator, CFIndex capacity )
{
    ( void )allocator;
    ( void )capacity;
    
    return NULL;
}

CFMutableDataRef CFDataCreateMutableCopy( CFAllocatorRef allocator, CFIndex capacity, CFDataRef theData )
{
    ( void )allocator;
    ( void )capacity;
    ( void )theData;
    
    return NULL;
}

UInt8 * CFDataGetMutableBytePtr( CFMutableDataRef theData )
{
    ( void )theData;
    
    return NULL;
}

void CFDataAppendBytes( CFMutableDataRef theData, const UInt8 * bytes, CFIndex length )
{
    ( void )theData;
    ( void )bytes;
    ( void )length;
}

void CFDataDeleteBytes( CFMutableDataRef theData, CFRange range )
{
    ( void )theData;
    ( void )range;
}

void CFDataReplaceBytes( CFMutableDataRef theData, CFRange range, const UInt8 * newBytes, CFIndex newLength )
{
    ( void )theData;
    ( void )range;
    ( void )newBytes;
    ( void )newLength;
}

void CFDataIncreaseLength( CFMutableDataRef theData, CFIndex extraLength )
{
    ( void )theData;
    ( void )extraLength;
}

void CFDataSetLength( CFMutableDataRef theData, CFIndex length )
{
    ( void )theData;
    ( void )length;
}
