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


#if defined(ZVD_HAS_STDINT_H_FILE)
#	include <cstdint>
#endif

#include <cstddef>

//-----------------------------------------------------------------------------
// OS detection

#if defined ZVD_COMPILER_GNUC
#	include "core/base/zvdplatformcheckgcc.h"

#elif defined ZVD_COMPILER_MSVC
#	include "core/base/zvdplatformcheckmsvc.h"

#endif      // eof if gnu C

#if defined(ZVD_PLATFORM_WIN32) || defined(ZVD_PLATFORM_WIN64)
#   if !defined(ZVD_PLATFORM_WIN)
#       define ZVD_PLATFORM_WIN
#		define ZVD_OS_WINDOWS
#   endif

#endif

// Verifies that a supported platform is detected.
#if !defined(ZVD_PLATFORM_WIN32) && \
    !defined(ZVD_PLATFORM_WIN64) && \
    !defined(ZVD_PLATFORM_LINUX)
#	error "For now windows and linux platforms are supported only."
#endif

#if defined(ZVD_PLATFORM_PS3)
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

//-----------------------------------------------------------------------------
// API macros, Library type
#if defined(ZVD_OS_WINDOWS) || defined(ZVD_PLATFORM_XBOX360)

#ifdef ZVD_DLL_EXPORTS
#	define ZVD_API __declspec(dllexport)
#else
#	define ZVD_API __declspec(dllimport)
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
	#define  ZVD_STDCALL			__stdcall
	#define  ZVD_FASTCALL			__fastcall
	#define  ZVD_FORCEINLINE		__forceinline	
#else
	#define  ZVD_STDCALL
	#define  ZVD_FASTCALL			   
	#define  ZVD_FORCEINLINE		   inline
#endif


// fixed size integers
//---------------------
#if defined(ZVD_HAS_STDINT_H_FILE)
typedef int8_t ZvdInt8;
typedef int16_t ZvdInt16;
typedef int32_t ZvdInt32;

typedef uint8_t ZvdUInt8;
typedef uint16_t ZvdUInt16;
typedef uint32_t ZvdUInt32;

#	if defined(ZVD_ARCH_X64)
typedef int64_t ZvdInt64;
typedef uint64_t ZvdUInt64;
#	endif

#elif defined(ZVD_MSVC)
typedef __int8 ZvdInt8;
typedef __int16 ZvdInt16;
typedef __int32 ZvdInt32;

typedef unsigned __int8 ZvdUInt8;
typedef unsigned __int16 ZvdUInt16;
typedef unsigned __int32 ZvdUInt32;

#	if defined(ZVD_ARCH_X64) // Нужен ли этот макрос здесь?
typedef __int64 ZvdInt64;
typedef unsigned __int64 ZvdUInt64;
#	endif

#else

typedef signed char ZvdInt8;
typedef short ZvdInt16;
typedef int ZvdInt32;

typedef unsigned char ZvdUInt8;
typedef unsigned short ZvdUInt16;
typedef unsigned int ZvdUInt32;

#	if defined(ZVD_ARCH_X64)
typedef long long ZvdInt64;
typedef unsigned long long ZvdUInt64;
#	endif

#endif // fixed size integers

//++++++++++++++++++++++++++
// Fixed size integers utils
//++++++++++++++++++++++++++

union ZvdU16U8Converter {
	ZvdU16U8Converter()
	{
		m_u16 = 0u;
	}
	ZvdUInt16 m_u16;
	ZvdUInt8 m_u8[2];
};

union ZvdU32U8Converter {
	ZvdU32U8Converter()
	{
		m_u32 = 0u;
	}
	ZvdUInt32 m_u32;
	ZvdUInt8 m_u8[4];
};

union ZvdU32U16Converter {
	ZvdU32U16Converter()
	{
		m_u32 = 0u;
	}
	ZvdUInt32 m_u32;
	ZvdUInt16 m_u16[2];
};

// Human readable convenient integers
//-----------------------------------
typedef ZvdUInt8 ZvdByte;
typedef ZvdUInt16 ZvdWord;
typedef ZvdUInt32 ZvdDword;

