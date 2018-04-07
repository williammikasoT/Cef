#pragma once
#include "afxcmn.h"
#include <vector>
#include "mysql/mysql.h"
#include "afxdtctl.h"
#pragma comment(lib, "mysql/libmysql.lib")

#define HOST	"localhost"
#define USER	"root"
#define PASSW	"secret"
#define DBNAME  "cefdata"
#define PORT    3306
// CDialogQuery 对话框

class CDialogQuery : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogQuery)

public:
	CDialogQuery(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogQuery();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGQUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	BOOL ConnectDB();
	MYSQL m_mysql;
	afx_msg void OnBnClickedButtonquery();
	afx_msg void OnBnClickedButtonpict();
	afx_msg void GetFilePathName(CString sbuf, CString &namex, CString &namey);
	afx_msg void ShowListData(CString sbufx, CString sbufy, CString sid, CString sname);
	afx_msg CString MysqlToCString(MYSQL_ROW mrow, int num);

	CListCtrl m_list;
	std::vector<std::string> m_data[100];
	CDateTimeCtrl m_DataCtrl;
};
