// Zv3D Engine. (C) 2012-2022 Marat Sungatullin (aka graveman, aka mrsung)
//
// License: double license GPLv3 and zlib (see "Zv3DLicense.txt").
// 
// Purpose: error handling utils (impl).
/*
	23-Dec-2022	grv creation.
*/


#include "core/zvderror.h"
#include "core/zvdassert.h"
#include "core/zvdbyteutils.h"


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
ZvdPackedError::ZvdPackedError(ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt)
{ 
	Pack(m_retVal, nStatus, nSource, nCode, bExt);
}

//-----------------------------------------------------------------------------
void ZvdPackedError::Pack(ZvdRetVal& retVal, ZvdByte nStatus, ZvdByte nSource, ZvdUInt16 nCode, bool bExt)
{
	ZvdSetByte(retVal, 0, nStatus);
	ZvdSetByte(retVal, 1, (nSource & kZVD_E_SOURCEMASK) | (bExt ? kZVD_EF_EXTLIB : 0u));
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
	bExt = (nSource & kZVD_E_SOURCEMASKEXT) != 0u;
	return nSource & kZVD_E_SOURCEMASK;
}

//-----------------------------------------------------------------------------
ZvdUInt16 ZvdPackedError::Code() const
{
	return ZvdGetWord(m_retVal, 1);
}

//-----------------------------------------------------------------------------
ZvdPackedError ZvdPackedError::Ok()
{
	return ZvdPackedError(kZVD_B_OK, 0u, 0u);
}