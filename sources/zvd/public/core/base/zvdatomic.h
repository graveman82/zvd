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
Purpose: Platform-independent atomic operations for Zv3D engine.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_ATOMIC_H_
#define ZVD_ATOMIC_H_

#include "core/base/zvdbasedefs.h"

#ifdef ZVD_CPP11
#   include <atomic>
#endif

/** @brief Atomically increments an unsigned 32-bit integer value (ZvdUInt32).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API ZvdUInt32 ZVD_STDCALL ZvdfAtomicIncrement(ZvdUInt32& value) ZVD_NOEXCEPT;

/** @brief Atomically decrements an unsigned 32-bit integer value (ZvdUInt32).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API ZvdUInt32 ZVD_STDCALL ZvdfAtomicDecrement(ZvdUInt32& value) ZVD_NOEXCEPT;

/** @brief Atomically increments a signed 32-bit integer value (ZvdInt32).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API ZvdInt32 ZVD_STDCALL ZvdfAtomicIncrement(ZvdInt32& value) ZVD_NOEXCEPT;

/** @brief Atomically decrements a signed 32-bit integer value (ZvdInt32).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API ZvdInt32 ZVD_STDCALL ZvdfAtomicDecrement(ZvdInt32& value) ZVD_NOEXCEPT;

/** @brief Atomically increments an unsigned 64-bit integer value (ZvdUInt64).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API ZvdUInt64 ZVD_STDCALL ZvdfAtomicIncrement(ZvdUInt64& value) ZVD_NOEXCEPT;

/** @brief Atomically decrements an unsigned 64-bit integer value (ZvdUInt64).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API ZvdUInt64 ZVD_STDCALL ZvdfAtomicDecrement(ZvdUInt64& value) ZVD_NOEXCEPT;

/** @brief Atomically increments a signed 64-bit integer value (ZvdInt64).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API ZvdInt64 ZVD_STDCALL ZvdfAtomicIncrement(ZvdInt64& value) ZVD_NOEXCEPT;

/** @brief Atomically decrements a signed 64-bit integer value (ZvdInt64).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API ZvdInt64 ZVD_STDCALL ZvdfAtomicDecrement(ZvdInt64& value) ZVD_NOEXCEPT;

/** @brief Atomically increments an unsigned integer value (ZvdSize).
 *  @param value Reference to the value to increment.
 *  @return The new value after increment.
 */
ZVD_API ZvdSize ZVD_STDCALL ZvdfAtomicIncrementSize(ZvdSize& value) ZVD_NOEXCEPT;

/** @brief Atomically decrements an unsigned integer value (ZvdSize).
 *  @param value Reference to the value to decrement.
 *  @return The new value after decrement.
 */
ZVD_API ZvdSize ZVD_STDCALL ZvdfAtomicDecrementSize(ZvdSize& value) ZVD_NOEXCEPT;

#ifdef ZVD_CPP11
/** @brief Atomically increments an unsigned 32-bit atomic integer value (std::atomic<ZvdUInt32>).
 *  @param value Reference to the atomic value to increment.
 *  @return The new value after increment.
 */
inline ZVD_API ZvdUInt32 ZVD_STDCALL ZvdfAtomicIncrement(std::atomic<ZvdUInt32>& value) ZVD_NOEXCEPT
{
    return value.fetch_add(1, std::memory_order_seq_cst) + 1;
}

/** @brief Atomically decrements an unsigned 32-bit atomic integer value (std::atomic<ZvdUInt32>).
 *  @param value Reference to the atomic value to decrement.
 *  @return The new value after decrement.
 */
inline ZVD_API ZvdUInt32 ZVD_STDCALL ZvdfAtomicDecrement(std::atomic<ZvdUInt32>& value) ZVD_NOEXCEPT
{
    return value.fetch_sub(1, std::memory_order_seq_cst) - 1;
}

/** @brief Atomically increments an unsigned 64-bit atomic integer value (std::atomic<ZvdUInt64>).
 *  @param value Reference to the atomic value to increment.
 *  @return The new value after increment.
 */
inline ZVD_API ZvdUInt64 ZVD_STDCALL ZvdfAtomicIncrement(std::atomic<ZvdUInt64>& value) ZVD_NOEXCEPT
{
    return value.fetch_add(1, std::memory_order_seq_cst) + 1;
}

/** @brief Atomically decrements an unsigned 64-bit atomic integer value (std::atomic<ZvdUInt64>).
 *  @param value Reference to the atomic value to decrement.
 *  @return The new value after decrement.
 */
inline ZVD_API ZvdUInt64 ZVD_STDCALL ZvdfAtomicDecrement(std::atomic<ZvdUInt64>& value) ZVD_NOEXCEPT
{
    return value.fetch_sub(1, std::memory_order_seq_cst) - 1;
}

/** @brief Atomically increments an unsigned atomic integer value (std::atomic<ZvdSize>).
 *  @param value Reference to the atomic value to increment.
 *  @return The new value after increment.
 */
inline ZVD_API ZvdSize ZVD_STDCALL ZvdfAtomicIncrementSize(std::atomic<ZvdSize>& value) ZVD_NOEXCEPT
{
    return value.fetch_add(1, std::memory_order_seq_cst) + 1;
}

/** @brief Atomically decrements an unsigned atomic integer value (std::atomic<ZvdSize>).
 *  @param value Reference to the atomic value to decrement.
 *  @return The new value after decrement.
 */
inline ZVD_API ZvdSize ZVD_STDCALL ZvdfAtomicDecrementSize(std::atomic<ZvdSize>& value) ZVD_NOEXCEPT
{
    return value.fetch_sub(1, std::memory_order_seq_cst) - 1;
}
#endif

#endif // ZVD_ATOMIC_H_