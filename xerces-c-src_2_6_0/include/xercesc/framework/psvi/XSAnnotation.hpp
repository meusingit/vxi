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
 * $Log: XSAnnotation.hpp,v $
 * Revision 1.11  2004/09/08 13:56:07  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.10  2004/09/02 19:08:09  cargilld
 * Fix API Doc warning message
 *
 * Revision 1.9  2004/04/02 16:51:05  peiyongz
 * Better error report support
 *
 * Revision 1.8  2003/12/01 23:23:26  neilg
 * fix for bug 25118; thanks to Jeroen Witmond
 *
 * Revision 1.7  2003/11/28 14:55:11  neilg
 * fix for compilation error on HPUX
 *
 * Revision 1.6  2003/11/27 21:29:05  neilg
 * implement writeAnnotation; thanks to Dave Cargill
 *
 * Revision 1.5  2003/11/14 22:47:53  neilg
 * fix bogus log message from previous commit...
 *
 * Revision 1.4  2003/11/14 22:33:30  neilg
 * Second phase of schema component model implementation.  
 * Implement XSModel, XSNamespaceItem, and the plumbing necessary
 * to connect them to the other components.
 * Thanks to David Cargill.
 *
 * Revision 1.3  2003/11/11 22:48:13  knoaman
 * Serialization of XSAnnotation.
 *
 * Revision 1.2  2003/11/06 19:28:11  knoaman
 * PSVI support for annotations.
 *
 * Revision 1.1  2003/09/16 14:33:36  neilg
 * PSVI/schema component model classes, with Makefile/configuration changes necessary to build them
 *
 */

#if !defined(XSANNOTATION_HPP)
#define XSANNOTATION_HPP

#include <xercesc/framework/psvi/XSObject.hpp>
#include <xercesc/internal/XSerializable.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
 * This class describes all properties of a Schema Annotation
 * component.
 * This is *always* owned by the validator /parser object from which
 * it is obtained.  
 */

// forward declarations
class DOMNode;
class ContentHandler;

class XMLPARSER_EXPORT XSAnnotation : public XSerializable, public XSObject
{
public:

    // TargetType
    enum ANNOTATION_TARGET {
	    /**
	     * The object type is <code>org.w3c.dom.Element</code>.
	     */
	    W3C_DOM_ELEMENT           = 1,
	    /**
	     * The object type is <code>org.w3c.dom.Document</code>.
	     */
	    W3C_DOM_DOCUMENT          = 2
    };

    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    /**
      * The default constructor 
      *
      * @param  contents    The string that is to be the content of this XSAnnotation
      * @param  manager     The configurable memory manager
      */
    XSAnnotation
    (
        const XMLCh* const contents
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    //@};

    /** @name Destructor */
    //@{
    ~XSAnnotation();
    //@}

    //---------------------
    /** @name XSAnnotation methods */

    //@{

    /**
     * Write contents of the annotation to the specified DOM object. In-scope 
     * namespace declarations for <code>annotation</code> element are added as 
     * attribute nodes of the serialized <code>annotation</code>. 
     * @param node  A target pointer to the annotation target object, i.e.
     * either <code>DOMDocument</code> or <code>DOMElement</code> cast as 
     * <code>DOMNode</code>. 
     * @param targetType  A target type.    
     */
 
    void writeAnnotation(DOMNode* node, ANNOTATION_TARGET targetType);  

    /**
     * Write contents of the annotation to the specified object. 
     * The corresponding events for all in-scope namespace declarations are 
     * sent via the specified document handler. 
     * @param handler  A target pointer to the annotation target object, i.e. 
     *   <code>ContentHandler</code>.
     */    
    void writeAnnotation(ContentHandler* handler);

    /**
     * A text representation of annotation.
     */
    const XMLCh *getAnnotationString() const;
    XMLCh *getAnnotationString();

    //@}

    //----------------------------------
    /** methods needed by implementation */
    //@{
    void            setNext(XSAnnotation* const nextAnnotation);
    XSAnnotation*   getNext();
    //@}

    //-----------------------------
    /** Getter */
    //@{
    inline void           getLineCol(int& line, int& col)  const;
    inline const XMLCh*   getSystemId()                    const;    
    //@}

    //-----------------------------
    /** Setter */
    //@{
    inline void           setLineCol(int line, int col);
           void           setSystemId(const XMLCh* const systemId);    
    //@}

    /***
     * Support for Serialization/De-serialization
     ***/
    DECL_XSERIALIZABLE(XSAnnotation)
    XSAnnotation(MemoryManager* const manager);

private:

    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSAnnotation(const XSAnnotation&);
    XSAnnotation & operator=(const XSAnnotation &);

protected:

    // -----------------------------------------------------------------------
    //  data members
    // -----------------------------------------------------------------------
    XMLCh*        fContents;
    XSAnnotation* fNext;

private:

    XMLCh*        fSystemId;
    int           fLine;
    int           fCol;

};

inline const XMLCh *XSAnnotation::getAnnotationString() const
{
    return fContents;
}

inline XMLCh *XSAnnotation::getAnnotationString()
{
    return fContents;
}

inline void XSAnnotation::getLineCol(int& line, int& col) const
{
    line = fLine;
    col  = fCol;
}

inline const XMLCh* XSAnnotation::getSystemId() const
{
    return fSystemId;
}

inline void XSAnnotation::setLineCol(int line, int col)
{
    fLine = line;
    fCol  = col;
}

XERCES_CPP_NAMESPACE_END

#endif
