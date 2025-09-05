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
Purpose: C++ object construction, destroying, moving, copying.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_CPPOBJ_H
#define ZVD_CPPOBJ_H

#include "core/base/zvdbasedefs.h"

#include "core/base/cpplib/zvdtypetraits.h"

#include <memory>

template <typename T,
    size_t(*FNextCapacity)(size_t),
    size_t KMinCap = 4>
class ZvdGrowCapacity
{
public:
    typedef size_t SizeType;

    static SizeType Evaluate(SizeType nNewCount, SizeType nCurrentCap)
    {
        SizeType nNewCap = nCurrentCap;

        if (nNewCap < KMinCap)
            nNewCap = KMinCap;

        while (nNewCap < nNewCount)
        {
            nNewCap = FNextCapacity(nNewCap);
        }
       
        return nNewCap;
    }
};

template<typename T, size_t KMinCap = 4>
class ZvdRegularContainerPolicy
{
public:
    typedef size_t SizeType;

    static SizeType NextCapacity(SizeType nCap)
    {
        return nCap + (nCap >> 1);
    }

    static SizeType GrowCapacity(SizeType nNewCount, SizeType nCurrentCap)
    {
        return ZvdGrowCapacity<T, NextCapacity, KMinCap>::Evaluate(nNewCount,
            nCurrentCap);
    }
};

#endif // ZVD_CPPOBJ_H