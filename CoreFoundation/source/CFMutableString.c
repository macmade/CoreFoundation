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
#include <stdlib.h>

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
    ( void )alloc;
    ( void )maxLength;
    
    return NULL;
}

CFMutableStringRef CFStringCreateMutableCopy( CFAllocatorRef alloc, CFIndex maxLength, CFStringRef theString )
{
    ( void )alloc;
    ( void )maxLength;
    ( void )theString;
    
    return NULL;
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
    ( void )theString;
    ( void )appendedString;
}

void CFStringAppendCharacters( CFMutableStringRef theString, const UniChar * chars, CFIndex numChars )
{
    ( void )theString;
    ( void )chars;
    ( void )numChars;
}

void CFStringAppendCString( CFMutableStringRef theString, const char * cStr, CFStringEncoding encoding )
{
    ( void )theString;
    ( void )cStr;
    ( void )encoding;
}

void CFStringAppendFormat( CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, ... )
{
    ( void )theString;
    ( void )formatOptions;
    ( void )format;
}

void CFStringAppendFormatAndArguments( CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, va_list arguments )
{
    ( void )theString;
    ( void )formatOptions;
    ( void )format;
    ( void )arguments;
}

void CFStringAppendPascalString( CFMutableStringRef theString, ConstStr255Param pStr, CFStringEncoding encoding )
{
    ( void )theString;
    ( void )pStr;
    ( void )encoding;
}

void CFStringCapitalize( CFMutableStringRef theString, CFLocaleRef locale )
{
    ( void )theString;
    ( void )locale;
}

void CFStringDelete( CFMutableStringRef theString, CFRange range )
{
    ( void )theString;
    ( void )range;
}

CFIndex CFStringFindAndReplace( CFMutableStringRef theString, CFStringRef stringToFind, CFStringRef replacementString, CFRange rangeToSearch, CFStringCompareFlags compareOptions )
{
    ( void )theString;
    ( void )stringToFind;
    ( void )replacementString;
    ( void )rangeToSearch;
    ( void )compareOptions;
    
    return kCFNotFound;
}

void CFStringFold( CFMutableStringRef theString, CFStringCompareFlags theFlags, CFLocaleRef theLocale )
{
    ( void )theString;
    ( void )theFlags;
    ( void )theLocale;
}

void CFStringInsert( CFMutableStringRef str, CFIndex idx, CFStringRef insertedStr )
{
    ( void )str;
    ( void )idx;
    ( void )insertedStr;
}

void CFStringLowercase( CFMutableStringRef theString, CFLocaleRef locale )
{
    ( void )theString;
    ( void )locale;
}

void CFStringNormalize( CFMutableStringRef theString, CFStringNormalizationForm theForm )
{
    ( void )theString;
    ( void )theForm;
}

void CFStringPad( CFMutableStringRef theString, CFStringRef padString, CFIndex length, CFIndex indexIntoPad )
{
    ( void )theString;
    ( void )padString;
    ( void )length;
    ( void )indexIntoPad;
}

void CFStringReplace( CFMutableStringRef theString, CFRange range, CFStringRef replacement )
{
    ( void )theString;
    ( void )range;
    ( void )theString;
    ( void )replacement;
}

void CFStringReplaceAll( CFMutableStringRef theString, CFStringRef replacement )
{
    ( void )theString;
    ( void )replacement;
}

void CFStringSetExternalCharactersNoCopy( CFMutableStringRef theString, UniChar * chars, CFIndex length, CFIndex capacity )
{
    ( void )theString;
    ( void )chars;
    ( void )length;
    ( void )capacity;
}

Boolean CFStringTransform( CFMutableStringRef string, CFRange * range, CFStringRef transform, Boolean reverse )
{
    ( void )string;
    ( void )range;
    ( void )transform;
    ( void )reverse;
    
    return false;
}

void CFStringTrim( CFMutableStringRef theString, CFStringRef trimString )
{
    ( void )theString;
    ( void )trimString;
}

void CFStringTrimWhitespace( CFMutableStringRef theString )
{
    ( void )theString;
}

void CFStringUppercase( CFMutableStringRef theString, CFLocaleRef locale )
{
    ( void )theString;
    ( void )locale;
}
