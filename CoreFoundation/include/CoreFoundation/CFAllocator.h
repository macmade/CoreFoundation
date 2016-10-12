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
 * @discussion  CFAllocator is an opaque type that allocates and deallocates
 *              memory for you. You never have to allocate, reallocate, or
 *              deallocate memory directly for Core Foundation objects—and
 *              rarely should you. You pass CFAllocator objects into functions
 *              that create objects; these functions have “Create” embedded in
 *              their names, for example, CFStringCreateWithPascalString. The
 *              creation functions use the allocators to allocate memory for
 *              the objects they create.
 */

#ifndef CORE_FOUNDATION_CF_ALLOCATOR_H
#define CORE_FOUNDATION_CF_ALLOCATOR_H

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

/*!
 * @typedef     CFAllocatorRef
 * @abstract    A reference to a CFAllocator object.
 * @discussion  The CFAllocatorRef type is a reference type used in many Core
 *              Foundation parameters and function results. It refers to a
 *              CFAllocator object, which allocates, reallocates, and
 *              deallocates memory for Core Foundation objects.
 */
typedef const struct CFAllocator * CFAllocatorRef;

/*
 * CFAllocatorRef needs to be defined prior to including CFString.h
 * and CFType.h
 */
#include <CoreFoundation/CFType.h>
#include <CoreFoundation/CFString.h>

/*!
 * @constant    kCFAllocatorDefault
 * @abstract    This is a synonym for NULL.
 */
CF_EXPORT const CFAllocatorRef kCFAllocatorDefault;

/*!
 * @constant    kCFAllocatorSystemDefault
 * @abstract    Default system allocator.
 * @discussion  You rarely need to use this.
 */
CF_EXPORT const CFAllocatorRef kCFAllocatorSystemDefault;

/*!
 * @constant    kCFAllocatorMalloc
 * @abstract    This allocator uses malloc(), realloc(), and free().
 * @discussion  Typically you should not use this allocator, use
 *              kCFAllocatorDefault instead. This allocator is useful as the
 *              bytesDeallocator in CFData or contentsDeallocator in CFString
 *              where the memory was obtained as a result of malloc type
 *              functions.
 */
CF_EXPORT const CFAllocatorRef kCFAllocatorMalloc;

/*!
 * @constant    kCFAllocatorMallocZone
 * @abstract    This allocator explicitly uses the default malloc zone, returned
 *              by malloc_default_zone().
 * @discussion  You should only use this when an object is safe to be allocated
 *              in non-scanned memory.
 */
CF_EXPORT const CFAllocatorRef kCFAllocatorMallocZone;

/*!
 * @constant    kCFAllocatorNull
 * @abstract    This allocator does nothing — it allocates no memory.
 * @discussion  This allocator is useful as the bytesDeallocator in CFData or
 *              contentsDeallocator in CFString where the memory should not be
 *              freed.
 */
CF_EXPORT const CFAllocatorRef kCFAllocatorNull;

/*!
 * @constant    kCFAllocatorUseContext
 * @abstract    Special allocator argument to CFAllocatorCreate — it uses the
 *              functions given in the context to allocate the allocator.
 */
CF_EXPORT const CFAllocatorRef kCFAllocatorUseContext;

/*!
 * @typedef     CFAllocatorRetainCallBack
 * @abstract    A prototype for a function callback that retains the given data.
 * @param       info    The data to be retained.
 * @result      The retained data
 * @discussion  A prototype for a function callback that retains the data
 *              pointed to by the info field. In implementing this function,
 *              retain the data you have defined for the allocator context in
 *              this field. (This might make sense only if the data is a Core
 *              Foundation object.)
 */
typedef const void * ( * CFAllocatorRetainCallBack )( const void * info );

/*!
 * @typedef     CFAllocatorReleaseCallBack
 * @abstract    A prototype for a function callback that releases the given
 *              data.
 * @param       info    The data to be released.
 * @discussion  A prototype for a function callback that releases the data
 *              pointed to by the info field. In implementing this function,
 *              release (or free) the data you have defined for the allocator
 *              context.
 */
typedef void ( * CFAllocatorReleaseCallBack )( const void * info );

/*!
 * @typedef     CFAllocatorCopyDescriptionCallBack
 * @abstract    A prototype for a function callback that provides a description
 *              of the specified data.
 * @param       info    An untyped pointer to program-defined data.
 * @result      A CFString object that describes the allocator. The caller is
 *              responsible for releasing this object.
 * @discussion  A prototype for a function callback that provides a description
 *              of the data pointed to by the info field. In implementing this
 *              function, return a reference to a CFString object that describes
 *              your allocator, particularly some characteristics of your
 *              program-defined data.
 */
