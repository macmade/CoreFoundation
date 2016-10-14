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
 * @header      CFMutableString.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  CFMutableString manages dynamic strings. The basic interface for
 *              managing strings is provided by CFString. CFMutableString adds
 *              functions to modify the contents of a string.
 *              CFMutableString is "toll-free bridged" with its Cocoa Foundation
 *              counterpart, NSMutableString. This means that the Core
 *              Foundation type is interchangeable in function or method calls
 *              with the bridged Foundation object. Therefore, in a method where
 *              you see an NSMutableString * parameter, you can pass in a
 *              CFMutableStringRef, and in a function where you see a
 *              CFMutableStringRef parameter, you can pass in an NSMutableString
 *              instance. This also applies to concrete subclasses of
 *              NSMutableString. See Toll-Free Bridged Types for more
 *              information on toll-free bridging.
 */

#ifndef CORE_FOUNDATION_CF_MUTABLE_STRING_H
#define CORE_FOUNDATION_CF_MUTABLE_STRING_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFString.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFMutableStringRef
 * @abstract    A reference to a CFMutableString object.
 * @discussion  The type refers to a CFMutableString object, which
 *              "encapsulates" a Unicode string along with its length;
 *              the object has the attribute of being mutable, which means that
 *              its character contents can be modified. CFString is an opaque
 *              type that defines the characteristics and behavior of CFString
 *              objects, both immutable and mutable.
 *              CFMutableString derives from CFString. Therefore, you can pass
 *              CFMutableString objects into functions accepting CFString
 *              objects.
 */
typedef struct CFString * CFMutableStringRef;

/*!
 * @typedef     CFStringNormalizationForm
 * @abstract    Unicode normalization forms as described in Unicode Technical
 *              Report #15.
 * @constant    kCFStringNormalizationFormD     Canonical decomposition.
 * @constant    kCFStringNormalizationFormKD    Compatibility decomposition.
 * @constant    kCFStringNormalizationFormC     Canonical decomposition followed
 *                                              by canonical composition.
 * @constant    kCFStringNormalizationFormKC    Compatibility decomposition
 *                                              followed by canonical
 *                                              composition.
 */
typedef enum
{
    kCFStringNormalizationFormD  = 0,
    kCFStringNormalizationFormKD = 1,
    kCFStringNormalizationFormC  = 2,
    kCFStringNormalizationFormKC = 3
}
CFStringNormalizationForm;

/*!
 * @function    
 */
CF_EXPORT CFMutableStringRef CFStringCreateMutable( CFAllocatorRef alloc, CFIndex maxLength );

/*!
 * @function    
 */
CF_EXPORT CFMutableStringRef CFStringCreateMutableCopy( CFAllocatorRef alloc, CFIndex maxLength, CFStringRef theString );

/*!
 * @function    
 */
CF_EXPORT CFMutableStringRef CFStringCreateMutableWithExternalCharactersNoCopy( CFAllocatorRef alloc, UniChar * chars, CFIndex numChars, CFIndex capacity, CFAllocatorRef externalCharactersAllocator );

/*!
 * @function    
 */
CF_EXPORT void CFStringAppend( CFMutableStringRef theString, CFStringRef appendedString );

/*!
 * @function    
 */
CF_EXPORT void CFStringAppendCharacters( CFMutableStringRef theString, const UniChar * chars, CFIndex numChars );

/*!
 * @function    
 */
