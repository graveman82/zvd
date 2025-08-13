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
Purpose: memory allocation routines (windows based systems).

----------------------
 For developers notes
----------------------
Attention: don't include this file directly! Use zvdmemalloc.h instead.
*/

#ifndef ZVD_MEMALLOCWIN_H
#define ZVD_MEMALLOCWIN_H

#include "core/system/memory/zvdmemdefs.h"

#if defined(ZVD_PLATFORM_XBOX360) || defined(ZVD_PLATFORM_WIN32) || defined(ZVD_PLATFORM_WIN64) 

extern Zvdfpt_malloc Zvdfp_malloc;
extern Zvdfpt_realloc Zvdfp_realloc;
extern Zvdfpt_free Zvdfp_free;

extern Zvdfpt_aligned_malloc Zvdfp_aligned_malloc;
extern Zvdfpt_aligned_realloc Zvdfp_aligned_realloc;
extern Zvdfpt_aligned_free Zvdfp_aligned_free;

extern Zvdfpt_malloca Zvdfp_malloca;
extern Zvdfpt_freea Zvdfp_freea;

#endif // eof (XBox or Win32 or Win64)

#endif // ZVD_MEMALLOCWIN_H