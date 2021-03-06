#ifndef DOMNodeIteratorImpl_HEADER_GUARD_
#define DOMNodeIteratorImpl_HEADER_GUARD_

/*
 * Copyright 2001-2002,2004 The Apache Software Foundation.
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
 * $Id: DOMNodeIteratorImpl.hpp,v 1.6 2004/09/26 01:06:30 cargilld Exp $
 */

//
//  This file is part of the internal implementation of the C++ XML DOM.
//  It should NOT be included or used directly by application programs.
//
//  Applications should include the file <xercesc/dom/DOM.hpp> for the entire
//  DOM API, or xercesc/dom/DOM*.hpp for individual DOM classes, where the class
//  name is substituded for the *.
//

//////////////////////////////////////////////////////////////////////
// DOMNodeIteratorImpl.hpp: interface for the DOMNodeIteratorImpl class.
//
//////////////////////////////////////////////////////////////////////

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class CDOM_EXPORT DOMNodeIteratorImpl : public DOMNodeIterator {
    private:
        //
        // Data
        //
        // The root.
        DOMNode* fRoot;

        // The Document used to create this iterator
        DOMDocument* fDocument;

        // The whatToShow mask.
        unsigned long fWhatToShow;

        // The NodeFilter reference.
        DOMNodeFilter* fNodeFilter;


        // The expandEntity reference flag.
        bool  fExpandEntityReferences;
        bool fDetached;


        //
        // Iterator state - current node and direction.
        //
        // Note: The current node and direction are sufficient to implement
        // the desired behaviour of the current pointer being _between_
        // two nodes. The fCurrentNode is actually the last node returned,
        // and the
        // direction is whether the pointer is in front or behind this node.
        // (usually akin to whether the node was returned via nextNode())
        // (eg fForward = true) or previousNode() (eg fForward = false).
        // The last Node returned.
        DOMNode* fCurrentNode;

        // The direction of the iterator on the fCurrentNode.
        //  <code>
        //  nextNode()  ==      fForward = true;<br>
        //  previousNode() ==   fForward = false;<br>
        //  </code>
        bool fForward;

    public:
        virtual ~DOMNodeIteratorImpl ();
        DOMNodeIteratorImpl (
            DOMDocument* fDocument,
            DOMNode* root,
            unsigned long whatToShow,
            DOMNodeFilter* nodeFilter,
            bool expandEntityRef);

        DOMNodeIteratorImpl ( const DOMNodeIteratorImpl& toCopy);
        DOMNodeIteratorImpl& operator= (const DOMNodeIteratorImpl& other);

        virtual DOMNode* getRoot ();                	
        virtual unsigned long getWhatToShow ();
        virtual DOMNodeFilter* getFilter ();
        // Get the expandEntity reference flag.
        virtual bool getExpandEntityReferences();

        virtual DOMNode* nextNode ();
        virtual DOMNode* previousNode ();
        virtual void detach ();

        virtual void release();
        void removeNode (DOMNode* node);

    private:
        DOMNode* matchNodeOrParent (DOMNode* node);
        DOMNode* nextNode (DOMNode* node, bool visitChildren);
        DOMNode* previousNode (DOMNode* node);
        bool acceptNode (DOMNode* node);

};

XERCES_CPP_NAMESPACE_END

#endif
