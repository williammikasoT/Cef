// SaveName.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "SaveName.h"
#include "afxdialogex.h"
#include "filefunc.h"

#include "CefMfcDemoDlg.h"
#include "Commdlg.h"
// CSaveName 对话框

IMPLEMENT_DYNAMIC(CSaveName, CDialogEx)

CSaveName::CSaveName(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGSAVENAME, pParent)
{

}

CSaveName::~CSaveName()
{
}

void CSaveName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveName, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CSaveName::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CSaveName 消息处理程序
BOOL CSaveName::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(L"aaa");
	return TRUE;
}


void CSaveName::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sbuf, sx, sy;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextW(sbuf);

	sx = sbuf + L"_x.txt";
	sy = sbuf + L"_y.txt";
	sx = L"TextData/" + sx;
	sx = OTHERPART + sx;
	sy = L"TextData/" + sy;
	sy = OTHERPART + sy;

	// 文件存在删除文件
	CFile TempFile;
	if (PathFileExists(sx)) {
		if (MessageBox(L"此文件名存在是否覆盖？", L"提示", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
		{
			return;
		}
		TempFile.Remove(sx);
		TempFile.Remove(sy);
	}
	
	// 保存数据 这个数据从哪里来 m_strDataTime
	//WriteData(sx, sy, m_strDataTime, m_strDataCul);
	// 现在子对话框不是这个的父对话框
	//CCommdlg *pDlg = (CCommdlg*)this->GetParent();
	//GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(sbuf);
	//pDlg->SaveData();
	//DestroyWindow();  //关闭当前窗口

	//GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(sbuf);
	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
	pDlg->m_pDlgd->SaveData(sbuf);
	DestroyWindow();  
}
