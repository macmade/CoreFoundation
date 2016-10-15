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
 * @header      CFString.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 * @discussion  CFString provides a suite of efficient string-manipulation and
 *              string-conversion functions. It offers seamless Unicode support
 *              and facilitates the sharing of data between Cocoa and C-based
 *              programs. CFString objects are immutable—use CFMutableStringRef
 *              to create and manage a string that can be changed after it has
 *              been created.
 *              CFString has two primitive functions, CFStringGetLength and
 *              CFStringGetCharacterAtIndex, that provide the basis for all
 *              other functions in its interface. The CFStringGetLength function
 *              returns the total number (in terms of UTF-16 code pairs) of
 *              characters in the string. The CFStringGetCharacterAtIndex
 *              function gives access to each character in the string by index,
 *              with index values starting at 0.
 *              CFString provides functions for finding and comparing strings.
 *              It also provides functions for reading numeric values from
 *              strings, for combining strings in various ways, and for
 *              converting a string to different forms (such as encoding and
 *              case changes). A number of functions, for example
 *              CFStringFindWithOptions, allow you to specify a range over which
 *              to operate within a string. The specified range must not exceed
 *              the length of the string. Debugging options may help you to
 *              catch any errors that arise if a range does exceed a string's
 *              length.
 *              Like other Core Foundation types, you can hash CFStrings using
 *              the CFHash function. You should never, though, store a hash
 *              value outside of your application and expect it to be useful if
 *              you read it back in later (hash values may change between
 *              different releases of the operating system).
 *              CFString is "toll-free bridged" with its Cocoa Foundation
 *              counterpart, NSString. This means that the Core Foundation type
 *              is interchangeable in function or method calls with the bridged
 *              Foundation object. Therefore, in a method where you see an
 *              NSString * parameter, you can pass in a CFStringRef, and in a
 *              function where you see a CFStringRef parameter, you can pass in
 *              an NSString instance. This also applies to concrete subclasses
 *              of NSString. See Toll-Free Bridged Types for more information
 *              on toll-free bridging.
 */

#ifndef CORE_FOUNDATION_CF_STRING_H
#define CORE_FOUNDATION_CF_STRING_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFCharacterSet.h>
#include <CoreFoundation/CFData.h>
#include <CoreFoundation/CFArray.h>
#include <CoreFoundation/CFLocale.h>
#include <stdarg.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFStringRef
 * @abstract    A reference to a CFString object.
 * @discussion  The CFStringRef type refers to a CFString object, which
 *              "encapsulates" a Unicode string along with its length. CFString
 *              is an opaque type that defines the characteristics and behavior
 *              of CFString objects.
 *              Values of type CFStringRef may refer to immutable or mutable
 *              strings, as CFMutableString objects respond to all functions
 *              intended for immutable CFString objects. Functions which accept
 *              CFStringRef values, and which need to hold on to the values
 *              immutably, should call CFStringCreateCopy (instead of CFRetain)
 *              to do so.
 */
typedef const struct CFString * CFStringRef;

#include <CoreFoundation/CFDictionary.h>

/*!
 * @define      CFSTR
 * @abstract    Creates an immutable string from a constant compile-time string.
 * @param       _s_     A constant C string (that is, text enclosed in
 *                      double-quotation marks) from which the string is to be
 *                      created.
 * @result      An immutable string, or NULL if there was a problem creating the
 *              object. The returned object is a constant. You may retain and
 *              release it, similar to other immutable CFString objects, but are
 *              not required to do so—it will remain valid until the program
 *              terminates.
 * @discussion  The CFSTR macro is a convenient way to create CFString
 *              representations of constant compile-time strings.
 *              A value returned by CFSTR has the following semantics:
 *              Values returned from CFSTR are not released by CFString—they are
 *              guaranteed to be valid until the program terminates.
 *              You can retain and release values returned from CFSTR in a
 *              balanced fashion, like any other CFString, but you are not
 *              required to do so.
 *              Note: When using this macro as an initializer, you must build
 *              using the -fconstant-cfstrings compiler flag.
 */
