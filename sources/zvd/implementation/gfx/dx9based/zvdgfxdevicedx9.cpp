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
Purpose: blank file for implementations (.cpp files).

----------------------
 For developers notes
----------------------

*/
#include "gfx/dx9based/zvdgfxdevicedx9.h"

static D3DPRIMITIVETYPE g_convertToD3dPrimitiveTypes[6] =
{
    D3DPT_POINTLIST, 
    D3DPT_TRIANGLELIST, 
    D3DPT_TRIANGLESTRIP,
    D3DPT_TRIANGLEFAN, 
    D3DPT_LINELIST, 
    D3DPT_LINESTRIP
};

ZvdRetVal ZvdcGfxDeviceDx9::DrawPrimitives(
    ZvdeGfxPrimitiveType iPrimitiveType,
    ZvdUIndex iStartIndexInIndexBuffer,
    ZvdSize nPrimitiveCount,
    ZvdUIndex iMinIndexInVertexBuffer,
    ZvdSize nNumVertices,
    ZvdUIndex iOffsetInVertexBuffer)
{
    this->m_nTotalPrimitivesRendered += nPrimitiveCount;
    ++this->m_nDrawPrimitivesCalls;
    if (!m_bIndexedPrimitives)
        return this->m_pD3dDevice->DrawPrimitive(
            g_convertToD3dPrimitiveTypes[iPrimitiveType],
            iStartIndexInIndexBuffer,
            nPrimitiveCount);
    if (iMinIndexInVertexBuffer == kZVD_INVALID_INDEX)
    {
        return m_pD3dDevice->DrawIndexedPrimitive(
            g_convertToD3dPrimitiveTypes[iPrimitiveType],
            iOffsetInVertexBuffer,
            0,
            m_nVertexBufferMaxSize,
            iStartIndexInIndexBuffer,
            nPrimitiveCount);
    }
        
    return this->m_pD3dDevice->DrawIndexedPrimitive(

        g_convertToD3dPrimitiveTypes[iPrimitiveType],
        iOffsetInVertexBuffer,
        iMinIndexInVertexBuffer,
        nNumVertices,
        iStartIndexInIndexBuffer,
        nPrimitiveCount);
}