typedef CFStringRef ( * CFAllocatorCopyDescriptionCallBack )( const void * info );

/*!
 * @typedef     CFAllocatorAllocateCallBack
 * @abstract    A prototype for a function callback that allocates memory of a
 *              requested size.
 * @param       allocSize   This function allocates a block of memory of at
 *                          least allocSize bytes (always greater than 0).
 * @param       hint        A bitfield that is currently not used (always set
 *                          to 0).
 * @param       info        An untyped pointer to program-defined data. Allocate
 *                          memory for the data and assign a pointer to it.
 *                          This data is often control information for the
 *                          allocator. It may be NULL.
 * @resutl      A pointer to the start of the block.
 */
typedef void * ( * CFAllocatorAllocateCallBack )( CFIndex allocSize, CFOptionFlags hint, void * info );

/*!
 * @typedef     CFAllocatorReallocateCallBack
 * @abstract    A prototype for a function callback that reallocates memory of a
 *              requested size for an existing block of memory.
 * @param       ptr         The block of memory to resize.
 * @param       newsize     The size of the new allocation.
 * @param       hint        A bitfield that is currently not used (always set to 0).
 * @param       info        An untyped pointer to program-defined data.
 * @result      Pointer to the new block of memory.
 * @discussion  In implementing this function, change the size of the block of
 *              memory pointed to by ptr to the size specified by newsize and
 *              return the pointer to the larger block of memory. Return NULL on
 *              any reallocation failure, leaving the old block of memory
 *              untouched. Also return NULL immediately if any of the following
 *              conditions if the ptr parameter is NULL or the newsize parameter
 *              is not greater than 0. Leave the contents of the old block of
 *              memory unchanged up to the lesser of the new or old sizes. If
 *              the ptr parameter is not a block of memory that has been
 *              previously allocated by the allocator, the results are
 *              undefined; abnormal program termination can occur. The hint
 *              argument is a bitfield that you should currently not use
 *              (that is, assign 0).
 */
typedef void * ( * CFAllocatorReallocateCallBack )( void * ptr, CFIndex newsize, CFOptionFlags hint, void * info );

/*!
 * @typedef     CFAllocatorDeallocateCallBack
 * @abstract    A prototype for a function callback that deallocates a block
 *              of memory.
 * @param       ptr     The block of memory to deallocate.
 * @param       info    An untyped pointer to program-defined data.
 * @discussion  A prototype for a function callback that deallocates a given
 *              block of memory. In implementing this function, make the block
 *              of memory pointed to by ptr available for subsequent reuse by
 *              the allocator but unavailable for continued use by the program.
 *              The ptr parameter cannot be NULL and if the ptr parameter is not
 *              a block of memory that has been previously allocated by the
 *              allocator, the results are undefined; abnormal program
 *              termination can occur.
 */
typedef void ( * CFAllocatorDeallocateCallBack )( void * ptr, void * info );

/*!
 * @typedef     CFAllocatorPreferredSizeCallBack
 * @abstract    A prototype for a function callback that gives the size of
 *              memory likely to be allocated, given a certain request.
 * @param       size    The amount of memory requested.
 * @param       hint    A bitfield that is currently not used (always set to 0).
 * @param       info    An untyped pointer to program-defined data.
 * @result      The actual size the allocator is likely to allocate given this
 *              request.
 * @discussion  A prototype for a function callback that determines whether
 *              there is enough free memory to satisfy a request. In
 *              implementing this function, return the actual size the allocator
 *              is likely to allocate given a request for a block of memory of
 *              size size. The hint argument is a bitfield that you should
 *              currently not use.
 */
typedef CFIndex ( * CFAllocatorPreferredSizeCallBack )( CFIndex size, CFOptionFlags hint, void * info );

