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
Purpose: base class for objects requiring custom memory allocation.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_MEMORYMANAGEABLE_H
#define ZVD_MEMORYMANAGEABLE_H

#include "core/base/zvdbasedefs.h"
#include "core/system/memory/zvdmemflags.h"

/**
 * @class ZvdcMemoryManageable
 * @brief Base class for objects requiring custom memory management in the game engine.
 *
 * Provides custom placement new and delete operators to allocate memory via a custom memory manager,
 * controlled by ZvdcMemFlags. In debug mode (ZVD_CFG_DEBUG_MEMORY), additional parameters
 * (source file, line, function) are used for allocation tracking.
 */
class ZVD_API ZvdcMemoryManageable
{
#ifdef ZVD_CFG_DEBUG_MEMORY
private:
	/// @name Disabled New Operators
	/// @{
	/// @brief Disabled in debug mode (ZVD_CFG_DEBUG_MEMORY); use overloads with debug parameters (pSrcFile, iSrcLine, pFunc).
	static void* operator new(size_t nInstanceSize, ZvdcMemFlags memFlags) ZVD_NOEXCEPT ZVD_DELETED_METHOD;
	static void* operator new[](size_t nInstanceSize, ZvdcMemFlags memFlags) ZVD_NOEXCEPT ZVD_DELETED_METHOD;
	/// @}

public:
	/// @name Placement New Operators (Debug Mode)
	/// @{
	/// @brief Allocates memory for a single object via custom memory manager, with debug information.
	/// @param nInstanceSize Size of the memory to allocate.
	/// @param memFlags Flags controlling allocation strategy (e.g., pool or heap).
	/// @param pSrcFile Source file name for debug tracking.
	/// @param iSrcLine Source line number for debug tracking.
	/// @param pFunc Function name for debug tracking.
	/// @return Pointer to allocated memory.
	static void* operator new(size_t nInstanceSize, ZvdcMemFlags memFlags,
		ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc) ZVD_NOEXCEPT;

	/// @brief Allocates memory for an array via custom memory manager, with debug information.
	static void* operator new[](size_t nInstanceSize, ZvdcMemFlags memFlags,
		ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc) ZVD_NOEXCEPT;
	/// @}


	/// @name Placement Delete Operators (Debug Mode)
	/// @{
	/// @brief Deallocates memory for a single object allocated via placement new, with debug information.
	/// Called if the constructor throws an exception.
	/// @param pInstanceMem Pointer to the memory to deallocate.
	/// @param memFlags Flags used during allocation.
	/// @param pSrcFile Source file name for debug tracking.
	/// @param iSrcLine Source line number for debug tracking.
	/// @param pFunc Function name for debug tracking.
	static void operator delete(void* pInstanceMem, ZvdcMemFlags memFlags,
		ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc) ZVD_NOEXCEPT;

	/// @brief Deallocates memory for an array allocated via placement new[], with debug information.
	static void operator delete[](void* pInstanceMem, ZvdcMemFlags memFlags,
		ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc) ZVD_NOEXCEPT;
	/// @}
#else // !ZVD_CFG_DEBUG_MEMORY
public:
	/// @name Placement New Operators (Release Mode)
	/// @{
	/// @brief Allocates memory for a single object via custom memory manager.
	/// @param nInstanceSize Size of the memory to allocate.
	/// @param memFlags Flags controlling allocation strategy (e.g., pool or heap).
	/// @return Pointer to allocated memory.
	static void* operator new(size_t nInstanceSize, ZvdcMemFlags memFlags) ZVD_NOEXCEPT;

	/// @brief Allocates memory for an array via custom memory manager.
	static void* operator new[](size_t nInstanceSize, ZvdcMemFlags memFlags) ZVD_NOEXCEPT;
	/// @}

	/// @name Placement Delete Operators (Release Mode)
	/// @{
	/// @brief Deallocates memory for a single object allocated via placement new.
	/// Called if the constructor throws an exception.
	/// @param pInstanceMem Pointer to the memory to deallocate.
	/// @param memFlags Flags used during allocation.
	static void operator delete(void* pInstanceMem, ZvdcMemFlags memFlags) ZVD_NOEXCEPT;

	/// @brief Deallocates memory for an array allocated via placement new[].
	static void operator delete[](void* pInstanceMem, ZvdcMemFlags memFlags) ZVD_NOEXCEPT;
	/// @}
#endif // eof ZVD_CFG_DEBUG_MEMORY

public:
	/// @name Sized Deallocation Operators
	/// @{
#ifdef ZVD_CPP14
	/// @brief Deallocates memory for a single object with sized deallocation.
	/// @param pInstanceMem Pointer to the memory to deallocate.
	/// @param nInstanceSize Size of the memory allocated.
	static void operator delete(void* pInstanceMem, size_t nInstanceSize) ZVD_NOEXCEPT;

	/// @brief Deallocates memory for an array with sized deallocation.
	static void operator delete[](void* pInstanceMem, size_t nInstanceSize) ZVD_NOEXCEPT;
#endif
	/// @}

