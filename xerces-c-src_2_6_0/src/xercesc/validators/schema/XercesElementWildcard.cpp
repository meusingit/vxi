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
 * $Log: XercesElementWildcard.cpp,v $
 * Revision 1.3  2004/09/08 13:56:58  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.2  2002/11/04 14:49:42  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:50  peiyongz
 * sane_include
 *
 * Revision 1.3  2001/11/21 14:30:13  knoaman
 * Fix for UPA checking.
 *
 * Revision 1.2  2001/08/22 16:58:27  tng
 * typo: the type should be t1/t2, not w1/w2.
 *
 * Revision 1.1  2001/08/21 15:58:42  tng
 * Schema: New files XercesElementWildCard.
 *
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/XercesElementWildcard.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Local methods
// ---------------------------------------------------------------------------

/**
 * XercesElementWildcard is used to check whether two element declarations conflict
 */
/**
 * Check whether two element declarations conflict
 */
bool XercesElementWildcard::conflict(SchemaGrammar* const pGrammar,
                                     ContentSpecNode::NodeTypes   type1,
                                     QName*                       q1,
                                     ContentSpecNode::NodeTypes   type2,
                                     QName*                       q2,
                                     SubstitutionGroupComparator* comparator)
{
    if (type1 == ContentSpecNode::Leaf &&
        type2 == ContentSpecNode::Leaf) {
        if (comparator->isEquivalentTo(q1, q2) || comparator->isEquivalentTo(q2, q1))
            return true;
    }
    else if (type1 == ContentSpecNode::Leaf) {
        return uriInWildcard(pGrammar, q1, q2->getURI(), type2, comparator);
    }
    else if (type2 == ContentSpecNode::Leaf) {
        return uriInWildcard(pGrammar, q2, q1->getURI(), type1, comparator);
    }
    else {
        return wildcardIntersect(type1, q1->getURI(), type2, q2->getURI());
    }
    return false;
}

bool XercesElementWildcard::uriInWildcard(SchemaGrammar* const         pGrammar,
                                          QName*                       qname,
                                          unsigned int                 wildcard,
                                          ContentSpecNode::NodeTypes   wtype,
                                          SubstitutionGroupComparator* comparator)
{
    if ((wtype & 0x0f)== ContentSpecNode::Any) {
        return true;
    }
    else if ((wtype & 0x0f)== ContentSpecNode::Any_NS) {
        // substitution of "uri" satisfies "wtype:wildcard"
        return comparator->isAllowedByWildcard(pGrammar, qname, wildcard, false);
    }
    else if ((wtype & 0x0f)== ContentSpecNode::Any_Other) {
        // substitution of "uri" satisfies "wtype:wildcard"
        return comparator->isAllowedByWildcard(pGrammar, qname, wildcard, true);
    }

    return false;
}

bool XercesElementWildcard::wildcardIntersect(ContentSpecNode::NodeTypes t1,
                                              unsigned int               w1,
                                              ContentSpecNode::NodeTypes t2,
                                              unsigned int               w2)
{
    if (((t1 & 0x0f) == ContentSpecNode::Any) ||
        ((t2 & 0x0f) == ContentSpecNode::Any)) {
        // if either one is "##any", then intersects
        return true;
    }
    else if (((t1 & 0x0f) == ContentSpecNode::Any_NS) &&
             ((t2 & 0x0f) == ContentSpecNode::Any_NS) &&
             (w1 == w2)) {
        // if both are "some_namespace" and equal, then intersects
        return true;
    }
    else if (((t1 & 0x0f) == ContentSpecNode::Any_Other) &&
             ((t2 & 0x0f) == ContentSpecNode::Any_Other)) {
        // if both are "##other", and equal, then intersects
        return true;
    }
    else if (((((t1 & 0x0f) == ContentSpecNode::Any_NS) &&
               ((t2 & 0x0f) == ContentSpecNode::Any_Other)) ||
              (((t1 & 0x0f) == ContentSpecNode::Any_Other) &&
               ((t2 & 0x0f) == ContentSpecNode::Any_NS))) &&
             (w1 != w2)) {
        return true;
    }
    return false;
}

XERCES_CPP_NAMESPACE_END
