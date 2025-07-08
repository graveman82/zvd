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
Purpose: error processing & reporting.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_ERROR_H
#define ZVD_ERROR_H

#include "core/base/zvderrorcodes.h"
#include "core/base/zvdbyteutils.h"

//=============================================================================
// Error format

// Use it to return from functions.
typedef ZvdUInt32 ZvdRetVal;

// Main (control) bits of error value
// Use other 6 bit for 64 codes. Error codes must be interpreted
// in context of local operation.
// "E" means error. "EF" means error flag.
//-------------------------------------------------
enum ZvdeErrorControlBits
{
	// 0 byte
	//

	/// no error (success)
	kZVD_EF_SUCCESS = 0,
	kZVD_EF_STOP = 1,
	/// special marker - dependent flag
	kZVD_EF_SPECIAL = (1 << 2),
	/// error marker
	kZVD_EF_FAIL = (1 << 1),
	/// no resource
	kZVD_EF_NO_RESOURCE = (1 << 3),
	/// bad resource
	kZVD_EF_BAD_RESOURCE = (1 << 4),
	/// logic error
	kZVD_EF_BAD_LOGIC = (1 << 5),
	/// crash ("Houston, we have a problem")
	kZVD_EF_CRASH = (1 << 6),

	/// big endian marker (7th & 31th bits of return value are always zero on LE-machines)
	kZVD_EF_BE = (1 << 7),

	kZVD_EF_UNKNOWN = kZVD_BAD_MARKER_U3,
	kZVD_EF_CANCEL = kZVD_EF_STOP | kZVD_EF_SPECIAL,
	kZVD_EF_FATAL = kZVD_EF_FAIL | kZVD_EF_SPECIAL,
	///  Abort program. Error is in design.
	kZVD_EF_ABORT = kZVD_EF_FATAL | kZVD_EF_CRASH,
	/// error was raised at external code (in 1st byte if begin since 0)
	kZVD_EF_EXTLIB = (1 << 7)
};

// Error byte main values
//------------------------

/// nothing known about some error case
const ZvdByte kZVD_ES_UNKNOWN = kZVD_EF_UNKNOWN;

/// operation succeeded
const ZvdByte kZVD_ES_OK = kZVD_EF_SUCCESS;

/// operation succeeded (did nothing)
const ZvdByte kZVD_ES_NOTHING = kZVD_EF_STOP;

/// operation failed
const ZvdByte kZVD_ES_ERROR = kZVD_EF_FAIL;

/// operation canceled by caller (user)
const ZvdByte kZVD_ES_CANCEL = kZVD_EF_CANCEL;

/// operation failed
const ZvdByte kZVD_ES_FATAL = kZVD_EF_FATAL;

// Returned value limits
//----------------------

/// source mask
const ZvdByte kZVD_EM_SOURCEMASK = 0x7F;
const ZvdByte kZVD_EM_SOURCEMASKEXT = 0x80;


#pragma pack(push, 1)
//-----------------------------------------------------------------------------
class ZvdPackedError
{
public:
	ZvdPackedError();
	ZvdPackedError(ZvdRetVal retVal) : m_retVal{ retVal } {}
	ZvdPackedError(ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt = false);
	ZvdPackedError(const ZvdPackedError& oth)
		: m_retVal(oth.RetVal())
	{

	}

	// setters
	void SetStatusFlag(ZvdUInt8 statusFlag);
	void AddStatusFlag(ZvdUInt8 statusFlag);
	void AddCrashFlag();

	// getters
	ZvdRetVal RetVal() const { return m_retVal; }
	ZvdByte Status() const;
	ZvdByte Source(bool& bExt) const;
	ZvdUInt16 Code() const;

	bool IsOk() const;
	static const ZvdPackedError& Ok();
	static bool HasErrorMarker(ZvdRetVal val);
private:
	static void Pack(ZvdRetVal& retVal, ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt);
	ZvdRetVal m_retVal;
};
#pragma pack(pop)


struct ZvdResultIndexTag {};



template <typename Tag>
struct ZvdResult;

#pragma pack(push, 1)
template <>
struct ZvdResult<ZvdsDefaultTag>
{
	ZvdResult(const ZvdPackedError& packedError = ZvdPackedError::Ok())
		: m_packedError(packedError)
		, m_pText(kZVD_NULLCSTR)
	{
	}

	const ZvdPackedError& Error() const 
	{
		return m_packedError;
	}

	ZvdPackedError& Error()
	{
		return m_packedError;
	}

	bool IsOk() const { return m_packedError.IsOk(); }

	const char* Text() const { return m_pText; }
	void SetText(const char* pText) { m_pText = pText; }

	ZvdPackedError m_packedError;
	const char* m_pText;
};
#pragma pack(pop)

typedef ZvdResult<ZvdsDefaultTag> ZvdRegularResult;

#pragma pack(push, 1)
template <>
struct ZvdResult <ZvdResultIndexTag> : ZvdRegularResult
{
	ZvdResult(const ZvdPackedError& packedError = ZvdPackedError::Ok())
		: ZvdResult<ZvdsDefaultTag>(packedError)
		, m_nIndex(0)
	{
#if defined(ZVD_ARCH_X64)
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3];
#endif
	}

	ZvdUIndex m_nIndex;

#if defined(ZVD_ARCH_X64)
	ZvdByte m_pad[4];
#endif
}; 
#pragma pack(pop)

#pragma pack(push, 1)
template <typename T>
struct ZvdResult<T*> : ZvdRegularResult
{
	ZvdResult(const ZvdPackedError& packedError = ZvdPackedError::Ok())
		: ZvdRegularResult(packedError)
		, m_ptr(kZVD_NULLPTR(T))
	{
#if defined(ZVD_ARCH_X64)
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3];
#endif
	}

	ZvdResult(const ZvdPackedError& packedError, T* ptr)
		: ZvdRegularResult(packedError)
		, m_ptr(ptr)
	{
#if defined(ZVD_ARCH_X64)
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3];
#endif
	}

	
	T* Get() { return m_ptr; }
	void Set(T* ptr) { m_ptr = ptr; }
	T* m_ptr;

#if defined(ZVD_ARCH_X64)
	ZvdByte m_pad[4];
#endif
};
#pragma pack(pop)


//-----------------------------------------------------------------------------
enum ZvdErrorSource
{
	kZVD_ESRC_UNDEFINED,
	kZVD_ESRC_CORE_MEMORY,
	kZVD_ESRC_CORE_DARRAY,
	kLangLib,
	kEngine,
	kSystem,
	kMemMng,
	kGfxDev
};




#endif // ZVD_ERROR_H