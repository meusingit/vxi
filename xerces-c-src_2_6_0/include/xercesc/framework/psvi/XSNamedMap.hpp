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
 * $Log: XSNamedMap.hpp,v $
 * Revision 1.4  2004/09/08 13:56:09  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.3  2004/01/29 11:46:30  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.2  2003/11/06 15:30:04  neilg
 * first part of PSVI/schema component model implementation, thanks to David Cargill.  This covers setting the PSVIHandler on parser objects, as well as implementing XSNotation, XSSimpleTypeDefinition, XSIDCDefinition, and most of XSWildcard, XSComplexTypeDefinition, XSElementDeclaration, XSAttributeDeclaration and XSAttributeUse.
 *
 * Revision 1.1  2003/09/16 14:33:36  neilg
 * PSVI/schema component model classes, with Makefile/configuration changes necessary to build them
 *
 */


#if !defined(XSNAMEDMAP_HPP)
#define XSNAMEDMAP_HPP


#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/RefHash2KeysTableOf.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLStringPool;

/*
 * This template provides convenient mappings between name,namespace
 * pairs and individual components, as well as means to iterate through all the 
 * named components on some object.
 */

template <class TVal> class XSNamedMap: public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    /** @name Constructors */
    //@{

    XSNamedMap(const unsigned int maxElems,
        const unsigned int modulus,
        XMLStringPool* uriStringPool,
        const bool adoptElems,
        MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );
    //@}

    /** @name Destructor */
    //@{
    ~XSNamedMap();

    //@}

    // -----------------------------------------------------------------------
    //  XSNamedMap methods
    // -----------------------------------------------------------------------
    /** @name XSNamedMap methods */ 
    //@{

    /**
     * The number of <code>XSObjects</code> in the <code>XSObjectList</code>. 
     * The range of valid child object indices is 0 to 
     * <code>mapLength-1</code> inclusive. 
     */
    unsigned int getLength();

    /**
     *  Returns the <code>index</code>th item in the collection. The index 
     * starts at 0. If <code>index</code> is greater than or equal to the 
     * number of objects in the list, this returns <code>null</code>. 
     * @param index  index into the collection. 
     * @return  The <code>XSObject</code> at the <code>index</code>th 
     *   position in the <code>XSObjectList</code>, or <code>null</code> if 
     *   that is not a valid index. 
     */
    TVal *item(unsigned int index);

    /**
     * Retrieves a component specified by local name and namespace URI.
     * <br>applications must use the value null as the 
     * <code>compNamespace</code> parameter for components whose targetNamespace property
     * is absent.
     * @param compNamespace The namespace URI of the component to retrieve.
     * @param localName The local name of the component to retrieve.
     * @return A component (of any type) with the specified local 
     *   name and namespace URI, or <code>null</code> if they do not 
     *   identify any node in this map.
     */
    TVal *itemByName(const XMLCh *compNamespace, 
                              const XMLCh *localName);

    //@}

    //----------------------------------
    /** methods needed by implementation */

    //@{
    void addElement(TVal* const toAdd, const XMLCh* key1, const XMLCh* key2);
    //@}
    

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XSNamedMap(const XSNamedMap<TVal>&);
    XSNamedMap<TVal>& operator=(const XSNamedMap<TVal>&);

    // -----------------------------------------------------------------------
    //  Data members
    //
    // fMemoryManager
    //  manager used to allocate memory needed by this object
    MemoryManager *const        fMemoryManager;
    XMLStringPool*              fURIStringPool;
    RefVectorOf<TVal>*          fVector;
    RefHash2KeysTableOf<TVal>*  fHash;
};



XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/framework/psvi/XSNamedMap.c>
#endif

#endif
