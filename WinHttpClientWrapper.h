// WinHttpClientWrapper.h : Declaration of the CWinHttpClientWrapper

#pragma once
#include "resource.h"       // main symbols

#include "OrsUtilitiesWinHttpClient_i.h"
#include "WinHttpClient.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CWinHttpClientWrapper

class ATL_NO_VTABLE CWinHttpClientWrapper :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWinHttpClientWrapper, &CLSID_WinHttpClientWrapper>,
	public IDispatchImpl<IWinHttpClientWrapper, &IID_IWinHttpClientWrapper, &LIBID_OrsUtilitiesWinHttpClientLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CWinHttpClientWrapper()
		: m_pLogger(0), m_bstrWrkFld(L"")
	{
		Init();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_WINHTTPCLIENTWRAPPER)


BEGIN_COM_MAP(CWinHttpClientWrapper)
	COM_INTERFACE_ENTRY(IWinHttpClientWrapper)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(get_Url)(BSTR* pVal);
	STDMETHOD(put_Url)(BSTR newVal);
	STDMETHOD(get_Proxy)(BSTR* pVal);
	STDMETHOD(put_Proxy)(BSTR newVal);
	STDMETHOD(PostData)(BSTR bstrIn, BSTR* pOut);

protected:
	void Init(void);

private:
	BSTR m_bstrUserAgent;
	BSTR m_bstrProxy;
	BSTR m_bstrUrl;

	_bstr_t m_bstrGuid;
	ILoggerPtr m_pLogger;
	_bstr_t m_bstrWrkFld;
};

OBJECT_ENTRY_AUTO(__uuidof(WinHttpClientWrapper), CWinHttpClientWrapper)
