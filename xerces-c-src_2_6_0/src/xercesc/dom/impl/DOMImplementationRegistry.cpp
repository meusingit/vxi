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
 * $Id: DOMImplementationRegistry.cpp,v 1.7 2004/09/08 13:55:51 peiyongz Exp $
 */

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/RefVectorOf.hpp>
#include <xercesc/util/XMLRegisterCleanup.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMImplementationSource.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include "DOMImplementationImpl.hpp"

XERCES_CPP_NAMESPACE_BEGIN


// -----------------------------------------------------------------------
//  Static constants.  These are lazily initialized on first usage.
//                     (Static constructors can not be safely used because
//                      of order of initialization dependencies.)
// -----------------------------------------------------------------------
// Points to the singleton instance of a registry of DOMImplementationSource
static RefVectorOf<DOMImplementationSource>* gDOMImplSrcVector = 0;

//  Global mutex that is used to synchronize access to the vector
static XMLMutex* gDOMImplSrcVectorMutex = 0;

static XMLRegisterCleanup cleanupDOMImplSrcVector;
static XMLRegisterCleanup cleanupDOMImplSrcVectorMutex;

// -----------------------------------------------------------------------
//  Function prototypes for internally used functions.
// -----------------------------------------------------------------------
RefVectorOf<DOMImplementationSource>* getDOMImplSrcVector();
XMLMutex& getDOMImplSrcVectorMutex();


// -----------------------------------------------------------------------
//  Reset the static data
// -----------------------------------------------------------------------
static void reinitDOMImplSrcVector()
{
	delete gDOMImplSrcVector;
	gDOMImplSrcVector = 0;
}

static void reinitDOMImplSrcVectorMutex()
{
    delete gDOMImplSrcVectorMutex;
    gDOMImplSrcVectorMutex = 0;
}

// -----------------------------------------------------------------------
//  Get the static data
// -----------------------------------------------------------------------
RefVectorOf<DOMImplementationSource>* getDOMImplSrcVector()
{
    // Note: we are not synchronizing on creation since that caller is doing
    //       it (i.e. caller is locking a mutex before calling us)
    if (!gDOMImplSrcVector)
    {
        gDOMImplSrcVector = new RefVectorOf<DOMImplementationSource>(3, false);
        cleanupDOMImplSrcVector.registerCleanup(reinitDOMImplSrcVector);
    }

    return gDOMImplSrcVector;
}

XMLMutex& getDOMImplSrcVectorMutex()
{
    if (!gDOMImplSrcVectorMutex)
    {
        XMLMutexLock lock(XMLPlatformUtils::fgAtomicMutex);

        if (!gDOMImplSrcVectorMutex)
        {
            gDOMImplSrcVectorMutex = new XMLMutex;
            cleanupDOMImplSrcVectorMutex.registerCleanup(reinitDOMImplSrcVectorMutex);
        }
    }

    return *gDOMImplSrcVectorMutex;
}


// -----------------------------------------------------------------------
//  DOMImplementationRegistry Functions
// -----------------------------------------------------------------------
DOMImplementation *DOMImplementationRegistry::getDOMImplementation(const XMLCh* features) {

    XMLMutexLock lock(&getDOMImplSrcVectorMutex());

    unsigned int len = getDOMImplSrcVector()->size();

    // Put our defined source there
    if (len == 0)
        getDOMImplSrcVector()->addElement((DOMImplementationSource*)DOMImplementationImpl::getDOMImplementationImpl());

    len = getDOMImplSrcVector()->size();

    for (unsigned int i = len; i > 0; i--) {
        DOMImplementationSource* source = getDOMImplSrcVector()->elementAt(i-1);
        DOMImplementation* impl = source->getDOMImplementation(features);
        if (impl)
            return impl;
    }

    return 0;
}

void DOMImplementationRegistry::addSource (DOMImplementationSource* source) {
    XMLMutexLock lock(&getDOMImplSrcVectorMutex());
    getDOMImplSrcVector()->addElement(source);
}


XERCES_CPP_NAMESPACE_END