typedef ZvdInt8 ZvdSByte;
typedef ZvdInt16 ZvdSWord;
typedef ZvdInt32 ZvdSDword;

typedef ZvdUInt32 ZvdSize32;
typedef ZvdUInt32 ZvdUIndex32;
typedef ZvdInt32 ZvdIndex32;

#ifdef ZVD_HAS_STD_DEFS
typedef size_t ZvdSize;
typedef ptrdiff_t ZvdPtrDiff;
typedef intptr_t ZvdIntPtr;
#else
#	if defined(ZVD_ARCH_X64)
		typedef ZvdUInt64 ZvdSize;
		typedef ZvdInt64 ZvdPtrDiff;
		typedef ZvdInt64 ZvdIntPtr;

#	elif defined(ZVD_ARCH_X86)
		typedef ZvdUInt32 ZvdSize;
		typedef ZvdInt32 ZvdPtrDiff;
		typedef ZvdInt32 ZvdIntPtr;

#	else
		typedef ZvdUInt16 ZvdSize;
		typedef ZvdInt16 ZvdPtrDiff;
		typedef ZvdInt16 ZvdIntPtr;

#	endif // arch

#endif

typedef ZvdSize ZvdUIndex;

const ZvdUInt32 kZVD_BAD_MARKER_U3 = 0x7;
const ZvdUInt32 kZVD_BAD_MARKER_U8 = 0xFF;
const ZvdUInt32 kZVD_BAD_MARKER_U16 = 0xFFFF;
const ZvdUInt32 kZVD_BAD_MARKER_U32 = 0xFFFFFFFF;

const ZvdUInt32 kZVD_ONE_U8 = 0x01;
const ZvdUInt32 kZVD_ONE_U32LE = 0x00000001;


inline bool ZvdIsLittleEndian()
{
	return ((*static_cast<const ZvdUInt8*>(static_cast<const void*>(&kZVD_ONE_U32LE))) == kZVD_ONE_U8);
}

//++++++++++++++++++++++++++++++++++++
// Language standard dependent things
//++++++++++++++++++++++++++++++++++++
#ifdef ZVD_CPP11 
#	define kZVD_NULLPTR(argType) nullptr
#	define kZVD_NULLFPTR(argType) nullptr
#	define kZVD_NULLVOID nullptr
#	define kZVD_NULLCSTR nullptr
#else
#	define kZVD_NULLPTR(argType) ((argType*)0)
#	define kZVD_NULLFPTR(argType) ((argType)0)
#	define kZVD_NULLVOID ((void*)0)
#	define kZVD_NULLCSTR ((const char*)0)
#endif



// Reals
typedef float ZvdReal32;
typedef double ZvdReal64;



//++++++++++++++++++
// Global constants
//++++++++++++++++++

//-----------------------------------------------------------------------------
// Boolean constants

// cpp lang
const bool			kZVD_TRUE = true;
const bool			kZVD_FALSE = false;

const bool			kZVD_YES = kZVD_TRUE;
const bool			kZVD_NO = kZVD_FALSE;

// as integers
const ZvdUInt32	kZVD_TRUE_U32 = 1;
const ZvdUInt32	kZVD_FALSE_U32 = 0;

const ZvdUInt8		kZVD_TRUE_U8 = 1;
const ZvdUInt8		kZVD_FALSE_U8 = 0;

// yes/no answer constants
const ZvdUInt32	kZVD_YES_U32 = kZVD_TRUE_U32;
const ZvdUInt32	kZVD_NO_U32 = kZVD_FALSE_U32;

const ZvdUInt8		kZVD_YES_U8 = kZVD_TRUE_U8;
const ZvdUInt8		kZVD_NO_U8 = kZVD_FALSE_U8;




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


// cpp standard >= 11 feauters
//----------------------------

#ifdef ZVD_CPP11
#	define ZVD_METHOD_OVERRIDE override
#else
#	define ZVD_METHOD_OVERRIDE
#endif


struct ZvdsDefaultTag {};




#endif // ZVD_BASEDEFS_H