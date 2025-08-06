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
Purpose: ZvdcObject and ZvdcClass implementations.

----------------------
 For developers notes
----------------------

*/

#include "core/base/zvdobject.h"
#include "core/base/zvdassert.h"

//-----------------------------------------------------------------------------
ZvdcClass::ZvdcClass(ZvdCString pClassName,
    ZvdfptCreateInstance pCreateInstance,
    ZvdfptDeleteInstance pDeleteInstance,
    ZvdfptCloneInstance pCloneInstance) ZVD_NOEXCEPT
    : m_pClassName(pClassName)
    , m_pCreateInstance(pCreateInstance)
    , m_pDeleteInstance(pDeleteInstance)
    , m_pCloneInstance(pCloneInstance)
{
    ZVD_ASSERT_HIGH_NOMSG(pClassName);
    ZVD_ASSERT_HIGH_NOMSG(pCreateInstance);
    ZVD_ASSERT_HIGH_NOMSG(pDeleteInstance);

}

//-----------------------------------------------------------------------------
ZvdcpObject ZvdcClass::CreateInstance(ZvdcMemFlags memFlags) const ZVD_NOEXCEPT
{
    ZVD_ASSERT_HIGH_NOMSG(m_pCreateInstance);
    if (!m_pCreateInstance)
        return kZVD_NULLPTR(ZvdcObject);
    return m_pCreateInstance(memFlags);
}

//-----------------------------------------------------------------------------
void ZvdcClass::DeleteInstance(ZvdcpObject pObject) const ZVD_NOEXCEPT
{
    ZVD_ASSERT_HIGH_NOMSG(pObject);
    ZVD_ASSERT_HIGH_NOMSG(m_pDeleteInstance);

    if (m_pDeleteInstance && pObject)
    {
        m_pDeleteInstance(pObject);
    }
}

//-----------------------------------------------------------------------------
ZvdcpObject ZvdcClass::CloneInstance(ZvdcpkObject pObject) const ZVD_NOEXCEPT
{
    ZVD_ASSERT_HIGH_NOMSG(pObject);
    if (!m_pCloneInstance)
    {
        // Error: this object can be cloned
        return kZVD_NULLPTR(ZvdcObject);
    }
    return m_pCloneInstance(pObject);
}