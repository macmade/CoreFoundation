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

int main( void )
{
    {
        CFAllocatorRef     a;
        CFAllocatorContext ctx;
        
        memset( &ctx, 0, sizeof( CFAllocatorContext ) );
        printf( "kCFAllocatorSystemDefault: %p (ID: %li / RC: %li)\n", ( void * )kCFAllocatorSystemDefault, ( long )CFGetTypeID( kCFAllocatorSystemDefault ), ( long )CFGetRetainCount( kCFAllocatorSystemDefault ) );
        
        a = CFAllocatorCreate( NULL, &ctx );
        
        printf( "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        printf( "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        CFRetain( a );
        printf( "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        CFRelease( a );
        printf( "Custom allocator:          %p (ID: %li / RC: %li)\n", ( void * )a, ( long )CFGetTypeID( a ), ( long )CFGetRetainCount( a ) );
        CFRelease( a );
    }
    
    printf( "--------------------------------------------------------------------------------\n" );
    
    {
        CFStringRef s1;
        CFStringRef s2;
        
        s1 = CFStringCreateWithCString( NULL, "hello, %s", kCFStringEncodingUTF8 );
        s2 = CFStringCreateWithFormat( NULL, NULL, s1, "universe" );
            
        printf( "%p - %s\n", ( void * )s1, CFStringGetCStringPtr( s1, kCFStringEncodingUTF8 ) );
        printf( "%p - %s\n", ( void * )s2, CFStringGetCStringPtr( s2, kCFStringEncodingUTF8 ) );
        
        CFShow( NULL );
        CFShow( kCFAllocatorSystemDefault );
        CFShow( s1 );
        CFShow( s2 );
        
        CFRelease( s1 );
        CFRelease( s2 );
    }
    
    printf( "--------------------------------------------------------------------------------\n" );
    
    {
        CFShow( kCFNull );
    }
    
    printf( "--------------------------------------------------------------------------------\n" );
    
    return 0;
}
