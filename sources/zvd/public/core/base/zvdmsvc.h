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
Purpose: Microsoft Visual C++ compiler related definitions.

----------------------
 For developers notes
----------------------

*/
   
#ifndef ZVD_MSVC_H
#define ZVD_MSVC_H

// correct header validation
#if !defined(ZVD_MSVC)
#   error "zvd: this file must be included by zvdcompiler.h"
#endif // correct header validation

//-----------------------------------------------------------------------------
// Microsoft compiler version

#define ZVD_VISUAL_STUDIO_6_x_0					1200
#define ZVD_VISUAL_STUDIO_NET_2002_7_x_0		1300
#define ZVD_VISUAL_STUDIO_NET_2003_7_x_1		1310
#define ZVD_VISUAL_STUDIO_2005_8_x_0			1400
#define ZVD_VISUAL_STUDIO_2008_9_x_0			1500
#define ZVD_VISUAL_STUDIO_2010_10_x_0			1600
#define ZVD_VISUAL_STUDIO_2012_11_x_0			1700
#define ZVD_VISUAL_STUDIO_2013_12_x_0			1800
#define ZVD_VISUAL_STUDIO_2015_14_x_0			1900
#define ZVD_VISUAL_STUDIO_2017_RTW_15_x_0		1910
#define ZVD_VISUAL_STUDIO_2017_15_x_3			1911
#define ZVD_VISUAL_STUDIO_2017_15_x_5			1912
#define ZVD_VISUAL_STUDIO_2017_15_x_6			1913
#define ZVD_VISUAL_STUDIO_2017_15_x_7			1914
#define ZVD_VISUAL_STUDIO_2017_15_x_8			1915
#define ZVD_VISUAL_STUDIO_2017_15_x_9			1916
#define ZVD_VISUAL_STUDIO_2019_RTW_16_x_0		1920
#define ZVD_VISUAL_STUDIO_2019_16_x_1			1921
#define ZVD_VISUAL_STUDIO_2019_16_x_2			1922
#define ZVD_VISUAL_STUDIO_2019_16_x_3			1923
#define ZVD_VISUAL_STUDIO_2019_16_x_4			1924
#define ZVD_VISUAL_STUDIO_2019_16_x_5			1925
#define ZVD_VISUAL_STUDIO_2019_16_x_6			1926
#define ZVD_VISUAL_STUDIO_2019_16_x_7			1927
#define ZVD_VISUAL_STUDIO_2019_16_x_8_16_x_9	1928
#define ZVD_VISUAL_STUDIO_2019_16_x_10_16_x_11	1929
#define ZVD_VISUAL_STUDIO_2022_RTW_17_x_0		1930

#define ZVD_COMPILER_MSVC_VERSION _MSC_VER


/** Macro to get MSVC version.
*/

#define ZVD_COMPILER_MSVC_VERSION_OR_HIGHER(ver) (ZVD_COMPILER_MSVC_VERSION >= ver)

#endif // ZVD_MSVC_H
