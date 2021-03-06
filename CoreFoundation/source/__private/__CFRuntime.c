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
 * @file        CFRuntime.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/__CFRuntime.h>
#include <CoreFoundation/__private/__CFAtomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CFRuntimeClassList
{
    const CFRuntimeClass               * cls;
    CFTypeID                             typeID;
    struct CFRuntimeClassList * volatile next;
};

CFIndex CFRuntimeClassCount                           = 0;
struct CFRuntimeClassList * volatile CFRuntimeClasses = NULL;

CFTypeID CFRuntimeRegisterClass( const CFRuntimeClass * cls )
{
    struct CFRuntimeClassList * new;
    struct CFRuntimeClassList * list;
    CFTypeID                    typeID;
    
    if( cls == NULL )
    {
        return 0;
    }
    
    new = calloc( sizeof( struct CFRuntimeClassList ), 1 );
    
    if( new == NULL )
    {
        CFRuntimeAbortWithOutOfMemoryError();
        
        return 0;
    }
    
    typeID      = ( CFTypeID )CFAtomicIncrement( &CFRuntimeClassCount );
    new->cls    = cls;
    new->typeID = typeID;
    
    if( CFAtomicCompareAndSwapPointer( NULL, new, ( void * volatile * )&CFRuntimeClasses ) )
    {
        return typeID;
    }
    
    list = CFRuntimeClasses;
    
    while( list )
    {
        if( CFAtomicCompareAndSwapPointer( NULL, new, ( void * volatile * )&( list->next ) ) )
        {
            return typeID;
        }
        
        list = list->next;
    }
    
    return 0;
}

CFTypeID CFRuntimeGetTypeID( CFTypeRef obj )
{
    struct CFRuntimeClassList * list;
    CFRuntimeBase             * base;
    
    if( obj == NULL )
    {
        return 0;
    }
    
    base = ( CFRuntimeBase * )obj;
    list = CFRuntimeClasses;
    
    if( base->isa == 0 )
    {
        return 0;
    }
    
    while( list )
    {
        if( ( const CFRuntimeClass * )( base->isa ) == list->cls )
        {
            return list->typeID;
        }
        
        list = list->next;
    }
    
    return 0;
}

const char * CFRuntimeGetTypeIDName( CFTypeID typeID )
{
    struct CFRuntimeClassList * list;
    
    list = CFRuntimeClasses;
    
    while( list )
    {
        if( list->typeID != typeID )
        {
            list = list->next;
            
            continue;
        }
        
        return list->cls->name;
    }
    
    return NULL;
}

CFTypeRef CFRuntimeCreateInstance( CFAllocatorRef allocator, CFTypeID typeID )
{
    void * obj;
    
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    obj = CFAllocatorAllocate( allocator, CFRuntimeGetInstanceSize( typeID ), 1 );
    
    CFRuntimeInitInstance( obj, typeID, allocator );
    
    return obj;
}

CFIndex CFRuntimeGetInstanceSize( CFTypeID typeID )
{
    struct CFRuntimeClassList * list;
    
    list = CFRuntimeClasses;
    
    while( list )
    {
        if( list->typeID != typeID )
        {
            list = list->next;
            
            continue;
        }
        
        return ( CFIndex )( list->cls->size );
    }
    
    return 0;
}

CFRuntimeHashCallback CFRuntimeGetHashCallback( CFTypeID typeID )
{
    struct CFRuntimeClassList * list;
    
    list = CFRuntimeClasses;
    
    while( list )
    {
        if( list->typeID != typeID )
        {
            list = list->next;
            
            continue;
        }
        
        return list->cls->hash;
    }
    
    return NULL;
}

CFRuntimeEqualsCallback CFRuntimeGetEqualsCallback( CFTypeID typeID )
{
    struct CFRuntimeClassList * list;
    
    list = CFRuntimeClasses;
    
    while( list )
    {
        if( list->typeID != typeID )
        {
            list = list->next;
            
            continue;
        }
        
        return list->cls->equals;
    }
    
    return NULL;
}

CFRuntimeCopyDescriptionCallback CFRuntimeGetCopyDescriptionCallback( CFTypeID typeID )
{
    struct CFRuntimeClassList * list;
    
    list = CFRuntimeClasses;
    
    while( list )
    {
        if( list->typeID != typeID )
        {
            list = list->next;
            
            continue;
        }
        
        return list->cls->copyDescription;
    }
    
    return NULL;
}

void CFRuntimeInitInstance( void * memory, CFTypeID typeID, CFAllocatorRef allocator )
{
    struct CFRuntimeClassList * list;
    CFRuntimeBase             * base;
    
    if( memory == NULL )
    {
        return;
    }
    
    list = CFRuntimeClasses;
    
    while( list )
    {
        if( list->typeID != typeID )
        {
            list = list->next;
            
            continue;
        }
        
        memset( memory, 0, list->cls->size );
        
        base            = ( CFRuntimeBase * )memory;
        base->isa       = ( uintptr_t )( list->cls );
        base->rc        = 1;
        base->allocator = ( allocator ) ? CFRetain( allocator ) : NULL;
        
        if( list->cls->constructor )
        {
            list->cls->constructor( memory );
        }
        
        break;
    }
}

void CFRuntimeInitStaticInstance( void * memory, CFTypeID typeID )
{
    if( memory == NULL )
    {
        return;
    }
    
    CFRuntimeInitInstance( memory, typeID, NULL );
    CFRuntimeSetObjectAsConstant( memory );
}

void CFRuntimeDeleteInstance( CFTypeRef obj )
{
    struct CFRuntimeClassList * list;
    CFRuntimeBase             * base;
    CFAllocatorRef              allocator;
    
    if( obj == NULL )
    {
        return;
    }
    
    base = ( CFRuntimeBase * )obj;
    list = CFRuntimeClasses;
    
    if( CFRuntimeIsConstantObject( obj ) )
    {
        return;
    }
    
    if( base->isa == 0 )
    {
        return;
    }
    
    while( list )
    {
        if( ( const CFRuntimeClass * )( base->isa ) != list->cls )
        {
            list = list->next;
            
            continue;
        }
        
        if( list->cls->destructor )
        {
            list->cls->destructor( obj );
        }
        
        allocator = CFGetAllocator( obj );
        
        if( allocator )
        {
            CFAllocatorDeallocate( allocator, ( void * )obj );
            CFRelease( allocator );
        }
        
        break;
    }
}

void CFRuntimeSetObjectAsConstant( CFTypeRef obj )
{
    CFRuntimeBase * base;
    
    if( obj == NULL )
    {
        return;
    }
    
    base = ( CFRuntimeBase * )obj;
    
    base->rc = -1;
}

bool CFRuntimeIsConstantObject( CFTypeRef obj )
{
    CFRuntimeBase * base;
    
    if( obj == NULL )
    {
        return false;
    }
    
    base = ( CFRuntimeBase * )obj;
    
    return base->rc == -1;
}

void CFRuntimeAbortWithError( const char * error, ... )
{
    va_list ap;
    
    if( error != NULL )
    {
        va_start( ap, error );
        
        fprintf( stderr, "CFRuntime error: " );
        vfprintf( stderr, error, ap );
        fprintf( stderr, "\n" );
        
        va_end( ap );
    }
    else
    {
        fprintf( stderr, "CFRuntime error\n" );
    }
    
    abort();
}

void CFRuntimeAbortWithOutOfMemoryError( void )
{
    CFRuntimeAbortWithError( "out of memory" );
}
