// DialogStimulator.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "DialogStimulator.h"
#include "USBTransmit.h"

// CDialogStimulator 对话框

IMPLEMENT_DYNAMIC(CDialogStimulator, CDialogEx)

CDialogStimulator::CDialogStimulator(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGSTIMULATOR, pParent)
{

}

CDialogStimulator::~CDialogStimulator()
{
}

void CDialogStimulator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}




BEGIN_MESSAGE_MAP(CDialogStimulator, CDialogEx)
	//ON_WM_QUERYDRAGICON()
	ON_WM_PAINT()
	//ON_WM_SIZE()
END_MESSAGE_MAP()


// CDialogStimulator 消息处理程序
BOOL CDialogStimulator::OnInitDialog()
{
	CDialogEx::OnInitDialog();

//	InitCEF();

	/*char *readusb = (char*)malloc(100);
	char *p = "{end}\\n";
	int len = strlen(p);
	int ret = USBBulkWriteData(0, EP1_OUT, p, len, 100);
	ret = USBBulkReadData(0, EP1_IN, readusb, 100, 100);*/  //USB写与读


	return TRUE;
}

bool CDialogStimulator::InitCEF()
{
	AfxEnableControlContainer();
	CefMainArgs mainArgs(AfxGetApp()->m_hInstance);
	CefSettings settings;
#ifdef _DEBUG
	settings.single_process = true;
#endif
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	CefRefPtr<CCefBrowser> objApp(new CCefBrowser());
	CefInitialize(mainArgs, settings, objApp.get(), NULL);

	CRect rtBody;
	GetDlgItem(IDC_STATIC_BODY)->GetWindowRect(&rtBody);
	CefWindowInfo cefWindowInfo;
	cefWindowInfo.SetAsChild(GetSafeHwnd(), rtBody);
	CefBrowserSettings browserSetting;
	CefRefPtr<CCefBrowserEventHandler> objEventHandler(new CCefBrowserEventHandler());
	m_simpleClient = objEventHandler;
	CString strPath;
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	CString strUrl = _T("file:///") + strPath + _T("/HtmlPage1.html"); //HtmlPage1
	CefBrowserHost::CreateBrowser(cefWindowInfo, objEventHandler.get(), CefString(strUrl), browserSetting, NULL);




	return TRUE;
}


//void CDialogStimulator::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	RECT rect;
//	GetClientRect(&rect);
//
//	if (m_simpleClient.get())
//	{
//		BrowserList s = m_simpleClient->GetBrowser();
//		BrowserList::iterator itor;
//		itor = s.begin();
//
//		CefRefPtr<CefBrowser> cefBrowser = *itor;
//		if (cefBrowser)
//		{
//			CefWindowHandle hwnd = cefBrowser->GetHost()->GetWindowHandle();
//			::MoveWindow(hwnd, 0, 50, rect.right - rect.left, rect.bottom - 50, true);
//		}
//	}
//
//}

void CDialogStimulator::OnPaint()
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

		// 绘制图标
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CRect rc;
		GetWindowRect(&rc);
		CImage mImage;
		if (mImage.Load(_T("jfc.jpg")) == S_OK)
		{
			//这里让图片绘制区域和窗口大小一致  
			mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		}
	}
}

