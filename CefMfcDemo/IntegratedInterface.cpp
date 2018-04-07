// IntegratedInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "IntegratedInterface.h"
#include "afxdialogex.h"
#include "Clogin.h"

//#pragma once
//#include "UIlib.h"
//using namespace DuiLib;

//#ifdef _DEBUG
//#   ifdef _UNICODE
//#       pragma comment(lib, "..\\Lib\\DuiLib_ud.lib")  //因为包含的目录就在DuiLib的外面就去其他的文件
//#   else
//#       pragma comment(lib, "..\\Lib\\DuiLib_d.lib")
//#   endif
//#else
//#   ifdef _UNICODE
//#       pragma comment(lib, "..\\Lib\\DuiLib_u.lib")
//#   else
//#       pragma comment(lib, "..\\Lib\\DuiLib.lib")
//#   endif
//#endif

// CIntegratedInterface 对话框

IMPLEMENT_DYNAMIC(CIntegratedInterface, CDialogEx)

CIntegratedInterface::CIntegratedInterface(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INTEGRATEDINTERFACE, pParent) //  
{

}

CIntegratedInterface::~CIntegratedInterface()
{
}

void CIntegratedInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIntegratedInterface, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_SHOW, &CIntegratedInterface::OnLbnSelchangeListShow)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CIntegratedInterface 消息处理程序

//class CDuiFrameWnd : public WindowImplBase
//{
//
//public:
//	virtual LPCTSTR GetWindowClassName() const { return L"DUImainFrame"; }
//	virtual CDuiString GetSkinFile() { return L"hello.xml"; } //duilib hello
//	virtual CDuiString GetSkinFolder() { return L""; }
//
//};

int CIntegratedInterface::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	/*Clogin dlg;
	dlg.DoModal();*/
	return 0;
}

BOOL CIntegratedInterface::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码
	//CPaintManagerUI::SetInstance(AfxGetInstanceHandle());                    // 指定duilib的实例
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());    // 指定duilib资源的路径，这里指定为和exe同目录
	//::CoInitialize(NULL);  // 记得释放::CoUninitialize();

	//CDuiFrameWnd m_duiFrame;
	//m_duiFrame.Create(*this, _T("DUIWnd"), UI_WNDSTYLE_CHILD, 0, 0, 0, 800, 600);
	//m_duiFrame.ShowWindow(TRUE);

	//ShowWindow(SW_SHOWMAXIMIZED);

	//m_pDlgs.Create(IDD_DIALOGSTIMULATOR, this);
	m_pDlgd.Create(IDD_DATA, this);
	//m_pDlgc.Create(IDD_CEFMFCDEMO_DIALOG, this);
	CRect rc;
	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(rc);
	ScreenToClient(rc);
	m_pDlgd.SetWindowPos(GetDlgItem(IDC_STATIC_RECT), rc.left, rc.top, rc.Width(), rc.Height(),SWP_SHOWWINDOW);
	/*m_pDlgc.SetWindowPos(GetDlgItem(IDC_STATIC_RECT), rc.left, rc.top, rc.Width(), rc.Height(), SWP_HIDEWINDOW);
	m_pDlgs.SetWindowPos(GetDlgItem(IDC_STATIC_RECT), rc.left, rc.top, rc.Width(), rc.Height(),SWP_HIDEWINDOW); */

	//CRect rect;		//适应最大化最小化使用
	//GetClientRect(&rect);
	//Old.x = rect.right - rect.left;
	//Old.y = rect.bottom - rect.top;

	
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_SHOW);
	pListBox->AddString(_T("输入身份信息"));
	pListBox->AddString(_T("器综合界面"));
	pListBox->AddString(_T("自由基激发器"));   
	pListBox->AddString(_T("过滤吸收器界面"));
	pListBox->SetCurSel(0);
	
	CFont font;
	font.CreatePointFont(160,_T("超细黑体"));
	pListBox->SetFont(&font);


	//GetClientRect(&m_rect);

	return TRUE;
}

void CIntegratedInterface::ChangeSize(UINT nID, int x, int y) //nID为控件ID，x,y分别为对话框的当前长和宽
{

	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL) //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{
		CRect rec;
		pWnd->GetWindowRect(&rec); //获取控件变化前的大小
		ScreenToClient(&rec); //将控件大小装换位在对话框中的区域坐标
		rec.left = rec.left*x / m_rect.Width(); //按照比例调整空间的新位置
		rec.top = rec.top*y / m_rect.Height() ;
		rec.bottom = rec.bottom*y / m_rect.Height() ;
		rec.right = rec.right*x / m_rect.Width() ;
		pWnd->MoveWindow(rec); //伸缩控件

	}
}
void CIntegratedInterface::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
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
}


void CIntegratedInterface::OnLbnSelchangeListShow()
{
	int nSel = static_cast<CListBox*>(GetDlgItem(IDC_LIST_SHOW))->GetCurSel();
	m_pDlgd.ShowWindow(nSel == 0);
	if (nSel == 1)
	{
		CCefMfcDemoDlg c;
		c.DoModal();
	}
	else if (nSel == 2)
	{
		CDialogStimulator c;
		c.DoModal();
	}
	//m_pDlgc.ShowWindow(nSel == 1);
	//m_pDlgs.ShowWindow(nSel == 2);
}




void CIntegratedInterface::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
	}
	else
	{
		CDialogEx::OnPaint();
	}
}




