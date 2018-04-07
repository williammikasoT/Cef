#pragma once

#include "SimpleClient.h"
#include "afxwin.h"
#include "CefBrowser.h"
#include "CefBrowserEventHandler.h"

// CDialogStimulator 对话框

class CDialogStimulator : public CDialogEx
{


public:
	CDialogStimulator(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogStimulator();
	CefRefPtr<CCefBrowserEventHandler>   m_simpleClient;
	//enum { IDD = IDD_DIALOGSTIMULATOR };
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSTIMULATOR };
#endif

	DECLARE_DYNAMIC(CDialogStimulator)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	bool InitCEF();
	afx_msg void OnPaint();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
