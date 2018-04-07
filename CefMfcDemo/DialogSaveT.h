#pragma once


// CDialogSaveT 对话框

class CDialogSaveT : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSaveT)

public:
	CDialogSaveT(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSaveT();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSAVET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonok();
};
