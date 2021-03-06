/*
 * Copyright 2003,2004 The Apache Software Foundation.
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
 * $Log: XSComplexTypeDefinition.cpp,v $
 * Revision 1.13  2004/09/08 13:56:08  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.12  2004/01/29 11:46:30  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.11  2003/12/24 17:42:02  knoaman
 * Misc. PSVI updates
 *
 * Revision 1.10  2003/12/19 15:09:47  knoaman
 * PSVI: process 'final' information
 *
 * Revision 1.9  2003/12/15 17:23:48  cargilld
 * psvi updates; cleanup revisits and bug fixes
 *
 * Revision 1.8  2003/11/27 16:42:00  neilg
 * fixes for segfaults and infinite loops in schema component model implementation; thanks to David Cargill
 *
 * Revision 1.7  2003/11/25 18:08:31  knoaman
 * Misc. PSVI updates. Thanks to David Cargill.
 *
 * Revision 1.6  2003/11/21 17:19:30  knoaman
 * PSVI update.
 *
 * Revision 1.5  2003/11/14 22:47:53  neilg
 * fix bogus log message from previous commit...
 *
 * Revision 1.4  2003/11/14 22:33:30  neilg
 * Second phase of schema component model implementation.  
 * Implement XSModel, XSNamespaceItem, and the plumbing necessary
 * to connect them to the other components.
 * Thanks to David Cargill.
 *
 * Revision 1.3  2003/11/10 21:56:54  neilg
 * make internal code use the new, stateless, method of traversing attribute lists
 *
 * Revision 1.2  2003/11/06 15:30:04  neilg
 * first part of PSVI/schema component model implementation, thanks to David Cargill.  This covers setting the PSVIHandler on parser objects, as well as implementing XSNotation, XSSimpleTypeDefinition, XSIDCDefinition, and most of XSWildcard, XSComplexTypeDefinition, XSElementDeclaration, XSAttributeDeclaration and XSAttributeUse.
 *
 * Revision 1.1  2003/09/16 14:33:36  neilg
 * PSVI/schema component model classes, with Makefile/configuration changes necessary to build them
 *
 */

#include <xercesc/framework/psvi/XSComplexTypeDefinition.hpp>
#include <xercesc/framework/psvi/XSWildcard.hpp>
#include <xercesc/framework/psvi/XSSimpleTypeDefinition.hpp>
#include <xercesc/framework/psvi/XSAttributeUse.hpp>
#include <xercesc/framework/psvi/XSModel.hpp>
#include <xercesc/framework/psvi/XSAnnotation.hpp>
#include <xercesc/framework/psvi/XSParticle.hpp>
#include <xercesc/validators/schema/ComplexTypeInfo.hpp>
#include <xercesc/validators/schema/SchemaElementDecl.hpp>
#include <xercesc/validators/schema/SchemaAttDefList.hpp>


XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  XSComplexTypeDefinition: Constructors and Destructor
// ---------------------------------------------------------------------------
XSComplexTypeDefinition::XSComplexTypeDefinition
(
    ComplexTypeInfo* const          complexTypeInfo
    , XSWildcard* const             xsWildcard
    , XSSimpleTypeDefinition* const xsSimpleType
    , XSAttributeUseList* const     xsAttList
    , XSTypeDefinition* const       xsBaseType
    , XSParticle* const             xsParticle
    , XSAnnotation* const           headAnnot
    , XSModel* const                xsModel
    , MemoryManager* const          manager
)
    : XSTypeDefinition(COMPLEX_TYPE, xsBaseType, xsModel, manager)
    , fComplexTypeInfo(complexTypeInfo)
    , fXSWildcard(xsWildcard)
    , fXSAttributeUseList(xsAttList)
    , fXSSimpleTypeDefinition(xsSimpleType)
    , fXSAnnotationList(0)
    , fParticle(xsParticle)
    , fProhibitedSubstitution(0)
{
    int blockset = fComplexTypeInfo->getBlockSet();
    if (blockset)
    {
        if (blockset & SchemaSymbols::XSD_EXTENSION)
            fProhibitedSubstitution |= XSConstants::DERIVATION_EXTENSION;

        if (blockset & SchemaSymbols::XSD_RESTRICTION)
            fProhibitedSubstitution |= XSConstants::DERIVATION_RESTRICTION;
    }

    int finalSet = fComplexTypeInfo->getFinalSet();
    if (finalSet)
    {
        if (finalSet & SchemaSymbols::XSD_EXTENSION)
            fFinal |= XSConstants::DERIVATION_EXTENSION;

        if (finalSet & SchemaSymbols::XSD_RESTRICTION)
            fFinal |= XSConstants::DERIVATION_RESTRICTION;
    }

    if (headAnnot)
    {
        fXSAnnotationList = new (manager) RefVectorOf<XSAnnotation>(1, false, manager);
        XSAnnotation* annot = headAnnot;

        do
        {
            fXSAnnotationList->addElement(annot);
            annot = annot->getNext();        
        } while (annot);
    }
}

