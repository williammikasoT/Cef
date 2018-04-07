// DialogSaveT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogSaveT.h"
#include "afxdialogex.h"
#include "filefunc.h"

#define FILEPATH  L"TextDataInfor/"
//#define FILEPATH  L"TextData/"

// CDialogSaveT �Ի���

IMPLEMENT_DYNAMIC(CDialogSaveT, CDialogEx)

CDialogSaveT::CDialogSaveT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGSAVET, pParent)
{

}

CDialogSaveT::~CDialogSaveT()
{
}

void CDialogSaveT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogSaveT, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONOK, &CDialogSaveT::OnBnClickedButtonok)
END_MESSAGE_MAP()


// CDialogSaveT ��Ϣ�������
BOOL CDialogSaveT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rtDesk; //����
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);

	return TRUE;
}

void CDialogSaveT::OnBnClickedButtonok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString csname, cslocat, csstaff,cspath,csbuf,sbuft;  //���Ǳ�������һ�������Ϣ
	GetDlgItem(IDC_EDITNAME)->GetWindowTextW(csname);
	GetDlgItem(IDC_EDITLOCAT)->GetWindowTextW(cslocat);
	GetDlgItem(IDC_EDITSTAFF)->GetWindowTextW(csstaff);
	GetDlgItem(IDC_EDITPATH)->GetWindowTextW(cspath);
	sbuft = csname + L"," + cslocat + L"," + csstaff;
	csbuf = FILEPATH + cspath + L".txt";
	WriteData(csbuf, sbuft);
}
