#include "stdafx.h"
#include "CefV8HandlerImpl.h"


CefV8HandlerImpl::CefV8HandlerImpl()
{
}


CefV8HandlerImpl::~CefV8HandlerImpl()
{

}

bool CefV8HandlerImpl::Execute(const CefString& name  //JavaScript���õ�C++��������
	, CefRefPtr<CefV8Value> object                 //JavaScript�����߶���
	, const CefV8ValueList& arguments              //JavaScript���ݵĲ���
	, CefRefPtr<CefV8Value>& retval                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	, CefString& exception)                        //֪ͨ�쳣��Ϣ��JavaScript
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
