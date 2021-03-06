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
 * $Log: XSerializeEngine.hpp,v $
 * Revision 1.18  2004/09/08 13:56:14  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.17  2004/03/05 22:21:45  peiyongz
 * readBytes()/writeBytes between BinOutputStream/BinInputStream and
 * XSerializeEngine will always be the full size of the buffer to maintain the exact
 * position for aligned data.
 *
 * Revision 1.16  2004/03/01 23:19:03  peiyongz
 * Grant XSerializeEngine access to GrammarPool
 *
 * Revision 1.15  2004/02/20 20:57:39  peiyongz
 * Bug#27046: path from David Bertoni
 *
 * Revision 1.14  2004/02/11 20:38:50  peiyongz
 * Fix to bug#26864, thanks to David Bertoni.
 *
 * Revision 1.13  2004/01/29 11:46:30  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.12  2004/01/16 21:55:18  peiyongz
 * maintain the same size on both 32/64 bit architecture
 *
 * Revision 1.11  2004/01/15 23:42:32  peiyongz
 * proper allignment for built-in datatype read/write
 *
 * Revision 1.10  2003/12/17 00:18:34  cargilld
 * Update to memory management so that the static memory manager (one used to call Initialize) is only for static data.
 *
 * Revision 1.9  2003/11/25 20:37:40  jberry
 * Cleanup build errors/warnings from CodeWarrior
 *
 * Revision 1.8  2003/11/11 22:48:13  knoaman
 * Serialization of XSAnnotation.
 *
 * Revision 1.7  2003/10/17 21:09:03  peiyongz
 * renaming methods
 *
 * Revision 1.6  2003/10/14 15:18:20  peiyongz
 * getMemoryManager()
 *
 * Revision 1.5  2003/10/09 19:11:53  peiyongz
 * Fix to linkage error on Solaris
 *
 * Revision 1.4  2003/10/07 19:38:31  peiyongz
 * API for Template_Class Object Serialization/Deserialization
 *
 * Revision 1.3  2003/09/25 22:22:00  peiyongz
 * Introduction of readString/writeString
 *
 * Revision 1.2  2003/09/19 04:29:11  neilg
 * fix compilation problems under GCC
 *
 * Revision 1.1  2003/09/18 18:31:24  peiyongz
 * OSU: Object Serialization Utilities
 *
 * $Id: XSerializeEngine.hpp,v 1.18 2004/09/08 13:56:14 peiyongz Exp $
 *
 */

#if !defined(XSERIALIZE_ENGINE_HPP)
#define XSERIALIZE_ENGINE_HPP

#include <xercesc/util/RefHashTableOf.hpp>
#include <xercesc/util/ValueVectorOf.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>

#include <xercesc/internal/XSerializationException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XSerializable;
class XProtoType;
class MemoryManager;
class XSerializedObjectId;
class BinOutputStream;
class BinInputStream;
class XMLGrammarPool;
class XMLStringPool;

class XMLUTIL_EXPORT XSerializeEngine
{
public:

    enum { mode_Store
         , mode_Load 
    };
    

    static const bool toReadBufferLen;

    typedef unsigned int   XSerializedObjectId_t;

    /***
      *
      *  Destructor 
      *
      ***/
    ~XSerializeEngine();

    /***
      *
      *  Constructor for de-serialization(loading)
      *
      *  Application needs to make sure that the instance of
      *  BinInputStream, persists beyond the life of this
      *  SerializeEngine.
      *
      *  Param
      *     inStream         input stream
      *     gramPool         Grammar Pool
      *     bufSize          the size of the internal buffer
      *
      ***/
    XSerializeEngine(BinInputStream*         inStream
                   , XMLGrammarPool* const   gramPool
                   , unsigned long           bufSize = 8192 );


    /***
      *
      *  Constructor for serialization(storing)
      *
      *  Application needs to make sure that the instance of
      *  BinOutputStream, persists beyond the life of this
      *  SerializeEngine.
      *
      *  Param
      *     outStream        output stream
      *     gramPool         Grammar Pool
      *     bufSize          the size of the internal buffer
      *
      ***/
    XSerializeEngine(BinOutputStream*        outStream
                   , XMLGrammarPool* const   gramPool
                   , unsigned long           bufSize = 8192 );


