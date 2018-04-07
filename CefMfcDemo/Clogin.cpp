// Clogin.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "Clogin.h"
#include "afxdialogex.h"
#include "IntegratedInterface.h"

// Clogin 对话框

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
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString str_User;
	GetDlgItem(IDC_EDIT_USER)->GetWindowTextW(str_User);
	CString str_Password;
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowTextW(str_Password);
	if (!(str_User == "admin" && str_Password == "admin"))
	{	
			MessageBox(L"密码错误");
	}
	else
	{
		//弹出下一个对话框
		CIntegratedInterface inteface;
		inteface.DoModal();
	}
}

void Clogin::OnPaint()
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
	}
	else
	{
		//CDialogEx::OnPaint();
		//CRect rc;
		//GetWindowRect(&rc);
		//CImage mImage;
		//if (mImage.Load(_T("1.png")) == S_OK)
		//{
		//	//这里让图片绘制区域和窗口大小一致  
		//	mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		//}

		CPaintDC dc(this);;
		CRect rect;
		GetClientRect(&rect);
		dc.FillSolidRect(rect,RGB(190,190,190));
	}
}