	/// @name Placement New/Delete Operators
	/// @{
	/// @brief Placement new for constructing a single object in pre-allocated memory.
	/// @param nInstanceSize Size of the memory (ignored, for standard compliance).
	/// @param pPlacementMem Pointer to pre-allocated memory.
	/// @return Pointer to pre-allocated memory.
	static void* operator new(size_t nInstanceSize, void* pPlacementMem) ZVD_NOEXCEPT;

	/// @brief Placement new for constructing an array in pre-allocated memory.
	static void* operator new[](size_t nInstanceSize, void* pPlacementMem) ZVD_NOEXCEPT;

	/// @brief Placement delete for a single object, called if constructor throws.
	/// @param pInstanceMem Pointer to the memory to deallocate (ignored).
	/// @param pPlacementMem Pointer to pre-allocated memory (ignored).
	static void operator delete(void* pInstanceMem, void* pPlacementMem) ZVD_NOEXCEPT;

	/// @brief Placement delete for an array, called if constructor throws.
	static void operator delete[](void* pInstanceMem, void* pPlacementMem) ZVD_NOEXCEPT;
	/// @}
};

//=============================================================================
// Placement new/delete operator implementations

//-----------------------------------------------------------------------------
inline
void* ZvdcMemoryManageable::operator new(size_t nInstantSize, void* pPlacementMem) ZVD_NOEXCEPT
{
	ZVD_UNUSED_ARG(nInstantSize);
	return pPlacementMem;
}

//-----------------------------------------------------------------------------
inline
void* ZvdcMemoryManageable::operator new[](size_t nInstantSize, void* pPlacementMem) ZVD_NOEXCEPT
{
	ZVD_UNUSED_ARG(nInstantSize);
	return pPlacementMem;
}

//-----------------------------------------------------------------------------
inline
void ZvdcMemoryManageable::operator delete(void* pInstanceMem, void* pPlacementMem) ZVD_NOEXCEPT
{
	ZVD_UNUSED_ARG(pInstanceMem);
	ZVD_UNUSED_ARG(pPlacementMem);
	// No-op: Memory is managed by the caller.
}

//-----------------------------------------------------------------------------
inline
void ZvdcMemoryManageable::operator delete[](void* pInstanceMem, void* pPlacementMem) ZVD_NOEXCEPT
{
	ZVD_UNUSED_ARG(pInstanceMem);
	ZVD_UNUSED_ARG(pPlacementMem);
	// No-op: Memory is managed by the caller.
}


#ifdef ZVD_CFG_DEBUG_MEMORY
inline void ZvdcMemoryManageable::operator delete(void* pInstanceMem, ZvdcMemFlags memFlags,
	ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc) ZVD_NOEXCEPT
{
#if defined(ZVD_CFG_USE_EXCEPTIONS)
#else
	ZVD_UNUSED_ARG(pInstanceMem);
	ZVD_UNUSED_ARG(memFlags);
	ZVD_UNUSED_ARG(pSrcFile);
	ZVD_UNUSED_ARG(iSrcLine);
	ZVD_UNUSED_ARG(pFunc);
	// No-op: Exceptions are disabled (ZVD_CFG_USE_EXCEPTIONS off), so this is never called.
#endif
}

inline void ZvdcMemoryManageable::operator delete[](void* pInstanceMem, ZvdcMemFlags memFlags,
	ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc) ZVD_NOEXCEPT
{
#if defined(ZVD_CFG_USE_EXCEPTIONS)
#else
	ZVD_UNUSED_ARG(pInstanceMem);
	ZVD_UNUSED_ARG(memFlags);
	ZVD_UNUSED_ARG(pSrcFile);
	ZVD_UNUSED_ARG(iSrcLine);
	ZVD_UNUSED_ARG(pFunc);
	// No-op: Exceptions are disabled (ZVD_CFG_USE_EXCEPTIONS off), so this is never called.
#endif
}

#else // !ZVD_CFG_DEBUG_MEMORY

inline void ZvdcMemoryManageable::operator delete(void* pInstanceMem, ZvdcMemFlags memFlags) ZVD_NOEXCEPT
{
#if defined(ZVD_CFG_USE_EXCEPTIONS)
#else
	ZVD_UNUSED_ARG(pInstanceMem);
	ZVD_UNUSED_ARG(memFlags);
	// No-op: Exceptions are disabled (ZVD_CFG_USE_EXCEPTIONS off), so this is never called.
#endif
}

inline void ZvdcMemoryManageable::operator delete[](void* pInstanceMem, ZvdcMemFlags memFlags) ZVD_NOEXCEPT
{
#if defined(ZVD_CFG_USE_EXCEPTIONS)
#else
	ZVD_UNUSED_ARG(pInstanceMem);
	ZVD_UNUSED_ARG(memFlags);
	// No-op: Exceptions are disabled (ZVD_CFG_USE_EXCEPTIONS off), so this is never called.
#endif
}

#endif // ZVD_CFG_DEBUG_MEMORY

#endif // ZVD_MEMORYMANAGEABLE_H