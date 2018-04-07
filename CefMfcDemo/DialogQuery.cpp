// DialogQuery.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogQuery.h"
#include "afxdialogex.h"
#include "filefunc.h"
#include "CefMfcDemoDlg.h"
#include "filefunc.h"

#define FILENAMEX L"_x.txt"
#define FILENAMEY L"_y.txt"
#define FILEPATH  L"TextData/"
#define DBINDEX_NUM  3
#define DBINDEX_PATH 5

// CDialogQuery 对话框

IMPLEMENT_DYNAMIC(CDialogQuery, CDialogEx)

CDialogQuery::CDialogQuery(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGQUERY, pParent)
{

}

CDialogQuery::~CDialogQuery()
{
}

void CDialogQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DataCtrl);
}


BEGIN_MESSAGE_MAP(CDialogQuery, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONQUERY, &CDialogQuery::OnBnClickedButtonquery)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTONPICT, &CDialogQuery::OnBnClickedButtonpict)
END_MESSAGE_MAP()


// CDialogQuery 消息处理程序
BOOL CDialogQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//居中
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);

	m_list.InsertColumn(0, TEXT("浓度"), 0, 100);
	m_list.InsertColumn(1,TEXT("时间"),0,100);
	m_list.InsertColumn(2, TEXT("编号"), 0, 100);
	m_list.InsertColumn(3,TEXT("文件名"),0,100);	 //对应数据库的路径

	if (!ConnectDB())
	{
		AfxMessageBox(TEXT("连接数据库失败"));
		return FALSE;
	}

	return TRUE;
}

BOOL CDialogQuery::ConnectDB()
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


void CDialogQuery::GetFilePathName(CString sbuf,CString &namex,CString &namey)
{
	namex = sbuf + FILENAMEX;
	namey = sbuf + FILENAMEY;
	namex = FILEPATH + namex;
	namey = FILEPATH + namey;
}

void CDialogQuery::ShowListData(CString sbufx,CString sbufy,CString sid,CString sname)
{
	std::list<CString> ls, lsy;
	CstringToList(sbufx, ls);
	CstringToList(sbufy, lsy);
	std::list<CString>::iterator its = ls.begin();
	std::list<CString>::iterator itsy = lsy.begin();
	int i = 0;
	for (; its != ls.end(); its++)
	{
		m_list.InsertItem(i, *itsy++);
		m_list.SetItemText(i, 1, *its);
		i++;
	}
	for (int num = 0; num < i; num++)
	{
		m_list.SetItemText(num, 2, sid);
		m_list.SetItemText(num,3, sname);
	}
}

CString CDialogQuery::MysqlToCString(MYSQL_ROW mrow,int num) {
	std::string s;
	CString sname;
	s = mrow[num];
	sname = s.c_str();
	return sname;
}


void CDialogQuery::OnBnClickedButtonquery()
{

	//1. 把.txt以好分隔标识读出数据，在Listctrl显示 2.把读出来的数据调用js画图显示波形 3.

	m_list.DeleteAllItems();

	MYSQL_RES* mres = NULL;
	MYSQL_ROW mrow = NULL;
	CString sbuf, sy, sx,sbufx,sbufy,sname;
	GetDlgItem(IDC_EDITID)->GetWindowTextW(sbuf);
	if (!sbuf.IsEmpty())
	{
		GetFilePathName(sbuf, sx, sy);
		if (!ReadData(sx, sy, sbufx, sbufy))  //x是时间，y是浓度
		{
			MessageBox(L"读取数据失败");
			return;
		}
		CString  query;
		query.Format(TEXT("select * from save where 路径 = '%s';"), sbuf);
		char*p = CStringToChar(query);
		if (mysql_query(&m_mysql, p))
			return;
		p = NULL;
		mres = mysql_store_result(&m_mysql);				 //获取结果集
		mrow = mysql_fetch_row(mres);						 //获得行
		CString sid = MysqlToCString(mrow,DBINDEX_NUM);
		ShowListData(sbufx, sbufy,sid,sbuf);
	}
	else
	{
		// 按时间查找
		CString strfind;
		SYSTEMTIME st;
		m_DataCtrl.GetTime(&st);
		strfind.Format(TEXT("select * from save where 日期 between UNIX_TIMESTAMP('%d-%d-%d 00:00:00') and UNIX_TIMESTAMP('%d-%d-%d 23:59:59')"), st.wYear, st.wMonth, st.wDay, st.wYear, st.wMonth, st.wDay);
		USES_CONVERSION;
		char* p=T2A(strfind.GetBuffer(0));
		if (mysql_query(&m_mysql, p))
			return;
		p = NULL;
		mres = mysql_store_result(&m_mysql);   
		while (mrow = mysql_fetch_row(mres))
		{
			CString sname = MysqlToCString(mrow, DBINDEX_PATH);
			CString sid = MysqlToCString(mrow, DBINDEX_NUM);
			GetFilePathName(sname, sx, sy);
			if (!ReadData(sx, sy, sbufx, sbufy))  //x是时间，y是浓度
			{
					MessageBox(L"读取数据失败");
					return;
			}
			CString str = stringToCString( mrow[DBINDEX_PATH]);
			ShowListData(sbufx, sbufy, sid,str);
		}
	}
	
}


void CDialogQuery::OnBnClickedButtonpict()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sbuf, sy, sx, sbufx, sbufy,strInfo;
	GetDlgItem(IDC_EDITID)->GetWindowTextW(sbuf);
	if (sbuf.IsEmpty())
	{
		MessageBox(L"输入文件名");
		return;
	}

	GetFilePathName(sbuf, sx, sy);
	if (!ReadData(sx, sy, sbufx, sbufy))  //x是时间，y是浓度
	{
		MessageBox(L"读取数据失败");
		return;
	}

	strInfo.Format(_T("clear();"));
	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
	pDlg->ExecuteJS(strInfo);
	pDlg->pirt_real(sbufx,sbufy);
}
