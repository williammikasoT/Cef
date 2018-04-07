
// CefMfcDemoDlg.h : ͷ�ļ�
// �ںܶ�汾��Cef���������˶��߳���Ϣѭ�����ᵼ�³����ڽ���ʱ�����жϣ�������Cef��bug��������release�汾��Cef��û�����⡣
// ��2623��2526�汾��Debugģʽ�У����������multi_threaded_message_loop���������˳�ʱ���ض��ᴥ���жϡ��������Cef��bug���ڹٷ�demo��Ҳ��������⣬������Releaseģʽ����û������ġ�
// �����ʹ��Cefģ��������һЩ�������������쳣��������ʹ��releaseģʽ+���������ģʽ������һ�Σ��ܶ����ⶼ��debugģʽ���ߵ�����ģʽ���µ�

#pragma once

#include "SimpleClient.h"
#include "afxwin.h"
#include "CefBrowser.h"

#include "CefBrowserEventHandler.h"
#include "mscomm1.h"
#include "Commdlg.h" 

// CCefMfcDemoDlg �Ի���
class CCefMfcDemoDlg : public CDialogEx
{
// ����
public:
	CCefMfcDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CEFMFCDEMO_DIALOG };
	CefRefPtr<CCefBrowserEventHandler>   m_simpleClient;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//CefRefPtr<CSimpleClient>  m_simpleClient;
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	afx_msg BOOL USBConnect();
	afx_msg void USBStart();
	afx_msg void  split(int numTest, char *p_x, char *p_y, int num,CString &x_vlue, CString &y_vlue);
	static  DWORD  WINAPI MyThreadFunction(LPVOID pParam);
	static  DWORD  WINAPI MyThreadUSBStart(LPVOID pParam);
	afx_msg bool InitCEF();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg long str_to_long_time();
	afx_msg void pirt_mode(CString sX,CString sY);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void resize();
	char* cstring_to_pchar(CString sStarOder);
	afx_msg void ExecuteJS(CString FunName);
	afx_msg  void pirt_real(CString data_x, CString data_y);
	afx_msg void OnBnClickedButtonconnect();
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtoncgabge();
	afx_msg void OnBnClickedButtoncgabge2();
	void ChangeSize(UINT nID, int x, int y);
	bool ReadText(CString name_x, CString name_y);
	afx_msg void OnCbnSelchangeCombopict();
	afx_msg void OnBnClickedButtonquery();

	//virtual BOOL OnEraseBkgnd(CDC* pDC);


	
	CRect m_rect;
	CComboBox m_cbPict;
	POINT Old;
	CCommdlg* m_pDlgd;
	//afx_msg void OnBnClickedButtonOpen();
	DECLARE_EVENTSINK_MAP()
	bool m_blUseCOM;
};
