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
 * $Log: CoreTests_RefHashTable.cpp,v $
 * Revision 1.8  2004/09/08 13:57:05  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.7  2003/05/30 13:08:26  gareth
 * move over to macros for std:: and iostream/iostream.h issues.
 *
 * Revision 1.6  2003/02/05 18:55:21  tng
 * [Bug 11915] Utility for freeing memory.
 *
 * Revision 1.5  2002/02/01 22:46:28  peiyongz
 * sane_include
 *
 * Revision 1.4  2000/03/02 19:55:48  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.3  2000/02/06 07:48:39  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.2  2000/01/19 00:59:06  roddey
 * Get rid of dependence on old utils output streams.
 *
 * Revision 1.1.1.1  1999/11/09 01:01:54  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:42:27  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

// ---------------------------------------------------------------------------
//  XML4C2 includes
// ---------------------------------------------------------------------------
#include "CoreTests.hpp"
#include <xercesc/util/RefHashTableOf.hpp>


// ---------------------------------------------------------------------------
//  A simple class to test the ref hash table with
// ---------------------------------------------------------------------------
class TestElem
{
    public :
        TestElem(   const   XMLCh* const    key
                    , const unsigned int    value1
                    , const double          value2) :
            fKey(XMLString::replicate(key))
            , fValue1(value1)
            , fValue2(value2)
        {
        }

        ~TestElem()
        {
            XMLString::release(&fKey);
        }

        const XMLCh* getKey() const
        {
            return fKey;
        }


    private :
        XMLCh*          fKey;
        unsigned int    fValue1;
        double          fValue2;
};


// ---------------------------------------------------------------------------
//  Force a full instantiation of our hashtable, and its enumerator, just to
//  insure that all methods get instantiated and compiled.
// ---------------------------------------------------------------------------
template RefHashTableOf<TestElem>;
template RefHashTableOfEnumerator<TestElem>;



// ---------------------------------------------------------------------------
//  Local testing methods
// ---------------------------------------------------------------------------
static bool basicTests()
{

    return true;
}


// ---------------------------------------------------------------------------
//  Test entry point
// ---------------------------------------------------------------------------
bool testRefHashTable()
{
    XERCES_STD_QUALIFIER wcout  << L"----------------------------------\n"
                << L"Testing RefHashTableOf class\n"
                << L"----------------------------------" << XERCES_STD_QUALIFIER endl;

    bool retVal = true;

    try
    {
        XERCES_STD_QUALIFIER wcout << L"Testing basic RefHashtable methods" << XERCES_STD_QUALIFIER endl;
        if (!basicTests())
        {
            XERCES_STD_QUALIFIER wcout  << L"RefHashtable basic test methods failed"
                        << XERCES_STD_QUALIFIER endl;
            retVal = false;
        }
         else
        {
            XERCES_STD_QUALIFIER wcout << L"RefHashtable basic tests passed" << XERCES_STD_QUALIFIER endl;
        }
        XERCES_STD_QUALIFIER wcout << XERCES_STD_QUALIFIER endl;
    }

    catch(const XMLException& toCatch)
    {
        XERCES_STD_QUALIFIER wcout  << L"  ERROR: Unexpected exception!\n   Msg: "
                    << toCatch.getMessage() << XERCES_STD_QUALIFIER endl;
        return false;
    }
    return retVal;
}
