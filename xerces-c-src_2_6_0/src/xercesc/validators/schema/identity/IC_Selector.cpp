/*
 * Copyright 2001,2004 The Apache Software Foundation.
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
 * $Log: IC_Selector.cpp,v $
 * Revision 1.7  2004/09/08 13:56:59  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.6  2003/10/14 15:24:23  peiyongz
 * Implementation of Serialization/Deserialization
 *
 * Revision 1.5  2003/05/15 18:59:34  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.4  2003/01/13 16:30:19  knoaman
 * [Bug 14469] Validator doesn't enforce xsd:key.
 *
 * Revision 1.3  2002/11/04 14:47:41  tng
 * C++ Namespace Support.
 *
 * Revision 1.2  2002/08/27 05:56:19  knoaman
 * Identity Constraint: handle case of recursive elements.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:50  peiyongz
 * sane_include
 *
 * Revision 1.3  2001/11/23 18:35:33  tng
 * Eliminate Warning from AIX xlC 3.6:1540-399: (W) "XMLAttr" is undefined.  The delete operator will not call a destructor.
 *
 * Revision 1.2  2001/11/15 17:10:19  knoaman
 * Particle derivation checking support.
 *
 * Revision 1.1  2001/11/02 14:08:40  knoaman
 * Add support for identity constraints.
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/framework/XMLAttr.hpp>
#include <xercesc/validators/schema/identity/IC_Selector.hpp>
#include <xercesc/validators/schema/identity/XercesXPath.hpp>
#include <xercesc/validators/schema/identity/IdentityConstraint.hpp>
#include <xercesc/validators/schema/identity/FieldActivator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  SelectorMatcher: Constructors and Destructor
// ---------------------------------------------------------------------------
SelectorMatcher::SelectorMatcher(XercesXPath* const xpath,
                                 IC_Selector* const selector,
                                 FieldActivator* const fieldActivator,
                                 const int initialDepth,
                                 MemoryManager* const manager)
    : XPathMatcher(xpath, selector->getIdentityConstraint(), manager)
    , fInitialDepth(initialDepth)
    , fElementDepth(0)
    , fMatchedDepth(-1)
    , fSelector(selector)
    , fFieldActivator(fieldActivator)
{
}

// ---------------------------------------------------------------------------
//  FieldMatcher: XMLDocumentHandler methods
// ---------------------------------------------------------------------------
void SelectorMatcher::startDocumentFragment() {

    XPathMatcher::startDocumentFragment();
    fElementDepth = 0;
    fMatchedDepth = -1;
}

void SelectorMatcher::startElement(const XMLElementDecl& elemDecl,
                                   const unsigned int urlId,
                                   const XMLCh* const elemPrefix,
                                   const RefVectorOf<XMLAttr>& attrList,
                                   const unsigned int attrCount) {

    XPathMatcher::startElement(elemDecl, urlId, elemPrefix, attrList, attrCount);
    fElementDepth++;

    // activate the fields, if selector is matched
    int matched = isMatched();
    if ((fMatchedDepth == -1 && ((matched & XP_MATCHED) == XP_MATCHED))
        || ((matched & XP_MATCHED_D) == XP_MATCHED_D)) {

        IdentityConstraint* ic = fSelector->getIdentityConstraint();
        int count = ic->getFieldCount();

        fMatchedDepth = fElementDepth;
        fFieldActivator->startValueScopeFor(ic, fInitialDepth);

        for (int i = 0; i < count; i++) {

            XPathMatcher* matcher = fFieldActivator->activateField(ic->getFieldAt(i), fInitialDepth);
            matcher->startElement(elemDecl, urlId, elemPrefix, attrList, attrCount);
        }
    }
}

void SelectorMatcher::endElement(const XMLElementDecl& elemDecl,
                                 const XMLCh* const elemContent) {

    XPathMatcher::endElement(elemDecl, elemContent);

    if (fElementDepth-- == fMatchedDepth) {

        fMatchedDepth = -1;
        fFieldActivator->endValueScopeFor(fSelector->getIdentityConstraint(), fInitialDepth);
    }
}

// ---------------------------------------------------------------------------
//  IC_Selector: Constructors and Destructor
// ---------------------------------------------------------------------------
IC_Selector::IC_Selector(XercesXPath* const xpath,
                         IdentityConstraint* const identityConstraint)
    : fXPath(xpath)
    , fIdentityConstraint(identityConstraint)
{
}


IC_Selector::~IC_Selector()
{
    delete fXPath;
}

// ---------------------------------------------------------------------------
//  IC_Selector: operators
// ---------------------------------------------------------------------------
bool IC_Selector::operator ==(const IC_Selector& other) const {

    return (*fXPath == *(other.fXPath));
}

bool IC_Selector::operator !=(const IC_Selector& other) const {

    return !operator==(other);
}

// ---------------------------------------------------------------------------
//  IC_Selector: Factory methods
// ---------------------------------------------------------------------------
XPathMatcher* IC_Selector::createMatcher(FieldActivator* const fieldActivator,
                                         const int initialDepth,
                                         MemoryManager* const manager) {

    return new (manager) SelectorMatcher(fXPath, this, fieldActivator, initialDepth, manager);
}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_TOCREATE(IC_Selector)

void IC_Selector::serialize(XSerializeEngine& serEng)
{
    if (serEng.isStoring())
    {
        serEng<<fXPath;
        
        IdentityConstraint::storeIC(serEng, fIdentityConstraint);
    }
    else
    {
        serEng>>fXPath;

        fIdentityConstraint = IdentityConstraint::loadIC(serEng);
    }

}

IC_Selector::IC_Selector(MemoryManager* const )
:fXPath(0)
,fIdentityConstraint(0)
{
}

XERCES_CPP_NAMESPACE_END

/**
  * End of file IC_Selector.cpp
  */

