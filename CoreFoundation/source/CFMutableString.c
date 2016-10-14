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
 * @file        CFMutableString.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFString.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const CFStringRef kCFStringTransformStripCombiningMarks = NULL;
const CFStringRef kCFStringTransformToLatin             = NULL;
const CFStringRef kCFStringTransformFullwidthHalfwidth  = NULL;
const CFStringRef kCFStringTransformLatinKatakana       = NULL;
const CFStringRef kCFStringTransformLatinHiragana       = NULL;
const CFStringRef kCFStringTransformHiraganaKatakana    = NULL;
const CFStringRef kCFStringTransformMandarinLatin       = NULL;
const CFStringRef kCFStringTransformLatinHangul         = NULL;
const CFStringRef kCFStringTransformLatinArabic         = NULL;
const CFStringRef kCFStringTransformLatinHebrew         = NULL;
const CFStringRef kCFStringTransformLatinThai           = NULL;
const CFStringRef kCFStringTransformLatinCyrillic       = NULL;
const CFStringRef kCFStringTransformLatinGreek          = NULL;
const CFStringRef kCFStringTransformToXMLHex            = NULL;
const CFStringRef kCFStringTransformToUnicodeName       = NULL;
const CFStringRef kCFStringTransformStripDiacritics     = NULL;

CFMutableStringRef CFStringCreateMutable( CFAllocatorRef alloc, CFIndex maxLength )
{
    struct CFString * o;
    CFIndex           capacity;
    
    capacity = ( maxLength ) ? maxLength : CF_STRING_DEFAULT_CAPACITY;
    o        = ( struct CFString * )CFRuntimeCreateInstance( alloc, CFStringTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    o->_cStr = CFAllocatorAllocate( alloc, capacity, 0 );
    
    if( o->_cStr == NULL )
    {
        CFRelease( o );
        
        return NULL;
    }
    
    o->_length      = 0;
    o->_capacity    = capacity;
    o->_mutable     = true;
    o->_allocator   = ( alloc ) ? CFRetain( alloc ) : NULL;
    o->_encoding    = kCFStringEncodingASCII;
    
    memset( o->_cStr, 0, capacity );
    
    return o;
}

CFMutableStringRef CFStringCreateMutableCopy( CFAllocatorRef alloc, CFIndex maxLength, CFStringRef theString )
{
    CFMutableStringRef o;
    CFIndex            capacity;
    
    if( theString == NULL )
    {
        return NULL;
    }
    
    capacity = ( maxLength < theString->_length + 1 ) ? theString->_length + 1 : maxLength;
    
    o = CFStringCreateMutable( alloc, capacity );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    o->_length   = theString->_length;
    o->_encoding = theString->_encoding;
    
    memcpy( o->_cStr, theString->_cStr, theString->_length );
    
    return o;
}

CFMutableStringRef CFStringCreateMutableWithExternalCharactersNoCopy( CFAllocatorRef alloc, UniChar * chars, CFIndex numChars, CFIndex capacity, CFAllocatorRef externalCharactersAllocator )
{
    ( void )alloc;
    ( void )chars;
    ( void )numChars;
    ( void )capacity;
    ( void )externalCharactersAllocator;
    
    return NULL;
}

void CFStringAppend( CFMutableStringRef theString, CFStringRef appendedString )
{
    char  * buf;
    CFIndex size;
    CFIndex capacity;
    char  * cStr;
    
    if( theString == NULL || appendedString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    size = CFStringGetMaximumSizeForEncoding( appendedString->_length + 1, theString->_encoding );
    buf  = CFAllocatorAllocate( NULL, size, 0 );
    
    if( buf == NULL )
    {
        return;
    }
    
    if( CFStringGetCString( appendedString, buf, size, theString->_encoding ) == false )
    {
        CFAllocatorDeallocate( NULL, buf );
        
        return;
    }
    
    capacity = theString->_length + size;
    
    if( capacity > theString->_capacity )
    {
        cStr = CFAllocatorReallocate( theString->_allocator, theString->_cStr, capacity, 0 );
        
        if( cStr == NULL )
        {
            CFAllocatorDeallocate( NULL, buf );
            
            return;
        }
        
        theString->_cStr     = cStr;
        theString->_capacity = capacity;
    }
    
    strcat( theString->_cStr, buf );
    
    theString->_length = theString->_length + appendedString->_length;
    
    CFAllocatorDeallocate( NULL, buf );
}

void CFStringAppendCharacters( CFMutableStringRef theString, const UniChar * chars, CFIndex numChars )
{
    CFStringRef s;
    
    if( theString == NULL || chars == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    s = CFStringCreateWithCharacters( NULL, chars, numChars );
    
    if( s )
    {
        CFStringAppend( theString, s );
        CFRelease( s );
    }
}

void CFStringAppendCString( CFMutableStringRef theString, const char * cStr, CFStringEncoding encoding )
{
    CFStringRef s;
    
    if( theString == NULL || cStr == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    s = CFStringCreateWithCString( NULL, cStr, encoding );
    
    if( s )
    {
        CFStringAppend( theString, s );
        CFRelease( s );
    }
}

void CFStringAppendFormat( CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, ... )
{
    va_list ap;
    
    if( theString == NULL || format == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    va_start( ap, format );
    CFStringAppendFormatAndArguments( theString, formatOptions, format, ap );
    va_end( ap );
}

void CFStringAppendFormatAndArguments( CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, va_list arguments )
{
    CFStringRef s;
    
    if( theString == NULL || format == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    s = CFStringCreateWithFormatAndArguments( NULL, formatOptions, format, arguments );
    
    if( s )
    {
        CFStringAppend( theString, s );
        CFRelease( s );
    }
}

void CFStringAppendPascalString( CFMutableStringRef theString, ConstStr255Param pStr, CFStringEncoding encoding )
{
    CFStringRef s;
    
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    s = CFStringCreateWithPascalString( NULL, pStr, encoding );
    
    if( s )
    {
        CFStringAppend( theString, s );
        CFRelease( s );
    }
}

void CFStringCapitalize( CFMutableStringRef theString, CFLocaleRef locale )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )locale;
}

void CFStringDelete( CFMutableStringRef theString, CFRange range )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )range;
}

CFIndex CFStringFindAndReplace( CFMutableStringRef theString, CFStringRef stringToFind, CFStringRef replacementString, CFRange rangeToSearch, CFStringCompareFlags compareOptions )
{
    if( theString == NULL )
    {
        return kCFNotFound;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )stringToFind;
    ( void )replacementString;
    ( void )rangeToSearch;
    ( void )compareOptions;
    
    return kCFNotFound;
}

void CFStringFold( CFMutableStringRef theString, CFStringCompareFlags theFlags, CFLocaleRef theLocale )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )theFlags;
    ( void )theLocale;
}

