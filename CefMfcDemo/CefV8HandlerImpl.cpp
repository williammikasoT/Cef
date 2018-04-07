#include "stdafx.h"
#include "CefV8HandlerImpl.h"


CefV8HandlerImpl::CefV8HandlerImpl()
{
}


CefV8HandlerImpl::~CefV8HandlerImpl()
{

}

bool CefV8HandlerImpl::Execute(const CefString& name  //JavaScript调用的C++方法名字
	, CefRefPtr<CefV8Value> object                 //JavaScript调用者对象
	, const CefV8ValueList& arguments              //JavaScript传递的参数
	, CefRefPtr<CefV8Value>& retval                //需要返回给JavaScript的值设置给这个对象
	, CefString& exception)                        //通知异常信息给JavaScript
{
	if (name == _T("addFunction"))
	{
		int32 nSum = 0;
		for (size_t i = 0; i < arguments.size(); ++i)
		{
			if (!arguments[i]->IsInt())
				return false;
			nSum += arguments[i]->GetIntValue();
		}
		retval = CefV8Value::CreateInt(nSum);
		return true;
	}
	else if (name == _T("hehe"))
	{
		retval = CefV8Value::CreateString(_T("hehe hehe!"));
		return true;
	}
	else
	{
		return false;
	}
}
