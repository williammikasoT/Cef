// DialogData.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogData.h"
#include "afxdialogex.h"
//#include "CefMfcDemoDlg.h"
#include "IntegratedInterface.h"

// CDialogData 对话框

IMPLEMENT_DYNAMIC(CDialogData, CDialogEx)

CDialogData::CDialogData(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DATA, pParent)
{

}

CDialogData::~CDialogData()
{
}

void CDialogData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogData, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTONFILTER, &CDialogData::OnBnClickedButtonfilter)
	ON_BN_CLICKED(IDC_BUTTONRFID, &CDialogData::OnBnClickedButtonrfid)
END_MESSAGE_MAP()


// CDialogData 消息处理程序


void CDialogData::OnBnClickedButtonfilter()
{
	CIntegratedInterface *pDlg;
	pDlg = new CIntegratedInterface();
	pDlg->Create(IDD_INTEGRATEDINTERFACE, this);
	pDlg->ShowWindow(SW_SHOW);
	//exit(1);
}


void CDialogData::OnBnClickedButtonrfid()
{
	// TODO: 在此添加控件通知处理程序代码
	// 1.连接成功显示过滤吸收器ID号 
	GetDlgItem(IDC_BUTTONRFID)->SetWindowTextW(L"连接成功");
	// 2.保存数据 保留多字段以后可以伸缩 ,json嵌入到数据库
	CString sFilter,sName,sId,sAddr,sAddrText;
	GetDlgItem(IDC_EDITFILTER)->GetWindowTextW(sFilter);
	GetDlgItem(IDC_EDITNAME)->GetWindowTextW(sName);
	GetDlgItem(IDC_EDITID)->GetWindowTextW(sId);
	GetDlgItem(IDC_EDITADDR)->GetWindowTextW(sAddr);
	GetDlgItem(IDC_EDITADDRTEXT)->GetWindowTextW(sAddrText);
	if (sFilter.IsEmpty() || sName.IsEmpty() || sId.IsEmpty() || sAddr.IsEmpty() || sAddrText.IsEmpty())
	{
		MessageBox(L"数据不能为空");
		return;
	}


}
BOOL CDialogData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	GetClientRect(&rect);
	Old.x = rect.right - rect.left;
	Old.y = rect.bottom - rect.top;

	return TRUE;
}

void CDialogData::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	//{
	//	float fsp[2];
	//	POINT Newp; //获取现在对话框的大小
	//	CRect recta;
	//	GetClientRect(&recta);     //取客户区大小  
	//	Newp.x = recta.right - recta.left;
	//	Newp.y = recta.bottom - recta.top;
	//	fsp[0] = (float)Newp.x / Old.x;
	//	fsp[1] = (float)Newp.y / Old.y;
	//	CRect Rect;
	//	int woc;
	//	CPoint OldTLPoint, TLPoint; //左上角
	//	CPoint OldBRPoint, BRPoint; //右下角
	//	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件  
	//	while (hwndChild)
	//	{
	//		woc = ::GetDlgCtrlID(hwndChild);//取得ID
	//		GetDlgItem(woc)->GetWindowRect(Rect);
	//		ScreenToClient(Rect);
	//		OldTLPoint = Rect.TopLeft();
	//		TLPoint.x = long(OldTLPoint.x*fsp[0]);
	//		TLPoint.y = long(OldTLPoint.y*fsp[1]);
	//		OldBRPoint = Rect.BottomRight();
	//		BRPoint.x = long(OldBRPoint.x *fsp[0]);
	//		BRPoint.y = long(OldBRPoint.y *fsp[1]);
	//		Rect.SetRect(TLPoint, BRPoint);
	//		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
	//		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	//	}
	//	Old = Newp;
	//}


	//resize(nType);
}

void CDialogData::resize(UINT nType)
{
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		float fsp[2];
		POINT Newp; //获取现在对话框的大小
		CRect recta;
		GetClientRect(&recta);     //取客户区大小  
		Newp.x = recta.right - recta.left;
		Newp.y = recta.bottom - recta.top;
		fsp[0] = (float)Newp.x / Old.x;
		fsp[1] = (float)Newp.y / Old.y;
		CRect Rect;
		int woc;
		CPoint OldTLPoint, TLPoint; //左上角
		CPoint OldBRPoint, BRPoint; //右下角
		HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件  
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//取得ID
			GetDlgItem(woc)->GetWindowRect(Rect);
			ScreenToClient(Rect);
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = long(OldTLPoint.x*fsp[0]);
			TLPoint.y = long(OldTLPoint.y*fsp[1]);
			OldBRPoint = Rect.BottomRight();
			BRPoint.x = long(OldBRPoint.x *fsp[0]);
			BRPoint.y = long(OldBRPoint.y *fsp[1]);
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		Old = Newp;
	}
}