/*
 * Copyright 1999-2000,2004 The Apache Software Foundation.
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
 * $Log: XMLBufferMgr.hpp,v $
 * Revision 1.8  2004/09/08 13:55:58  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.7  2004/01/29 11:46:29  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.6  2003/05/16 21:36:55  knoaman
 * Memory manager implementation: Modify constructors to pass in the memory manager.
 *
 * Revision 1.5  2003/05/15 18:26:07  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.4  2002/12/04 02:32:43  knoaman
 * #include cleanup.
 *
 * Revision 1.3  2002/11/04 15:00:21  tng
 * C++ Namespace Support.
 *
 * Revision 1.2  2002/08/21 18:54:52  tng
 * [Bug 11869] Add the const modifier (XMLBuffer.hpp).
 *
 * Revision 1.1.1.1  2002/02/01 22:21:51  peiyongz
 * sane_include
 *
 * Revision 1.5  2000/03/02 19:54:24  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.4  2000/02/24 20:00:23  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.3  2000/02/15 01:21:30  roddey
 * Some initial documentation improvements. More to come...
 *
 * Revision 1.2  2000/02/06 07:47:47  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.1.1.1  1999/11/09 01:08:30  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:44:36  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */


#if !defined(XMLBUFFERMGR_HPP)
#define XMLBUFFERMGR_HPP

#include <xercesc/framework/XMLBuffer.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLBufBid;

/**
 *  There are many places where XMLBuffer objects are needed. In order to
 *  avoid either constantly creating and destroying them or maintaining a
 *  fixed set and worrying about accidental reuse, a buffer manager can
 *  provide a pool of buffers which can be temporarily used and then put
 *  back into the pool. This provides a good compromise between performance
 *  and easier maintenance.
 */
class XMLPARSER_EXPORT XMLBufferMgr : public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    /** @name Constructor */
    //@{
    XMLBufferMgr(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    //@}

    /** @name Destructor */
    //@{
    ~XMLBufferMgr();
    //@}


    // -----------------------------------------------------------------------
    //  Buffer management
    // -----------------------------------------------------------------------
    XMLBuffer& bidOnBuffer();
    void releaseBuffer(XMLBuffer& toRelease);


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLBufferMgr(const XMLBufferMgr&);
    XMLBufferMgr& operator=(const XMLBufferMgr&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fBufCount
    //      The count of buffers that have been allocated so far.
    //
    //  fBufList;
    //      The list of pointers to buffers that are loaned out. There will
    //      never be a lot of them, so a flat list is good enough.
    // -----------------------------------------------------------------------
    unsigned int    fBufCount;
    MemoryManager*  fMemoryManager;
    XMLBuffer**     fBufList;
};


/**
 *  XMLBufBid is a scoped based janitor that allows the scanner code to ask
 *  for a buffer on a scoped basis and then insure that it gets freed back
 *  into the pool no matter how the scope is exited (exception or normal exit.)
 */
class XMLBufBid : public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XMLBufBid(XMLBufferMgr* const srcMgr) :

        fBuffer(srcMgr->bidOnBuffer())
        , fMgr(srcMgr)
    {
    }

    ~XMLBufBid()
    {
        fMgr->releaseBuffer(fBuffer);
    }



    // -----------------------------------------------------------------------
    //  Buffer access
    // -----------------------------------------------------------------------
    void append(const XMLCh toAppend)
    {
        fBuffer.append(toAppend);
    }

    void append(const XMLCh* const toAppend, const unsigned int count = 0)
    {
        fBuffer.append(toAppend, count);
    }

    const XMLBuffer& getBuffer() const
    {
        return fBuffer;
    }

    XMLBuffer& getBuffer()
    {
        return fBuffer;
    }

    const XMLCh* getRawBuffer() const
    {
        fBuffer.fBuffer[fBuffer.fIndex] = 0;
        return fBuffer.fBuffer;
    }

    XMLCh* getRawBuffer()
    {
        fBuffer.fBuffer[fBuffer.fIndex] = 0;
        return fBuffer.fBuffer;
    }

    unsigned int getLen() const
    {
        return fBuffer.fIndex;
    }

    bool isEmpty() const
    {
        return (fBuffer.fIndex == 0);
    }

    void reset()
    {
        fBuffer.reset();
    }

    void set(const XMLCh* const chars, const unsigned int count = 0)
    {
        fBuffer.set(chars, count);
    }


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLBufBid(const XMLBufBid&);
    XMLBufBid& operator=(const XMLBufBid&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fBuffer
    //      This is the buffer we got, and which we will release.
    //
    //  fMgr
    //      This is the buffer manager we got the buffer from. This is needed
    //      to release the buffer later.
    // -----------------------------------------------------------------------
    XMLBuffer&          fBuffer;
    XMLBufferMgr* const fMgr;
};

XERCES_CPP_NAMESPACE_END

#endif
