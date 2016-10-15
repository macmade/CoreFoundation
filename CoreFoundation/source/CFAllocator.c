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
 * @file        CFAllocator.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/__CFAllocator.h>
#include <CoreFoundation/__private/__CFRuntime.h>
#include <CoreFoundation/__private/__CFThreading.h>
#include <stdlib.h>
#include <string.h>

CFTypeID CFAllocatorGetTypeID( void )
{
    return CFAllocatorTypeID;
}

CFAllocatorRef CFAllocatorCreate( CFAllocatorRef allocator, CFAllocatorContext * context )
{
    struct CFAllocator * o;
    
    if( allocator == kCFAllocatorUseContext )
    {
        if( context == NULL || context->allocate == NULL )
        {
            return NULL;
        }
        
        o = context->allocate( CFRuntimeGetInstanceSize( CFAllocatorTypeID ), 0, context->info );
        
        CFRuntimeInitInstance( o, CFAllocatorTypeID, o );
    }
    else
    {
        o = ( struct CFAllocator * )CFRuntimeCreateInstance( allocator, CFAllocatorTypeID );
    }
    
    if( o && context )
    {
        o->_context = *( context );
        
        if( o->_context.retain )
        {
            o->_context.info = ( void * )( o->_context.retain( o->_context.info ) );
        }
    }
    
    return o;
}

void * CFAllocatorAllocate( CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint )
{
    void * p;
    
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( allocator != NULL && allocator->_context.allocate != NULL )
    {
        p = allocator->_context.allocate( size, hint, allocator->_context.info );
        
        CFAllocatorDebugRegisterAlloc( allocator, p, hint );
        
        return p;
    }
    
    return NULL;
}

void CFAllocatorDeallocate( CFAllocatorRef allocator, void * ptr )
{
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( allocator != NULL && allocator->_context.deallocate != NULL )
    {
        CFAllocatorDebugRegisterFree( allocator, ptr );
        
        allocator->_context.deallocate( ptr, allocator->_context.info );
    }
}

CFIndex CFAllocatorGetPreferredSizeForSize( CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint )
{
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( allocator != NULL && allocator->_context.preferredSize != NULL )
    {
        return allocator->_context.preferredSize( size, hint, allocator->_context.info );
    }
    
    return size;
}

void * CFAllocatorReallocate( CFAllocatorRef allocator, void * ptr, CFIndex newsize, CFOptionFlags hint )
{
    void * p;
    
    if( allocator == NULL )
    {
        allocator = CFAllocatorGetDefault();
    }
    
    if( ptr == NULL )
    {
        return ( newsize > 0 ) ? CFAllocatorAllocate( allocator, newsize, hint ) : NULL;
    }
    
    if( newsize == 0 )
    {
        CFAllocatorDeallocate( allocator, ptr );
        
        return NULL;
    }
    
    if( allocator != NULL && allocator->_context.reallocate != NULL )
    {
        p = allocator->_context.reallocate( ptr, newsize, hint, allocator->_context.info );
        
        CFAllocatorDebugRegisterRealloc( allocator, ptr, p );
        
        return p;
    }
    
    return NULL;
}

CFAllocatorRef CFAllocatorGetDefault( void )
{
    CFAllocatorRef current;
    
    current = CFThreadingGetSpecific( CFAllocatorDefaultKey );
    
    return ( current == NULL ) ? kCFAllocatorSystemDefault : current;
}

void CFAllocatorSetDefault( CFAllocatorRef allocator )
{
    CFAllocatorRef current;
    
    current = CFThreadingGetSpecific( CFAllocatorDefaultKey );
    
    if( current )
    {
        CFRelease( current );
    }
    
    if( allocator )
    {
        CFRetain( allocator );
    }
    
    CFThreadingSetSpecific( CFAllocatorDefaultKey, allocator );
}

void CFAllocatorGetContext( CFAllocatorRef allocator, CFAllocatorContext * context )
{
    if( allocator == NULL )
    {
        if( context != NULL )
        {
            memset( context, 0, sizeof( CFAllocatorContext ) );
        }
    }
    else if( context != NULL )
    {
        *( context ) = allocator->_context;
    }
}
