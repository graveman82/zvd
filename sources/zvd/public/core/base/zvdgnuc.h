/*
-----------------
 Persistent info
-----------------

This file is part of the "Zv3D" project.

MIT License

Copyright (c) 2012-2099 Marat Sungatullin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

......
 Web:
......

 + https:// (for questions and help)

-------------
 Description
-------------
Purpose: GNU C compiler detection macros.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_GNUC_H
#define ZVD_GNUC_H

// correct header validation
#if !defined(ZVD_GNUC)
#   error "zvd: this file must be included by zvdcompiler.h"
#endif // correct header validation


#define ZVD_GCC_VER_PACKED_TO_INT(major,minor,patch) \
(major * 10000 + minor * 100 + patch)

#define ZVD_GCC_CUR_VER_PACKED_TO_INT \
ZVD_GCC_VER_PACKED_TO_INT(__GNUC__,__GNUC_MINOR__,__GNUC_PATCHLEVEL__)

/**  GCC version helper

Usage
    @code
// Test for GCC >= 8.2.1
#if ZVD_GCC_VER_LESS(8,2,1)
#error "too old version of gcc"
#endif
    @endcode

*/
#define ZVD_GCC_VER_LESS(major,minor,patch) \
(ZVD_GCC_CUR_VER_PACKED_TO_INT < ZVD_GCC_VER_PACKED_TO_INT(major,minor,patch))



/** Macro to get gcc version.
    @code
// Test for GCC >= 8.1.0
#if ZVD_COMPILER_GNUC_VERSION >= 80100
    @endcode
*/
#   define ZVD_COMPILER_GNUC_VERSION ZVD_GCC_CUR_VER_PACKED_TO_INT

/** Macro to check if gcc version is higher than given one.
    @code
// Test for GCC >= 8.1.0
#if ZVD_COMPILER_GNUC_VERSION_OR_HIGHER(8,1,0)
    @endcode
*/
#define ZVD_COMPILER_GNUC_VERSION_OR_HIGHER(major,minor,patchlevel) \
    (!ZVD_GCC_VER_LESS(major,minor,patch))



#endif // ZVD_GNUC_H
