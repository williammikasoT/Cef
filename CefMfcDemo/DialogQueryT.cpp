// DialogQueryT.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogQueryT.h"
#include "afxdialogex.h"
#include"filefunc.h"
#include "CefMfcDemoDlg.h"

#define FILENAMEX L"_x.txt"
#define FILENAMEY L"_y.txt"

//#define FILEPATH  L"../WSsystem/TextData/"  //别人调用我的程序时使用
//#define FILEPATH  L"TextData/"


// CDialogQueryT 对话框

IMPLEMENT_DYNAMIC(CDialogQueryT, CDialogEx)

CDialogQueryT::CDialogQueryT(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGQUERYT, pParent)
{

}

CDialogQueryT::~CDialogQueryT()
{
}

void CDialogQueryT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}




BEGIN_MESSAGE_MAP(CDialogQueryT, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTONPICT, &CDialogQueryT::OnBnClickedButtonpict)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDialogQueryT::OnNMDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CDialogQueryT::OnNMRClickList1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDialogQueryT::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDialogQueryT 消息处理程序

std::list<CString> GetFileFromDir(CString csDirPath)
{
	std::list<CString> mFileList;
	csDirPath += "\\*.txt";
	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];
	//mbstowcs(fn,csDirPath.GetBuffer(),999);  
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	mFileList.push_back(fileData.cFileName);
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState) {
		//wcstombs(line,(const char*)fileData.cFileName,259);  
		mFileList.push_back(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
	return mFileList;
}

void OnGetAttr(CString mstrFile,CString& ssize,CString& sdate)
{
	CFileStatus rStatus;//结构体
	if (CFile::GetStatus(mstrFile, rStatus))
	{
		ssize.Format(L"%d字节", rStatus.m_size);                      //文件大小
		sdate = rStatus.m_ctime.Format(L"%Y年%m月%d日 %H:%M:%S");     //创建时间
	}
}

BOOL CDialogQueryT::OnInitDialog()
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

	m_list.InsertColumn(0, TEXT("文件名"), 0, 120);
	m_list.InsertColumn(1, TEXT("大小"), 0, 80);
	m_list.InsertColumn(2, TEXT("时间"), 0, 160);

	CString str,ssize,sdate;
	std::list<CString> mFileList = GetFileFromDir(FILEPATH);
	std::list<CString>::iterator its = mFileList.begin();
	for (int i = 0;its != mFileList.end();its++)			// 打印出文件夹下的.txt
	{
		m_list.InsertItem(i, *its);
		str = FILEPATH + *its;
		OnGetAttr(str, ssize, sdate);
		m_list.SetItemText(i, 1,ssize );
		m_list.SetItemText(i, 2, sdate);

		i++;
	}


	return TRUE;
}


void GetFilePathName(CString sbuf, CString &namex, CString &namey)
{
	namex = sbuf + FILENAMEX;
	namey = sbuf + FILENAMEY;
	namex = FILEPATH + namex;
	namey = FILEPATH + namey;
}

//void CDialogQueryT::OnBnClickedButtonpict()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString sbuf, sy, sx, sbufx, sbufy, strInfo, name, bookName, str;
//	int iCount = m_list.GetItemCount();
//	int j = 0;
//	//可以多选然后删除
//	for (int i = iCount; i >= 0; i--)
//	{
//		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
//		{
//			bookName = m_list.GetItemText(i, 0);
//		}
//	}
//	sbuf = bookName.Right(6);
//	if ( sbuf == FILENAMEX)
//	{
//		sx = bookName;
//		sx = FILEPATH + sx;
//		name = sy = bookName.Left(bookName.GetLength()-6);
//		sy += FILENAMEY;
//		sy = FILEPATH + sy;
//	}
//	else
//	{
//		sy = bookName;
//		sy = FILEPATH + sy;
//		name = sx = bookName.Left(bookName.GetLength() - 6);
//		sx += FILENAMEX;
//		sx = FILEPATH + sx;
//	}
//	if (!ReadData(sx, sy, sbufx, sbufy))  //x是时间，y是浓度
//	{
//		MessageBox(L"读取数据失败");
//		return;
//	}
//	strInfo.Format(_T("clear();"));
//	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
//	pDlg->ExecuteJS(strInfo);
//	pDlg->pirt_real(sbufx, sbufy);
//
//	pDlg->GetDlgItem(IDC_EDITID)->SetWindowTextW(name);
//}


/*
	bookName传进来的名字
	sy返回出去的路径名字
	sx返回出去的路径命令
*/
void GetPartName(CString  bookName, CString& sx, CString& sy)
{
	CString name, sbuf;
	sbuf = bookName.Right(6);
	if (sbuf == FILENAMEX)
	{
		sx = bookName;
		sx = FILEPATH + sx;
		name = sy = bookName.Left(bookName.GetLength() - 6);
		sy += FILENAMEY;
		sy = FILEPATH + sy;
	}
	else
	{
		sy = bookName;
		sy = FILEPATH + sy;
		name = sx = bookName.Left(bookName.GetLength() - 6);
		sx += FILENAMEX;
		sx = FILEPATH + sx;
	}
}

void CDialogQueryT::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString sbuf, sy, sx, sbufx, sbufy, strInfo, name, bookName, str;
	int iCount = m_list.GetItemCount();
	int j = 0;
	//可以多选然后删除
	for (int i = iCount; i >= 0; i--)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			bookName = m_list.GetItemText(i, 0);
		}
	}
	GetPartName(bookName, sx, sy);
	if (!ReadData(sx, sy, sbufx, sbufy))  //x是时间，y是浓度
	{
		MessageBox(L"读取数据失败");
		return;
	}
	strInfo.Format(_T("clear();"));
	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
	pDlg->ExecuteJS(strInfo);
	pDlg->pirt_real(sbufx, sbufy);
}


void CDialogQueryT::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//if (pNMItemActivate->iItem != -1)
	//{
	//	DWORD dwPos = GetMessagePos();
	//	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	//	CMenu menu;
	//	/*VERIFY(menu.LoadMenu(IDR_MENU1));
	//	CMenu* popup = menu.GetSubMenu(0);
	//	ASSERT(popup != NULL);
	//	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);*/
	//}
	//获取鼠标坐标
	//CPoint ptCurSel(0, 0);
	//GetCursorPos(&ptCurSel);
	////转换为当前控件坐标系的坐标
	//m_list.ScreenToClient(&ptCurSel);
	//LVHITTESTINFO HitTestInfo;
	//HitTestInfo.pt = ptCurSel;
	////判断坐标命中第几项
	//int nItem = m_list.HitTest(&HitTestInfo);
	//如果有选中项
	
	*pResult = 0;
}


void CDialogQueryT::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString bookName, sx, sy;
	int iCount = m_list.GetItemCount();
	for (int i = iCount; i >= 0; i--)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			bookName = m_list.GetItemText(i, 0);
		}
	}
	GetPartName(bookName, sx, sy);
	CFile TempFile;
	if (PathFileExists(sx)) {
		if (MessageBox(L"是否删除此文件？", L"提示", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
		{
			return;
		}
		TempFile.Remove(sx);
		TempFile.Remove(sy);
	}
	m_list.DeleteAllItems();
	OnInitDialog();
}
