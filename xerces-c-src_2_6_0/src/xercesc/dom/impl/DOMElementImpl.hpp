#ifndef DOMElementImpl_HEADER_GUARD_
#define DOMElementImpl_HEADER_GUARD_

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
 * $Id: DOMElementImpl.hpp,v 1.9 2004/09/20 15:00:50 amassari Exp $
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
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "DOMChildNode.hpp"
#include "DOMNodeImpl.hpp"
#include "DOMParentNode.hpp"

#include "DOMAttrMapImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN

class DOMTypeInfo;
class DOMNodeList;
class DOMAttrMapImpl;
class DOMDocument;




class CDOM_EXPORT DOMElementImpl: public DOMElement {
public:
    DOMNodeImpl       fNode;
    DOMParentNode     fParent;
    DOMChildNode      fChild;
    DOMAttrMapImpl    *fAttributes;
    DOMAttrMapImpl    *fDefaultAttributes;
    const XMLCh      *fName;

public:
    DOMElementImpl(DOMDocument *ownerDoc, const XMLCh *name);

    DOMElementImpl(const DOMElementImpl &other, bool deep=false);
    virtual ~DOMElementImpl();

    // Declare functions from DOMNode.  They all must be implemented by this class
    DOMNODE_FUNCTIONS;

    // Functions introduced on Element...
    virtual const XMLCh*      getAttribute(const XMLCh *name) const;
    virtual DOMAttr*          getAttributeNode(const XMLCh *name) const;
    virtual DOMNodeList*      getElementsByTagName(const XMLCh *tagname) const;
    virtual const XMLCh*      getTagName() const;
    virtual void              removeAttribute(const XMLCh *name);
    virtual DOMAttr*          removeAttributeNode(DOMAttr * oldAttr);
    virtual void              setAttribute(const XMLCh *name, const XMLCh *value);
    virtual DOMAttr*          setAttributeNode(DOMAttr *newAttr);
    virtual void              setReadOnly(bool readOnly, bool deep);

    //Introduced in DOM Level 2
    virtual const XMLCh*      getAttributeNS(const XMLCh *namespaceURI,
                                             const XMLCh *localName) const;
    virtual void              setAttributeNS(const XMLCh *namespaceURI,
                                             const XMLCh *qualifiedName,
                                             const XMLCh *value);
    virtual void              removeAttributeNS(const XMLCh *namespaceURI,
                                                const XMLCh *localName);
    virtual DOMAttr*          getAttributeNodeNS(const XMLCh *namespaceURI,
                                                 const XMLCh *localName) const;
    virtual DOMAttr*          setAttributeNodeNS(DOMAttr *newAttr);
    virtual DOMNodeList*      getElementsByTagNameNS(const XMLCh *namespaceURI,
                                                     const XMLCh *localName) const;
    virtual bool              hasAttribute(const XMLCh *name) const;
    virtual bool              hasAttributeNS(const XMLCh *namespaceURI,
                                             const XMLCh *localName) const;

    //Introduced in DOM level 3
    virtual void setIdAttribute(const XMLCh* name);
    virtual void setIdAttributeNS(const XMLCh* namespaceURI, const XMLCh* localName);
    virtual void setIdAttributeNode(const DOMAttr *idAttr);
    virtual const DOMTypeInfo * getTypeInfo() const;

    // for handling of default attribute
    virtual DOMAttr*          setDefaultAttributeNode(DOMAttr *newAttr);
    virtual DOMAttr*          setDefaultAttributeNodeNS(DOMAttr *newAttr);
    virtual DOMAttrMapImpl*   getDefaultAttributes() const;

    // helper function for DOM Level 3 renameNode
    virtual DOMNode* rename(const XMLCh* namespaceURI, const XMLCh* name);

protected:
    // default attribute helper functions
    virtual void setupDefaultAttributes();

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------    
    DOMElementImpl & operator = (const DOMElementImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif
