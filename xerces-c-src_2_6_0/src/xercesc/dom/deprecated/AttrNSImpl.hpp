#ifndef AttrNSImpl_HEADER_GUARD_
#define AttrNSImpl_HEADER_GUARD_

/*
 * Copyright 1999-2002,2004 The Apache Software Foundation.
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
 * $Id: AttrNSImpl.hpp,v 1.5 2004/09/08 13:55:42 peiyongz Exp $
 */

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/deprecated/DOM.hpp> for the entire
//  DOM API, or DOM_*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//


#include "AttrImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN



class DEPRECATED_DOM_EXPORT AttrNSImpl: public AttrImpl {
protected:
    //Introduced in DOM Level 2
    DOMString namespaceURI;     //namespace URI of this node
    DOMString localName;        //local part of qualified name


public:
    AttrNSImpl(DocumentImpl *ownerDoc, const DOMString &name);
    AttrNSImpl(DocumentImpl *ownerDoc, //DOM Level 2
	const DOMString &namespaceURI, const DOMString &qualifiedName);
    AttrNSImpl(const AttrNSImpl &other, bool deep=false);

    virtual NodeImpl * cloneNode(bool deep);
    //Introduced in DOM Level 2
    virtual DOMString	getNamespaceURI();
    virtual DOMString   getPrefix();
    virtual DOMString   getLocalName();
    virtual void        setPrefix(const DOMString &prefix);
};

XERCES_CPP_NAMESPACE_END

#endif
