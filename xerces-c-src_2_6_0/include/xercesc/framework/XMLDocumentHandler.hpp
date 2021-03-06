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
  * $Log: XMLDocumentHandler.hpp,v $
  * Revision 1.11  2004/09/20 15:00:49  amassari
  * Added a setCreateSchemaInfo method to the DOM parsers, to store PSVI informations in element and attribute nodes
  *
  * Revision 1.10  2004/09/08 13:55:58  peiyongz
  * Apache License Version 2.0
  *
  * Revision 1.9  2004/09/02 19:08:09  cargilld
  * Fix API Doc warning message
  *
  * Revision 1.8  2004/02/25 18:29:16  amassari
  * Fixed typo in documentation
  *
  * Revision 1.7  2004/01/29 11:46:29  cargilld
  * Code cleanup changes to get rid of various compiler diagnostic messages.
  *
  * Revision 1.6  2003/11/28 05:14:34  neilg
  * update XMLDocumentHandler to enable stateless passing of type information for elements.  Note that this is as yet unimplemented.
  *
  * Revision 1.5  2003/03/07 18:08:10  tng
  * Return a reference instead of void for operator=
  *
  * Revision 1.4  2002/11/04 15:00:21  tng
  * C++ Namespace Support.
  *
  * Revision 1.3  2002/05/28 20:41:11  tng
  * [Bug 9104] prefixes dissapearing when schema validation turned on.
  *
  * Revision 1.2  2002/02/20 18:17:01  tng
  * [Bug 5977] Warnings on generating apiDocs.
  *
  * Revision 1.1.1.1  2002/02/01 22:21:51  peiyongz
  * sane_include
  *
  * Revision 1.8  2000/03/02 19:54:24  roddey
  * This checkin includes many changes done while waiting for the
  * 1.1.0 code to be finished. I can't list them all here, but a list is
  * available elsewhere.
  *
  * Revision 1.7  2000/02/24 20:00:23  abagchi
  * Swat for removing Log from API docs
  *
  * Revision 1.6  2000/02/16 20:29:20  aruna1
  * API Doc++ summary changes in
  *
  * Revision 1.5  2000/02/16 19:48:56  roddey
  * More documentation updates
  *
  * Revision 1.4  2000/02/15 01:21:30  roddey
  * Some initial documentation improvements. More to come...
  *
  * Revision 1.3  2000/02/09 19:47:27  abagchi
  * Added docs for startElement
  *
  * Revision 1.2  2000/02/06 07:47:48  rahulj
  * Year 2K copyright swat.
  *
  * Revision 1.1.1.1  1999/11/09 01:08:31  twl
  * Initial checkin
  *
  * Revision 1.3  1999/11/08 20:44:37  rahul
  * Swat for adding in Product name and CVS comment log variable.
  *
  */


#if !defined(XMLDOCUMENTHANDLER_HPP)
#define XMLDOCUMENTHANDLER_HPP

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/RefVectorOf.hpp>
#include <xercesc/framework/XMLAttr.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLElementDecl;
class XMLEntityDecl;

/**
  * This abstract class provides the interface for the scanner to return
  * XML document information up to the parser as it scans through the
  * document.
  *
  * The interface is very similar to org.sax.DocumentHandler, but
  * has some extra methods required to get all the data out.
  */
class XMLPARSER_EXPORT XMLDocumentHandler
{
public:
    // -----------------------------------------------------------------------
    //  Constructors are hidden, just the virtual destructor is exposed
    // -----------------------------------------------------------------------
    /** @name Destructor */
    //@{
    virtual ~XMLDocumentHandler()
    {
    }
    //@}

    /** @name The document handler interface */
    //@{
    /** Receive notification of character data.
      *
      * <p>The scanner will call this method to report each chunk of
      * character data. The scanner may return all contiguous character
      * data in a single chunk, or they may split it into several
      * chunks; however, all of the characters in any single event
      * will come from the same external entity, so that the Locator
      * provides useful information.</p>
      *
      * <p>The parser must not attempt to read from the array
      * outside of the specified range.</p>
      *
      * @param  chars           The content (characters) between markup from the XML
      *                         document.
      * @param  length          The number of characters to read from the array.
      * @param  cdataSection    Indicates that this data is inside a CDATA
      *                         section.
      * @see #ignorableWhitespace
      * @see Locator
      */
    virtual void docCharacters
    (
        const   XMLCh* const    chars
        , const unsigned int    length
        , const bool            cdataSection
    ) = 0;

    /** Receive notification of comments in the XML content being parsed.
      *
      * This scanner will call this method for any comments found in the
      * content of the document.
      *
      * @param comment The text of the comment.
      */
    virtual void docComment
    (
        const   XMLCh* const    comment
    ) = 0;

