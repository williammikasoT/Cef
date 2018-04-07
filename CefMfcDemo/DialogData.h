#pragma once
#include "SimpleClient.h"
#include "afxwin.h"
#include "CefBrowser.h"

#include "CefBrowserEventHandler.h"

// CDialogData �Ի���

class CDialogData : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogData)

public:
	CDialogData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogData();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void resize(UINT nType);
	virtual BOOL OnInitDialog();
	POINT Old;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonfilter();
	afx_msg void OnBnClickedButtonrfid();

};
