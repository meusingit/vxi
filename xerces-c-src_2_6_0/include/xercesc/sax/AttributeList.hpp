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
 * $Log: AttributeList.hpp,v $
 * Revision 1.5  2004/09/26 01:06:30  cargilld
 * Fix documentation generation problem.  Replace <pre> with <code>.  Patch from James Littlejohn.
 *
 * Revision 1.4  2004/09/08 13:56:19  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.3  2003/03/07 18:10:06  tng
 * Return a reference instead of void for operator=
 *
 * Revision 1.2  2002/11/04 14:56:25  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:07  peiyongz
 * sane_include
 *
 * Revision 1.8  2000/03/02 19:54:34  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.7  2000/02/24 20:12:54  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.6  2000/02/12 03:31:55  rahulj
 * Removed duplicate CVS Log entries.
 *
 * Revision 1.5  2000/02/12 01:27:19  aruna1
 * Documentation updated
 *
 * Revision 1.4  2000/02/09 02:12:21  abagchi
 * Added getValue docs
 *
 * Revision 1.3  2000/02/06 07:47:57  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.2  1999/12/15 19:58:31  roddey
 * Added new convenience version of getValue() that takes a short character
 * string for the attribute name.
 *
 * Revision 1.1.1.1  1999/11/09 01:07:43  twl
 * Initial checkin
 *
 * Revision 1.2  1999/11/08 20:44:54  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */

#ifndef ATTRIBUTELIST_HPP
#define ATTRIBUTELIST_HPP

#include <xercesc/util/XercesDefs.hpp>

XERCES_CPP_NAMESPACE_BEGIN

/**
  * Interface for an element's attribute specifications.
  *
  * The SAX parser implements this interface and passes an instance
  * to the SAX application as the second argument of each startElement
  * event.
  *
  * The instance provided will return valid results only during the
  * scope of the startElement invocation (to save it for future
  * use, the application must make a copy: the AttributeListImpl
  * helper class provides a convenient constructor for doing so).
  *
  * An AttributeList includes only attributes that have been
  * specified or defaulted: #IMPLIED attributes will not be included.
  *
  * There are two ways for the SAX application to obtain information
  * from the AttributeList.  First, it can iterate through the entire
  * list:
  *
  * <code>
  * public void startElement (String name, AttributeList atts) {<br>
  * &nbsp;for (int i = 0; i < atts.getLength(); i++) {<br>
  * &nbsp;&nbsp;String name = atts.getName(i);<br>
  * &nbsp;&nbsp;String type = atts.getType(i);<br>
  * &nbsp;&nbsp;String value = atts.getValue(i);<br>
  * &nbsp;&nbsp;[...]<br>
  * &nbsp;}<br>
  * }
  * </code>
  *
  * (Note that the result of getLength() will be zero if there
  * are no attributes.)
  *
  * As an alternative, the application can request the value or
  * type of specific attributes:
  *
  * <code>
  * public void startElement (String name, AttributeList atts) {<br>
  * &nbsp;String identifier = atts.getValue("id");<br>
  * &nbsp;String label = atts.getValue("label");<br>
  * &nbsp;[...]<br>
  * }
  * </code>
  *
  * The AttributeListImpl helper class provides a convenience
  * implementation for use by parser or application writers.
  *
  * @see DocumentHandler#startElement
  * @see AttributeListImpl#AttributeListImpl
  */

class SAX_EXPORT AttributeList
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors and Destructor */
    //@{
    /** Default constructor */
    AttributeList()
    {
    }

    /** Destructor */
    virtual ~AttributeList()
    {
    }
    //@}

    /** @name The virtual attribute list interface */
    //@{
  /**
    * Return the number of attributes in this list.
    *
    * The SAX parser may provide attributes in any
    * arbitrary order, regardless of the order in which they were
    * declared or specified.  The number of attributes may be
    * zero.
    *
    * @return The number of attributes in the list.
    */
    virtual unsigned int getLength() const = 0;

  /**
    * Return the name of an attribute in this list (by position).
    *
    * The names must be unique: the SAX parser shall not include the
    * same attribute twice.  Attributes without values (those declared
    * #IMPLIED without a value specified in the start tag) will be
    * omitted from the list.
    *
    * If the attribute name has a namespace prefix, the prefix
    * will still be attached.
    *
    * @param index The index of the attribute in the list (starting at 0).
    * @return The name of the indexed attribute, or null
    *         if the index is out of range.
    * @see #getLength
    */
    virtual const XMLCh* getName(const unsigned int index) const = 0;

  /**
    * Return the type of an attribute in the list (by position).
    *
    * The attribute type is one of the strings "CDATA", "ID",
    * "IDREF", "IDREFS", "NMTOKEN", "NMTOKENS", "ENTITY", "ENTITIES",
    * or "NOTATION" (always in upper case).
    *
    * If the parser has not read a declaration for the attribute,
    * or if the parser does not report attribute types, then it must
    * return the value "CDATA" as stated in the XML 1.0 Recommentation
    * (clause 3.3.3, "Attribute-Value Normalization").
    *
    * For an enumerated attribute that is not a notation, the
    * parser will report the type as "NMTOKEN".
    *
    * @param index The index of the attribute in the list (starting at 0).
    * @return The attribute type as a string, or
    *         null if the index is out of range.
    * @see #getLength
    * @see #getType(String)
    */
    virtual const XMLCh* getType(const unsigned int index) const = 0;

  /**
    * Return the value of an attribute in the list (by position).
    *
    * If the attribute value is a list of tokens (IDREFS,
    * ENTITIES, or NMTOKENS), the tokens will be concatenated
    * into a single string separated by whitespace.
    *
    * @param index The index of the attribute in the list (starting at 0).
    * @return The attribute value as a string, or
    *         null if the index is out of range.
    * @see #getLength
    * @see #getValue(XMLCh*)
    * @see #getValue(char *)
    */
    virtual const XMLCh* getValue(const unsigned int index) const = 0;

  /**
    * Return the type of an attribute in the list (by name).
    *
    * The return value is the same as the return value for
    * getType(int).
    *
    * If the attribute name has a namespace prefix in the document,
    * the application must include the prefix here.
    *
    * @param name The name of the attribute.
    * @return The attribute type as a string, or null if no
    *         such attribute exists.
    * @see #getType(int)
    */
    virtual const XMLCh* getType(const XMLCh* const name) const = 0;

  /**
    * Return the value of an attribute in the list (by name).
    *
    * The return value is the same as the return value for
    * getValue(int).
    *
    * If the attribute name has a namespace prefix in the document,
    * the application must include the prefix here.
    *
    * @param name The name of the attribute in the list.
    * @return The attribute value as a string, or null if
    *         no such attribute exists.
    * @see #getValue(int)
    * @see #getValue(char *)
    */
    virtual const XMLCh* getValue(const XMLCh* const name) const = 0;

  /**
    * Return the value of an attribute in the list (by name).
    *
    * The return value is the same as the return value for
    * getValue(int).
    *
    * If the attribute name has a namespace prefix in the document,
    * the application must include the prefix here.
    *
    * @param name The name of the attribute in the list.
    * @return The attribute value as a string, or null if
    *         no such attribute exists.
    * @see #getValue(int)
    * @see #getValue(XMLCh*)
    */
    virtual const XMLCh* getValue(const char* const name) const = 0;
    //@}

private :
    /* Constructors and operators */
    /* Copy constructor */
    AttributeList(const AttributeList&);
    /* Assignment operator */
    AttributeList& operator=(const AttributeList&);

};

XERCES_CPP_NAMESPACE_END

#endif
