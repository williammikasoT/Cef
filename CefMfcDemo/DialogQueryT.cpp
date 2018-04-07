// DialogQueryT.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogQueryT.h"
#include "afxdialogex.h"
#include"filefunc.h"
#include "CefMfcDemoDlg.h"

#define FILENAMEX L"_x.txt"
#define FILENAMEY L"_y.txt"

//#define FILEPATH  L"../WSsystem/TextData/"  //���˵����ҵĳ���ʱʹ��
//#define FILEPATH  L"TextData/"


// CDialogQueryT �Ի���

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


// CDialogQueryT ��Ϣ�������

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
	CFileStatus rStatus;//�ṹ��
	if (CFile::GetStatus(mstrFile, rStatus))
	{
		ssize.Format(L"%d�ֽ�", rStatus.m_size);                      //�ļ���С
		sdate = rStatus.m_ctime.Format(L"%Y��%m��%d�� %H:%M:%S");     //����ʱ��
	}
}

BOOL CDialogQueryT::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//����
	CRect rtDesk;
	CRect rtDlg;
	::GetWindowRect(::GetDesktopWindow(), &rtDesk);
	GetWindowRect(&rtDlg);
	int iXpos = rtDesk.Width() / 2 - rtDlg.Width() / 2;
	int iYpos = rtDesk.Height() / 2 - rtDlg.Height() / 2;
	SetWindowPos(NULL, iXpos, iYpos, 0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);

	m_list.InsertColumn(0, TEXT("�ļ���"), 0, 120);
	m_list.InsertColumn(1, TEXT("��С"), 0, 80);
	m_list.InsertColumn(2, TEXT("ʱ��"), 0, 160);

	CString str,ssize,sdate;
	std::list<CString> mFileList = GetFileFromDir(FILEPATH);
	std::list<CString>::iterator its = mFileList.begin();
	for (int i = 0;its != mFileList.end();its++)			// ��ӡ���ļ����µ�.txt
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString sbuf, sy, sx, sbufx, sbufy, strInfo, name, bookName, str;
//	int iCount = m_list.GetItemCount();
//	int j = 0;
//	//���Զ�ѡȻ��ɾ��
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
//	if (!ReadData(sx, sy, sbufx, sbufy))  //x��ʱ�䣬y��Ũ��
//	{
//		MessageBox(L"��ȡ����ʧ��");
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
	bookName������������
	sy���س�ȥ��·������
	sx���س�ȥ��·������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CString sbuf, sy, sx, sbufx, sbufy, strInfo, name, bookName, str;
	int iCount = m_list.GetItemCount();
	int j = 0;
	//���Զ�ѡȻ��ɾ��
	for (int i = iCount; i >= 0; i--)
	{
		if (m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			bookName = m_list.GetItemText(i, 0);
		}
	}
	GetPartName(bookName, sx, sy);
	if (!ReadData(sx, sy, sbufx, sbufy))  //x��ʱ�䣬y��Ũ��
	{
		MessageBox(L"��ȡ����ʧ��");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//��ȡ�������
	//CPoint ptCurSel(0, 0);
	//GetCursorPos(&ptCurSel);
	////ת��Ϊ��ǰ�ؼ�����ϵ������
	//m_list.ScreenToClient(&ptCurSel);
	//LVHITTESTINFO HitTestInfo;
	//HitTestInfo.pt = ptCurSel;
	////�ж��������еڼ���
	//int nItem = m_list.HitTest(&HitTestInfo);
	//�����ѡ����
	
	*pResult = 0;
}


void CDialogQueryT::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		if (MessageBox(L"�Ƿ�ɾ�����ļ���", L"��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
		{
			return;
		}
		TempFile.Remove(sx);
		TempFile.Remove(sy);
	}
	m_list.DeleteAllItems();
	OnInitDialog();
}
