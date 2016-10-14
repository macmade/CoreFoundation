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

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFString.h>
#include <CoreFoundation/__private/CFRuntime.h>
#include <string.h>
#include <stdio.h>

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFStringTypeID = CFRuntimeRegisterClass( &CFStringClass );
}

CFTypeID CFStringGetTypeID( void )
{
    return CFStringTypeID;
}

CFArrayRef CFStringCreateArrayBySeparatingStrings( CFAllocatorRef alloc, CFStringRef theString, CFStringRef separatorString )
{
    ( void )alloc;
    ( void )theString;
    ( void )separatorString;
    
    return NULL;
}

CFStringRef CFStringCreateByCombiningStrings( CFAllocatorRef alloc, CFArrayRef theArray, CFStringRef separatorString )
{
    ( void )alloc;
    ( void )theArray;
    ( void )separatorString;
    
    return NULL;
}

CFStringRef CFStringCreateCopy( CFAllocatorRef alloc, CFStringRef theString )
{
    return CFStringCreateWithCString( alloc, theString->_cStr, theString->_encoding );
}

CFStringRef CFStringCreateFromExternalRepresentation( CFAllocatorRef alloc, CFDataRef data, CFStringEncoding encoding )
{
    ( void )alloc;
    ( void )data;
    ( void )encoding;
    
    return NULL;
}

CFStringRef CFStringCreateWithBytes( CFAllocatorRef alloc, const UInt8 * bytes, CFIndex numBytes, CFStringEncoding encoding, Boolean isExternalRepresentation )
{
    ( void )alloc;
    ( void )bytes;
    ( void )numBytes;
    ( void )encoding;
    ( void )isExternalRepresentation;
    
    return NULL;
}

CFStringRef CFStringCreateWithBytesNoCopy( CFAllocatorRef alloc, const UInt8 * bytes, CFIndex numBytes, CFStringEncoding encoding, Boolean isExternalRepresentation, CFAllocatorRef contentsDeallocator )
{
    ( void )alloc;
    ( void )bytes;
    ( void )numBytes;
    ( void )encoding;
    ( void )isExternalRepresentation;
    ( void )contentsDeallocator;
    
    return NULL;
}

CFStringRef CFStringCreateWithCharacters( CFAllocatorRef alloc, const UniChar * chars, CFIndex numChars )
{
    ( void )alloc;
    ( void )chars;
    ( void )numChars;
    
    return NULL;
}

CFStringRef CFStringCreateWithCharactersNoCopy( CFAllocatorRef alloc, const UniChar * chars, CFIndex numChars, CFAllocatorRef contentsDeallocator )
{
    ( void )alloc;
    ( void )chars;
    ( void )numChars;
    ( void )contentsDeallocator;
    
    return NULL;
}

CFStringRef CFStringCreateWithCString( CFAllocatorRef alloc, const char * cStr, CFStringEncoding encoding )
{
    struct CFString * o;
    char            * buf;
    
    if( cStr == NULL )
    {
        return NULL;
    }
    
    o = ( struct CFString * )CFRuntimeCreateInstance( alloc, CFStringTypeID );
    
    if( o )
    {
        o->_deallocator = ( alloc ) ? CFRetain( alloc ) : NULL;
        o->_length      = ( CFIndex )strlen( cStr );
        o->_encoding    = encoding;
        buf             = CFAllocatorAllocate( alloc, o->_length + 1, 0 );
        
        if( buf == NULL )
        {
            CFRelease( o );
            CFRuntimeAbortWithOutOfMemoryError();
            
            return NULL;
        }
        
        memcpy( buf, cStr, o->_length + 1 );
        
        o->_cStr = buf;
    }
    
    return ( CFStringRef )o;
}

CFStringRef CFStringCreateWithCStringNoCopy( CFAllocatorRef alloc, const char * cStr, CFStringEncoding encoding, CFAllocatorRef contentsDeallocator )
{
    struct CFString * o;
    
    if( cStr == NULL )
    {
        return NULL;
    }
    
    o = ( struct CFString * )CFRuntimeCreateInstance( alloc, CFStringTypeID );
    
    if( o )
    {
        o->_cStr        = cStr;
        o->_encoding    = encoding;
        o->_length      = ( CFIndex )strlen( cStr );
        o->_deallocator = ( contentsDeallocator ) ? CFRetain( contentsDeallocator ) : NULL;
    }
    
    return ( CFStringRef )o;
}

