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

/*
 * $Log: SynchronizedStringPool.cpp,v $
 * Revision 1.3  2004/09/08 13:56:23  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.2  2003/10/09 15:35:13  neilg
 * fix bug in synchronized addOrFind method; thanks to Khaled for pointing this out
 *
 * Revision 1.1  2003/10/09 13:51:16  neilg
 * implementation of a StringPool implementation that permits thread-safe updates.  This can now be used by a grammar pool that is locked so that scanners have somehwere to store information about newly-encountered URIs
 *
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/SynchronizedStringPool.hpp>


XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  XMLSynchronizedStringPool: Constructors and Destructor
// ---------------------------------------------------------------------------
XMLSynchronizedStringPool::XMLSynchronizedStringPool(const XMLStringPool *constPool
                , const  unsigned int  modulus
                , MemoryManager* const manager) :

    XMLStringPool(modulus, manager)
    , fConstPool(constPool)
{
}

XMLSynchronizedStringPool::~XMLSynchronizedStringPool()
{
}


// ---------------------------------------------------------------------------
//  XMLSynchronizedStringPool: Pool management methods
// ---------------------------------------------------------------------------
unsigned int XMLSynchronizedStringPool::addOrFind(const XMLCh* const newString)
{
    unsigned int id = fConstPool->getId(newString);
    if(id)
        return id;
    // might have to add it to our own table.
    // synchronize this bit
    {
        XMLMutexLock lockInit(&fMutex);
        id = XMLStringPool::addOrFind(newString);
        return id+fConstPool->getStringCount();
    }
}

bool XMLSynchronizedStringPool::exists(const XMLCh* const newString) const
{
    if(fConstPool->exists(newString))
        return true;
    return XMLStringPool::exists(newString);
}

bool XMLSynchronizedStringPool::exists(const unsigned int id) const
{
    if (!id || (id >= fCurId+fConstPool->getStringCount()))
        return false;

    return true;
}

void XMLSynchronizedStringPool::flushAll()
{
    // don't touch const pool!
    XMLStringPool::flushAll();
}


unsigned int XMLSynchronizedStringPool::getId(const XMLCh* const toFind) const
{
    unsigned int retVal = fConstPool->getId(toFind);
    if(retVal)
        return retVal;
    // make sure we return a truly unique id
    return XMLStringPool::getId(toFind)+fConstPool->getStringCount();
}


const XMLCh* XMLSynchronizedStringPool::getValueForId(const unsigned int id) const
{
    if (id <= fConstPool->getStringCount())
        return fConstPool->getValueForId(id);
    return XMLStringPool::getValueForId(id-fConstPool->getStringCount());
}

unsigned int XMLSynchronizedStringPool::getStringCount() const
{
    return fCurId+fConstPool->getStringCount()-1;
}

XERCES_CPP_NAMESPACE_END
