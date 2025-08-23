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

ZvdcMallocFreeMemoryAllocator::~ZvdcMallocFreeMemoryAllocator() noexcept
{

}

//-----------------------------------------------------------------------------
ZvdResult<void*>
ZvdcMallocFreeMemoryAllocator::Allocate(SizeType nBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
	, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
) noexcept
{
	ZvdResult<void*> retVal(ZvdPackedError::Ok(), ::malloc(nBytes));
	return retVal;
}

//-----------------------------------------------------------------------------
ZvdResult<void*>
ZvdcMallocFreeMemoryAllocator::Reallocate(void* p, SizeType nBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
	, ZvdCString pSrcFile, int iSrcLine, ZvdCString pFunc
#endif
) noexcept
{
	ZvdResult<void*> retVal(ZvdPackedError::Ok(), ::realloc(p, nBytes));
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
	return ZvdResult<void*>();
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
	return ResultType(
		ZvdPackedError(kZVD_ES_ERROR, kZVD_ESRC_CORE_MEMORY, kZVD_EC_NOIMPL));
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
	return ResultType(
		ZvdPackedError(kZVD_ES_ERROR, kZVD_ESRC_CORE_MEMORY, kZVD_EC_NOIMPL));
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
	return ResultType(ZvdPackedError::Ok(), p);
}