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
 * $Log: AllContentModel.cpp,v $
 * Revision 1.10  2004/09/16 13:32:03  amassari
 * Updated error message for UPA to also state the complex type that is failing the test
 *
 * Revision 1.9  2004/09/08 13:56:51  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.8  2004/01/29 11:51:21  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.7  2003/12/17 00:18:38  cargilld
 * Update to memory management so that the static memory manager (one used to call Initialize) is only for static data.
 *
 * Revision 1.6  2003/11/20 18:09:18  knoaman
 * Store a copy of each child, instead of a reference, as the content spec node
 * tree is not guaranteed to be persistent.
 *
 * Revision 1.5  2003/05/18 14:02:06  knoaman
 * Memory manager implementation: pass per instance manager.
 *
 * Revision 1.4  2003/05/15 18:48:27  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.3  2002/11/04 14:54:58  tng
 * C++ Namespace Support.
 *
 * Revision 1.2  2002/09/24 19:48:39  tng
 * Performance: use XMLString::equals instead of XMLString::compareString
 *
 * Revision 1.1.1.1  2002/02/01 22:22:37  peiyongz
 * sane_include
 *
 * Revision 1.3  2001/11/21 14:30:13  knoaman
 * Fix for UPA checking.
 *
 * Revision 1.2  2001/08/27 12:19:00  tng
 * Schema: AllContentModel UPA Check typo fix
 *
 * Revision 1.1  2001/08/24 12:48:48  tng
 * Schema: AllContentModel
 *
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/RuntimeException.hpp>
#include <xercesc/framework/XMLElementDecl.hpp>
#include <xercesc/framework/XMLValidator.hpp>
#include <xercesc/validators/common/ContentSpecNode.hpp>
#include <xercesc/validators/common/AllContentModel.hpp>
#include <xercesc/validators/schema/SubstitutionGroupComparator.hpp>
#include <xercesc/validators/schema/XercesElementWildcard.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  AllContentModel: Constructors and Destructor
// ---------------------------------------------------------------------------
AllContentModel::AllContentModel( ContentSpecNode* const parentContentSpec
                                , const bool             isMixed
                                , MemoryManager* const   manager) :
   fMemoryManager(manager)
 , fCount(0)
 , fChildren(0)
 , fChildOptional(0)
 , fNumRequired(0)
 , fIsMixed(isMixed)
{
    //
    //  Create a vector of unsigned ints that will be filled in with the
    //  ids of the child nodes. It will be expanded as needed but we give
    //  it an initial capacity of 64 which should be more than enough for
    //  99% of the scenarios.
    //

    ValueVectorOf<QName*> children(64, fMemoryManager);
    ValueVectorOf<bool> childOptional(64, fMemoryManager);

    //
    //  Get the parent element's content spec. This is the head of the tree
    //  of nodes that describes the content model. We will iterate this
    //  tree.
    //
    ContentSpecNode* curNode = parentContentSpec;
    if (!curNode)
        ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::CM_NoParentCSN, fMemoryManager);

    // And now call the private recursive method that iterates the tree
    buildChildList(curNode, children, childOptional);

    //
    //  And now we know how many elements we need in our member list. So
    //  fill them in.
    //
    fCount = children.size();
    fChildren = (QName**) fMemoryManager->allocate(fCount * sizeof(QName*)); //new QName*[fCount];
    fChildOptional = (bool*) fMemoryManager->allocate(fCount * sizeof(bool)); //new bool[fCount];
    for (unsigned int index = 0; index < fCount; index++) {
        fChildren[index] = new (fMemoryManager) QName(*(children.elementAt(index)));
        fChildOptional[index] = childOptional.elementAt(index);
    }
}

AllContentModel::~AllContentModel()
{
    for (unsigned int index = 0; index < fCount; index++)
        delete fChildren[index];
    fMemoryManager->deallocate(fChildren); //delete [] fChildren;
    fMemoryManager->deallocate(fChildOptional); //delete [] fChildOptional;
}