    /***
      *
      *  Deprecated
      *
      *  Constructor for de-serialization(loading)
      *
      *  Application needs to make sure that the instance of
      *  BinInputStream, persists beyond the life of this
      *  SerializeEngine.
      *
      *  Param
      *     inStream         input stream
      *     manager          MemoryManager
      *     bufSize          the size of the internal buffer
      *
      ***/
    XSerializeEngine(BinInputStream*         inStream
                   , MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
                   , unsigned long           bufSize = 8192 );

    
    /***
      *
      *  Deprecated
      *
      *  Constructor for serialization(storing)
      *
      *  Application needs to make sure that the instance of
      *  BinOutputStream, persists beyond the life of this
      *  SerializeEngine.
      *
      *  Param
      *     outStream        output stream
      *     manager          MemoryManager
      *     bufSize          the size of the internal buffer
      *
      ***/
    XSerializeEngine(BinOutputStream*        outStream
                   , MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
                   , unsigned long           bufSize = 8192 );

    /***
      *
      *  When serialization, flush out the internal buffer
      *
      *  Return: 
      *
      ***/
    void flush();

    /***
      *
      *  Checking if the serialize engine is doing serialization(storing)
      *
      *  Return: true, if it is 
      *          false, otherwise
      *
      ***/
    inline bool isStoring() const;

    /***
      *
      *  Checking if the serialize engine is doing de-serialization(loading)
      *
      *  Return: true, if it is 
      *          false, otherwise
      *
      ***/
    inline bool isLoading() const;

    /***
      *
      *  Get the GrammarPool
      *
      *  Return: XMLGrammarPool
      *
      ***/
    XMLGrammarPool* getGrammarPool() const;

    /***
      *
      *  Get the StringPool
      *
      *  Return: XMLStringPool
      *
      ***/
    XMLStringPool* getStringPool() const;

    /***
      *
      *  Get the embeded Memory Manager
      *
      *  Return: MemoryManager
      *
      ***/
    MemoryManager* getMemoryManager() const;

    /***
      *
      *  Write object to the internal buffer.
      *
      *  Param
      *     objectToWrite:    the object to be serialized
      *
      *  Return:
      *
      ***/
           void           write(XSerializable* const objectToWrite);

    /***
      *
      *  Write prototype info to the internal buffer.
      *
      *  Param
      *     protoType:    instance of prototype
      *
      *  Return:
      *
      ***/
           void           write(XProtoType* const protoType);

    /***
      *
      *  Write a stream of XMLByte to the internal buffer.
      *
      *  Param
      *     toWrite:   the stream of XMLByte to write
      *     writeLen:  the length of the stream
      *
      *  Return:
      *
      ***/
           void           write(const XMLByte* const toWrite
                               ,      int            writeLen);

    /***
      *
      *  Write a stream of XMLCh to the internal buffer.
      *
      *  Param
      *     toWrite:   the stream of XMLCh to write
      *     writeLen:  the length of the stream
      *
      *  Return:
      *
      ***/
           void           write(const XMLCh* const toWrite
                               ,      int          writeLen);

    /***
      *
      *  Write a stream of XMLCh to the internal buffer.
      *
      *  Write the bufferLen first if requested, then the length
      *  of the stream followed by the stream.
      *
      *  Param
      *     toWrite:        the stream of XMLCh to write
      *     bufferLen:      the maximum size of the buffer
      *     toWriteBufLen:  specify if the bufferLen need to be written or not
      *
      *  Return:
      *
      ***/
           void           writeString(const XMLCh* const toWrite
                                    , const int          bufferLen = 0
                                    , bool               toWriteBufLen = false);

    /***
      *
      *  Write a stream of XMLByte to the internal buffer.
      *
      *  Write the bufferLen first if requested, then the length
      *  of the stream followed by the stream.
      *
      *  Param
      *     toWrite:        the stream of XMLByte to write
      *     bufferLen:      the maximum size of the buffer
      *     toWriteBufLen:  specify if the bufferLen need to be written or not
      *
      *  Return:
      *
      ***/
           void           writeString(const XMLByte* const toWrite
                                    , const int            bufferLen = 0
                                    , bool                 toWriteBufLen = false);

    static const bool toWriteBufferLen;

    /***
      *
      *  Read/Create object from the internal buffer.
      *
      *  Param
      *     protoType:    an instance of prototype of the object anticipated
      *
      *  Return:          to object read/created
      *
      ***/
	       XSerializable* read(XProtoType* const protoType);