#define CFSTR( _s_ )    CFStringMakeConstantString( _s_ )

/*!
 * @typedef     
 */
typedef UInt32 CFStringEncoding;

/*!
 * @define      
 */
#define kCFStringEncodingInvalidId  ( 0xffffffffU )

/*!
 * typedef      
 */
typedef enum
{
    kCFCompareCaseInsensitive       = 1,
    kCFCompareBackwards             = 4,
    kCFCompareAnchored              = 8,
    kCFCompareNonliteral            = 16,
    kCFCompareLocalized             = 32,
    kCFCompareNumerically           = 64,
    kCFCompareDiacriticInsensitive  = 128,
    kCFCompareWidthInsensitive      = 256,
    kCFCompareForcedOrdering        = 512
}
CFStringCompareFlags;

/*!
 * typedef      
 */
typedef struct
{
    UniChar         buffer[ 64 ];
    CFIndex         bufferedRangeEnd;
    CFIndex         bufferedRangeStart;
    const char    * directCStringBuffer;
    const UniChar * directUniCharBuffer;
    CFRange         rangeToBuffer;
    CFStringRef     theString;
}
CFStringInlineBuffer;

/*!
 * typedef      
 */
typedef enum
{
    kCFStringEncodingMacRoman       = 0,
    kCFStringEncodingWindowsLatin1  = 0x0500,
    kCFStringEncodingISOLatin1      = 0x0201,
    kCFStringEncodingNextStepLatin  = 0x0B01,
    kCFStringEncodingASCII          = 0x0600,
    kCFStringEncodingUnicode        = 0x0100,
    kCFStringEncodingUTF8           = 0x08000100,
    kCFStringEncodingNonLossyASCII  = 0x0BFF,
    kCFStringEncodingUTF16          = 0x0100,
    kCFStringEncodingUTF16BE        = 0x10000100,
    kCFStringEncodingUTF16LE        = 0x14000100,
    kCFStringEncodingUTF32          = 0x0c000100,
    kCFStringEncodingUTF32BE        = 0x18000100,
    kCFStringEncodingUTF32LE        = 0x1c000100
}
CFStringBuiltInEncodings;

/*!
 * typedef      
 */
