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
Purpose: Zv3D engine definitions.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_ENGINE_H
#define ZVD_ENGINE_H

#include "core/base/zvderror.h"

class ZVD_API ZvdcEngine
{
public:
    /// Construct.
    explicit ZvdcEngine(/*context*/);
    /// Destroy. Cleanup all subsystems.
    ~ZvdcEngine();

    /** Initialize engine using parameters given.
    */ 
    ZvdRetVal Initialize(/*params*/);
    /** Engine competes its work. */
    ZvdRetVal Terminate();

    /// Run one tick (frame).
    ZvdRetVal Tick();
};

#endif // ZVD_ENGINE_H