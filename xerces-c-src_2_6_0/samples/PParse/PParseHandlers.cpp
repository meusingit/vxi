/*
 * Copyright 1999-2001,2004 The Apache Software Foundation.
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
 * $Id: PParseHandlers.cpp,v 1.8 2004/09/08 13:55:32 peiyongz Exp $
 */



// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include "PParse.hpp"


// ---------------------------------------------------------------------------
//  PParseHandlers: Constructors and Destructor
// ---------------------------------------------------------------------------
PParseHandlers::PParseHandlers() :

    fElementCount(0)
    , fAttrCount(0)
    , fCharacterCount(0)
    , fSpaceCount(0)
{
}

PParseHandlers::~PParseHandlers()
{
}


// ---------------------------------------------------------------------------
//  PParseHandlers: Overrides of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------
void PParseHandlers::startElement(const   XMLCh* const    name
                                    ,       AttributeList&  attributes)
{
    fElementCount++;
    fAttrCount += attributes.getLength();
}

void PParseHandlers::characters(  const   XMLCh* const    chars
								    , const unsigned int    length)
{
    fCharacterCount += length;
}

void PParseHandlers::ignorableWhitespace( const   XMLCh* const chars
										    , const unsigned int length)
{
    fSpaceCount += length;
}

void PParseHandlers::resetDocument()
{
    fAttrCount = 0;
    fCharacterCount = 0;
    fElementCount = 0;
    fSpaceCount = 0;
}


// ---------------------------------------------------------------------------
//  PParseHandlers: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------
void PParseHandlers::error(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nError at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void PParseHandlers::fatalError(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nFatal Error at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void PParseHandlers::warning(const SAXParseException& e)
{
    XERCES_STD_QUALIFIER cerr << "\nWarning at file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "\n  Message: " << StrX(e.getMessage()) << XERCES_STD_QUALIFIER endl;
}

