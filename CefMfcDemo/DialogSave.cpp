// DialogSave.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogSave.h"
#include "afxdialogex.h"


// CDialogSave 对话框

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


// CDialogSave 消息处理程序
BOOL CDialogSave::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CRect rtDesk; //居中
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);

	if (!ConnectDB())
	{
		AfxMessageBox(TEXT("连接数据库失败"));
		return FALSE;
	}

	return TRUE;
}

BOOL CDialogSave::ConnectDB()
{
	//初始化数据库
	mysql_init(&m_mysql);
	//设置数据库编码格式
	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	if (!mysql_real_connect(&m_mysql, HOST, USER, PASSW, DBNAME, PORT, NULL, 0))
		return FALSE;
	return TRUE;
}

void CDialogSave::OnBnClickedButtonok()
{
	// 插入数据
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
		MessageBox(L"输入字段");
		return ;
	}

	query.Format(TEXT("insert into save values(NULL,'%s','%s','%s','%s','%s',%d);"), csname, cslocat, csid, csstaff, cspath, day);
	USES_CONVERSION;
	char*p = T2A(query.GetBuffer(0));
	if (mysql_query(&m_mysql, p))
	{
		AfxMessageBox(TEXT("插入数据失败！"));
		return ;
	}
	else{
		AfxMessageBox(TEXT("数据保存成功"));
	}
	
}
