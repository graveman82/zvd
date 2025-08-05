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
Purpose: memory allocation routines.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_MEMALLOC_H
#define ZVD_MEMALLOC_H

#include "core/system/memory/zvdmemdefs.h"


#if defined(ZVD_PLATFORM_PS3)

#include "core/platformwin/zvdmemallocps3.h"

#elif defined (ZVD_PLATFORM_LINUX)

#include "core/platformwin/zvdmemallocposix.h"

#elif defined(ZVD_PLATFORM_XBOX360) || defined(ZVD_PLATFORM_WIN32) || defined(ZVD_PLATFORM_WIN64) 

#include "core/platformwin/zvdmemallocwin.h"

#endif

void* __cdecl ZvdfAlignedMalloc(ZvdSize nBytes, ZvdSize nAlignment);
void* __cdecl ZvdfAlignedRealloc(void* pMemblockOld, ZvdSize nOldBytes, ZvdSize nBytes, ZvdSize nAlignment);
void __cdecl ZvdfAlignedFree(void* pMemblock);

void* __cdecl ZvdfStackAlloc(ZvdSize nBytes);
void __cdecl ZvdfStackFree(void* pMemblock);
#endif // ZVD_MEMALLOC_H