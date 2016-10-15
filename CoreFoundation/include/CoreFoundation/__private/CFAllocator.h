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
 * @header      CFAllocator.h
 * @copyright   (c) 2016, Jean-David Gadina - www.xs-labs.com
 */

#ifndef CORE_FOUNDATION___PRIVATE_CF_ALLOCATOR_H
#define CORE_FOUNDATION___PRIVATE_CF_ALLOCATOR_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/__private/CFRuntime.h>
#include <CoreFoundation/__private/CFThreading.h>
#include <CoreFoundation/__private/CFSpinLock.h>

CF_EXTERN_C_BEGIN

#define CF_ALLOCATOR_DEBUG  1

typedef struct
{
    const void  * ptr;
    CFOptionFlags hint;
}
CFAllocatorRegistry;

struct CFAllocator
{
    CFRuntimeBase         _base;
    CFAllocatorContext    _context;
    CFSpinLock            _registryLock;
    CFAllocatorRegistry * _registry;
    CFIndex               _registrySize;
};

CF_EXPORT CFTypeID       CFAllocatorTypeID;
CF_EXPORT CFRuntimeClass CFAllocatorClass;

CF_EXPORT struct CFAllocator CFAllocatorSystemDefault;
CF_EXPORT struct CFAllocator CFAllocatorMalloc;
CF_EXPORT struct CFAllocator CFAllocatorMallocZone;
CF_EXPORT struct CFAllocator CFAllocatorNull;

CF_EXPORT CFThreadingKey CFAllocatorDefaultKey;

CF_EXPORT void        CFAllocatorConstruct( CFAllocatorRef allocator );
CF_EXPORT void        CFAllocatorDestruct( CFAllocatorRef allocator );
CF_EXPORT CFStringRef CFAllocatorCopyDescription( CFAllocatorRef allocator );

CF_EXPORT void CFAllocatorDebugRegisterAlloc( CFAllocatorRef allocator, const void * ptr, CFOptionFlags hint );
CF_EXPORT void CFAllocatorDebugRegisterRealloc( CFAllocatorRef allocator, const void * oldPtr, const void * newPtr );
CF_EXPORT void CFAllocatorDebugRegisterFree( CFAllocatorRef allocator, const void * ptr );
CF_EXPORT void CFAllocatorDebugReportLeaks( CFAllocatorRef allocator, CFAllocatorRegistry * registry, CFIndex registrySize );
CF_EXPORT void CFAllocatorExit( void );

CF_EXPORT void  * CFAllocatorSystemDefaultAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
CF_EXPORT void  * CFAllocatorSystemDefaultReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
CF_EXPORT void    CFAllocatorSystemDefaultDeallocateCallBack( void * ptr, void * info );

CF_EXPORT void  * CFAllocatorNullAllocateCallBack( CFIndex allocSize, CFOptionFlags hint, void * info );
CF_EXPORT void  * CFAllocatorNullReallocateCallBack( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );
CF_EXPORT void    CFAllocatorNullDeallocateCallBack( void * ptr, void * info );
CF_EXPORT CFIndex CFAllocatorNullPreferredSizeCallBack( CFIndex size, CFOptionFlags hint, void * info );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION___PRIVATE_CF_ALLOCATOR_H */
