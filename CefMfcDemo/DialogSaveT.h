#pragma once


// CDialogSaveT �Ի���

class CDialogSaveT : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSaveT)

public:
	CDialogSaveT(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSaveT();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSAVET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonok();
};
