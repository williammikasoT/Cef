#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CCommdlg 对话框

class CCommdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommdlg)

public:
	CCommdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COMM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbo;
	//afx_msg void OnBnClickedButtonOpen();
	CMscomm1 m_mscomm;
	void OnCommMscomm1();
	afx_msg void OnBnClickedButtonClose();
	long lTmpTime, lLastTime, lCurlTime;
	
	virtual BOOL OnInitDialog();
	int com_id[10];
	int m_iFirst = 0;   //用来记录存储字符串
	afx_msg void OnBnClickedButtonStart();
	CTime tLast;
	afx_msg void SaveData(CString sbuf);
	afx_msg void OnClose();
	afx_msg BOOL OpenDevicei();
	DECLARE_EVENTSINK_MAP()
};