/*!
 * @typedef     CFAllocatorContext
 * @abstract    A structure that defines the context or operating environment
 *              for an allocator (CFAllocator) object. Every Core Foundation
 *              allocator object must have a context defined for it.
 * @field       version             An integer of type CFIndex. Assign the
 *                                  version number of the allocator. Currently
 *                                  the only valid value is 0.
 * @field       info                An untyped pointer to program-defined data.
 *                                  Allocate memory for this data and assign a
 *                                  pointer to it. This data is often control
 *                                  information for the allocator. You may
 *                                  assign NULL.
 * @field       retain              A prototype for a function callback that
 *                                  retains the data pointed to by the info
 *                                  field. In implementing this function, retain
 *                                  the data you have defined for the allocator
 *                                  context in this field. (This might make
 *                                  sense only if the data is a Core Foundation
 *                                  object.) You may set this function pointer
 *                                  to NULL.
 * @field       release             A prototype for a function callback that
 *                                  releases the data pointed to by the info
 *                                  field. In implementing this function,
 *                                  release (or free) the data you have defined
 *                                  for the allocator context. You may set this
 *                                  function pointer to NULL, but doing so might
 *                                  result in memory leaks.
 * @field       copyDescription     A prototype for a function callback that
 *                                  provides a description of the data pointed
 *                                  to by the info field. In implementing this
 *                                  function, return a reference to a CFString
 *                                  object that describes your allocator,
 *                                  particularly some characteristics of your
 *                                  program-defined data. You may set this
 *                                  function pointer to NULL, in which case Core
 *                                  Foundation will provide a rudimentary
 *                                  description.
 * @field       allocate            A prototype for a function callback that
 *                                  allocates memory of a requested size. In
 *                                  implementing this function, allocate a block
 *                                  of memory of at least size bytes and return
 *                                  a pointer to the start of the block. The
 *                                  hint argument is a bitfield that you should
 *                                  currently not use (that is, assign 0). The
 *                                  size parameter should always be greater than
 *                                  0. If it is not, or if problems in
 *                                  allocation occur, return NULL. This function
 *                                  pointer may not be assigned NULL.
 * @field       reallocate          A prototype for a function callback that
 *                                  reallocates memory of a requested size for
 *                                  an existing block of memory. In implementing
 *                                  this function, change the size of the block
 *                                  of memory pointed to by ptr to the size
 *                                  specified by newsize and return the pointer
 *                                  to the larger block of memory. Return NULL
 *                                  on any reallocation failure, leaving the old
 *                                  block of memory untouched.
 * @field       deallocate          A prototype for a function callback that
 *                                  deallocates a given block of memory. In
 *                                  implementing this function, make the block
 *                                  of memory pointed to by ptr available for
 *                                  subsequent reuse by the allocator but
 *                                  unavailable for continued use by the
 *                                  program. The ptr parameter cannot be NULL
 *                                  and if the ptr parameter is not a block of
 *                                  memory that has been previously allocated by
 *                                  the allocator, the results are undefined;
 *                                  abnormal program termination can occur. You
 *                                  can set this callback to NULL, in which case
 *                                  the CFAllocatorDeallocate function has no
 *                                  effect.
 * @field       preferredSize       A prototype for a function callback that
 *                                  determines whether there is enough free
 *                                  memory to satisfy a request. In implementing
 *                                  this function, return the actual size the
 *                                  allocator is likely to allocate given a
 *                                  request for a block of memory of size size.
 *                                  The hint argument is a bitfield that you
 *                                  should currently not use.
 */
typedef struct
{
    CFIndex                             version;
    void                              * info;
    CFAllocatorRetainCallBack           retain;
    CFAllocatorReleaseCallBack          release;        
    CFAllocatorCopyDescriptionCallBack	copyDescription;
    CFAllocatorAllocateCallBack         allocate;
    CFAllocatorReallocateCallBack       reallocate;
    CFAllocatorDeallocateCallBack       deallocate;
    CFAllocatorPreferredSizeCallBack    preferredSize;
}
CFAllocatorContext;

/*!
 * @function    CFAllocatorGetTypeID
 * @abstract    Returns the type identifier for the CFAllocator opaque type.
 * @result      The type identifier for the CFAllocator opaque type.
 */
CF_EXPORT CFTypeID CFAllocatorGetTypeID( void );

