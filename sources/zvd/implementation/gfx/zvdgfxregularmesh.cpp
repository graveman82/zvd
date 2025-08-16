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
Purpose: regular mesh for graphics class implementation.

----------------------
 For developers notes
----------------------

*/

#include "gfx/zvdgfxregularmesh.h"
#include "core/base/zvdcommonutils.h"
#include "core/base/zvdassert.h"

ZvdUInt32
ZvdGfxRegularMesh::CalcPrimitiveCount(ZvdeGfxPrimitiveType ePrimitiveType, ZvdUInt32 nElements)
{
    ZvdUInt32 nPrimitives = 0;
    switch (ePrimitiveType)
    {
    case kZVD_GFX_PRIMITIVE_TRIANGLESTRIP:
        if (nElements < 3)
            return 0;
        nPrimitives = nElements - 2;
        break;
    case kZVD_GFX_PRIMITIVE_TRIANGLELIST:
        if (nElements < 3)
            return 0;
        nPrimitives = nElements / 3;
        break;
    case kZVD_GFX_PRIMITIVE_LINELIST:
        if (nElements < 2)
            return 0;
        nPrimitives = ZvdFastDivideBy2(nElements);
        break;
    case kZVD_GFX_PRIMITIVE_LINESTRIP:
        if (nElements < 2)
            return 0;
        nPrimitives = nElements - 1;
        break;
    case kZVD_GFX_PRIMITIVE_POINTLIST:
        nPrimitives = nElements;
        break;
    case kZVD_GFX_PRIMITIVE_QUADLIST:
        if (nElements < 4)
            return 0;
        nPrimitives = ZvdFastDivideBy4(nElements);
        break;
    default:
        ZVD_ASSERT_HIGH(false, "can't be reached");
        break;
    }
    return nPrimitives;
}
