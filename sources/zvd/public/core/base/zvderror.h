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

enum ZvdeErrorLevel
{
	kZVD_WARN,
	kZVD_ERROR,
	kZVD_FATAL
};

/** Reports error and terminates program.
 */
void ZvdfFatalError(const char* pFormat, ...);

//=============================================================================
// Error format

// Use it to return from functions.
typedef uint32_t ZvdRetVal;

//-----------------------------------------------------------------------------
/// <summary>
/// A bitmask of flags that define the status and severity of an error.
/// This is packed into the first byte of a ZvdPackedError.
/// Flags can be combined using the bitwise OR operator.
/// Error codes must be interpreted
/// in context of local operation.
/// "E" means error. "EF" means error flag.
/// </summary>
/// <example><code>
/// ZvdByte status = kZVD_ES_FATAL | kZVD_EF_BAD_LOGIC;
/// </code></example>
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

const uint32_t kZVD_E_CODE_MAX = 32767;
#pragma pack(push, 1)

//-----------------------------------------------------------------------------
/// <summary>
/// A compact, 32-bit error object that packs status, source, and a specific code.
/// This is the core error type used throughout the engine instead of exceptions.
/// It is designed to be returned by value from functions.
///
/// The 32-bit value is structured as follows:
/// - Byte 0: Status flags (e.g., success, error, fatal). See ZvdeErrorControlBits.
/// - Byte 1: Source ID of the error (e.g., renderer, physics). See ZvdeErrorSource.
/// - Word 1 (Bytes 2-3): Specific error code. See ZvdeErrorCodes.
/// </summary>
/// <example><code>
/// ZvdPackedError error(kZVD_ES_ERROR, kZVD_ESRC_CORE_DARRAY, kZVD_EC_OUT_OF_RANGE);
/// </code></example>
class ZvdPackedError
{
public:
	ZvdPackedError();
	ZvdPackedError(ZvdRetVal retVal) : m_retVal{ retVal } {}
	ZvdPackedError(ZvdByte nStatus, ZvdByte nSource, uint16_t nCode, bool bExt = false);
	ZvdPackedError(const ZvdPackedError& oth)
		: m_retVal(oth.RetVal())
	{

	}

	// setters
	void SetStatusFlag(uint8_t statusFlag);
	void AddStatusFlag(uint8_t statusFlag);
	void AddCrashFlag();

	// getters
	ZvdRetVal RetVal() const { return m_retVal; }
	ZvdByte Status() const;
	ZvdByte Source(bool& bExt) const;
	uint16_t Code() const;

	bool IsOk() const;
	static const ZvdPackedError& Ok();
	static bool HasErrorMarker(ZvdRetVal val);
private:
	static void Pack(ZvdRetVal& retVal, ZvdByte nStatus, ZvdByte nSource, uint16_t nCode, bool bExt);
	ZvdRetVal m_retVal;
};
#pragma pack(pop)


template <typename Tag, typename... TArgs>
struct ZvdResult;

#pragma pack(push, 1)
template <>
struct ZvdResult<ZvdsDefaultTag>
{
	ZvdResult(const ZvdPackedError& packedError = ZvdPackedError::Ok(),
		const char* pText = nullptr)
		: m_packedError{ packedError }
		, m_pText{ pText }
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

	/// <summary>
	/// A factory method to create a success result object for cleaner code.
	/// </summary>
	static ZvdResult<ZvdsDefaultTag> Ok()
	{
		// It just calls the default constructor which already defaults to an OK state.
		return ZvdResult<ZvdsDefaultTag>();
	}

	ZvdPackedError m_packedError;
	const char* m_pText{};
};
#pragma pack(pop)



/// <summary>
/// A generic result object that wraps a ZvdPackedError.
/// This is the primary type that functions should return to indicate success or failure.
/// </summary>
/// <example><code>
/// ZvdRegularResult MyFunction()
/// {
///     if (error)
///         return ZvdRegularResult(myPackedError);
///     return ZvdRegularResult::Ok(); // or just ZvdRegularResult();
/// }
/// </code></example>
typedef ZvdResult<ZvdsDefaultTag> ZvdRegularResult;

struct ZvdResultIndexTag {};

#pragma pack(push, 1)
template <typename TIndex>
struct ZvdResult <ZvdResultIndexTag, TIndex> : ZvdResult<ZvdsDefaultTag>
{
	ZvdResult(TIndex nIndex = kZVD_INVALID_INDEX, 
		const ZvdPackedError& packedError = ZvdPackedError::Ok(),
		const char* pText = nullptr)
		: ZvdResult<ZvdsDefaultTag>(packedError, pText)
		, m_nIndex{ nIndex }
	{
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3];
	}

	TIndex Get() const { return m_nIndex; }

	TIndex m_nIndex{};
	ZvdByte m_pad[4];
}; 
#pragma pack(pop)

template <typename TIndex>
using ZvdUIndexResult = ZvdResult <ZvdResultIndexTag, TIndex>;

struct ZvdResultPointerTag {};

#pragma pack(push, 1)
template <typename T>
struct ZvdResult<ZvdResultPointerTag, T*> : ZvdRegularResult
{
	ZvdResult(T* ptr = nullptr, 
		const ZvdPackedError& packedError = ZvdPackedError::Ok(),
		const char* pText = nullptr)
		: ZvdRegularResult(packedError, pText)
		, m_ptr{ptr}
	{
		m_pad[0] = m_pad[1] = m_pad[2] = m_pad[3];
	}

	T* Get() { return m_ptr; }
	void Set(T* ptr) { m_ptr = ptr; }

	T* m_ptr{};
	ZvdByte m_pad[4];
};
#pragma pack(pop)

template <typename T>
using ZvdPointerResult = ZvdResult <ZvdResultPointerTag, T*>;

//-----------------------------------------------------------------------------
/// <summary>
/// An enumeration of modules or subsystems where an error can originate.
/// The value is packed into the second byte of a ZvdPackedError.
/// The valid range for custom sources is from 1 to 127.
/// </summary>
enum class ZvdeErrorSource : uint8_t
{
	kUNDEFINED = 0, // if no error, there is no source
	kCORE_MEMORY,
	kCORE_DARRAY,
	kMAX = 127
};




#endif // ZVD_ERROR_H