XSComplexTypeDefinition::~XSComplexTypeDefinition() 
{
    // don't delete fXSWildcard - deleted by XSModel
    // don't delete fXSSimpleTypeDefinition - deleted by XSModel
    if (fXSAttributeUseList)
        delete fXSAttributeUseList;

    if (fXSAnnotationList)
        delete fXSAnnotationList;

    if (fParticle)
        delete fParticle;
}

// ---------------------------------------------------------------------------
//  XSComplexTypeDefinition: access methods
// ---------------------------------------------------------------------------
XSConstants::DERIVATION_TYPE XSComplexTypeDefinition::getDerivationMethod() const
{
    if(fComplexTypeInfo->getDerivedBy() == SchemaSymbols::XSD_EXTENSION)
        return XSConstants::DERIVATION_EXTENSION;    
    return XSConstants::DERIVATION_RESTRICTION;
}

bool XSComplexTypeDefinition::getAbstract() const
{
    return fComplexTypeInfo->getAbstract();
}


XSComplexTypeDefinition::CONTENT_TYPE XSComplexTypeDefinition::getContentType() const
{
    switch(fComplexTypeInfo->getContentType()) {
        case SchemaElementDecl::Simple:
            return CONTENTTYPE_SIMPLE;
        case SchemaElementDecl::Empty:
            return CONTENTTYPE_EMPTY;
        case SchemaElementDecl::Children:
            return CONTENTTYPE_ELEMENT;
        default:
            //case SchemaElementDecl::Mixed_Complex:
            //case SchemaElementDecl::Mixed_Simple:
            //case SchemaElementDecl::Any:
            return CONTENTTYPE_MIXED;
    }
}

bool XSComplexTypeDefinition::isProhibitedSubstitution(XSConstants::DERIVATION_TYPE toTest)                                                     
{
    if (fProhibitedSubstitution & toTest)
        return true;

    return false;
}

XSAnnotationList *XSComplexTypeDefinition::getAnnotations()
{    
    return fXSAnnotationList;
}

// ---------------------------------------------------------------------------
//  XSComplexTypeDefinition: virtual methods
// ---------------------------------------------------------------------------
const XMLCh *XSComplexTypeDefinition::getName() 
{
    return fComplexTypeInfo->getTypeLocalName();
}

const XMLCh *XSComplexTypeDefinition::getNamespace() 
{
    return fComplexTypeInfo->getTypeUri();
}

XSNamespaceItem *XSComplexTypeDefinition::getNamespaceItem() 
{
    return fXSModel->getNamespaceItem(getNamespace());
}

bool XSComplexTypeDefinition::getAnonymous() const
{
    return fComplexTypeInfo->getAnonymous(); 
}

XSTypeDefinition *XSComplexTypeDefinition::getBaseType() 
{
    return fBaseType;
}

bool XSComplexTypeDefinition::derivedFromType(const XSTypeDefinition * const ancestorType)
{
    if (!ancestorType)
        return false;

    XSTypeDefinition* type = this;

    while (type && (type != ancestorType))
    {
        type = type->getBaseType();
    }

    return (type == ancestorType);
}

XERCES_CPP_NAMESPACE_END
