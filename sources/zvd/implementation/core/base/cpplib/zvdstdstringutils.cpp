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
Purpose: std-like string utils.

----------------------
 For developers notes
----------------------

*/



#include "core/base/zvdassert.h"
#include "core/base/cpplib/zvdstdstringutils.h"
#include "core/base/zvdcommonutils.h"


ZvdSize Zvdf_strlen(const char* str)
{
	if (!str)
		return 0;
	const char* pEnd = str + ZVD_CFG_MAX_CSTR_LEN;
	for (const char* p = str; p < pEnd; ++p)
		if (*p == '\0')
			return p - str;
	return 0;
}

ZvdSize Zvdf_snprintf(char* pDest, ZvdSize nDestSize, ZvdSize nCount, char const* pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);
	ZvdSize nRetVal = Zvdf_vsnprintf(pDest, nDestSize, nCount, pFormat, args);
	va_end(args);

	return nRetVal;
}

ZvdSize Zvdf_vsnprintf(char* pDest, ZvdSize nDestSize, ZvdSize nCount, char const* pFormat, va_list params)
{
	if (!pDest || nDestSize == 0)
	{
		return 0;
	}

	ZVD_ASSERT_HIGH_NOMSG(nDestSize > 0);
	ZVD_ASSERT_HIGH_NOMSG(pDest);
	pDest[0] = '\0';
	if (nDestSize == 1)
	{
		return 0;
	}
	ZVD_ASSERT_HIGH_NOMSG(pFormat);
	ZVD_ASSERT_HIGH_NOMSG(nCount < nDestSize);
#if !defined(ZVD_CFG_USE_NOSECURE_VSNPRINTF) && defined(ZVD_MSVC) && ZVD_COMPILER_MSVC_VERSION_OR_HIGHER(ZVD_VISUAL_STUDIO_2005_8_x_0)
	int nRetVal = _vsnprintf_s(pDest, nDestSize, nCount, pFormat, params);	
#else
	int nRetVal = _vsnprintf(pDest, nCount, pFormat, params);
#endif
	// Ensure that the string ends in a null terminator.
	if (nRetVal < 0)
	{
		pDest[nDestSize - 1] = 0;
		return nDestSize - 1;
	}
	pDest[ZvdfMin<ZvdSize>(nRetVal, nCount)] = 0;
	return nRetVal;
}