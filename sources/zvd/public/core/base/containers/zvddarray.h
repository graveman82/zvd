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

#pragma once

#include "core/system/memory/zvdimemoryallocator.h"
#include "core/system/memory/zvdmallocfreeallocator.h"
#include "core/base/zvdassert.h"
#include "core/base/cpplib/zvdcppobj.h"

template <typename TElement, 
	typename TMemoryAllocator = ZvdcMallocFreeMemoryAllocator,
	typename TPolicies = ZvdRegularContainerPolicy<TElement>>
class ZvdcDArray
{
public:
	typedef size_t size_type;
	typedef TElement value_type;
	typedef TElement* pointer;
	typedef TElement* iterator;
	typedef const TElement* const_iterator;

	ZvdcDArray() = default;

	~ZvdcDArray()
	{
		clear();
		ZvdRegularResult retVal = ResizeMemory(0);
		if (!retVal.IsOk())
		{
			/// @todo
			// abort program
			ZvdfFatalError("ZvdcDArray destructor, ResizeMemory(0) returned %x", retVal.Error().RetVal());
		}
	}

	void clear()
	{
		std::destroy_n(m_pData, m_nCount);
		m_nCount = 0;
	}

	/// <summary>
	/// Changes the number of elements stored.
	/// If the new size is greater than the current size, new elements are default-constructed.
	/// </summary>
	ZvdRegularResult resize(size_type nNewCount)
	{
		if (nNewCount < m_nCount)
		{
			if constexpr (!std::is_trivially_destructible_v<TElement>)
			{
				std::destroy(m_pData + nNewCount, m_pData + m_nCount);
			}
			m_nCount = nNewCount;
			return ZvdRegularResult::Ok();
		}
		else if (nNewCount > m_nCount)
		{
			auto nGrowBy = nNewCount - m_nCount;
			ZvdRegularResult retVal = GrowMemory(nGrowBy);
			if (!retVal.IsOk())
			{
				return retVal;
			}
			
			try
			{
				std::uninitialized_default_construct_n(m_pData + m_nCount, nGrowBy);
			}
			catch (...)
			{
				return ZvdRegularResult(ZvdPackedError(kZVD_ES_ERROR,
					static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY),
					kZVD_EC_CONSTRUCTEXCEPTION));
			}

			m_nCount = nNewCount;
		}

