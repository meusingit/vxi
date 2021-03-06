/*
 * Copyright 2001,2004 The Apache Software Foundation.
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
 * $Id: CharToken.hpp,v 1.5 2004/09/08 13:56:47 peiyongz Exp $
 */

#if !defined(CHARTOKEN_HPP)
#define CHARTOKEN_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/regx/Token.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT CharToken : public Token {
public:
	// -----------------------------------------------------------------------
    //  Public Constructors and Destructor
    // -----------------------------------------------------------------------
	CharToken(const unsigned short tokType, const XMLInt32 ch
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
	~CharToken();

	// -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
	XMLInt32 getChar() const;

	// -----------------------------------------------------------------------
    //  Match methods
    // -----------------------------------------------------------------------
	bool match(const XMLInt32 ch);

private:
	// -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CharToken(const CharToken&);
    CharToken& operator=(const CharToken&);

	// -----------------------------------------------------------------------
    //  Private data members
	// -----------------------------------------------------------------------
	XMLInt32 fCharData;
};


// ---------------------------------------------------------------------------
//  CharToken: getter methods
// ---------------------------------------------------------------------------
inline XMLInt32 CharToken::getChar() const {

	return fCharData;
}


// ---------------------------------------------------------------------------
//  CharToken: getter methods
// ---------------------------------------------------------------------------
inline bool CharToken::match(const XMLInt32 ch){

	return ch == fCharData;
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file CharToken.hpp
  */
