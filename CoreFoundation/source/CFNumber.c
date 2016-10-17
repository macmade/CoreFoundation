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
#include <float.h>

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
    
    if( type == kCFNumberNSIntegerType )
    {
        #if defined( __LP64__ ) || defined( __LLP64__ ) || defined( _WIN64 )
        
        type = kCFNumberSInt64Type;
        
        #else
        
        type = kCFNumberSInt32Type;
        
        #endif
    }
    else if( type == kCFNumberCGFloatType )
    {
        #if defined( __LP64__ ) || defined( __LLP64__ ) || defined( _WIN64 )
        
        type = kCFNumberFloat64Type;
        
        #else
        
        type = kCFNumberFloat32Type;
        
        #endif
    }
    
    o->_type = type;
    
    switch( type )
    {
        case kCFNumberSInt8Type:        o->_value.int8    = *( ( const SInt8     * )valuePtr ); break;
        case kCFNumberSInt16Type:       o->_value.int16   = *( ( const SInt16    * )valuePtr ); break;
        case kCFNumberSInt32Type:       o->_value.int32   = *( ( const SInt32    * )valuePtr ); break;
        case kCFNumberSInt64Type:       o->_value.int64   = *( ( const SInt64    * )valuePtr ); break;
        case kCFNumberFloat32Type:      o->_value.float32 = *( ( const Float32   * )valuePtr ); break;
        case kCFNumberFloat64Type:      o->_value.float64 = *( ( const Float64   * )valuePtr ); break;
        case kCFNumberCharType:         o->_value.c       = *( ( const char      * )valuePtr ); break;
        case kCFNumberShortType:        o->_value.s       = *( ( const short     * )valuePtr ); break;
        case kCFNumberIntType:          o->_value.i       = *( ( const int       * )valuePtr ); break;
        case kCFNumberLongType:         o->_value.l       = *( ( const long      * )valuePtr ); break;
        case kCFNumberLongLongType:     o->_value.ll      = *( ( const long long * )valuePtr ); break;
        case kCFNumberFloatType:        o->_value.f       = *( ( const float     * )valuePtr ); break;
        case kCFNumberDoubleType:       o->_value.d       = *( ( const double    * )valuePtr ); break;
        case kCFNumberCFIndexType:      o->_value.x       = *( ( const CFIndex   * )valuePtr ); break;
        
        default:
            
            CFRelease( o );
            
            return NULL;
    }
    
    return o;
}

