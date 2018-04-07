#pragma once

#include "SimpleClient.h"
#include "afxwin.h"
#include "CefBrowser.h"
#include "CefBrowserEventHandler.h"

// CDialogStimulator �Ի���

class CDialogStimulator : public CDialogEx
{


public:
	CDialogStimulator(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogStimulator();
	CefRefPtr<CCefBrowserEventHandler>   m_simpleClient;
	//enum { IDD = IDD_DIALOGSTIMULATOR };
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSTIMULATOR };
#endif

	DECLARE_DYNAMIC(CDialogStimulator)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	bool InitCEF();
	afx_msg void OnPaint();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
