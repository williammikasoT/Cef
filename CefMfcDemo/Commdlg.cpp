// Commdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CefMfcDemo.h"
#include "Commdlg.h"
#include "afxdialogex.h"
#include "CefMfcDemoDlg.h"
#include "filefunc.h"
#include "afxdialogex.h"
#include "enumser.h"
#include "SaveName.h"

//#define OTHERPART   L"../WSsystem/"  // 其它程序打开本程序路径
//#define OTHERPART   L"" 

CString m_strDataTime, m_strDataCul; //记实时读取到录数据使用
// CCommdlg 对话框
IMPLEMENT_DYNAMIC(CCommdlg, CDialogEx)

CCommdlg::CCommdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_COMM, pParent)
{

}

CCommdlg::~CCommdlg()
{
}

void CCommdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_cbo);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
}


BEGIN_MESSAGE_MAP(CCommdlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCommdlg 消息处理程序




//void CCommdlg::OnBnClickedButtonOpen()
//{
//	OpenDevicei();
//}
BEGIN_EVENTSINK_MAP(CCommdlg, CDialogEx)
	ON_EVENT(CCommdlg, IDC_MSCOMM1, 1, CCommdlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


 BOOL CCommdlg::OpenDevicei()
{
	 CString strIndex;
	 m_cbo.GetWindowTextW(strIndex);
	 CString strTemp = strIndex.Right(2);
	 int flag = _ttoi(strTemp);
	 if (flag)
	 {
		 if (m_mscomm.get_PortOpen())
		 {
			 m_mscomm.put_PortOpen(FALSE);
		 }
		 m_mscomm.put_CommPort(flag);
		 m_mscomm.put_InBufferSize(1024);
		 m_mscomm.put_OutBufferSize(1024);
		 m_mscomm.put_InputLen(0);
		 m_mscomm.put_InputMode(1);
		 m_mscomm.put_RThreshold(1);
		 m_mscomm.put_Settings(_T("115200,n,8,1"));
		 if (!m_mscomm.get_PortOpen())
		 {
			 m_mscomm.put_PortOpen(TRUE);
			 //GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
			 //GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);
			 //GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);
			 CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
			 CString strInfo;
			 strInfo.Format(_T("clear();"));
			 pDlg->ExecuteJS(strInfo);
			 return TRUE;

		 }
		 else
		 {
			 m_mscomm.put_OutBufferCount(0);
			 MessageBox(_T("串口打开失败"));
			 return FALSE;
		 }
	 }
	 else
	 {
		 MessageBox(_T("请先输入需要打开串口编号"), L"提示");
		 return FALSE;
	 }
}

BOOL CCommdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CUIntArray ports;
	EnumerateSerialPorts(ports);
	CString com;
	for (int i = 0; i < 10; i++)
	{
		com_id[i] = 0;
	}
	for (int i = 0; i<ports.GetSize(); i++)
	{
		com.Format(_T("COM%d\n"), ports.ElementAt(i));// 为组合框控件的列表框添加列表项
		com_id[i] = ports.ElementAt(i);
		m_cbo.AddString(com);
	}

	m_cbo.SetCurSel(1);



	return TRUE;
}

void CCommdlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	static unsigned int cnt = 0;
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len, k;
	unsigned int data[1024] = { 0 };
	byte rxdata[1024] = " ";										//设置 BYTE 数组
	CString strtemp, str = _T(" ");
	char *pReadDataBuffer = (char *)malloc(40);
	len = strlen(pReadDataBuffer);
	CString csTempBuf, strTmp, strTmp_y;
	CString  ppm = L"", temp1 = L"", temp2 = L"", hum1 = L"", hum2 = L"", wind1 = L"", wnid2 = L"", stmp = L"";
	double fValue;
	char **arr = (char **)malloc(sizeof(char *) * 1024);
	//char p[] = "{value0:浓度,温度1,温度2,湿度1,湿度2,风速1,风速2}\n";
	char *readusb = (char*)malloc(100);
	int i = 0;
	float fV = 0, fTemp = 0;
	const float PI = 3.1415926;
	float d = 0.0961;
	int iWhile = 0;  //判断如果读取usb三次错误

	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();

	if (m_mscomm.get_CommEvent() == 2)						//值为 2 表示接收缓冲区内有字符
	{
		Sleep(100);                                         //注意不休眠读取数据会断帧
		variant_inp = m_mscomm.get_Input();					//读缓冲区消息
		safearray_inp = variant_inp;						//变量转换
		len = safearray_inp.GetOneDimSize();				//得到有效的数据长度
		for (k = 0; k<len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);
		}
		for (k = 0; k<len; k++)								//将数组转换为 CString 型变量
		{
			strtemp.Format(_T("%c"), *(rxdata + k));
			str += strtemp;
		}
		USES_CONVERSION;
		pReadDataBuffer = T2A(str.GetBuffer(0));
	
		
		for (int i = 0; i < 6; i++)
		{
			if (0 == i)
			{
				split_del(arr, pReadDataBuffer, "}");   // p测试用
				split_usb(*arr, i, csTempBuf, ":", 2);
				split_usb(*arr, 1, csTempBuf, ":", 2);
				int len = csTempBuf.Find(L",");
				stmp = csTempBuf.Left(len);
				csTempBuf = stmp;

				pDlg->GetDlgItem(IDC_EDIT_INFOPPM)->SetWindowText(csTempBuf);
				ppm = csTempBuf;

				CTime tCurl = CTime::GetCurrentTime();
				CTimeSpan span = tCurl - tLast;
				int iSec = span.GetTotalSeconds();
				fValue = (double)iSec / 60.0;

				strTmp.Format(L"%.6f", fValue);

				strTmp_y = csTempBuf;
				pDlg->pirt_real(strTmp, strTmp_y);

				if (0 != m_iFirst)
				{
					m_strDataTime += L"," + strTmp;
					m_strDataCul += L"," + strTmp_y;
				}else {
					m_strDataTime = strTmp;
					m_strDataCul = strTmp_y;
					m_iFirst = 1;
				}
			}
			else {
				split_usb(*arr, i, csTempBuf, ",", 6);
			}

			if (1 == i) {
				pDlg->GetDlgItem(IDC_EDITTEMP1)->SetWindowText(csTempBuf);
				temp1 = csTempBuf;
			}
			if (2 == i) {
				pDlg->GetDlgItem(IDC_EDITTEMP2)->SetWindowText(csTempBuf);
				temp2 = csTempBuf;
			}
			if (3 == i) {
				pDlg->GetDlgItem(IDC_EDITHUMI1)->SetWindowText(csTempBuf);
				hum1 = csTempBuf;
			}
			if (4 == i) {
				pDlg->GetDlgItem(IDC_EDITHUMI2)->SetWindowText(csTempBuf);
				hum2 = csTempBuf;
			}
			if (5 == i) {
				pDlg->GetDlgItem(IDC_EDITHUMI3)->SetWindowText(csTempBuf);
				wind1 = csTempBuf;
				// 获得风速 传给web界面  fValue = (PI*( (d*d) / 4)* v) * 3600;
				fV = _ttof(wind1);
				fTemp = d / 4;
				fTemp = PI * fTemp;
				fTemp = fTemp * fV;
				fTemp = fTemp * 3600;
				wind1.Format(L"%f", fTemp);
			}
		}
		CString strInfo,strWind;
		strInfo.Format(_T("outputWS('%s','%s','%s','%s');"), L"0", temp1, hum1, ppm);  // ppm保存到数据库，查询数据库时调出来
		pDlg->ExecuteJS(strInfo);
		strInfo.Format(_T("inputWS('%s','%s','%s');"), L"0", temp2, hum2);
		pDlg->ExecuteJS(strInfo);
		pDlg->GetDlgItem(IDC_EDITWIND)->GetWindowText(strWind);
		strInfo.Format(_T("cfj('%s','%s');"), wind1, strWind);
		pDlg->ExecuteJS(strInfo);

	}
}


