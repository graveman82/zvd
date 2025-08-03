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
Purpose: error processing and reporting operations implementation.

----------------------
 For developers notes
----------------------
Original author:    Marat Sungatullin
Created:            jan 13, 2012
*/

#include "core/base/zvderror.h"
#include "core/base/zvdassert.h"
#include "core/base/zvdbyteutils.h"
#include "core/base/zvdstaticsingleton.h"
#include "core/base/cpplib/zvdstdstringutils.h"

#ifdef ZVD_MSVC
#include <Windows.h>
#endif

#include <new>

#if 0
const char* ZvdErrorStatusToCString(ZvdByte nStatus)
{
	static const char* textualDesc[] =
	{
		"Unknown",
		"None",
		"Ok" ,
		"Fail",
		"Warning",
		"Error",
		"Cancel"
	};
	
	return textualDesc[status];
}
#endif

//-----------------------------------------------------------------------------
ZvdPackedError::ZvdPackedError()
{
	Pack(m_retVal, kZVD_ES_FATAL, kZVD_ESRC_UNDEFINED, kZVD_EC_UNACCEPTABLE, false);
}

//-----------------------------------------------------------------------------
ZvdPackedError::ZvdPackedError(ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt)
{ 
	Pack(m_retVal, nStatus, nSource, nCode, bExt);
}

//-----------------------------------------------------------------------------
void ZvdPackedError::Pack(ZvdRetVal& retVal, ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt)
{
	ZvdSetByte(retVal, 0, nStatus);
	ZvdSetByte(retVal, 1, (nSource & kZVD_EM_SOURCEMASK) | (bExt ? kZVD_EF_EXTLIB : 0u));
	ZVD_ASSERT_HIGH_NOMSG(nCode <= kZVD_E_CODE_MAX);
	ZvdSetWord(retVal, 1, nCode);
}

//-----------------------------------------------------------------------------
ZvdByte ZvdPackedError::Status() const
{
	return ZvdGetByte(m_retVal, 0);
}

//-----------------------------------------------------------------------------
ZvdByte ZvdPackedError::Source(bool& bExt) const
{
	ZvdByte nSource = ZvdGetByte(m_retVal, 1);
	bExt = (nSource & kZVD_EM_SOURCEMASKEXT) != 0u;
	return nSource & kZVD_EM_SOURCEMASK;
}

//-----------------------------------------------------------------------------
ZvdUInt16 ZvdPackedError::Code() const
{
	return ZvdGetWord(m_retVal, 1);
}

//-----------------------------------------------------------------------------
const ZvdPackedError& ZvdPackedError::Ok()
{
	static ZvdPackedError sOk(kZVD_ES_OK, kZVD_ESRC_UNDEFINED, kZVD_EC_UNDEFINED);
	return sOk;
}

//-----------------------------------------------------------------------------
void ZvdPackedError::SetStatusFlag(ZvdUInt8 statusFlag)
{
	ZvdSetByte(m_retVal, 0, statusFlag);
}

//-----------------------------------------------------------------------------
void ZvdPackedError::AddStatusFlag(ZvdUInt8 statusFlag)
{
	ZvdSetByte(m_retVal, 0, ZvdGetByte(m_retVal, 0) | statusFlag);
}

//-----------------------------------------------------------------------------
void ZvdPackedError::AddCrashFlag()
{
	AddStatusFlag(kZVD_EF_ABORT);
}

//-----------------------------------------------------------------------------
bool ZvdPackedError::IsOk() const
{
	return Status() == kZVD_ES_OK;
}

//-----------------------------------------------------------------------------
bool ZvdPackedError::HasErrorMarker(ZvdRetVal val)
{
	return (ZvdGetByte(val, 0) & kZVD_EF_FAIL) != 0;
}


//=============================================================================
// Error handling.
//=============================================================================



namespace zvd
{
	namespace details
	{
		class ErrorReporter;
		struct ErrorReporterCtor
		{
			ErrorReporter* operator()(void* p);
		};
		
