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
 * $Log: BinFileOutputStream.cpp,v $
 * Revision 1.4  2004/09/08 13:56:13  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.3  2004/02/16 04:02:34  neilg
 * fix for bug 26936
 *
 * Revision 1.2  2003/12/17 13:58:02  cargilld
 * Platform update for memory management so that the static memory manager (one
 * used to call Initialize) is only for static data.
 *
 * Revision 1.1  2003/09/18 18:39:12  peiyongz
 * Binary File Output Stream:
 *
 * $Id: BinFileOutputStream.cpp,v 1.4 2004/09/08 13:56:13 peiyongz Exp $
 *
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/internal/BinFileOutputStream.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>
#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  BinFileOutputStream: Constructors and Destructor
// ---------------------------------------------------------------------------
BinFileOutputStream::~BinFileOutputStream()
{
    if (fSource)
        XMLPlatformUtils::closeFile(fSource, fMemoryManager);
}

BinFileOutputStream::BinFileOutputStream(const XMLCh*   const fileName
                                         , MemoryManager* const manager)

:fSource(0)
,fMemoryManager(manager)
{
    fSource = XMLPlatformUtils::openFileToWrite(fileName, manager);
}

BinFileOutputStream::BinFileOutputStream(const char*    const fileName
                                       , MemoryManager* const manager)
:fSource(0)
,fMemoryManager(manager)
{
    // Transcode the file name and put a janitor on the temp buffer
    XMLCh* realName = XMLString::transcode(fileName, manager);
    ArrayJanitor<XMLCh> janName(realName, manager);

    // Try to open the file
    fSource = XMLPlatformUtils::openFileToWrite(realName, manager);
}

// ---------------------------------------------------------------------------
//  BinFileOutputStream: Getter methods
// ---------------------------------------------------------------------------
unsigned int BinFileOutputStream::getSize() const
{
    return XMLPlatformUtils::fileSize(fSource, fMemoryManager);
}


// ---------------------------------------------------------------------------
//  BinFileOutputStream: Stream management methods
// ---------------------------------------------------------------------------
void BinFileOutputStream::reset()
{
    XMLPlatformUtils::resetFile(fSource, fMemoryManager);
}


// ---------------------------------------------------------------------------
//  BinFileOutputStream: Implementation of the input stream interface
// ---------------------------------------------------------------------------
unsigned int BinFileOutputStream::curPos() const
{
    return XMLPlatformUtils::curFilePos(fSource, fMemoryManager);
}


void BinFileOutputStream::writeBytes( const XMLByte* const  toGo
                                    , const unsigned int    maxToWrite)
{
    //
    //  Write up to the maximum bytes requested. 
    //  

    XMLPlatformUtils::writeBufferToFile(fSource, maxToWrite, toGo, fMemoryManager);
}

XERCES_CPP_NAMESPACE_END
