#pragma once
#include "afxcmn.h"


// CDialogQueryT 对话框

class CDialogQueryT : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogQueryT)

public:
	CDialogQueryT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogQueryT();
	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGQUERYT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	//afx_msg void OnBnClickedButtonpict();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelete();
};
