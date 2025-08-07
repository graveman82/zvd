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
Purpose: dynamic arrays templates.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_DARRAY_H
#define ZVD_DARRAY_H

#include "core/system/memory/zvdimemoryallocator.h"
#include "core/base/zvdassert.h"
#include "core/base/cpplib/zvdcppobj.h"

template <typename TElement, 
	typename TMemoryAllocator,
	typename TUtil = ZvdRegularCppObjectUtil<TElement>>
class ZvdñDArray
{
public:
	typedef ZvdSize SizeType;
	typedef TElement ValueType;
	typedef TElement* Pointer;
	typedef TElement* Iterator;

	ZvdñDArray()
		: m_pData(kZVD_NULLPTR(TElement))
		, m_nCount(0)
		, m_nCapacity(0)
	{

	}

	~ZvdñDArray()
	{
		Clear();
		ZvdRegularResult retVal = ResizeMemory(0);
		if (!retVal.IsOk())
		{
			/// @todo
			// abort program
			ZvdfFatalError("ZvdñDArray destructor, ResizeMemory(0) returned %x", retVal.Error().RetVal());
		}
	}

	void Clear()
	{
		for (SizeType i = 0; i < m_nCount; ++i)
		{
			TUtil::Destroy(&m_pData[i]);
		}
		m_nCount = 0;
	}

	ZvdRegularResult Grow(SizeType nGrowBy = 1)
	{
		ZvdRegularResult retVal = GrowMemory(nGrowBy);
		if (retVal.IsOk())
		{
			return retVal;
		}

		SizeType nNewCount = m_nCount + nGrowBy;
		for (SizeType i = m_nCount; i < nNewCount; ++i)
		{
			TUtil::Construct(m_pData + i);
		}
		m_nCount = nNewCount;
		return ZvdRegularResult();
	}

	ZvdRegularResult PushBack(const TElement& val)
	{
		ZvdRegularResult retVal = GrowMemory(1);
		if (!retVal.IsOk())
		{
			return retVal;
		}
		TUtil::CopyConstruct(m_pData + m_nCount, val);
		++m_nCount;
		return ZvdRegularResult();
	}

	ZvdRegularResult Reserve(SizeType nNewCap)
	{
		if (nNewCap <= m_nCapacity)
			return ZvdRegularResult();
		return ResizeMemory(nNewCap);
	}

	template<typename EqPred>
	SizeType Find(const TElement& val, const EqPred& pred,
		SizeType startIdx = 0, SizeType endIdx = m_nCount) const
	{
		if (endIdx > m_nCount)
			endIdx = m_nCount;

		for (SizeType idx = startIdx; idx < endIdx; ++idx)
		{
			if (pred(m_pData[idx], val))
				return idx;
		}
		return m_nCount;
	}

	TElement* PointerAt(SizeType idx)
	{
		if (idx >= m_nCount)
			return kZVD_NULLPTR(TElement);
		return m_pData + idx;
	}

	const TElement* PointerAt(SizeType idx) const
	{
		if (idx >= m_nCount)
			return kZVD_NULLPTR(TElement);
		return m_pData + idx;
	}

	Iterator Begin()
	{
		return m_nCount ? m_pData : End();
	}

	Iterator End()
	{
		return m_pData + m_nCount;
	}

	SizeType Size() const
	{
		return m_nCount;
	}

	SizeType Capacity() const
	{
		return m_nCapacity;
	}

	ZvdiMemoryAllocator::ResultType get_allocator()
	{
		return M_GetMemoryAllocator(kZVD_NO_U32);
	}

private:
	ZvdiMemoryAllocator::ResultType
	M_GetMemoryAllocator(
		ZvdUInt32 bUsedByThisClass = kZVD_YES_U32,
		void* pStackMem = kZVD_NULLVOID)
	{
		typedef ZvdiMemoryAllocator::ResultType Result;
		typedef TMemoryAllocator TAllocator;
		typedef ZvdiMemoryAllocator IAllocator;

		IAllocator* pAllocator = kZVD_NULLPTR(IAllocator);

		if (TAllocator::IsSingleton() == kZVD_YES_U32)
		{
			Result result = TAllocator::Instance();
			pAllocator = result.Get();
			ZVD_ASSERT_MEDIUM_NOMSG(pAllocator);
			if (!pAllocator)
			{
				if (result.Error().Code() == kZVD_EC_NOIMPL)
				{
					result.Error().SetStatusFlag(kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC);
					return result;
				}
				return result;
			}
			return result;
		}
#ifndef ZVD_USE_ZVD_AS_LIB_ONLY
		else if (TAllocator::IsSubsystem())
		{
			Result result = TAllocator::AsSubsystem();
			pAllocator = result.Get();
			if (!pAllocator)
			{
				if (result.Error().Code() == kZVD_EC_NOIMPL)
				{
					result.Error().SetStatusFlag(kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC);
					return result;
				}
				return result;
			}

			if (pAllocator->IsReady() == kZVD_NO_U32)
			{
				if (pAllocator->IsInitialized() == kZVD_NO_U32)
				{
					/// @todo log
					return Result(ZvdPackedError(kZVD_ES_ERROR, kZVD_ESRC_CORE_DARRAY, kZVD_EC_NOPRECOND));
				}
				/// @todo log
				return Result(ZvdPackedError(kZVD_ES_ERROR, kZVD_ESRC_CORE_DARRAY, kZVD_EC_NOPRECOND));
			}
		}
#endif // ! zvd as lib only
		else
		{
			// create mem alloc on stack of called function
			// This is default method if no any.

			ZVD_ASSERT_HIGH_NOMSG(kZVD_YES_U32 == bUsedByThisClass);
			ZVD_ASSERT_HIGH_NOMSG(pStackMem);

			if (TAllocator::CanBeCreatedOnStack() == kZVD_NO_U32)
			{
				return Result(ZvdPackedError(kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC, 
					kZVD_ESRC_CORE_DARRAY, kZVD_EC_NOSTACKALLOCATOR));
			}
			return TAllocator::CreateOnStack(pStackMem);
		}

		return Result(ZvdPackedError(kZVD_ES_FATAL, kZVD_ESRC_CORE_DARRAY, kZVD_EC_UNACCEPTABLE));
	}

