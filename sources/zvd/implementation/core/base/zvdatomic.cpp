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
Purpose: .

----------------------
 For developers notes
----------------------

*/

#include "core/base/zvdatomic.h"

#ifdef ZVD_CPP11
#   include <atomic>

#else
#   if defined(ZVD_PLATFORM_WIN64) || defined(ZVD_PLATFORM_WIN32)
#       include <windows.h>
#   endif

#endif

//-----------------------------------------------------------------------------
ZVD_API ZvdUInt32 ZVD_STDCALL ZvdfAtomicIncrement(ZvdUInt32& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_add_explicit(reinterpret_cast<std::atomic<ZvdUInt32>*>(&value), 1, std::memory_order_seq_cst) + 1;
#else
#if defined(ZVD_PLATFORM_WIN64) || defined(ZVD_PLATFORM_WIN32)
    return InterlockedIncrement(&value);
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_add_and_fetch(&value, 1);
#else
#   error "Unsupported platform for atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdUInt32 ZVD_STDCALL ZvdfAtomicDecrement(ZvdUInt32& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_sub_explicit(reinterpret_cast<std::atomic<ZvdUInt32>*>(&value), 1, std::memory_order_seq_cst) - 1;
#else
#if defined(ZVD_PLATFORM_WIN64) || defined(ZVD_PLATFORM_WIN32)
    return InterlockedDecrement(&value);
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_sub_and_fetch(&value, 1);
#else
#   error "Unsupported platform for atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdInt32 ZVD_STDCALL ZvdfAtomicIncrement(ZvdInt32& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_add_explicit(reinterpret_cast<std::atomic<ZvdInt32>*>(&value), 1, std::memory_order_seq_cst) + 1;
#else
#if defined(ZVD_PLATFORM_WIN64) || defined(ZVD_PLATFORM_WIN32)
    return InterlockedIncrement(reinterpret_cast<LONG*>(&value));
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_add_and_fetch(&value, 1);
#else
#   error "Unsupported platform for atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdInt32 ZVD_STDCALL ZvdfAtomicDecrement(ZvdInt32& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_sub_explicit(reinterpret_cast<std::atomic<ZvdInt32>*>(&value), 1, std::memory_order_seq_cst) - 1;
#else
#if defined(ZVD_PLATFORM_WIN64) || defined(ZVD_PLATFORM_WIN32)
    return InterlockedDecrement(reinterpret_cast<LONG*>(&value));
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_sub_and_fetch(&value, 1);
#else
#   error "Unsupported platform for atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdUInt64 ZVD_STDCALL ZvdfAtomicIncrement(ZvdUInt64& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_add_explicit(reinterpret_cast<std::atomic<ZvdUInt64>*>(&value), 1, std::memory_order_seq_cst) + 1;
#else
#if defined(ZVD_PLATFORM_WIN64)
    return InterlockedIncrement64(&value);
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_add_and_fetch(&value, 1);
#else
#   error "Unsupported platform for 64-bit atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdUInt64 ZVD_STDCALL ZvdfAtomicDecrement(ZvdUInt64& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_sub_explicit(reinterpret_cast<std::atomic<ZvdUInt64>*>(&value), 1, std::memory_order_seq_cst) - 1;
#else
#if defined(ZVD_PLATFORM_WIN64)
    return InterlockedDecrement64(&value);
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_sub_and_fetch(&value, 1);
#else
#   error "Unsupported platform for 64-bit atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdInt64 ZVD_STDCALL ZvdfAtomicIncrement(ZvdInt64& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_add_explicit(reinterpret_cast<std::atomic<ZvdInt64>*>(&value), 1, std::memory_order_seq_cst) + 1;
#else
#if defined(ZVD_PLATFORM_WIN64)
    return InterlockedIncrement64(reinterpret_cast<LONGLONG*>(&value));
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_add_and_fetch(&value, 1);
#else
#   error "Unsupported platform for 64-bit atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdInt64 ZVD_STDCALL ZvdfAtomicDecrement(ZvdInt64& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_sub_explicit(reinterpret_cast<std::atomic<ZvdInt64>*>(&value), 1, std::memory_order_seq_cst) - 1;
#else
#if defined(ZVD_PLATFORM_WIN64)
    return InterlockedDecrement64(reinterpret_cast<LONGLONG*>(&value));
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_sub_and_fetch(&value, 1);
#else
#   error "Unsupported platform for 64-bit atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdSize ZVD_STDCALL ZvdfAtomicIncrementSize(ZvdSize& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_add_explicit(reinterpret_cast<std::atomic<ZvdSize>*>(&value), 1, std::memory_order_seq_cst) + 1;
#else
#if defined(ZVD_PLATFORM_WIN64) || defined(ZVD_PLATFORM_WIN32)
    return InterlockedIncrement(reinterpret_cast<volatile unsigned long*>(&value));
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_add_and_fetch(&value, 1);
#else
#error "Unsupported platform for atomic operations"
#endif
#endif
}

//-----------------------------------------------------------------------------
ZVD_API ZvdSize ZVD_STDCALL ZvdfAtomicDecrementSize(ZvdSize& value) ZVD_NOEXCEPT
{
#ifdef ZVD_CPP11
    return std::atomic_fetch_sub_explicit(reinterpret_cast<std::atomic<ZvdSize>*>(&value), 1, std::memory_order_seq_cst) - 1;
#else
#if defined(ZVD_PLATFORM_WIN64) || defined(ZVD_PLATFORM_WIN32)
    return InterlockedDecrement(reinterpret_cast<volatile unsigned long*>(&value));
#elif defined(ZVD_PLATFORM_LINUX)
    return __sync_sub_and_fetch(&value, 1);
#else
#error "Unsupported platform for atomic operations"
#endif
#endif
}

