#ifndef DOMTextImpl_HEADER_GUARD_
#define DOMTextImpl_HEADER_GUARD_

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
 * $Id: DOMTextImpl.hpp,v 1.7 2004/09/08 13:55:52 peiyongz Exp $
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
#include <xercesc/dom/DOMText.hpp>

#include "DOMChildNode.hpp"
#include "DOMNodeImpl.hpp"
#include "DOMCharacterDataImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


class CDOM_EXPORT DOMTextImpl: public DOMText {
public:
    DOMNodeImpl             fNode;
    DOMChildNode            fChild;
    DOMCharacterDataImpl    fCharacterData;

public:
    DOMTextImpl(DOMDocument* ownerDoc, const XMLCh* data);
    DOMTextImpl(const DOMTextImpl& other, bool deep=false);

    virtual                ~DOMTextImpl();
    virtual DOMText*        splitText(XMLSize_t offset);
    // DOM Level 3
    virtual bool            getIsWhitespaceInElementContent() const;
    virtual const XMLCh*    getWholeText();
    virtual DOMText*        replaceWholeText(const XMLCh* content);

    // non-standard extension
    virtual bool            isIgnorableWhitespace() const;

    // Declare the functions coming from DOMNode.
    DOMNODE_FUNCTIONS;


    // All of the functions coming from DOMCharacterData
    virtual const XMLCh*    getData() const;
    virtual XMLSize_t       getLength() const;
    virtual const XMLCh*    substringData(XMLSize_t offset,
                                          XMLSize_t count) const;
    virtual void            appendData(const XMLCh *arg);
    virtual void            insertData(XMLSize_t offset, const  XMLCh *arg);
    virtual void            deleteData(XMLSize_t offset,
                                       XMLSize_t count);
    virtual void            replaceData(XMLSize_t offset,
                                        XMLSize_t count,
                                        const XMLCh *arg);
    virtual void            setData(const XMLCh *data);

protected:
    virtual void            setIgnorableWhitespace(bool ignorable);
    friend class            AbstractDOMParser;

private:
    // -----------------------------------------------------------------------
    // Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DOMTextImpl & operator = (const DOMTextImpl &);
};

XERCES_CPP_NAMESPACE_END

#endif

