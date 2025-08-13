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
Purpose: blank file for headers.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_GFXDEFSDX9_H
#define ZVD_GFXDEFSDX9_H

#include <d3d9.h>
#include <d3dx9math.h>

// Type aliases for Direct3D interface pointers
typedef LPDIRECT3DDEVICE9 ZvdpD3dDevice9;
typedef LPDIRECT3DRESOURCE9 ZvdpD3dResource9;
typedef LPDIRECT3DSURFACE9 ZvdpD3dSurface9;
typedef LPDIRECT3DBASETEXTURE9 ZvdpD3dBaseTexture9;
typedef LPDIRECT3DTEXTURE9 ZvdpD3dTexture9;
typedef LPDIRECT3DVERTEXBUFFER9 ZvdpD3dVertexBuffer9;
typedef LPDIRECT3DINDEXBUFFER9 ZvdpD3dIndexBuffer9;

#endif // ZVD_GFXDEFSDX9_H