#pragma once
#include "afxcmn.h"


// CDialogQueryT �Ի���

class CDialogQueryT : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogQueryT)

public:
	CDialogQueryT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogQueryT();
	virtual BOOL OnInitDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGQUERYT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	//afx_msg void OnBnClickedButtonpict();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelete();
};