void CFStringInsert( CFMutableStringRef str, CFIndex idx, CFStringRef insertedStr )
{
    if( str == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( str );
    
    ( void )idx;
    ( void )insertedStr;
}

void CFStringLowercase( CFMutableStringRef theString, CFLocaleRef locale )
{
    CFIndex i;
    
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )locale;
    
    for( i = 0; i < theString->_length; i++ )
    {
        theString->_cStr[ i ] = ( char )tolower( theString->_cStr[ i ] );
    }
}

void CFStringNormalize( CFMutableStringRef theString, CFStringNormalizationForm theForm )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )theForm;
}

void CFStringPad( CFMutableStringRef theString, CFStringRef padString, CFIndex length, CFIndex indexIntoPad )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )padString;
    ( void )length;
    ( void )indexIntoPad;
}

void CFStringReplace( CFMutableStringRef theString, CFRange range, CFStringRef replacement )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )range;
    ( void )theString;
    ( void )replacement;
}

void CFStringReplaceAll( CFMutableStringRef theString, CFStringRef replacement )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )replacement;
}

void CFStringSetExternalCharactersNoCopy( CFMutableStringRef theString, UniChar * chars, CFIndex length, CFIndex capacity )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )chars;
    ( void )length;
    ( void )capacity;
}

Boolean CFStringTransform( CFMutableStringRef string, CFRange * range, CFStringRef transform, Boolean reverse )
{
    if( string == NULL )
    {
        return false;
    }
    
    CFStringAssertMutable( string );
    
    ( void )range;
    ( void )transform;
    ( void )reverse;
    
    return false;
}

void CFStringTrim( CFMutableStringRef theString, CFStringRef trimString )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )trimString;
}

void CFStringTrimWhitespace( CFMutableStringRef theString )
{
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
}

void CFStringUppercase( CFMutableStringRef theString, CFLocaleRef locale )
{
    CFIndex i;
    
    if( theString == NULL )
    {
        return;
    }
    
    CFStringAssertMutable( theString );
    
    ( void )locale;
    
    for( i = 0; i < theString->_length; i++ )
    {
        theString->_cStr[ i ] = ( char )toupper( theString->_cStr[ i ] );
    }
}
