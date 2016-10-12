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
 * @file        CFType.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>
#include <CoreFoundation/__private/CFAtomic.h>
#include <stdlib.h>
#include <stdio.h>

CFAllocatorRef CFGetAllocator( CFTypeRef obj )
{
    CFRuntimeBase * base;
    
    if( obj == NULL )
    {
        return NULL;
    }
    
    base = ( CFRuntimeBase * )obj;
    
    return base->allocator;
}

CFIndex CFGetRetainCount( CFTypeRef obj )
{
    CFRuntimeBase * base;
    
    if( obj == NULL )
    {
        return 0;
    }
    
    base = ( CFRuntimeBase * )obj;
    
    return base->rc;
}

CFTypeRef CFMakeCollectable( CFTypeRef obj )
{
    /* No GC support... */
    return obj;
}

CFTypeRef CFRetain( CFTypeRef obj )
{
    CFRuntimeBase * base;
    
    if( obj == NULL )
    {
        return NULL;
    }
    
    base = ( CFRuntimeBase * )obj;
    
    if( base->rc == -1 )
    {
        return obj;
    }
    
    CFAtomicIncrement( &( base->rc ) );
    
    return obj;
}

void CFRelease( CFTypeRef obj )
{
    CFRuntimeBase * base;
    
    if( obj == NULL )
    {
        return;
    }
    
    base = ( CFRuntimeBase * )obj;
    
    if( base->rc == -1 )
    {
        return;
    }
    
    if( CFAtomicDecrement( &( base->rc ) ) == 0 )
    {
        CFRuntimeDeleteInstance( obj );
    }
}

Boolean CFEqual( CFTypeRef obj1, CFTypeRef obj2 )
{
    if( obj1 == obj2 )
    {
        return true;
    }
    
    return false;
}

CFHashCode CFHash( CFTypeRef obj )
{
    ( void )obj;
    
    return 0;
}

CFStringRef CFCopyDescription( CFTypeRef obj )
{
    if( obj == NULL )
    {
        return CFStringCreateWithCString( NULL, "(null)", kCFStringEncodingUTF8 );
    }
    
    return NULL;
}

CFStringRef CFCopyTypeIDDescription( CFTypeID typeID )
{
    ( void )typeID;
    
    return NULL;
}

CFTypeID CFGetTypeID( CFTypeRef obj )
{
    CFRuntimeBase * base;
    
    if( obj == NULL )
    {
        return 0;
    }
    
    base = ( CFRuntimeBase * )obj;
    
    return base->isa;
}

void CFShow( CFTypeRef obj )
{
    CFStringRef description;
    char      * buf;
    
    description = CFCopyDescription( obj );
    
    if( description == NULL || CFStringGetLength( description ) == 0 )
    {
        return;
    }
    
    buf = CFAllocatorAllocate( NULL, CFStringGetLength( description ) + 1, 0 );
    
    if( buf == NULL )
    {
        CFRelease( description );
        CFRuntimeAbortWithOutOfMemoryError();
        
        return;
    }
    
    if( CFStringGetCString( description, buf, CFStringGetLength( description ) + 1, kCFStringEncodingUTF8 ) == false )
    {
        CFRelease( description );
        
        return;
    }
    
    fprintf( stderr, "%s\n", buf );
    CFAllocatorDeallocate( NULL, buf );
    CFRelease( description );
}
