#
# Copyright 1999-2001,2004 The Apache Software Foundation.
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
# $Id: Makefile.in,v 1.8 2004/09/08 13:56:17 peiyongz Exp $
#

PLATFORM = LINUX
CC  = gcc
CXX = g++
CXXVER = 
GCC = yes
GXX = yes
CXXFLAGS =   -w -O -DPROJ_XMLPARSER  -DPROJ_XMLUTIL  -DPROJ_PARSERS  -DPROJ_SAX4C  -DPROJ_SAX2  -DPROJ_DOM -DPROJ_DEPRECATED_DOM -DPROJ_VALIDATORS -DXML_USE_NATIVE_TRANSCODER -DXML_USE_INMEM_MESSAGELOADER -DXML_USE_PTHREADS -DXML_USE_NETACCESSOR_SOCKET  
CFLAGS =   -w -O -DPROJ_XMLPARSER  -DPROJ_XMLUTIL  -DPROJ_PARSERS  -DPROJ_SAX4C  -DPROJ_SAX2  -DPROJ_DOM -DPROJ_DEPRECATED_DOM -DPROJ_VALIDATORS -DXML_USE_NATIVE_TRANSCODER -DXML_USE_INMEM_MESSAGELOADER -DXML_USE_PTHREADS -DXML_USE_NETACCESSOR_SOCKET   
PREFIX = /usr/local
PREFIX_INCLUDE = ${PREFIX}/include/xercesc
LDFLAGS =    
LIBS =   -lpthread 
OSVER = 
USELIBWWW = 
MESSAGELOADER = INMEM
TRANSCODER = NATIVE
THREADS = pthread

include ../Makefile.incl

MODULE = parsers

PARSERS_CPP_PUBHEADERS = \
	AbstractDOMParser.hpp \
	DOMBuilderImpl.hpp \
	XercesDOMParser.hpp \
	SAXParser.hpp \
	SAX2XMLReaderImpl.hpp

PARSERS_CPP_PRIVHEADERS =

PARSERS_C_FILES =

PARSERS_CPP_OBJECTS = \
	AbstractDOMParser.$(TO) \
	DOMBuilderImpl.$(TO) \
	XercesDOMParser.$(TO) \
	SAXParser.$(TO) \
	SAX2XMLReaderImpl.$(TO)

XML_INCL := $(XML_INCL) -I$(XERCESCROOT)/src

all::	includes $(PARSERS_CPP_OBJECTS)

includes::	pubheaders $(PARSERS_C_FILES)

pubheaders::
	-mkdir -p $(XML_INC_DIR)/$(MODULE)
	$(CP) $(PARSERS_CPP_PUBHEADERS) $(PARSERS_C_FILES) $(XML_INC_DIR)/$(MODULE)

# this may generate unnecessary dependencies, but it makes life easier
depend:: includes
	$(MAKE_DEPEND) $(XML_INCL) *.cpp > $(DEPFILE)

clean::
	@echo "Making clean in $(MODULE) ..."
	$(RM2) $(addprefix $(XML_OBJ_DIR)/,$(PARSERS_CPP_OBJECTS))

distclean::	clean
	$(RM) Makefile $(DEPFILE)
	@echo "Removing all $(MODULE) header files ..."
	$(RM2) $(addprefix $(XML_INC_DIR)/$(MODULE)/,$(PARSERS_CPP_PUBHEADERS))

install::
	-mkdir -p $(DESTDIR)$(PREFIX_INCLUDE)/$(MODULE)
	$(CP) $(PARSERS_CPP_PUBHEADERS) $(PARSERS_C_FILES) $(DESTDIR)$(PREFIX_INCLUDE)/$(MODULE)
