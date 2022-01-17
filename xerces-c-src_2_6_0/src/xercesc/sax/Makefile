# Generated automatically from Makefile.in by configure.
#
# Copyright 1999-2000,2004 The Apache Software Foundation.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
#
# $Id: Makefile.in,v 1.5 2004/09/08 13:56:19 peiyongz Exp $
#

PLATFORM = LINUX
CC  = gcc
CXX = c++
CXXVER = 
GCC = yes
GXX = yes
CXXFLAGS = -g -O2
CFLAGS = -g -O2
PREFIX = /usr/local
PREFIX_INCLUDE = ${PREFIX}/include/xercesc
LDFLAGS = 
LIBS = 
OSVER = 
USELIBWWW = 
MESSAGELOADER = 
TRANSCODER = 
THREADS = 

include ../Makefile.incl

MODULE = sax

SAX_CPP_PUBHEADERS = \
	AttributeList.hpp \
	DTDHandler.hpp \
	DocumentHandler.hpp \
	EntityResolver.hpp \
	ErrorHandler.hpp \
	HandlerBase.hpp \
	InputSource.hpp \
	Locator.hpp \
	Parser.hpp \
	SAXException.hpp \
	SAXParseException.hpp

SAX_CPP_PRIVHEADERS =

SAX_C_FILES =

SAX_CPP_OBJECTS = \
	Dummy.$(TO) \
	InputSource.$(TO) \
	SAXException.$(TO) \
	SAXParseException.$(TO)

all::	includes $(SAX_CPP_OBJECTS)

includes::	pubheaders $(SAX_C_FILES)

pubheaders::
	-mkdir -p $(XML_INC_DIR)/$(MODULE)
	$(CP) $(SAX_CPP_PUBHEADERS) $(SAX_C_FILES) $(XML_INC_DIR)/$(MODULE)

# this may generate unnecessary dependencies, but it makes life easier
depend:: includes
	$(MAKE_DEPEND) $(XML_INCL) *.cpp > $(DEPFILE)

clean::
	@echo "Making clean in $(MODULE) ..."
	$(RM2) $(addprefix $(XML_OBJ_DIR)/,$(SAX_CPP_OBJECTS))

distclean::	clean
	$(RM) Makefile $(DEPFILE)
	@echo "Removing all $(MODULE) header files ..."
	$(RM2) $(addprefix $(XML_INC_DIR)/$(MODULE)/,$(SAX_CPP_PUBHEADERS))

install::
	-mkdir -p $(DESTDIR)$(PREFIX_INCLUDE)/$(MODULE)
	$(CP) $(SAX_CPP_PUBHEADERS) $(SAX_C_FILES) $(DESTDIR)$(PREFIX_INCLUDE)/$(MODULE)