    /***
      *
      *  Read prototype object from the internal buffer.
      *  Verify if the same prototype object found in buffer.
      *
      *  Param
      *     protoType:    an instance of prototype of the object anticipated
      *     objTag:       the object Tag to an existing object
      *
      *  Return:          true  : if matching found
      *                   false : otherwise
      *
      ***/
           bool           read(XProtoType* const    protoType
		                     , XSerializedObjectId_t*       objTag);

    /***
      *
      *  Read XMLByte stream from the internal buffer.
      *
      *  Param
      *     toRead:   the buffer to hold the XMLByte stream
      *     readLen:  the length of the XMLByte to read in
      *
      *  Return:
      *
      ***/
           void           read(XMLByte* const toRead
                             , int            readLen);

    /***
      *
      *  Read XMLCh stream from the internal buffer.
      *
      *  Param
      *     toRead:   the buffer to hold the XMLCh stream
      *     readLen:  the length of the XMLCh to read in
      *
      *  Return:
      *
      ***/
           void           read(XMLCh* const toRead
                             , int          readLen);

    /***
      *
      *  Read a stream of XMLCh from the internal buffer.
      *
      *  Read the bufferLen first if requested, then the length
      *  of the stream followed by the stream.
      *
      *  Param
      *     toRead:       the pointer to the buffer to hold the XMLCh stream
      *     bufferLen:    the size of the buffer created
      *     dataLen:       the length of the stream
      *     toReadBufLen: specify if the bufferLen need to be read or not
      *
      *  Return:
      *
      ***/
           void           readString(XMLCh*&        toRead
                                   , int&           bufferLen
                                   , int&           dataLen
                                   , bool           toReadBufLen = false);

     /***
       *
       *  Read a stream of XMLCh from the internal buffer.
       *
       *  Read the bufferLen first if requested, then the length
       *  of the stream followed by the stream.
       *
       *  Param
       *     toRead:       the pointer to the buffer to hold the XMLCh stream
       *     bufferLen:    the size of the buffer created
       *
       *  Return:
       *
       ***/
            inline void     readString(XMLCh*&        toRead
                                    , int&            bufferLen);
 
     /***
       *
       *  Read a stream of XMLCh from the internal buffer.
       *
       *  Param
       *     toRead:       the pointer to the buffer to hold the XMLCh stream
       *
       *  Return:
       *
       ***/
            inline void      readString(XMLCh*&        toRead);

    /***
      *
      *  Read a stream of XMLByte from the internal buffer.
      *
      *  Read the bufferLen first if requested, then the length
      *  of the stream followed by the stream.
      *
      *  Param
      *     toRead:       the pointer to the buffer to hold the XMLByte stream
      *     bufferLen:    the size of the buffer created
      *     dataLen:       the length of the stream
      *     toReadBufLen: specify if the bufferLen need to be read or not
      *
      *  Return:
      *
      ***/
           void           readString(XMLByte*&      toRead
                                   , int&           bufferLen
                                   , int&           dataLen
                                   , bool           toReadBufLen = false);


     /***
       *
       *  Read a stream of XMLByte from the internal buffer.
       *
       *  Read the bufferLen first if requested, then the length
       *  of the stream followed by the stream.
       *
       *  Param
       *     toRead:       the pointer to the buffer to hold the XMLByte stream
       *     bufferLen:    the size of the buffer created
       *
       *  Return:
       *
       ***/
            inline void       readString(XMLByte*&      toRead
                                       , int&           bufferLen);
 
     /***
       *
       *  Read a stream of XMLByte from the internal buffer.
       *
       *  Read the bufferLen first if requested, then the length
       *  of the stream followed by the stream.
       *
       *  Param
       *     toRead:       the pointer to the buffer to hold the XMLByte stream
       *     bufferLen:    the size of the buffer created
       *     dataLen:       the length of the stream
       *     toReadBufLen: specify if the bufferLen need to be read or not
       *
       *  Return:
       *
       ***/
            inline void       readString(XMLByte*&      toRead);

    /***
      *
      *  Check if the template object has been stored or not
      *
      *  Param
      *    objectPtr:     the template object pointer
      *
      *  Return:          true  : the object has NOT been stored yet
      *                   false : otherwise
      *
      ***/
           bool           needToStoreObject(void* const templateObjectToWrite);

    /***
      *
      *  Check if the template object has been loaded or not
      *
      *  Param
      *    objectPtr:     the address of the template object pointer
      *
      *  Return:          true  : the object has NOT been loaded yet
      *                   false : otherwise
      *
      ***/
           bool           needToLoadObject(void**       templateObjectToRead);

