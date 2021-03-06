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
 * $Log: DOMErrorImpl.hpp,v $
 * Revision 1.10  2004/09/08 13:55:51  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.9  2003/12/02 14:33:13  amassari
 * Don't use the word "exception" as a variable name, as VC 7.1 complains about it
 *
 * Revision 1.8  2003/09/04 14:38:25  gareth
 * Fix for bug #22008. Removed the ability to adopt the DOMObject.
 *
 * Revision 1.7  2003/05/15 15:56:24  gareth
 * Removed unnecessary include.
 *
 * Revision 1.6  2003/05/14 18:06:53  gareth
 * Updated DOMError to http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/core.html.
 *
 * Revision 1.5  2003/03/07 18:07:17  tng
 * Return a reference instead of void for operator=
 *
 * Revision 1.4  2002/11/04 15:07:34  tng
 * C++ Namespace Support.
 *
 * Revision 1.3  2002/07/15 19:25:49  tng
 * DOM L3:  declare a dummy DOMError::set/getRelatedException
 *
 * Revision 1.2  2002/05/30 19:26:00  knoaman
 * documentation update
 *
 * Revision 1.1  2002/05/23 15:47:24  knoaman
 * DOM L3 core - support for DOMError, DOMErrorHandler and DOMLocator
 *
 */


#ifndef DOMERRORIMPL_HPP
#define DOMERRORIMPL_HPP

#include <xercesc/dom/DOMError.hpp>
#include <xercesc/util/XMLString.hpp>
XERCES_CPP_NAMESPACE_BEGIN


/**
  * Introduced in DOM Level 3
  * Implementation of a DOMError interface.
  *
  * @see DOMError#DOMError
  */

class CDOM_EXPORT DOMErrorImpl : public DOMError
{
public:
    /** @name Constructors and Destructor */
    //@{

    /** Constructors */
    DOMErrorImpl(const short severity);

    DOMErrorImpl
    (
        const short severity
        , const XMLCh* const message
        , DOMLocator* const location
    );

    DOMErrorImpl
    (
        const short severity
        , const XMLCh* type
        , const XMLCh* message
        , void* relatedData 
    );

    /** Desctructor */
    virtual ~DOMErrorImpl();

    //@}

    /** @name Get function */
    //@{

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the severity of the error
    */
    virtual short getSeverity() const;

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the message describing the error that occured.
    */
    virtual const XMLCh* getMessage() const;

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Get the location of the error
    */
    virtual DOMLocator* getLocation() const;

    /**
     * The related platform dependent exception if any.
     *
     * <p><b>"Experimental - subject to change"</b></p>
     *
     * @see   setRelatedException
     * @since DOM Level 3
     */
    virtual void* getRelatedException() const;

    virtual const XMLCh* getType() const;

    virtual void* getRelatedData() const;

    //@}


   /** @name Set function */
    //@{

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the severity of the error
    *
    * @param severity the type of the error to set
    */
    virtual void setSeverity(const short severity);

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the error message
    *
    * @param message the error message to set.
    */
    virtual void setMessage(const XMLCh* const message);

   /**
    * <p><b>"Experimental - subject to change"</b></p>
    *
    * Set the location of the error
    *
    * @param location the location of the error to set.
    */
    virtual void setLocation(DOMLocator* const location);

   /**
    * @param value <code>true</code> if DOMLocator is owned and should be
    *              deleted, <code>false</code> otherwise.
    */
    void setAdoptLocation(const bool value);

    /**
     * The related platform dependent exception if any.
     *
     * <p><b>"Experimental - subject to change"</b></p>
     *
     * @param exc the related exception to set.
     * @see   getRelatedException
     * @since DOM Level 3
     */
    virtual void setRelatedException(void* exc) const;

    virtual void setType(const XMLCh* type);

    virtual void setRelatedData(void* relatedData);


private :
    /* Unimplemented constructors and operators */

    /* Copy constructor */
    DOMErrorImpl(const DOMErrorImpl&);

    /* Assignment operator */
    DOMErrorImpl& operator=(const DOMErrorImpl&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fAdoptLocation
    //      Indicates whether we own the DOMLocator object or not.
    //
    //  fSeverity
    //      The type of the error.
    //
    //  fMessage
    //      The error message.
    //
    //  fLocation
    //      The location info of the error.
    //
    //  fType
    //      The type of the error.
    //
    //  fRelatedData
    //      The data related to this error.
    //
    // -----------------------------------------------------------------------
    bool         fAdoptLocation;
    short        fSeverity;
    const XMLCh* fMessage;
    DOMLocator*  fLocation;
    const XMLCh* fType;
    void*        fRelatedData;
};

// ---------------------------------------------------------------------------
//  DOMErrorImpl: Getter methods
// ---------------------------------------------------------------------------
inline short DOMErrorImpl::getSeverity() const
{
    return fSeverity;
}

inline const XMLCh* DOMErrorImpl::getMessage() const
{
    return fMessage;
}

inline DOMLocator* DOMErrorImpl::getLocation() const
{
    return fLocation;
}

inline void* DOMErrorImpl::getRelatedException() const
{
    return 0;
}

inline const XMLCh* DOMErrorImpl::getType() const 
{
    return fType;
}

inline void* DOMErrorImpl::getRelatedData() const 
{
    return fRelatedData;
}

// ---------------------------------------------------------------------------
//  DOMLocatorImpl: Setter methods
// ---------------------------------------------------------------------------
inline void DOMErrorImpl::setSeverity(const short severity)
{
    fSeverity = severity;
}

inline void DOMErrorImpl::setMessage(const XMLCh* const message)
{
    fMessage = message;
}

inline void DOMErrorImpl::setAdoptLocation(const bool value)
{
    fAdoptLocation = value;
}

inline void DOMErrorImpl::setType(const XMLCh* type)
{
    fType = type;
}

inline void DOMErrorImpl::setRelatedData(void* relatedData)
{
    fRelatedData = relatedData;
}


XERCES_CPP_NAMESPACE_END

#endif