		// If nNewCount == m_nCount, do nothing.
		return ZvdRegularResult::Ok();
	}

	ZvdRegularResult push_back(const TElement& val)
	{
		size_type nNewCount = m_nCount + 1;

		if (nNewCount > m_nCapacity)
		{
			return M_ResizeMemoryAndInsert(end(), val);
		}

		try
		{
			std::construct_at(m_pData + m_nCount, val);
		}
		catch (...)
		{
			return ZvdRegularResult(ZvdPackedError(kZVD_ES_ERROR,
				static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY),
				kZVD_EC_CONSTRUCTEXCEPTION));
		}
		++m_nCount;
		return ZvdRegularResult::Ok();
	}

	ZvdRegularResult push_back(TElement&& val)
	{
		size_type nNewCount = m_nCount + 1;

		if (nNewCount > m_nCapacity)
		{
			return M_ResizeMemoryAndInsert(end(), std::move(val));
		}

		try
		{
			std::construct_at(m_pData + m_nCount, std::move(val));
		}
		catch (...)
		{
			return ZvdRegularResult(ZvdPackedError(kZVD_ES_ERROR,
				static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY),
				kZVD_EC_CONSTRUCTEXCEPTION));
		}
		++m_nCount;
		return ZvdRegularResult::Ok();
	}

	ZvdRegularResult reserve(size_type nNewCap)
	{
		if (nNewCap <= m_nCapacity)
			return ZvdRegularResult::Ok();
		return ResizeMemory(nNewCap);
	}

	template<typename EqPred>
	size_type find(const TElement& val, const EqPred& pred,
		size_type startIdx = 0, size_type endIdx = m_nCount) const
	{
		if (endIdx > m_nCount)
			endIdx = m_nCount;

		for (size_type idx = startIdx; idx < endIdx; ++idx)
		{
			if (pred(m_pData[idx], val))
				return idx;
		}
		return m_nCount;
	}

	size_type size() const noexcept { return m_nCount; }
	size_type capacity() const noexcept { return m_nCapacity; }
	bool empty() const noexcept { return m_nCount == 0; }

	size_type max_size() const noexcept
	{
		// A theoretical maximum based on size_t and element size.
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	TElement& operator[](size_type nIndex)
	{
		ZVD_ASSERT_HIGH(nIndex < m_nCount, "Index out of bounds");
		return m_pData[nIndex];
	}

	const TElement& operator[](size_type nIndex) const
	{
		ZVD_ASSERT_HIGH(nIndex < m_nCount, "Index out of bounds");
		return m_pData[nIndex];
	}

	TElement& at(size_type nIndex)
	{
		if (nIndex >= m_nCount)
		{
			throw std::out_of_range("ZvdcDArray::at index out of bounds");
		}
		return m_pData[nIndex];
	}

	const TElement& at(size_type nIndex) const
	{
		if (nIndex >= m_nCount)
		{
			throw std::out_of_range("ZvdcDArray::at index out of bounds");
		}
		return m_pData[nIndex];
	}

	TElement& front()
	{
		ZVD_ASSERT_HIGH(!empty(), "front() called on empty array");
		return m_pData[0];
	}

	const TElement& front() const
	{
		ZVD_ASSERT_HIGH(!empty(), "front() called on empty array");
		return m_pData[0];
	}

	TElement& back()
	{
		ZVD_ASSERT_HIGH(!empty(), "back() called on empty array");
		return m_pData[m_nCount - 1];
	}

	const TElement& back() const
	{
		ZVD_ASSERT_HIGH(!empty(), "back() called on empty array");
		return m_pData[m_nCount - 1];
	}

	TElement* data() noexcept { return m_pData; }
	const TElement* data() const noexcept { return m_pData; }

	iterator begin() noexcept { return m_pData; }
	iterator end() noexcept { return m_pData + m_nCount; }
	const_iterator begin() const noexcept { return m_pData; }
	const_iterator end() const noexcept { return m_pData + m_nCount; }

	constexpr const_iterator cbegin() const noexcept { return m_pData; }
	constexpr const_iterator cend() const noexcept { return m_pData + m_nCount; }

	ZvdiMemoryAllocator::ResultType get_allocator()
	{
		return M_GetMemoryAllocator(false);
	}

private:
	ZvdiMemoryAllocator::ResultType
	M_GetMemoryAllocator(
		bool bUsedByThisClass = true,
		void* pStackMem = nullptr)
	{
		typedef ZvdiMemoryAllocator::ResultType Result;
		typedef TMemoryAllocator TAllocator;
		typedef ZvdiMemoryAllocator IAllocator;

		IAllocator* pAllocator = nullptr;

		if (TAllocator::IsSingleton() == true)
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

			if (pAllocator->IsReady() == false)
			{
				if (pAllocator->IsInitialized() == false)
				{
					/// @todo log
					return Result(nullptr, ZvdPackedError(kZVD_ES_ERROR, 
						static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
							kZVD_EC_NOPRECOND));
				}
				/// @todo log
				return Result(nullptr, ZvdPackedError(kZVD_ES_ERROR, 
					static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
						kZVD_EC_NOPRECOND));
			}
		}
#endif // ! zvd as lib only
		else
		{
			// create mem alloc on stack of called function
			// This is default method if no any.

			ZVD_ASSERT_HIGH_NOMSG(true == bUsedByThisClass);
			ZVD_ASSERT_HIGH_NOMSG(pStackMem);

			if (TAllocator::CanBeCreatedOnStack() == false)
			{
				return Result(nullptr, ZvdPackedError(kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC, 
					static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
						kZVD_EC_NOSTACKALLOCATOR));
			}
			return TAllocator::CreateOnStack(pStackMem);
		}

		return Result(nullptr, ZvdPackedError(kZVD_ES_FATAL, 
			static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
				kZVD_EC_UNACCEPTABLE));
	}

	ZvdRegularResult GrowMemory(size_type nGrowBy)
	{
		size_type nNewCount = m_nCount + nGrowBy;

		if (nNewCount > m_nCapacity)
		{
			size_type nNewCap = TPolicies::GrowCapacity(nNewCount, m_nCapacity);

			ZvdRegularResult retVal = ResizeMemory(nNewCap);
			if (!retVal.IsOk())
			{
				return retVal;
			}
		}

		return ZvdRegularResult();
	}

	template<typename... TArgs>
	ZvdRegularResult M_ResizeMemoryAndInsert(iterator position, TArgs&&... args)
	{
		static_assert(sizeof...(TArgs) > 0, "M_ResizeMemoryAndInsert requires at least one argument after position!");

		ZvdiMemoryAllocator* pMemAlloc{};
		ZvdByte allocStorage[ZVD_ALIGNED_TYPE_SIZE(TMemoryAllocator, 0, 16)];
		ZvdiMemoryAllocator::ResultType allocatorResult = M_GetMemoryAllocator(true, &allocStorage[0]);
		if (!allocatorResult.IsOk())
		{
			return ZvdRegularResult(allocatorResult.Error());
		}
		pMemAlloc = allocatorResult.Get();
		ZVD_ASSERT_MEDIUM_NOMSG(pMemAlloc);

		ZVD_ASSERT_HIGH_NOMSG(m_pData);
		const size_type nGrowBy{ 1 };

		size_type nNewCap = M_CalculateSafeNewCapacity(nGrowBy, "ZvdcDArray reallocation exceeds max_size()").Get();

		size_type nReqBytes = sizeof(TElement) * nNewCap;
		ZvdPointerResult<void> memResult = pMemAlloc->Allocate(nReqBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
			, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryAndInsert"
#endif
		);
		if (!memResult.Get())
		{
			return ZvdRegularResult(memResult.Error());
		}

		TElement* pNewMemAsData = (TElement*)memResult.Get();
		const size_type nInsertIndex = position - begin();
		const_iterator citInsertPosition = cbegin() + nInsertIndex;
		iterator itInsertPosition = begin() + nInsertIndex;
		TElement* pInsertedMem = std::addressof(pNewMemAsData[nInsertIndex]);

		// insert new values
		try
		{
			std::construct_at(pInsertedMem, std::forward<TArgs>(args)...);
		}
		catch (...)
		{
			ZvdRegularResult retVal = pMemAlloc->Deallocate(pNewMemAsData
#ifdef ZVD_CFG_DEBUG_MEMORY
				, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryAndInsert"
#endif	
			);
			if (!retVal.IsOk())
			{
				retVal.Error().AddCrashFlag();
				return retVal;
			}
			return ZvdRegularResult(ZvdPackedError(kZVD_ES_ERROR, 
				static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
					kZVD_EC_CONSTRUCTEXCEPTION));
		}

		if constexpr (std::is_nothrow_move_constructible_v<TElement>)
		{
			std::uninitialized_move(begin(), itInsertPosition, pNewMemAsData);
			std::uninitialized_move(itInsertPosition, end(), pInsertedMem + nGrowBy);
		}
		else
		{
			// insert old values (before)
			try
			{
				std::uninitialized_copy(cbegin(), citInsertPosition, pNewMemAsData);
			}
			catch (...)
			{
				std::destroy_at(std::addressof(*pInsertedMem));
				ZvdRegularResult retVal = pMemAlloc->Deallocate(pNewMemAsData
#ifdef ZVD_CFG_DEBUG_MEMORY
					, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryAndInsert"
#endif
				);
				if (!retVal.IsOk())
				{
					retVal.Error().AddCrashFlag();
					return retVal;
				}
				return ZvdRegularResult(ZvdPackedError(kZVD_ES_ERROR, 
					static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
						kZVD_EC_CONSTRUCTEXCEPTION));
			}

			// insert old values (after)
			try
			{
				std::uninitialized_copy(citInsertPosition, cend(), pInsertedMem + nGrowBy);
			}
			catch (...)
			{
				std::destroy(pNewMemAsData, pInsertedMem + nGrowBy);
				ZvdRegularResult retVal = pMemAlloc->Deallocate(pNewMemAsData
#ifdef ZVD_CFG_DEBUG_MEMORY
					, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryAndInsert"
#endif
				);
				if (!retVal.IsOk())
				{
					retVal.Error().AddCrashFlag();
					return retVal;
				}
				return ZvdRegularResult(ZvdPackedError(kZVD_ES_ERROR, 
					static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
						kZVD_EC_CONSTRUCTEXCEPTION));
			}
		}

		if (m_pData)
		{
			if constexpr (!std::is_trivially_destructible_v<TElement>)
			{
				std::destroy(begin(), end());
			}
	
			ZvdRegularResult retVal = pMemAlloc->Deallocate(m_pData
#ifdef ZVD_CFG_DEBUG_MEMORY
				, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryAndInsert"
#endif
			);
			if (!retVal.IsOk())
			{
				retVal.Error().AddCrashFlag();
				return retVal;
			}
		}

		m_pData = pNewMemAsData;
		m_nCapacity = nNewCap;
		m_nCount += nGrowBy;

		return ZvdRegularResult::Ok();
	}

	ZvdRegularResult ResizeMemory(size_type nNewCap)
	{
		if (m_pData)
		{
			return M_ResizeMemoryIfData(nNewCap);
		}

		ZvdiMemoryAllocator* pMemAlloc = nullptr;
		ZvdByte allocStorage[ZVD_ALIGNED_TYPE_SIZE(TMemoryAllocator, 0, 16)];
		ZvdiMemoryAllocator::ResultType allocatorResult =
			M_GetMemoryAllocator(true, &allocStorage[0]);
		if (!allocatorResult.IsOk())
		{
			return ZvdRegularResult(allocatorResult.Error());
		}
		pMemAlloc = allocatorResult.Get();
		ZVD_ASSERT_MEDIUM_NOMSG(pMemAlloc);

		ZVD_ASSERT_HIGH_NOMSG(!m_pData);
		if (0 == nNewCap)
		{
			return ZvdRegularResult::Ok();
		}
		ZVD_ASSERT_HIGH_NOMSG(nNewCap > 0);

		size_type nReqBytes = sizeof(TElement) * nNewCap;
		ZvdPointerResult<void> memResult = pMemAlloc->Allocate(nReqBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
			, __FILE__, __LINE__, "ZvdRcDArray::ResizeMemory"
#endif
		);
		if (!memResult.IsOk())
		{
			return ZvdRegularResult(memResult.Error());
		}

		m_pData = (TElement*)memResult.Get();
		m_nCapacity = nNewCap;
		return ZvdRegularResult::Ok();
	}

	ZvdRegularResult M_ResizeMemoryIfData(size_type nNewCap)
	{
		ZvdiMemoryAllocator* pMemAlloc{};
		ZvdByte allocStorage[ZVD_ALIGNED_TYPE_SIZE(TMemoryAllocator, 0, 16)];
		ZvdiMemoryAllocator::ResultType allocatorResult = M_GetMemoryAllocator(true, &allocStorage[0]);
		if (!allocatorResult.IsOk())
		{
			return ZvdRegularResult(allocatorResult.Error());
		}
		pMemAlloc = allocatorResult.Get();
		ZVD_ASSERT_MEDIUM_NOMSG(pMemAlloc);

		ZVD_ASSERT_HIGH_NOMSG(m_pData);
	
		if (0 == nNewCap)
		{
			if (m_nCount > 0)
			{
				if constexpr (!std::is_trivially_destructible_v<TElement>)
				{
					std::destroy(begin(), end());
				}
				m_nCount = 0;
			}
			ZvdRegularResult retVal = pMemAlloc->Deallocate(m_pData
#ifdef ZVD_CFG_DEBUG_MEMORY
				, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryIfData"
#endif
			);
			if (!retVal.IsOk())
			{
				retVal.Error().AddCrashFlag();
				return retVal;
			}
			m_pData = nullptr;
			m_nCapacity = 0;
			return retVal;
		}

		ZVD_ASSERT_HIGH_NOMSG(nNewCap);
		size_type nReqBytes = sizeof(TElement) * nNewCap;
		ZvdPointerResult<void> memResult = pMemAlloc->Allocate(nReqBytes
#ifdef ZVD_CFG_DEBUG_MEMORY
			, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryIfData"
#endif
		);
		if (!memResult.Get())
		{
			return ZvdRegularResult(memResult.Error());
		}

		TElement* pNewMemAsData = (TElement*)memResult.Get();
		
		if constexpr (std::is_nothrow_move_constructible_v<TElement>)
		{
			std::uninitialized_move(begin(), end(), pNewMemAsData);
		}
		else
		{
			try
			{
				std::uninitialized_copy(cbegin(), cend(), pNewMemAsData);
			}
			catch (...)
			{
				ZvdRegularResult retVal = pMemAlloc->Deallocate(pNewMemAsData
#ifdef ZVD_CFG_DEBUG_MEMORY
					, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryIfData"
#endif			
				);
				if (!retVal.IsOk())
				{
					retVal.Error().AddCrashFlag();
					return retVal;
				}
				return ZvdRegularResult(ZvdPackedError(kZVD_ES_ERROR,
					static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY),
					kZVD_EC_CONSTRUCTEXCEPTION));
			}
		}
		
		ZvdRegularResult retVal = pMemAlloc->Deallocate(m_pData
#ifdef ZVD_CFG_DEBUG_MEMORY
			, __FILE__, __LINE__, "ZvdRcDArray::M_ResizeMemoryIfData"
#endif
		);
		if (!retVal.IsOk())
		{
			retVal.Error().AddCrashFlag();
			return retVal;
		}
		
		m_pData = pNewMemAsData;
		m_nCapacity = nNewCap;
		return ZvdRegularResult::Ok();
	}

	/// <summary>
	/// Calculates a new, safe capacity required to hold at least nGrowBy.
	/// Returns the proposed new capacity.
	/// </summary>
	ZvdUIndexResult<size_type> M_CalculateSafeNewCapacity(size_type nGrowBy, const char* pDebugComment) const
	{
		if (max_size() - size() < nGrowBy)
		{
			return ZvdUIndexResult<size_type>(kZVD_INVALID_INDEX,
				ZvdPackedError(kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC, 
					static_cast<std::underlying_type_t<ZvdeErrorSource>>(ZvdeErrorSource::kCORE_DARRAY), 
						kZVD_EC_LENGTHERROR),
				pDebugComment);
		}

		const size_type nNewCount = m_nCount + nGrowBy;
		size_type nNewCap = TPolicies::GrowCapacity(nNewCount, m_nCapacity);

		return (nNewCap > max_size()) ? max_size() : nNewCap;
	}
// Data members
private:
	TElement* m_pData{};
	size_type m_nCount{};
	size_type m_nCapacity{};
#ifndef ZVD_USE_TDK_AS_LIB_ONLY
	TMemoryAllocator* m_pMemAlloc{}; // cached pointer to allocator
#endif
};
