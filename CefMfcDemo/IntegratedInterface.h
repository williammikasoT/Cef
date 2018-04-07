#pragma once
#include "CefMfcDemoDlg.h"
#include "DialogStimulator.h"
#include "DialogData.h"

// CIntegratedInterface �Ի���

class CIntegratedInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CIntegratedInterface)

public:

	CIntegratedInterface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIntegratedInterface();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangeSize(UINT nID, int x, int y);
	CRect m_rect;
	CDialogStimulator m_pDlgs;// = new CDialogStimulator();;
	CCefMfcDemoDlg m_pDlgc;// = new CCefMfcDemoDlg();
	CDialogData m_pDlgd;

	POINT Old;
	void resize();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INTEGRATEDINTERFACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListShow();
};
