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
 * $Log: XTemplateComparator.cpp,v $
 * Revision 1.4  2004/09/08 13:56:14  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.3  2003/12/19 23:02:43  cargilld
 * Fix compiler messages on OS390.
 *
 * Revision 1.2  2003/12/17 00:18:34  cargilld
 * Update to memory management so that the static memory manager (one used to call Initialize) is only for static data.
 *
 * Revision 1.1  2003/10/29 16:14:15  peiyongz
 * XObjectComparator/XTemplateComparator
 *
 * $Id: XTemplateComparator.cpp,v 1.4 2004/09/08 13:56:14 peiyongz Exp $
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/internal/XTemplateComparator.hpp>
#include <xercesc/internal/XObjectComparator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

    /**********************************************************
     *
     * ValueVectorOf
     *
     *   SchemaElementDecl*
     *   unsigned int
     *
     ***********************************************************/   
bool XTemplateComparator::isEquivalent(ValueVectorOf<SchemaElementDecl*>* const lValue
                                     , ValueVectorOf<SchemaElementDecl*>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        SchemaElementDecl*& data1 = lValue->elementAt(i);
        SchemaElementDecl*& data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

bool XTemplateComparator::isEquivalent(ValueVectorOf<unsigned int>* const lValue
                                     , ValueVectorOf<unsigned int>* const rValue)
                                     
{

    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        unsigned int& data1 = lValue->elementAt(i);
        unsigned int& data2 = rValue->elementAt(i);
        if (data1!=data2)
            return false;
    }

    return true;

}

    /**********************************************************
     *
     * RefArrayVectorOf
     *
     *   XMLCh
     *
     ***********************************************************/   
bool XTemplateComparator::isEquivalent(RefArrayVectorOf<XMLCh>* const lValue
                                     , RefArrayVectorOf<XMLCh>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        XMLCh* data1 = lValue->elementAt(i);
        XMLCh* data2 = rValue->elementAt(i);

        if (!XMLString::equals(data1, data2))
        {            
            return false;
        }
    }

    return true;

}

    /**********************************************************
     *
     * RefVectorOf
     *
     *   SchemaAttDef
     *   SchemaElementDecl
     *   ContentSpecNode
     *   IC_Field
     *   DatatypeValidator
     *   IdentityConstraint
     *   XMLNumber
     *   XercesLocationPath
     *   XercesStep
     *
     ***********************************************************/
