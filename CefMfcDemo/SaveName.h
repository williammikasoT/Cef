#pragma once


// CSaveName �Ի���

class CSaveName : public CDialogEx
{
	DECLARE_DYNAMIC(CSaveName)

public:
	CSaveName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSaveName();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSAVENAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
};
