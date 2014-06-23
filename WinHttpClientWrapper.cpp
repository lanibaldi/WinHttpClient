// WinHttpClientWrapper.cpp : Implementation of CWinHttpClientWrapper

#include "stdafx.h"
#include "WinHttpClientWrapper.h"
#include "WinHttpClientWrapperUtils.h"

// CWinHttpClientWrapper
void CWinHttpClientWrapper::Init(void)
{
	CWinHttpClientWrapperUtils::InitWorkingFolder(m_bstrWrkFld);
	CWinHttpClientWrapperUtils::CreateLogger(m_pLogger, m_bstrWrkFld);

	m_bstrUserAgent = A2BSTR("Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; InfoPath.2; CIBA; MS-RTC LM 8)");
}

STDMETHODIMP CWinHttpClientWrapper::get_Url(BSTR* pVal)
{
	// TODO: Add your implementation code here
	(*pVal) = m_bstrUrl;

	return S_OK;
}

STDMETHODIMP CWinHttpClientWrapper::put_Url(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bstrUrl = newVal;

	return S_OK;
}

STDMETHODIMP CWinHttpClientWrapper::get_Proxy(BSTR* pVal)
{
	// TODO: Add your implementation code here
	(*pVal) = m_bstrProxy;

	return S_OK;
}

STDMETHODIMP CWinHttpClientWrapper::put_Proxy(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bstrProxy = newVal;

	return S_OK;
}

STDMETHODIMP CWinHttpClientWrapper::PostData(BSTR bstrIn, BSTR* pOut)
{
	// TODO: Add your implementation code here
	try
	{
		// Create client
		m_pLogger->StandardLog(L"Creating client, url:", AMSLOG_SEVERITY_INFO);
		m_pLogger->StandardLog(m_bstrUrl, AMSLOG_SEVERITY_INFO);

		WinHttpClient client(m_bstrUrl);
		
		// Set the proxy 
		m_pLogger->StandardLog(L"Set proxy:", AMSLOG_SEVERITY_INFO);
		m_pLogger->StandardLog(m_bstrProxy, AMSLOG_SEVERITY_INFO);
		client.SetProxy(m_bstrProxy);
	    
		// Set post data.
		m_pLogger->StandardLog(L"Set post data:", AMSLOG_SEVERITY_INFO);
		m_pLogger->StandardLog(bstrIn, AMSLOG_SEVERITY_INFO);
		UINT len = SysStringLen(bstrIn);
		BYTE *byteArray = new BYTE[len+1];
		for (UINT i=0; i<len; i++)		
			byteArray[i] = (BYTE) bstrIn[i];
		byteArray[len] = '\0'; 
		client.SetAdditionalDataToSend(byteArray, len);
		delete byteArray;
		
		// Set request headers.
		wchar_t szSize[50] = L"";
		swprintf_s(szSize, L"%d", len);
		wstring headers = L"Content-Length: ";
		headers += szSize;
		headers += L"\r\nContent-Type: text/xml; charset=utf-8\r\n";
		client.SetAdditionalRequestHeaders(headers);
		m_pLogger->StandardLog(L"Set request headers:", AMSLOG_SEVERITY_INFO);
		BSTR bstrHeaders = SysAllocStringLen(headers.data(), headers.size());
		m_pLogger->StandardLog(bstrHeaders, AMSLOG_SEVERITY_INFO);		

		// Send http post request.
		m_pLogger->StandardLog(L"Send http POST request.", AMSLOG_SEVERITY_INFO);
		client.SendHttpRequest(L"POST");

		wstring wsResponseHeader = client.GetResponseHeader();
		wstring wsResponseContent = client.GetResponseContent();

		BSTR bstrResponseHeader = SysAllocStringLen(wsResponseHeader.data(), wsResponseHeader.size());
		m_pLogger->StandardLog(L"Response header:", AMSLOG_SEVERITY_INFO);
		m_pLogger->StandardLog(bstrResponseHeader, AMSLOG_SEVERITY_INFO);

		BSTR bstrResponseContent = SysAllocStringLen(wsResponseContent.data(), wsResponseContent.size());
		m_pLogger->StandardLog(L"Response Content:", AMSLOG_SEVERITY_INFO);
		m_pLogger->StandardLog(bstrResponseContent, AMSLOG_SEVERITY_INFO);
		(*pOut) = bstrResponseContent;
	}	
	catch(...)
	{
		m_pLogger->StandardLog(L"PostData failed", AMSLOG_SEVERITY_CRITICAL);
		return E_FAIL;
	}

	return S_OK;
}