CFStringRef CFStringCreateWithFormat( CFAllocatorRef alloc, CFDictionaryRef formatOptions, CFStringRef format, ... )
{
    va_list     ap;
    CFStringRef o;
    
    va_start( ap, format );
    
    o = CFStringCreateWithFormatAndArguments( alloc, formatOptions, format, ap );
    
    va_end( ap );
    
    return o;
}

CFStringRef CFStringCreateWithFormatAndArguments( CFAllocatorRef alloc, CFDictionaryRef formatOptions, CFStringRef format, va_list arguments )
{
    char  * fmt;
    char  * str;
    va_list ap;
    int     length;
    
    ( void )formatOptions;
    
    if( format == NULL || CFStringGetLength( format ) == 0 )
    {
        return NULL;
    }
    
    fmt = CFAllocatorAllocate( alloc, CFStringGetLength( format ) + 1, 0 );
    
    if( fmt == NULL )
    {
        CFRuntimeAbortWithOutOfMemoryError();
        
        return NULL;
    }
    
    if( CFStringGetCString( format, fmt, CFStringGetLength( format ) + 1, kCFStringEncodingUTF8 ) == false )
    {
        CFAllocatorDeallocate( alloc, fmt );
        
        return NULL;
    }
    
    va_copy( ap, arguments );
    
    length = vsnprintf( NULL, 0, fmt, arguments );
    
    if( length <= 0 )
    {
        va_end( ap );
        CFAllocatorDeallocate( alloc, fmt );
        
        return NULL;
    }
    
    str = CFAllocatorAllocate( alloc, length + 1, 0 );
    
    if( str == NULL )
    {
        va_end( ap );
        CFAllocatorDeallocate( alloc, fmt );
        CFRuntimeAbortWithOutOfMemoryError();
        
        return NULL;
    }
    
    vsnprintf( str, length + 1, fmt, ap );
    va_end( ap );
    CFAllocatorDeallocate( alloc, fmt );
    
    return CFStringCreateWithCStringNoCopy( alloc, str, kCFStringEncodingUTF8, alloc );
}

CFStringRef CFStringCreateWithPascalString( CFAllocatorRef alloc, ConstStr255Param pStr, CFStringEncoding encoding )
{
    ( void )alloc;
    ( void )pStr;
    ( void )encoding;
    
    return NULL;
}

CFStringRef CFStringCreateWithPascalStringNoCopy( CFAllocatorRef alloc, ConstStr255Param pStr, CFStringEncoding encoding, CFAllocatorRef contentsDeallocator )
{
    ( void )alloc;
    ( void )pStr;
    ( void )encoding;
    ( void )contentsDeallocator;
    
    return NULL;
}

CFStringRef CFStringCreateWithSubstring( CFAllocatorRef alloc, CFStringRef str, CFRange range )
{
    ( void )alloc;
    ( void )str;
    ( void )range;
    
    return NULL;
}

CFArrayRef CFStringCreateArrayWithFindResults( CFAllocatorRef alloc, CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags compareOptions )
{
    ( void )alloc;
    ( void )theString;
    ( void )stringToFind;
    ( void )rangeToSearch;
    ( void )compareOptions;
    
    return NULL;
}

CFRange CFStringFind( CFStringRef theString, CFStringRef stringToFind, CFStringCompareFlags compareOptions )
{
    ( void )theString;
    ( void )stringToFind;
    ( void )compareOptions;
    
    return CFRangeMake( 0, 0 );
}

Boolean CFStringFindCharacterFromSet( CFStringRef theString, CFCharacterSetRef theSet, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFRange * result )
{
    ( void )theString;
    ( void )theSet;
    ( void )rangeToSearch;
    ( void )searchOptions;
    ( void )result;
    
    return false;
}

Boolean CFStringFindWithOptions( CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFRange * result )
{
    ( void )theString;
    ( void )stringToFind;
    ( void )rangeToSearch;
    ( void )searchOptions;
    ( void )result;
    
    return false;
}

Boolean CFStringFindWithOptionsAndLocale( CFStringRef theString, CFStringRef stringToFind, CFRange rangeToSearch, CFStringCompareFlags searchOptions, CFLocaleRef locale, CFRange * result )
{
    ( void )theString;
    ( void )stringToFind;
    ( void )rangeToSearch;
    ( void )searchOptions;
    ( void )locale;
    ( void )result;
    
    return false;
}

void CFStringGetLineBounds( CFStringRef theString, CFRange range, CFIndex * lineBeginIndex, CFIndex * lineEndIndex, CFIndex * contentsEndIndex )
{
    ( void )theString;
    ( void )range;
    ( void )lineBeginIndex;
    ( void )lineEndIndex;
    ( void )contentsEndIndex;
}

