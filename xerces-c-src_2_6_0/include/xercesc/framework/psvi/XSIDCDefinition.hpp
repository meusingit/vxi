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
 * $Log: XSIDCDefinition.hpp,v $
 * Revision 1.7  2004/09/08 13:56:08  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.6  2003/12/01 23:23:26  neilg
 * fix for bug 25118; thanks to Jeroen Witmond
 *
 * Revision 1.5  2003/11/21 17:29:53  knoaman
 * PSVI update
 *
 * Revision 1.4  2003/11/14 22:47:53  neilg
 * fix bogus log message from previous commit...
 *
 * Revision 1.3  2003/11/14 22:33:30  neilg
 * Second phase of schema component model implementation.  
 * Implement XSModel, XSNamespaceItem, and the plumbing necessary
 * to connect them to the other components.
 * Thanks to David Cargill.
 *
 * Revision 1.2  2003/11/06 15:30:04  neilg
 * first part of PSVI/schema component model implementation, thanks to David Cargill.  This covers setting the PSVIHandler on parser objects, as well as implementing XSNotation, XSSimpleTypeDefinition, XSIDCDefinition, and most of XSWildcard, XSComplexTypeDefinition, XSElementDeclaration, XSAttributeDeclaration and XSAttributeUse.
 *
 * Revision 1.1  2003/09/16 14:33:36  neilg
 * PSVI/schema component model classes, with Makefile/configuration changes necessary to build them
 *
 */

#if !defined(XSIDCDEFINITION_HPP)
#define XSIDCDEFINITION_HPP

#include <xercesc/framework/psvi/XSObject.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Identity Constraint
 * Definition component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAnnotation;
class IdentityConstraint;

class XMLPARSER_EXPORT XSIDCDefinition : public XSObject
{
public:

    // Identity Constraints
    enum IC_CATEGORY {
	    /**
	     * 
	     */
	    IC_KEY                    = 1,
	    /**
	     * 
	     */
	    IC_KEYREF                 = 2,
	    /**
	     * 
	     */
	    IC_UNIQUE                 = 3
    };

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  identityConstraint
      * @param  keyIC
      * @param  headAnnot
      * @param  stringList
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSIDCDefinition
    (
        IdentityConstraint* const identityConstraint
        , XSIDCDefinition*  const keyIC
        , XSAnnotation* const     headAnnot
        , StringList* const       stringList
        , XSModel* const          xsModel
        , MemoryManager* const    manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSIDCDefinition();
    //@}

    //---------------------
    /** @name overridden XSXSObject methods */

    //@{

    /**
     * The name of type <code>NCName</code> of this declaration as defined in 
     * XML Namespaces.
     */
    const XMLCh* getName();

    /**
     *  The [target namespace] of this object, or <code>null</code> if it is 
     * unspecified. 
     */
    const XMLCh* getNamespace();

    /**
     * A namespace schema information item corresponding to the target 
     * namespace of the component, if it's globally declared; or null 
     * otherwise.
     */
    XSNamespaceItem *getNamespaceItem();

    //@}

    //---------------------
    /** @name XSIDCDefinition methods */

    //@{

    /**
     * [identity-constraint category]: one of IC_KEY, IC_KEYREF or IC_UNIQUE. 
     */
    IC_CATEGORY getCategory() const;

    /**
     * [selector]: a restricted XPath expression. 
     */
    const XMLCh *getSelectorStr();

    /**
     * [fields]: a non-empty list of restricted XPath ([XPath]) expressions. 
     */
    StringList *getFieldStrs();

    /**
     * [referenced key]: required if [identity-constraint category] is IC_KEYREF, 
     * forbidden otherwise (when an identity-constraint definition with [
     * identity-constraint category] equal to IC_KEY or IC_UNIQUE). 
     */
    XSIDCDefinition *getRefKey() const;

    /**
     * A set of [annotations]. 
     */
    XSAnnotationList *getAnnotations();

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{

    //@}
private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSIDCDefinition(const XSIDCDefinition&);
    XSIDCDefinition & operator=(const XSIDCDefinition &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    IdentityConstraint* fIdentityConstraint;
    XSIDCDefinition*    fKey;
    StringList*         fStringList;
    XSAnnotationList*   fXSAnnotationList;
};


inline StringList* XSIDCDefinition::getFieldStrs()
{
    return fStringList;
}

inline XSIDCDefinition* XSIDCDefinition::getRefKey() const
{
    return fKey;
}

XERCES_CPP_NAMESPACE_END

#endif
