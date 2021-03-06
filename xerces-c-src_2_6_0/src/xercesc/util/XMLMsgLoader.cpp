/*
 * Copyright 1999-2002,2004 The Apache Software Foundation.
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
 *  $Id: XMLMsgLoader.cpp,v 1.5 2004/09/08 13:56:24 peiyongz Exp $
 * $Log: XMLMsgLoader.cpp,v $
 * Revision 1.5  2004/09/08 13:56:24  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.4  2003/12/24 15:24:13  cargilld
 * More updates to memory management so that the static memory manager.
 *
 * Revision 1.3  2003/05/15 19:07:46  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.2  2003/02/17 19:54:47  peiyongz
 * Allow set user specified error message file location in PlatformUtils::Initialize().
 *
 * Revision 1.1  2002/11/04 22:24:21  peiyongz
 * Locale setting for message loader
 *
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/XMLMsgLoader.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/***
 *   The PlatformUtils::initialize() would set fLocale
 *   to either a user-privded string or 0
 *
 ***/
char* XMLMsgLoader::fLocale = 0;

char* XMLMsgLoader::fPath = 0;

XMLCh XMLMsgLoader::fLanguage[] = {chLatin_e, chLatin_n, chNull};

/***
 *  if localeToAdopt is 0, that is to release memory for
 *  the user defined locale string
 *
 ***/
void  XMLMsgLoader::setLocale(const char* const localeToAdopt)
{
    /***
     * Release the current setting's memory, if any
     ***/
	if (fLocale)
	{
        XMLPlatformUtils::fgMemoryManager->deallocate(fLocale);//delete [] fLocale;
		fLocale = 0;
	}

    /***
     *  
     *  REVISIT: later we may do locale format checking
     * 
     *           refer to phttp://oss.software.ibm.com/icu/userguide/locale.html
     *           for details.
     */
	if (localeToAdopt)
	{
		fLocale   = XMLString::replicate(localeToAdopt, XMLPlatformUtils::fgMemoryManager);
        XMLString::transcode(fLocale, fLanguage, 2, XMLPlatformUtils::fgMemoryManager);
        fLanguage[2] = 0;
    }

}

const char* XMLMsgLoader::getLocale()
{
	return fLocale;
}

/***
 *  if nlsHomeToAdopt is 0, that is to release memory for
 *  the user defined NLSHome string
 *
 ***/
void  XMLMsgLoader::setNLSHome(const char* const nlsHomeToAdopt)
{
    /***
     * Release the current setting's memory, if any
     ***/
    if (fPath)
    {
        XMLPlatformUtils::fgMemoryManager->deallocate(fPath);//delete [] fPath;
        fPath = 0;
    }

    if (nlsHomeToAdopt)
    {
        fPath = XMLString::replicate(nlsHomeToAdopt, XMLPlatformUtils::fgMemoryManager);
    }

}

const char* XMLMsgLoader::getNLSHome()
{
    return fPath;
}

// ---------------------------------------------------------------------------
//  Deprecated
//
//     These two methods are deprecated.
//  
//     The default implementations for these two methods are provided as is,
//     any specific derivative may change this as and when necessary.
//      
// ---------------------------------------------------------------------------
const XMLCh* XMLMsgLoader::getLanguageName() const
{
    return fLanguage;
}

void XMLMsgLoader::setLanguageName(XMLCh* const)
{
}

XERCES_CPP_NAMESPACE_END
