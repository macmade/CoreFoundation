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
 * @file        CFThreading.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/__CFThreading.h>
#include <stdlib.h>

bool CFThreadingKeyCreate( CFThreadingKey * key )
{
    if( key == NULL )
    {
        return false;
    }
    
    #ifdef _WIN32
    
    return ( *( key ) = TlsAlloc() ) != TLS_OUT_OF_INDEXES;
    
    #else
    
    return pthread_key_create( key, NULL ) == 0;
    
    #endif
}

void * CFThreadingGetSpecific( CFThreadingKey key )
{
    #ifdef _WIN32
    
    return TlsGetValue( key );
    
    #else
    
    return pthread_getspecific( key );
    
    #endif
}

bool CFThreadingSetSpecific( CFThreadingKey key, const void * value )
{
    #ifdef _WIN32
    
    return TlsSetValue( key, ( void * )value );
    
    #else
    
    return pthread_setspecific( key, value ) == 0;
    
    #endif
}
