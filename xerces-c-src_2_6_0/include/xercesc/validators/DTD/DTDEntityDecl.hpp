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
 * $Log: DTDEntityDecl.hpp,v $
 * Revision 1.6  2004/09/08 13:56:50  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.5  2003/10/10 16:24:51  peiyongz
 * Implementation of Serialization/Deserialization
 *
 * Revision 1.4  2003/05/16 21:43:19  knoaman
 * Memory manager implementation: Modify constructors to pass in the memory manager.
 *
 * Revision 1.3  2003/03/07 18:17:12  tng
 * Return a reference instead of void for operator=
 *
 * Revision 1.2  2002/11/04 14:50:40  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:43  peiyongz
 * sane_include
 *
 * Revision 1.4  2000/02/24 20:16:49  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.3  2000/02/09 21:42:37  abagchi
 * Copyright swat
 *
 * Revision 1.2  2000/01/20 01:57:07  rahulj
 * Reported by marc@ist.de
 * Removed extra 'const' qualifiers.
 *
 * Revision 1.1.1.1  1999/11/09 01:03:34  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:45:40  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */


#if !defined(DTDENTITYDECL_HPP)
#define DTDENTITYDECL_HPP

#include <xercesc/framework/XMLEntityDecl.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  This is a derivative of the abstract version of an entity decl in the
//  framework directory. We just need to provide implementation of a couple
//  of methods.
//
class VALIDATORS_EXPORT DTDEntityDecl : public XMLEntityDecl
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    DTDEntityDecl(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);
    DTDEntityDecl
    (
        const   XMLCh* const   entName
        , const bool           fromIntSubset = false
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    DTDEntityDecl
    (
        const   XMLCh* const   entName
        , const XMLCh* const   value
        , const bool           fromIntSubset = false
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    DTDEntityDecl
    (
        const   XMLCh* const    entName
        , const XMLCh           value
        , const bool            fromIntSubset = false
        , const bool            specialChar = false
    );
    ~DTDEntityDecl();


    // -----------------------------------------------------------------------
    //  Implementation of the virtual XMLEntityDecl interface
    // -----------------------------------------------------------------------
    virtual bool getDeclaredInIntSubset() const;
    virtual bool getIsParameter() const;
    virtual bool getIsSpecialChar() const;


    // -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------
    void setDeclaredInIntSubset(const bool newValue);
    void setIsParameter(const bool newValue);
    void setIsSpecialChar(const bool newValue);

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(DTDEntityDecl)

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    DTDEntityDecl(const DTDEntityDecl&);
    DTDEntityDecl& operator=(DTDEntityDecl&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fDeclaredInIntSubset
    //      Indicates whether the entity was declared in the internal subset
    //      or not. If not, it cannot be referred to from a standalone
    //      document.
    //
    //  fIsParameter
    //      Indicates whether this is a parameter entity or a general entity.
    //
    //  fIsSpecialChar
    //      This indicates that its one of the special character entities,
    //      e.g. lt or gt or amp. We need to know this because there are
    //      places where only a numeric char ref or special char ref is valid
    //      and all others are ignored or illegal.
    // -----------------------------------------------------------------------
    bool    fDeclaredInIntSubset;
    bool    fIsParameter;
    bool    fIsSpecialChar;
};


// ---------------------------------------------------------------------------
//  DTDEntityDecl: Constructors and Destructor
// ---------------------------------------------------------------------------
inline DTDEntityDecl::DTDEntityDecl(MemoryManager* const manager) :

    XMLEntityDecl(manager)
    , fDeclaredInIntSubset(false)
    , fIsParameter(false)
    , fIsSpecialChar(false)
{
}

inline DTDEntityDecl::DTDEntityDecl( const XMLCh* const   entName
                                   , const bool           fromIntSubset
                                   , MemoryManager* const manager) :

    XMLEntityDecl(entName, manager)
    , fDeclaredInIntSubset(fromIntSubset)
    , fIsParameter(false)
    , fIsSpecialChar(false)
{
}

inline DTDEntityDecl::DTDEntityDecl( const XMLCh* const   entName
                                   , const XMLCh* const   value
                                   , const bool           fromIntSubset
                                   , MemoryManager* const manager) :
    XMLEntityDecl(entName, value, manager)
    , fDeclaredInIntSubset(fromIntSubset)
    , fIsParameter(false)
    , fIsSpecialChar(false)
{
}

inline DTDEntityDecl::DTDEntityDecl(const   XMLCh* const    entName
                                    , const XMLCh           value
                                    , const bool            fromIntSubset
                                    , const bool            specialChar) :
    XMLEntityDecl(entName, value, XMLPlatformUtils::fgMemoryManager)
    , fDeclaredInIntSubset(fromIntSubset)
    , fIsParameter(false)
    , fIsSpecialChar(specialChar)
{
}

inline DTDEntityDecl::~DTDEntityDecl()
{
}


// ---------------------------------------------------------------------------
//  DTDEntityDecl: Getter methods
// ---------------------------------------------------------------------------
inline bool DTDEntityDecl::getDeclaredInIntSubset() const
{
    return fDeclaredInIntSubset;
}

inline bool DTDEntityDecl::getIsParameter() const
{
    return fIsParameter;
}

inline bool DTDEntityDecl::getIsSpecialChar() const
{
    return fIsSpecialChar;
}


// ---------------------------------------------------------------------------
//  DTDEntityDecl: Setter methods
// ---------------------------------------------------------------------------
inline void DTDEntityDecl::setDeclaredInIntSubset(const bool newValue)
{
    fDeclaredInIntSubset = newValue;
}

inline void DTDEntityDecl::setIsParameter(const bool newValue)
{
    fIsParameter = newValue;
}

inline void DTDEntityDecl::setIsSpecialChar(const bool newValue)
{
    fIsSpecialChar = newValue;
}

XERCES_CPP_NAMESPACE_END

#endif
