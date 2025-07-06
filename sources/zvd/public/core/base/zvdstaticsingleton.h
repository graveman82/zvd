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
Purpose: singleton design pattern definition.

----------------------
 For developers notes
----------------------
This singleton is intended to be used in static allocated memory.
*/

#ifndef ZVD_STATICSINGLETON_H
#define ZVD_STATICSINGLETON_H

#include "core/zvdbasedefs.h"


//-----------------------------------------------------------------------------
/** @class StaticSingleton
    An object instance is allocated in static buffer.
    @param kBufferSize buffer size to store T instance inside.
    Specify kBufferSize in code using this class - it must have enough size
    to place T instance in.
    @param TPseudoCtor is functor to construct instance of T in buffer. 

    @code
    // Usage example

    struct DummyCreator
    {
        Dummy* operator()(void* p)
        {
            return ::new(p) Dummy();
        }
    };

    void test()
    {
        Dummy& dummy =
            ZvdStaticSingleton<Dummy,
            sizeof(Dummy),
            DummyCreator>::Instance();

        dummy.setName("Gagarin");

        ZvdStaticSingleton<Dummy,
            sizeof(Dummy),
            DummyCreator>::Destroy();
    }
    @endcode

*/
template <typename T, ZvdUInt32 kBufferSize, typename TPseudoCtor>
class ZvdStaticSingleton
{
public:
#ifdef ZVD_CPP11
    ZvdStaticSingleton() = default;
#else
    ZvdStaticSingleton() {}
#endif
    /// Returns reference to a single instance of given template type.
    static T& Instance()
    {
        if (!m_pInstance)
        {
            m_pInstance = TPseudoCtor()(&m_buffer[0]);
        }
        return *m_pInstance;
    }

    /// Destroys the instance explicitly.
    static void Destroy()
    {
        if (m_pInstance)
        {
            m_pInstance->~T();
            m_pInstance = kZVD_NULLPTR(T);
        }
    }

private:
#ifdef ZVD_CPP11
    // not allowed
    ZvdStaticSingleton(
        const ZvdStaticSingleton<T, kBufferSize, TPseudoCtor>&) = delete;
    ZvdStaticSingleton& operator=(
        const ZvdStaticSingleton<T, kBufferSize, TPseudoCtor>&) = delete;
#else
    ZvdStaticSingleton(
        const ZvdStaticSingleton<T, kBufferSize, TPseudoCtor>&);
    ZvdStaticSingleton& operator=(
        const ZvdStaticSingleton<T, kBufferSize, TPseudoCtor>&);
#endif

    static T* m_pInstance;
    static ZvdByte m_buffer[kBufferSize];
};

//-----------------------------------------------------------------------------
template <typename T, ZvdUInt32 kBufferSize, typename TPseudoCtor>
T* ZvdStaticSingleton<T,
    kBufferSize, TPseudoCtor>::m_pInstance = kZVD_NULLPTR(T);

//-----------------------------------------------------------------------------
template <typename T, ZvdUInt32 kBufferSize, typename TPseudoCtor>
ZvdByte ZvdStaticSingleton<T,
    kBufferSize, TPseudoCtor>::m_buffer[kBufferSize];


#endif // ZVD_STATICSINGLETON_H