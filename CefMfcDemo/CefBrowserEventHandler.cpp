//#include "stdafx.h"
//#include "CefBrowserEventHandler.h"
//
//
//CCefBrowserEventHandler::CCefBrowserEventHandler()
//{
//}
//
//
//CCefBrowserEventHandler::~CCefBrowserEventHandler()
//{
//}
#include "StdAfx.h"
#include "CefBrowserEventHandler.h"
#include <sstream>
#include <string>
#include "include/base/cef_bind.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "CefV8HandlerImpl.h"

CCefBrowserEventHandler::CCefBrowserEventHandler(void)
{
}

CCefBrowserEventHandler::~CCefBrowserEventHandler(void)
{
}

CefRefPtr<CefDisplayHandler> CCefBrowserEventHandler::GetDisplayHandler() 
{
	return this;
}

CefRefPtr<CefLifeSpanHandler> CCefBrowserEventHandler::GetLifeSpanHandler() 
{
	return this;
}

CefRefPtr<CefLoadHandler> CCefBrowserEventHandler::GetLoadHandler() 
{
	return this;
}

void CCefBrowserEventHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) 
{
	CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
	if (GetParent(hwnd) == AfxGetApp()->m_pMainWnd->GetSafeHwnd())
	{
		AfxGetApp()->m_pMainWnd->SetWindowText(std::wstring(title).c_str());
	}
	else
	{
		::SetWindowText(hwnd, std::wstring(title).c_str());
	}
}

void CCefBrowserEventHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode,
	const CefString& errorText, const CefString& failedUrl) 
{
	CEF_REQUIRE_UI_THREAD();
	if (ERR_ABORTED == errorCode)
		return;

	std::stringstream ss;
	ss << "<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL " << std::string(failedUrl) <<
		" with error " << std::string(errorText) << " (" << errorCode <<
		").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

void CCefBrowserEventHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) 
{
	CEF_REQUIRE_UI_THREAD();
	m_browser_list.push_back(browser);
}

bool CCefBrowserEventHandler::DoClose(CefRefPtr<CefBrowser> browser) 
{
	CEF_REQUIRE_UI_THREAD();
	if (1 == m_browser_list.size())
	{
	}
	return false;
}

void CCefBrowserEventHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) 
{
	CEF_REQUIRE_UI_THREAD();
	for (BrowserList::iterator bit = m_browser_list.begin(); bit != m_browser_list.end(); ++bit)
	{
		if ((*bit)->IsSame(browser)) {
			m_browser_list.erase(bit);
			break;
		}
	}

	if (m_browser_list.empty())
	{
		CefQuitMessageLoop();
	}
}




void CCefBrowserEventHandler::CloseAllBrowser(bool force_close)
{
	if (!CefCurrentlyOn(TID_UI))
	{
		CefPostTask(TID_UI, base::Bind(&CCefBrowserEventHandler::CloseAllBrowser, this, force_close));
		return;
	}

	if (m_browser_list.empty())
		return;

	BrowserList::const_iterator it = m_browser_list.begin();
	for (; it != m_browser_list.end(); ++it)
	{
		(*it)->GetHost()->CloseBrowser(force_close);
	}
}
