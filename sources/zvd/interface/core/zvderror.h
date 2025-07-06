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
Purpose: error handling related definitions.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_ERROR_H
#define ZVD_ERROR_H

#include "core/zvdbasedefs.h"
#include "core/zvdbyteutils.h"

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

	/// error was raised at external code (in 1st byte if begin since 0)
	kZVD_EF_EXTLIB = (1 << 7)
};

// Error byte main values
//------------------------

/// nothing known about some error case
const ZvdByte kZVD_B_UNKNOWN = kZVD_EF_UNKNOWN;

/// operation succeeded
const ZvdByte kZVD_B_OK = kZVD_EF_SUCCESS;

/// operation succeeded (did nothing)
const ZvdByte kZVD_B_NOTHING = kZVD_EF_STOP;

/// operation failed
const ZvdByte kZVD_B_ERROR = kZVD_EF_FAIL;

/// operation canceled by caller (user)
const ZvdByte kZVD_B_CANCEL = kZVD_EF_CANCEL;

/// operation failed
const ZvdByte kZVD_B_FATAL = kZVD_EF_FATAL;

// Returned value limits
//----------------------

/// source mask
const ZvdByte kZVD_E_SOURCEMASK = 0x7F;
const ZvdByte kZVD_E_SOURCEMASKEXT = 0x80;

/// code mask LE
const ZvdUInt16 kZVD_E_CODE_MAX = 32767u;

#pragma pack(push, 1)
//-----------------------------------------------------------------------------
class ZvdPackedError
{
public:
	ZvdPackedError(ZvdRetVal retVal = 0u) : m_retVal{ retVal } {}
	ZvdPackedError(ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt = false);

	ZvdRetVal RetVal() const { return m_retVal; }
	ZvdByte Status() const;
	ZvdByte Source(bool& bExt) const;
	ZvdUInt16 Code() const;

	static ZvdPackedError Ok();
private:
	static void Pack(ZvdRetVal& retVal, ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt);
	ZvdRetVal m_retVal;
};
#pragma pack(pop)


struct ZvdResultDescOnlyTag {};
struct ZvdResultIndexTag {};



template <typename Tag>
struct ZvdResult;

#pragma pack(push, 1)
template <>
struct ZvdResult<ZvdResultDescOnlyTag>
{
	ZvdResult()
	{
	}

	ZvdPackedError m_packedError;
};
#pragma pack(pop)

#pragma pack(push, 1)
template <>
struct ZvdResult <ZvdResultIndexTag> : ZvdResult<ZvdResultDescOnlyTag>
{
	ZvdResult()
		: m_nIndex(0)
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
struct ZvdResult <T*> : ZvdResult <ZvdResultDescOnlyTag>
{
	ZvdResult()
		: m_ptr(kZVD_NULLPTR(T))
	{
#if defined(ZVD_ARCH_X64)
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3];
#endif
	}

	T* m_ptr;

#if defined(ZVD_ARCH_X64)
	ZvdByte m_pad[4];
#endif
};
#pragma pack(pop)


//-----------------------------------------------------------------------------
enum ZvdErrorSource
{
	kCore,
	kLangLib,
	kEngine,
	kSystem,
	kMemMng,
	kGfxDev
};




#endif // ZVD_ERROR_H