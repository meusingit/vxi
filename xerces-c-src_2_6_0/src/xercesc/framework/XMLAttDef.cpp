/*
 * Copyright 1999-2004 The Apache Software Foundation.
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

/**
 * $Id: XMLAttDef.cpp,v 1.9 2004/09/08 13:55:58 peiyongz Exp $
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/framework/XMLAttDef.hpp>
#include <xercesc/util/ArrayIndexOutOfBoundsException.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Local const data
//
//  gAttTypeStrings
//      A list of strings which are used to map attribute type numbers to
//      attribute type names.
//
//  gDefAttTypesStrings
//      A list of strings which are used to map default attribute type
//      numbers to default attribute type names.
// ---------------------------------------------------------------------------
const XMLCh* const gAttTypeStrings[XMLAttDef::AttTypes_Count] =
{
    XMLUni::fgCDATAString
    , XMLUni::fgIDString
    , XMLUni::fgIDRefString
    , XMLUni::fgIDRefsString
    , XMLUni::fgEntityString
    , XMLUni::fgEntitiesString
    , XMLUni::fgNmTokenString
    , XMLUni::fgNmTokensString
    , XMLUni::fgNotationString
    , XMLUni::fgEnumerationString
    , XMLUni::fgCDATAString
    , XMLUni::fgCDATAString
    , XMLUni::fgCDATAString
    , XMLUni::fgCDATAString

};

const XMLCh* const gDefAttTypeStrings[XMLAttDef::DefAttTypes_Count] =
{
    XMLUni::fgDefaultString
    , XMLUni::fgFixedString
    , XMLUni::fgRequiredString
    , XMLUni::fgImpliedString
    , XMLUni::fgImpliedString
    , XMLUni::fgImpliedString
    , XMLUni::fgImpliedString
    , XMLUni::fgImpliedString
    , XMLUni::fgImpliedString
};



// ---------------------------------------------------------------------------
//  XMLAttDef: Public, static data members
// ---------------------------------------------------------------------------
const unsigned int XMLAttDef::fgInvalidAttrId = 0xFFFFFFFE;


// ---------------------------------------------------------------------------
//  XMLAttDef: Public, static methods
// ---------------------------------------------------------------------------
const XMLCh* XMLAttDef::getAttTypeString(const XMLAttDef::AttTypes attrType
                                         , MemoryManager* const manager)
{
    // Check for an invalid attribute type and return a null
    if ((attrType < AttTypes_Min) || (attrType > AttTypes_Max))
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::AttDef_BadAttType, manager);
    return gAttTypeStrings[attrType];
}

const XMLCh* XMLAttDef::getDefAttTypeString(const XMLAttDef::DefAttTypes attrType
                                            , MemoryManager* const manager)
{
    // Check for an invalid attribute type and return a null
    if ((attrType < DefAttTypes_Min) || (attrType > DefAttTypes_Max))
        ThrowXMLwithMemMgr(ArrayIndexOutOfBoundsException, XMLExcepts::AttDef_BadDefAttType, manager);
    return gDefAttTypeStrings[attrType];
}


// ---------------------------------------------------------------------------
//  XMLAttDef: Destructor
// ---------------------------------------------------------------------------
XMLAttDef::~XMLAttDef()
{
    cleanUp();
}


// ---------------------------------------------------------------------------
//  XMLAttDef: Hidden constructors
// ---------------------------------------------------------------------------
XMLAttDef::XMLAttDef( const XMLAttDef::AttTypes    type
                    , const XMLAttDef::DefAttTypes defType
                    , MemoryManager* const         manager) :

    fDefaultType(defType)
    , fType(type)
    , fCreateReason(XMLAttDef::NoReason)
    , fProvided(false)
    , fExternalAttribute(false)
    , fId(XMLAttDef::fgInvalidAttrId)
    , fValue(0)
    , fEnumeration(0)
    , fMemoryManager(manager)
{
}

XMLAttDef::XMLAttDef( const XMLCh* const           attrValue
                    , const XMLAttDef::AttTypes    type
                    , const XMLAttDef::DefAttTypes defType
                    , const XMLCh* const           enumValues
                    , MemoryManager* const         manager) :

    fDefaultType(defType)
    , fType(type)
    , fCreateReason(XMLAttDef::NoReason)
    , fProvided(false)
    , fExternalAttribute(false)
    , fId(XMLAttDef::fgInvalidAttrId)
    , fValue(0)
    , fEnumeration(0)
    , fMemoryManager(manager)
{
    try
    {
        fValue = XMLString::replicate(attrValue, fMemoryManager);
        fEnumeration = XMLString::replicate(enumValues, fMemoryManager);
    }
    catch(const OutOfMemoryException&)
    {
        throw;
    }
    catch(...)
    {
        cleanUp();
    }
}


// ---------------------------------------------------------------------------
//  XMLAttDef: Private helper methods
// ---------------------------------------------------------------------------
void XMLAttDef::cleanUp()
{
    if (fEnumeration)
        fMemoryManager->deallocate(fEnumeration);

    if (fValue)
        fMemoryManager->deallocate(fValue);
}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_NOCREATE(XMLAttDef)

void XMLAttDef::serialize(XSerializeEngine& serEng)
{

    if (serEng.isStoring())
    {
        serEng<<(int)fDefaultType;
        serEng<<(int)fType;
        serEng<<(int)fCreateReason;
        serEng<<fProvided;
        serEng<<fExternalAttribute;
        serEng<<fId;

        serEng.writeString(fValue);
        serEng.writeString(fEnumeration);
    }
    else
    {
        int i;
        serEng>>i;
        fDefaultType = (DefAttTypes) i;

        serEng>>i;
        fType = (AttTypes)i;

        serEng>>i;
        fCreateReason = (CreateReasons)i;

        serEng>>fProvided;
        serEng>>fExternalAttribute;
        serEng>>fId;

        serEng.readString(fValue);
        serEng.readString(fEnumeration);
    }
}

XERCES_CPP_NAMESPACE_END

