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
 * $Id: BinMemOutputStream.cpp,v 1.5 2004/09/08 13:56:13 peiyongz Exp $
 * $Log: BinMemOutputStream.cpp,v $
 * Revision 1.5  2004/09/08 13:56:13  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.4  2004/03/05 22:19:32  peiyongz
 * getSize() to return fCapacity to differentiate it from curPos()
 *
 * Revision 1.3  2004/02/16 04:02:34  neilg
 * fix for bug 26936
 *
 * Revision 1.2  2003/12/17 00:01:44  peiyongz
 * getSize()
 *
 * Revision 1.1  2003/12/16 16:56:51  peiyongz
 * BinMemOutputStream
 *
 *
 */

#include <xercesc/internal/BinMemOutputStream.hpp>
#include <xercesc/util/XMLString.hpp>
#include <string.h>

XERCES_CPP_NAMESPACE_BEGIN

BinMemOutputStream::BinMemOutputStream( int                  initCapacity
                                      , MemoryManager* const manager)
: fMemoryManager(manager)
, fDataBuf(0)
, fIndex(0)
, fCapacity(initCapacity)
{
    // Buffer is one larger than capacity, to allow for zero term
    fDataBuf = (XMLByte*) fMemoryManager->allocate
    (
        (fCapacity + 4) * sizeof(XMLByte)
    );

    // Keep it null terminated
    fDataBuf[0] = XMLByte(0);
}

BinMemOutputStream::~BinMemOutputStream()
{
    fMemoryManager->deallocate(fDataBuf);
}

void BinMemOutputStream::writeBytes( const XMLByte*     const      toGo
                                   , const unsigned int            maxToWrite)
{

    if (maxToWrite) 
    {
        insureCapacity(maxToWrite);
        memcpy(&fDataBuf[fIndex], toGo, maxToWrite * sizeof(XMLByte));
        fIndex += maxToWrite;
    }

}

const XMLByte* BinMemOutputStream::getRawBuffer() const
{
    fDataBuf[fIndex] = 0;
    fDataBuf[fIndex + 1] = 0;
    fDataBuf[fIndex + 2] = 0;
    fDataBuf[fIndex + 3] = 0;
    return fDataBuf;
}

void BinMemOutputStream::reset()
{
    fIndex = 0;
    for (int i = 0; i < 4; i++)
    {
        fDataBuf[fIndex + i] = 0;
    }
}

unsigned int BinMemOutputStream::curPos() const
{
    return fIndex;
}

unsigned int BinMemOutputStream::getSize() const
{
    return fCapacity;
}

// ---------------------------------------------------------------------------
//  BinMemOutputStream: Private helper methods
// ---------------------------------------------------------------------------
void BinMemOutputStream::insureCapacity(const unsigned int extraNeeded)
{
    // If we can handle it, do nothing yet
    if (fIndex + extraNeeded < fCapacity)
        return;

    // Oops, not enough room. Calc new capacity and allocate new buffer
    const unsigned int newCap = (unsigned int)((fIndex + extraNeeded) * 2);
    XMLByte* newBuf = (XMLByte*) fMemoryManager->allocate
    (
        (newCap+4) * sizeof(XMLByte)
    );

    // Copy over the old stuff
    memcpy(newBuf, fDataBuf, fCapacity * sizeof(XMLByte) + 4);

    // Clean up old buffer and store new stuff
    fMemoryManager->deallocate(fDataBuf); 
    fDataBuf = newBuf;
    fCapacity = newCap;
}


XERCES_CPP_NAMESPACE_END