bool XTemplateComparator::isEquivalent(RefVectorOf<SchemaAttDef>* const lValue
                                     , RefVectorOf<SchemaAttDef>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        SchemaAttDef* data1 = lValue->elementAt(i);
        SchemaAttDef* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

bool XTemplateComparator::isEquivalent(RefVectorOf<SchemaElementDecl>* const lValue
                                     , RefVectorOf<SchemaElementDecl>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        SchemaElementDecl* data1 = lValue->elementAt(i);
        SchemaElementDecl* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

bool XTemplateComparator::isEquivalent(RefVectorOf<ContentSpecNode>* const lValue
                                     , RefVectorOf<ContentSpecNode>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        ContentSpecNode* data1 = lValue->elementAt(i);
        ContentSpecNode* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;

}

bool XTemplateComparator::isEquivalent(RefVectorOf<IC_Field>* const lValue
                                     , RefVectorOf<IC_Field>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        IC_Field* data1 = lValue->elementAt(i);
        IC_Field* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;

}

bool XTemplateComparator::isEquivalent(RefVectorOf<DatatypeValidator>* const lValue
                                     , RefVectorOf<DatatypeValidator>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        DatatypeValidator* data1 = lValue->elementAt(i);
        DatatypeValidator* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

bool XTemplateComparator::isEquivalent(RefVectorOf<IdentityConstraint>* const lValue
                                     , RefVectorOf<IdentityConstraint>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        IdentityConstraint* data1 = lValue->elementAt(i);
        IdentityConstraint* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

bool XTemplateComparator::isEquivalent(RefVectorOf<XMLNumber>* const lValue
                                     , RefVectorOf<XMLNumber>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        XMLNumber* data1 = lValue->elementAt(i);
        XMLNumber* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

bool XTemplateComparator::isEquivalent(RefVectorOf<XercesLocationPath>* const lValue
                                     , RefVectorOf<XercesLocationPath>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        XercesLocationPath* data1 = lValue->elementAt(i);
        XercesLocationPath* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

bool XTemplateComparator::isEquivalent(RefVectorOf<XercesStep>* const lValue
                                     , RefVectorOf<XercesStep>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    int size1 = lValue->size();
    int size2 = rValue->size();

    if (size1 != size2)
        return false;

    for ( int i = 0; i < size1; i++)
    {            
        XercesStep* data1 = lValue->elementAt(i);
        XercesStep* data2 = rValue->elementAt(i);
        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;
    }

    return true;
}

    /**********************************************************
     *
     * RefHashTableOf
     *
     *   KVStringPair
     *   XMLAttDef
     *   DTDAttDef
     *   ComplexTypeInfo
     *   XercesGroupInfo
     *   XercesAttGroupInfo
     *   XMLRefInfo
     *   DatatypeValidator
     *   Grammar
     *
     ***********************************************************/
bool XTemplateComparator::isEquivalent(RefHashTableOf<KVStringPair>* const lValue
                                     , RefHashTableOf<KVStringPair>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<KVStringPair> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<KVStringPair> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*        key   = (XMLCh*) lEnum.nextElementKey();
        KVStringPair* data1 = lValue->get(key);
        KVStringPair* data2 = rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

bool XTemplateComparator::isEquivalent(RefHashTableOf<XMLAttDef>* const lValue
                                     , RefHashTableOf<XMLAttDef>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<XMLAttDef> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<XMLAttDef> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*     key   = (XMLCh*) lEnum.nextElementKey();
        //we know they are SchemaAttDef
        SchemaAttDef* data1 = (SchemaAttDef*) lValue->get(key);
        SchemaAttDef* data2 = (SchemaAttDef*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;

}

bool XTemplateComparator::isEquivalent(RefHashTableOf<DTDAttDef>* const lValue
                                     , RefHashTableOf<DTDAttDef>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<DTDAttDef> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<DTDAttDef> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*     key   = (XMLCh*) lEnum.nextElementKey();
        DTDAttDef* data1 = (DTDAttDef*) lValue->get(key);
        DTDAttDef* data2 = (DTDAttDef*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;

}

bool XTemplateComparator::isEquivalent(RefHashTableOf<ComplexTypeInfo>* const lValue
                                     , RefHashTableOf<ComplexTypeInfo>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<ComplexTypeInfo> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<ComplexTypeInfo> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*           key   = (XMLCh*) lEnum.nextElementKey();
        ComplexTypeInfo* data1 = (ComplexTypeInfo*) lValue->get(key);
        ComplexTypeInfo* data2 = (ComplexTypeInfo*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

bool XTemplateComparator::isEquivalent(RefHashTableOf<XercesGroupInfo>* const lValue
                                     , RefHashTableOf<XercesGroupInfo>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<XercesGroupInfo> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<XercesGroupInfo> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*           key   = (XMLCh*) lEnum.nextElementKey();
        XercesGroupInfo* data1 = (XercesGroupInfo*) lValue->get(key);
        XercesGroupInfo* data2 = (XercesGroupInfo*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

bool XTemplateComparator::isEquivalent(RefHashTableOf<XercesAttGroupInfo>* const lValue
                                     , RefHashTableOf<XercesAttGroupInfo>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<XercesAttGroupInfo> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<XercesAttGroupInfo> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*              key   = (XMLCh*) lEnum.nextElementKey();
        XercesAttGroupInfo* data1 = (XercesAttGroupInfo*) lValue->get(key);
        XercesAttGroupInfo* data2 = (XercesAttGroupInfo*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

bool XTemplateComparator::isEquivalent(RefHashTableOf<XMLRefInfo>* const lValue
                                     , RefHashTableOf<XMLRefInfo>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<XMLRefInfo> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<XMLRefInfo> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*      key   = (XMLCh*) lEnum.nextElementKey();
        XMLRefInfo* data1 = (XMLRefInfo*) lValue->get(key);
        XMLRefInfo* data2 = (XMLRefInfo*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

bool XTemplateComparator::isEquivalent(RefHashTableOf<DatatypeValidator>* const lValue
                                     , RefHashTableOf<DatatypeValidator>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<DatatypeValidator> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<DatatypeValidator> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*             key   = (XMLCh*) lEnum.nextElementKey();
        DatatypeValidator* data1 = (DatatypeValidator*) lValue->get(key);
        DatatypeValidator* data2 = (DatatypeValidator*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

bool XTemplateComparator::isEquivalent(RefHashTableOf<Grammar>* const lValue
                                     , RefHashTableOf<Grammar>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHashTableOfEnumerator<Grammar> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHashTableOfEnumerator<Grammar> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*   key   = (XMLCh*) lEnum.nextElementKey();
        Grammar* data1 = (Grammar*) lValue->get(key);
        Grammar* data2 = (Grammar*) rValue->get(key);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

    /**********************************************************
     *
     * RefHash2KeysTableOf
     *
     *   SchemaAttDef
     *   ElemVector
     *
     ***********************************************************/
bool XTemplateComparator::isEquivalent(RefHash2KeysTableOf<SchemaAttDef>* const lValue
                                     , RefHash2KeysTableOf<SchemaAttDef>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue);

    RefHash2KeysTableOfEnumerator<SchemaAttDef> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHash2KeysTableOfEnumerator<SchemaAttDef> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*     key1;
        int        key2;
            
        lEnum.nextElementKey((void*&)key1, key2);

        SchemaAttDef* data1 = (SchemaAttDef*) lValue->get(key1, key2);
        SchemaAttDef* data2 = (SchemaAttDef*) rValue->get(key1, key2);

        if (!XObjectComparator::isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

bool XTemplateComparator::isEquivalent(RefHash2KeysTableOf<ElemVector>* const lValue
                                     , RefHash2KeysTableOf<ElemVector>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue);

    RefHash2KeysTableOfEnumerator<ElemVector> lEnum(lValue, false, lValue->getMemoryManager());
    int lItemNumber = 0;        
    while (lEnum.hasMoreElements())
    {
        lEnum.nextElement();
        lItemNumber++;
    }

    RefHash2KeysTableOfEnumerator<ElemVector> rEnum(rValue, false, rValue->getMemoryManager());
    int rItemNumber = 0;        
    while (rEnum.hasMoreElements())
    {
        rEnum.nextElement();
        rItemNumber++;
    }

    //both shall have the number of item in it
    if (lItemNumber != rItemNumber)
        return false;

    //Any thing in the lValue shall be found in the rValue
    lEnum.Reset();
    while (lEnum.hasMoreElements())
    {
        XMLCh*     key1;
        int        key2;
            
        lEnum.nextElementKey((void*&)key1, key2);

        ElemVector* data1 = (ElemVector*) lValue->get(key1, key2);
        ElemVector* data2 = (ElemVector*) rValue->get(key1, key2);

        if (!isEquivalent(data1, data2))
            return false;

    }  

    return true;
}

    /**********************************************************
     *
     * RefHash3KeysIdPool
     *
     *   SchemaElementDecl
     *
     ***********************************************************/
bool XTemplateComparator::isEquivalent(RefHash3KeysIdPool<SchemaElementDecl>* const lValue
                                     , RefHash3KeysIdPool<SchemaElementDecl>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue)

    RefHash3KeysIdPoolEnumerator<SchemaElementDecl> lEnum(lValue, false, lValue->getMemoryManager());
    RefHash3KeysIdPoolEnumerator<SchemaElementDecl> rEnum(rValue, false, rValue->getMemoryManager());

    if (lEnum.size() != rEnum.size())
        return false;

    for (int i = 0; i < lEnum.size(); i++)
    {
        SchemaElementDecl&  lData = lEnum.nextElement();
        SchemaElementDecl&  rData = rEnum.nextElement();

        if (!XObjectComparator::isEquivalent(&lData, &rData))
            return false;
    }

    return true;

}

    /**********************************************************
     *
     * NameIdPool
     *
     *   DTDElementDecl
     *   DTDEntityDecl
     *   XMLNotationDecl
     *
     ***********************************************************/
bool XTemplateComparator::isEquivalent(NameIdPool<DTDElementDecl>* const lValue
                                     , NameIdPool<DTDElementDecl>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue)

    NameIdPoolEnumerator<DTDElementDecl> lEnum(lValue, lValue->getMemoryManager());
    NameIdPoolEnumerator<DTDElementDecl> rEnum(rValue, rValue->getMemoryManager());

    if (lEnum.size() != rEnum.size())
        return false;

    for (int i = 0; i < lEnum.size(); i++)
    {
        DTDElementDecl& lData = lEnum.nextElement();
        DTDElementDecl& rData = rEnum.nextElement();

        if (!XObjectComparator::isEquivalent(&lData, &rData))
            return false;

    }

    return true;

}

bool XTemplateComparator::isEquivalent(NameIdPool<DTDEntityDecl>* const lValue
                                     , NameIdPool<DTDEntityDecl>* const rValue)
{

    IS_EQUIVALENT(lValue, rValue)

    NameIdPoolEnumerator<DTDEntityDecl> lEnum(lValue, lValue->getMemoryManager());
    NameIdPoolEnumerator<DTDEntityDecl> rEnum(rValue, rValue->getMemoryManager());

    if (lEnum.size() != rEnum.size())
        return false;

    for (int i = 0; i < lEnum.size(); i++)
    {
        DTDEntityDecl& lData = lEnum.nextElement();
        DTDEntityDecl& rData = rEnum.nextElement();

        if (!XObjectComparator::isEquivalent(&lData, &rData))
            return false;

    }

    return true;

}

bool XTemplateComparator::isEquivalent(NameIdPool<XMLNotationDecl>* const lValue
                                     , NameIdPool<XMLNotationDecl>* const rValue)
{
    IS_EQUIVALENT(lValue, rValue)

    NameIdPoolEnumerator<XMLNotationDecl> lEnum(lValue, lValue->getMemoryManager());
    NameIdPoolEnumerator<XMLNotationDecl> rEnum(rValue, rValue->getMemoryManager());

    if (lEnum.size() != rEnum.size())
        return false;

    for (int i = 0; i < lEnum.size(); i++)
    {
        XMLNotationDecl& lData = lEnum.nextElement();
        XMLNotationDecl& rData = rEnum.nextElement();

        if (!XObjectComparator::isEquivalent(&lData, &rData))
            return false;

    }

    return true;

}

XERCES_CPP_NAMESPACE_END

