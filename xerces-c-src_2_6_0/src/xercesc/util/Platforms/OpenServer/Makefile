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
# $Log: Makefile.in,v $
# Revision 1.4  2004/09/08 13:56:41  peiyongz
# Apache License Version 2.0
#
# Revision 1.3  2004/07/09 16:22:39  peiyongz
# Build on HP-Itanium, aCC A.05.52
#
# Revision 1.2  2002/07/26 16:49:28  tng
# [Bug 2681] Can't build with gcc/g++ not named 'gcc'/'g++'.  Patch from Jonathan Lennox.
#
# Revision 1.1  2002/02/27 22:57:59  peiyongz
# Bug# 6445 Caldera (SCO) OpenServer Port : patch from Martin Kalen
#
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

MODULE = util

include ../../../Makefile.incl

SUBMODULE = Platforms/OpenServer
CPP_PUBHEADERS = OpenServerDefs.hpp
CPP_OBJECTS = OpenServerPlatformUtils.$(TO)

include ../../Makefile.util.submodule