/*!
 * @function    CFAllocatorCreate
 * @abstract    Creates an allocator object.
 * @param       allocator   The existing allocator to use to allocate memory for
 *                          the new allocator. Pass the kCFAllocatorUseContext
 *                          constant for this parameter to allocate memory using
 *                          the appropriate function callback specified in the
 *                          context parameter. Pass NULL or kCFAllocatorDefault
 *                          to allocate memory for the new allocator using the
 *                          default allocator.
 * @param       context     A structure of type CFAllocatorContext. The fields
 *                          of this structure hold (among other things) function
 *                          pointers to callbacks used for allocating,
 *                          reallocating, and deallocating memory.
 * @result      The new allocator object, or NULL if there was a problem
 *              allocating memory. Ownership follows the Create Rule..
 * @discussion  You use this function to create custom allocators which you can
 *              then pass into various Core Foundation object-creation
 *              functions. You must implement a function callback that allocates
 *              memory and assign it to the allocate field of this structure.
 *              You typically also implement deallocate, reallocate, and
 *              preferred-size callbacks.
 */
CF_EXPORT CFAllocatorRef CFAllocatorCreate( CFAllocatorRef allocator, CFAllocatorContext * context );

/*!
 * @function    CFAllocatorAllocate
 * @abstract    Allocates memory using the specified allocator.
 * @param       allocator   The allocator to use to allocate the memory. Pass
 *                          NULL or kCFAllocatorDefault to use the current
 *                          default allocator.
 * @param       size        The size of the memory to allocate.
 * @param       hint        A bitfield containing flags that suggest how memory
 *                          is to be allocated. 0 indicates no hints. No hints
 *                          are currently defined, so only 0 should be passed
 *                          for this value.
 * @result      A pointer to the newly allocated memory.
 */
CF_EXPORT void * CFAllocatorAllocate( CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint );

/*!
 * @function    CFAllocatorDeallocate
 * @abstract    Deallocates a block of memory with a given allocator.
 * @param       allocator   The allocator that was used to allocate the block of
 *                          memory pointed to by ptr.
 * @param       ptr         An untyped pointer to a block of memory to
 *                          deallocate using allocator.
 * @discussion  If the allocator does not specify a deallocate callback
 *              function, the memory is not deallocated.
 *              You must use the same allocator to deallocate memory as was used
 *              to allocate it.
 */
CF_EXPORT void CFAllocatorDeallocate( CFAllocatorRef allocator, void * ptr );

/*!
 * @function    CFAllocatorGetPreferredSizeForSize
 * @abstract    Obtains the number of bytes likely to be allocated upon a
 *              specific request.
 * @param       allocator   The allocator to use, or NULL for the default
 *                          allocator.
 * @param       size        The number of bytes to allocate. If the value is 0
 *                          or less, the result is the same value.
 * @param       hint        A bitfield of type CFOptionsFlags. Pass flags to the
 *                          allocator that suggest how memory is to be
 *                          allocated. 0 indicates no hints. No hints are
 *                          currently defined, only 0 should be passed for this
 *                          argument.
 * @result      The number of bytes likely to be allocated upon a specific
 *              request.
 * @discussion  The return value depends on the allocator's internal allocation
 *              strategy, and will be equal to or larger than size. Calling this
 *              function may help you better match your memory allocation or
 *              reallocation strategy to that of the allocator.
 *              Note that the return value depends on the internal
 *              implementation of the allocator and the results may change from
 *              release to release or from platform to platform.
 *              If no function callback is assigned to the preferredSize field
 *              of the allocator's context (see the CFAllocatorContext
 *              structure), then the value of size is returned.
 */
CF_EXPORT CFIndex CFAllocatorGetPreferredSizeForSize( CFAllocatorRef allocator, CFIndex size, CFOptionFlags hint );

