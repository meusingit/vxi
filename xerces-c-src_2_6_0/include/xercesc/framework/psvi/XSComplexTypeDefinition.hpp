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
 * $Log: XSComplexTypeDefinition.hpp,v $
 * Revision 1.9  2004/09/08 13:56:08  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.8  2003/12/24 17:42:02  knoaman
 * Misc. PSVI updates
 *
 * Revision 1.7  2003/12/01 23:23:26  neilg
 * fix for bug 25118; thanks to Jeroen Witmond
 *
 * Revision 1.6  2003/11/25 18:08:31  knoaman
 * Misc. PSVI updates. Thanks to David Cargill.
 *
 * Revision 1.5  2003/11/21 17:19:30  knoaman
 * PSVI update.
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

#if !defined(XSCOMPLEXTYPEDEFINITION_HPP)
#define XSCOMPLEXTYPEDEFINITION_HPP

#include <xercesc/framework/psvi/XSTypeDefinition.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class represents a complexType definition
 * schema component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 *
 */

// forward declarations
class XSAnnotation;
class XSAttributeUse;
class XSSimpleTypeDefinition;
class XSParticle;
class XSWildcard;
class ComplexTypeInfo;

class XMLPARSER_EXPORT XSComplexTypeDefinition : public XSTypeDefinition
{
public:

	// Content Model Types
    enum CONTENT_TYPE {
	    /**
	     * Represents an empty content type. A content type with the distinguished 
	     * value empty validates elements with no character or element 
	     * information item children. 
	     */
	     CONTENTTYPE_EMPTY         = 0,
	    /**
	     * Represents a simple content type. A content type which is a simple 
	     * validates elements with character-only children. 
	     */
	     CONTENTTYPE_SIMPLE        = 1,
	    /**
	     * Represents an element-only content type. An element-only content type 
	     * validates elements with children that conform to the supplied content 
	     * model. 
	     */
	     CONTENTTYPE_ELEMENT       = 2,
	    /**
	     * Represents a mixed content type.
	     */
	     CONTENTTYPE_MIXED         = 3
	};

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  complexTypeInfo
      * @param  xsWildcard
      * @param  xsSimpleType
      * @param  xsAttList
      * @param  xsBaseType
      * @param  xsParticle
      * @param  headAnnot
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSComplexTypeDefinition
    (
        ComplexTypeInfo* const          complexTypeInfo
        , XSWildcard* const             xsWildcard
        , XSSimpleTypeDefinition* const xsSimpleType
        , XSAttributeUseList* const     xsAttList
        , XSTypeDefinition* const       xsBaseType
        , XSParticle* const             xsParticle
        , XSAnnotation* const           headAnnot
        , XSModel* const                xsModel
        , MemoryManager* const          manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSComplexTypeDefinition();
    //@}

    //---------------------
    /** @name XSComplexTypeDefinition methods */

    //@{

    /**
     * [derivation method]: either <code>DERIVATION_EXTENSION</code>, 
     * <code>DERIVATION_RESTRICTION</code>, or <code>DERIVATION_NONE</code> 
     * (see <code>XSObject</code>). 
     */
    XSConstants::DERIVATION_TYPE getDerivationMethod() const;

    /**
     * [abstract]: a boolean. Complex types for which <code>abstract</code> is 
     * true must not be used as the type definition for the validation of 
     * element information items. 
     */
    bool getAbstract() const;

    /**
     *  A set of attribute uses. 
     */
    XSAttributeUseList *getAttributeUses();

    /**
     * Optional.An attribute wildcard. 
     */
    XSWildcard *getAttributeWildcard() const;

    /**
     * [content type]: one of empty (<code>CONTENTTYPE_EMPTY</code>), a simple 
     * type definition (<code>CONTENTTYPE_SIMPLE</code>), mixed (
     * <code>CONTENTTYPE_MIXED</code>), or element-only (
     * <code>CONTENTTYPE_ELEMENT</code>). 
     */
    CONTENT_TYPE getContentType() const;

    /**
     * A simple type definition corresponding to simple content model, 
     * otherwise <code>null</code> 
     */
    XSSimpleTypeDefinition *getSimpleType() const;

    /**
     * A particle for mixed or element-only content model, otherwise 
     * <code>null</code> 
     */
    XSParticle *getParticle() const;

    /**
     * [prohibited substitutions]: a subset of {extension, restriction}
     * @param toTest  Extention or restriction constants (see 
     *   <code>XSObject</code>). 
     * @return True if toTest is a prohibited substitution, otherwise 
     *   false.
     */
    bool isProhibitedSubstitution(XSConstants::DERIVATION_TYPE toTest);

    /**
     *  [prohibited substitutions]: A subset of {extension, restriction} or 
     * <code>DERIVATION_NONE</code> represented as a bit flag (see 
     * <code>XSObject</code>). 
     */
    short getProhibitedSubstitutions() const;

    /**
     * A set of [annotations]. 
     */
    XSAnnotationList *getAnnotations();
    
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

    /**
     *  A boolean that specifies if the type definition is 
     * anonymous. Convenience attribute. 
     */
    bool getAnonymous() const;

    /**
     * {base type definition}: either a simple type definition or a complex 
     * type definition. 
     */
    XSTypeDefinition *getBaseType();

    /**
     * Convenience method: check if this type is derived from the given 
     * <code>ancestorType</code>. 
     * @param ancestorType  An ancestor type definition. 
     * @return  Return true if this type is derived from 
     *   <code>ancestorType</code>.
     */
    bool derivedFromType(const XSTypeDefinition* const ancestorType);

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{


    //@}

private:

    /**
     * Set the base type
     */
    void setBaseType(XSTypeDefinition* const xsBaseType);
    friend class XSObjectFactory;

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSComplexTypeDefinition(const XSComplexTypeDefinition&);
    XSComplexTypeDefinition & operator=(const XSComplexTypeDefinition &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    ComplexTypeInfo*        fComplexTypeInfo;
    XSWildcard*             fXSWildcard;
    XSAttributeUseList*     fXSAttributeUseList;
    XSSimpleTypeDefinition* fXSSimpleTypeDefinition;
    XSAnnotationList*       fXSAnnotationList;
    XSParticle*             fParticle;
    short                   fProhibitedSubstitution;
};


inline XSAttributeUseList* XSComplexTypeDefinition::getAttributeUses()
{
    return fXSAttributeUseList;
}

inline XSWildcard* XSComplexTypeDefinition::getAttributeWildcard() const
{
    return fXSWildcard;
}

inline XSSimpleTypeDefinition* XSComplexTypeDefinition::getSimpleType() const
{
    return fXSSimpleTypeDefinition;
}

inline short XSComplexTypeDefinition::getProhibitedSubstitutions() const
{
    return fProhibitedSubstitution;
}

inline XSParticle *XSComplexTypeDefinition::getParticle() const
{
    return fParticle;
}

inline void
XSComplexTypeDefinition::setBaseType(XSTypeDefinition* const xsBaseType)
{
    fBaseType = xsBaseType;
}

XERCES_CPP_NAMESPACE_END

#endif
