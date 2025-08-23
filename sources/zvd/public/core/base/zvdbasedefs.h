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
Purpose: base definitions.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_BASEDEFS_H
#define ZVD_BASEDEFS_H

#include "zvdconfig.h"

#ifndef __cplusplus
#error "This project is for C++ language only!"
#endif



//-----------------------------------------------------------------------------
// Compilers family detection

#include "core/base/zvdcompiler.h"

#if defined(ZVD_MSVC) 
#	ifdef _DEBUG
#		ifndef ZVD_DEBUG
#			define ZVD_DEBUG
#		endif
#	endif

#endif


#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <limits>


//-----------------------------------------------------------------------------
// OS detection

#if defined ZVD_COMPILER_GNUC
#	include "core/base/zvdplatformcheckgcc.h"

#elif defined ZVD_COMPILER_MSVC
#	include "core/base/zvdplatformcheckmsvc.h"

#endif      // eof if gnu C

#if defined(ZVD_PLATFORM_WIN64)
#   if !defined(ZVD_PLATFORM_WIN)
#       define ZVD_PLATFORM_WIN
#		define ZVD_OS_WINDOWS
#   endif

#endif

// Verifies that a supported platform is detected.
#if !defined(ZVD_PLATFORM_WIN64) && \
    !defined(ZVD_PLATFORM_LINUX)
#	error "For now windows and linux platforms are supported only."
#endif

#if defined(ZVD_PLATFORM_PS4) || defined(ZVD_PLATFORM_PS5) || defined(ZVD_PLATFORM_XBOX_SCARLETT)
#error "Isn't implemented yet"
#endif

//-----------------------------------------------------------------------------
// Endiannes
#if !defined (ZVD_BIG_ENDIAN) && !defined (ZVD_LITTLE_ENDIAN)
#	if defined (_MIPSEB) || defined (__sparc) || defined (_AIX) || \
	   defined (__hpux) || defined (macintosh) || defined (_MAC) || \
	   defined (_XBOX)
#		define ZVD_BIG_ENDIAN 1
#	elif defined (__i386) || defined (_M_IX86) || defined (_M_ARM) || \
         defined (__amd64__) || defined (_M_AMD64) || defined (__x86_64__) || \
         defined (__alpha__)
#		define ZVD_LITTLE_ENDIAN 1
#  elif defined (__ia64__)
	// itanium allows both settings - so, a seperate check is needed */
#		if defined (__BIG_ENDIAN__)
#			define ZVD_BIG_ENDIAN 1
#		else
#			define ZVD_LITTLE_ENDIAN 1
#		endif
#	else
#		error "endianness couldn't be determined"
#	endif
#endif /* ZVD_BIG_ENDIAN */

#if defined (ZVD_BIG_ENDIAN) && !defined (ZVD_LITTLE_ENDIAN)
#   error "big endian based platforms is not supported"
#endif

//-----------------------------------------------------------------------------
// API macros, Library type
#if defined(ZVD_OS_WINDOWS) || defined(ZVD_PLATFORM_XBOX_SCARLETT)

#ifdef ZVD_DLL_EXPORTS
#	define ZVD_API __declspec(dllexport)
#elif ZVD_DLL_IMPORTS
#	define ZVD_API __declspec(dllimport)
#else
// static library use this
#	define ZVD_API 
#endif

// Used for dll exporting and importing functions
#define  ZVD_DLL_EXPORTED_FUNCLIST_BEGIN	extern "C" { 
#define  ZVD_DLL_EXPORTED_FUNCLIST_END }

// Used for dll exporting and importing globals
#define  ZVD_DLL_GLOBAL_EXPORT	extern __declspec(dllexport) 
#define  ZVD_DLL_GLOBAL_IMPORT	extern __declspec(dllimport)

#elif defined ZVD_OS_LINUX

#ifdef ZVD_DLL_EXPORTS
#	define ZVD_API
#else
#	define ZVD_API
#endif

