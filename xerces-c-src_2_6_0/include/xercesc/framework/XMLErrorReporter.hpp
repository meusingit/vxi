/*
 * Copyright 1999-2001,2004 The Apache Software Foundation.
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
  * $Log: XMLErrorReporter.hpp,v $
  * Revision 1.7  2004/09/08 13:55:59  peiyongz
  * Apache License Version 2.0
  *
  * Revision 1.6  2003/03/07 18:08:10  tng
  * Return a reference instead of void for operator=
  *
  * Revision 1.5  2002/12/04 02:32:43  knoaman
  * #include cleanup.
  *
  * Revision 1.4  2002/11/04 15:00:21  tng
  * C++ Namespace Support.
  *
  * Revision 1.3  2002/05/27 18:34:59  tng
  * To get ready for 64 bit large file, use XMLSSize_t to represent line and column number.
  *
  * Revision 1.2  2002/02/20 18:17:01  tng
  * [Bug 5977] Warnings on generating apiDocs.
  *
  * Revision 1.1.1.1  2002/02/01 22:21:51  peiyongz
  * sane_include
  *
  * Revision 1.11  2001/05/11 13:25:32  tng
  * Copyright update.
  *
  * Revision 1.10  2001/05/03 19:08:56  knoaman
  * Support Warning/Error/FatalError messaging.
  * Validity constraints errors are treated as errors, with the ability by user to set
  * validity constraints as fatal errors.
  *
  * Revision 1.9  2000/12/14 18:49:57  tng
  * Fix API document generation warning: "Warning: end of member group without matching begin"
  *
  * Revision 1.8  2000/03/02 19:54:25  roddey
  * This checkin includes many changes done while waiting for the
  * 1.1.0 code to be finished. I can't list them all here, but a list is
  * available elsewhere.
  *
  * Revision 1.7  2000/02/24 20:00:23  abagchi
  * Swat for removing Log from API docs
  *
  * Revision 1.6  2000/02/16 23:03:48  roddey
  * More documentation updates
  *
  * Revision 1.5  2000/02/16 21:42:58  aruna1
  * API Doc++ summary changes in
  *
  * Revision 1.4  2000/02/15 23:59:07  roddey
  * More updated documentation of Framework classes.
  *
  * Revision 1.3  2000/02/15 01:21:31  roddey
  * Some initial documentation improvements. More to come...
  *
  * Revision 1.2  2000/02/06 07:47:48  rahulj
  * Year 2K copyright swat.
  *
  * Revision 1.1.1.1  1999/11/09 01:08:34  twl
  * Initial checkin
  *
  * Revision 1.2  1999/11/08 20:44:39  rahul
  * Swat for adding in Product name and CVS comment log variable.
  *
  */


#if !defined(XMLERRORREPORTER_HPP)
#define XMLERRORREPORTER_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN


/**
 *  This abstract class defines a callback mechanism for the scanner. By
 *  creating a class that implements this interface and plugging an instance
 *  of that class into the scanner, the scanner will call back on the object's
 *  virtual methods to report error events. This class is also used with the
 *  validator, to allow it to report errors.
 *
 *  This class is primarily for use by those writing their own parser classes.
 *  If you use the standard parser classes, DOMParser and SAXParser, you won't
 *  use this API. You will instead use a similar mechanism defined by the SAX
 *  API, called ErrorHandler.
 */
class XMLPARSER_EXPORT XMLErrorReporter
{
public:
    // -----------------------------------------------------------------------
    //  The types of errors we can issue
    // -----------------------------------------------------------------------
    enum ErrTypes
    {
        ErrType_Warning
        , ErrType_Error
        , ErrType_Fatal

        , ErrTypes_Unknown
    };


    // -----------------------------------------------------------------------
    //  Constructors are hidden, only the virtual destructor is exposed
    // -----------------------------------------------------------------------

    /** @name Destructor */
    //@{

    /**
      *   Default destructor
      */
    virtual ~XMLErrorReporter()
    {
    }
    //@}


    // -----------------------------------------------------------------------
    //  The error handler interface
    // -----------------------------------------------------------------------

    /** @name Error Handler interface */
    //@{

    /** Called to report errors from the scanner or validator
      *
      * This method is called back on by the scanner or validator (or any other
      * internal parser component which might need to report an error in the
      * future.) It contains all the information that the client code might
      * need to report or log the error.
      *
      * @param  errCode     The error code of the error being reported. What
      *                     this means is dependent on the domain it is from.
      *
      * @param  errDomain   The domain from which the error occured. The domain
      *                     is a means of providing a hierarchical layering to
      *                     the error system, so that a single set of error id
      *                     numbers don't have to be split up.
      *
      * @param  type        The error type, which is defined mostly by XML which
      *                     categorizes errors into warning, errors and validity
      *                     constraints.
      *
      * @param  errorText   The actual text of the error. This is translatable,
      *                     so can possibly be in the local language if a
      *                     translation has been provided.
      *
      * @param  systemId    The system id of the entity where the error occured,
      *                     fully qualified.
      *
      * @param  publicId    The optional public id of the entity were the error
      *                     occured. It can be an empty string if non was provided.
      *
      * @param  lineNum     The line number within the source XML of the error.
      *
      * @param  colNum      The column number within the source XML of the error.
      *                     Because of the parsing style, this is usually just
      *                     after the actual offending text.
      */
    virtual void error
    (
        const   unsigned int        errCode
        , const XMLCh* const        errDomain
        , const ErrTypes            type
        , const XMLCh* const        errorText
        , const XMLCh* const        systemId
        , const XMLCh* const        publicId
        , const XMLSSize_t          lineNum
        , const XMLSSize_t          colNum
    ) = 0;

    /** Called before a new parse event to allow the handler to reset
      *
      * This method is called by the scanner before a new parse event is
      * about to start. It gives the error handler a chance to reset its
      * internal state.
      */
    virtual void resetErrors() = 0;

    //@}


protected :

    /** @name Constructor */
    //@{

    /**
      *   Default constructor
      */
    XMLErrorReporter()
    {
    }
    //@}

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and destructor
    // -----------------------------------------------------------------------
    XMLErrorReporter(const XMLErrorReporter&);
    XMLErrorReporter& operator=(const XMLErrorReporter&);
};

XERCES_CPP_NAMESPACE_END

#endif