		// for size calculation
		struct ErrorReporterData
		{
			enum Constants
			{
				kDESC_BUF_SIZE = 1024
			};
			typedef ZVD_ASSERT_CHARTYPE CharType;
			typedef const CharType* ConstStringType;

		private:
			CharType m_descBuffer[kDESC_BUF_SIZE];
			ZvdUInt32 m_bInReporting{ kZVD_NO_U32 };
			ConstStringType m_fileAndLine;
		};

		typedef ZvdStaticSingleton<ErrorReporter,
			ZVD_ALIGNED_TYPE_SIZE(ErrorReporterData, 0, 16),
			ErrorReporterCtor> ErrorReporterBase;

		class ErrorReporter : public ErrorReporterBase
		{
		public:
			enum Constants
			{
				kDESC_BUF_SIZE = ErrorReporterData::kDESC_BUF_SIZE
			};
			typedef ErrorReporterData::CharType CharType;
			typedef ErrorReporterData::ConstStringType ConstStringType;

			friend class ZvdStaticSingleton<ErrorReporter,
				ZVD_ALIGNED_TYPE_SIZE(ErrorReporterData, 0, 16),
				ErrorReporterCtor>;
			friend struct ErrorReporterCtor;

			ErrorReporter()
				: m_bInReporting( kZVD_NO_U32 )
				, m_fileAndLine(ZVD_ASSERT_TEXT("")) {}

			ZvdUInt32 Report(ZvdeErrorLevel level, ZvdUInt32 bLog, const char* pFormat, va_list params)
			{
				// disable recursion
				if (m_bInReporting)
					return kZVD_NO_U32;
				m_bInReporting = kZVD_YES_U32;
				
				const char* pTitle = "Warning: \n";
				if ((ZvdInt32)level == kZVD_FATAL)
				{
					pTitle = "FatalError:\n";
				}
				else if ((ZvdInt32)level == kZVD_ERROR)
				{
					pTitle = "Error:\n";
				}
				
				// format the message and save it in buffer
				
				Zvdf_strcpy(m_descBuffer, kDESC_BUF_SIZE, pTitle);
				ZvdSize nTitleLen = Zvdf_strlen(pTitle);
				ZvdSize nBufSize = kDESC_BUF_SIZE - nTitleLen;
				char* pBuf = m_descBuffer + nTitleLen;
				Zvdf_vsnprintf(pBuf, nBufSize, nBufSize - 1, pFormat, params);
				
				// print the buffer to the console
				/// @todo
				if (bLog)
				{
					/// @todo
				}
				
#ifdef ZVD_MSVC
				
				::MessageBoxA(kZVD_NULLVOID, m_descBuffer, "Fatal Error",
					MB_OK | MB_ICONHAND | MB_SETFOREGROUND | MB_TASKMODAL);
#endif
				m_descBuffer[0] = '\0';
				m_bInReporting = kZVD_NO_U32;
				return kZVD_YES_U32;
			}

			void Set(ConstStringType fileAndLine)
			{
				m_fileAndLine = fileAndLine;
			}

			ConstStringType FileAndLine() const { return m_fileAndLine; }

			ZvdUInt32 IsInReporting() const { return m_bInReporting; }

		private:
			CharType m_descBuffer[kDESC_BUF_SIZE];
			ZvdUInt32 m_bInReporting;
			ConstStringType m_fileAndLine;
		};

		ErrorReporter* ErrorReporterCtor::operator()(void* p)
		{
			return ::new(p) ErrorReporter();
		}
	} // eof details
} // eof zvd


void ZvdfFatalError(const char* pFormat, ...)
{
	zvd::details::ErrorReporter& errorReporter = zvd::details::ErrorReporter::Instance();

	// disable recursion
	if (errorReporter.IsInReporting())
		return;

	va_list args;
	va_start(args, pFormat);
	errorReporter.Report(kZVD_FATAL, kZVD_YES_U32, pFormat, args);
	va_end(args);
	
	
	// exit program
	//exit(EXIT_FAILURE);
}