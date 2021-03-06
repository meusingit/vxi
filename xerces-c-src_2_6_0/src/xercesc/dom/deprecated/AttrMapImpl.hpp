#ifndef AttrMapImpl_HEADER_GUARD_
#define AttrMapImpl_HEADER_GUARD_

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

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/deprecated/DOM.hpp> for the entire
//  DOM API, or DOM_*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

/*
 * $Id: AttrMapImpl.hpp,v 1.5 2004/09/08 13:55:42 peiyongz Exp $
 */

#include <xercesc/util/XercesDefs.hpp>
#include "AttrImpl.hpp"
#include "NodeImpl.hpp"
#include "NamedNodeMapImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class NamedNodeMapImpl;

class DEPRECATED_DOM_EXPORT AttrMapImpl : public NamedNodeMapImpl
{
private:
	bool attrDefaults;

public:
	AttrMapImpl(NodeImpl *ownerNod);
	AttrMapImpl(NodeImpl *ownerNod, NamedNodeMapImpl *defaults);
	virtual ~AttrMapImpl();
	virtual AttrMapImpl *cloneAttrMap(NodeImpl *ownerNode);
	virtual bool hasDefaults();
	virtual void hasDefaults(bool value);

    virtual NodeImpl *removeNamedItem(const DOMString &name);
    virtual NodeImpl *removeNamedItemNS(const DOMString &namespaceURI, const DOMString &localName);
};

// ---------------------------------------------------------------------------
//  AttrMapImpl: Getters & Setters
// ---------------------------------------------------------------------------

inline bool AttrMapImpl::hasDefaults()
{
	return attrDefaults;
}

inline void AttrMapImpl::hasDefaults(bool value)
{
	attrDefaults = value;
}


XERCES_CPP_NAMESPACE_END

#endif
