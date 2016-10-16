XS-Labs / CoreFoundation
========================

[![Build Status](https://img.shields.io/travis/macmade/CoreFoundation.svg?branch=master&style=flat)](https://travis-ci.org/macmade/CoreFoundation)
[![Coverage Status](https://img.shields.io/coveralls/macmade/CoreFoundation.svg?branch=master&style=flat)](https://coveralls.io/r/macmade/CoreFoundation?branch=master)
[![Issues](http://img.shields.io/github/issues/macmade/CoreFoundation.svg?style=flat)](https://github.com/macmade/CoreFoundation/issues)
![Status](https://img.shields.io/badge/status-prototype-orange.svg?style=flat)
![License](https://img.shields.io/badge/license-mit-brightgreen.svg?style=flat)
[![Contact](https://img.shields.io/badge/contact-@macmade-blue.svg?style=flat)](https://twitter.com/macmade)

About
-----

This project is a custom implementation of Apple's CoreFoundation framework intended to be used in the [XEOS operating system](http://www.xs-labs.com/en/projects/xeos/) as a base for its Objective-C library.

Actually, the project targets macOS, Linux and Windows, and should compile fine on these platforms.

### Binary compatibility

Note that this implementation is **NOT** binary compatible with Apple's own implementation.

While the public interface is strictly identical, the private runtime functions and data structures are completely different, so don't expect them to be compatible with libraries using Apple's version of CoreFoundation.

### Building CoreFoundation

 - **macOS**  
   Use the provided xCode project, or use the provided makefile.
 - **Linux**  
   Use the provided makefile.
 - **Windows**  
   Use the provided VisualStudio project.

### Improvements

#### 1 - NULL checking:

This implementation is designed to be safer than Apple's implementation regarding `NULL` pointers.  
While Apple's implementation usually invokes undefined behaviour when passing `NULL` pointers as CF objects, and actually crashes most of the time in such a case, this implementation does not.

All functions/methods actually checks for `NULL`, and won't crash because of this.  
The behaviour is much more similar to Objective-C, where it's usually valid to use `nil` for objects.

#### 2 - Memory leak detection:

The actual implementation of `CFAllocator` can detect and report memory leaks.

When an allocator is destroyed (exit time for predefined allocators such as `kCFAllocatorDefault`), it will report unfreed memory, providing a description for CoreFoundation objects, making it easier to spot memory leaks in a program.

As an example, the following program:

    #include <CoreFoundation/CoreFoundation.h>
    
    int main( void )
    {
        CFStringRef str;
        
        str = CFStringCreateWithCString
        (
            kCFAllocatorDefault,
            "hello, world",
            kCFStringEncodingASCII
        );
        
        return 0;
    }
        
Will report the following:

    *** [ CoreFoundation - WARNING ]
    *** Deleting an instance of CFAllocator while allocations are still active.
    *** Leaking memory.
    
    - Allocator:       <CFAllocator 0x1000ac748 [ 0x0 ]> { info = 0x0 } kCFAllocatorSystemDefault
    - Active records:  2    
    - Records:
    {
        1. <CFString 0x100202450 [ kCFAllocatorSystemDefault ]> hello, world
        2. 0x1002000a0
    }

### Available/Completed classes

- [x] **CFAllocator**
- [x] **CFBoolean**
- [x] **CFData**
- [x] **CFDictionary**
- [x] **CFError**
- [x] **CFMutableDictionary**
- [x] **CFNull**
- [x] **CFType** (generic type methods)
- [x] **CFUUID**

### Partially available classes

- [ ] **CFString** (no encoding support)
- [ ] **CFMutableString** (no encoding support)
- [ ] **CFNotificationCenter** (work in progress)
- [ ] **CFNumber** (work in progress)

### Creating custom CoreFoundation classes

This implementation obviously supports custom classes, meaning you can use it as a base for a complete project, if you need object-oriented programming style in C with reference-counted objects.

Here's an example for the public declaration of a custom CoreFoundation class:

`Foo.h`

    #include <CoreFoundation/CoreFoundation.h>
    
    #ifndef FOO_H
    #define FOO_H
    
    typedef struct Foo * FooRef; // Opaque type for your class
    
    CFTypeID    FooGetTypeID( void );                               // Returns the type ID of your class
    FooRef      FooCreate( CFAllocatorRef alloc, CFStringRef str ); // Creates an instance of your class
    CFStringRef FooGetString( FooRef foo );                         // Member method
    
    #endif
    
And here's the implementation:

`Foo.c`

    #include "Foo.h"
    #include <CoreFoundation/__private/__CFRuntime.h>
    
    // Member fields
    struct Foo
    {
        CFRuntimeBase _base; // Mandatory first field
        CFStringRef   _str;
    };
    
    // Type ID for your class
    static CFTypeID FooTypeID = 0;
    
    // Class destructor
    static void FooDestruct( FooRef foo );
    
    // Your class
    CFRuntimeClass FooClass  =
    {
        "Foo",                                  // Class name
        sizeof( struct Foo ),                   // Instance size
        NULL,                                   // Constructor
        ( void ( * )( CFTypeRef ) )FooDestruct, // Destructor
        NULL,                                   // Hash
        NULL,                                   // Equality
        NULL                                    // Copy description
    };
    
    static void init( void ) __attribute__( ( constructor ) );
    static void init( void )
    {
        // Registers the custom class
        FooTypeID = CFRuntimeRegisterClass( &FooClass );
    }
    
    // Class destructor
    static void FooDestruct( FooRef foo )
    {
        CFRelease( foo->_str );
    }
    
    // Returns the type ID of your class
    CFTypeID FooGetTypeID( void )
    {
        return FooTypeID;
    }
    
    // Creates an instance of your class
    FooRef FooCreate( CFAllocatorRef alloc, CFStringRef str )
    {
        struct Foo * foo;
        
        // Creates an instance, using the type ID
        foo = ( struct Foo * )CFRuntimeCreateInstance( alloc, FooTypeID );
        
        // Member initialization
        if( foo )
        {
            foo->_str = CFRetain( str );
        }
        
        return foo;
    }
    
    // Member method
    CFStringRef FooGetString( FooRef foo )
    {
        return ( foo ) ? foo->_str : NULL;
    }
    
License
-------

XS-Labs' implementation of CoreFoundation is released under the terms of the MIT License.

Repository Infos
----------------

    Owner:			Jean-David Gadina - XS-Labs
    Web:			www.xs-labs.com
    Blog:			www.noxeos.com
    Twitter:		@macmade
    GitHub:			github.com/macmade
    LinkedIn:		ch.linkedin.com/in/macmade/
    StackOverflow:	stackoverflow.com/users/182676/macmade
