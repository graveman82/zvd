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
