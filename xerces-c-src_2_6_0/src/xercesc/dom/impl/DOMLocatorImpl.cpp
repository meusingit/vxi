/*
 * Copyright 2002,2004 The Apache Software Foundation.
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
 * $Log: DOMLocatorImpl.cpp,v $
 * Revision 1.5  2004/09/08 13:55:51  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.4  2002/11/04 15:07:34  tng
 * C++ Namespace Support.
 *
 * Revision 1.3  2002/05/27 18:25:41  tng
 * To get ready for 64 bit large file, use XMLSSize_t to represent line and column number.
 *
 * Revision 1.2  2002/05/24 14:02:07  knoaman
 * Fix complilation error.
 *
 * Revision 1.1  2002/05/23 15:47:24  knoaman
 * DOM L3 core - support for DOMError, DOMErrorHandler and DOMLocator
 *
 */

#include "DOMLocatorImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


// ---------------------------------------------------------------------------
//  DOMLocatorImpl: Constructors and Destructor
// ---------------------------------------------------------------------------
DOMLocatorImpl::DOMLocatorImpl() :
fLineNum(-1)
, fColumnNum(-1)
, fOffset(-1)
, fErrorNode(0)
, fURI(0)
{
}


DOMLocatorImpl::DOMLocatorImpl(const XMLSSize_t lineNum,
                               const XMLSSize_t columnNum,
                               DOMNode* const errorNode,
                               const XMLCh* const uri,
                               const XMLSSize_t offset) :
fLineNum(lineNum)
, fColumnNum(columnNum)
, fOffset(offset)
, fErrorNode(errorNode)
, fURI(uri)
{
}

DOMLocatorImpl::~DOMLocatorImpl()
{
}

XERCES_CPP_NAMESPACE_END

