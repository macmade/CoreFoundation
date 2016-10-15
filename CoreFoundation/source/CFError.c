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
 * @file        CFError.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFError.h>
#include <CoreFoundation/__private/CFString.h>
#include <stdlib.h>

CF_STRING_CONST_DECL( kCFErrorDomainPOSIX,      "NSPOSIXErrorDomain" );
CF_STRING_CONST_DECL( kCFErrorDomainOSStatus,   "NSOSStatusErrorDomain" );
CF_STRING_CONST_DECL( kCFErrorDomainMach,       "NSMachErrorDomain" );
CF_STRING_CONST_DECL( kCFErrorDomainCocoa,      "NSCocoaErrorDomain" );

CF_STRING_CONST_DECL( kCFErrorLocalizedDescriptionKey,          "NSLocalizedDescription" );
CF_STRING_CONST_DECL( kCFErrorLocalizedFailureReasonKey,        "NSLocalizedFailureReason" );
CF_STRING_CONST_DECL( kCFErrorLocalizedRecoverySuggestionKey,   "NSLocalizedRecoverySuggestion" );
CF_STRING_CONST_DECL( kCFErrorDescriptionKey,                   "NSDescription" );
CF_STRING_CONST_DECL( kCFErrorUnderlyingErrorKey,               "NSUnderlyingError" );
CF_STRING_CONST_DECL( kCFErrorURLKey,                           "NSURL" );
CF_STRING_CONST_DECL( kCFErrorFilePathKey,                      "NSFilePath" );

CFTypeID CFErrorGetTypeID( void )
{
    return CFErrorTypeID;
}

CFErrorRef CFErrorCreate( CFAllocatorRef allocator, CFErrorDomain domain, CFIndex code, CFDictionaryRef userInfo )
{
    struct CFError * o;
    
    o = ( struct CFError * )CFRuntimeCreateInstance( allocator, CFErrorTypeID );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    o->_code = code;
    
    if( domain )
    {
        o->_domain = CFRetain( domain );
    }
    
    if( userInfo )
    {
        o->_userInfo = CFDictionaryCreateCopy( allocator, userInfo );
    }
    
    return o;
}

CFErrorRef CFErrorCreateWithUserInfoKeysAndValues( CFAllocatorRef allocator, CFErrorDomain domain, CFIndex code, const void * const * userInfoKeys, const void * const * userInfoValues, CFIndex numUserInfoValues )
{
    CFDictionaryRef d;
    
    if( userInfoKeys && userInfoValues && numUserInfoValues > 0 )
    {
        d = CFDictionaryCreate
        (
            allocator,
            ( const void ** )userInfoKeys,
            ( const void ** )userInfoValues,
            numUserInfoValues,
            &kCFCopyStringDictionaryKeyCallBacks,
            &kCFTypeDictionaryValueCallBacks
        );
    }
    else
    {
        d = NULL;
    }
    
    return CFErrorCreate( allocator, domain, code, d );
}

CFErrorDomain CFErrorGetDomain( CFErrorRef err )
{
    if( err == NULL )
    {
        return NULL;
    }
    
    return err->_domain;
}

CFIndex CFErrorGetCode( CFErrorRef err )
{
    if( err == NULL )
    {
        return 0;
    }
    
    return err->_code;
}

CFDictionaryRef CFErrorCopyUserInfo( CFErrorRef err )
{
    if( err == NULL )
    {
        return NULL;
    }
    
    return CFDictionaryCreateCopy( NULL, err->_userInfo );
}

CFStringRef CFErrorCopyDescription( CFErrorRef err )
{
    CFStringRef        s;
    CFMutableStringRef m;
    
    if( err == NULL )
    {
        return CFSTR( "Unknown/Invalid error" );
    }
    
    s = CFDictionaryGetValue( err->_userInfo, kCFErrorLocalizedDescriptionKey );
    
    if( s != NULL )
    {
        return CFStringCreateCopy( NULL, s );
    }
    
    m = CFStringCreateMutable( NULL, 0 );
    s = CFDictionaryGetValue( err->_userInfo, kCFErrorLocalizedFailureReasonKey );
    
    CFStringAppend( m, CFSTR( "Operation could not be completed: " ) );
    
    if( s != NULL )
    {
        CFStringAppend( m , s );
    }
    else
    {
        CFStringAppendFormat( m, NULL, CFSTR( "code %li" ), err->_code );
        
        if( err->_domain )
        {
            CFStringAppend( m, CFSTR( " / " ) );
            CFStringAppend( m, err->_domain );
        }
    }
    
    s = CFStringCreateCopy( NULL, m );
    
    CFRelease( m );
    
    return s;
}

CFStringRef CFErrorCopyFailureReason( CFErrorRef err )
{
    CFStringRef s;
    
    if( err == NULL || err->_userInfo == NULL )
    {
        return NULL;
    }
    
    s = CFDictionaryGetValue( err->_userInfo, kCFErrorLocalizedFailureReasonKey );
    
    if( s == NULL )
    {
        return NULL;
    }
    
    return CFStringCreateCopy( NULL, s );
}

CFStringRef CFErrorCopyRecoverySuggestion( CFErrorRef err )
{
    CFStringRef s;
    
    if( err == NULL || err->_userInfo == NULL )
    {
        return NULL;
    }
    
    s = CFDictionaryGetValue( err->_userInfo, kCFErrorLocalizedRecoverySuggestionKey );
    
    if( s == NULL )
    {
        return NULL;
    }
    
    return CFStringCreateCopy( NULL, s );
}
