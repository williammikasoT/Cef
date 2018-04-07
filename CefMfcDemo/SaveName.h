#pragma once


// CSaveName 对话框

class CSaveName : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveName)

public:
	CSaveName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSaveName();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSAVENAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
};