typedef enum
{
    kCFStringEncodingMacJapanese                = 1,
    kCFStringEncodingMacChineseTrad             = 2,
    kCFStringEncodingMacKorean                  = 3,
    kCFStringEncodingMacArabic                  = 4,
    kCFStringEncodingMacHebrew                  = 5,
    kCFStringEncodingMacGreek                   = 6,
    kCFStringEncodingMacCyrillic                = 7,
    kCFStringEncodingMacDevanagari              = 9,
    kCFStringEncodingMacGurmukhi                = 10,
    kCFStringEncodingMacGujarati                = 11,
    kCFStringEncodingMacOriya                   = 12,
    kCFStringEncodingMacBengali                 = 13,
    kCFStringEncodingMacTamil                   = 14,
    kCFStringEncodingMacTelugu                  = 15,
    kCFStringEncodingMacKannada                 = 16,
    kCFStringEncodingMacMalayalam               = 17,
    kCFStringEncodingMacSinhalese               = 18,
    kCFStringEncodingMacBurmese                 = 19,
    kCFStringEncodingMacKhmer                   = 20,
    kCFStringEncodingMacThai                    = 21,
    kCFStringEncodingMacLaotian                 = 22,
    kCFStringEncodingMacGeorgian                = 23,
    kCFStringEncodingMacArmenian                = 24,
    kCFStringEncodingMacChineseSimp             = 25,
    kCFStringEncodingMacTibetan                 = 26,
    kCFStringEncodingMacMongolian               = 27,
    kCFStringEncodingMacEthiopic                = 28,
    kCFStringEncodingMacCentralEurRoman         = 29,
    kCFStringEncodingMacVietnamese              = 30,
    kCFStringEncodingMacExtArabic               = 31,
    kCFStringEncodingMacSymbol                  = 33,
    kCFStringEncodingMacDingbats                = 34,
    kCFStringEncodingMacTurkish                 = 35,
    kCFStringEncodingMacCroatian                = 36,
    kCFStringEncodingMacIcelandic               = 37,
    kCFStringEncodingMacRomanian                = 38,
    kCFStringEncodingMacCeltic                  = 39,
    kCFStringEncodingMacGaelic                  = 40,
    kCFStringEncodingMacFarsi                   = 0x8C,
    kCFStringEncodingMacUkrainian               = 0x98,
    kCFStringEncodingMacInuit                   = 0xEC,
    kCFStringEncodingMacVT100                   = 0xFC,
    kCFStringEncodingMacHFS                     = 0xFF,
    kCFStringEncodingISOLatin2                  = 0x0202,
    kCFStringEncodingISOLatin3                  = 0x0203,
    kCFStringEncodingISOLatin4                  = 0x0204,
    kCFStringEncodingISOLatinCyrillic           = 0x0205,
    kCFStringEncodingISOLatinArabic             = 0x0206,
    kCFStringEncodingISOLatinGreek              = 0x0207,
    kCFStringEncodingISOLatinHebrew             = 0x0208,
    kCFStringEncodingISOLatin5                  = 0x0209,
    kCFStringEncodingISOLatin6                  = 0x020A,
    kCFStringEncodingISOLatinThai               = 0x020B,
    kCFStringEncodingISOLatin7                  = 0x020D,
    kCFStringEncodingISOLatin8                  = 0x020E,
    kCFStringEncodingISOLatin9                  = 0x020F,
    kCFStringEncodingISOLatin10                 = 0x0210,
    kCFStringEncodingDOSLatinUS                 = 0x0400,
    kCFStringEncodingDOSGreek                   = 0x0405,
    kCFStringEncodingDOSBalticRim               = 0x0406,
    kCFStringEncodingDOSLatin1                  = 0x0410,
    kCFStringEncodingDOSGreek1                  = 0x0411,
    kCFStringEncodingDOSLatin2                  = 0x0412,
    kCFStringEncodingDOSCyrillic                = 0x0413,
    kCFStringEncodingDOSTurkish                 = 0x0414,
    kCFStringEncodingDOSPortuguese              = 0x0415,
    kCFStringEncodingDOSIcelandic               = 0x0416,
    kCFStringEncodingDOSHebrew                  = 0x0417,
    kCFStringEncodingDOSCanadianFrench          = 0x0418,
    kCFStringEncodingDOSArabic                  = 0x0419,
    kCFStringEncodingDOSNordic                  = 0x041A,
    kCFStringEncodingDOSRussian                 = 0x041B,
    kCFStringEncodingDOSGreek2                  = 0x041C,
    kCFStringEncodingDOSThai                    = 0x041D,
    kCFStringEncodingDOSJapanese                = 0x0420,
    kCFStringEncodingDOSChineseSimplif          = 0x0421,
    kCFStringEncodingDOSKorean                  = 0x0422,
    kCFStringEncodingDOSChineseTrad             = 0x0423,
    kCFStringEncodingWindowsLatin2              = 0x0501,
    kCFStringEncodingWindowsCyrillic            = 0x0502,
    kCFStringEncodingWindowsGreek               = 0x0503,
    kCFStringEncodingWindowsLatin5              = 0x0504,
    kCFStringEncodingWindowsHebrew              = 0x0505,
    kCFStringEncodingWindowsArabic              = 0x0506,
    kCFStringEncodingWindowsBalticRim           = 0x0507,
    kCFStringEncodingWindowsVietnamese          = 0x0508,
    kCFStringEncodingWindowsKoreanJohab         = 0x0510,
    kCFStringEncodingANSEL                      = 0x0601,
    kCFStringEncodingJIS_X0201_76               = 0x0620,
    kCFStringEncodingJIS_X0208_83               = 0x0621,
    kCFStringEncodingJIS_X0208_90               = 0x0622,
    kCFStringEncodingJIS_X0212_90               = 0x0623,
    kCFStringEncodingJIS_C6226_78               = 0x0624,
    kCFStringEncodingShiftJIS_X0213             = 0x0628,
    kCFStringEncodingShiftJIS_X0213_MenKuTen    = 0x0629,
    kCFStringEncodingGB_2312_80                 = 0x0630,
    kCFStringEncodingGBK_95                     = 0x0631,
    kCFStringEncodingGB_18030_2000              = 0x0632,
    kCFStringEncodingKSC_5601_87                = 0x0640,
    kCFStringEncodingKSC_5601_92_Johab          = 0x0641,
    kCFStringEncodingCNS_11643_92_P1            = 0x0651,
    kCFStringEncodingCNS_11643_92_P2            = 0x0652,
    kCFStringEncodingCNS_11643_92_P3            = 0x0653,
    kCFStringEncodingISO_2022_JP                = 0x0820,
    kCFStringEncodingISO_2022_JP_2              = 0x0821,
    kCFStringEncodingISO_2022_JP_1              = 0x0822,
    kCFStringEncodingISO_2022_JP_3              = 0x0823,
    kCFStringEncodingISO_2022_CN                = 0x0830,
    kCFStringEncodingISO_2022_CN_EXT            = 0x0831,
    kCFStringEncodingISO_2022_KR                = 0x0840,
    kCFStringEncodingEUC_JP                     = 0x0920,
    kCFStringEncodingEUC_CN                     = 0x0930,
    kCFStringEncodingEUC_TW                     = 0x0931,
    kCFStringEncodingEUC_KR                     = 0x0940,
    kCFStringEncodingShiftJIS                   = 0x0A01,
    kCFStringEncodingKOI8_R                     = 0x0A02,
    kCFStringEncodingBig5                       = 0x0A03,
    kCFStringEncodingMacRomanLatin1             = 0x0A04,
    kCFStringEncodingHZ_GB_2312                 = 0x0A05,
    kCFStringEncodingBig5_HKSCS_1999            = 0x0A06,
    kCFStringEncodingVISCII                     = 0x0A07,
    kCFStringEncodingKOI8_U                     = 0x0A08,
    kCFStringEncodingBig5_E                     = 0x0A09,
    kCFStringEncodingNextStepJapanese           = 0x0B02,
    kCFStringEncodingEBCDIC_US                  = 0x0C01,
    kCFStringEncodingEBCDIC_CP037               = 0x0C02,
    kCFStringEncodingUTF7                       = 0x04000100,
    kCFStringEncodingUTF7_IMAP                  = 0x0A10,
    kCFStringEncodingShiftJIS_X0213_00          = 0x0628
}
CFStringEncodings;

