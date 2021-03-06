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
 * $Log: XSModelGroup.hpp,v $
 * Revision 1.6  2004/09/08 13:56:08  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.5  2003/12/01 23:23:26  neilg
 * fix for bug 25118; thanks to Jeroen Witmond
 *
 * Revision 1.4  2003/11/21 17:29:53  knoaman
 * PSVI update
 *
 * Revision 1.3  2003/11/14 22:47:53  neilg
 * fix bogus log message from previous commit...
 *
 * Revision 1.2  2003/11/14 22:33:30  neilg
 * Second phase of schema component model implementation.  
 * Implement XSModel, XSNamespaceItem, and the plumbing necessary
 * to connect them to the other components.
 * Thanks to David Cargill.
 *
 * Revision 1.1  2003/09/16 14:33:36  neilg
 * PSVI/schema component model classes, with Makefile/configuration changes necessary to build them
 *
 */

#if !defined(XSMODELGROUP_HPP)
#define XSMODELGROUP_HPP

#include <xercesc/framework/psvi/XSObject.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Model Group
 * component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class XSAnnotation;
class XSParticle;

class XMLPARSER_EXPORT XSModelGroup : public XSObject
{
public:

    // Content model compositors
    enum COMPOSITOR_TYPE {
	    /**
	     * This constant value signifies a sequence operator.
	     */
	    COMPOSITOR_SEQUENCE       = 1,
	    /**
	     * This constant value signifies a choice operator.
	     */
	    COMPOSITOR_CHOICE         = 2,
	    /**
	     * This content model represents a simplified version of the SGML 
	     * &amp;-Connector and is limited to the top-level of any content model. 
	     * No element in the all content model may appear more than once.
	     */
	    COMPOSITOR_ALL            = 3
    };
	
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  compositorType
      * @param  particleList
      * @param  annot
      * @param  xsModel
      * @param  manager     The configurable memory manager
      */
    XSModelGroup
    (
        COMPOSITOR_TYPE compositorType
        , XSParticleList* const particleList
        , XSAnnotation* const annot
        , XSModel* const xsModel
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSModelGroup();
    //@}

    //---------------------
    /** @name XSModelGroup methods */
    //@{

    /**
     * [compositor]: one of all, choice or sequence. The valid constants 
     * values are: 
     * <code>COMPOSITOR_SEQUENCE, COMPOSITOR_CHOICE, COMPOSITOR_ALL</code>. 
     */
    COMPOSITOR_TYPE getCompositor() const;

    /**
     *  A list of [particles]. 
     */
    XSParticleList *getParticles() const;

    /**
     * Optional. An [annotation]. 
     */
    XSAnnotation *getAnnotation() const;

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{

    //@}
private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSModelGroup(const XSModelGroup&);
    XSModelGroup & operator=(const XSModelGroup &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    COMPOSITOR_TYPE fCompositorType;
    XSParticleList* fParticleList;
    XSAnnotation*   fAnnotation;
};

inline XSModelGroup::COMPOSITOR_TYPE XSModelGroup::getCompositor() const
{
    return fCompositorType;
}

inline XSParticleList* XSModelGroup::getParticles() const
{
    return fParticleList;
}

inline XSAnnotation* XSModelGroup::getAnnotation() const
{
    return fAnnotation;
}

XERCES_CPP_NAMESPACE_END

#endif