// Used for dll exporting and importing functions
#define  ZVD_DLL_EXPORTED_FUNCLIST_BEGIN	extern "C" { 
#define  ZVD_DLL_EXPORTED_FUNCLIST_END }  

// Used for dll exporting and importing globals
#define  ZVD_DLL_GLOBAL_EXPORT	extern
#define  ZVD_DLL_GLOBAL_IMPORT	extern 

#else

#error "Unsupported Platform."

#endif


// Used for standard calling conventions
#ifdef ZVD_OS_WINDOWS
#	define  ZVD_STDCALL			__stdcall
#	define	ZVD_CDECL			__cdecl
#	define  ZVD_FASTCALL		__fastcall
#	define  ZVD_FORCEINLINE		__forceinline	

#else
#	define  ZVD_STDCALL
#	define	ZVD_CDECL
#	define  ZVD_FASTCALL			   
#	define  ZVD_FORCEINLINE		   inline

#endif


//++++++++++++++++++++++++++
// Fixed size integers utils
//++++++++++++++++++++++++++

union ZvdU16U8Converter {
	ZvdU16U8Converter()
	{
		m_u16 = 0u;
	}
	uint16_t m_u16;
	uint8_t m_u8[2];
};

union ZvdU32U8Converter {
	ZvdU32U8Converter()
	{
		m_u32 = 0u;
	}
	uint32_t m_u32;
	uint8_t m_u8[4];
};

union ZvdU32U16Converter {
	ZvdU32U16Converter()
	{
		m_u32 = 0u;
	}
	uint32_t m_u32;
	uint16_t m_u16[2];
};

// Human readable convenient integers
//-----------------------------------
typedef uint8_t ZvdByte;
typedef uint16_t ZvdWord;
typedef uint32_t ZvdDword;

typedef int8_t ZvdSByte;
typedef int16_t ZvdSWord;
typedef int32_t ZvdSDword;

typedef uint32_t ZvdSize32;
typedef uint32_t ZvdUIndex32;
typedef int32_t ZvdIndex32;



//  ZVD_SIZE_MAX
const size_t kZVD_SIZE_MAX = std::numeric_limits<size_t>::max();

typedef size_t ZvdUIndex;
const ZvdUIndex kZVD_INVALID_INDEX = kZVD_SIZE_MAX;

const uint32_t kZVD_BAD_MARKER_U3 = 0x7;
const uint32_t kZVD_BAD_MARKER_U8 = 0xFF;
const uint32_t kZVD_BAD_MARKER_U16 = 0xFFFF;
const uint32_t kZVD_BAD_MARKER_U32 = 0xFFFFFFFF;

const uint32_t kZVD_ONE_U8 = 0x01;
const uint32_t kZVD_ONE_U32LE = 0x00000001;


inline bool ZvdIsLittleEndian()
{
	return ((*static_cast<const uint8_t*>(static_cast<const void*>(&kZVD_ONE_U32LE))) == kZVD_ONE_U8);
}

//++++++++++++++++++++++++++++++++++++
// Language standard dependent things
//++++++++++++++++++++++++++++++++++++




// Reals
typedef float ZvdReal32;
typedef double ZvdReal64;



//++++++++++++++++++
// Global constants
//++++++++++++++++++

//-----------------------------------------------------------------------------
// Boolean constants


const bool kZVD_TRUE = true;
const bool kZVD_FALSE = false;
const bool kZVD_YES = true;
const bool kZVD_NO = false;
const bool kZVD_ON = true;
const bool kZVD_OFF = false;

// Offset, align
//--------------
#define ZVD_TYPE_SIZE(nameOfType,padBytesCount) (sizeof(nameOfType) + (padBytesCount))
#define ZVD_DIV_TYPE_SIZE_INTO_ALIGN_MOD(nameOfType,padBytesCount,alignValue) \
(ZVD_TYPE_SIZE(nameOfType,(padBytesCount)) % (alignValue))

