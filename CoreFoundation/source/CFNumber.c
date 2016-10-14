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
#include <stdbool.h>
#include <math.h>

struct CFNumber
{
    CFRuntimeBase _base;
    bool          _isFloat;
    Float64       _doubleValue;
    SInt64        _integerValue;
    bool          _nan;
    bool          _pinf;
    bool          _ninf;
};

static CFTypeID CFNumberTypeID      = 0;
static CFRuntimeClass CFNumberClass =
{
    "CFNumber",
    sizeof( struct CFNumber ),
    NULL,
    NULL,
    NULL,
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
    
    CFNumberNaN._isFloat              = true;
    CFNumberNegativeInfinity._isFloat = true;
    CFNumberPositiveInfinity._isFloat = true;
    
    CFNumberNaN._nan               = true;
    CFNumberNegativeInfinity._pinf = true;
    CFNumberPositiveInfinity._ninf = true;
}

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
    
    if( type == kCFNumberSInt8Type )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const SInt8 * )valuePtr );
    }
    else if( type == kCFNumberSInt16Type )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const SInt16 * )valuePtr );
    }
    else if( type == kCFNumberSInt32Type )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const SInt32 * )valuePtr );
    }
    else if( type == kCFNumberSInt64Type )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const SInt64 * )valuePtr );
    }
    else if( type == kCFNumberFloat32Type )
    {
        o->_isFloat      = true;
        o->_doubleValue  = ( Float64 )*( ( const Float32 * )valuePtr );
    }
    else if( type == kCFNumberFloat64Type )
    {
        o->_isFloat      = true;
        o->_doubleValue  = ( Float64 )*( ( const Float64 * )valuePtr );
    }
    else if( type == kCFNumberCharType )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const char * )valuePtr );
    }
    else if( type == kCFNumberShortType )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const short * )valuePtr );
    }
    else if( type == kCFNumberIntType )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const int * )valuePtr );
    }
    else if( type == kCFNumberLongType )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const long * )valuePtr );
    }
    else if( type == kCFNumberLongLongType )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const long long * )valuePtr );
    }
    else if( type == kCFNumberFloatType )
    {
        o->_isFloat      = true;
        o->_doubleValue  = ( double )*( ( const float * )valuePtr );
    }
    else if( type == kCFNumberDoubleType )
    {
        o->_isFloat      = true;
        o->_doubleValue  = ( SInt64 )*( ( const double * )valuePtr );
    }
    else if( type == kCFNumberCFIndexType )
    {
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const CFIndex * )valuePtr );
    }
    else if( type == kCFNumberNSIntegerType )
    {
        #if defined( __LP64__ ) && __LP64__
        
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const long * )valuePtr );
        
        #else
        
        o->_isFloat      = false;
        o->_integerValue = ( SInt64 )*( ( const int * )valuePtr );
        
        #endif
    }
    else if( type == kCFNumberCGFloatType || type == kCFNumberMaxType )
    {
        #if defined( __LP64__ ) && __LP64__
        
        o->_isFloat      = true;
        o->_doubleValue  = ( Float64 )*( ( const double * )valuePtr );
        
        #else
        
        o->_isFloat      = true;
        o->_doubleValue  = ( Float64 )*( ( const float * )valuePtr );
        
        #endif
    }
    
    return o;
}

CFIndex CFNumberGetByteSize( CFNumberRef number )
{
    if( number == NULL )
    {
        return 0;
    }
    
    return ( number->_isFloat ) ? sizeof( double ) : sizeof( uint64_t );
}

CFNumberType CFNumberGetType( CFNumberRef number )
{
    if( number == NULL )
    {
        return kCFNumberSInt8Type;
    }
    
    return ( number->_isFloat ) ? kCFNumberFloat64Type : kCFNumberSInt64Type;
}

Boolean CFNumberGetValue( CFNumberRef number, CFNumberType type, void * valuePtr )
{
    if( valuePtr == NULL )
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
    
    return number->_isFloat;
}

CFComparisonResult CFNumberCompare( CFNumberRef number, CFNumberRef otherNumber, void * context )
{
    ( void )number;
    ( void )otherNumber;
    ( void )context;
    
    return kCFCompareEqualTo;
}
