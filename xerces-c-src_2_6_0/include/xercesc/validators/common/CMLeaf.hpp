/*
 * Copyright 1999-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Log: CMLeaf.hpp,v $
 * Revision 1.8  2004/09/08 13:56:51  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.7  2004/01/29 11:51:21  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.6  2003/05/30 16:11:45  gareth
 * Fixes so we compile under VC7.1. Patch by Alberto Massari.
 *
 * Revision 1.5  2003/05/18 14:02:06  knoaman
 * Memory manager implementation: pass per instance manager.
 *
 * Revision 1.4  2003/05/16 21:43:20  knoaman
 * Memory manager implementation: Modify constructors to pass in the memory manager.
 *
 * Revision 1.3  2003/05/15 18:48:27  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.2  2002/11/04 14:54:58  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:37  peiyongz
 * sane_include
 *
 * Revision 1.6  2001/12/06 17:52:17  tng
 * Performance Enhancement.  The QName that was passed to the CMLeaf
 * constructor was always being copied, even though the CMLeaf objects
 * only existed during construction of a DFA.  In most cases the original
 * QName that was passed into the CMLeaf constructor continued to exist long
 * after the CMLeaf was destroyed; in some cases the QName was constructed
 * specifically to be passed to the CMLeaf constructor.  Added a second CMLeaf constructor that indicated the QName passed in was to be adopted; otherwise the CMLeaf constructor just sets a reference to the QName passed in.
 * By Henry Zongaro.
 *
 * Revision 1.5  2001/10/03 15:08:45  tng
 * typo fix: remove the extra space which may confuse some compilers while constructing the qname.
 *
 * Revision 1.4  2001/05/11 13:27:16  tng
 * Copyright update.
 *
 * Revision 1.3  2001/04/19 18:17:27  tng
 * Schema: SchemaValidator update, and use QName in Content Model
 *
 * Revision 1.2  2001/02/16 14:58:57  tng
 * Schema: Update Makefile, configure files, project files, and include path in
 * certain cpp files because of the move of the common Content Model files.  By Pei Yong Zhang.
 *
 * Revision 1.1  2001/02/16 14:17:29  tng
 * Schema: Move the common Content Model files that are shared by DTD
 * and schema from 'DTD' folder to 'common' folder.  By Pei Yong Zhang.
 *
 * Revision 1.5  2000/03/28 19:43:25  roddey
 * Fixes for signed/unsigned warnings. New work for two way transcoding
 * stuff.
 *
 * Revision 1.4  2000/03/02 19:55:37  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.3  2000/02/24 20:16:47  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.2  2000/02/09 21:42:36  abagchi
 * Copyright swat
 *
 * Revision 1.1.1.1  1999/11/09 01:03:04  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:45:36  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

#if !defined(CMLEAF_HPP)
#define CMLEAF_HPP

#include <xercesc/validators/common/CMNode.hpp>


XERCES_CPP_NAMESPACE_BEGIN

//
//  This class represents a leaf in the content spec node tree of an
//  element's content model. It just has an element qname and a position value,
//  the latter of which is used during the building of a DFA.
//
class CMLeaf : public CMNode
{
public :
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    CMLeaf
    (
          QName* const         element
        , const unsigned int   position = (~0)
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    CMLeaf
    (
          QName* const         element
        , const unsigned int   position
        , const bool           adopt
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    ~CMLeaf();


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    QName* getElement();
    const QName* getElement() const;
    unsigned int getPosition() const;


    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setPosition(const unsigned int newPosition);


    // -----------------------------------------------------------------------
    //  Implementation of public CMNode virtual interface
    // -----------------------------------------------------------------------
    bool isNullable() const;


protected :
    // -----------------------------------------------------------------------
    //  Implementation of protected CMNode virtual interface
    // -----------------------------------------------------------------------
    void calcFirstPos(CMStateSet& toSet) const;
    void calcLastPos(CMStateSet& toSet) const;


private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fElement
    //      This is the element that this leaf represents.
    //
    //  fPosition
    //      Part of the algorithm to convert a regex directly to a DFA
    //      numbers each leaf sequentially. If its -1, that means its an
    //      epsilon node. All others are non-epsilon positions.
    //
    //  fAdopt
    //      This node is responsible for the storage of the fElement QName.
    // -----------------------------------------------------------------------
    QName*          fElement;
    unsigned int    fPosition;
    bool            fAdopt;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CMLeaf(const CMLeaf&);
    CMLeaf& operator=(const CMLeaf&);
};


// -----------------------------------------------------------------------
//  Constructors
// -----------------------------------------------------------------------
inline CMLeaf::CMLeaf(       QName* const         element
                     , const unsigned int         position
                     ,       MemoryManager* const manager) :
    CMNode(ContentSpecNode::Leaf, manager)
    , fElement(0)
    , fPosition(position)
    , fAdopt(false)
{
    if (!element)
    {
        fElement = new (fMemoryManager) QName
        (
              XMLUni::fgZeroLenString
            , XMLUni::fgZeroLenString
            , XMLElementDecl::fgInvalidElemId
            , fMemoryManager
        );
        // We have to be responsible for this QName - override default fAdopt
        fAdopt = true;
    }
    else
    {
        fElement = element;
    }
}

inline CMLeaf::CMLeaf(       QName* const         element
                     , const unsigned int         position
                     , const bool                 adopt
                     ,       MemoryManager* const manager) :
    CMNode(ContentSpecNode::Leaf, manager)
    , fElement(0)
    , fPosition(position)
    , fAdopt(adopt)
{
    if (!element)
    {
        fElement = new (fMemoryManager) QName
        (
              XMLUni::fgZeroLenString
            , XMLUni::fgZeroLenString
            , XMLElementDecl::fgInvalidElemId
            , fMemoryManager
        );
        // We have to be responsible for this QName - override adopt parameter
        fAdopt = true;
    }
    else
    {
        fElement = element;
    }
}

inline CMLeaf::~CMLeaf()
{
    if (fAdopt)
        delete fElement;
}


// ---------------------------------------------------------------------------
//  Getter methods
// ---------------------------------------------------------------------------
inline QName* CMLeaf::getElement()
{
    return fElement;
}

inline const QName* CMLeaf::getElement() const
{
    return fElement;
}

inline unsigned int CMLeaf::getPosition() const
{
    return fPosition;
}


// ---------------------------------------------------------------------------
//  Setter methods
// ---------------------------------------------------------------------------
inline void CMLeaf::setPosition(const unsigned int newPosition)
{
    fPosition = newPosition;
}


// ---------------------------------------------------------------------------
//  Implementation of public CMNode virtual interface
// ---------------------------------------------------------------------------
inline bool CMLeaf::isNullable() const
{
    // Leaf nodes are never nullable unless its an epsilon node
    return (fPosition == -1);
}


// ---------------------------------------------------------------------------
//  Implementation of protected CMNode virtual interface
// ---------------------------------------------------------------------------
inline void CMLeaf::calcFirstPos(CMStateSet& toSet) const
{
    // If we are an epsilon node, then the first pos is an empty set
    if (fPosition == -1)
    {
        toSet.zeroBits();
        return;
    }

    // Otherwise, its just the one bit of our position
    toSet.setBit(fPosition);
}

inline void CMLeaf::calcLastPos(CMStateSet& toSet) const
{
    // If we are an epsilon node, then the last pos is an empty set
    if (fPosition == -1)
    {
        toSet.zeroBits();
        return;
    }

    // Otherwise, its just the one bit of our position
    toSet.setBit(fPosition);
}

XERCES_CPP_NAMESPACE_END

#endif