#define ZVD_TYPE_SIZE_TO_ALIGNED_DIFF(nameOfType,padBytesCount,alignValue) \
(alignValue - (\
ZVD_DIV_TYPE_SIZE_INTO_ALIGN_MOD(nameOfType,padBytesCount,alignValue) ? \
ZVD_DIV_TYPE_SIZE_INTO_ALIGN_MOD(nameOfType,padBytesCount,alignValue) : alignValue \
))

#define ZVD_ALIGNED_TYPE_SIZE(nameOfType,padBytesCount,alignValue) \
(ZVD_TYPE_SIZE(nameOfType,padBytesCount) + \
ZVD_TYPE_SIZE_TO_ALIGNED_DIFF(nameOfType,padBytesCount,alignValue))




struct ZvdsDefaultTag {};


typedef const char* ZvdCString;
typedef void* ZvdpVoid;
typedef const void* ZvdpCVoid;


/// The type of a data unit in C++ terms
enum ZvdeDataUnitType
{
    /// Invalid or unknown type.
    kZVD_DATAUNITTYPE_UNKNOWN = 0,

    /// Signed 8-bit integer (int8_t).
    kZVD_DATAUNITTYPE_INT8,

    /// Unsigned 8-bit integer (uint8_t).
    kZVD_DATAUNITTYPE_UINT8,

    /// Signed 16-bit integer (int16_t).
    kZVD_DATAUNITTYPE_INT16,

    /// Unsigned 16-bit integer (uint16_t).
    kZVD_DATAUNITTYPE_UINT16,

    /// Signed 32-bit integer (int32_t).
    kZVD_DATAUNITTYPE_INT32,

    /// Unsigned 32-bit integer (uint32_t).
    kZVD_DATAUNITTYPE_UINT32,


    /// Normalized signed 8-bit integer.
    kZVD_DATAUNITTYPE_INT8N,

    /// Normalized unsigned 8-bit integer.
    kZVD_DATAUNITTYPE_UINT8N,

    /// Normalized signed 16-bit integer.
    kZVD_DATAUNITTYPE_INT16N,

    /// Normalized unsigned 16-bit integer.
    kZVD_DATAUNITTYPE_UINT16N,

    /// Normalized signed 32-bit integer.
    kZVD_DATAUNITTYPE_INT32N,

    /// Normalized unsigned 32-bit integer.
    kZVD_DATAUNITTYPE_UINT32N,


    /// 16-bit floating point number (No mapping).
    kZVD_DATAUNITTYPE_REAL16,

    /// 32-bit floating point number (ZvdReal32).
    kZVD_DATAUNITTYPE_REAL32,

    /// 64-bit floating point number (ZvdReal64).
    kZVD_DATAUNITTYPE_REAL64,


    /// Normalized 16-bit floating point number.
    kZVD_DATAUNITTYPE_REAL16N,

    /// Normalized 32-bit floating point number.
    kZVD_DATAUNITTYPE_REAL32N,

    /// Normalized 64-bit floating point number.
    kZVD_DATAUNITTYPE_REAL64N,


    /// 8-bit character
    kZVD_DATAUNITTYPE_CHAR8,

    /// 16-bit character
    kZVD_DATAUNITTYPE_CHAR16,

    /// Signed 64-bit integer (int64_t).
    kZVD_DATAUNITTYPE_INT64,

    /// Unsigned 64-bit integer (uint64_t).
    kZVD_DATAUNITTYPE_UINT64,

    /// Predefined data unit type count.
    kZVD_DATAUNITTYPE_PREDEFINED_COUNT,

    /// User custom data unit types start.
    kZVD_DATAUNITTYPE_USER_FIRST,
    /// Max data unit types available.
    kZVD_DATAUNITTYPE_MAX = 0xFFF
};

#endif // ZVD_BASEDEFS_H