CFComparisonResult CFStringCompare( CFStringRef theString1, CFStringRef theString2, CFStringCompareFlags compareOptions )
{
    ( void )theString1;
    ( void )theString2;
    ( void )compareOptions;
    
    return kCFCompareEqualTo;
}

CFComparisonResult CFStringCompareWithOptions( CFStringRef theString1, CFStringRef theString2, CFRange rangeToCompare, CFStringCompareFlags compareOptions )
{
    ( void )theString1;
    ( void )theString2;
    ( void )rangeToCompare;
    ( void )compareOptions;
    
    return kCFCompareEqualTo;
}

CFComparisonResult CFStringCompareWithOptionsAndLocale( CFStringRef theString1, CFStringRef theString2, CFRange rangeToCompare, CFStringCompareFlags compareOptions, CFLocaleRef locale )
{
    ( void )theString1;
    ( void )theString2;
    ( void )rangeToCompare;
    ( void )compareOptions;
    ( void )locale;
    
    return kCFCompareEqualTo;
}

Boolean CFStringHasPrefix( CFStringRef theString, CFStringRef prefix )
{
    ( void )theString;
    ( void )prefix;
    
    return false;
}

Boolean CFStringHasSuffix( CFStringRef theString, CFStringRef suffix )
{
    ( void )theString;
    ( void )suffix;
    
    return false;
}

CFDataRef CFStringCreateExternalRepresentation( CFAllocatorRef alloc, CFStringRef theString, CFStringEncoding encoding, UInt8 lossByte )
{
    ( void )alloc;
    ( void )theString;
    ( void )encoding;
    ( void )lossByte;
    
    return NULL;
}

CFIndex CFStringGetBytes( CFStringRef theString, CFRange range, CFStringEncoding encoding, UInt8 lossByte, Boolean isExternalRepresentation, UInt8 * buffer, CFIndex maxBufLen, CFIndex * usedBufLen )
{
    ( void )theString;
    ( void )range;
    ( void )encoding;
    ( void )lossByte;
    ( void )isExternalRepresentation;
    ( void )buffer;
    ( void )maxBufLen;
    ( void )usedBufLen;
    
    return 0;
}

UniChar CFStringGetCharacterAtIndex( CFStringRef theString, CFIndex idx )
{
    ( void )theString;
    ( void )idx;
    
    return 0;
}

void CFStringGetCharacters( CFStringRef theString, CFRange range, UniChar * buffer )
{
    ( void )theString;
    ( void )range;
    ( void )buffer;
}

const UniChar * CFStringGetCharactersPtr( CFStringRef theString )
{
    ( void )theString;
    
    return NULL;
}

UniChar CFStringGetCharacterFromInlineBuffer( CFStringInlineBuffer * buf, CFIndex idx )
{
    ( void )buf;
    ( void )idx;
    
    return 0;
}

Boolean CFStringGetCString( CFStringRef theString, char * buffer, CFIndex bufferSize, CFStringEncoding encoding )
{
    if( theString == NULL || buffer == NULL || bufferSize == 0 )
    {
        return false;
    }
    
    if( bufferSize < theString->_length + 1 )
    {
        return false;
    }
    
    if( theString->_encoding != encoding )
    {
        return false;
    }
    
    memcpy( buffer, theString->_cStr, theString->_length + 1 );
    
    return true;
}

const char * CFStringGetCStringPtr( CFStringRef theString, CFStringEncoding encoding )
{
    if( theString == NULL || theString->_encoding != encoding )
    {
        return NULL;
    }
    
    return theString->_cStr;
}

CFIndex CFStringGetLength( CFStringRef theString )
{
    if( theString == NULL )
    {
        return 0;
    }
    
    return theString->_length;
}

Boolean CFStringGetPascalString( CFStringRef theString, StringPtr buffer, CFIndex bufferSize, CFStringEncoding encoding )
{
    ( void )theString;
    ( void )buffer;
    ( void )bufferSize;
    ( void )encoding;
    
    return false;
}

ConstStringPtr CFStringGetPascalStringPtr( CFStringRef theString, CFStringEncoding encoding )
{
    ( void )theString;
    ( void )encoding;
    
    return NULL;
}

CFRange CFStringGetRangeOfComposedCharactersAtIndex( CFStringRef theString, CFIndex theIndex )
{
    ( void )theString;
    ( void )theIndex;
    
    return CFRangeMake( kCFNotFound, 0 );
}

void CFStringInitInlineBuffer( CFStringRef str, CFStringInlineBuffer * buf, CFRange range )
{
    ( void )str;
    ( void )buf;
    ( void )range;
}

