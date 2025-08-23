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
Purpose: memory allocation implementation (posix).

----------------------
 For developers notes
----------------------

*/


#include "core/base/zvdassert.h"


#include "core/base/zvderror.h"
#include "core/system//memory/zvdmemdefs.h"
#include "core/base/zvdcommonmacros.h"

#include <malloc.h>

#if defined (ZVD_PLATFORM_LINUX)

#include <alloca.h>

Zvdfpt_aligned_malloc Zvdfp_aligned_malloc = memalign;
Zvdfpt_realloc Zvdfp_realloc = realloc;
Zvdfpt_free Zvdfp_free = free;

Zvdfpt_alloca Zvdfp_alloca = alloca;

//-----------------------------------------------------------------------------
void* __cdecl ZvdfAlignedMalloc(size_t nBytes, size_t nAlignment)
{
    void* pResultMem = nullptr;

	pResultMem = Zvdfp_aligned_malloc(nAlignment, nBytes);
	
    return pResultMem;
}

//-----------------------------------------------------------------------------
void* __cdecl ZvdfAlignedRealloc(void* pMemblockOld, size_t nOldBytes, size_t nBytes, size_t nAlignment)
{
    void* pResultMem = nullptr;

    void* pMemblockNew = Zvdfp_aligned_malloc(nAlignment, nBytes);
    if (!pMemblockNew)
    {
        return nullptr;
    }

    // Copy data from old block to new block
    if (pMemblock) 
    {
        size_t nBytesToCopy = ZvdfMin(nOldBytes, nBytes);
        Zvdf_memcpy(pMemblockNew, pMemblock, nBytesToCopy);
        Zvdfp_free(pMemblock);
    }

    pResultMem = pMemblockNew;
    
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
void* __cdecl ZvdfStackAlloc(size_t nBytes)
{
    void* pResultMem = nullptr;

    pResultMem = Zvdfp_alloca(nBytes);

    return pResultMem;
}

//-----------------------------------------------------------------------------
void __cdecl ZvdfStackFree(void* pMemblock)
{
    if (!pMemblock)
        return;

    // do nothing
}

#endif