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
 * @file        CFNotificationCenter.c
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#include <CoreFoundation/__private/CFNotificationCenter.h>

CFTypeID       CFNotificationCenterTypeID = 0;
CFRuntimeClass CFNotificationCenterClass  =
{
    "CFNotificationCenter",
    sizeof( struct CFNotificationCenter ),
    NULL,
    NULL,
    NULL,
    NULL,
    ( CFStringRef ( * )( CFTypeRef ) )CFNotificationCenterCopyDescription
};

CFSpinLock CFNotificationCenterLocalLock       = 0;
CFSpinLock CFNotificationCenterDarwinLock      = 0;
CFSpinLock CFNotificationCenterDistributedLock = 0;

CFNotificationCenterRef CFNotificationCenterLocal       = NULL;
CFNotificationCenterRef CFNotificationCenterDarwin      = NULL;
CFNotificationCenterRef CFNotificationCenterDistributed = NULL;

void CFNotificationCenterInitialize( void )
{
    CFNotificationCenterTypeID = CFRuntimeRegisterClass( &CFNotificationCenterClass );
}

CFNotificationCenterRef CFNotificationCenterCreate( CFAllocatorRef alloc )
{
    struct CFNotificationCenter * o;
    
    o = ( struct CFNotificationCenter * )CFRuntimeCreateInstance( alloc, CFNotificationCenterTypeID );
    
    return o;
}

CFStringRef CFNotificationCenterCopyDescription( CFNotificationCenterRef center )
{
    if( center == NULL )
    {
        return NULL;
    }
    
    if( center == CFNotificationCenterDarwin )
    {
        return CFSTR( "Darwin" );
    }
    
    if( center == CFNotificationCenterDistributed )
    {
        return CFSTR( "Distributed" );
    }
    
    if( center == CFNotificationCenterLocal )
    {
        return CFSTR( "Local" );
    }
    
    return NULL;
}
