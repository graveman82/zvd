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
Purpose: Matrix 4 x 4 implementations (.cpp files).

----------------------
 For developers notes
----------------------

*/

#include "core/mathlib/zvdmatrix4x4.h"

template <typename T>
T __stdcall ZvdfDeterminant2x2(	T e11, T e12,
								T e21, T e22)
{
	return e11 * e22 - e21 * e12;
}

template <typename T>
T __stdcall ZvdfDeterminant3x3(T e11, T e12, T e13,
						T e21, T e22, T e23,
						T e31, T e32, T e33)
{
    return e11 * (e22 * e33 - e23 * e32) -
           e12 * (e21 * e33 - e23 * e31) +
           e13 * (e21 * e32 - e22 * e31);

}

template <typename T>
T __stdcall ZvdfMatrixInverse(ZvdsMatrix4x4<T>* pDstMtx, const ZvdsMatrix4x4<T>* pSrcMtx)
{
	T sm11 = pSrcMtx->m[0][0];
	T sm12 = pSrcMtx->m[0][1];
	T sm13 = pSrcMtx->m[0][2];
	T sm14 = pSrcMtx->m[0][3];

	T sm21 = pSrcMtx->m[1][0];
	T sm22 = pSrcMtx->m[1][1];
	T sm23 = pSrcMtx->m[1][2];
	T sm24 = pSrcMtx->m[1][3];

	T sm31 = pSrcMtx->m[2][0];
	T sm32 = pSrcMtx->m[2][1];
	T sm33 = pSrcMtx->m[2][2];
	T sm34 = pSrcMtx->m[2][3];

	T sm41 = pSrcMtx->m[3][0];
	T sm42 = pSrcMtx->m[3][1];
	T sm43 = pSrcMtx->m[3][2];
	T sm44 = pSrcMtx->m[3][3];

	// x x o o
	// x x o o
	// o o o o
	// o o o o
	T d11_12_21_22 = ZvdfDeterminant2x2(sm11, sm12, sm21, sm22);
	// x x o o
	// o o o o
	// x x o o
	// o o o o
	T d11_12_31_32 = ZvdfDeterminant2x2(sm11, sm12, sm31, sm32);
	// x x o o
	// o o o o
	// o o o o
	// x x o o
	T d11_12_41_42 = ZvdfDeterminant2x2(sm11, sm12, sm41, sm42);
	// o o o o
	// x x o o
	// x x o o
	// o o o o
	T d21_22_31_32 = ZvdfDeterminant2x2(sm21, sm22, sm31, sm32);
	// o o o o
	// x x o o
	// o o o o
	// x x o o
	T d21_22_41_42 = ZvdfDeterminant2x2(sm21, sm22, sm41, sm42);
	// o o o o
	// o o o o
	// x x o o
	// x x o o
	T d31_32_41_42 = ZvdfDeterminant2x2(sm31, sm32, sm41, sm42);
	// o o x x
	// o o x x
	// o o o o
	// o o o o
	T d13_14_23_24 = ZvdfDeterminant2x2(sm13, sm14, sm23, sm24);
	// o o x x
	// o o o o
	// o o x x
	// o o o o
	T d13_14_33_34 = ZvdfDeterminant2x2(sm13, sm14, sm33, sm34);
	// o o x x
	// o o o o
	// o o o o
	// o o x x
	T d13_14_43_44 = ZvdfDeterminant2x2(sm13, sm14, sm43, sm44);
	// o o o o
	// o o x x
	// o o x x
	// o o o o
	T d23_24_33_34 = ZvdfDeterminant2x2(sm23, sm24, sm33, sm34);
	// o o o o
	// o o x x
	// o o o o
	// o o x x
	T d23_24_43_44 = ZvdfDeterminant2x2(sm23, sm24, sm43, sm44);
	// o o o o
	// o o o o
	// o o x x
	// o o x x
	T d33_34_43_44 = ZvdfDeterminant2x2(sm33, sm34, sm43, sm44);


	// o o o o
	// o x x x
	// o x x x
	// o x x x
	T aa11 = sm22 * d33_34_43_44 - sm32 * d23_24_43_44 + sm42 * d23_24_33_34;
	// o o o o
	// x o x x
	// x o x x
	// x o x x
	T aa12 = -(sm21 * d33_34_43_44 - sm31 * d23_24_43_44 + sm41 * d23_24_33_34);
	// o o o o
	// x x o x
	// x x o x
	// x x o x
	T aa13 = sm24 * d31_32_41_42 - sm34 * d21_22_41_42 + sm44 * d21_22_31_32;
	// o o o o
	// x x x o
	// x x x o
	// x x x o
	T aa14 = -(sm23 * d31_32_41_42 - sm33 * d21_22_41_42 + sm43 * d21_22_31_32);
	// o x x x
	// o o o o
	// o x x x
	// o x x x
	T aa21 = -(sm12 * d33_34_43_44 - sm32 * d13_14_43_44 + sm42 * d13_14_33_34);
	// x o x x
	// o o o o
	// x o x x
	// x o x x
	T aa22 = sm11 * d33_34_43_44 - sm31 * d13_14_43_44 + sm41 * d13_14_33_34;
	// x x o x
	// o o o o
	// x x o x
	// x x o x
	T aa23 = -(sm14 * d31_32_41_42 - sm34 * d11_12_41_42 + sm44 * d11_12_31_32);
	// x x x o
	// o o o o
	// x x x o
	// x x x o
	T aa24 = sm13 * d31_32_41_42 - sm33 * d11_12_41_42 + sm43 * d11_12_31_32;
	// o x x x
	// o x x x
	// o o o o
	// o x x x
	T aa31 = sm12 * d23_24_43_44 - sm22 * d13_14_43_44 + sm42 * d13_14_23_24;
	// x o x x
	// x o x x
	// o o o o
	// x o x x
	T aa32 = -(sm11 * d23_24_43_44 - sm21 * d13_14_43_44 + sm41 * d13_14_23_24);
	// x x o x
	// x x o x
	// o o o o
	// x x o x
	T aa33 = sm14 * d21_22_41_42 - sm24 * d11_12_41_42 + sm44 * d11_12_21_22;
	// x x x o
	// x x x o
	// o o o o
	// x x x o
	T aa34 = -(sm13 * d21_22_41_42 - sm23 * d11_12_41_42 + sm43 * d11_12_21_22);
	// o x x x
	// o x x x
	// o x x x
	// o o o o
	T aa41 = -(sm12 * d23_24_33_34 - sm22 * d13_14_33_34 + sm32 * d13_14_23_24);
	// x o x x
	// x o x x
	// x o x x
	// o o o o
	T aa42 = sm11 * d23_24_33_34 - sm21 * d13_14_33_34 + sm31 * d13_14_23_24;
	// x x o x
	// x x o x
	// x x o x
	// o o o o
	T aa43 = -(sm14 * d21_22_31_32 - sm24 * d11_12_31_32 + sm34 * d11_12_21_22);
	// x x x o
	// x x x o
	// x x x o
	// o o o o
	T aa44 = sm13 * d21_22_31_32 - sm23 * d11_12_31_32 + sm33 * d11_12_21_22;

	T rDet = sm11 * aa11 + sm21 * aa21 + sm31 * aa31 + sm41 * aa41;

	if (0.0 == rDet)
		return 0;
	T rInvDet = 1.0 / rDet;

	pDstMtx->m[0][0] = aa11 * rInvDet;
	pDstMtx->m[0][1] = aa21 * rInvDet;
	pDstMtx->m[0][2] = aa31 * rInvDet;
	pDstMtx->m[0][3] = aa41 * rInvDet;

	pDstMtx->m[1][0] = aa12 * rInvDet;
	pDstMtx->m[1][1] = aa22 * rInvDet;
	pDstMtx->m[1][2] = aa32 * rInvDet;
	pDstMtx->m[1][3] = aa42 * rInvDet;

	pDstMtx->m[2][0] = aa13 * rInvDet;
	pDstMtx->m[2][1] = aa23 * rInvDet;
	pDstMtx->m[2][2] = aa33 * rInvDet;
	pDstMtx->m[2][3] = aa43 * rInvDet;

	pDstMtx->m[3][0] = aa14 * rInvDet;
	pDstMtx->m[3][1] = aa24 * rInvDet;
	pDstMtx->m[3][2] = aa34 * rInvDet;
	pDstMtx->m[3][3] = aa44 * rInvDet;

	return rDet;
}