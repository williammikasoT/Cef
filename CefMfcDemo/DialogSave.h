#pragma once
#include "mysql/mysql.h"
#include "afxcmn.h"
#include <vector>
#include "afxdtctl.h"
#pragma comment(lib, "mysql/libmysql.lib")

#define HOST	"localhost"
#define USER	"root"
#define PASSW	"secret"
#define DBNAME  "cefdata"
#define PORT    3306

// CDialogSave �Ի���

class CDialogSave : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSave)

public:
	CDialogSave(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSave();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSAVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonok();
	BOOL ConnectDB();
	MYSQL m_mysql;
	CDateTimeCtrl m_dateCtrl;
};
