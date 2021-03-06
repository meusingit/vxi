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
 * $Log: StdAfx.h,v $
 * Revision 1.2  2004/09/08 13:55:35  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.1.1.1  2002/02/01 22:21:40  peiyongz
 * sane_include
 *
 * Revision 1.3  2000/06/03 00:28:55  andyh
 * COM Wrapper changes from Curt Arnold
 *
 * Revision 1.2  2000/03/30 02:00:12  abagchi
 * Initial checkin of working code with Copyright Notice
 *
 */

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__975CB5CC_234E_4CA0_940E_DA102634BF51__INCLUDED_)
#define AFX_STDAFX_H__975CB5CC_234E_4CA0_940E_DA102634BF51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#define DOMDocument _MSXMLDOMDocument
#define XMLHTTPRequest _MSXMLHTTPRequest
#define CLSID_DOMDocument CLSID_MSDOMDocument
#define CLSID_XMLHTTPRequest CLSID_MSXMLHTTPRequest

//
//   suppress MSXML.H since we duplicate some of the information
//      in xml4com.h
//

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <comdef.h>
#include <ExDisp.h>
#include <ShlGuid.h>
#include <stdio.h>
#include <process.h>
#include <Wininet.h>

#undef DOMDocument
#undef XMLHTTPRequest
#undef CLSID_DOMDocument
#undef CLSID_XMLHTTPRequest

//
//   These are defined in xml4dom_i.c which is included in xml4dom.cpp
//
//
extern const IID CLSID_DOMDocument;
extern const IID CLSID_XMLHTTPRequest;
extern const IID LIBID_Xerces;

const long	MSG_READY_STATE_CHANGE = WM_APP + 0x0001;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__975CB5CC_234E_4CA0_940E_DA102634BF51__INCLUDED)
