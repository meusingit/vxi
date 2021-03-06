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
 * $Id: MacOSUnicodeConverter.hpp,v 1.12 2004/09/08 13:56:46 peiyongz Exp $
 */

#ifndef MACOSUNICODECONVERTER_HPP
#define MACOSUNICODECONVERTER_HPP

#include <cstddef>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/Mutexes.hpp>

#if defined(__APPLE__)
    //	Framework includes from ProjectBuilder
    #include <CoreServices/CoreServices.h>
#else
    //	Classic includes otherwise
    #include <UnicodeConverter.h>
#endif

XERCES_CPP_NAMESPACE_BEGIN

//
//  The transcoding service has to provide a couple of required string
//  and character operations, but its most important service is the creation
//  of transcoder objects. There are two types of transcoders, which are
//  discussed below in the XMLTranscoder class' description.
//
class XMLUTIL_EXPORT MacOSUnicodeConverter : public XMLTransService
{
public :
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    ~MacOSUnicodeConverter();

    // -----------------------------------------------------------------------
    //  Implementation of the virtual transcoding service API
    // -----------------------------------------------------------------------
    virtual int compareIString
    (
        const   XMLCh* const    comp1
        , const XMLCh* const    comp2
    );

    virtual int compareNIString
    (
        const   XMLCh* const    comp1
        , const XMLCh* const    comp2
        , const unsigned int    maxChars
    );

    virtual const XMLCh* getId() const;

    virtual bool isSpace(const XMLCh toCheck) const;

    virtual XMLLCPTranscoder* makeNewLCPTranscoder();

    virtual bool supportsSrcOfs() const;

    virtual void upperCase(XMLCh* const toUpperCase) const;
    virtual void lowerCase(XMLCh* const toLowerCase) const;

protected :
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    MacOSUnicodeConverter();

    // -----------------------------------------------------------------------
    //  Protected virtual methods
    // -----------------------------------------------------------------------
    virtual XMLTranscoder* makeNewXMLTranscoder
    (
        const   XMLCh* const            encodingName
        ,       XMLTransService::Codes& resValue
        , const unsigned int            blockSize
        ,       MemoryManager* const    manager
    );
    virtual XMLTranscoder* makeNewXMLTranscoder
    (
        const   XMLCh* const            encodingName
        ,       XMLTransService::Codes& resValue
        , const unsigned int            blockSize
        ,		TextEncoding			textEncoding
        ,       MemoryManager* const    manager
    );

    //	Sniff for available functionality
    static bool IsMacOSUnicodeConverterSupported(void);


private :
	friend class XMLPlatformUtils;
	
	static const XMLCh fgMyServiceId[];			// Name of the our unicode converter
	static const XMLCh fgMacLCPEncodingName[];	// Name of the LCP transcoder we create

	bool	mHasUnicodeCollation;	// True if unicode collation is available
	
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    MacOSUnicodeConverter(const MacOSUnicodeConverter&);
    MacOSUnicodeConverter& operator=(const MacOSUnicodeConverter&);

    // -----------------------------------------------------------------------
    //  Private methods
    // -----------------------------------------------------------------------
	void ConvertWideToNarrow(const XMLCh* wide, char* narrow, std::size_t maxChars);
	
	//  Figure out what text encoding to use for LCP transcoder
	TextEncoding discoverLCPEncoding();

};


//
//  This type of transcoder is for non-local code page encodings, i.e.
//  named encodings. These are used internally by the scanner to internalize
//  raw XML into the internal Unicode format, and by writer classes to
//  convert that internal Unicode format (which comes out of the parser)
//  back out to a format that the receiving client code wants to use.
//
class XMLUTIL_EXPORT MacOSTranscoder : public XMLTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    MacOSTranscoder(
	    const XMLCh* const		encodingName,
	    TECObjectRef			textToUnicode,
	    TECObjectRef			unicodeToText,
	    const unsigned int		blockSize,
	    MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
		);
    ~MacOSTranscoder();


    // -----------------------------------------------------------------------
    //  The virtual transcoding interface
    // -----------------------------------------------------------------------
    virtual unsigned int transcodeFrom
    (
        const   XMLByte* const          srcData
        , const unsigned int            srcCount
        ,       XMLCh* const            toFill
        , const unsigned int            maxChars
        ,       unsigned int&           bytesEaten
        ,       unsigned char* const    charSizes
    );

    virtual unsigned int transcodeTo
    (
        const   XMLCh* const    srcData
        , const unsigned int    srcCount
        ,       XMLByte* const  toFill
        , const unsigned int    maxBytes
        ,       unsigned int&   charsEaten
        , const UnRepOpts       options
    );

    virtual bool canTranscodeTo
    (
        const   unsigned int    toCheck
    )   const;




private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    MacOSTranscoder(const MacOSTranscoder&);
    MacOSTranscoder& operator=(const MacOSTranscoder&);

    // -----------------------------------------------------------------------
    //  Private members
    // -----------------------------------------------------------------------
    TECObjectRef	mTextToUnicode;
    TECObjectRef	mUnicodeToText;
};



//
//  This class is a specialized transcoder that only transcodes between
//  the internal XMLCh format and the local code page. It is specialized
//  for the very common job of translating data from the client app's
//  native code page to the internal format and vice versa.
//
class XMLUTIL_EXPORT MacOSLCPTranscoder : public XMLLCPTranscoder
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    MacOSLCPTranscoder(XMLTranscoder* const	transcoder, MemoryManager* const manager);
    ~MacOSLCPTranscoder();


    // -----------------------------------------------------------------------
    //  The virtual transcoder API
    //
    //  NOTE:   All these APIs don't include null terminator characters in
    //          their parameters. So calcRequiredSize() returns the number
    //          of actual chars, not including the null. maxBytes and maxChars
    //          parameters refer to actual chars, not including the null so
    //          its assumed that the buffer is physically one char or byte
    //          larger.
    // -----------------------------------------------------------------------
    virtual unsigned int calcRequiredSize(const char* const srcText
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    virtual unsigned int calcRequiredSize(const XMLCh* const srcText
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    virtual char* transcode(const XMLCh* const toTranscode);
    virtual char* transcode(const XMLCh* const toTranscode,
                            MemoryManager* const manager);

    virtual XMLCh* transcode(const char* const toTranscode);
    virtual XMLCh* transcode(const char* const toTranscode,
                            MemoryManager* const manager);

    virtual bool transcode
    (
        const   char* const     toTranscode
        ,       XMLCh* const    toFill
        , const unsigned int    maxChars
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    virtual bool transcode
    (
        const   XMLCh* const    toTranscode
        ,       char* const     toFill
        , const unsigned int    maxChars
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    MacOSLCPTranscoder(const MacOSLCPTranscoder&);
    MacOSLCPTranscoder& operator=(const MacOSLCPTranscoder&);

    // -----------------------------------------------------------------------
    //  Private data members
    // -----------------------------------------------------------------------
    XMLTranscoder* const	mTranscoder;
	MemoryManager* const	mManager;
	XMLMutex				mMutex;			// Mutex to enable rentrancy of LCP transcoder
 };

XERCES_CPP_NAMESPACE_END

#endif
