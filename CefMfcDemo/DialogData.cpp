// DialogData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogData.h"
#include "afxdialogex.h"
//#include "CefMfcDemoDlg.h"
#include "IntegratedInterface.h"

// CDialogData �Ի���

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


// CDialogData ��Ϣ�������


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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 1.���ӳɹ���ʾ����������ID�� 
	GetDlgItem(IDC_BUTTONRFID)->SetWindowTextW(L"���ӳɹ�");
	// 2.�������� �������ֶ��Ժ�������� ,jsonǶ�뵽���ݿ�
	CString sFilter,sName,sId,sAddr,sAddrText;
	GetDlgItem(IDC_EDITFILTER)->GetWindowTextW(sFilter);
	GetDlgItem(IDC_EDITNAME)->GetWindowTextW(sName);
	GetDlgItem(IDC_EDITID)->GetWindowTextW(sId);
	GetDlgItem(IDC_EDITADDR)->GetWindowTextW(sAddr);
	GetDlgItem(IDC_EDITADDRTEXT)->GetWindowTextW(sAddrText);
	if (sFilter.IsEmpty() || sName.IsEmpty() || sId.IsEmpty() || sAddr.IsEmpty() || sAddrText.IsEmpty())
	{
		MessageBox(L"���ݲ���Ϊ��");
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


	//resize(nType);
}

void CDialogData::resize(UINT nType)
{
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		float fsp[2];
		POINT Newp; //��ȡ���ڶԻ���Ĵ�С
		CRect recta;
		GetClientRect(&recta);     //ȡ�ͻ�����С  
		Newp.x = recta.right - recta.left;
		Newp.y = recta.bottom - recta.top;
		fsp[0] = (float)Newp.x / Old.x;
		fsp[1] = (float)Newp.y / Old.y;
		CRect Rect;
		int woc;
		CPoint OldTLPoint, TLPoint; //���Ͻ�
		CPoint OldBRPoint, BRPoint; //���½�
		HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�  
		while (hwndChild)
		{
			woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
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