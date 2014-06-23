// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void PostDataTest(void)
{
	CoInitialize(NULL);

	MSXML2::IXMLDOMDocument2Ptr pXMLDoc = NULL;
	pXMLDoc.CreateInstance(DOM_CLSID);
	VARIANT_BOOL vt = pXMLDoc->load(_variant_t("C:\\Default.xml"));
	if (vt == VARIANT_FALSE)
		return;
	_bstr_t xml = pXMLDoc->xml;

	IWinHttpClientWrapperPtr whcw;
	HRESULT hr = whcw.CreateInstance(__uuidof(WinHttpClientWrapper));
	if (SUCCEEDED(hr))
	{
		whcw->Url = L"http://localhost/Facade/audit";
		whcw->Proxy = L"proxy.ors.local:8080";
		_bstr_t response = whcw->PostData(xml);

		whcw.Release();
	}
	pXMLDoc.Release();
	CoUninitialize();
}

int _tmain(int argc, _TCHAR* argv[])
{
	PostDataTest();	

	return 0;
}

