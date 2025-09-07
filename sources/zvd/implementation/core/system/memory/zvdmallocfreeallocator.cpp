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
Purpose: blank file for implementations (.cpp files).

----------------------
 For developers notes
----------------------

*/

#include "core/system/memory/zvdmallocfreeallocator.h"
#include <new>

//-----------------------------------------------------------------------------
#ifdef ZVD_CFG_UNITTEST_MEMORY
std::unordered_map<void*, size_t> ZvdcMallocFreeMemoryAllocator::s_mActiveAllocations;
#endif
//-----------------------------------------------------------------------------

ZvdcMallocFreeMemoryAllocator::~ZvdcMallocFreeMemoryAllocator() noexcept
{

}

//-----------------------------------------------------------------------------
ZvdPointerResult<void>
ZvdcMallocFreeMemoryAllocator::Allocate(SizeType nBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
	, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
) noexcept
{
	ZvdPointerResult<void> retVal(::malloc(nBytes), ZvdPackedError::Ok());
#ifdef ZVD_CFG_UNITTEST_MEMORY
	if (retVal.Get())
	{
		s_mActiveAllocations[retVal.Get()] = nBytes;
	}
#endif
	return retVal;
}

//-----------------------------------------------------------------------------
ZvdPointerResult<void>
ZvdcMallocFreeMemoryAllocator::Reallocate(void* p, SizeType nBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
	, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
) noexcept
{
	ZvdPointerResult<void> retVal(::realloc(p, nBytes), ZvdPackedError::Ok());
#ifdef ZVD_CFG_UNITTEST_MEMORY
	if (retVal.Get())
	{
		if (p != retVal.Get())
		{
			s_mActiveAllocations.erase(p);
			s_mActiveAllocations[retVal.Get()] = nBytes;
		}
		else
		{
			s_mActiveAllocations[p] = nBytes;
		}
	}
#endif
	return retVal;
}

//-----------------------------------------------------------------------------
ZvdRegularResult
ZvdcMallocFreeMemoryAllocator::Deallocate(void* p
#ifdef ZVD_CFG_DEBUG_MEMORY
	, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
) noexcept
{
	::free(p);
#ifdef ZVD_CFG_UNITTEST_MEMORY
	if (p)
	{
		s_mActiveAllocations.erase(p);
	}
#endif
	return ZvdRegularResult();
}

//-----------------------------------------------------------------------------

bool
ZvdcMallocFreeMemoryAllocator::IsSingleton() noexcept 
{ 
	return false; 
}

//-----------------------------------------------------------------------------

ZvdcMallocFreeMemoryAllocator::ResultType
ZvdcMallocFreeMemoryAllocator::Instance() noexcept
{
	return ResultType(nullptr,
		ZvdPackedError(kZVD_ES_ERROR, 
			static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_MEMORY), 
			kZVD_EC_NOIMPL));
}

//-----------------------------------------------------------------------------

bool
ZvdcMallocFreeMemoryAllocator::IsSubsystem() noexcept 
{ 
	return false; 
}

//-----------------------------------------------------------------------------

ZvdcMallocFreeMemoryAllocator::ResultType
ZvdcMallocFreeMemoryAllocator::AsSubsystem() noexcept
{
	return ResultType(nullptr,
		ZvdPackedError(kZVD_ES_ERROR, 
			static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_MEMORY), 
			kZVD_EC_NOIMPL));
}

//-----------------------------------------------------------------------------

bool
ZvdcMallocFreeMemoryAllocator::IsReady() const noexcept 
{ 
	return false; 
}

//-----------------------------------------------------------------------------

bool
ZvdcMallocFreeMemoryAllocator::IsInitialized() const noexcept 
{ 
	return false; 
}

//-----------------------------------------------------------------------------

bool
ZvdcMallocFreeMemoryAllocator::CanBeCreatedOnStack() noexcept 
{ 
	return true; 
}

//-----------------------------------------------------------------------------

ZvdcMallocFreeMemoryAllocator::ResultType 
ZvdcMallocFreeMemoryAllocator::CreateOnStack(void* pStackMem) noexcept
{
	ZvdiMemoryAllocator* p = ::new(pStackMem) ZvdcMallocFreeMemoryAllocator;
	return ResultType(p, ZvdPackedError::Ok());
}