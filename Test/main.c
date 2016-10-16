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
 * @file        main.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <stdio.h>
#include <string.h>
#include "Foo.h"

int main( void )
{
    {
        CFAllocatorRef     a;
        CFAllocatorContext ctx;
        
        memset( &ctx, 0, sizeof( CFAllocatorContext ) );
        fprintf( stderr,  "kCFAllocatorSystemDefault: %p (ID: %li / RC: %li)\n", ( void * )kCFAllocatorSystemDefault, ( long )CFGetTypeID( kCFAllocatorSystemDefault ), ( long )CFGetRetainCount( kCFAllocatorSystemDefault ) );
        
        a = CFAllocatorCreate( NULL, &ctx );
        
        fprintf( stderr,  "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        fprintf( stderr,  "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        CFRetain( a );
        fprintf( stderr,  "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        CFRelease( a );
        fprintf( stderr,  "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        CFRelease( a );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFStringRef s1;
        CFStringRef s2;
        CFStringRef s3;
        
        s1 = CFStringCreateWithCString( NULL, "hello, %s", kCFStringEncodingASCII );
        s2 = CFStringCreateWithFormat( NULL, NULL, s1, "universe" );
        s3 = CFStringCreateCopy( NULL, s2 );
            
        fprintf( stderr,  "%p - %s\n", ( void * )s1, CFStringGetCStringPtr( s1, kCFStringEncodingASCII ) );
        fprintf( stderr,  "%p - %s\n", ( void * )s2, CFStringGetCStringPtr( s2, kCFStringEncodingASCII ) );
        fprintf( stderr,  "%p - %s\n", ( void * )s3, CFStringGetCStringPtr( s3, kCFStringEncodingASCII ) );
        
        CFShowStr( s1 );
        CFShowStr( s2 );
        CFShowStr( s3 );
        
        CFShow( NULL );
        CFShow( kCFAllocatorSystemDefault );
        CFShow( s1 );
        CFShow( s2 );
        CFShow( s3 );
        
        fprintf
        (
            stderr,
            "%s == %s : %i\n",
            CFStringGetCStringPtr( s1, kCFStringEncodingASCII ),
            CFStringGetCStringPtr( s2, kCFStringEncodingASCII ),
            CFEqual( s1, s2 )
        );
        fprintf
        (
            stderr,
            "%s == %s : %i\n",
            CFStringGetCStringPtr( s2, kCFStringEncodingASCII ),
            CFStringGetCStringPtr( s3, kCFStringEncodingASCII ),
            CFEqual( s2, s3 )
        );
        
        CFRelease( s1 );
        CFRelease( s2 );
        CFRelease( s3 );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFShow( kCFNull );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFShow( kCFBooleanTrue );
        CFShow( kCFBooleanFalse );
        
        fprintf( stderr,  "kCFBooleanTrue:  %i\n", CFBooleanGetValue( kCFBooleanTrue ) );
        fprintf( stderr,  "kCFBooleanFalse: %i\n", CFBooleanGetValue( kCFBooleanFalse ) );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        unsigned int i;
        UInt8        buf[ 256 ];
        CFDataRef    d1;
        CFDataRef    d2;
        CFDataRef    d3;
        CFDataRef    d4;
        
        for( i = 0; i < sizeof( buf ); i++ )
        {
            buf[ i ] = ( UInt8 )i;
        }
        
        d1 = CFDataCreate( NULL, buf, sizeof( buf ) );
        d2 = CFDataCreateWithBytesNoCopy( NULL, buf, sizeof( buf ), kCFAllocatorNull );
        d3 = CFDataCreateCopy( NULL, d1 );
        d4 = CFDataCreateCopy( NULL, d2 );
        
        CFShow( d1 );
        CFShow( d2 );
        CFShow( d3 );
        CFShow( d4 );
        
        buf[ 42 ] = 0;
        
        fprintf( stderr, "Equals: %i\n", CFEqual( d1, d2 ) );
        fprintf( stderr, "Equals: %i\n", CFEqual( d1, d3 ) );
        
        CFRelease( d1 );
        CFRelease( d2 );
        CFRelease( d3 );
        CFRelease( d4 );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFDictionaryRef d1;
        CFDictionaryRef d2;
        CFStringRef     s1;
        CFStringRef     s2;
        CFStringRef     s3;
        CFStringRef     s4;
        const void    * k1[ 2 ];
        const void    * v1[ 2 ];
        const void    * k2[ 2 ];
        const void    * v2[ 2 ];
        
        k1[ 0 ] = "foo";
        k1[ 1 ] = "bar";
        v1[ 0 ] = "hello, world";
        v1[ 1 ] = "hello, universe";
        
        s1 = CFStringCreateWithCString( NULL, k1[ 0 ], kCFStringEncodingASCII );
        s2 = CFStringCreateWithCString( NULL, k1[ 1 ], kCFStringEncodingASCII );
        s3 = CFStringCreateWithCString( NULL, v1[ 0 ], kCFStringEncodingASCII );
        s4 = CFStringCreateWithCString( NULL, v1[ 1 ], kCFStringEncodingASCII );
        
        k2[ 0 ] = s1;
        k2[ 1 ] = s2;
        v2[ 0 ] = s3;
        v2[ 1 ] = s4;
        
        d1 = CFDictionaryCreate( NULL, k1, v1, 2, NULL, NULL );
        d2 = CFDictionaryCreate( NULL, k2, v2, 2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
        
        CFShow( d1 );
        CFShow( d2 );
        
        fprintf( stderr,  "%s: %s\n", ( char * )k1[ 0 ], ( char * )CFDictionaryGetValue( d1, k1[ 0 ] ) );
        fprintf( stderr,  "%s: %s\n", ( char * )k1[ 1 ], ( char * )CFDictionaryGetValue( d1, k1[ 1 ] ) );
        
        CFShow( CFDictionaryGetValue( d2, k2[ 0 ] ) );
        CFShow( CFDictionaryGetValue( d2, k2[ 1 ] ) );
        
        CFRelease( s1 );
        CFRelease( s2 );
        CFRelease( s3 );
        CFRelease( s4 );
        
        CFRelease( d1 );
        CFRelease( d2 );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFStringRef            s1;
        CFStringRef            s2;
        CFStringRef            s3;
        CFMutableDictionaryRef d1;
        CFMutableDictionaryRef d2;
        CFDictionaryRef        d3;
        
        s1 = CFStringCreateWithCString( NULL, "foo", kCFStringEncodingASCII );
        s2 = CFStringCreateWithCString( NULL, "bar", kCFStringEncodingASCII );
        s3 = CFStringCreateCopy( NULL, s1 );
        
        d1 = CFDictionaryCreateMutable( NULL, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
        
        CFDictionaryAddValue( d1, s1, s2 );
        CFDictionaryAddValue( d1, s2, s1 );
        CFShow( d1 );
        CFDictionaryAddValue( d1, s3, s2 );
        CFShow( d1 );
        
        d2 = CFDictionaryCreateMutableCopy( NULL, 0, d1 );
        
        CFShow( d2 );
        fprintf( stderr, "Equals: %i\n", CFEqual( d1, d2 ) );
        CFDictionarySetValue( d2, s1, s1 );
        CFShow( d2 );
        fprintf( stderr, "Equals: %i\n", CFEqual( d1, d2 ) );
        
        d3 = CFDictionaryCreateCopy( NULL, d2 );
        
        CFShow( d3 );
        
        CFRelease( s1 );
        CFRelease( s2 );
        CFRelease( s3 );
        CFRelease( d1 );
        CFRelease( d2 );
        CFRelease( d3 );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFStringRef        s1;
        CFStringRef        s2;
        CFMutableStringRef s3;
        CFMutableStringRef s4;
        
        s1 = CFStringCreateWithCString( NULL, "hello", kCFStringEncodingASCII );
        s2 = CFStringCreateWithCString( NULL, ", world", kCFStringEncodingASCII );
        s3 = CFStringCreateMutable( NULL, 0 );
        s4 = CFStringCreateMutableCopy( NULL, 0, s1 );
        
        CFShow( s1 );
        CFShow( s2 );
        CFShow( s3 );
        CFShow( s4 );
        
        CFStringAppendCString( s3, "hello", kCFStringEncodingASCII );
        CFShow( s3 );
        
        CFStringAppend( s3, s2 );
        CFStringAppend( s4, s2 );
        CFShow( s3 );
        CFShow( s4 );
        
        CFRelease( s1 );
        CFRelease( s2 );
        CFRelease( s3 );
        CFRelease( s4 );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFShow( CFSTR( "hello, world" ) );
        CFShow( CFSTR( "hello, universe" ) );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFStringRef  leak;
        volatile int i;
        
        i    = 0;
        leak = CFStringCreateWithCString( NULL, "hello, world", kCFStringEncodingASCII );
        
        fprintf( stderr, "This should be reported as a memory leak:\n" );
        CFShow( leak );
        
        if( i )
        {
            CFRelease( leak );
        }
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFShow( kCFErrorDomainPOSIX );
        CFShow( kCFErrorDescriptionKey );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFMutableDictionaryRef info;
        CFErrorRef             e1;
        CFErrorRef             e2;
        CFErrorRef             e3;
        
        info = CFDictionaryCreateMutable( NULL, 0, &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks );
        
        e1 = CFErrorCreate( NULL, kCFErrorDomainPOSIX, 42, NULL );
        
        CFDictionaryAddValue( info, kCFErrorLocalizedFailureReasonKey, CFSTR( "Unknown error" ) );
        
        e2 = CFErrorCreate( NULL, kCFErrorDomainOSStatus, -1, info );
        
        CFDictionaryAddValue( info, kCFErrorLocalizedDescriptionKey, CFSTR( "An error occured" ) );
        
        e3 = CFErrorCreate( NULL, kCFErrorDomainOSStatus, -1, info );
        
        CFShow( e1 );
        CFShow( e2 );
        CFShow( e3 );
        
        CFRelease( info );
        CFRelease( e1 );
        CFRelease( e2 );
        CFRelease( e3 );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        FooRef foo;
        
        foo = FooCreate( CFSTR( "hello, world" ) );
        
        CFShow( foo );
        CFShow( FooGetString( foo ) );
        CFRelease( foo );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFNotificationCenterRef local;
        CFNotificationCenterRef darwin;
        CFNotificationCenterRef distributed;
        
        local       = CFNotificationCenterGetLocalCenter();
        darwin      = CFNotificationCenterGetDarwinNotifyCenter();
        distributed = CFNotificationCenterGetDistributedCenter();
        
        CFShow( local );
        CFShow( darwin );
        CFShow( distributed );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    {
        CFUUIDRef   u1;
        CFUUIDRef   u2;
        CFStringRef s;
        
        s  = CFSTR( "68753A44-4D6F-1226-9C60-0050E4C00067" );
        u1 = CFUUIDCreate( NULL );
        u2 = CFUUIDCreateFromString( NULL, s );
        
        CFShow( u1 );
        CFShow( s );
        CFShow( u2 );
        
        CFRelease( u1 );
        CFRelease( u2 );
    }
    
    fprintf( stderr,  "--------------------------------------------------------------------------------\n" );
    
    return 0;
}
