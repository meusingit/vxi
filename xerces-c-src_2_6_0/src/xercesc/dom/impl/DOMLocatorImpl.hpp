/*
 * Copyright 2002,2004 The Apache Software Foundation.
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
 * $Log: DOMLocatorImpl.hpp,v $
 * Revision 1.6  2004/09/08 13:55:51  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.5  2003/03/07 18:07:17  tng
 * Return a reference instead of void for operator=
 *
 * Revision 1.4  2002/11/04 15:07:34  tng
 * C++ Namespace Support.
 *
 * Revision 1.3  2002/05/30 19:26:00  knoaman
 * documentation update
 *
 * Revision 1.2  2002/05/27 18:25:41  tng
 * To get ready for 64 bit large file, use XMLSSize_t to represent line and column number.
 *
 * Revision 1.1  2002/05/23 15:47:24  knoaman
 * DOM L3 core - support for DOMError, DOMErrorHandler and DOMLocator
 *
 */


#ifndef DOMLOCATORIMPL_HPP
#define DOMLOCATORIMPL_HPP

#include <xercesc/dom/DOMLocator.hpp>

XERCES_CPP_NAMESPACE_BEGIN



/**
  * Introduced in DOM Level 3
  *
  * Implementation of a DOMLocator interface.
  *
  * @see DOMLocator#DOMLocator
  */

class CDOM_EXPORT DOMLocatorImpl : public DOMLocator
{
public:
    /** @name Constructors and Destructor */
    //@{

    /** Constructor */
    DOMLocatorImpl();

    DOMLocatorImpl
    (
        const XMLSSize_t lineNum
        , const XMLSSize_t columnNum
        , DOMNode* const errorNode
        , const XMLCh* const uri
        , const XMLSSize_t offset = -1
    );

    /** Desctructor */
    virtual ~DOMLocatorImpl();

    //@}

    /** @name Get function */
    //@{

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the line number where the error occured. The value is -1 if there is
    * no line number available.
    *
    * @see #setLineNumber
    */
    virtual XMLSSize_t getLineNumber() const;

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the column number where the error occured. The value is -1 if there
    * is no column number available.
    *
    * @see #setColumnNumber
    */
    virtual XMLSSize_t getColumnNumber() const;

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the byte or character offset into the input source, if we're parsing
    * a file or a byte stream then this will be the byte offset into that
    * stream, but if a character media is parsed then the offset will be the
    * character offset. The value is -1 if there is no offset available.
    *
    * @see #setOffset
    */
    virtual XMLSSize_t getOffset() const;

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the DOM Node where the error occured, or <code>null</code> if there
    * is no node available.
    *
    * @see #setErrorNode
    */
    virtual DOMNode* getErrorNode() const;

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the URI where the error occured, or <code>null</code> if there is no
    * URI available.
    *
    * @see #setURI
    */
    virtual const XMLCh* getURI() const;

    //@}


   /** @name Set function */
    //@{

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the line number of the error
    *
    * @param lineNumber the line number to set
    *
    * @see #getLinNumner
    */
    virtual void setLineNumber(const XMLSSize_t lineNumber);

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the column number of the error
    *
    * @param columnNumber the column number to set.
    *
    * @see #getColumnNumner
    */
    virtual void setColumnNumber(const XMLSSize_t columnNumber);

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the byte/character offset.
    *
    * @param offset the byte/characte offset to set.
    *
    * @see #getOffset
    */
    virtual void setOffset(const XMLSSize_t offset);

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the DOM Node where the error occured
    *
    * @param errorNode the DOM Node to set
    *
    * @see #getErrorNode
    */
    virtual void setErrorNode(DOMNode* const errorNode);

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the URI where the error occured
    *
    * @param uri the URI to set.
    *
    * @see #getURI
    */
    virtual void setURI(const XMLCh* const uri);

    //@}


private :
    /* Unimplemented constructors and operators */

    /* Copy constructor */
    DOMLocatorImpl(const DOMLocatorImpl&);

    /* Assignment operator */
    DOMLocatorImpl& operator=(const DOMLocatorImpl&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLineNum
    //  fColumnNum
    //      Track line/column number of where the error occured
    //
    //  fOffset
    //      Track character/byte offset in the input source where the error
    //      occured
    //
    //  fErrorNode
    //      Current error node where the error occured
    //
    //  fURI
    //      The uri where the error occured
    // -----------------------------------------------------------------------
    XMLSSize_t   fLineNum;
    XMLSSize_t   fColumnNum;
    XMLSSize_t   fOffset;
    DOMNode*     fErrorNode;
    const XMLCh* fURI;
};


// ---------------------------------------------------------------------------
//  DOMLocatorImpl: Getter methods
// ---------------------------------------------------------------------------
inline XMLSSize_t DOMLocatorImpl::getLineNumber() const
{
    return fLineNum;
}

inline XMLSSize_t DOMLocatorImpl::getColumnNumber() const
{
    return fColumnNum;
}

inline XMLSSize_t DOMLocatorImpl::getOffset() const
{
    return fOffset;
}

inline DOMNode* DOMLocatorImpl::getErrorNode() const
{
    return fErrorNode;
}

inline const XMLCh* DOMLocatorImpl::getURI() const
{
    return fURI;
}


// ---------------------------------------------------------------------------
//  DOMLocatorImpl: Setter methods
// ---------------------------------------------------------------------------
inline void DOMLocatorImpl::setLineNumber(const XMLSSize_t lineNumber)
{
    fLineNum = lineNumber;
}

inline void DOMLocatorImpl::setColumnNumber(const XMLSSize_t columnNumber)
{
    fColumnNum = columnNumber;
}

inline void DOMLocatorImpl::setOffset(const XMLSSize_t offset)
{
    fOffset = offset;
}

inline void DOMLocatorImpl::setErrorNode(DOMNode* const errorNode)
{
    fErrorNode = errorNode;
}

inline void DOMLocatorImpl::setURI(const XMLCh* const uri)
{
    fURI = uri;
}

XERCES_CPP_NAMESPACE_END

#endif
