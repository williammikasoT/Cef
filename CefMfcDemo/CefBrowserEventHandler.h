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
	, public CefDisplayHandler// 显示变化事件
	, public CefLoadHandler   // 加载错误事件
	, public CefLifeSpanHandler   // 声明周期事件
								  //, public CefContextMenuHandler// 上下文菜单事件
								  //, public CefDialogHandler// 对话框事件
								  //, public CefDownloadHandler// 下载事件
								  //, public CefDragHandler// 拖拽事件
								  //, public CefFindHandler// 查找事件
								  //, public ...
{
public:
	CCefBrowserEventHandler(void);
	virtual ~CCefBrowserEventHandler(void);
public:
	// CefClient 事件处理器,如果没有对应处理器则默认使用内部处理器
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