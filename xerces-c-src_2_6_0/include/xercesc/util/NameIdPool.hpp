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
 * $Log: NameIdPool.hpp,v $
 * Revision 1.11  2004/09/23 07:10:13  amassari
 * Removed const from variable declaration (jira#1259)
 *
 * Revision 1.10  2004/09/08 13:56:22  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.9  2004/01/29 11:48:46  cargilld
 * Code cleanup changes to get rid of various compiler diagnostic messages.
 *
 * Revision 1.8  2003/12/17 00:18:35  cargilld
 * Update to memory management so that the static memory manager (one used to call Initialize) is only for static data.
 *
 * Revision 1.7  2003/10/29 16:17:48  peiyongz
 * size() added
 *
 * Revision 1.6  2003/05/16 06:01:52  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.5  2003/05/15 19:04:35  knoaman
 * Partial implementation of the configurable memory manager.
 *
 * Revision 1.4  2003/03/07 18:11:54  tng
 * Return a reference instead of void for operator=
 *
 * Revision 1.3  2002/12/04 02:32:43  knoaman
 * #include cleanup.
 *
 * Revision 1.2  2002/11/04 15:22:04  tng
 * C++ Namespace Support.
 *
 * Revision 1.1.1.1  2002/02/01 22:22:11  peiyongz
 * sane_include
 *
 * Revision 1.6  2000/09/09 00:11:48  andyh
 * Virtual Destructor Patch, submitted by Kirk Wylie
 *
 * Revision 1.5  2000/07/19 18:47:26  andyh
 * More Macintosh port tweaks, submitted by James Berry.
 *
 * Revision 1.4  2000/03/02 19:54:42  roddey
 * This checkin includes many changes done while waiting for the
 * 1.1.0 code to be finished. I can't list them all here, but a list is
 * available elsewhere.
 *
 * Revision 1.3  2000/02/24 20:05:24  abagchi
 * Swat for removing Log from API docs
 *
 * Revision 1.2  2000/02/06 07:48:02  rahulj
 * Year 2K copyright swat.
 *
 * Revision 1.1.1.1  1999/11/09 01:04:48  twl
 * Initial checkin
 *
 * Revision 1.3  1999/11/08 20:45:10  rahul
 * Swat for adding in Product name and CVS comment log variable.
 *
 */


#if !defined(NAMEIDPOOL_HPP)
#define NAMEIDPOOL_HPP

#include <xercesc/util/XMemory.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

//
//  Forward declare the enumerator so he can be our friend. Can you say
//  friend? Sure...
//
template <class TElem> class NameIdPoolEnumerator;


//
//  This class is provided to serve as the basis of many of the pools that
//  are used by the scanner and validators. They often need to be able to
//  store objects in such a way that they can be quickly accessed by the
//  name field of the object, and such that each element added is assigned
//  a unique id via which it can be accessed almost instantly.
//
//  Object names are enforced as being unique, since that's what all these
//  pools require. So its effectively a hash table in conjunction with an
//  array of references into the hash table by id. Ids are assigned such that
//  id N can be used to get the Nth element from the array of references.
//  This provides very fast access by id.
//
//  The way these pools are used, elements are never removed except when the
//  whole thing is flushed. This makes it very easy to maintain the two
//  access methods in sync.
//
//  For efficiency reasons, the id refererence array is never flushed until
//  the dtor. This way, it does not have to be regrown every time its reused.
//
//  All elements are assumed to be owned by the pool!
//
//  We have to have a bucket element structure to use to maintain the linked
//  lists for each bucket. Because some of the compilers we have to support
//  are totally brain dead, it cannot be a nested class as it should be.
//
template <class TElem> struct NameIdPoolBucketElem : public XMemory
{
public :
    NameIdPoolBucketElem
    (
        TElem* const                            value
        , NameIdPoolBucketElem<TElem>* const    next
    );
    ~NameIdPoolBucketElem();

    TElem*                          fData;
    NameIdPoolBucketElem<TElem>*    fNext;
private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    NameIdPoolBucketElem(const NameIdPoolBucketElem<TElem>&);
    NameIdPoolBucketElem<TElem>& operator=(const NameIdPoolBucketElem<TElem>&);
};


template <class TElem> class NameIdPool : public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Contructors and Destructor
    // -----------------------------------------------------------------------
    NameIdPool
    (
        const   unsigned int    hashModulus
        , const unsigned int    initSize = 128
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    ~NameIdPool();


    // -----------------------------------------------------------------------
    //  Element management
    // -----------------------------------------------------------------------
    bool containsKey(const XMLCh* const key) const;
    void removeAll();


    // -----------------------------------------------------------------------
    //  Getters
    // -----------------------------------------------------------------------
    TElem* getByKey(const XMLCh* const key);
    const TElem* getByKey(const XMLCh* const key) const;
    TElem* getById(const unsigned elemId);
    const TElem* getById(const unsigned elemId) const;

    MemoryManager* getMemoryManager() const;
    // -----------------------------------------------------------------------
    //  Putters
    //
    //  Dups are not allowed and cause an IllegalArgumentException. The id
    //  of the new element is returned.
    // -----------------------------------------------------------------------
    unsigned int put(TElem* const valueToAdopt);


protected :
    // -----------------------------------------------------------------------
    //  Declare the enumerator our friend so he can see our members
    // -----------------------------------------------------------------------
    friend class NameIdPoolEnumerator<TElem>;


private :
    // -----------------------------------------------------------------------
    //  Unused constructors and operators
    // -----------------------------------------------------------------------
    NameIdPool(const NameIdPool<TElem>&);
    NameIdPool<TElem>& operator=(const NameIdPool<TElem>&);


    // -----------------------------------------------------------------------
    //  Private helper methods
    // -----------------------------------------------------------------------
    NameIdPoolBucketElem<TElem>* findBucketElem
    (
        const XMLCh* const      key
        ,     unsigned int&     hashVal
    );
    const NameIdPoolBucketElem<TElem>* findBucketElem
    (
        const   XMLCh* const    key
        ,       unsigned int&   hashVal
    )   const;


    // -----------------------------------------------------------------------
    //  Data members
    //
    //  fBucketList
    //      This is the array that contains the heads of all of the list
    //      buckets, one for each possible hash value.
    //
    //  fIdPtrs
    //  fIdPtrsCount
    //      This is the array of pointers to the bucket elements in order of
    //      their assigned ids. So taking id N and referencing this array
    //      gives you the element with that id. The count field indicates
    //      the current size of this list. When fIdCounter+1 reaches this
    //      value the list must be expanded.
    //
    //  fIdCounter
    //      This is used to give out unique ids to added elements. It starts
    //      at zero (which means empty), and is bumped up for each newly added
    //      element. So the first element is 1, the next is 2, etc... This
    //      means that this value is set to the top index of the fIdPtrs array.
    //
    //  fHashModulus
    //      This is the modulus to use in this pool. The fBucketList array
    //      is of this size. It should be a prime number.
    // -----------------------------------------------------------------------
    MemoryManager*                  fMemoryManager;
    NameIdPoolBucketElem<TElem>**   fBucketList;
    TElem**                         fIdPtrs;
    unsigned int                    fIdPtrsCount;
    unsigned int                    fIdCounter;
    unsigned int                    fHashModulus;
};


//
//  An enumerator for a name id pool. It derives from the basic enumerator
//  class, so that pools can be generically enumerated.
//
template <class TElem> class NameIdPoolEnumerator : public XMLEnumerator<TElem>, public XMemory
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    NameIdPoolEnumerator
    (
                NameIdPool<TElem>* const    toEnum
                , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );

    NameIdPoolEnumerator
    (
        const   NameIdPoolEnumerator<TElem>& toCopy
    );

    virtual ~NameIdPoolEnumerator();

    // -----------------------------------------------------------------------
    //  Public operators
    // -----------------------------------------------------------------------
    NameIdPoolEnumerator<TElem>& operator=
    (
        const   NameIdPoolEnumerator<TElem>& toAssign
    );
   
    // -----------------------------------------------------------------------
    //  Enum interface
    // -----------------------------------------------------------------------
    bool hasMoreElements() const;
    TElem& nextElement();
    void Reset();
    int  size()  const;

private :
    // -----------------------------------------------------------------------
    //  Data Members
    //
    //  fCurIndex
    //      This is the current index into the pool's id mapping array. This
    //      is now we enumerate it.
    //
    //  fToEnum
    //      The name id pool that is being enumerated.
    // -----------------------------------------------------------------------
    unsigned int            fCurIndex;
    NameIdPool<TElem>*      fToEnum;
    MemoryManager*          fMemoryManager;
};

XERCES_CPP_NAMESPACE_END

#if !defined(XERCES_TMPLSINC)
#include <xercesc/util/NameIdPool.c>
#endif

#endif
