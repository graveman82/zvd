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
Purpose: this file declares ZvdñObject - the root class of Zv3D's object model that provides:
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
#include "core/system/memory/zvdmemflags.h"




// Forward declaration of the base class for Zv3D objects. 
class ZVD_API ZvdcObject;

/** @brief Type alias for a raw pointer to a ZvdcObject. */
typedef ZvdcObject* ZvdcpObject;
typedef const ZvdcObject* ZvdcpkObject;



/** @brief Class for storing metadata about classes in the ZvdcObject hierarchy, 
managing object creation, deletion, and cloning.
 */
class ZVD_API ZvdcClass
{
public:
    /** @brief Function pointer type for creating a new instance of an object.
 *  @param memFlags Memory allocation flags specifying how the object should be allocated.
 *  @return A pointer to the newly created object, or nullptr on failure.
 */
    typedef ZvdcpObject(ZVD_STDCALL* ZvdfptCreateInstance)(ZvdcMemFlags memFlags);

    /** @brief Function pointer type for deleting an object instance.
     *  @param pObject Pointer to the object to be deleted.
     */
    typedef void (ZVD_STDCALL* ZvdfptDeleteInstance)(ZvdcpObject pObject);

    /** @brief Function pointer type for cloning an existing object instance.
     *  @param pObject Pointer to the source object to be cloned.
     *  @return A pointer to the cloned object, or nullptr on failure.
     */
    typedef ZvdcpObject(ZVD_STDCALL* ZvdfptCloneInstance)(ZvdcpkObject pObject);

    /** @brief Constructs a ZvdcClass with metadata and function pointers for object management.
     *  @param pClassName Name of the class as a null-terminated string.
     *  @param pCreateInstance Function pointer to create a new instance.
     *  @param pDeleteInstance Function pointer to delete an instance.
     *  @param pCloneInstance Function pointer to clone an instance.
     */
    ZvdcClass(ZvdCString pClassName,
        ZvdfptCreateInstance pCreateInstance,
        ZvdfptDeleteInstance pDeleteInstance,
        ZvdfptCloneInstance pCloneInstance) ZVD_NOEXCEPT;

    /** @brief Creates a new instance of the associated class.
     *  @param memFlags Memory allocation flags.
     *  @return Pointer to the created object, or nullptr if creation fails.
     */
    ZvdcpObject CreateInstance(ZvdcMemFlags memFlags) const ZVD_NOEXCEPT;

    /** @brief Deletes an instance of the associated class.
     *  @param pObject Pointer to the object to delete.
     */
    void DeleteInstance(ZvdcpObject pObject) const ZVD_NOEXCEPT;

    /** @brief Clones an existing instance of the associated class.
     *  @param pObject Pointer to the source object to clone.
     *  @return Pointer to the cloned object, or nullptr if cloning fails.
     */
    ZvdcpObject CloneInstance(ZvdcpkObject pObject) const ZVD_NOEXCEPT;

    /** @brief Gets the name of the associated class.
     *  @return The class name as a null-terminated string.
     */
    ZvdCString GetClassName() const ZVD_NOEXCEPT
    {
        return m_pClassName;
    }

private:
    ZvdCString m_pClassName;
    ZvdfptCreateInstance m_pCreateInstance;
    ZvdfptDeleteInstance m_pDeleteInstance;
    ZvdfptCloneInstance m_pCloneInstance;
};


#endif // ZVD_OBJECT_H