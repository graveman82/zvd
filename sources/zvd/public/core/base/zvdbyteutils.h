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
Purpose: byte utilities.

----------------------
 For developers notes
----------------------

*/
#ifndef ZVD_BYTEUTILS_H
#define ZVD_BYTEUTILS_H



#include "core/base/zvdbasedefs.h"


//++++++++++++++++++
// Byte utils
//++++++++++++++++++

#define ZVD_ENUM2U8(enumVal) ((ZvdUInt8)(enumVal))
#define ZVD_ENUM2U32(enumVal) ((ZvdUInt32)(enumVal))

#define ZVD_C_CAST_PTR_TO_INT(val,inttype) ((inttype*)&(val)) 
#define ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,inttype,offs) (((inttype*)&(val)) + offs)

//=== unsigned ================================================================
#ifdef ZVD_BIG_ENDIAN
/// High ZvdUInt8 (byte) in ZvdUint16 (word)
#	define ZVD_HIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdUInt8))  
#else // LE
#	define ZVD_HIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt8,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low ZvdUInt8 (byte) in ZvdUint16 (word)
#	define ZVD_LOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt8,1))  
#else // LE
#	define ZVD_LOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdUInt8)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High ZvdUInt16 (word) in ZvdUInt32 (dword)
#	define ZVD_HIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdUInt16))  
#else // LE
#	define ZVD_HIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt16,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low ZvdUInt16 (word) in ZvdUInt32 (dword)
#	define ZVD_LOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt16,1))  
#else // LE
#	define ZVD_LOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdUInt16)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High ZvdUInt32 (dword) in ZvdUInt64 (qword)
#	define ZVD_HIDWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdUInt32))  
#else // LE
#	define ZVD_HIDWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUIn32,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low ZvdUInt32 (dword) in ZvdUInt64 (qword)
#	define ZVD_LODWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUIn32,1)) 
#else // LE
#	define ZVD_LODWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdUInt32))  
#endif


#ifdef ZVD_BIG_ENDIAN
/// n-th ZvdUInt8 (byte) in type
#	define ZVD_BYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt8,sizeof(t) - (n + 1)))
#else // LE
#	define ZVD_BYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt8,n))
#endif
	
#define ZVD_BYTE0(val, t)   ZVD_BYTEn(val, t,  0)
#define ZVD_BYTE1(val, t)   ZVD_BYTEn(val, t,  1)
#define ZVD_BYTE2(val, t)   ZVD_BYTEn(val, t,  2)
#define ZVD_BYTE3(val, t)   ZVD_BYTEn(val, t,  3)
#define ZVD_BYTE4(val, t)   ZVD_BYTEn(val, t,  4)
#define ZVD_BYTE5(val, t)   ZVD_BYTEn(val, t,  5)
#define ZVD_BYTE6(val, t)   ZVD_BYTEn(val, t,  6)
#define ZVD_BYTE7(val, t)   ZVD_BYTEn(val, t,  7)
#define ZVD_BYTE8(val, t)   ZVD_BYTEn(val, t,  8)
#define ZVD_BYTE9(val, t)   ZVD_BYTEn(val, t,  9)
#define ZVD_BYTE10(val, t)  ZVD_BYTEn(val, t, 10)
#define ZVD_BYTE11(val, t)  ZVD_BYTEn(val, t, 11)
#define ZVD_BYTE12(val, t)  ZVD_BYTEn(val, t, 12)
#define ZVD_BYTE13(val, t)  ZVD_BYTEn(val, t, 13)
#define ZVD_BYTE14(val, t)  ZVD_BYTEn(val, t, 14)
#define ZVD_BYTE15(val, t)  ZVD_BYTEn(val, t, 15)


#ifdef ZVD_BIG_ENDIAN
/// n-th ZvdUInt16 (word) in type
#	define ZVD_WORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt16,sizeof(t)/sizeof(ZvdUInt16) - (n + 1)))
#else // LE
#	define ZVD_WORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUInt16,n))
#endif

#define ZVD_WORD0(val, t)   ZVD_WORDn(val, t,  0)
#define ZVD_WORD1(val, t)   ZVD_WORDn(val, t,  1)
#define ZVD_WORD2(val, t)   ZVD_WORDn(val, t,  2)
#define ZVD_WORD3(val, t)   ZVD_WORDn(val, t,  3)
#define ZVD_WORD4(val, t)   ZVD_WORDn(val, t,  4)
#define ZVD_WORD5(val, t)   ZVD_WORDn(val, t,  5)
#define ZVD_WORD6(val, t)   ZVD_WORDn(val, t,  6)
#define ZVD_WORD7(val, t)   ZVD_WORDn(val, t,  7)


//===== signed ================================================================
#ifdef ZVD_BIG_ENDIAN
/// High ZvdInt8 (signed byte) in 2-byte sized type
#	define ZVD_SHIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdInt8))  
#else // LE
#	define ZVD_SHIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt8,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low ZvdInt8 (byte) in 2-byte sized type
#	define ZVD_SLOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt8,1))  
#else // LE
#	define ZVD_SLOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdInt8)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High ZvdInt16 (signed word) in 4-byte sized type
#	define ZVD_SHIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdInt16))  
#else // LE
#	define ZVD_SHIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt16,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low ZvdInt16 (signed word) in 4-byte sized type
#	define ZVD_SLOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt16,1))  
#else // LE
#	define ZVD_SLOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,ZvdInt16)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High ZvdInt32 (signed dword) in 8-byte sized type
#	define ZVD_SHIDWORD(val)	(*ZVD_C_CAST_PTR_TO_INT(val,ZvdInt32))  
#else // LE
#	define ZVD_SHIDWORD(val)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdIn32,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low ZvdInt32 (signed dword) in 8-byte sized type
#	define ZVD_SLODWORD(val)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdIn32,1)) 
#else // LE
#	define ZVD_SLODWORD(val)	(*ZVD_C_CAST_PTR_TO_INT(val,ZvdInt32))  
#endif