// ---------------------------------------------------------------------------
//  AllContentModel: Implementation of the ContentModel virtual interface
// ---------------------------------------------------------------------------
//
//Under the XML Schema mixed model,
//the order and number of child elements appearing in an instance
//must agree with
//the order and number of child elements specified in the model.
//
int
AllContentModel::validateContent( QName** const         children
                                , const unsigned int    childCount
                                , const unsigned int) const
{
    // If <all> had minOccurs of zero and there are
    // no children to validate, trivially validate
    if (!fNumRequired && !childCount)
        return -1;

    // Check for duplicate element
    bool* elementSeen = (bool*) fMemoryManager->allocate(fCount*sizeof(bool)); //new bool[fCount];

    // initialize the array
    for (unsigned int i = 0; i < fCount; i++)
        elementSeen[i] = false;

    // keep track of the required element seen
    unsigned int numRequiredSeen = 0;

    for (unsigned int outIndex = 0; outIndex < childCount; outIndex++) {
        // Get the current child out of the source index
        const QName* curChild = children[outIndex];

        // If its PCDATA, then we just accept that
        if (fIsMixed && curChild->getURI() == XMLElementDecl::fgPCDataElemId)
            continue;

        // And try to find it in our list
        unsigned int inIndex = 0;
        for (; inIndex < fCount; inIndex++)
        {
            const QName* inChild = fChildren[inIndex];
            if ((inChild->getURI() == curChild->getURI()) &&
                (XMLString::equals(inChild->getLocalPart(), curChild->getLocalPart()))) {
                // found it
                // If this element was seen already, indicate an error was
                // found at the duplicate index.
                if (elementSeen[inIndex]) {
                    fMemoryManager->deallocate(elementSeen); //delete [] elementSeen;
                    return outIndex;
                }
                else
                    elementSeen[inIndex] = true;

                if (!fChildOptional[inIndex])
                    numRequiredSeen++;

                break;
            }
        }

        // We did not find this one, so the validation failed
        if (inIndex == fCount) {
            fMemoryManager->deallocate(elementSeen); //delete [] elementSeen;
            return outIndex;
        }

    }

    fMemoryManager->deallocate(elementSeen); //delete [] elementSeen;

    // Were all the required elements of the <all> encountered?
    if (numRequiredSeen != fNumRequired) {
        return childCount;
    }

    // Everything seems to be ok, so return success
    // success
    return -1;
}


int AllContentModel::validateContentSpecial(QName** const           children
                                          , const unsigned int      childCount
                                          , const unsigned int
                                          , GrammarResolver*  const pGrammarResolver
                                          , XMLStringPool*    const pStringPool) const
{

    SubstitutionGroupComparator comparator(pGrammarResolver, pStringPool);

    // If <all> had minOccurs of zero and there are
    // no children to validate, trivially validate
    if (!fNumRequired && !childCount)
        return -1;

    // Check for duplicate element
    bool* elementSeen = (bool*) fMemoryManager->allocate(fCount*sizeof(bool)); //new bool[fCount];

    // initialize the array
    for (unsigned int i = 0; i < fCount; i++)
        elementSeen[i] = false;

    // keep track of the required element seen
    unsigned int numRequiredSeen = 0;

    for (unsigned int outIndex = 0; outIndex < childCount; outIndex++) {
        // Get the current child out of the source index
        QName* const curChild = children[outIndex];

        // If its PCDATA, then we just accept that
        if (fIsMixed && curChild->getURI() == XMLElementDecl::fgPCDataElemId)
            continue;

        // And try to find it in our list
        unsigned int inIndex = 0;
        for (; inIndex < fCount; inIndex++)
        {
            QName* const inChild = fChildren[inIndex];
            if ( comparator.isEquivalentTo(curChild, inChild)) {
                // match
                // If this element was seen already, indicate an error was
                // found at the duplicate index.
                if (elementSeen[inIndex]) {
                    fMemoryManager->deallocate(elementSeen); //delete [] elementSeen;
                    return outIndex;
                }
                else
                    elementSeen[inIndex] = true;

                if (!fChildOptional[inIndex])
                    numRequiredSeen++;

                break;
            }
        }

        // We did not find this one, so the validation failed
        if (inIndex == fCount) {
            fMemoryManager->deallocate(elementSeen); //delete [] elementSeen;
            return outIndex;
        }

    }

    fMemoryManager->deallocate(elementSeen); //delete [] elementSeen;

    // Were all the required elements of the <all> encountered?
    if (numRequiredSeen != fNumRequired) {
        return childCount;
    }

    // Everything seems to be ok, so return success
    // success
    return -1;

}

