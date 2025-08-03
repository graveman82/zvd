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
Purpose: std-like string utils.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_STD_STRING_UTILS_H
#define ZVD_STD_STRING_UTILS_H

#include "core/base/zvdbasedefs.h"



#if defined(ZVD_MSVC) && ZVD_COMPILER_MSVC_VERSION_OR_HIGHER(ZVD_VISUAL_STUDIO_2005_8_x_0)
#define ZVD_CSTR_TRUNCATE _TRUNCATE
#else
#define ZVD_CSTR_TRUNCATE ((ZVD_CFG_MAX_CSTR_LEN)-1)
#endif

ZvdSize Zvdf_strlen(const char* str);
ZvdSize Zvdf_snprintf(char* pDest, ZvdSize nDestSize, ZvdSize nCount, char const* pFormat, ...);
ZvdSize Zvdf_vsnprintf(char* pDest, ZvdSize nDestSize, ZvdSize nCount, char const* pFormat, va_list params);
#endif // ZVD_STD_STRING_UTILS_H