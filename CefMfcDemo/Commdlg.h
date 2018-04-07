#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CCommdlg �Ի���

class CCommdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommdlg)

public:
	CCommdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommdlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COMM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	int m_iFirst = 0;   //������¼�洢�ַ���
	afx_msg void OnBnClickedButtonStart();
	CTime tLast;
	afx_msg void SaveData(CString sbuf);
	afx_msg void OnClose();
	afx_msg BOOL OpenDevicei();
	DECLARE_EVENTSINK_MAP()
};