/*!
 * @function    CFAllocatorReallocate
 * @abstract    Reallocates memory using the specified allocator.
 * @param       allocator   The allocator to use for reallocating memory. Pass
 *                          NULL to request the default allocator.
 * @param       ptr         An untyped pointer to a block of memory to
 *                          reallocate to a new size. If ptr is NULL and newsize
 *                          is greater than 0, memory is allocated (using the
 *                          allocate function callback of the allocator's
 *                          context). If ptr is NULL and newsize is 0, the
 *                          result is NULL.
 * @param       newsize     The number of bytes to allocate. If you pass 0 and
 *                          the ptr parameter is non-NULL, the block of memory
 *                          that ptr points to is typically deallocated. If you
 *                          pass 0 for this parameter and the ptr parameter is
 *                          NULL, nothing happens and the result returned is
 *                          NULL.
 * @param       hint        A bitfield of type CFOptionsFlags. Pass flags to the
 *                          allocator that suggest how memory is to be
 *                          allocated. Zero indicates no hints. No hints are
 *                          currently defined, only 0 should be passed for this
 *                          argument.
 * @result      The reallocated memory or NULL to indicate failure.
 * @dicussion   The CFAllocatorReallocate function's primary purpose is to
 *              reallocate a block of memory to a new (and usually larger) size.
 *              However, based on the values passed in certain of the
 *              parameters, this function can also allocate memory afresh or
 *              deallocate a given block of memory. The following summarizes the
 *              semantic combinations:
 *                  - If the ptr parameter is non-NULL and the newsize parameter
 *                    is greater than 0, the behavior is to reallocate.
 *                  - If the ptr parameter is NULL and the newsize parameter is
 *                    greater than 0, the behavior is to allocate.
 *                  - If the ptr parameter is non- NULL and the newsize
 *                    parameter is 0, the behavior is to deallocate.
 *              The result of the CFAllocatorReallocate function is either an
 *              untyped pointer to a block of memory or NULL. A NULL result
 *              indicates either a failure to allocate memory or some other
 *              outcome, the precise interpretation of which is determined by
 *              the values of certain parameters and the presence or absence of
 *              callbacks in the allocator context. To summarize, a NULL result
 *              can mean one of the following:
 *                  - An error occurred in the attempt to allocate memory, such
 *                    as insufficient free space.
 *                  - No allocate, reallocate, or deallocate function callback
 *                    (depending on parameters) was defined in the allocator
 *                    context.
 *                  - The semantic operation is "deallocate" (that is, there is
 *                    no need to return anything).
 *                  - The ptr parameter is NULL and the requested size is 0.
 */
CF_EXPORT void * CFAllocatorReallocate( CFAllocatorRef allocator, void * ptr, CFIndex newsize, CFOptionFlags hint );

/*!
 * @function    CFAllocatorGetDefault
 * @abstract    Gets the default allocator object for the current thread.
 * @result      A reference to the default allocator for the current thread.
 *              If none has been explicitly set, returns the generic system
 *              allocator, kCFAllocatorSystemDefault. Ownership follows The Get
 *              Rule.
 * @discussion  See the discussion for CFAllocatorSetDefault for more detail on
 *              the default allocator and for advice on how and when to set a
 *              custom allocator as the default.
 */
CF_EXPORT CFAllocatorRef CFAllocatorGetDefault( void );

/*!
 * @function    CFAllocatorSetDefault
 * @abstract    Sets the given allocator as the default for the current thread.
 * @param       allocator   The allocator to set as the default for the current
 *                          thread.
 * @discussion  The CFAllocatorSetDefault function sets the allocator that is
 *              used in the current thread whenever NULL is specified as an
 *              allocator argument. Generally, most allocations use the default
 *              allocator. Because of this, the default allocator must be
 *              prepared to deal with arbitrary memory-allocation requests.
 *              In addition, the size and number of requests can change between
 *              releases.
 *              A further characteristic of the default allocator is that it can
 *              never be released, even if another allocator replaces it as the
 *              default. Not only is it impractical to release a default
 *              allocator (because there might be caches created somewhere that
 *              refer to the allocator) but it is generally safer and more
 *              efficient to keep it around.
 *              If you wish to use a custom allocator in a context, the best
 *              approach is to specify it in the first parameter of creation
 *              functions rather than to set it as the default. Generally,
 *              setting the default allocator is not encouraged. If you do set
 *              an allocator as the default, either do it for the life time of
 *              your application or do it in a nested fashion (that is, restore
 *              the previous allocator before you exit your context). The latter
 *              approach might be more appropriate for plug-ins or libraries
 *              that wish to set the default allocator.
 */
CF_EXPORT void CFAllocatorSetDefault( CFAllocatorRef allocator );

/*!
 * @function    CFAllocatorGetContext
 * @abstract    Obtains the context of the specified allocator or of the default
 *              allocator.
 * @param       allocator   The allocator to examine. Pass NULL to obtain the
 *                          context of the default allocator.
 * @param       context     On return, contains the context of allocator.
 * @discussion  An allocator's context, a structure of type CFAllocatorContext,
 *              holds pointers to various function callbacks (particularly those
 *              that allocate, reallocate, and deallocate memory for an object).
 *              The context also contains a version number and the info field
 *              for program-defined data. To obtain the value of the info field
 *              you usually first have to get an allocator's context.
 */
CF_EXPORT void CFAllocatorGetContext( CFAllocatorRef allocator, CFAllocatorContext * context );

CF_EXTERN_C_END

#endif /* CORE_FOUNDATION_CF_ALLOCATOR_H */