CF_EXPORT void CFStringAppendCString( CFMutableStringRef theString, const char * cStr, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT void CFStringAppendFormat( CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, ... );

/*!
 * @function    
 */
CF_EXPORT void CFStringAppendFormatAndArguments( CFMutableStringRef theString, CFDictionaryRef formatOptions, CFStringRef format, va_list arguments );

/*!
 * @function    
 */
CF_EXPORT void CFStringAppendPascalString( CFMutableStringRef theString, ConstStr255Param pStr, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT void CFStringCapitalize( CFMutableStringRef theString, CFLocaleRef locale );

/*!
 * @function    
 */
CF_EXPORT void CFStringDelete( CFMutableStringRef theString, CFRange range );

/*!
 * @function    
 */
CF_EXPORT CFIndex CFStringFindAndReplace( CFMutableStringRef theString, CFStringRef stringToFind, CFStringRef replacementString, CFRange rangeToSearch, CFStringCompareFlags compareOptions );

/*!
 * @function    
 */
CF_EXPORT void CFStringFold( CFMutableStringRef theString, CFStringCompareFlags theFlags, CFLocaleRef theLocale );

/*!
 * @function    
 */
CF_EXPORT void CFStringInsert( CFMutableStringRef str, CFIndex idx, CFStringRef insertedStr );

/*!
 * @function    
 */
CF_EXPORT void CFStringLowercase( CFMutableStringRef theString, CFLocaleRef locale );

/*!
 * @function    
 */
CF_EXPORT void CFStringNormalize( CFMutableStringRef theString, CFStringNormalizationForm theForm );

/*!
 * @function    
 */
CF_EXPORT void CFStringPad( CFMutableStringRef theString, CFStringRef padString, CFIndex length, CFIndex indexIntoPad );

/*!
 * @function    
 */
CF_EXPORT void CFStringReplace( CFMutableStringRef theString, CFRange range, CFStringRef replacement );

/*!
 * @function    
 */
CF_EXPORT void CFStringReplaceAll( CFMutableStringRef theString, CFStringRef replacement );

/*!
 * @function    
 */
CF_EXPORT void CFStringSetExternalCharactersNoCopy( CFMutableStringRef theString, UniChar * chars, CFIndex length, CFIndex capacity );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringTransform( CFMutableStringRef string, CFRange * range, CFStringRef transform, Boolean reverse );

/*!
 * @function    
 */
CF_EXPORT void CFStringTrim( CFMutableStringRef theString, CFStringRef trimString );

/*!
 * @function    
 */
CF_EXPORT void CFStringTrimWhitespace( CFMutableStringRef theString );

/*!
 * @function    
 */
CF_EXPORT void CFStringUppercase( CFMutableStringRef theString, CFLocaleRef locale );

/*!
 * @constant    kCFStringTransformStripCombiningMarks
 * @abstract    The identifier of a transform to strip combining marks (accents
 *              or diacritics).
 */
CF_EXPORT const CFStringRef kCFStringTransformStripCombiningMarks;

/*!
 * @constant    kCFStringTransformToLatin
 * @abstract    The identifier of a transform to transliterate all text possible
 *              to Latin script. Ideographs are transliterated as Mandarin
 *              Chinese.
 */
CF_EXPORT const CFStringRef kCFStringTransformToLatin;

/*!
 * @constant    kCFStringTransformFullwidthHalfwidth
 * @abstract    The identifier of a reversible transform to convert full-width
 *              characters to their half-width equivalents.
 */
CF_EXPORT const CFStringRef kCFStringTransformFullwidthHalfwidth;

/*!
 * @constant    kCFStringTransformLatinKatakana
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Katakana from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinKatakana;

/*!
 * @constant    kCFStringTransformLatinHiragana
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Hiragana from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinHiragana;

/*!
 * @constant    kCFStringTransformHiraganaKatakana
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Katakana from Hiragana.
 */
CF_EXPORT const CFStringRef kCFStringTransformHiraganaKatakana;

/*!
 * @constant    kCFStringTransformMandarinLatin
 * @abstract    The identifier of a transform to transliterate text to Latin
 *              from ideographs interpreted as Mandarin Chinese. This transform
 *              is not reversible.
 */
CF_EXPORT const CFStringRef kCFStringTransformMandarinLatin;

/*!
 * @constant    kCFStringTransformLatinHangul
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Hangul from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinHangul;

/*!
 * @constant    kCFStringTransformLatinArabic
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Arabic from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinArabic;

/*!
 * @constant    kCFStringTransformLatinHebrew
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Hebrew from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinHebrew;

/*!
 * @constant    kCFStringTransformLatinThai
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Thai from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinThai;

/*!
 * @constant    kCFStringTransformLatinCyrillic
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Cyrillic from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinCyrillic;

/*!
 * @constant    kCFStringTransformLatinGreek
 * @abstract    The identifier of a reversible transform to transliterate text
 *              to Greek from Latin.
 */
CF_EXPORT const CFStringRef kCFStringTransformLatinGreek;

/*!
 * @constant    kCFStringTransformToXMLHex
 * @abstract    The identifier of a reversible transform to transliterate
 *              characters other than printable ASCII to XML/HTML numeric
 *              entities.
 */
CF_EXPORT const CFStringRef kCFStringTransformToXMLHex;

/*!
 * @constant    kCFStringTransformToUnicodeName
 * @abstract    The identifier of a reversible transform to transliterate
 *              characters other than printable ASCII (minus braces) to their
 *              Unicode character name in braces.
 */
CF_EXPORT const CFStringRef kCFStringTransformToUnicodeName;

/*!
 * @constant    kCFStringTransformStripDiacritics
 * @abstract    The identifier of a transform to remove diacritic markings.
 */
CF_EXPORT const CFStringRef kCFStringTransformStripDiacritics;

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_MUTABLE_STRING_H */