    /***
      *
      *  In the case of needToLoadObject() return true, the client
      *  application needs to instantiate an expected template object, and
      *  register the address to the engine.
      *
      *  Param
      *    objectPtr:     the template object pointer newly instantiated
      *
      *  Return:  
      *
      ***/
           void           registerObject(void* const templateObjectToRegister);

    /***
      *
      *  Insertion operator for serializable classes
      *
      ***/

	friend XSerializeEngine& operator<<(XSerializeEngine&
                                      , XSerializable* const );

    /***
      *
      *  Insertion operators for 
      *     . basic Xerces data types
      *     . built-in types 
      *
      ***/
           XSerializeEngine& operator<<(XMLByte);
           XSerializeEngine& operator<<(XMLCh);

           XSerializeEngine& operator<<(char);
           XSerializeEngine& operator<<(short);
           XSerializeEngine& operator<<(int);
           XSerializeEngine& operator<<(unsigned int);
           XSerializeEngine& operator<<(long);
           XSerializeEngine& operator<<(unsigned long);
           XSerializeEngine& operator<<(float);
           XSerializeEngine& operator<<(double);
           XSerializeEngine& operator<<(bool);

    /***
      *
      *  Extraction operators for 
      *     . basic Xerces data types
      *     . built-in types 
      *
      ***/
           XSerializeEngine& operator>>(XMLByte&);
           XSerializeEngine& operator>>(XMLCh&);

           XSerializeEngine& operator>>(char&);
           XSerializeEngine& operator>>(short&);
           XSerializeEngine& operator>>(int&);
           XSerializeEngine& operator>>(unsigned int&);
           XSerializeEngine& operator>>(long&);
           XSerializeEngine& operator>>(unsigned long&);
           XSerializeEngine& operator>>(float&);
           XSerializeEngine& operator>>(double&);
           XSerializeEngine& operator>>(bool&);

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
	XSerializeEngine();
    XSerializeEngine(const XSerializeEngine&);
	XSerializeEngine& operator=(const XSerializeEngine&);

    /***
      *
      *   Store Pool Opertions
      *
      ***/
           XSerializedObjectId_t  lookupStorePool(void* const objectPtr) const;
           void                   addStorePool(void* const objectPtr);

    /***
      *
      *   Load Pool Opertions
      *
      ***/
           XSerializable* lookupLoadPool(XSerializedObjectId_t objectTag) const;
           void           addLoadPool(void* const objectPtr);
   
    /***
      *   
      *    Intenal Buffer Operations
      *
      ***/
    inline void           checkAndFillBuffer(int bytesNeedToRead);

    inline void           checkAndFlushBuffer(int bytesNeedToWrite);

           void           fillBuffer();

           void           flushBuffer();

           void           pumpCount();

    /***
      *   
      *    Helper
      *
      ***/
    inline void            ensureStoring()                          const;

    inline void            ensureLoading()                          const;

    inline void            ensureStoreBuffer()                      const;

    inline void            ensureLoadBuffer()                       const;

    inline void            ensurePointer(void* const)               const;

    inline void            ensureBufferLen(int  bufferLen)          const;

    inline void            Assert(bool  toEval
                                , const XMLExcepts::Codes toThrow)  const;

    inline size_t          allignAdjust()                           const;

    inline void            allignBufCur();

    // Make XTemplateSerializer friend of XSerializeEngine so that
    // we can call lookupStorePool and lookupLoadPool in the case of
    // annotations.
    friend class XTemplateSerializer;

    // -------------------------------------------------------------------------------
    //  data
    //
    //  fStoreLoad: 
    //               Indicator: storing(serialization) or loading(de-serialization)
    //
    //  fGrammarPool:
    //               Thw owning GrammarPool which instantiate this SerializeEngine 
    //               instance
    //
    //  fInputStream:
    //               Binary stream to read from (de-serialization), provided
    //               by client application, not owned.
    //
    //  fOutputStream:
    //               Binary stream to write to (serialization), provided 
    //               by client application, not owned.
    //
    //  fBufSize:
    //               The size of the internal buffer
    //
    //  fBufStart/fBufEnd:
    //               
    //               The internal buffer.
    //  fBufEnd:
    //               one beyond the last valid cell
    //               fBufEnd === (fBufStart + fBufSize)
    //
    //  fBufCur:
    //               The cursor of the buffer
    //
    //  fBufLoadMax:
    //               Indicating the end of the valid content in the buffer
    //
    //  fStorePool:
    //                Object collection for storing
    //
    //  fLoadPool:
    //                Object collection for loading
    //
    //  fMapCount:
    // -------------------------------------------------------------------------------
    const short                            fStoreLoad;  
    XMLGrammarPool*  const                 fGrammarPool;
    BinInputStream*  const                 fInputStream;
    BinOutputStream* const                 fOutputStream;

