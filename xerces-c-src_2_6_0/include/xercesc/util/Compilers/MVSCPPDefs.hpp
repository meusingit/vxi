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
 * $Log: MVSCPPDefs.hpp,v $
 * Revision 1.9  2004/09/08 13:56:32  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.8  2003/01/30 19:09:50  tng
 * [Bug 3041] wrong PLATFORM_IMPORT in MVSCPPDefs.hpp
 *
 * Revision 1.7  2003/01/20 19:28:52  tng
 * 390: turn on C++ namespace.  Patch from Stephen Dulin.
 *
 * Revision 1.6  2002/11/04 14:45:20  tng
 * C++ Namespace Support.
 *
 * Revision 1.5  2002/08/08 16:40:16  tng
 * 390 Changes from Stephen Dulin.
 *
 * Revision 1.4  2002/05/28 12:57:17  tng
 * Fix typo.
 *
 * Revision 1.3  2002/05/27 18:02:40  tng
 * define XMLSize_t, XMLSSize_t and their associate MAX
 *
 * Revision 1.2  2002/05/21 19:45:53  tng
 * Define DOMSize_t and XMLSize_t
 *
 * Revision 1.1.1.1  2002/02/01 22:22:18  peiyongz
 * sane_include
 *
 * Revision 1.8  2001/03/02 20:53:03  knoaman
 * Schema: Regular expression - misc. updates for error messages,
 * and additions of new functions to XMLString class.
 *
 * Revision 1.7  2000/10/17 00:52:00  andyh
 * Change XMLCh back to unsigned short on all platforms.
 *
 * Revision 1.6  2000/03/09 18:54:44  abagchi
 * Added header-guards to include inlines only once
 *
 * Revision 1.5  2000/03/02 19:55:08  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.4  2000/02/16 22:51:04  abagchi
 * defined PLATFORM_EXPORT to _Export
 *
 * Revision 1.3  2000/02/08 02:32:59  abagchi
 * Changed characters from ASCII to Hex
 *
 * Revision 1.2  2000/02/06 07:48:17  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.1  2000/01/21 22:15:55  abagchi
 * Initial check-in for OS390: added MVSCPPDefs.hpp and MVSCPPDefs.cpp
 *
 * Revision 1.5  2000/01/14 02:28:16  aruna1
 * Added L"string" support for cset compiler
 *
 * Revision 1.4  2000/01/12 19:11:49  aruna1
 * XMLCh now defined to wchar_t
 *
 * Revision 1.3  1999/11/12 20:36:51  rahulj
 * Changed library name to xerces-c.lib.
 *
 * Revision 1.1.1.1  1999/11/09 01:07:31  twl
 * Initial checkin
 *
 * Revision 1.3  1999/11/08 20:45:22  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

#if !defined(MVSCPPDEFS_HPP)
#define MVSCPPDEFS_HPP

// ---------------------------------------------------------------------------
//  Include some runtime files that will be needed product wide
// ---------------------------------------------------------------------------
#include <sys/types.h>  // for size_t and ssize_t
#include <limits.h>  // for MAX of size_t and ssize_t

// ---------------------------------------------------------------------------
//  A define in the build for each project is also used to control whether
//  the export keyword is from the project's viewpoint or the client's.
//  These defines provide the platform specific keywords that they need
//  to do this.
// ---------------------------------------------------------------------------
#define PLATFORM_EXPORT _Export
#define PLATFORM_IMPORT

// ---------------------------------------------------------------------------
//  Indicate that we do not support native bools
//  If the compiler can handle boolean itself, do not define it
// ---------------------------------------------------------------------------
//#define NO_NATIVE_BOOL

// ---------------------------------------------------------------------------
//  Each compiler might support L"" prefixed constants. There are places
//  where it is advantageous to use the L"" where it supported, to avoid
//  unnecessary transcoding.
//  If your compiler does not support it, don't define this.
// ---------------------------------------------------------------------------
#define XML_LSTRSUPPORT

// ---------------------------------------------------------------------------
//  Indicate that we support C++ namespace
//  Do not define it if the compile cannot handle C++ namespace
// ---------------------------------------------------------------------------
#define XERCES_HAS_CPP_NAMESPACE

// ---------------------------------------------------------------------------
//  Define our version of the XML character
// ---------------------------------------------------------------------------
typedef unsigned short XMLCh;
// typedef wchar_t XMLCh;

// ---------------------------------------------------------------------------
//  Define unsigned 16 and 32 bits integers
// ---------------------------------------------------------------------------
typedef unsigned short XMLUInt16;
typedef unsigned int   XMLUInt32;

// ---------------------------------------------------------------------------
//  Define signed 32 bits integers
// ---------------------------------------------------------------------------
typedef int            XMLInt32;

// ---------------------------------------------------------------------------
//  XMLSize_t is the unsigned integral type.
// ---------------------------------------------------------------------------
#if defined(_SIZE_T) && defined(SIZE_MAX) && defined(_SSIZE_T) && defined(SSIZE_MAX)
    typedef size_t              XMLSize_t;
    #define XML_SIZE_MAX        SIZE_MAX
    typedef ssize_t             XMLSSize_t;
    #define XML_SSIZE_MAX       SSIZE_MAX
#else
    typedef unsigned long       XMLSize_t;
    #define XML_SIZE_MAX        ULONG_MAX
    typedef long                XMLSSize_t;
    #define XML_SSIZE_MAX       LONG_MAX
#endif

// ---------------------------------------------------------------------------
//  Force on the Xerces debug token if it was on in the build environment
// ---------------------------------------------------------------------------
#if defined(_DEBUG)
#define XERCES_DEBUG
#endif


// ---------------------------------------------------------------------------
//  Provide some common string ops that are different/notavail on MVSCPP
// ---------------------------------------------------------------------------

//
// This is a upper casing function. Note that this will not cover
// all NLS cases such as European accents etc. but there aren't
// any of these in the current uses of this function in Xerces.
// If this changes in the future, than we can re-address the issue
// at that time.
//
inline char mytoupper(const char toUpper)
{
    if ((toUpper >= 0x61) && (toUpper <= 0x7A))
        return char(toUpper - 0x20);
    return toUpper;
}

inline char mytolower(const char toLower)
{
    if ((toLower >= 0x41) && (toLower <= 0x5A))
        return char(toLower + 0x20);
    return toLower;
}

inline XMLCh mytowupper(const XMLCh toUpper)
{
    if ((toUpper >= 0x61) && (toUpper <= 0x7A))
       return XMLCh(toUpper - 0x20);
    return toUpper;
}

inline XMLCh mytowlower(const XMLCh toLower)
{
    if ((toLower >= 0x41) && (toLower <= 0x5A))
       return XMLCh(toLower + 0x20);
    return toLower;
}

int stricmp(const char* const str1, const char* const  str2);
int strnicmp(const char* const str1, const char* const  str2, const unsigned int count);



// ---------------------------------------------------------------------------
//  The name of the DLL that is built by the MVSCPP version of the system.
// ---------------------------------------------------------------------------
const char* const Xerces_DLLName = "libxerces-c";

#endif  // MVSCPPDEFS_HPP
