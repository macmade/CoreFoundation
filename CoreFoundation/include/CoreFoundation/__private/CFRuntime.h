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
 * @header      CFRuntime.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION_CF___PRIVATE_RUNTIME_H
#define CORE_FOUNDATION_CF___PRIVATE_RUNTIME_H

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFAllocator.h>
#include <stdint.h>
#include <stdlib.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFRuntimeBase
 * @abstract    Base for all CoreFoundation classes
 * @field       isa     ID of the object's class
 * @discussion  This structure shall be used as first member of all
 *              CoreFoundation classes.
 *              It is reserved for internal use and should never be accessed
 *              directly. Fields may be added or removed at any time. Binary
 *              compatibility is not guaranteed.
 */
typedef struct
{
    CFTypeID         isa;
    volatile CFIndex rc;
    CFAllocatorRef   allocator;
}
CFRuntimeBase;

/*!
 * @typedef     CFRuntimeClass
 * @abstract    Definition of a CoreFoundation class
 * @field       name            The name of the class
 * @field       size            The size of the class instances
 * @field       constructor     The class constructor (may be NULL)
 * @field       destructor      The class destructor (may be NULL)
 */
typedef struct
{
    const char * name;
    size_t       size;
    
    void        ( * constructor     )( CFTypeRef obj );
    void        ( * destructor      )( CFTypeRef obj );
    CFHashCode  ( * hash            )( CFTypeRef obj );
    CFStringRef ( * equals          )( CFTypeRef obj );
    CFStringRef ( * copyDescription )( CFTypeRef obj );
}
CFRuntimeClass;

/*!
 * @function    CFRuntimeRegisterClass
 * @abstract    Registers a new CoreFoundation class.
 * @param       cls     The class to register
 * @result      The ID of the registered class
 */
CF_EXPORT CFTypeID CFRuntimeRegisterClass( const CFRuntimeClass * cls );

/*!
 * @function    CFRuntimeCreateInstance
 * @abstract    Creates a new instance of a CoreFoundation class.
 * @param       allocator   The allocator to use
 * @param       typeID      The type ID of the class
 * @result      The new instance
 */
CF_EXPORT CFTypeRef CFRuntimeCreateInstance( CFAllocatorRef allocator, CFTypeID typeID );

/*!
 * @function    CFRuntimeGetInstanceSize
 */
CF_EXPORT CFIndex CFRuntimeGetInstanceSize( CFTypeID typeID );

/*!
 * @function    CFRuntimeInitInstance
 */
CF_EXPORT void CFRuntimeInitInstance( void * memory, CFTypeID typeID, CFAllocatorRef allocator );

/*!
 * @function    CFRuntimeInitStaticInstance
 * @abstract    Initializes a static instance of a CoreFoundation class.
 * @param       memory      The static class instance
 * @param       typeID      The ID of the class
 */
CF_EXPORT void CFRuntimeInitStaticInstance( void * memory, CFTypeID typeID );

/*!
 * @function    CFRuntimeDeleteInstance
 * @abstract    Deletes an instance of a CoreFoundation class.
 * @param       obj     The class instance to delete
 */
CF_EXPORT void CFRuntimeDeleteInstance( CFTypeRef obj );

/*!
 * @function    CFAbortWithError
 * @abstract    Prints an error message and aborts the program's execution.
 * @param       error       The error message
 */
CF_EXPORT void CFAbortWithError( const char * error );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF___PRIVATE_RUNTIME_H */
