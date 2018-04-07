#include "stdafx.h"
#include "CefBrowser.h"
#include"CefV8HandlerImpl.h"

CCefBrowser::CCefBrowser()
{
}


CCefBrowser::~CCefBrowser()
{
}
												
CefRefPtr<CefBrowserProcessHandler> CCefBrowser::GetBrowserProcessHandler()
{
	return this;
}

void CCefBrowser::OnContextInitialized()
{

}
CefRefPtr<CefRenderProcessHandler> CCefBrowser::GetRenderProcessHandler()// OVERRIDE
{
	return this;
}

// �󶨵������window��
void CCefBrowser::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) //OVERRIDE
{
	// The var type can accept all object or variable
	CefRefPtr<CefV8Value> window = context->GetGlobal();

	// bind value into window[or you can bind value into window sub node]
	CefRefPtr<CefV8Value> strValue = CefV8Value::CreateString(_T("say yes"));
	window->SetValue(_T("say_yes"), strValue, V8_PROPERTY_ATTRIBUTE_NONE);

	// bind function 
	CefRefPtr<CefV8HandlerImpl> pJsHandler(new CefV8HandlerImpl());
	CefRefPtr<CefV8Value> myFunc = CefV8Value::CreateFunction(_T("addFunction"), pJsHandler);
	window->SetValue(_T("addFunction"), myFunc, V8_PROPERTY_ATTRIBUTE_NONE);

	CefRefPtr<CefV8HandlerImpl> pJsHandler2(new CefV8HandlerImpl());
	CefRefPtr<CefV8Value> myFunc2 = CefV8Value::CreateFunction(_T("hehe"), pJsHandler2);
	window->SetValue(_T("hehe"), myFunc2, V8_PROPERTY_ATTRIBUTE_NONE);
}
void CCefBrowser::OnBeforeChildProcessLaunch(
	CefRefPtr<CefCommandLine> command_line)
{

}

void CCefBrowser::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info)
{

}

void CCefBrowser::OnScheduleMessagePumpWork(int64 delay)
{
}
void CCefBrowser::OnWebKitInitialized()
{
	std::string extensionCode =
		"var g_value=\"global value here\";"
		"var test;"
		"if (!test)"
		"  test = {};"
		"(function() {"
		"  test.myfunc = function() {"
		"    native function hehe(int,int);"
		"    return hehe(10, 50);"
		"  };"
		"})();";


	// �������غ��� native function hehe();" ����в����б���Ҫд���������,������дvar���ͣ��뱾������һֱ
	// ���ñ��غ���    return hehe();"

	// Create an instance of my CefV8Handler object.
	CefRefPtr<CefV8HandlerImpl> handler = new CefV8HandlerImpl();

	// Register the extension.
	CefRegisterExtension("v8/mycode", extensionCode, handler);
}