void CCommdlg::OnBnClickedButtonClose()
{
	// 获取父对话框对象
	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
	CString strInfo;
	// 发命令关闭COM口
	m_mscomm.put_Output(COleVariant(L"{end}\\n"));
	m_mscomm.put_PortOpen(FALSE);     //关闭串口
	// 控件界面恢复初始化
	//GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
	// 实时显示数据界面清零
	strInfo.Format(_T("clear();"));
	pDlg->ExecuteJS(strInfo);
	// 风量等等界面清零
	strInfo.Format(_T("startDev('%s');"), L"1");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("cfj('%s','%s');"), L"0", L"0");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("srackGas('%s','%s');"), L"1", L"0");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("sf6('%s');"), L"1");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("inputWS('%s','%s','%s');"), L"1", L"0", L"0");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("exciter('%s','%s');"), L"1", L"1");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("outputWS('%s','%s','%s','%s');"), L"1", L"0", L"0", L"0");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("yunConnect('%s');"), L"1");
	pDlg->ExecuteJS(strInfo);

	//等待机器停止等待UI界面
	Sleep(500); 
	// 询问保存数据
	if (MessageBox(L"是否保存数据", L"提示", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
	{
		return ;
	}
	CSaveName *pDlgName = new CSaveName();
	pDlgName->Create(IDD_DIALOGSAVENAME, this);
	pDlgName->ShowWindow(SW_SHOW);

}


void CCommdlg::OnBnClickedButtonStart()
{
	// COM发送消息到单片机，开始接收数据
	CCefMfcDemoDlg *pDlg = (CCefMfcDemoDlg*)this->GetParent();
	m_mscomm.put_Output(COleVariant(L"{start}\\n"));
	// 初始化开JS始界面
	CString strInfo, strWind;
	strInfo.Format(_T("startDev('%s');"), L"0");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("yunConnect('%s');"), L"0");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("exciter('%s','%s');"), L"0", L"0");
	pDlg->ExecuteJS(strInfo);
	pDlg->GetDlgItem(IDC_EDITPOWERTIME)->GetWindowTextW(strWind);  //初始化数据
	strInfo.Format(_T("srackGas('%s','%s');"), L"0", L"5");
	pDlg->ExecuteJS(strInfo);
	strInfo.Format(_T("sf6('%s');"), L"0");
	pDlg->ExecuteJS(strInfo);
	//按钮自己不可用
	/*GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);*/
	//获取当前的时间来算时间
	//lLastTime = pDlg->str_to_long_time();
	tLast = CTime::GetCurrentTime();
	if (tLast < 0)
	{
		tLast = CTime::GetCurrentTime();
	}


}


void CCommdlg::SaveData(CString sbuf)
{
	CString  sy, sx;    // 保存一个线数据 在不同的文件夹 sbuf,
	//GetDlgItem(IDC_EDIT_NAME)->GetWindowTextW(sbuf);
	sx = sbuf + L"_x.txt";
	sy = sbuf + L"_y.txt";
	sx = L"TextData/" + sx;
	sx = OTHERPART + sx;
	sy = L"TextData/" + sy;
	sy = OTHERPART + sy;
	WriteData(sx, sy, m_strDataTime, m_strDataCul);
	//DestroyWindow();
}

void CCommdlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnClose();
}