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
 * $Log: IXMLDOMCharacterDataImpl.h,v $
 * Revision 1.5  2004/09/08 13:55:35  peiyongz
 * Apache License Version 2.0
 *
 * Revision 1.4  2004/02/25 18:38:33  amassari
 * The COM wrapper doesn't use the deprecated DOM anymore
 *
 * Revision 1.3  2003/11/21 12:05:48  amassari
 * Updated version to 2.4
 *
 * Revision 1.2  2003/03/14 12:44:49  tng
 * [Bug 17147] C++ namespace breaks build of XercesCOM DLL
 *
 * Revision 1.1.1.1  2002/02/01 22:21:39  peiyongz
 * sane_include
 *
 * Revision 1.3  2000/07/07 00:12:51  jpolast
 * bug fixes for non-null terminated strings
 *
 * Revision 1.2  2000/03/30 02:00:13  abagchi
 * Initial checkin of working code with Copyright Notice
 *
 */

#ifndef ___ixmldomcharacterdataimpl_h___
#define ___ixmldomcharacterdataimpl_h___

#include "IXMLDOMNodeImpl.h"
XERCES_CPP_NAMESPACE_USE

template <class T, const IID* piid, class tihclass = CComTypeInfoHolder>
class ATL_NO_VTABLE IXMLDOMCharacterDataImpl: public IXMLDOMNodeImpl<T,piid,tihclass>
{
public:

	virtual DOMCharacterData* get_DOMCharacterData() = 0; 
	virtual DOMNode* get_DOMNode() { return get_DOMCharacterData(); } 

	// IXMLDOMCharacterData 

STDMETHOD(get_data)(BSTR  *pVal)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::get_data\n"));

	if (NULL == pVal)
		return E_POINTER;

	*pVal = NULL;
	
	try
	{
		*pVal = SysAllocString(get_DOMCharacterData()->getData());
	}
	catch(...)
	{
		return E_FAIL;
	}
	

	return S_OK;
}

STDMETHOD(put_data)(BSTR newVal)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::put_data\n"));

	try
	{
		get_DOMCharacterData()->setData(newVal);
	}
	catch(...)
	{
		return E_FAIL;
	}
	

	return S_OK;
}

STDMETHOD(get_length)(long  *pVal)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::get_length\n"));

	if (NULL == pVal)
		return E_POINTER;

	*pVal = 0;

	try
	{
		*pVal = get_DOMCharacterData()->getLength();
	}
	catch(...)
	{
		return E_FAIL;
	}

	return S_OK;
}

STDMETHOD(substringData)(long offset, long count, BSTR  *data)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::substringData\n"));

	if (NULL == data)
		return E_POINTER;

	*data = NULL;

	try
	{
        *data = SysAllocString(get_DOMCharacterData()->substringData(offset, count));
	}
	catch(...)
	{
		return E_FAIL;
	}
	
	return S_OK;
}

STDMETHOD(appendData)(BSTR data)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::appendData\n"));

	try
	{
		get_DOMCharacterData()->appendData(data);
	}
	catch(...)
	{
		return E_FAIL;
	}
	

	return S_OK;
}

STDMETHOD(insertData)(long offset, BSTR data)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::insertData\n"));

	try
	{
		get_DOMCharacterData()->insertData(offset, data);
	}
	catch(...)
	{
		return E_FAIL;
	}
	

	return S_OK;
}

STDMETHOD(deleteData)(long offset, long count)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::deleteData\n"));

	try
	{
		get_DOMCharacterData()->deleteData(offset, count);
	}
	catch(...)
	{
		return E_FAIL;
	}
	

	return S_OK;
}

STDMETHOD(replaceData)(long offset, long count, BSTR data)
{
	ATLTRACE(_T("IXMLDOMCharacterDataImpl::replaceData\n"));

	try
	{
		get_DOMCharacterData()->replaceData(offset, count, data);
	}
	catch(...)
	{
		return E_FAIL;
	}
	
	return S_OK;
}

};

#endif // ___ixmldomcharacterdataimpl_h___