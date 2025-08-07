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
Purpose: simple allocator based on malloc/realloc/free routines.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_MALLOCFREEALLOCATOR_H
#define ZVD_MALLOCFREEALLOCATOR_H

#include "core/system/memory/zvdimemoryallocator.h"

class ZvdcMallocFreeMemoryAllocator : public ZvdiMemoryAllocator
{
public:
	typedef ZvdSize SizeType;
	typedef ZvdResult<ZvdiMemoryAllocator*> ResultType;

	virtual ~ZvdcMallocFreeMemoryAllocator() ZVD_NOEXCEPT;

	virtual ZvdResult<void*> Allocate(SizeType nBytes) ZVD_NOEXCEPT;

	virtual ZvdResult<void*> Reallocate(void* p, SizeType nBytes) ZVD_NOEXCEPT;
	virtual ZvdRegularResult Deallocate(void* p) ZVD_NOEXCEPT;
	// Methods to be used when allocator is template parameter
	//--------------------------------------------------------
	static ZvdUInt32 IsSingleton() ZVD_NOEXCEPT;
	// If singleton implement these methods:
	static ResultType Instance() ZVD_NOEXCEPT;

	/// If true this memory allocator is subsystem of some larger system (engine).
	static ZvdUInt32 IsSubsystem() ZVD_NOEXCEPT;
	// If subsystem implement these methods:
	// 
	//	You can request to engine class for example 
	static ResultType AsSubsystem() ZVD_NOEXCEPT;
	//
	virtual ZvdUInt32 IsReady() const ZVD_NOEXCEPT;
	virtual ZvdUInt32 IsInitialized() const ZVD_NOEXCEPT;

	static ZvdUInt32 CanBeCreatedOnStack() ZVD_NOEXCEPT;
	// If subsystem implement these methods:
	static ResultType CreateOnStack(void* pStackMem) ZVD_NOEXCEPT;
};

#endif // ZVD_MALLOCFREEALLOCATOR_H