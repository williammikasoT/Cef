// DialogSave.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogSave.h"
#include "afxdialogex.h"


// CDialogSave �Ի���

IMPLEMENT_DYNAMIC(CDialogSave, CDialogEx)

CDialogSave::CDialogSave(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGSAVE, pParent)
{

}

CDialogSave::~CDialogSave()
{
}

void CDialogSave::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dateCtrl);
}


BEGIN_MESSAGE_MAP(CDialogSave, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONOK, &CDialogSave::OnBnClickedButtonok)
END_MESSAGE_MAP()


// CDialogSave ��Ϣ�������
BOOL CDialogSave::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CRect rtDesk; //����
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);

	if (!ConnectDB())
	{
		AfxMessageBox(TEXT("�������ݿ�ʧ��"));
		return FALSE;
	}

	return TRUE;
}

BOOL CDialogSave::ConnectDB()
{
	//��ʼ�����ݿ�
	mysql_init(&m_mysql);
	//�������ݿ�����ʽ
	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	if (!mysql_real_connect(&m_mysql, HOST, USER, PASSW, DBNAME, PORT, NULL, 0))
		return FALSE;
	return TRUE;
}

void CDialogSave::OnBnClickedButtonok()
{
	// ��������
	CString query;
	CString csname, cslocat, csid, csstaff, csbuf, cspath;
	int num;
	GetDlgItem(IDC_EDITNAME)->GetWindowTextW(csname);
	GetDlgItem(IDC_EDITLOCAT)->GetWindowTextW(cslocat);
	GetDlgItem(IDC_EDITID)->GetWindowTextW(csid);
	GetDlgItem(IDC_EDITSTAFF)->GetWindowTextW(csstaff);
	GetDlgItem(IDC_EDITPATH)->GetWindowTextW(cspath);

	CTime time;
	CString str;
	m_dateCtrl.GetTime(time);
	str.Format(L"%u", time.GetTime());
	long int day = _ttoi(str);

	if (csname.IsEmpty() ||cslocat.IsEmpty() ||csid.IsEmpty() || csstaff.IsEmpty()||cspath.IsEmpty() )
	{
		MessageBox(L"�����ֶ�");
		return ;
	}

	query.Format(TEXT("insert into save values(NULL,'%s','%s','%s','%s','%s',%d);"), csname, cslocat, csid, csstaff, cspath, day);
	USES_CONVERSION;
	char*p = T2A(query.GetBuffer(0));
	if (mysql_query(&m_mysql, p))
	{
		AfxMessageBox(TEXT("��������ʧ�ܣ�"));
		return ;
	}
	else{
		AfxMessageBox(TEXT("���ݱ���ɹ�"));
	}
	
}
