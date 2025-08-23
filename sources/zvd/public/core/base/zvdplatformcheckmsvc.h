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
Purpose: detect the target operating system.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_PLATFORMCHECKMSVC_H
#define ZVD_PLATFORMCHECKMSVC_H

#ifndef ZVD_COMPILER_MSVC
#error "This file is for microsoft c++ compiler only"
#endif
//-------------------------------
// Identify the Operating System



#ifdef _GAMING_XBOX
// all Xbox 

#	ifdef _GAMING_XBOX_SCARLETT
#		if !defined(ZVD_PLATFORM_XBOX_SCARLETT)
#			define ZVD_PLATFORM_XBOX_SCARLETT
#			define ZVD_OS_XBOX
#			define ZVD_OS_STRING "XBoxScarlett"
#			define ZVD_LITTLE_ENDIAN 1
#			pragma message("Platform: XBoxScarlett")
#		endif

#	else
#		error "too old xbox version - unsupported"

#	endif

#elif defined(_WIN64)
#	if !defined(ZVD_PLATFORM_WIN64)
#		define ZVD_PLATFORM_WIN64
#		define ZVD_OS_WINDOWS64
#		define ZVD_OS_STRING "Win64"
#       if !defined(ZVD_OS_64)
#           define ZVD_OS_64
#       endif
#		pragma message("Platform: Win64")
#	endif


#elif (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined ( _WIN64 )
#   error "32 bit platform is not supported"

#else
#   error "Your platform is not identified"

#endif


// Test to define how much bit processor architecture has.
//--------------------------------------------------------

// test x86
#if defined(_M_IX86)
#	if !defined(ZVD_ARCH_X86)
#		define ZVD_ARCH_X86
#		define ZVD_LITTLE_ENDIAN 1
#	endif
#endif

// test x64
#if defined(_M_X64)
#	if !defined(ZVD_ARCH_X64)
#		define ZVD_ARCH_X64
#		define ZVD_LITTLE_ENDIAN 1
#	endif
#endif

#endif // ZVD_PLATFORMCHECKMSVC_H