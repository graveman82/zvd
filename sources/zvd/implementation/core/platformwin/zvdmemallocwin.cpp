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
Purpose: memory allocation implementation (windows based systems).

----------------------
 For developers notes
----------------------

*/


#include "core/base/zvdassert.h"
#include "core/base/zvderror.h"
#include "core/system//memory/zvdmemdefs.h"
#include "core/base/zvdcommonmacros.h"

#include <malloc.h>

#if defined(ZVD_PLATFORM_XBOX360) || defined(ZVD_PLATFORM_WIN32) || defined(ZVD_PLATFORM_WIN64)

Zvdfpt_aligned_malloc Zvdfp_aligned_malloc = _aligned_malloc;
Zvdfpt_aligned_realloc Zvdfp_aligned_realloc = _aligned_realloc;
Zvdfpt_aligned_free Zvdfp_aligned_free = _aligned_free;

#ifdef ZVD_DEBUG
Zvdfpt_malloca Zvdfp_malloca = malloc;
Zvdfpt_freea Zvdfp_freea = free;
#else
Zvdfpt_malloca Zvdfp_malloca = _malloca;
Zvdfpt_freea Zvdfp_freea = _freea;
#endif

//-----------------------------------------------------------------------------
void* __cdecl ZvdfAlignedMalloc(ZvdSize nBytes, ZvdSize nAlignment)
{
    void* pResultMem = kZVD_NULLVOID;

	pResultMem = Zvdfp_aligned_malloc(nBytes, nAlignment);

    return pResultMem;
}

//-----------------------------------------------------------------------------
void* __cdecl ZvdfAlignedRealloc(void* pMemblockOld, ZvdSize nOldBytes, ZvdSize nBytes, ZvdSize nAlignment)
{
    void* pResultMem = kZVD_NULLVOID;

    ZVD_UNUSED_ARG(nOldBytes);
    pResultMem = Zvdfp_aligned_realloc(pMemblockOld, nBytes, nAlignment);

    return pResultMem;
}

//-----------------------------------------------------------------------------
void __cdecl ZvdfAlignedFree(void* pMemblock)
{
    if (!pMemblock)
        return;

    Zvdfp_aligned_free(pMemblock);

}

//-----------------------------------------------------------------------------
void* __cdecl ZvdfStackAlloc(ZvdSize nBytes)
{
    void* pResultMem = kZVD_NULLVOID;

    pResultMem = Zvdfp_malloca(nBytes);
    
    return pResultMem;
}

//----------------------------------------------------------------------------- 
void __cdecl ZvdfStackFree(void* pMemblock)
{
    if (!pMemblock)
        return;

    Zvdfp_freea(pMemblock);
}

#endif // eof (XBox or Win32 or Win64)