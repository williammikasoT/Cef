
// CefMfcDemoDlg.h : 头文件
// 在很多版本的Cef里，如果开启了多线程消息循环，会导致程序在结束时触发中断，这属于Cef的bug，不过在release版本的Cef中没有问题。
// 在2623、2526版本，Debug模式中，如果开启了multi_threaded_message_loop，当程序退出时，必定会触发中断。这个属于Cef的bug，在官方demo中也有这个问题，但是在Release模式中是没有问题的。
// 如果在使用Cef模块中遇到一些崩溃或者其他异常现象，请先使用release模式+开启多进程模式再运行一次，很多问题都是debug模式或者单进程模式导致的

#pragma once

#include "SimpleClient.h"
#include "afxwin.h"
#include "CefBrowser.h"

#include "CefBrowserEventHandler.h"
#include "mscomm1.h"
#include "Commdlg.h" 

// CCefMfcDemoDlg 对话框
class CCefMfcDemoDlg : public CDialogEx
{
// 构造
public:
	CCefMfcDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CEFMFCDEMO_DIALOG };
	CefRefPtr<CCefBrowserEventHandler>   m_simpleClient;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//CefRefPtr<CSimpleClient>  m_simpleClient;
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
