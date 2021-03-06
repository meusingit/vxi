#ifndef DOMCDATASectionImpl_HEADER_GUARD_
#define DOMCDATASectionImpl_HEADER_GUARD_
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
 * $Id: DOMCDATASectionImpl.hpp,v 1.8 2004/09/08 13:55:51 peiyongz Exp $
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
#include <xercesc/dom/DOMCDATASection.hpp>
#include "DOMNodeImpl.hpp"
#include "DOMChildNode.hpp"
#include "DOMParentNode.hpp"
#include "DOMCharacterDataImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMCDATASectionImpl: public DOMCDATASection {
private:
    DOMNodeImpl           fNode;
    DOMParentNode         fParent;
    DOMChildNode          fChild;
    DOMCharacterDataImpl  fCharacterData;


public:
    DOMCDATASectionImpl(DOMDocument *ownerDoc, const XMLCh * data);
    DOMCDATASectionImpl(const DOMCDATASectionImpl &other, bool deep = false);

    virtual             ~DOMCDATASectionImpl();

    // Functions inherited from TEXT
    virtual DOMText*     splitText(XMLSize_t offset);
    // DOM Level 3
    virtual bool            getIsWhitespaceInElementContent() const;
    virtual const XMLCh*    getWholeText();
    virtual DOMText*        replaceWholeText(const XMLCh* content);

    // non-standard extension
    virtual bool         isIgnorableWhitespace() const;


    // Declare all of the functions from DOMNode.
    DOMNODE_FUNCTIONS;


    // Functions introduced by DOMCharacterData
    virtual const XMLCh* getData() const;
    virtual XMLSize_t    getLength() const;
    virtual const XMLCh* substringData(XMLSize_t offset,
                                       XMLSize_t count) const;
    virtual void         appendData(const XMLCh *arg);
    virtual void         insertData(XMLSize_t offset, const  XMLCh *arg);
    virtual void         deleteData(XMLSize_t offset,
                                    XMLSize_t count);
    virtual void         replaceData(XMLSize_t offset,
                                     XMLSize_t count,
                                     const XMLCh *arg);
    virtual void         setData(const XMLCh *data);

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMCDATASectionImpl & operator = (const DOMCDATASectionImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif

