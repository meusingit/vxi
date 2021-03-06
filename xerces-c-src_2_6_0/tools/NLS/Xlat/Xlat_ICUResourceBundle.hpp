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
 * $Id: Xlat_ICUResourceBundle.hpp,v 1.2 2004/09/08 13:57:07 peiyongz Exp $
 * $Log: Xlat_ICUResourceBundle.hpp,v $
 * Revision 1.2  2004/09/08 13:57:07  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1  2002/09/30 22:09:28  peiyongz
 * To generate icu resource file (in text) for error message.
 *
 *
 */

#ifndef ICU_RESBUND_FORMATTER_H
#define ICU_RESBUND_FORMATTER_H

class ICUResBundFormatter : public XlatFormatter
{
public :
    // -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
    ICUResBundFormatter();
    virtual ~ICUResBundFormatter();


    // -----------------------------------------------------------------------
    //  Implementation of the formatter interface
    // -----------------------------------------------------------------------
    virtual void endDomain
    (
        const XMLCh* const    domainName
      , const unsigned int    msgCount
    );

    virtual void endMsgType
    (
        const   MsgTypes        type
    );

    virtual void endOutput();

    virtual void nextMessage
    (
          const XMLCh* const    msgText
        , const XMLCh* const    msgId
        , const unsigned int    messageId
        , const unsigned int    curId
    );

    virtual void startDomain
    (
          const XMLCh* const    domainName
        , const XMLCh* const    nameSpace
    );

    virtual void startMsgType
    (
        const   MsgTypes        type
    );

    virtual void startOutput
    (
          const XMLCh* const locale
        , const XMLCh* const outPath
    );


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    ICUResBundFormatter(const ICUResBundFormatter&);
    void operator=(const ICUResBundFormatter&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fOutFl
    //      This is the current output file for the message catalog contents.
    //
    //  fTranscoder
    //      This is our transcoder. We transcode to the local code page in
    //      order to output Unicode based text to the message catalog.
    // -----------------------------------------------------------------------
    FILE*               fOutFl;
    XMLLCPTranscoder*   fTranscoder;
};

#endif

