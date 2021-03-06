/*
 * Copyright 2004 The Apache Software Foundation.
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
 * $Log: XSAXMLScanner.hpp,v $
 * Revision 1.1  2004/09/27 20:58:14  knoaman
 * A new scanner used by TraverseSchema to validate annotations contents
 *
 */


#if !defined(XSAXMLSCANNER_HPP)
#define XSAXMLSCANNER_HPP

#include <xercesc/internal/SGXMLScanner.hpp>


XERCES_CPP_NAMESPACE_BEGIN

//
//  This is a scanner class, which processes/validates contents of XML Schema
//  Annotations. It's intended for internal use only.
//
class XMLPARSER_EXPORT XSAXMLScanner : public SGXMLScanner
{
public :
    // -----------------------------------------------------------------------
    //  Destructor
    // -----------------------------------------------------------------------
    virtual ~XSAXMLScanner();

    // -----------------------------------------------------------------------
    //  XMLScanner public virtual methods
    // -----------------------------------------------------------------------
    virtual const XMLCh* getName() const;

protected:
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    /**
     * The grammar representing the XML Schema annotation (xsaGrammar) is
     * passed in by the caller. The scanner will own it and is responsible
     * for deleting it.
     */
    XSAXMLScanner
    (
        GrammarResolver* const grammarResolver
        , XMLStringPool* const   uriStringPool
        , SchemaGrammar* const   xsaGrammar
        , MemoryManager* const   manager = XMLPlatformUtils::fgMemoryManager
    );
    friend class TraverseSchema;

    // -----------------------------------------------------------------------
    //  XMLScanner virtual methods
    // -----------------------------------------------------------------------
    virtual void scanReset(const InputSource& src);

    // -----------------------------------------------------------------------
    //  SGXMLScanner virtual methods
    // -----------------------------------------------------------------------
    virtual bool scanStartTag(bool& gotData);
    virtual void scanEndTag(bool& gotData);

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSAXMLScanner();
    XSAXMLScanner(const XSAXMLScanner&);
    XSAXMLScanner& operator=(const XSAXMLScanner&);

    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    void scanRawAttrListforNameSpaces(int attCount);
    void switchGrammar(const XMLCh* const newGrammarNameSpace, bool laxValidate);
};

inline const XMLCh* XSAXMLScanner::getName() const
{
    return XMLUni::fgXSAXMLScanner;
}

XERCES_CPP_NAMESPACE_END

#endif