	ZvdRegularResult GrowMemory(SizeType nGrowBy)
	{
		SizeType nNewCount = m_nCount + nGrowBy;

		if (nNewCount > m_nCapacity)
		{
			SizeType nNewCap = TUtil::GrowCapacity(nNewCount, m_nCapacity);

			ZvdRegularResult retVal = ResizeMemory(nNewCap);
			if (!retVal.IsOk())
			{
				return retVal;
			}
		}

		return ZvdRegularResult();
	}

	ZvdRegularResult M_ResizeMemoryIfData(SizeType nNewCap, ZvdiMemoryAllocator* pMemAlloc)
	{
		ZVD_ASSERT_HIGH_NOMSG(pMemAlloc);
		ZVD_ASSERT_HIGH_NOMSG(m_pData);
	
		if (0 == nNewCap)
		{
			Clear();
			ZvdRegularResult retVal = pMemAlloc->Deallocate(m_pData);
			if (!retVal.IsOk())
			{
				retVal.Error().AddCrashFlag();
				return retVal;
			}
			m_pData = kZVD_NULLPTR(TElement);
			m_nCapacity = 0;
			return retVal;
		}

		ZVD_ASSERT_HIGH_NOMSG(nNewCap);
		SizeType nReqBytes = sizeof(TElement) * nNewCap;
		ZvdResult<void*> memResult = pMemAlloc->Allocate(nReqBytes);
		if (!memResult.Get())
		{
			return ZvdRegularResult(memResult.Error());
		}

		TElement* pMemAsData = (TElement*)memResult.Get();
		for (SizeType i = 0; i < m_nCount; ++i)
		{
			TUtil::CopyConstruct(pMemAsData + i, m_pData[i]);
		}

		for (SizeType i = 0; i < m_nCount; ++i)
		{
			TUtil::Destroy(&m_pData[i]);
		}

		ZvdRegularResult retVal = pMemAlloc->Deallocate(m_pData);
		if (!retVal.IsOk())
		{
			retVal.Error().AddCrashFlag();
			return retVal;
		}
		
		m_pData = pMemAsData;
		m_nCapacity = nNewCap;
		return ZvdRegularResult();
	}

	ZvdRegularResult ResizeMemory(SizeType nNewCap)
	{
		ZVD_ASSERT_HIGH_NOMSG(nNewCap > 0);

		ZvdiMemoryAllocator* pMemAlloc = kZVD_NULLPTR(ZvdiMemoryAllocator);
		ZvdByte allocStorage[ZVD_ALIGNED_TYPE_SIZE(TMemoryAllocator, 0, 16)];
		ZvdiMemoryAllocator::ResultType allocatorResult = 
			M_GetMemoryAllocator(kZVD_YES_U32, &allocStorage[0]);
		if (!allocatorResult.IsOk())
		{
			return ZvdRegularResult(allocatorResult.Error());
		}
		pMemAlloc = allocatorResult.Get();
		ZVD_ASSERT_MEDIUM_NOMSG(pMemAlloc);

		if (m_pData)
		{
			return M_ResizeMemoryIfData(nNewCap, pMemAlloc);
		}

		ZVD_ASSERT_HIGH_NOMSG(!m_pData);

		if (nNewCap)
		{
			SizeType nReqBytes = sizeof(TElement) * nNewCap;
			ZvdResult<void*> memResult = pMemAlloc->Allocate(nReqBytes);
			if (!memResult.IsOk())
			{
				return ZvdRegularResult(memResult.Error());
			}

			m_pData = (TElement*)memResult.Get();
			m_nCapacity = nNewCap;
			return ZvdRegularResult();
		}
		return ZvdRegularResult(ZvdPackedError(kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC, kZVD_ESRC_CORE_DARRAY, kZVD_EC_UNACCEPTABLE));
	}

// Data members
private:
	TElement* m_pData;
	SizeType m_nCount;
	SizeType m_nCapacity;
#ifndef ZVD_USE_TDK_AS_LIB_ONLY
	TMemoryAllocator* m_pMemAlloc; // cached pointer to allocator
#endif
};


#endif // ZVD_DARRAY_H