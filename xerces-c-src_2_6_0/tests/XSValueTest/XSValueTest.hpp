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
 * $Id: XSValueTest.hpp,v 1.3 2004/09/08 13:57:06 peiyongz Exp $
 * $Log: XSValueTest.hpp,v $
 * Revision 1.3  2004/09/08 13:57:06  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.2  2004/08/24 16:00:15  peiyongz
 * To build on AIX/Win2003-ecl
 *
 * Revision 1.1  2004/08/19 17:17:21  peiyongz
 * XSValueTest
 *
 *
 */

#if !defined(XSVALUE_TEST_HPP)
#define XSVALUE_TEST_HPP

// ---------------------------------------------------------------------------
//  Includes for all the program files to see
// ---------------------------------------------------------------------------
#include <xercesc/util/XercesDefs.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

#include <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_USE

// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
    {
        fUnicodeForm = XMLString::replicate(toTranscode);
        fLocalForm   = XMLString::transcode(toTranscode);
    }

    StrX(const char* const toTranscode)
    {
        // Call the private transcoding method
        fLocalForm   = XMLString::replicate(toTranscode);
        fUnicodeForm = XMLString::transcode(toTranscode);
    }

    ~StrX()
    {
        XMLString::release(&fLocalForm);
        XMLString::release(&fUnicodeForm);
    }

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm() const
    {
        return fLocalForm;
    }

    const XMLCh* unicodeForm() const
    {
        return fUnicodeForm;
    }

private :

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    StrX(const StrX&);
    StrX & operator=(const StrX &);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
    char*    fLocalForm;
};

#define UniForm(str) StrX(str).unicodeForm()
#define LocForm(str) StrX(str).localForm()

inline XERCES_STD_QUALIFIER ostream& operator<<(XERCES_STD_QUALIFIER ostream& target, const StrX& toDump)
{
    target << toDump.localForm();
    return target;
}

#endif