/*!
 * @function    CFStringGetTypeID
 * @abstract    Returns the type identifier for the CFString opaque type.
 * @result      The type identifier for the CFString opaque type.
 * @discussion  CFMutableString objects have the same type identifier as
 *              CFString objects.
 */
CF_EXPORT CFTypeID CFStringGetTypeID( void );

/*!
 * @define      CFStringMakeConstantString
 * @abstract    Creates an immutable string from a constant compile-time string.
 * @param       cp      A constant C string (that is, text enclosed in
 *                      double-quotation marks) from which the string is to be
 *                      created.
 * @result      An immutable string, or NULL if there was a problem creating the
 *              object. The returned object is a constant. You may retain and
 *              release it, similar to other immutable CFString objects, but are
 *              not required to do so—it will remain valid until the program
 *              terminates.
 * @see         CFSTR
 */
CF_EXPORT CFStringRef CFStringMakeConstantString( const char * cp );

/*!
 * @function    
 */
CF_EXPORT CFArrayRef CFStringCreateArrayBySeparatingStrings( CFAllocatorRef alloc, CFStringRef theString, CFStringRef separatorString );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateByCombiningStrings( CFAllocatorRef alloc, CFArrayRef theArray, CFStringRef separatorString );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateCopy( CFAllocatorRef alloc, CFStringRef theString );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateFromExternalRepresentation( CFAllocatorRef alloc, CFDataRef data, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithBytes( CFAllocatorRef alloc, const UInt8 * bytes, CFIndex numBytes, CFStringEncoding encoding, Boolean isExternalRepresentation );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithBytesNoCopy( CFAllocatorRef alloc, const UInt8 * bytes, CFIndex numBytes, CFStringEncoding encoding, Boolean isExternalRepresentation, CFAllocatorRef contentsDeallocator );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithCharacters( CFAllocatorRef alloc, const UniChar * chars, CFIndex numChars );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithCharactersNoCopy( CFAllocatorRef alloc, const UniChar * chars, CFIndex numChars, CFAllocatorRef contentsDeallocator );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithCString( CFAllocatorRef alloc, const char * cStr, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithCStringNoCopy( CFAllocatorRef alloc, const char * cStr, CFStringEncoding encoding, CFAllocatorRef contentsDeallocator );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithFormat( CFAllocatorRef alloc, CFDictionaryRef formatOptions, CFStringRef format, ... );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithFormatAndArguments( CFAllocatorRef alloc, CFDictionaryRef formatOptions, CFStringRef format, va_list arguments );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithPascalString( CFAllocatorRef alloc, ConstStr255Param pStr, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithPascalStringNoCopy( CFAllocatorRef alloc, ConstStr255Param pStr, CFStringEncoding encoding, CFAllocatorRef contentsDeallocator );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithSubstring( CFAllocatorRef alloc, CFStringRef str, CFRange range );

/*!
 * @function    
 */
CF_EXPORT CFArrayRef CFStringCreateArrayWithFindResults( CFAllocatorRef alloc, CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags compareOptions );

/*!
 * @function    
 */
CF_EXPORT CFRange CFStringFind( CFStringRef theString, CFStringRef stringToFind, CFStringCompareFlags compareOptions );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringFindCharacterFromSet( CFStringRef theString, CFCharacterSetRef theSet, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFRange * result );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringFindWithOptions( CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFRange * result );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringFindWithOptionsAndLocale( CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFLocaleRef locale, CFRange * result );

/*!
 * @function    
 */
CF_EXPORT void CFStringGetLineBounds( CFStringRef theString, CFRange range, CFIndex * lineBeginIndex, CFIndex * lineEndIndex, CFIndex * contentsEndIndex );

/*!
 * @function    
 */
CF_EXPORT CFComparisonResult CFStringCompare( CFStringRef theString1, CFStringRef theString2, CFStringCompareFlags compareOptions );

/*!
 * @function    
 */
CF_EXPORT CFComparisonResult CFStringCompareWithOptions( CFStringRef theString1, CFStringRef theString2, CFRange rangeToCompare, CFStringCompareFlags compareOptions );

/*!
 * @function    
 */
CF_EXPORT CFComparisonResult CFStringCompareWithOptionsAndLocale( CFStringRef theString1, CFStringRef theString2, CFRange rangeToCompare, CFStringCompareFlags compareOptions, CFLocaleRef locale );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringHasPrefix( CFStringRef theString, CFStringRef prefix );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringHasSuffix( CFStringRef theString, CFStringRef suffix );

/*!
 * @function    
 */
CF_EXPORT CFDataRef CFStringCreateExternalRepresentation( CFAllocatorRef alloc, CFStringRef theString, CFStringEncoding encoding, UInt8 lossByte );

/*!
 * @function    
 */
CF_EXPORT CFIndex CFStringGetBytes( CFStringRef theString, CFRange range, CFStringEncoding encoding, UInt8 lossByte, Boolean isExternalRepresentation, UInt8 * buffer, CFIndex maxBufLen, CFIndex * usedBufLen );

/*!
 * @function    
 */
CF_EXPORT UniChar CFStringGetCharacterAtIndex( CFStringRef theString, CFIndex idx );

/*!
 * @function    
 */
CF_EXPORT void CFStringGetCharacters( CFStringRef theString, CFRange range, UniChar * buffer );

/*!
 * @function    
 */
CF_EXPORT const UniChar * CFStringGetCharactersPtr( CFStringRef theString );

/*!
 * @function    
 */
CF_EXPORT UniChar CFStringGetCharacterFromInlineBuffer( CFStringInlineBuffer * buf, CFIndex idx );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringGetCString( CFStringRef theString, char * buffer, CFIndex bufferSize, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT const char * CFStringGetCStringPtr( CFStringRef theString, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFIndex CFStringGetLength( CFStringRef theString );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringGetPascalString( CFStringRef theString, StringPtr buffer, CFIndex bufferSize, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT ConstStringPtr CFStringGetPascalStringPtr( CFStringRef theString, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFRange CFStringGetRangeOfComposedCharactersAtIndex( CFStringRef theString, CFIndex theIndex );

/*!
 * @function    
 */
CF_EXPORT void CFStringInitInlineBuffer( CFStringRef str, CFStringInlineBuffer * buf, CFRange range );

/*!
 * @function    
 */
CF_EXPORT CFIndex CFStringGetHyphenationLocationBeforeIndex( CFStringRef string, CFIndex location, CFRange limitRange, CFOptionFlags options, CFLocaleRef locale, UTF32Char * character );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringIsHyphenationAvailableForLocale( CFLocaleRef locale );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringConvertEncodingToIANACharSetName( CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT unsigned long CFStringConvertEncodingToNSStringEncoding( CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT UInt32 CFStringConvertEncodingToWindowsCodepage( CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringEncoding CFStringConvertIANACharSetNameToEncoding( CFStringRef theString );

/*!
 * @function    
 */
CF_EXPORT CFStringEncoding CFStringConvertNSStringEncodingToEncoding( unsigned long encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringEncoding CFStringConvertWindowsCodepageToEncoding( UInt32 codepage );

/*!
 * @function    
 */
CF_EXPORT CFStringEncoding CFStringGetFastestEncoding( CFStringRef theString );

/*!
 * @function    
 */
CF_EXPORT const CFStringEncoding * CFStringGetListOfAvailableEncodings( void );

/*!
 * @function    
 */
CF_EXPORT CFIndex CFStringGetMaximumSizeForEncoding( CFIndex length, CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringEncoding CFStringGetMostCompatibleMacStringEncoding( CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringGetNameOfEncoding( CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT CFStringEncoding CFStringGetSmallestEncoding( CFStringRef theString );

/*!
 * @function    
 */
CF_EXPORT CFStringEncoding CFStringGetSystemEncoding( void );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringIsEncodingAvailable( CFStringEncoding encoding );

/*!
 * @function    
 */
CF_EXPORT double CFStringGetDoubleValue( CFStringRef str );

/*!
 * @function    
 */
CF_EXPORT SInt32 CFStringGetIntValue( CFStringRef str );

/*!
 * @function    
 */
CF_EXPORT void CFShowStr( CFStringRef str );

/*!
 * @function    
 */
CF_EXPORT CFStringRef CFStringCreateWithFileSystemRepresentation( CFAllocatorRef alloc, const char * buffer );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringGetFileSystemRepresentation( CFStringRef string, char * buffer, CFIndex maxBufLen );

/*!
 * @function    
 */
CF_EXPORT CFIndex CFStringGetMaximumSizeOfFileSystemRepresentation( CFStringRef string );

/*!
 * @function    
 */
CF_EXPORT void CFStringGetParagraphBounds( CFStringRef string, CFRange range, CFIndex * parBeginIndex, CFIndex * parEndIndex, CFIndex * contentsEndIndex );

/*!
 * @function    
 */
CF_EXPORT UTF32Char CFStringGetLongCharacterForSurrogatePair( UniChar surrogateHigh, UniChar surrogateLow );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringGetSurrogatePairForLongCharacter( UTF32Char character, UniChar * surrogates );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringIsSurrogateHighCharacter( UniChar character );

/*!
 * @function    
 */
CF_EXPORT Boolean CFStringIsSurrogateLowCharacter( UniChar character );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_STRING_H */
