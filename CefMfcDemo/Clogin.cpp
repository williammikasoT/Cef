// Clogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "Clogin.h"
#include "afxdialogex.h"
#include "IntegratedInterface.h"

// Clogin �Ի���

IMPLEMENT_DYNAMIC(Clogin, CDialogEx)

Clogin::Clogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{


}

Clogin::~Clogin()
{
}

void Clogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Clogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &Clogin::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL Clogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	return true;
}


void Clogin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	CString str_User;
	GetDlgItem(IDC_EDIT_USER)->GetWindowTextW(str_User);
	CString str_Password;
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowTextW(str_Password);
	if (!(str_User == "admin" && str_Password == "admin"))
	{	
			MessageBox(L"�������");
	}
	else
	{
		//������һ���Ի���
		CIntegratedInterface inteface;
		inteface.DoModal();
	}
}

void Clogin::OnPaint()
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
	}
	else
	{
		//CDialogEx::OnPaint();
		//CRect rc;
		//GetWindowRect(&rc);
		//CImage mImage;
		//if (mImage.Load(_T("1.png")) == S_OK)
		//{
		//	//������ͼƬ��������ʹ��ڴ�Сһ��  
		//	mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		//}

		CPaintDC dc(this);;
		CRect rect;
		GetClientRect(&rect);
		dc.FillSolidRect(rect,RGB(190,190,190));
	}
}