    /** Receive notification of PI's parsed in the XML content.
      *
      * The scanner will call this method for any PIs it finds within the
      * content of the document.
      *
      * @param  target  The name of the PI.
      * @param  data    The body of the PI. This may be an empty string since
      *                 the body is optional.
      */
    virtual void docPI
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    ) = 0;

    /** Receive notification after the scanner has parsed the end of the
      * document.
      *
      * The scanner will call this method when the current document has been
      * fully parsed. The handler may use this opportunity to do something with
      * the data, clean up temporary data, etc...
      */
    virtual void endDocument() = 0;

    /** Receive notification of the end of an element.
      *
      * This method is called when scanner encounters the end of element tag.
      * There will be a corresponding startElement() event for every
      * endElement() event, but not necessarily the other way around. For
      * empty tags, there is only a startElement() call.
      *
      * @param  elemDecl The name of the element whose end tag was just
      *                     parsed.
      * @param  uriId       The ID of the URI in the URI pool (only valid if
      *                     name spaces is enabled)
      * @param  isRoot      Indicates if this is the root element.
      * @param  prefixName  The string representing the prefix name
      */
    virtual void endElement
    (
        const   XMLElementDecl& elemDecl
        , const unsigned int    uriId
        , const bool            isRoot
        , const XMLCh* const    prefixName = 0
    ) = 0;

    /** Receive notification when a referenced entity's content ends
      *
      * This method is called when scanner encounters the end of an entity
      * reference.
      *
      * @param  entDecl  The name of the entity reference just scanned.
      */
    virtual void endEntityReference
    (
        const   XMLEntityDecl&  entDecl
    ) = 0;

    /** Receive notification of ignorable whitespace in element content.
      *
      * <p>Validating Parsers must use this method to report each chunk
      * of ignorable whitespace (see the W3C XML 1.0 recommendation,
      * section 2.10): non-validating parsers may also use this method
      * if they are capable of parsing and using content models.</p>
      *
      * <p>The scanner may return all contiguous whitespace in a single
      * chunk, or it may split it into several chunks; however, all of
      * the characters in any single event will come from the same
      * external entity, so that the Locator provides useful
      * information.</p>
      *
      * <p>The parser must not attempt to read from the array
      * outside of the specified range.</p>
      *
      * @param  chars       The whitespace characters from the XML document.
      * @param  length      The number of characters to read from the array.
      * @param  cdataSection Indicates that this data is inside a CDATA
      *                     section.
      * @see #characters
      */
    virtual void ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const unsigned int    length
        , const bool            cdataSection
    ) = 0;

    /** Reset the document handler's state, if required
      *
      * This method is used to give the registered document handler a
      * chance to reset itself. Its called by the scanner at the start of
      * every parse.
      */
    virtual void resetDocument() = 0;

    /** Receive notification of the start of a new document
      *
      * This method is the first callback called the scanner at the
      * start of every parse. This is before any content is parsed.
      */
    virtual void startDocument() = 0;

    /** Receive notification of a new start tag
      *
      * This method is called when scanner encounters the start of an element tag.
      * All elements must always have a startElement() tag. Empty tags will
      * only have the startElement() tag and no endElement() tag.
      *
      * @param  elemDecl The name of the element whose start tag was just
      *                     parsed.
      * @param  uriId       The ID of the URI in the URI pool (only valid if
      *                     name spaces is enabled)
      * @param  prefixName  The string representing the prefix name
      * @param  attrList    List of attributes in the element
      * @param  attrCount   Count of the attributes in the element
      * @param  isEmpty     Indicates if the element is empty, in which case
      *                     you should not expect an endElement() event.
      * @param  isRoot      Indicates if this is the root element.
      */
    virtual void startElement
    (
        const   XMLElementDecl&         elemDecl
        , const unsigned int            uriId
        , const XMLCh* const            prefixName
        , const RefVectorOf<XMLAttr>&   attrList
        , const unsigned int            attrCount
        , const bool                    isEmpty
        , const bool                    isRoot
    ) = 0;

    /** Receive notification when the scanner hits an entity reference.
      *
      * This is currently useful only to DOM parser configurations as SAX
      * does not provide any api to return this information.
      *
      * @param  entDecl  The name of the entity that was referenced.
      */
    virtual void startEntityReference(const XMLEntityDecl& entDecl) = 0;

    /** Receive notification of an XML declaration
      *
      * Currently neither DOM nor SAX provide API's to return back this
      * information.
      *
      * @param  versionStr      The value of the <code>version</code> pseudoattribute
      *                         of the XML decl.
      * @param  encodingStr     The value of the <code>encoding</code> pseudoattribute
      *                         of the XML decl.
      * @param  standaloneStr   The value of the <code>standalone</code>
      *                         pseudoattribute of the XML decl.
      * @param  autoEncodingStr The encoding string auto-detected by the
      *                         scanner. In absence of any 'encoding' attribute in the
      *                         XML decl, the XML standard specifies how a parser can
      *                         auto-detect. If there is no <code>encodingStr</code>
      *                         this is what will be used to try to decode the file.
      */
    virtual void XMLDecl
    (
        const   XMLCh* const    versionStr
        , const XMLCh* const    encodingStr
        , const XMLCh* const    standaloneStr
        , const XMLCh* const    autoEncodingStr
    ) = 0;

    /** Receive notification of the name and namespace of the type that validated 
      * the element corresponding to the most recent endElement event.
      * This event will be fired immediately after the
      * endElement() event that signifies the end of the element
      * to which it applies; no other events will intervene.
      * This method is <em>EXPERIMENTAL</em> and may change, disappear 
      * or become pure virtual at any time.
      *
      * This corresponds to a part of the information required by DOM Core
      * level 3's TypeInfo interface.
      *
      * @param  typeName        local name of the type that actually validated
      *                         the content of the element corresponding to the
      *                         most recent endElement() callback
      * @param  typeURI         namespace of the type that actually validated
      *                         the content of the element corresponding to the
      *                         most recent endElement() callback
      * @deprecated
      */
    virtual void elementTypeInfo
    (
        const   XMLCh* const /* typeName */
        , const XMLCh* const /* typeURI */
    ) { /* non pure virtual to permit backward compatibility of implementations.  */  };
    //@}



protected :
    // -----------------------------------------------------------------------
    //  Hidden Constructors
    // -----------------------------------------------------------------------
    XMLDocumentHandler()
    {
    }


private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLDocumentHandler(const XMLDocumentHandler&);
    XMLDocumentHandler& operator=(const XMLDocumentHandler&);
};

XERCES_CPP_NAMESPACE_END

#endif