CFIndex CFStringGetHyphenationLocationBeforeIndex( CFStringRef string, CFIndex location, CFRange limitRange, CFOptionFlags options, CFLocaleRef locale, UTF32Char * character )
{
    ( void )string;
    ( void )location;
    ( void )limitRange;
    ( void )options;
    ( void )locale;
    ( void )character;
    
    return 0;
}

Boolean CFStringIsHyphenationAvailableForLocale( CFLocaleRef locale )
{
    ( void )locale;
    
    return false;
}

CFStringRef CFStringConvertEncodingToIANACharSetName( CFStringEncoding encoding )
{
    ( void )encoding;
    
    return NULL;
}

unsigned long CFStringConvertEncodingToNSStringEncoding( CFStringEncoding encoding )
{
    ( void )encoding;
    
    return 0;
}

UInt32 CFStringConvertEncodingToWindowsCodepage( CFStringEncoding encoding )
{
    ( void )encoding;
    
    return 0;
}

CFStringEncoding CFStringConvertIANACharSetNameToEncoding( CFStringRef theString )
{
    ( void )theString;
    
    return kCFStringEncodingUTF8;
}

CFStringEncoding CFStringConvertNSStringEncodingToEncoding( unsigned long encoding )
{
    ( void )encoding;
    
    return kCFStringEncodingUTF8;
}

CFStringEncoding CFStringConvertWindowsCodepageToEncoding( UInt32 codepage )
{
    ( void )codepage;
    
    return kCFStringEncodingUTF8;
}

CFStringEncoding CFStringGetFastestEncoding( CFStringRef theString )
{
    ( void )theString;
    
    return kCFStringEncodingUTF8;
}

const CFStringEncoding * CFStringGetListOfAvailableEncodings( void )
{
    return NULL;
}

CFIndex CFStringGetMaximumSizeForEncoding( CFIndex length, CFStringEncoding encoding )
{
    ( void )length;
    ( void )encoding;
    
    return 0;
}

CFStringEncoding CFStringGetMostCompatibleMacStringEncoding( CFStringEncoding encoding )
{
    ( void )encoding;
    
    return kCFStringEncodingUTF8;
}

CFStringRef CFStringGetNameOfEncoding( CFStringEncoding encoding )
{
    ( void )encoding;
    
    return NULL;
}

CFStringEncoding CFStringGetSmallestEncoding( CFStringRef theString )
{
    ( void )theString;
    
    return kCFStringEncodingUTF8;
}

CFStringEncoding CFStringGetSystemEncoding( void )
{
    return kCFStringEncodingUTF8;
}

Boolean CFStringIsEncodingAvailable( CFStringEncoding encoding )
{
    ( void )encoding;
    
    return false;
}

double CFStringGetDoubleValue( CFStringRef str )
{
    ( void )str;
    
    return 0.0;
}

SInt32 CFStringGetIntValue( CFStringRef str )
{
    ( void )str;
    
    return 0;
}

void CFShowStr( CFStringRef str )
{
    ( void )str;
}

CFStringRef CFStringCreateWithFileSystemRepresentation( CFAllocatorRef alloc, const char * buffer )
{
    ( void )alloc;
    ( void )buffer;
    
    return NULL;
}

Boolean CFStringGetFileSystemRepresentation( CFStringRef string, char * buffer, CFIndex maxBufLen )
{
    ( void )string;
    ( void )buffer;
    ( void )maxBufLen;
    
    return false;
}

CFIndex CFStringGetMaximumSizeOfFileSystemRepresentation( CFStringRef string )
{
    ( void )string;
    
    return 0;
}

void CFStringGetParagraphBounds( CFStringRef string, CFRange range, CFIndex * parBeginIndex, CFIndex * parEndIndex, CFIndex * contentsEndIndex )
{
    ( void )string;
    ( void )range;
    ( void )parBeginIndex;
    ( void )parEndIndex;
    ( void )contentsEndIndex;
}

UTF32Char CFStringGetLongCharacterForSurrogatePair( UniChar surrogateHigh, UniChar surrogateLow )
{
    ( void )surrogateHigh;
    ( void )surrogateLow;
    
    return 0;
}

Boolean CFStringGetSurrogatePairForLongCharacter( UTF32Char character, UniChar * surrogates )
{
    ( void )character;
    ( void )surrogates;
    
    return false;
}

Boolean CFStringIsSurrogateHighCharacter( UniChar character )
{
    ( void )character;
    
    return false;
}

Boolean CFStringIsSurrogateLowCharacter( UniChar character )
{
    ( void )character;
    
    return false;
}
