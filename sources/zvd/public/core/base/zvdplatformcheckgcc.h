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

#ifndef ZVD_PLATFORMCHECKGCC_H
#define ZVD_PLATFORMCHECKGCC_H

//-------------------------------
// Identify the Operating System

#if defined(_WIN64)
#	if !defined(ZVD_PLATFORM_WIN64)
#		define ZVD_PLATFORM_WIN64
#		define ZVD_OS_WINDOWS64
#		define ZVD_OS_STRING "Win64"
#       if !defined(ZVD_OS_64)
#           define ZVD_OS_64
#       endif
#	endif


#elif defined(_WIN32) || defined(__WIN32__)  || defined(WIN32)
#	if !defined(ZVD_PLATFORM_WIN32)
#		define ZVD_PLATFORM_WIN32
#		define ZVD_OS_WINDOWS32
#		define ZVD_OS_STRING "Win32"
#	endif


#elif defined(__linux__) || defined(linux)
#   if !defined(ZVD_PLATFORM_LINUX)
#       define ZVD_PLATFORM_LINUX
#		define ZVD_OS_LINUX
#		define ZVD_OS_STRING "Linux"
#   endif


#elif defined(SN_TARGET_PS3) || defined(_PS3) || defined(PS3)
#   if !defined(ZVD_PLATFORM_PS3)
#       define ZVD_PLATFORM_PS3
#		define ZVD_OS_PS3
#		define ZVD_OS_STRING "PS3"
#   endif


#elif defined(__APPLE__)
#   if !defined(ZVD_PLATFORM_MACOS)
#       define ZVD_PLATFORM_MACOS
#		define ZVD_OS_MACOS
#		define ZVD_OS_STRING "MacOS"
#   endif


#else
#   error "Your platform is not identified"
#endif


#endif // ZVD_PLATFORMCHECKGCC_H