#ifdef ZVD_BIG_ENDIAN
/// n-th ZvdInt8 (signed byte) in type
#	define ZVD_SBYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt8,sizeof(t) - (n + 1)))
#else // LE
#	define ZVD_SBYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt8,n))
#endif

#define ZVD_SBYTE0(val, t)   ZVD_SBYTEn(val, t,  0)
#define ZVD_SBYTE1(val, t)   ZVD_SBYTEn(val, t,  1)
#define ZVD_SBYTE2(val, t)   ZVD_SBYTEn(val, t,  2)
#define ZVD_SBYTE3(val, t)   ZVD_SBYTEn(val, t,  3)
#define ZVD_SBYTE4(val, t)   ZVD_SBYTEn(val, t,  4)
#define ZVD_SBYTE5(val, t)   ZVD_SBYTEn(val, t,  5)
#define ZVD_SBYTE6(val, t)   ZVD_SBYTEn(val, t,  6)
#define ZVD_SBYTE7(val, t)   ZVD_SBYTEn(val, t,  7)
#define ZVD_SBYTE8(val, t)   ZVD_SBYTEn(val, t,  8)
#define ZVD_SBYTE9(val, t)   ZVD_SBYTEn(val, t,  9)
#define ZVD_SBYTE10(val, t)  ZVD_SBYTEn(val, t, 10)
#define ZVD_SBYTE11(val, t)  ZVD_SBYTEn(val, t, 11)
#define ZVD_SBYTE12(val, t)  ZVD_SBYTEn(val, t, 12)
#define ZVD_SBYTE13(val, t)  ZVD_SBYTEn(val, t, 13)
#define ZVD_SBYTE14(val, t)  ZVD_SBYTEn(val, t, 14)
#define ZVD_SBYTE15(val, t)  ZVD_SBYTEn(val, t, 15)


#ifdef ZVD_BIG_ENDIAN
/// n-th ZvdInt16 (signed word) in type
#	define ZVD_SWORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt16,sizeof(t)/sizeof(ZvdInt16) - (n + 1)))
#else // LE
#	define ZVD_SWORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdInt16,n))
#endif

#define ZVD_SWORD0(val, t)   ZVD_SWORDn(val, t,  0)
#define ZVD_SWORD1(val, t)   ZVD_SWORDn(val, t,  1)
#define ZVD_SWORD2(val, t)   ZVD_SWORDn(val, t,  2)
#define ZVD_SWORD3(val, t)   ZVD_SWORDn(val, t,  3)
#define ZVD_SWORD4(val, t)   ZVD_SWORDn(val, t,  4)
#define ZVD_SWORD5(val, t)   ZVD_SWORDn(val, t,  5)
#define ZVD_SWORD6(val, t)   ZVD_SWORDn(val, t,  6)
#define ZVD_SWORD7(val, t)   ZVD_SWORDn(val, t,  7)

//== functions ================================================================
//
inline ZvdUInt8 ZvdGetByte(ZvdUInt32 v, ZvdSize idx)
{
	ZvdU32U8Converter conv = {};
	conv.m_u32 = v;

	return ZvdIsLittleEndian() ? conv.m_u8[idx] : conv.m_u8[3 - idx];
}

inline void ZvdSetByte(ZvdUInt32& v, ZvdSize idx, ZvdUInt8 val)
{
	ZvdU32U8Converter conv = {};
	conv.m_u32 = v;

	if (ZvdIsLittleEndian())
		conv.m_u8[idx] = val;
	else
		conv.m_u8[3 - idx] = val;
	v = conv.m_u32;
}

inline ZvdUInt16 ZvdGetWord(ZvdUInt32 v, ZvdSize idx)
{
	ZvdU32U16Converter conv = {};
	conv.m_u32 = v;

	return ZvdIsLittleEndian() ? conv.m_u16[idx] : conv.m_u16[1 - idx];
}

inline void ZvdSetWord(ZvdUInt32& v, ZvdSize idx, ZvdUInt16 val)
{
	ZvdU32U16Converter conv;
	conv.m_u32 = v;

	if (ZvdIsLittleEndian())
		conv.m_u16[idx] = val;
	else
		conv.m_u16[1 - idx] = val;
	v = conv.m_u32;
}



template <typename T>
class ZvdByteModifier
{
public:
	ZvdByteModifier(T& value)
	{
		m_pData = reinterpret_cast<ZvdByte*>(&value);
	}

	ZvdByte get(ZvdSize byteIndex) const
	{
		return m_pData[byteIndex];
	}

	ZvdByte& get(ZvdSize byteIndex)
	{
		return m_pData[byteIndex];
	}

private:
	ZvdByte* m_pData{};
};

template <typename T>
class ZvdWordModifier
{
public:
	ZvdWordModifier(T& value)
	{
		m_pData = reinterpret_cast<ZvdUInt16*>(&value);
	}

	ZvdUInt16 get(ZvdSize wordIndex) const
	{
		return m_pData[wordIndex];
	}

	ZvdUInt16& get(ZvdSize wordIndex)
	{
		return m_pData[wordIndex];
	}

private:
	ZvdUInt16* m_pData{};
};
#endif // ZVD_BYTEUTILS_H