    //buffer
    const unsigned long                    fBufSize;
	XMLByte* const                         fBufStart;
	XMLByte* const                         fBufEnd; 
    XMLByte*                               fBufCur;
    XMLByte*                               fBufLoadMax; 

    /***
     *   Map for storing object
     *
     *   key:   XSerializable*
     *          XProtoType*
     *
     *   value: XMLInteger*, owned
     *
     ***/
    RefHashTableOf<XSerializedObjectId>*   fStorePool;  

    /***
     *   Vector for loading object, objects are NOT owned
     *
     *   data:   XSerializable*
     *           XProtoType*
     *
     ***/
    ValueVectorOf<void*>*                  fLoadPool;    

    /***
     *   object counter
     ***/
	XSerializedObjectId_t                  fObjectCount;
};

inline bool XSerializeEngine::isStoring() const
{
    return (fStoreLoad == mode_Store);
}

inline bool XSerializeEngine::isLoading() const
{
    return (fStoreLoad == mode_Load);
}

inline XSerializeEngine& operator<<(XSerializeEngine&       serEng
                                  , XSerializable* const    serObj)
{
	serEng.write(serObj); 
    return serEng; 
}

inline void XSerializeEngine::ensureStoring() const
{
	Assert(isStoring(), XMLExcepts::XSer_Storing_Violation);
}

inline void XSerializeEngine::ensureLoading() const
{
	Assert(isLoading(), XMLExcepts::XSer_Loading_Violation);
}



inline void XSerializeEngine::Assert(bool toEval
                                   , const XMLExcepts::Codes toThrow) const
{
    if (!toEval)
    {
        ThrowXMLwithMemMgr(XSerializationException, toThrow, getMemoryManager());  
    }

}

// For the following built-in datatype, we assume
// the same allignment requirement
//
// short    unsigned short
// int      unsigned long
// long     unsigned long
// float
// double
//
// Based on the current position (fBufCur), calculated the needed size
// to read/write
//
inline size_t XSerializeEngine::allignAdjust() const
{
	#ifdef XML_PLATFORM_NEW_BLOCK_ALIGNMENT
		size_t alignment = XML_PLATFORM_NEW_BLOCK_ALIGNMENT;
	#else
		size_t alignment = (sizeof(void*) >= sizeof(double)) ? sizeof(void*) : sizeof(double);
	#endif
	
	size_t remainder = (size_t) fBufCur % alignment;	
	return (remainder == 0) ? 0 : (alignment - remainder);
}

// Adjust the fBufCur
inline void XSerializeEngine::allignBufCur()
{
    fBufCur+=allignAdjust();
}

inline void XSerializeEngine::readString(XMLCh*&        toRead
                                       , int&           bufferLen)
{
    int  dummyDataLen;                
    readString(toRead, bufferLen, dummyDataLen);
}

inline void XSerializeEngine::readString(XMLCh*&        toRead)
{
    int  dummyBufferLen;
    int  dummyDataLen;
    readString(toRead, dummyBufferLen, dummyDataLen);
}

inline void XSerializeEngine::readString(XMLByte*&      toRead
                                       , int&           bufferLen)
{
    int  dummyDataLen;
    readString(toRead, bufferLen, dummyDataLen);
}

inline void XSerializeEngine::readString(XMLByte*&      toRead)
{
    int  dummyBufferLen;
    int  dummyDataLen;
    readString(toRead, dummyBufferLen, dummyDataLen);
}

/***
 *  Ought to be nested class
 ***/
class XSerializedObjectId : public XMemory
{
public:

    ~XSerializedObjectId(){};

private:

    inline XSerializedObjectId(XSerializeEngine::XSerializedObjectId_t val):
        fData(val) { };

    inline XSerializeEngine::XSerializedObjectId_t getValue() const {return fData; };

    friend class XSerializeEngine;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
	XSerializedObjectId();
    XSerializedObjectId(const XSerializedObjectId&);
	XSerializedObjectId& operator=(const XSerializedObjectId&);

    XSerializeEngine::XSerializedObjectId_t    fData;

};


XERCES_CPP_NAMESPACE_END

#endif
