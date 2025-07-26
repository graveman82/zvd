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

//-------------------------------
// Identify the Operating System


/*.  
Detect for PS3 before win32 to avoid the situation when devenv.exe is used
to batch build a SN VSI project because difficult compile errors  can be 
appeared.
*/
#if defined(SN_TARGET_PS3) || defined(_PS3) || defined(PS3)
#   if !defined(ZVD_PLATFORM_PS3)
#       define ZVD_PLATFORM_PS3
#		define ZVD_OS_PS3
#		define ZVD_OS_STRING "PS3"
#		pragma message("Platform: PS3")
#   endif

/*
*  Warning: _XBOX_VER check must precede _WIN32 check
*/
#elif defined( _XBOX_VER ) || defined(_XENON)
#	if _XBOX_VER >= 200 || defined(_XENON)
#		if !defined(ZVD_PLATFORM_XBOX360)
#			define ZVD_PLATFORM_XBOX360
#			define ZVD_OS_XBOX360
#			define ZVD_OS_STRING "XBox360"
#			pragma message("Platform: XBox360")
#		endif
#	else
#		if !defined(ZVD_PLATFORM_XBOX)
#			define ZVD_PLATFORM_XBOX
#			define ZVD_OS_XBOX
#			define ZVD_OS_STRING "XBox"
#			pragma message("Platform: XBox")
#		endif
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
#	if !defined(ZVD_PLATFORM_WIN32)
#		define ZVD_PLATFORM_WIN32
#		define ZVD_OS_WINDOWS32
#		define ZVD_OS_STRING "Win32"
#		pragma message("Platform: Win32")
#	endif


#else
#   error "Your platform is not identified"
#endif



#endif // ZVD_PLATFORMCHECKMSVC_H