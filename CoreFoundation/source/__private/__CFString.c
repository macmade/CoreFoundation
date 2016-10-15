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
 * @file        CFString.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/__CFString.h>
#include <string.h>

CFTypeID       CFStringTypeID = 0;
CFRuntimeClass CFStringClass  =
{
    "CFString",
    sizeof( struct CFString ),
    NULL,
    ( void ( * )( CFTypeRef ) )CFStringDestruct,
    ( CFHashCode ( * )( CFTypeRef ) )CFStringHash,
    ( bool ( * )( CFTypeRef, CFTypeRef ) )CFStringEquals,
    ( CFStringRef ( * )( CFTypeRef ) )CFStringCopyDescription
};

CFSpinLock    CFStringConstantStringsLock     = 0;
CFIndex       CFStringConstantStringsCapacity = 0;
CFStringRef * CFStringConstantStrings         = NULL;

void CFStringInitialize( void )
{
    CFStringTypeID = CFRuntimeRegisterClass( &CFStringClass );
}

void CFStringDestruct( CFStringRef str )
{
    if( str->_cStr )
    {
        CFAllocatorDeallocate( str->_allocator, ( void * )( str->_cStr ) );
    }
    
    if( str->_allocator )
    {
        CFRelease( str->_allocator );
    }
}

CFHashCode CFStringHash( CFStringRef str )
{
    CFHashCode            h;
    unsigned char         c;
    const unsigned char * cp;
    
    if( str->_cStr == NULL )
    {
        return ( CFHashCode )str;
    }
    
    cp = ( const unsigned char * )( str->_cStr );
    h  = 0;
    
    while( ( c = *( cp++ ) ) )
    {
        h = h * 31 + c;
    }
    
    return h;
}

bool CFStringEquals( CFStringRef s1, CFStringRef s2 )
{
    if( s1->_cStr == NULL || s2->_cStr == NULL )
    {
        return false;
    }
    
    if( s1->_cStr == s2->_cStr )
    {
        return true;
    }
    
    if( s1->_length != s2->_length )
    {
        return false;
    }
    
    return memcmp( s1->_cStr, s2->_cStr, ( size_t )( s1->_length ) ) == 0;
}

CFStringRef CFStringCopyDescription( CFStringRef str )
{
    CFStringRef s;
    
    s = CFStringCreateWithFormat
    (
        NULL,
        NULL,
        CFSTR( "%s" ),
        ( str->_cStr ) ? str->_cStr : "(null)"
    );
    
    return s;
}

void CFStringAssertMutable( CFStringRef str )
{
    if( str == NULL )
    {
        return;
    }
    
    if( str->_mutable == false )
    {
        CFRuntimeAbortWithError( "<CFString 0x%llu> is not mutable", ( unsigned long long )str );
    }
}
