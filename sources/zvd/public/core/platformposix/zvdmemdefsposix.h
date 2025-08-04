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
Purpose: memory management related definitions (posix based systems).

----------------------
 For developers notes
----------------------
Attention: don't include this file directly! Use zvdmemdefs.h instead.
*/

#ifndef ZVD_MEMDEFSPOSIX_H
#define ZVD_MEMDEFSPOSIX_H

#include "core/base/zvdbasedefs.h"


#if defined (ZVD_PLATFORM_LINUX)

#define ZVD_ALIGN_OF(T) __alignof__(T)
#define ZVD_ALIGN_CLASS_BEGIN(T)
#define ZVD_ALIGN_CLASS_END(T) __attribute__((aligned(T)))

typedef void* (__cdecl* Zvdfpt_aligned_malloc)(ZvdSize nBoundary, ZvdSize nBytes);
typedef void* (__cdecl* Zvdfpt_realloc)(void* pMemblock, ZvdSize nBytes);
typedef void  (__cdecl* Zvdfpt_free)(void* pMemblock);

typedef void* (__cdecl* Zvdfpt_alloca)(ZvdSize nBytes);

#endif // linux


#endif // ZVD_MEMDEFSPOSIX_H