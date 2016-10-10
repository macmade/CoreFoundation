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
 * @file        CFAtomic.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/CFAtomic.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Winnt.h>
#else
#include <libkern/OSAtomic.h>
#endif

CFIndex CFAtomicIncrement( volatile CFIndex * value )
{
    if( sizeof( CFIndex ) == sizeof( int32_t ) )
    {
        return CFAtomicIncrement32( ( volatile int32_t * )value );
    }
    else if( sizeof( CFIndex ) == sizeof( int64_t ) )
    {
        return CFAtomicIncrement64( ( volatile int64_t * )value );
    }
    
    fprintf( stderr, "Invalid size for CFIndex - Unknown platform\n" );
    abort();
    
    return 0;
}

int32_t CFAtomicIncrement32( volatile int32_t * value )
{
    #ifdef _WIN32
    return InterlockedIncrement( reinterpret_cast< volatile LONG * >( value  ) );
    #else
    return OSAtomicIncrement32( value );
    #endif
}

int64_t CFAtomicIncrement64( volatile int64_t * value )
{
    #ifdef _WIN32
    return InterlockedIncrement64( reinterpret_cast< volatile LONGLONG * >( value ) );
    #else
    return OSAtomicIncrement64( value );
    #endif
}

CFIndex CFAtomicDecrement( volatile CFIndex * value )
{
    if( sizeof( CFIndex ) == sizeof( int32_t ) )
    {
        return CFAtomicDecrement32( ( volatile int32_t * )value );
    }
    else if( sizeof( CFIndex ) == sizeof( int64_t ) )
    {
        return CFAtomicDecrement64( ( volatile int64_t * )value );
    }
    
    fprintf( stderr, "Invalid size for CFIndex - Unknown platform\n" );
    abort();
    
    return 0;
}

int32_t CFAtomicDecrement32( volatile int32_t * value )
{
    #ifdef _WIN32
    return InterlockedDecrement( reinterpret_cast< volatile LONG * >( value ) );
    #else
    return OSAtomicDecrement32( value );
    #endif
}

int64_t CFAtomicDecrement64( volatile int64_t * value )
{
    #ifdef _WIN32
    return InterlockedDecrement64( reinterpret_cast< volatile LONGLONG * >( value ) );
    #else
    return OSAtomicDecrement64( value );
    #endif
}

bool CFAtomicCompareAndSwap( CFIndex oldValue, CFIndex newValue, volatile CFIndex * value )
{
    if( sizeof( CFIndex ) == sizeof( int32_t ) )
    {
        return CFAtomicCompareAndSwap32( ( int32_t )oldValue, ( int32_t )newValue, ( volatile int32_t * )value );
    }
    else if( sizeof( CFIndex ) == sizeof( int64_t ) )
    {
        return CFAtomicCompareAndSwap64( ( int64_t )oldValue, ( int64_t )newValue, ( volatile int64_t * )value );
    }
    
    fprintf( stderr, "Invalid size for CFIndex - Unknown platform\n" );
    abort();
    
    return 0;
}

bool CFAtomicCompareAndSwap32( int32_t oldValue, int32_t newValue, volatile int32_t * value )
{
    #ifdef _WIN32
    return ( InterlockedCompareExchange( reinterpret_cast< volatile LONG * >( value ), newValue, oldValue ) == oldValue ) ? true : false;
    #else
    return ( OSAtomicCompareAndSwap32( oldValue, newValue, value ) ) ? true : false;
    #endif
}

bool CFAtomicCompareAndSwap64( int64_t oldValue, int64_t newValue, volatile int64_t * value )
{
    #ifdef _WIN32
    return ( InterlockedCompareExchange64( reinterpret_cast< volatile LONGLONG * >( value ), newValue, oldValue ) == oldValue ) ? true : false;
    #else
    return ( OSAtomicCompareAndSwap64( oldValue, newValue, value ) ) ? true : false;
    #endif
}

bool CFAtomicCompareAndSwapPointer( void * oldValue, void * newValue, void * volatile * value )
{
    #ifdef _WIN32
    return ( InterlockedCompareExchangePointer( value, newValue, oldValue ) == oldValue ) ? true : false;
    #else
    return ( OSAtomicCompareAndSwapPtr( oldValue, newValue, value ) ) ? true : false;
    #endif
}
