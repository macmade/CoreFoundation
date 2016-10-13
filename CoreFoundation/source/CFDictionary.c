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
 * @file        CFDictionary.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>

struct CFDictionary
{
    CFRuntimeBase _base;
};

static CFTypeID CFDictionaryTypeID      = 0;
static CFRuntimeClass CFDictionaryClass =
{
    "CFDictionary",
    sizeof( struct CFDictionary ),
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static void init( void ) __attribute__( ( constructor ) );
static void init( void )
{
    CFDictionaryTypeID = CFRuntimeRegisterClass( &CFDictionaryClass );
}

const CFDictionaryKeyCallBacks kCFCopyStringDictionaryKeyCallBacks =
{
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

const CFDictionaryKeyCallBacks kCFTypeDictionaryKeyCallBacks =
{
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

const CFDictionaryValueCallBacks kCFTypeDictionaryValueCallBacks =
{
    0,
    NULL,
    NULL,
    NULL,
    NULL
};

CFTypeID CFDictionaryGetTypeID( void )
{
    return 0;
}

CFDictionaryRef CFDictionaryCreate( CFAllocatorRef allocator, const void ** keys, const void ** values, CFIndex numValues, const CFDictionaryKeyCallBacks * keyCallBacks, const CFDictionaryValueCallBacks * valueCallBacks )
{
    ( void )allocator;
    ( void )keys;
    ( void )values;
    ( void )numValues;
    ( void )keyCallBacks;
    ( void )valueCallBacks;
    
    return NULL;
}

CFDictionaryRef CFDictionaryCreateCopy( CFAllocatorRef allocator, CFDictionaryRef theDict )
{
    ( void )allocator;
    ( void )theDict;
    
    return NULL;
}

Boolean CFDictionaryContainsKey( CFDictionaryRef theDict, const void * key )
{
    ( void )theDict;
    ( void )key;
    
    return false;
}

Boolean CFDictionaryContainsValue( CFDictionaryRef theDict, const void * value )
{
    ( void )theDict;
    ( void )value;
    
    return false;
}

CFIndex CFDictionaryGetCount( CFDictionaryRef theDict )
{
    ( void )theDict;
    
    return 0;
}

CFIndex CFDictionaryGetCountOfKey( CFDictionaryRef theDict, const void * key )
{
    ( void )theDict;
    ( void )key;
    
    return 0;
}

CFIndex CFDictionaryGetCountOfValue( CFDictionaryRef theDict, const void * value )
{
    ( void )theDict;
    ( void )value;
    
    return 0;
}

void CFDictionaryGetKeysAndValues( CFDictionaryRef theDict, const void ** keys, const void ** values )
{
    ( void )theDict;
    ( void )keys;
    ( void )values;
}

const void * CFDictionaryGetValue( CFDictionaryRef theDict, const void * key )
{
    ( void )theDict;
    ( void )key;
    
    return NULL;
}

Boolean CFDictionaryGetValueIfPresent( CFDictionaryRef theDict, const void * key, const void ** value )
{
    ( void )theDict;
    ( void )key;
    ( void )value;
    
    return false;
}

void CFDictionaryApplyFunction( CFDictionaryRef theDict, CFDictionaryApplierFunction applier, void * context )
{
    ( void )theDict;
    ( void )applier;
    ( void )context;
}
