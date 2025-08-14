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
Purpose: blank file for headers.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_DATAUNIT_H
#define ZVD_DATAUNIT_H

#include "core/base/zvdmemorymanageable.h"


class ZvdcDataUnitFormat
{
public:
    enum FormatEncoding
    {
        /// Data unit type code offset. 
        kFE_CODE_OFFSET = 0,
        /// Data unit type code mask. Bits 0-11.
        kFE_CODE_MASK = 0x00000FFF,

        /// Data unit size (in bytes) offset. 
        kFE_SIZE_OFFSET = 12,
        /// Data unit size (in bytes) mask. Bits 12-23.
        kFE_SIZE_MASK = 0x00FFF000,

        /// Data unit count offset. 
        kFE_COUNT_OFFSET = 24,
        /// Data unit count mask. Bits 24-31.
        kFE_COUNT_MASK = 0xFF000000
    };

#define ZVD_MAKE_DATA_UNIT_FORMAT(nCode, nSize, nCount) \
    (((nCode << kFE_CODE_OFFSET) & kFE_CODE_MASK) | \
     ((nSize << kFE_SIZE_OFFSET) & kFE_SIZE_MASK) | \
     ((nCount << kFE_COUNT_OFFSET) & kFE_COUNT_MASK))


    enum PredefinedFormats
    {
        kF_UNKNOWN      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UNKNOWN, 0, 0),

        // 8-bit integers
        kF_INT8_1       = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8, 1, 1),
        kF_INT8_2       = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8, 1, 2),
        kF_INT8_3       = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8, 1, 3),
        kF_INT8_4       = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8, 1, 4),

        kF_UINT8_1      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8, 1, 1),
        kF_UINT8_2      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8, 1, 2),
        kF_UINT8_3      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8, 1, 3),
        kF_UINT8_4      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8, 1, 4),

        
        kF_INT8N_1      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8N, 1, 1),
        kF_INT8N_2      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8N, 1, 2),
        kF_INT8N_3      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8N, 1, 3),
        kF_INT8N_4      = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT8N, 1, 4),

        kF_UINT8N_1     = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8N, 1, 1),
        kF_UINT8N_2     = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8N, 1, 2),
        kF_UINT8N_3     = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8N, 1, 3),
        kF_UINT8N_4     = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT8N, 1, 4),

        // 16-bit integers
        kF_INT16_1 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16, 1, 1),
        kF_INT16_2 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16, 1, 2),
        kF_INT16_3 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16, 1, 3),
        kF_INT16_4 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16, 1, 4),

        kF_UINT16_1 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16, 1, 1),
        kF_UINT16_2 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16, 1, 2),
        kF_UINT16_3 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16, 1, 3),
        kF_UINT16_4 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16, 1, 4),


        kF_INT16N_1 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16N, 1, 1),
        kF_INT16N_2 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16N, 1, 2),
        kF_INT16N_3 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16N, 1, 3),
        kF_INT16N_4 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_INT16N, 1, 4),

        kF_UINT16N_1 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16N, 1, 1),
        kF_UINT16N_2 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16N, 1, 2),
        kF_UINT16N_3 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16N, 1, 3),
        kF_UINT16N_4 = ZVD_MAKE_DATA_UNIT_FORMAT(kZVD_DATAUNITTYPE_UINT16N, 1, 4),
    };

private:
    ZvdUInt32 m_nFormat;
};


class ZvdcDataUnit : public ZvdcMemoryManageable
{
public:

};

#endif // ZVD_DATAUNIT_H