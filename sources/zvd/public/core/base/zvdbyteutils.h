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

#define ZVD_ENUM2U8(enumVal) ((uint8_t)(enumVal))
#define ZVD_ENUM2U32(enumVal) ((uint32_t)(enumVal))

#define ZVD_C_CAST_PTR_TO_INT(val,inttype) ((inttype*)&(val)) 
#define ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,inttype,offs) (((inttype*)&(val)) + offs)

//=== unsigned ================================================================
#ifdef ZVD_BIG_ENDIAN
/// High uint8_t (byte) in ZvdUint16 (word)
#	define ZVD_HIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,uint8_t))  
#else // LE
#	define ZVD_HIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint8_t,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low uint8_t (byte) in ZvdUint16 (word)
#	define ZVD_LOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint8_t,1))  
#else // LE
#	define ZVD_LOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,uint8_t)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High uint16_t (word) in uint32_t (dword)
#	define ZVD_HIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,uint16_t))  
#else // LE
#	define ZVD_HIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint16_t,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low uint16_t (word) in uint32_t (dword)
#	define ZVD_LOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint16_t,1))  
#else // LE
#	define ZVD_LOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,uint16_t)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High uint32_t (dword) in uint64_t (qword)
#	define ZVD_HIDWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,uint32_t))  
#else // LE
#	define ZVD_HIDWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUIn32,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low uint32_t (dword) in uint64_t (qword)
#	define ZVD_LODWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdUIn32,1)) 
#else // LE
#	define ZVD_LODWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,uint32_t))  
#endif


#ifdef ZVD_BIG_ENDIAN
/// n-th uint8_t (byte) in type
#	define ZVD_BYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint8_t,sizeof(t) - (n + 1)))
#else // LE
#	define ZVD_BYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint8_t,n))
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
/// n-th uint16_t (word) in type
#	define ZVD_WORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint16_t,sizeof(t)/sizeof(uint16_t) - (n + 1)))
#else // LE
#	define ZVD_WORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,uint16_t,n))
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
/// High int8_t (signed byte) in 2-byte sized type
#	define ZVD_SHIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,int8_t))  
#else // LE
#	define ZVD_SHIBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int8_t,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low int8_t (byte) in 2-byte sized type
#	define ZVD_SLOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int8_t,1))  
#else // LE
#	define ZVD_SLOBYTE(val)		(*ZVD_C_CAST_PTR_TO_INT(val,int8_t)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High int16_t (signed word) in 4-byte sized type
#	define ZVD_SHIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,int16_t))  
#else // LE
#	define ZVD_SHIWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int16_t,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low int16_t (signed word) in 4-byte sized type
#	define ZVD_SLOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int16_t,1))  
#else // LE
#	define ZVD_SLOWORD(val)		(*ZVD_C_CAST_PTR_TO_INT(val,int16_t)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// High int32_t (signed dword) in 8-byte sized type
#	define ZVD_SHIDWORD(val)	(*ZVD_C_CAST_PTR_TO_INT(val,int32_t))  
#else // LE
#	define ZVD_SHIDWORD(val)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdIn32,1)) 
#endif

#ifdef ZVD_BIG_ENDIAN
/// Low int32_t (signed dword) in 8-byte sized type
#	define ZVD_SLODWORD(val)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,ZvdIn32,1)) 
#else // LE
#	define ZVD_SLODWORD(val)	(*ZVD_C_CAST_PTR_TO_INT(val,int32_t))  
#endif


#ifdef ZVD_BIG_ENDIAN
/// n-th int8_t (signed byte) in type
#	define ZVD_SBYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int8_t,sizeof(t) - (n + 1)))
#else // LE
#	define ZVD_SBYTEn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int8_t,n))
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
/// n-th int16_t (signed word) in type
#	define ZVD_SWORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int16_t,sizeof(t)/sizeof(int16_t) - (n + 1)))
#else // LE
#	define ZVD_SWORDn(val, t, n)	(*ZVD_C_CAST_PTR_TO_INT_AND_OFFSET(val,int16_t,n))
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
inline uint8_t ZvdGetByte(uint32_t v, size_t idx)
{
	ZvdU32U8Converter conv = {};
	conv.m_u32 = v;

	return ZvdIsLittleEndian() ? conv.m_u8[idx] : conv.m_u8[3 - idx];
}

inline void ZvdSetByte(uint32_t& v, size_t idx, uint8_t val)
{
	ZvdU32U8Converter conv = {};
	conv.m_u32 = v;

	if (ZvdIsLittleEndian())
		conv.m_u8[idx] = val;
	else
		conv.m_u8[3 - idx] = val;
	v = conv.m_u32;
}

inline uint16_t ZvdGetWord(uint32_t v, size_t idx)
{
	ZvdU32U16Converter conv = {};
	conv.m_u32 = v;

	return ZvdIsLittleEndian() ? conv.m_u16[idx] : conv.m_u16[1 - idx];
}

inline void ZvdSetWord(uint32_t& v, size_t idx, uint16_t val)
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

	ZvdByte get(size_t byteIndex) const
	{
		return m_pData[byteIndex];
	}

	ZvdByte& get(size_t byteIndex)
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
		m_pData = reinterpret_cast<uint16_t*>(&value);
	}

	uint16_t get(size_t wordIndex) const
	{
		return m_pData[wordIndex];
	}

	uint16_t& get(size_t wordIndex)
	{
		return m_pData[wordIndex];
	}

private:
	uint16_t* m_pData{};
};
#endif // ZVD_BYTEUTILS_H
