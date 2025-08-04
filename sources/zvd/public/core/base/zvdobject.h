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
Purpose: this file declares ZvdObject - the root class of Zv3D's object model that provides:
  - core runtime type information (RTTI)
  - object lifecycle management
  - hierarchical ownership
  - serialization infrastructure
 
  All complex engine entities should inherit from this class.
  Simple data containers (vectors, matrices, etc.) should use standalone structs.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_OBJECT_H
#define ZVD_OBJECT_H

#include "core/base/zvdbasedefs.h"

/**
 * @brief Base class for all Zv3D engine objects with runtime behavior or complex structure.
 *
 * ZvdObject serves as the root class for all entities that:
 * - Require dynamic memory management
 * - Participate in the object hierarchy
 * - Need RTTI (Run-Time Type Information)
 * - Support serialization/deserialization
 *
 * @note Simple data containers (vectors, matrices) should NOT inherit from this class.
 */

class ZVD_API ZvdObject
{

};

#endif // ZVD_OBJECT_H