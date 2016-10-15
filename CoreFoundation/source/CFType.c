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
#include <CoreFoundation/__private/__CFRuntime.h>
#include <CoreFoundation/__private/__CFAtomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    CFRuntimeEqualsCallback f;
    
    if( obj1 == NULL || obj2 == NULL )
    {
        return false;
    }
    
    if( obj1 == obj2 )
    {
        return true;
    }
    
    if( CFGetTypeID( obj1 ) != CFGetTypeID( obj2 ) )
    {
        return false;
    }
    
    f = CFRuntimeGetEqualsCallback( CFGetTypeID( obj1 ) );
    
    if( f )
    {
        return f( obj1, obj2 );
    }
    
    return false;
}

CFHashCode CFHash( CFTypeRef obj )
{
    CFRuntimeHashCallback f;
    
    if( obj == NULL )
    {
        return 0;
    }
    
    f = CFRuntimeGetHashCallback( CFGetTypeID( obj ) );
    
    if( f )
    {
        return f( obj );
    }
    
    return ( CFHashCode )obj;
}

CFStringRef CFCopyDescription( CFTypeRef obj )
{
    CFTypeID                         typeID;
    CFStringRef                      type;
    CFStringRef                      description;
    CFRuntimeCopyDescriptionCallback copyDescription;
    char                           * buf1;
    char                           * buf2;
    CFTypeRef                        ret;
    CFAllocatorRef                   allocator;
    const char                     * allocatorName;
    
    if( obj == NULL )
    {
        return CFStringCreateWithCString( NULL, "(null)", kCFStringEncodingASCII );
    }
    
    typeID          = CFGetTypeID( obj );
    type            = CFCopyTypeIDDescription( typeID );
    copyDescription = CFRuntimeGetCopyDescriptionCallback( typeID );
    
    if( type == NULL )
    {
        return NULL;
    }
    
    buf1 = CFAllocatorAllocate( NULL, CFStringGetLength( type ) + 1, 0 );
    
    if
    (
           buf1 == NULL
        || CFStringGetCString( type, buf1, CFStringGetLength( type ) + 1, kCFStringEncodingASCII ) == false
        || strlen( buf1 ) == 0
    )
    {
        CFRelease( type );
        CFRuntimeAbortWithOutOfMemoryError();
        
        return NULL;
    }
    
    if( copyDescription == NULL )
    {
        description = NULL;
        buf2        = NULL;
    }
    else
    {
        description = copyDescription( obj );
        buf2        = NULL;
        
        if( description )
        {
            buf2 = CFAllocatorAllocate( NULL, CFStringGetLength( description ) + 1, 0 );
            
            if( buf2 )
            {
                memset( buf2, 0, CFStringGetLength( description ) + 1 );
                CFStringGetCString( description, buf2, CFStringGetLength( description ) + 1, kCFStringEncodingASCII );
            }
        }
    }
    
    allocator = CFGetAllocator( obj );
    
    if( allocator == kCFAllocatorSystemDefault )
    {
        allocatorName = "kCFAllocatorSystemDefault";
    }
    else if( allocator == kCFAllocatorMalloc )
    {
        allocatorName = "kCFAllocatorMalloc";
    }
    else if( allocator == kCFAllocatorMallocZone )
    {
        allocatorName = "kCFAllocatorMallocZone";
    }
    else if( allocator == kCFAllocatorNull )
    {
        allocatorName = "kCFAllocatorNull";
    }
    else
    {
        allocatorName = NULL;
    }
    
    if( buf2 && strlen( buf2 ) )
    {
        if( allocatorName )
        {
            ret = CFStringCreateWithFormat( NULL, NULL, CFSTR( "<%s 0x%lx [ %s ]> %s" ), buf1, obj, allocatorName, buf2 );
        }
        else
        {
            ret = CFStringCreateWithFormat( NULL, NULL, CFSTR( "<%s 0x%lx [ 0x%lx ]> %s" ), buf1, obj, allocator, buf2 );
        }
    }
    else
    {
        if( allocatorName )
        {
            ret = CFStringCreateWithFormat( NULL, NULL, CFSTR( "<%s 0x%lx [ %s ]>" ), buf1, obj, allocatorName );
        }
        else
        {
            ret = CFStringCreateWithFormat( NULL, NULL, CFSTR( "<%s 0x%lx [ 0x%lx ]>" ), buf1, obj, allocator );
        }
    }
    
    if( buf2 )
    {
        CFAllocatorDeallocate( NULL, buf2 );
    }
    
    if( description )
    {
        CFRelease( description );
    }
    
    CFAllocatorDeallocate( NULL, buf1 );
    CFRelease( type );
    
    return ret;
}

CFStringRef CFCopyTypeIDDescription( CFTypeID typeID )
{
    const char * name;
    
    name = CFRuntimeGetTypeIDName( typeID );
    
    if( name == NULL )
    {
        return NULL;
    }
    
    return CFStringCreateWithCStringNoCopy( NULL, name, kCFStringEncodingASCII, kCFAllocatorNull );
}

CFTypeID CFGetTypeID( CFTypeRef obj )
{
    return CFRuntimeGetTypeID( obj );
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
    
    if( CFStringGetCString( description, buf, CFStringGetLength( description ) + 1, kCFStringEncodingASCII ) == false )
    {
        CFRelease( description );
        
        return;
    }
    
    fprintf( stderr, "%s\n", buf );
    CFAllocatorDeallocate( NULL, buf );
    CFRelease( description );
}
