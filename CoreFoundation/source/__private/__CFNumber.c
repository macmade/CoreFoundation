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
#include <math.h>
#include <stdint.h>

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
    return ( CFHashCode )CFNumberGetSInt64Value( n );
}

bool CFNumberEquals( CFNumberRef n1, CFNumberRef n2 )
{
    return CFNumberCompare( n1, n2, NULL ) == kCFCompareEqualTo;
}

CFStringRef CFNumberCopyDescription( CFNumberRef n )
{
    const char * type;
    
    switch( n->_type )
    {
        case kCFNumberSInt8Type:        type = "kCFNumberSInt8Type";     break;
        case kCFNumberSInt16Type:       type = "kCFNumberSInt16Type";    break;
        case kCFNumberSInt32Type:       type = "kCFNumberSInt32Type";    break;
        case kCFNumberSInt64Type:       type = "kCFNumberSInt64Type";    break;
        case kCFNumberFloat32Type:      type = "kCFNumberFloat32Type";   break;
        case kCFNumberFloat64Type:      type = "kCFNumberFloat64Type";   break;
        case kCFNumberCharType:         type = "kCFNumberCharType";      break;
        case kCFNumberShortType:        type = "kCFNumberShortType";     break;
        case kCFNumberIntType:          type = "kCFNumberIntType";       break;
        case kCFNumberLongType:         type = "kCFNumberLongType";      break;
        case kCFNumberLongLongType:     type = "kCFNumberLongLongType";  break;
        case kCFNumberFloatType:        type = "kCFNumberFloatType";     break;
        case kCFNumberDoubleType:       type = "kCFNumberDoubleType";    break;
        case kCFNumberCFIndexType:      type = "kCFNumberCFIndexType";   break;
        default:                        type = "unknown";                break;
    }
    
    if( CFNumberIsPositiveInfinity( n ) )
    {
        return CFStringCreateWithFormat( NULL, NULL, CFSTR( "{ value = +infinity, type = %s }" ), type );
    }
    else if( CFNumberIsNegativeInfinity( n ) )
    {
        return CFStringCreateWithFormat( NULL, NULL, CFSTR( "{ value = -infinity, type = %s }" ), type );
    }
    else if( CFNumberIsNAN( n ) )
    {
        return CFStringCreateWithFormat( NULL, NULL, CFSTR( "{ value = nan, type = %s }" ), type );
    }
    
    if( CFNumberIsFloatType( n ) )
    {
        return CFStringCreateWithFormat( NULL, NULL, CFSTR( "{ value = %f, type = %s }" ), CFNumberGetFloat64Value( n ), type );
    }
    
    return CFStringCreateWithFormat( NULL, NULL, CFSTR( "{ value = %lli, type = %s }" ), CFNumberGetSInt64Value( n ), type );
}

SInt64 CFNumberGetSInt64Value( CFNumberRef n )
{
    if( n == NULL )
    {
        return 0;
    }
    
    if
    (
           CFNumberIsPositiveInfinity( n )
        || CFNumberIsNegativeInfinity( n )
        || CFNumberIsNAN( n )
    )
    {
        return INT64_MAX;
    }
    
    switch( n->_type )
    {
        case kCFNumberSInt8Type:        return ( SInt64 )( n->_value.int8 );
        case kCFNumberSInt16Type:       return ( SInt64 )( n->_value.int16 );
        case kCFNumberSInt32Type:       return ( SInt64 )( n->_value.int32 );
        case kCFNumberSInt64Type:       return ( SInt64 )( n->_value.int64 );
        case kCFNumberFloat32Type:      return ( SInt64 )( n->_value.float32 );
        case kCFNumberFloat64Type:      return ( SInt64 )( n->_value.float64 );
        case kCFNumberCharType:         return ( SInt64 )( n->_value.c );
        case kCFNumberShortType:        return ( SInt64 )( n->_value.s );
        case kCFNumberIntType:          return ( SInt64 )( n->_value.i );
        case kCFNumberLongType:         return ( SInt64 )( n->_value.l );
        case kCFNumberLongLongType:     return ( SInt64 )( n->_value.ll );
        case kCFNumberFloatType:        return ( SInt64 )( n->_value.f );
        case kCFNumberDoubleType:       return ( SInt64 )( n->_value.d );
        case kCFNumberCFIndexType:      return ( SInt64 )( n->_value.x );
        default:                        return 0;
    }
}

Float64 CFNumberGetFloat64Value( CFNumberRef n )
{
    if( n == NULL )
    {
        return 0.0;
    }
    
    switch( n->_type )
    {
        case kCFNumberSInt8Type:        return ( Float64 )( n->_value.int8 );
        case kCFNumberSInt16Type:       return ( Float64 )( n->_value.int16 );
        case kCFNumberSInt32Type:       return ( Float64 )( n->_value.int32 );
        case kCFNumberSInt64Type:       return ( Float64 )( n->_value.int64 );
        case kCFNumberFloat32Type:      return ( Float64 )( n->_value.float32 );
        case kCFNumberFloat64Type:      return ( Float64 )( n->_value.float64 );
        case kCFNumberCharType:         return ( Float64 )( n->_value.c );
        case kCFNumberShortType:        return ( Float64 )( n->_value.s );
        case kCFNumberIntType:          return ( Float64 )( n->_value.i );
        case kCFNumberLongType:         return ( Float64 )( n->_value.l );
        case kCFNumberLongLongType:     return ( Float64 )( n->_value.ll );
        case kCFNumberFloatType:        return ( Float64 )( n->_value.f );
        case kCFNumberDoubleType:       return ( Float64 )( n->_value.d );
        case kCFNumberCFIndexType:      return ( Float64 )( n->_value.x );
        default:                        return 0.0;
    }
}

bool CFNumberIsPositiveInfinity( CFNumberRef n )
{
    double d;
    
    if( n == NULL )
    {
        return false;
    }
    
    if( CFNumberIsFloatType( n ) == false )
    {
        return false;
    }
            
    CFNumberGetValue( n, kCFNumberDoubleType, &d );
            
    if( isinf( d ) && d > 0 )
    {
        return true;
    }
    
    return false;
}

bool CFNumberIsNegativeInfinity( CFNumberRef n )
{
    double d;
    
    if( n == NULL )
    {
        return false;
    }
    
    if( CFNumberIsFloatType( n ) == false )
    {
        return false;
    }
            
    CFNumberGetValue( n, kCFNumberDoubleType, &d );
            
    if( isinf( d ) && d < 0 )
    {
        return true;
    }
    
    return false;
}

bool CFNumberIsNAN( CFNumberRef n )
{
    double d;
    
    if( n == NULL )
    {
        return false;
    }
    
    if( CFNumberIsFloatType( n ) == false )
    {
        return false;
    }
            
    CFNumberGetValue( n, kCFNumberDoubleType, &d );
            
    if( isnan( d ) )
    {
        return true;
    }
    
    return false;
}
