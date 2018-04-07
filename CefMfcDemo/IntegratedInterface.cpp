// IntegratedInterface.cpp : ʵ���ļ�
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
//#       pragma comment(lib, "..\\Lib\\DuiLib_ud.lib")  //��Ϊ������Ŀ¼����DuiLib�������ȥ�������ļ�
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

// CIntegratedInterface �Ի���

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


// CIntegratedInterface ��Ϣ�������

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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//CPaintManagerUI::SetInstance(AfxGetInstanceHandle());                    // ָ��duilib��ʵ��
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());    // ָ��duilib��Դ��·��������ָ��Ϊ��exeͬĿ¼
	//::CoInitialize(NULL);  // �ǵ��ͷ�::CoUninitialize();

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

	//CRect rect;		//��Ӧ�����С��ʹ��
	//GetClientRect(&rect);
	//Old.x = rect.right - rect.left;
	//Old.y = rect.bottom - rect.top;

	
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_SHOW);
	pListBox->AddString(_T("���������Ϣ"));
	pListBox->AddString(_T("���ۺϽ���"));
	pListBox->AddString(_T("���ɻ�������"));   
	pListBox->AddString(_T("��������������"));
	pListBox->SetCurSel(0);
	
	CFont font;
	font.CreatePointFont(160,_T("��ϸ����"));
	pListBox->SetFont(&font);


	//GetClientRect(&m_rect);

	return TRUE;
}

void CIntegratedInterface::ChangeSize(UINT nID, int x, int y) //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{

	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL) //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{
		CRect rec;
		pWnd->GetWindowRect(&rec); //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec); //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left = rec.left*x / m_rect.Width(); //���ձ��������ռ����λ��
		rec.top = rec.top*y / m_rect.Height() ;
		rec.bottom = rec.bottom*y / m_rect.Height() ;
		rec.right = rec.right*x / m_rect.Width() ;
		pWnd->MoveWindow(rec); //�����ؼ�

	}
}
void CIntegratedInterface::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	//if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	//{
	//	float fsp[2];
	//	POINT Newp; //��ȡ���ڶԻ���Ĵ�С
	//	CRect recta;
	//	GetClientRect(&recta);     //ȡ�ͻ�����С  
	//	Newp.x = recta.right - recta.left;
	//	Newp.y = recta.bottom - recta.top;
	//	fsp[0] = (float)Newp.x / Old.x;
	//	fsp[1] = (float)Newp.y / Old.y;
	//	CRect Rect;
	//	int woc;
	//	CPoint OldTLPoint, TLPoint; //���Ͻ�
	//	CPoint OldBRPoint, BRPoint; //���½�
	//	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�  
	//	while (hwndChild)
	//	{
	//		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
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
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
	}
	else
	{
		CDialogEx::OnPaint();
	}
}




