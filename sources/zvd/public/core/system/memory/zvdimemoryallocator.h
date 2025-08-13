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
Purpose: memory allocator interface.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_IMEMORYALLOCATOR_H
#define ZVD_IMEMORYALLOCATOR_H

#include "core/base/zvderror.h"

class ZvdiMemoryAllocator
{
public:
	typedef ZvdSize SizeType;
	typedef ZvdResult<ZvdiMemoryAllocator*> ResultType;

	virtual ~ZvdiMemoryAllocator() ZVD_NOEXCEPT {}

	virtual ZvdResult<void*> Allocate(SizeType nBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
		, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
	) 
	ZVD_NOEXCEPT = 0;

	virtual ZvdResult<void*> Reallocate(void* p, SizeType nBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
		, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
	) ZVD_NOEXCEPT = 0;

	virtual ZvdRegularResult Deallocate(void* p
#ifdef ZVD_CFG_DEBUG_MEMORY
		, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
	) ZVD_NOEXCEPT = 0;

	// Methods to be used when allocator is template parameter
	//--------------------------------------------------------
	static ZvdUInt32 IsSingleton() ZVD_NOEXCEPT { return kZVD_NO_U32; }
	// If singleton implement these methods:
	static ResultType Instance() ZVD_NOEXCEPT
	{ 
		return ResultType(
			ZvdPackedError(kZVD_ES_ERROR, kZVD_ESRC_CORE_MEMORY, kZVD_EC_NOIMPL));
	}

	/// If true this memory allocator is subsystem of some larger system (engine).
	static ZvdUInt32 IsSubsystem() ZVD_NOEXCEPT { return kZVD_NO_U32; }
	// If subsystem implement these methods:
	// 
	//	You can request to engine class for example 
	static ResultType AsSubsystem() ZVD_NOEXCEPT
	{ 
		return ResultType(
			ZvdPackedError(kZVD_ES_ERROR, kZVD_ESRC_CORE_MEMORY, kZVD_EC_NOIMPL));
	}
		//
	virtual ZvdUInt32 IsReady() const ZVD_NOEXCEPT { return kZVD_NO_U32; }
	virtual ZvdUInt32 IsInitialized() const ZVD_NOEXCEPT { return kZVD_NO_U32; }

	static ZvdUInt32 CanBeCreatedOnStack() ZVD_NOEXCEPT { return kZVD_YES_U32; }
	// If subsystem implement these methods:
	static ResultType CreateOnStack(void* pStackMem) ZVD_NOEXCEPT
	{
		return ResultType(
			ZvdPackedError(kZVD_ES_ERROR, kZVD_ESRC_CORE_MEMORY, kZVD_EC_NOIMPL));
	}
};

#endif // ZVD_IMEMORYALLOCATOR_H