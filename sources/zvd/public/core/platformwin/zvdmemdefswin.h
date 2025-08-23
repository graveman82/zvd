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
Purpose: memory management related definitions (windows based systems).

----------------------
 For developers notes
----------------------
Attention: don't include this file directly! Use zvdmemdefs.h instead.
*/

#ifndef ZVD_MEMDEFSWIN_H
#define ZVD_MEMDEFSWIN_H

#include "core/base/zvdbasedefs.h"

#if defined(ZVD_PLATFORM_XBOX360) || defined(ZVD_PLATFORM_WIN32) || defined(ZVD_PLATFORM_WIN64) 

//-----------------------------------------------------------------------------
// Macro utils
#define ZVD_ALIGN_OF(T) __alignof(T)
#define ZVD_ALIGN_CLASS_BEGIN(T) __declspec(align(T))
#define ZVD_ALIGN_CLASS_END(T)

//-----------------------------------------------------------------------------
// Memory allocation functions prototypes pointers
typedef ZvdpVoid	(ZVD_CDECL* Zvdfpt_malloc)(size_t nBytes);
typedef ZvdpVoid	(ZVD_CDECL* Zvdfpt_realloc)(ZvdpVoid pMemBlock, size_t nNewBytes);
typedef void		(ZVD_CDECL* Zvdfpt_free)(ZvdpVoid _Memory);

typedef ZvdpVoid	(ZVD_CDECL* Zvdfpt_aligned_malloc)(size_t nBytes, size_t nAlignment);
typedef ZvdpVoid	(ZVD_CDECL* Zvdfpt_aligned_realloc)(ZvdpVoid pMemBlock, size_t nBytes, size_t nAlignment);
typedef void		(ZVD_CDECL* Zvdfpt_aligned_free)(ZvdpVoid pMemBlock);

typedef ZvdpVoid	(ZVD_CDECL* Zvdfpt_malloca)(size_t nBytes);
typedef void		(ZVD_CDECL* Zvdfpt_freea)(ZvdpVoid pMemBlock);

#endif // eof (XBox or Win32 or Win64)

#endif // ZVD_MEMDEFSWIN_H