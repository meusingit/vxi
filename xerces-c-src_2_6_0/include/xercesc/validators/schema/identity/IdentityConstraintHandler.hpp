/*
 * Copyright 2004,2004 The Apache Software Foundation.
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
 * $Id: IdentityConstraintHandler.hpp,v 1.2 2004/09/08 13:56:59 peiyongz Exp $
 * $Log: IdentityConstraintHandler.hpp,v $
 * Revision 1.2  2004/09/08 13:56:59  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1  2004/04/13 16:41:17  peiyongz
 * IdentityConstraintHandler
 *
 *
 */

#if !defined(IDENTITYCONSTRAINT_HANDLER_HPP)
#define IDENTITYCONSTRAINT_HANDLER_HPP

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/validators/schema/identity/ValueStoreCache.hpp>
#include <xercesc/validators/schema/identity/XPathMatcherStack.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Forward Declarations
// ---------------------------------------------------------------------------

class XMLScanner;
class FieldActivator;
class MemoryManager;
class XMLElementDecl;

class VALIDATORS_EXPORT IdentityConstraintHandler: public XMemory
{
public:

    // -----------------------------------------------------------------------
    //  Constructors/Destructor
    // -----------------------------------------------------------------------
	virtual ~IdentityConstraintHandler();

    IdentityConstraintHandler
              (
               XMLScanner*   const scanner
             , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
              );

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    inline  int          getMatcherCount() const;

	// -----------------------------------------------------------------------
    //  Setter methods
    // -----------------------------------------------------------------------

	// -----------------------------------------------------------------------
    //  Access methods
    // -----------------------------------------------------------------------
    inline  void         endDocument();

            void         deactivateContext
                             (
                                    SchemaElementDecl* const elem
                            , const XMLCh*             const content
                              );

            void         activateIdentityConstraint
                               (
                                     SchemaElementDecl* const     elem
                             ,       int                          elemDepth
                             , const unsigned int                 uriId
                             , const XMLCh*                 const elemPrefix
                             , const RefVectorOf<XMLAttr>&        attrList
                             , const unsigned int                 attrCount
                               );

            void         reset();

private:
    // -----------------------------------------------------------------------
    //  Unimplemented contstructors and operators
    // -----------------------------------------------------------------------
    IdentityConstraintHandler(const IdentityConstraintHandler& other);
    IdentityConstraintHandler& operator= (const IdentityConstraintHandler& other);

    // -----------------------------------------------------------------------
    //  CleanUp methods
    // -----------------------------------------------------------------------
    void    cleanUp();

    // -----------------------------------------------------------------------
    //  Helper
    // -----------------------------------------------------------------------
    void    activateSelectorFor(
                                      IdentityConstraint* const ic
                              , const int                       initialDepth
                               ) ;

    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fMatcherStack
    //      Stack of active XPath matchers for identity constraints. All
    //      active XPath matchers are notified of startElement, characters
    //      and endElement callbacks in order to perform their matches.
    //
    //  fValueStoreCache
    //      Cache of value stores for identity constraint fields.
    //
    //  fFieldActivator
    //      Activates fields within a certain scope when a selector matches
    //      its xpath.
    //
    // -----------------------------------------------------------------------
    XMLScanner*                 fScanner;
    MemoryManager*              fMemoryManager;

    XPathMatcherStack*          fMatcherStack;
    ValueStoreCache*            fValueStoreCache;
    FieldActivator*             fFieldActivator;

};


// ---------------------------------------------------------------------------
//  IdentityConstraintHandler: 
// ---------------------------------------------------------------------------

inline 
void  IdentityConstraintHandler::endDocument()
{
    fValueStoreCache->endDocument();
}

inline
int  IdentityConstraintHandler::getMatcherCount() const
{
    return fMatcherStack->getMatcherCount();
}

XERCES_CPP_NAMESPACE_END

#endif

/**
  * End of file IdentityConstraintHandler.hpp
  */

