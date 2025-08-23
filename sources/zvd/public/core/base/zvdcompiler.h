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
Purpose: compiler detection and related definitions.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_COMPILER_H
#define ZVD_COMPILER_H

//=============================================================================
// Compiler detection and related helpers.
//=============================================================================


//-----------------------------------------------------------------------------
// Compilers family detection

#if defined(_MSC_VER) && !defined(ZVD_MSVC)
// Microsoft Visual C++ compiler
#	define ZVD_COMPILER_MSVC
#	define ZVD_COMPILER_VER _MSC_VER
/* define zvd-scope symbol for Microsoft Visual C++.
*/
#	define ZVD_MSVC _MSC_VER

#elif defined(__GNUC__) && !defined(ZVD_GNUC)
#	define ZVD_COMPILER_GCC
#	define ZVD_COMPILER_VER __GNUC__
/* define zvd-scope symbol for gnu cpp compiler.
*/
#	define ZVD_GNUC __GNUC__// GNU C compilers

#else
#	error "No supported compiler was found."

#endif // compiler detection


// GNU C compiler related header for further detections
#if defined(ZVD_COMPILER_GCC)
#	include "core/base/zvdgnuc.h"
#	if !ZVD_COMPILER_GNUC_VERSION_OR_HIGHER(ZVD_CFG_MIN_GNUC_MAJOR,\
		ZVD_CFG_MIN_GNUC_MINOR,ZVD_CFG_MIN_GNUC_PATCHLEVEL)
#		error "too old gcc version"
#	endif
#endif

// Microsoft Visual C++ compiler related header for further detections
#if defined(ZVD_COMPILER_MSVC)
#	include "core/base/zvdmsvc.h"
#	if (ZVD_COMPILER_MSVC_VERSION_LESS_THAN(ZVD_CFG_MIN_MSVC_VER))
#		error "unsupported VC version -- its too old; you need VC 2022 (17.0) or higher"
#	endif
#endif


//-----------------------------------------------------------------------------
// C++ standard detection

// In Visual Studio add:
// /Zc:__cplusplus
// in project command line additional parameters field
// https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus?view=msvc-170
#if (__cplusplus==202302L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP23 __cplusplus
#   define ZVD_CPP20 202002L
#   define ZVD_CPP17 201703L
#   define ZVD_CPP14 201402L
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++23")

#elif(__cplusplus == 202002L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP20 __cplusplus
#   define ZVD_CPP17 201703L
#   define ZVD_CPP14 201402L
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++20")

#elif(__cplusplus == 201703L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP17 __cplusplus
#   define ZVD_CPP14 201402L
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++17")

#elif(__cplusplus == 201402L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP14 __cplusplus
#   define ZVD_CPP11 201103L
#   define ZVD_CPP03 199711L
#	pragma message("C++14")

#elif(__cplusplus == 201103L)
#   define ZVD_CPP11 __cplusplus
#   define ZVD_CPP03 199711L
#	pragma message("C++11")

#elif(__cplusplus == 199711L)
#   define ZVD_CPP __cplusplus
#   define ZVD_CPP03 __cplusplus
#	pragma message("C++98")

#else
#error "No any standart of C++ detected. You can comment this line for your own risk!"
//#define ZVD_CPP __cplusplus
//#define ZVD_CPP98 // 98/03 ?

#endif // C++ standard detection end

#ifndef ZVD_CPP
#   error "No required C++ standard is supported by current compiler!"
#endif

#ifndef ZVD_CPP20
#	error "too old C++ standard, you need 20 or higher"
#endif

#endif // ZVD_COMPILER_H
