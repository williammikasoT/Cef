#pragma once


// Clogin �Ի���

class Clogin : public CDialogEx
{
	DECLARE_DYNAMIC(Clogin)

public:
	Clogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Clogin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
	virtual BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
