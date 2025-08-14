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
Purpose: linked list node.

----------------------
 For developers notes
----------------------

*/

#ifndef ZVD_LISTNODE_H
#define ZVD_LISTNODE_H


#include "core/base/zvdassert.h"


class ZvdcListNode;
typedef ZvdcListNode* ZvdcpListNode;
typedef ZvdcListNode** ZvdcppListNode;
typedef const ZvdcpListNode ZvdcCpListNode;
typedef const ZvdcListNode* ZvdcpCListNode;

class ZvdcListNode
{
	friend class ZvdcList;
public:
  
	ZvdcListNode();
    ZvdcListNode(ZvdpVoid pUserData);
    /// Gets the next node in the list
    ZvdcpListNode GetNext() const;
    void SetNext(ZvdcpListNode pNode);
    /// Gets the previous node in the list
    ZvdcpListNode GetPrev() const;
    void SetPrev(ZvdcpListNode pNode);

    /// checks if node is linked into a list
    ZvdBool IsLinked() const;

    /// links this node before candidate node into linked list
    void LinkBeforeNodeInList(ZvdcpListNode pNodeInList);
    /// links this node after candidate node into linked list
    void LinkAfterNodeInList(ZvdcpListNode pNodeInList);
    /// unlinks node from the list
    void UnlinkFromList();
private:
    ZvdcpListNode m_pNext;
    ZvdcpListNode m_pPrev;
    ZvdpVoid m_pUserData;
};

//-----------------------------------------------------------------------------
/**
*/
inline
ZvdcListNode::ZvdcListNode()
	: m_pNext(kZVD_NULLPTR(ZvdcListNode))
	, m_pPrev(kZVD_NULLPTR(ZvdcListNode))
	, m_pUserData(kZVD_NULLVOID)
{
	
}

//-----------------------------------------------------------------------------
/**
*/
inline
ZvdcListNode::ZvdcListNode(ZvdpVoid pUserData)
    : m_pNext(kZVD_NULLPTR(ZvdcListNode))
    , m_pPrev(kZVD_NULLPTR(ZvdcListNode))
    , m_pUserData(pUserData)
{
    
}

//-----------------------------------------------------------------------------
/**
    Gets the node after this node in the linled list. 

    @return the next node or null if there is no next node.
*/
inline
ZvdcpListNode
ZvdcListNode::GetNext() const
{
    ZVD_ASSERT_HIGH(this->m_pNext, "Tail marker node - forbidden!");
    if (this->m_pNext->m_pNext)
        return this->m_pNext;
    else
        return kZVD_NULLPTR(ZvdcListNode); // last node
}

//-----------------------------------------------------------------------------
/**
    Sets the node after this node in the linled list.

*/
inline
void
ZvdcListNode::SetNext(ZvdcpListNode pNode)
{
    this->m_pNext = pNode;
}

//-----------------------------------------------------------------------------
/**
    Gets the node before this node in the linked list.

    @return the previous node or null if there is no previous node.
*/
inline
ZvdcpListNode
ZvdcListNode::GetPrev() const
{
    ZVD_ASSERT_HIGH(this->m_pPrev, "Head marker node - forbidden!");
    if (this->m_pPrev->m_pPrev)
        return this->m_pPrev;
    else
        return kZVD_NULLPTR(ZvdcListNode); // first node
}

//-----------------------------------------------------------------------------
/**
    Sets the node before this node in the linled list.

*/
inline
void
ZvdcListNode::SetPrev(ZvdcpListNode pNode)
{
    this->m_pPrev = pNode;
}

//-----------------------------------------------------------------------------
/**
    @param pNodeInList node before which this node should be inserted
*/
inline
void
ZvdcListNode::LinkBeforeNodeInList(ZvdcpListNode pNodeInList)
{
    ZVD_ASSERT_HIGH(pNodeInList->GetPrev(), "candidate node must be linked to list");
    ZVD_ASSERT_HIGH(!this->GetNext(), "already in list");
    this->m_pPrev = pNodeInList->GetPrev();
    this->m_pNext = pNodeInList;
    this->m_pPrev->SetNext(this);
    pNodeInList->SetPrev(this);
}

//-----------------------------------------------------------------------------
/**
    @param pNodeInList node after which this node should be inserted
*/
inline
void
ZvdcListNode::LinkAfterNodeInList(ZvdcpListNode pNodeInList)
{
    ZVD_ASSERT_HIGH(pNodeInList->GetNext(), "candidate node must be linked to list");
    ZVD_ASSERT_HIGH(!this->GetPrev(), "already in list");
    this->m_pPrev = pNodeInList;
    this->m_pNext = pNodeInList->GetNext();
    pNodeInList->SetNext(this);
    this->m_pNext->SetPrev(this);
}

//-----------------------------------------------------------------------------
/**
*/
inline
void
ZvdcListNode::UnlinkFromList()
{
    ZVD_ASSERT_HIGH(this->GetPrev(), "must be linked in list - invalid prev field");
    ZVD_ASSERT_HIGH(this->GetNext(), "must be linked in list - invalid next field");
    this->m_pNext->SetPrev(this->GetPrev());
    this->m_pPrev->SetNext(this->GetNext());
    this->m_pNext = kZVD_NULLPTR(ZvdcListNode);
    this->m_pPrev = kZVD_NULLPTR(ZvdcListNode);;
}



//-----------------------------------------------------------------------------
/**
    @return true if node is linked into a list
*/
inline
ZvdBool
ZvdcListNode::IsLinked() const
{
    return (m_pNext != kZVD_NULLPTR(ZvdcListNode) &&
        m_pPrev != kZVD_NULLPTR(ZvdcListNode));
}
#endif // ZVD_LISTNODE_H