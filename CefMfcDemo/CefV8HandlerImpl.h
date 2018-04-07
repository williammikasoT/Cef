#pragma once
#include "D:\cef\cef_binary_3.3239.1710.g85f637a_windows32\include\cef_v8.h"
class CefV8HandlerImpl :
	public CefV8Handler
{
public:
	CefV8HandlerImpl();
	virtual ~CefV8HandlerImpl();
public:
	/**
	*  CefV8Handler Methods, Which will be called when the V8 extension
	*  is called in the Javascript environment
	*/
 virtual bool Execute(const CefString& name
		, CefRefPtr<CefV8Value> object
		, const CefV8ValueList& arguments
		, CefRefPtr<CefV8Value>& retval
		, CefString& exception) OVERRIDE;

	IMPLEMENT_REFCOUNTING(CefV8HandlerImpl);
};

