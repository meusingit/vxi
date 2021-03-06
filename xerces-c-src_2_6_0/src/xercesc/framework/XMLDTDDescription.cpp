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
 * $Id: XMLDTDDescription.cpp,v 1.2 2004/09/08 13:55:58 peiyongz Exp $
 * $Log: XMLDTDDescription.cpp,v $
 * Revision 1.2  2004/09/08 13:55:58  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1  2003/10/14 15:16:58  peiyongz
 * Implementation of Serialization/Deserialization
 *
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/framework/XMLDTDDescription.hpp>

XERCES_CPP_NAMESPACE_BEGIN

XMLDTDDescription::~XMLDTDDescription()
{
}

XMLDTDDescription::XMLDTDDescription(MemoryManager* const memMgr)
:XMLGrammarDescription(memMgr)
{
}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_NOCREATE(XMLDTDDescription)

void XMLDTDDescription::serialize(XSerializeEngine& serEng)
{

    XMLGrammarDescription::serialize(serEng);

    //no data
}

XERCES_CPP_NAMESPACE_END