void AllContentModel::checkUniqueParticleAttribution
    (
        SchemaGrammar*    const pGrammar
      , GrammarResolver*  const pGrammarResolver
      , XMLStringPool*    const pStringPool
      , XMLValidator*     const pValidator
      , unsigned int*     const pContentSpecOrgURI
      , const XMLCh*            pComplexTypeName /*= 0*/
    )
{
    SubstitutionGroupComparator comparator(pGrammarResolver, pStringPool);

    unsigned int i, j;

    // rename back
    for (i = 0; i < fCount; i++) {
        unsigned int orgURIIndex = fChildren[i]->getURI();
        fChildren[i]->setURI(pContentSpecOrgURI[orgURIIndex]);
    }

    // check whether there is conflict between any two leaves
    for (i = 0; i < fCount; i++) {
        for (j = i+1; j < fCount; j++) {
            // If this is text in a Schema mixed content model, skip it.
            if ( fIsMixed &&
                 (( fChildren[i]->getURI() == XMLElementDecl::fgPCDataElemId) ||
                  ( fChildren[j]->getURI() == XMLElementDecl::fgPCDataElemId)))
                continue;

            if (XercesElementWildcard::conflict(pGrammar,
                                                ContentSpecNode::Leaf,
                                                fChildren[i],
                                                ContentSpecNode::Leaf,
                                                fChildren[j],
                                                &comparator)) {
                pValidator->emitError(XMLValid::UniqueParticleAttributionFail,
                                      pComplexTypeName,
                                      fChildren[i]->getRawName(),
                                      fChildren[j]->getRawName());
             }
         }
    }
}

// ---------------------------------------------------------------------------
//  AllContentModel: Private helper methods
// ---------------------------------------------------------------------------
void
AllContentModel::buildChildList(ContentSpecNode* const       curNode
                              , ValueVectorOf<QName*>&       toFill
                              , ValueVectorOf<bool>&         toOptional)
{
    // Get the type of spec node our current node is
    const ContentSpecNode::NodeTypes curType = curNode->getType();

    if (curType == ContentSpecNode::All)
    {
        // Get both the child node pointers
        ContentSpecNode* leftNode = curNode->getFirst();
        ContentSpecNode* rightNode = curNode->getSecond();

        // Recurse on the left and right nodes
        buildChildList(leftNode, toFill, toOptional);
        buildChildList(rightNode, toFill, toOptional);
    }
    else if (curType == ContentSpecNode::Leaf)
    {
        // At leaf, add the element to list of elements permitted in the all
        toFill.addElement(curNode->getElement());
        toOptional.addElement(false);
        fNumRequired++;
    }
    else if (curType == ContentSpecNode::ZeroOrOne)
    {
        // At ZERO_OR_ONE node, subtree must be an element
        // that was specified with minOccurs=0, maxOccurs=1
        ContentSpecNode* leftNode = curNode->getFirst();
        if (leftNode->getType() != ContentSpecNode::Leaf)
            ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::CM_UnknownCMSpecType, fMemoryManager);

        toFill.addElement(leftNode->getElement());
        toOptional.addElement(true);
    }
    else
        ThrowXMLwithMemMgr(RuntimeException, XMLExcepts::CM_UnknownCMSpecType, fMemoryManager);
}

XERCES_CPP_NAMESPACE_END
