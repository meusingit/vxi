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
  * $Log: XMLRefInfo.cpp,v $
  * Revision 1.2  2004/09/08 13:55:59  peiyongz
  * Apache License Version 2.0
  *
  * Revision 1.1  2003/09/30 18:14:34  peiyongz
  * Implementation of Serialization/Deserialization
  *
  * $Id: XMLRefInfo.cpp,v 1.2 2004/09/08 13:55:59 peiyongz Exp $
  *
  */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/framework/XMLRefInfo.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_TOCREATE(XMLRefInfo)

void XMLRefInfo::serialize(XSerializeEngine& serEng)
{
    if (serEng.isStoring())
    {   
        serEng<<fDeclared;
        serEng<<fUsed;
        serEng.writeString(fRefName);
    }
    else
    {
        serEng>>fDeclared;
        serEng>>fUsed;
        serEng.readString(fRefName);
    }

}

XMLRefInfo::XMLRefInfo(MemoryManager* const manager) 
:fDeclared(false)
,fUsed(false)
,fRefName(0)
,fMemoryManager(manager)
{
}

XERCES_CPP_NAMESPACE_END
