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

#include <CoreFoundation/__private/__CFError.h>

CFTypeID       CFErrorTypeID = 0;
CFRuntimeClass CFErrorClass =
{
    "CFError",
    sizeof( struct CFError ),
    NULL,
    ( void ( * )( CFTypeRef ) )CFErrorDestruct,
    NULL,
    ( bool ( * )( CFTypeRef, CFTypeRef ) )CFErrorEquals,
    ( CFStringRef ( * )( CFTypeRef ) )CFErrorCopyDescription
};

void CFErrorInitialize( void )
{
    CFErrorTypeID = CFRuntimeRegisterClass( &CFErrorClass );
}

void CFErrorDestruct( CFErrorRef e )
{
    if( e->_domain )
    {
        CFRelease( e->_domain );
    }
    
    if( e->_userInfo )
    {
        CFRelease( e->_userInfo );
    }
}

bool CFErrorEquals( CFErrorRef e1,  CFErrorRef e2 )
{
    if( e1->_code != e2->_code )
    {
        return false;
    }
    
    if( e1->_domain == NULL && e1->_domain != NULL )
    {
        return false;
    }
    
    if( e2->_domain == NULL && e1->_domain != NULL )
    {
        return false;
    }
    
    if( e1->_domain != NULL && e2->_domain != NULL )
    {
        if( CFEqual( e1->_domain, e2->_domain ) == false )
        {
            return false;
        }
    }
    
    if( e1->_userInfo == NULL && e1->_userInfo != NULL )
    {
        return false;
    }
    
    if( e2->_userInfo == NULL && e1->_userInfo != NULL )
    {
        return false;
    }
    
    if( e1->_userInfo != NULL && e2->_userInfo != NULL )
    {
        if( CFEqual( e1->_userInfo, e2->_userInfo ) == false )
        {
            return false;
        }
    }
    
    return true;
}
