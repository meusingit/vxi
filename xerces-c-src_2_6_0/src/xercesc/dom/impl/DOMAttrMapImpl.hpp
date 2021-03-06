#ifndef DOMAttrMapImpl_HEADER_GUARD_
#define DOMAttrMapImpl_HEADER_GUARD_

/*
 * Copyright 2001-2002,2004 The Apache Software Foundation.
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
 * $Id: DOMAttrMapImpl.hpp,v 1.8 2004/09/08 13:55:51 peiyongz Exp $
 */

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class DOMNodeVector;
class DOMNode;

class CDOM_EXPORT DOMAttrMapImpl : public DOMNamedNodeMap
{
protected:
    DOMNodeVector*    fNodes;
    DOMNode*          fOwnerNode;       // the node this map belongs to

    virtual void	cloneContent(const DOMAttrMapImpl *srcmap);

    bool            readOnly();  // revisit.  Look at owner node read-only.

private:
    bool attrDefaults;

public:
    DOMAttrMapImpl(DOMNode *ownerNod);

    // revisit.  This "copy" constructor is used for cloning an Element with Attributes,
    //                and for setting up default attributes.  It's probably not right
    //                for one or the other or both.
    DOMAttrMapImpl(DOMNode *ownerNod, const DOMAttrMapImpl *defaults);
    DOMAttrMapImpl();

    virtual ~DOMAttrMapImpl();
    virtual DOMAttrMapImpl *cloneAttrMap(DOMNode *ownerNode);
    virtual bool hasDefaults();
    virtual void hasDefaults(bool value);
    virtual int             findNamePoint(const XMLCh *name) const;
    virtual int             findNamePoint(const XMLCh *namespaceURI,
	                                       const XMLCh *localName) const;
    virtual DOMNode*        removeNamedItemAt(XMLSize_t index);
    virtual void            setReadOnly(bool readOnly, bool deep);


    virtual XMLSize_t       getLength() const;
    virtual DOMNode*        item(XMLSize_t index) const;

    virtual DOMNode*        getNamedItem(const XMLCh *name) const;
    virtual DOMNode*        setNamedItem(DOMNode *arg);
    virtual DOMNode*        removeNamedItem(const XMLCh *name);
    
    virtual DOMNode*        getNamedItemNS(const XMLCh *namespaceURI,
	                                        const XMLCh *localName) const;
    virtual DOMNode*        setNamedItemNS(DOMNode *arg);
    virtual DOMNode*        removeNamedItemNS(const XMLCh *namespaceURI, const XMLCh *localName);

    void reconcileDefaultAttributes(const DOMAttrMapImpl* defaults);
    void moveSpecifiedAttributes(DOMAttrMapImpl* srcmap);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMAttrMapImpl(const DOMAttrMapImpl &);
    DOMAttrMapImpl & operator = (const DOMAttrMapImpl &);
};

// ---------------------------------------------------------------------------
//  DOMAttrMapImpl: Getters & Setters
// ---------------------------------------------------------------------------

inline bool DOMAttrMapImpl::hasDefaults()
{
    return attrDefaults;
}

inline void DOMAttrMapImpl::hasDefaults(bool value)
{
    attrDefaults = value;
}

XERCES_CPP_NAMESPACE_END


#endif
