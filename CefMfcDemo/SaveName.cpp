// SaveName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "SaveName.h"
#include "afxdialogex.h"
#include "filefunc.h"

#include "CefMfcDemoDlg.h"
#include "Commdlg.h"
// CSaveName �Ի���

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


// CSaveName ��Ϣ�������
BOOL CSaveName::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(L"aaa");
	return TRUE;
}


void CSaveName::OnBnClickedButtonOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sbuf, sx, sy;
	GetDlgItem(IDC_EDIT_NAME)->GetWindowTextW(sbuf);

	sx = sbuf + L"_x.txt";
	sy = sbuf + L"_y.txt";
	sx = L"TextData/" + sx;
	sx = OTHERPART + sx;
	sy = L"TextData/" + sy;
	sy = OTHERPART + sy;

	// �ļ�����ɾ���ļ�
	CFile TempFile;
	if (PathFileExists(sx)) {
		if (MessageBox(L"���ļ��������Ƿ񸲸ǣ�", L"��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
		{
			return;
		}
		TempFile.Remove(sx);
		TempFile.Remove(sy);
	}
	
	// �������� ������ݴ������� m_strDataTime
	//WriteData(sx, sy, m_strDataTime, m_strDataCul);
	// �����ӶԻ���������ĸ��Ի���
	//CCommdlg *pDlg = (CCommdlg*)this->GetParent();
	//GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(sbuf);
	//pDlg->SaveData();
	//DestroyWindow();  //�رյ�ǰ����

	//GetDlgItem(IDC_EDIT_NAME)->SetWindowTextW(sbuf);
	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
	pDlg->m_pDlgd->SaveData(sbuf);
	DestroyWindow();  
}