CFIndex CFNumberGetByteSize( CFNumberRef number )
{
    if( number == NULL )
    {
        return 0;
    }
    
    switch( number->_type )
    {
        case kCFNumberSInt8Type:        return sizeof( SInt8 );     break;
        case kCFNumberSInt16Type:       return sizeof( SInt16 );    break;
        case kCFNumberSInt32Type:       return sizeof( SInt32 );    break;
        case kCFNumberSInt64Type:       return sizeof( SInt64 );    break;
        case kCFNumberFloat32Type:      return sizeof( Float32 );   break;
        case kCFNumberFloat64Type:      return sizeof( Float64 );   break;
        case kCFNumberCharType:         return sizeof( char );      break;
        case kCFNumberShortType:        return sizeof( short );     break;
        case kCFNumberIntType:          return sizeof( int );       break;
        case kCFNumberLongType:         return sizeof( long );      break;
        case kCFNumberLongLongType:     return sizeof( long long ); break;
        case kCFNumberFloatType:        return sizeof( float );     break;
        case kCFNumberDoubleType:       return sizeof( double );    break;
        case kCFNumberCFIndexType:      return sizeof( CFIndex );   break;
        
        default:
            
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
    
    return number->_type;
}

Boolean CFNumberGetValue( CFNumberRef number, CFNumberType type, void * valuePtr )
{
    if( number == NULL || valuePtr == NULL )
    {
        return false;
    }
    
    if( type == kCFNumberNSIntegerType )
    {
        #if defined( __LP64__ ) || defined( __LLP64__ ) || defined( _WIN64 )
        
        type = kCFNumberSInt64Type;
        
        #else
        
        type = kCFNumberSInt32Type;
        
        #endif
    }
    else if( type == kCFNumberCGFloatType )
    {
        #if defined( __LP64__ ) || defined( __LLP64__ ) || defined( _WIN64 )
        
        type = kCFNumberFloat64Type;
        
        #else
        
        type = kCFNumberFloat32Type;
        
        #endif
    }
    
    switch( type )
    {
        case kCFNumberSInt8Type:        *( ( SInt8     * )valuePtr ) = ( SInt8     )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberSInt16Type:       *( ( SInt16    * )valuePtr ) = ( SInt16    )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberSInt32Type:       *( ( SInt32    * )valuePtr ) = ( SInt32    )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberSInt64Type:       *( ( SInt64    * )valuePtr ) = ( SInt64    )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberFloat32Type:      *( ( Float32   * )valuePtr ) = ( Float32   )CFNumberGetFloat64Value( number ); break;
        case kCFNumberFloat64Type:      *( ( Float64   * )valuePtr ) = ( Float64   )CFNumberGetFloat64Value( number ); break;
        case kCFNumberCharType:         *( ( char      * )valuePtr ) = ( char      )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberShortType:        *( ( short     * )valuePtr ) = ( short     )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberIntType:          *( ( int       * )valuePtr ) = ( int       )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberLongType:         *( ( long      * )valuePtr ) = ( long      )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberLongLongType:     *( ( long long * )valuePtr ) = ( long long )CFNumberGetSInt64Value(  number ); break;
        case kCFNumberFloatType:        *( ( float     * )valuePtr ) = ( float     )CFNumberGetFloat64Value( number ); break;
        case kCFNumberDoubleType:       *( ( double    * )valuePtr ) = ( double    )CFNumberGetFloat64Value( number ); break;
        case kCFNumberCFIndexType:      *( ( CFIndex   * )valuePtr ) = ( CFIndex   )CFNumberGetSInt64Value(  number ); break;

        default:
            
            return false;
    }
    
    return true;
}

Boolean CFNumberIsFloatType( CFNumberRef number )
{
    if( number == NULL )
    {
        return false;
    }
    
    if
    (
           number->_type == kCFNumberFloat32Type
        || number->_type == kCFNumberFloat64Type
        || number->_type == kCFNumberFloatType
        || number->_type == kCFNumberDoubleType
        || number->_type == kCFNumberCGFloatType
    )
    {
        return true;
    }
    
    return false;
}

CFComparisonResult CFNumberCompare( CFNumberRef number, CFNumberRef otherNumber, void * context )
{
    ( void )context;
    
    if( number == NULL && otherNumber == NULL )
    {
        return kCFCompareEqualTo;
    }
    
    if( number == NULL )
    {
        {
            SInt64 i;
            
            i = CFNumberGetSInt64Value( otherNumber );
            
            if( i == 0 )
            {
                return kCFCompareEqualTo;
            }
            
            return ( i < 0 ) ? kCFCompareGreaterThan : kCFCompareLessThan;
        }
    }
    
    if( otherNumber == NULL )
    {
        {
            SInt64 i;
            
            i = CFNumberGetSInt64Value( number );
            
            if( i == 0 )
            {
                return kCFCompareEqualTo;
            }
            
            return ( i < 0 ) ? kCFCompareLessThan : kCFCompareGreaterThan;
        }
    }
    
    if( CFNumberIsPositiveInfinity( number ) )
    {
        return ( CFNumberIsPositiveInfinity( otherNumber ) ) ? kCFCompareEqualTo : kCFCompareGreaterThan;
    }
    
    if( CFNumberIsPositiveInfinity( otherNumber ) )
    {
        return ( CFNumberIsPositiveInfinity( number ) ) ? kCFCompareEqualTo : kCFCompareLessThan;
    }
    
    if( CFNumberIsNegativeInfinity( number ) )
    {
        return ( CFNumberIsNegativeInfinity( otherNumber ) ) ? kCFCompareEqualTo : kCFCompareLessThan;
    }
    
    if( CFNumberIsNegativeInfinity( otherNumber ) )
    {
        return ( CFNumberIsNegativeInfinity( number ) ) ? kCFCompareEqualTo : kCFCompareGreaterThan;
    }
    
    if( CFNumberIsNAN( number ) )
    {
        if( CFNumberIsNAN( otherNumber ) )
        {
            return kCFCompareEqualTo;
        }
        
        return ( CFNumberGetSInt64Value( otherNumber ) < 0 ) ? kCFCompareGreaterThan : kCFCompareLessThan;
    }
    
    if( CFNumberIsNAN( otherNumber ) )
    {
        if( CFNumberIsNAN( number ) )
        {
            return kCFCompareEqualTo;
        }
        
        return ( CFNumberGetSInt64Value( number ) < 0 ) ? kCFCompareLessThan : kCFCompareGreaterThan;
    }
    
    if( CFNumberIsFloatType( number ) || CFNumberIsFloatType( otherNumber ) )
    {
        {
            Float64 f1;
            Float64 f2;
            
            f1 = CFNumberGetFloat64Value( number );
            f2 = CFNumberGetFloat64Value( otherNumber );
            
            if( fabs( f1 - f2 ) < DBL_EPSILON )
            {
                return kCFCompareEqualTo;
            }
            
            return ( f1 < f2 ) ? kCFCompareLessThan : kCFCompareGreaterThan;
        }
    }
    
    {
        SInt64 i1;
        SInt64 i2;
        
        i1 = CFNumberGetSInt64Value( number );
        i2 = CFNumberGetSInt64Value( otherNumber );
        
        if( i1 == i2 )
        {
            return kCFCompareEqualTo;
        }
        
        return ( i1 < i2 ) ? kCFCompareLessThan : kCFCompareGreaterThan;
    }
}
