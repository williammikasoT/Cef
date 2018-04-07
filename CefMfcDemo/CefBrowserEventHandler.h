#pragma once
//class CCefBrowserEventHandler
//{
//public:
//	CCefBrowserEventHandler();
//	~CCefBrowserEventHandler();
//};

#include <list>
using namespace std;

typedef std::list<CefRefPtr<CefBrowser>> BrowserList;

class CCefBrowserEventHandler
	: public CefClient
	, public CefDisplayHandler// ��ʾ�仯�¼�
	, public CefLoadHandler   // ���ش����¼�
	, public CefLifeSpanHandler   // ���������¼�
								  //, public CefContextMenuHandler// �����Ĳ˵��¼�
								  //, public CefDialogHandler// �Ի����¼�
								  //, public CefDownloadHandler// �����¼�
								  //, public CefDragHandler// ��ק�¼�
								  //, public CefFindHandler// �����¼�
								  //, public ...
{
public:
	CCefBrowserEventHandler(void);
	virtual ~CCefBrowserEventHandler(void);
public:
	// CefClient �¼�������,���û�ж�Ӧ��������Ĭ��ʹ���ڲ�������
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;

public:
	// display handler method
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;

public:
	// load handler method
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) OVERRIDE;

public:
	// display handler meethod
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

	

	//CefRefPtr<CefBrowser>
		BrowserList	GetBrowser() { return m_browser_list; }
public:
	// own method of cef browser event handler
	void CloseAllBrowser(bool bForceClose = true);
private:
	BrowserList m_browser_list;

	IMPLEMENT_REFCOUNTING(CCefBrowserEventHandler);
};