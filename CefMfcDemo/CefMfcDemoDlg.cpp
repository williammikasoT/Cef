
// CefMfcDemoDlg.cpp : ʵ���ļ�
// ����1.�޴󻯲����Զ�ˢ��js����Ŀؼ� 
// ����2.��ʱ���ظ�����USB������
// ����3.�ڱ��˵ĳ���������windows8���в��в�ѯ
// ����4.��Ҫ����libusb0.dll��������


#include "stdafx.h"
#include "CefMfcDemo.h"
#include "CefMfcDemoDlg.h"
#include "afxdialogex.h"
#include "c_fun.h"
#include "include/cef_app.h"
#include "USBTransmit.h"
#include "DialogQueryT.h"
#include "DialogSaveT.h"
#include "filefunc.h"
#include "DialogData.h"

#define USB_VID     0x0483
#define USB_PID     0x5710
#define INUM		1700
#define IMAX		1024*10
#define SPLIT		1000			//150
//#define STRURL		"/main.html"	 // �򿪵�JS
//#define OTHERPART   L"../WSsystem/"    // ��������򿪱�����·��
//#define OTHERPART   L""  


int test_coor, technical_coor;
int inum ;
int i_x = 0, i_y = 0;
CString s_x, s_y;
CString strp_x, strp_y;
static char *p_x = (char *)malloc(1024 * 10);
static char *p_y = (char *)malloc(1024 * 10);

struct gas_concentration stand, analog, gsend, difend;								//���㺯��ʹ��
char USBTimeDisPlaybuf[1024] = { 0 };
bool OPNE_USB = false;
bool three_read_data = true;
int starbool ;				
long lTmpTime, lLastTime, lCurlTime;					//�߳���ֹ
CString m_pidp = L"1", m_pidi = L"1", m_pidd = L"1", m_gastime = L"5",m_wind=L"5";  //���õĳ�ʼ������
CString m_strPirt;																	//�ж�combox��ѡ��
CString m_strTmp, m_strTmp_y;														//�������ݣ���ֹͣ����

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//����json��������

// CCefMfcDemoDlg �Ի���

void InitData() {
	lTmpTime = 0, lLastTime = 0, lCurlTime = 0;
    starbool = 0 ,three_read_data = true,  OPNE_USB = false;
	p_x = "", p_x = "";
}


CCefMfcDemoDlg::CCefMfcDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCefMfcDemoDlg::IDD, pParent)
	, m_blUseCOM(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCefMfcDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOPICT, m_cbPict);
	//DDX_Control(pDX, IDC_COMBO_COM, m_cboCOM);
	//DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
}





//�ⲿ���������ҳ�渲�����⣬�������ڽ������
//BOOL CCefMfcDemoDlg::OnEraseBkgnd(CDC* pDC) {
//	return TRUE;
//	//return FALSE;
//}



BEGIN_MESSAGE_MAP(CCefMfcDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTONCONNECT, &CCefMfcDemoDlg::OnBnClickedButtonconnect)
	ON_BN_CLICKED(IDC_BUTTONSTART, &CCefMfcDemoDlg::OnBnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTONCGABGE, &CCefMfcDemoDlg::OnBnClickedButtoncgabge)
	ON_BN_CLICKED(IDC_BUTTONCGABGE2, &CCefMfcDemoDlg::OnBnClickedButtoncgabge2)

	ON_CBN_SELCHANGE(IDC_COMBOPICT, &CCefMfcDemoDlg::OnCbnSelchangeCombopict)
	ON_BN_CLICKED(IDC_BUTTONQUERY, &CCefMfcDemoDlg::OnBnClickedButtonquery)
	//ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCefMfcDemoDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CCefMfcDemoDlg ��Ϣ�������


void  CCefMfcDemoDlg::split(int numTest,char *p_x, char *p_y,int num,CString &x_vlue,CString &y_vlue)  // char* buff ,char* buff2
{
		CString sp;
		char dest_x[128] = { "" };
		char* pTemp_x = p_x;
		char* pTemp_x1 = NULL;
		char* pTemp_x2 = NULL;
		int len_x;
		char dest_y[128] = { "" };
		char* pTemp_y = p_y;
		char* pTemp_y1 = NULL;
		char* pTemp_y2 = NULL;
		int len_y;
	for (int i = 0; i < numTest; ++i)
	{
		pTemp_x1 = strchr(pTemp_x + 1, ',');
		len_x = pTemp_x1 - pTemp_x;
		pTemp_y1 = strchr(pTemp_y + 1, ',');
		len_y = pTemp_y1 - pTemp_y;
		if (i == num)
		{
			memset(dest_x, 0, sizeof(dest_x));
			memset(dest_y, 0, sizeof(dest_y));
			strncpy(dest_x, pTemp_x, len_x);
			strncpy(dest_y, pTemp_y, len_y);
			x_vlue = dest_x;
			y_vlue = dest_y;
			break;
		}
		pTemp_x = pTemp_x1 + 1;
		pTemp_y = pTemp_y1 + 1;
	}
}



BOOL CCefMfcDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//ShowWindow(SW_SHOWMAXIMIZED);

	GetDlgItem(IDC_EDITPIDP)->SetWindowTextW(m_pidp);
	GetDlgItem(IDC_EDITPIDI)->SetWindowTextW(m_pidi);
	GetDlgItem(IDC_EDITPIDD)->SetWindowTextW(m_pidd);
	GetDlgItem(IDC_EDITPOWERTIME)->SetWindowTextW(m_gastime);
	GetDlgItem(IDC_EDITWIND)->SetWindowTextW(m_wind);

	m_cbPict.AddString(L"S500");
	m_cbPict.AddString(L"S1000");
	m_cbPict.AddString(L"V500");
	m_cbPict.AddString(L"V1000");
	m_cbPict.AddString(L"Ĭ��");
	m_cbPict.SetCurSel(4);

	GetDlgItem(IDC_EDITID)->SetWindowTextW(L"aaa");

	InitCEF();

	CRect rect;		//��Ӧ�����С��ʹ��
	GetClientRect(&rect);
	Old.x = rect.right - rect.left;
	Old.y = rect.bottom - rect.top;


	//CDialogData* m_pDlgd;
	CRect rc;
	GetDlgItem(IDC_STATIC_RECT_T)->GetWindowRect(rc);
	ScreenToClient(rc);
	//m_pDlgd.SetWindowPos(GetDlgItem(IDC_STATIC_RECT_T), rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);*/
	m_pDlgd = new CCommdlg();
	m_pDlgd->Create(IDD_DLG_COMM, this);
	m_pDlgd->MoveWindow(rc.left, rc.top, rc.Width(), rc.Height());
	m_pDlgd->ShowWindow(SW_SHOW);




	
	/*GetClientRect(&m_rect);
	CRect rect;
	GetClientRect(&rect);
	Old.x = rect.right - rect.left;
	Old.y = rect.bottom - rect.top;*/

	/*CDialogData m_pDlgd;
	m_pDlgd.Create(IDD_DATA, this);

	CRect rc;
	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(rc);
	ScreenToClient(rc);
	m_pDlgd.SetWindowPos(GetDlgItem(IDC_STATIC_RECT), rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);*/



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CCefMfcDemoDlg::ChangeSize(UINT nID, int x, int y) //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{


	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL) //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{
		CRect rec;
		pWnd->GetWindowRect(&rec); //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec); //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left = rec.left*x / m_rect.Width(); //���ձ��������ռ����λ��
		rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec); //�����ؼ�

	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCefMfcDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCefMfcDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCefMfcDemoDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	starbool = 1;
	Sleep(400);

	free(stand.datax);
	free(stand.datay);
	free(analog.datax);
	free(analog.datay);
	free(gsend.datax);
	free(gsend.datay);
	free(difend.datax);
	free(difend.datay);
	CDialogEx::OnClose();
}



void CCefMfcDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	//resize(); //�Զ���Ӧ���ڵĴ�С
			  //������¼���cef
}

void CCefMfcDemoDlg::resize()
{
	float fsp[2];
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С
	CRect recta;
	GetClientRect(&recta);     //ȡ�ͻ�����С  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / Old.x;
	fsp[1] = (float)Newp.y / Old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //���Ͻ�
	CPoint OldBRPoint, BRPoint; //���½�
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	Old = Newp;
}





BOOL CCefMfcDemoDlg::USBConnect()
{
	CString strCBText;
	int PacketSize = 100;//20 * 1024;
	char *pReadDataBuffer = (char *)malloc(PacketSize);
	char pR[100] = { 0 };

	m_cbPict.GetWindowText(strCBText);
	if (L"S500" == strCBText || L"S1000" == strCBText || L"V500" == strCBText || L"V1000" == strCBText)
	{
		GetDlgItem(IDC_BUTTONSTART)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTONCONNECT)->SetWindowText(L"���ӳɹ�");
		GetDlgItem(IDC_BUTTONCONNECT)->EnableWindow(FALSE);
		return TRUE;
	}

	//int DevNum = USBScanDevice(USB_PID, USB_VID);
	if (!USBOpenDevice(0))
	{
		//MessageBox(L"���豸ʧ�ܣ�",L"��ʾ");
		USBCloseDevice(0);
		return FALSE;
	}
	else {
		char *p = "{end}\\n";
		int len = strlen(p);
		int ret = USBBulkWriteData(0, EP1_OUT, p, len, 100);
		char *readusb = (char*)malloc(100);
		ret = USBBulkReadData(0, EP1_IN, readusb, 100, 100);
		if (ret > 0) {
		}
		free(readusb);
	}

	//1. ��usbͨ�� {connect}\n USB�ɹ����� {connection success}\n
	char WriteData[] = { "{connect}\\n" };
	int ret = USBBulkWriteData(0, EP1_OUT, WriteData, sizeof(WriteData), 100);
	if (ret < 0)
	{
		MessageBox(L"д�豸ʧ�ܣ�");
		USBCloseDevice(0);
		return FALSE;
	}

	ret = USBBulkReadData(0, EP1_IN, pReadDataBuffer, PacketSize, 100);
	int i = 0;
	if (ret > 0) {
		for (;i<ret;i++) {
			pR[i] = pReadDataBuffer[i];
		}
	}
	else {
		MessageBox(L"���豸ʧ�ܣ�");
		USBCloseDevice(0);
		return FALSE;
	}
	pR[i] = '\0';

	//add momo
	free(pReadDataBuffer);

	const char *string1 = "{connection success}\\n";
	int num = strcmp(string1, pR);
	if (num == 0)
	{
		// ƥ��ɹ�����
		GetDlgItem(IDC_BUTTONSTART)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTONCONNECT)->SetWindowText(L"���ӳɹ�");
		GetDlgItem(IDC_BUTTONCONNECT)->EnableWindow(FALSE);
	}
	else
	{
		MessageBox(L"���Ӷ�ȡʧ��");
		USBCloseDevice(0);
		return FALSE;
	}

	// 5sһֱ�ڶ������о��ж��������� û�о�5���ѯһ��query\n
	//2. 5Sû�������ϴ���ʱ��ʼ��ʱ��ѯ ��ѯ����{query}\n �ɹ�����{answer}\n   {valuex��Ũ�ȣ��¶�1���¶�2��ʪ��1��ʪ��2}\n ͬʱ����WEBʵ
}


void CCefMfcDemoDlg::OnBnClickedButtonconnect()
{
	// USB ��ʧ�� ʹ��COM
	if (!USBConnect())
	{
		//m_pDlgd->GetDlgItem(IDC_COMBO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(L"��ѡ����ȷ��COM��");
		BOOL blSuccess = m_pDlgd->OpenDevicei();
		if (blSuccess)
		{
			m_blUseCOM = TRUE;  // ��־COM����ʹ�õ���COM
			GetDlgItem(IDC_BUTTONSTART)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTONCONNECT)->SetWindowText(L"���ӳɹ�");
			GetDlgItem(IDC_BUTTONCONNECT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_TITLE)->SetWindowText(L"");
		}
		
	}
	
	
	

}


char* CCefMfcDemoDlg::cstring_to_pchar(CString sStarOder)
{
	int len = WideCharToMultiByte(CP_ACP, 0, sStarOder, -1, NULL, 0, NULL, NULL);
	char *pTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, sStarOder, -1, pTemp, len, NULL, NULL);
	return pTemp;
}


void CCefMfcDemoDlg::pirt_real(CString data_x,CString data_y) {
	CString strInfo;
	USES_CONVERSION;
	p_x = T2A(strp_x.GetBuffer(0));
	p_y = T2A(strp_y.GetBuffer(0));
	strInfo.Format(_T("updataRealTimeLine('%s','%s');"), data_x, data_y);
	ExecuteJS(strInfo);
}


long CCefMfcDemoDlg::str_to_long_time() {

	CTime tm = CTime::GetCurrentTime();
	CString str;
	str.Format(_T("%u"), tm.GetTime());
	//tm.GetTotalSeconds();
	long lResult;
	USES_CONVERSION;
	char *Buf = T2A(str.GetBuffer(0));
	lResult = atol(Buf);
	return lResult;
}


void CCefMfcDemoDlg::USBStart()
{
	// ��ʼ��ȡusb����
	// 1.PC��USB {start}\n {set PID:5.1��4.0��8.4}\n { set Gas time:500}\n �����Ǳ��� �ɹ����� {set PID OK}\n   �趨����{adjust wind speed:*****}\n  �ɹ�����ʵ�ʷ���	����ʵʱ�ϴ�

	char *p = "{start}\\n";
	int len = strlen(p);
	
	int ret = USBBulkWriteData(0, EP1_OUT, p,len , 100);
	
	CString strInfo;
	strInfo.Format(_T("startDev('%s');"), L"0");
	ExecuteJS(strInfo);
	strInfo.Format(_T("yunConnect('%s');"), L"0");
	ExecuteJS(strInfo);
	strInfo.Format(_T("exciter('%s','%s');"), L"0", L"0");
	ExecuteJS(strInfo);
	GetDlgItem(IDC_EDITPOWERTIME)->GetWindowTextW(m_gastime);
	strInfo.Format(_T("srackGas('%s','%s');"), L"0", m_gastime);
	ExecuteJS(strInfo);
	strInfo.Format(_T("sf6('%s');"), L"0");
	ExecuteJS(strInfo);

	char *pReadDataBuffer = (char *)malloc(40);
	len = strlen(pReadDataBuffer);
	CString csTempBuf, strTmp, strTmp_y;
	CString  ppm=L"",temp1=L"",temp2=L"",hum1=L"",hum2=L"",wind1=L"",wnid2=L"", stmp=L"";
	int iFirst=0;
	float fValue;
	char **arr = (char **)malloc(sizeof(char *) * 1024);
	//char p[] = "{value0:Ũ��,�¶�1,�¶�2,ʪ��1,ʪ��2,����1,����2}\n";
	lLastTime = str_to_long_time();
	char *readusb = (char*)malloc(100);
	int i = 0;
	float fV = 0, fTemp = 0;
	const float PI = 3.1415926;
	float d = 0.0961;
	int iWhile = 0;  //�ж������ȡusb���δ���
	while (true)
	{
		Sleep(1000);
		if (starbool == 1)  //����ѭ��
		{
			char *p = "{end}\\n";
			int len = strlen(p);
			int ret = USBBulkWriteData(0, EP1_OUT, p, len, 100);
			ret = USBBulkReadData(0, EP1_IN, readusb, len, 100);
			/*if (ret > 0) {
				USBCloseDevice(0);
			}*/
			printf("%s\n",readusb);
			USBCloseDevice(0);
			starbool = 2;
			return ;
		}else{
			ret = USBBulkReadData(0, EP1_IN, pReadDataBuffer, len, 100);

			printf("%s\n",pReadDataBuffer);

			if (ret > 0)
			{
				for (int i = 0; i < 6; i++)
				{
					if (i == 0)
					{
						split_del(arr, pReadDataBuffer, "}");   // p������
						split_usb(*arr, i, csTempBuf, ":",2);
						split_usb(*arr, 1, csTempBuf, ":",2);
						int len = csTempBuf.Find(L",");
						stmp = csTempBuf.Left(len);
						csTempBuf = stmp;
					}else {
						split_usb(*arr, i, csTempBuf, ",",6);
					}

					if (0 == i) {
						GetDlgItem(IDC_EDIT_INFOPPM)->SetWindowText(csTempBuf);
						ppm = csTempBuf;
						// ��¼��ʵʱ������ ���.txt �浽.txt,  s_x =
						lCurlTime = str_to_long_time();
						lTmpTime = lCurlTime - lLastTime;
						fValue = (float)lTmpTime / 60.0;
						strTmp.Format(L"%2f", fValue);
						strTmp_y = csTempBuf;
						pirt_real(strTmp, strTmp_y);

						if (0 != iFirst)
						{
							m_strTmp += L"," + strTmp;
							m_strTmp_y += L"," + strTmp_y;
						}else {
							m_strTmp = strTmp;
							m_strTmp_y = strTmp_y;
							iFirst = 1;
						}
					/*	ix.push_back(m_strTmp);
						iv.push_back(m_strTmp_y);*/
					}else if (1 == i) {
						GetDlgItem(IDC_EDITTEMP1)->SetWindowText(csTempBuf);
						temp1 = csTempBuf;
					}else if (2 == i) {
						GetDlgItem(IDC_EDITTEMP2)->SetWindowText(csTempBuf);
						temp2 = csTempBuf;

					}else if (3 == i) {
						GetDlgItem(IDC_EDITHUMI1)->SetWindowText(csTempBuf);
						hum1 = csTempBuf;
					}else if (4 == i) {
						GetDlgItem(IDC_EDITHUMI2)->SetWindowText(csTempBuf);
						hum2 = csTempBuf;
					}else if (5 == i) {
						GetDlgItem(IDC_EDITHUMI3)->SetWindowText(csTempBuf);
						wind1 = csTempBuf;
						// ��÷��� ����web����
						fV = _ttof(wind1);
						fTemp = d / 4;
						fTemp = PI * fTemp;
						fTemp = fTemp * fV;
						fTemp = fTemp * 3600;  
						wind1.Format(L"%f",fTemp);
						//fValue = (PI*( (d*d) / 4)* v) * 3600;
					}
				 }
				strInfo.Format(_T("outputWS('%s','%s','%s','%s');"), L"0", temp1, hum1, ppm);  // ppm���浽���ݿ⣬��ѯ���ݿ�ʱ������
				ExecuteJS(strInfo);
				strInfo.Format(_T("inputWS('%s','%s','%s');"), L"0", temp2, hum2);
				ExecuteJS(strInfo);
				GetDlgItem(IDC_EDITWIND)->GetWindowText(m_wind);
				strInfo.Format(_T("cfj('%s','%s');"), wind1, m_wind);
				ExecuteJS(strInfo);
			}/*else{ //��ȡ����ʧ��
				iWhile++;
				if (iWhile > 3) {
					starbool = 1;
				}
			}*/
		}
	}

	free(pReadDataBuffer);
	free(readusb);
}

void CCefMfcDemoDlg::OnBnClickedButtonstart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	starbool = 0;
	CString strCBText;
	CString strInfo;
	CString strInfo1;
	inum = 0;
	CString s;



	GetDlgItem(IDC_EDITID)->GetWindowTextW(s);
	if (s.IsEmpty())
	{
		MessageBox(L"�ļ�������");
		return;
	}
	GetDlgItem(IDC_BUTTONCGABGE2)->EnableWindow(TRUE);
	m_cbPict.GetWindowText(strCBText);
	strInfo1.Format(_T("clear();"));
	ExecuteJS(strInfo1);
	CString strX, strY;
	if (L"Ĭ��" == strCBText)
	{
		if (m_blUseCOM)
		{
			m_pDlgd->OnBnClickedButtonStart();
		}
		else {
			HANDLE hThread = CreateThread(NULL, 0, MyThreadUSBStart, this, 0, NULL);
		}
		m_strPirt = L"Ĭ��";
	}
	else if (L"S500" == strCBText)
	{
		strX = OTHERPART;
		strX = strX + L"MateText/S500X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/S500Y.txt";
		ReadText(strX, strY);

		m_strPirt = L"S500";
		strInfo.Format(_T("changeChart('%s');"), L"1");
		ExecuteJS(strInfo);
		SetTimer(2, SPLIT, NULL);
	}
	else if (L"S1000" == strCBText)
	{
		strX = OTHERPART;
		strX = strX + L"MateText/S1000X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/S1000Y.txt";
		ReadText(strX, strY);

		m_strPirt = L"S1000";
		strInfo.Format(_T("changeChart('%s');"), L"1");
		ExecuteJS(strInfo);
		SetTimer(2, SPLIT, NULL);
	}
	else if (L"V500" == strCBText)
	{
		strX = OTHERPART;
		strX = strX + L"MateText/V500X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/V500Y.txt";
		ReadText(strX, strY);

		m_strPirt = L"V500";
		strInfo.Format(_T("changeChart('%s');"), L"1");
		ExecuteJS(strInfo);
		SetTimer(2, SPLIT, NULL);
	}
	else if (L"V1000" == strCBText)
	{
		strX = OTHERPART;
		strX = strX + L"MateText/V1000X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/V1000Y.txt";
		ReadText(strX, strY);

		m_strPirt = L"V1000";
		strInfo.Format(_T("changeChart('%s');"), L"1");
		ExecuteJS(strInfo);
		SetTimer(2, SPLIT, NULL);
	}
	GetDlgItem(IDC_BUTTONSTART)->EnableWindow(false);
}



bool CCefMfcDemoDlg::InitCEF()
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
	m_simpleClient =  objEventHandler;
	CString strPath;
	GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strPath.ReleaseBuffer();
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos);
	CString strUrl = _T("file:///") + strPath +  _T("/main.html");
	CefBrowserHost::CreateBrowser(cefWindowInfo, objEventHandler.get(), CefString(strUrl), browserSetting, NULL); //index.html  

	

	//CRect rtWindow;
	//GetWindowRect(GetDesktopWindow(), &rtWindow);
	//::MoveWindow(m_pBrowserWnd->GetHWND(), rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), TRUE);
	//m_pBrowserWnd->ShowModal();


	return 0;
}

DWORD CCefMfcDemoDlg::MyThreadFunction(LPVOID pParam)  //UINT 
{
	CCefMfcDemoDlg *p = (CCefMfcDemoDlg*)pParam;
	p->USBConnect();
	return 0;
}

DWORD  CCefMfcDemoDlg::MyThreadUSBStart(LPVOID pParam)
{
	CCefMfcDemoDlg *p = (CCefMfcDemoDlg*)pParam;
	p->USBStart();
	return 0;
}

void CCefMfcDemoDlg::pirt_mode(CString sX, CString sY)
{
	CString sTech_x, sTech_y, anlog_x, anlog_y;
	ReadData(L"MateText\test_X_Technical.txt", L"MateText\test_Y_Technical.txt", sTech_x, sTech_y);  
	sX = L"TextData\\" + sX;
	sY = L"TextData\\" + sY;
	ReadData(sX,sY, anlog_x, anlog_y);

	stand.datax = (float *)malloc(sizeof(float)*(IMAX + 1));
	stand.datay = (float *)malloc(sizeof(float)*(IMAX + 1));
	analog.datax = (float *)malloc(sizeof(float)*(IMAX + 1));
	analog.datay = (float *)malloc(sizeof(float)*(IMAX + 1));
	gsend.datax = (float *)malloc(sizeof(float)*(IMAX + 1));
	gsend.datay = (float *)malloc(sizeof(float)*(IMAX + 1));

	difend.datax = (float *)malloc(sizeof(float)*(IMAX + 1));
	difend.datay = (float *)malloc(sizeof(float)*(IMAX + 1));

	// sTech_x sTech_y ��ȡ���֣�ת��int �Ž�����
	CString sp;
	char dest_x[128] = { "" };
	char* pTemp_x1 = NULL;
	char* pTemp_x2 = NULL;
	int len_x;
	char dest_y[128] = { "" };
	char* pTemp_y1 = NULL;
	char* pTemp_y2 = NULL;
	int len_y;
	char *pTemp_x;
	char *pTemp_y;

	int len = WideCharToMultiByte(CP_ACP, 0, sTech_x, -1, NULL, 0, NULL, NULL);
	pTemp_x = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, sTech_x, -1, pTemp_x, len, NULL, NULL);
	technical_coor = strsplinum(pTemp_x, ",");									// ��ȡ��

	len = WideCharToMultiByte(CP_ACP, 0, sTech_y, -1, NULL, 0, NULL, NULL);
	pTemp_y = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, sTech_y, -1, pTemp_y, len, NULL, NULL);


	for (int i = 0; i < technical_coor; i++) {
		pTemp_x1 = strchr(pTemp_x + 1, ',');
		len_x = pTemp_x1 - pTemp_x;

		memset(dest_x, 0, sizeof(dest_x));
		memset(dest_y, 0, sizeof(dest_y));
		strncpy(dest_x, pTemp_x, len_x);
		dest_x[len_x] = '\0';
		pTemp_y1 = strchr(pTemp_y + 1, ',');
		len_y = pTemp_y1 - pTemp_y;
		strncpy(dest_y, pTemp_y, len_y);
		dest_y[len_y] = '\0';
		stand.datax[i] = atof(dest_x);
		stand.datay[i] = atof(dest_y);

		pTemp_x = pTemp_x1 + 1;
		pTemp_y = pTemp_y1 + 1;
	}

	len = WideCharToMultiByte(CP_ACP, 0, anlog_x, -1, NULL, 0, NULL, NULL);
	pTemp_x = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, anlog_x, -1, pTemp_x, len, NULL, NULL);
	test_coor = strsplinum(pTemp_x, ",");

	len = WideCharToMultiByte(CP_ACP, 0, anlog_y, -1, NULL, 0, NULL, NULL);
	pTemp_y = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, anlog_y, -1, pTemp_y, len, NULL, NULL);

	pTemp_x1 = NULL;
	pTemp_x2 = NULL;
	pTemp_y1 = NULL;
	pTemp_y2 = NULL;

	for (int i = 0; i < test_coor; ++i) {                     // ��������
		pTemp_x1 = strchr(pTemp_x + 1, ',');
		len_x = pTemp_x1 - pTemp_x;

		memset(dest_x, 0, sizeof(dest_x));
		memset(dest_y, 0, sizeof(dest_y));
		strncpy(dest_x, pTemp_x, len_x);
		dest_x[len_x] = '\0';
		pTemp_y1 = strchr(pTemp_y + 1, ',');
		len_y = pTemp_y1 - pTemp_y;
		strncpy(dest_y, pTemp_y, len_y);
		dest_y[len_y] = '\0';
		analog.datax[i] = atof(dest_x);
		analog.datay[i] = atof(dest_y);

		pTemp_x = pTemp_x1 + 1;
		pTemp_y = pTemp_y1 + 1;
	}

	stand.len = technical_coor;
	analog.len = test_coor;
	gsend.len = 0;

	Correction_curve(&stand, &analog, &difend);
	CString dif_tmp_x, dif_tmp_y, dif_x, dif_y;
	for (int i = 0; i < difend.len; i++)					// �Ƚ�����
	{
		dif_tmp_x.Format(L"%f,", difend.datax[i]);
		dif_x += dif_tmp_x;
		dif_tmp_y.Format(L"%f,", difend.datay[i]);
		dif_y += dif_tmp_y;
	}
	CString strInfo;
	strInfo.Format(_T("updataDeviationLine('%s','%s');"), dif_x, dif_y);
	ExecuteJS(strInfo);

	Comparative_data(&stand, &difend, &gsend);
	CString tmpend_tmp_x, tmpend_tmp_y, tmpend_x, tmpend_y;
	for (int i = 0; i < gsend.len; i++)
	{
		tmpend_tmp_x.Format(L"%f,", gsend.datax[i]);
		tmpend_x += tmpend_tmp_x;
		tmpend_tmp_y.Format(L"%f,", gsend.datay[i]);
		tmpend_y += tmpend_tmp_y;
	}
	strInfo.Format(_T("updataDifferenceLine('%s','%s');"), tmpend_x, tmpend_y);
	ExecuteJS(strInfo);

	strInfo.Format(_T("updataStandardLine('%s','%s');"), sTech_x, sTech_y);
	ExecuteJS(strInfo);
}

void CCefMfcDemoDlg::OnBnClickedButtoncgabge()
{
	//ʹ��c�����������������ƫ������
	CString sTech_x, sTech_y,  strInfo,strInfo1,s;
	sTech_x.Empty();
	sTech_y.Empty();
	m_cbPict.GetWindowTextW(s);


	// ����һ��Ĭ��ͼ��ˢ�½�����Ի�һ���Ա�ͼ
	// ����ǻ������θ�˹ͼ��ˢ���ػ�
	CString strX, strY;
	if (L"Ĭ��" == s)
	{
		strInfo1.Format(_T("clear();"));
		ExecuteJS(strInfo1);
		CString str,stry,strTemp;
		GetDlgItem(IDC_EDITID)->GetWindowTextW(str);
		//stry = str + L"../WSsystem/MateText/_y.txt";  
		//str += L"../WSsystem/MateText/_x.txt";
		//pirt_mode(str,stry);
	}
	else if (L"S500" == s)
	{
		
		strInfo1.Format(_T("clear2();"));
		ExecuteJS(strInfo1); 
		
		strX = OTHERPART;
		strX = strX + L"MateText/SGS500X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/SGS500Y.txt";
		ReadData(strX, strY, sTech_x, sTech_y);
		//ReadData(L"../WSsystem/MateText/SGS500X.txt", L"../WSsystem/MateText/SGS500Y.txt", sTech_x, sTech_y);
		


		strInfo.Format(_T("updataDifferenceLine('%s','%s');"), sTech_x, sTech_y);
		ExecuteJS(strInfo);
	}
	else if (L"S1000" == s)
	{
		strInfo1.Format(_T("clear2();"));
		ExecuteJS(strInfo1);

		strX = OTHERPART;
		strX = strX + L"MateText/SGS1000X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/SGS1000Y.txt";
		ReadData(strX, strY, sTech_x, sTech_y);

		//ReadData(L"../WSsystem/MateText/SGS1000X.txt", L"../WSsystem/MateText/SGS1000Y.txt", sTech_x, sTech_y);
		strInfo.Format(_T("updataDifferenceLine('%s','%s');"), sTech_x, sTech_y);
		ExecuteJS(strInfo);
		
	}
	else if (L"V500" == s)
	{
		strInfo1.Format(_T("clear2();"));
		ExecuteJS(strInfo1);

		strX = OTHERPART;
		strX = strX + L"MateText/VGS500X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/VGS500Y.txt";
		ReadData(strX, strY, sTech_x, sTech_y);
		

		//ReadData(L"../WSsystem/MateText/VGS500X.txt", L"../WSsystem/MateText/VGS500Y.txt", sTech_x, sTech_y);
		strInfo.Format(_T("updataDifferenceLine('%s','%s');"), sTech_x, sTech_y);
		ExecuteJS(strInfo);

	}
	else if (L"V1000" == s)
	{
		strInfo1.Format(_T("clear2();"));
		ExecuteJS(strInfo1);

		strX = OTHERPART;
		strX = strX + L"MateText/VGS100X.txt";
		strY = OTHERPART;
		strY = strY + L"MateText/VGS1000Y.txt";
		ReadData(strX, strY, sTech_x, sTech_y);
		

		//ReadData(L"../WSsystem/MateText/VGS1000X.txt", L"../WSsystem/MateText/VGS1000Y.txt", sTech_x, sTech_y);
		strInfo.Format(_T("updataDifferenceLine('%s','%s');"), sTech_x, sTech_y);
		ExecuteJS(strInfo);
	}

}

void CCefMfcDemoDlg::ExecuteJS(CString FunName)
{
	
	CString strInfo = FunName;
	if (m_simpleClient.get())
	{
		BrowserList s = m_simpleClient->GetBrowser();
		BrowserList::iterator itor;
		itor = s.begin();
		
		CefRefPtr<CefBrowser> cefBrowser = *itor;
		//CefRefPtr<CefBrowser> cefBrowser = m_simpleClient->GetBrowser();
		CefRefPtr<CefFrame> cefFrame = cefBrowser->GetMainFrame();
		if (cefFrame)
		{
			cefFrame->ExecuteJavaScript(CefString(strInfo), cefFrame->GetURL(), 0);
		}
	}
}

int iTime = 0;
void CCefMfcDemoDlg::OnTimer(UINT_PTR nIDEvent)
{

	CString strInfo;
	if (nIDEvent == 1)
	{
		switch (iTime++)
		{
		case 0:
			strInfo.Format(_T("startDev('%s');"), L"0");  
			ExecuteJS(strInfo);
			strInfo.Format(_T("yunConnect('%s');"), L"0");
			ExecuteJS(strInfo);
			break;
		case 1:
			strInfo.Format(_T("cfj('%s','%s');"), L"2", L"4.88");
			ExecuteJS(strInfo);
			break;
		case 2:
			strInfo.Format(_T("srackGas('%s','%s');"), L"0", L"5");
			ExecuteJS(strInfo);
			break;
		case 3:
			strInfo.Format(_T("sf6('%s');"), L"0");
			ExecuteJS(strInfo);
			break;
		case 4:
			strInfo.Format(_T("inputWS('%s','%s','%s');"), L"0", L"25", L"60");
			ExecuteJS(strInfo);
			break;
		case 5:
			strInfo.Format(_T("exciter('%s','%s');"), L"0", L"0");
			ExecuteJS(strInfo);
			break;
		case 6:
			strInfo.Format(_T("outputWS('%s','%s','%s','%s');"), L"0", L"25", L"60", L"10");
			ExecuteJS(strInfo);
			break;
		default:
			//iTime = 0;
			break;
		}
	}
	else if (nIDEvent == 2)
	{
		if (inum == test_coor)
		{
			OnBnClickedButtoncgabge();
			s_x.Empty();
			s_y.Empty();
			KillTimer(2);
		}

		USES_CONVERSION;
		p_x = T2A(strp_x.GetBuffer(0));
		p_y = T2A(strp_y.GetBuffer(0));
		split(test_coor, p_x, p_y, inum, s_x, s_y);
		strInfo.Format(_T("updataRealTimeLine('%s','%s');"), s_x, s_y);
		ExecuteJS(strInfo);
		inum++;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CCefMfcDemoDlg::OnBnClickedButtoncgabge2()
{
	
	// 4. ����{end}\n ֹͣ���� usb�ɹ�����{system stop}\n    �����ֹͣ��ť
	if (m_blUseCOM)
	{
		m_pDlgd->OnBnClickedButtonClose();
	}
	else {
		InitData();
		KillTimer(2);
		starbool = 1;
		CString strInfo;         // JS����״̬
		strInfo.Format(_T("startDev('%s');"), L"1");
		ExecuteJS(strInfo);
		strInfo.Format(_T("cfj('%s','%s');"), L"0", L"0");
		ExecuteJS(strInfo);
		strInfo.Format(_T("srackGas('%s','%s');"), L"1", L"0");
		ExecuteJS(strInfo);
		strInfo.Format(_T("sf6('%s');"), L"1");
		ExecuteJS(strInfo);
		strInfo.Format(_T("inputWS('%s','%s','%s');"), L"1", L"0", L"0");
		ExecuteJS(strInfo);
		strInfo.Format(_T("exciter('%s','%s');"), L"1", L"1");
		ExecuteJS(strInfo);
		strInfo.Format(_T("outputWS('%s','%s','%s','%s');"), L"1", L"0", L"0", L"0");
		ExecuteJS(strInfo);
		strInfo.Format(_T("yunConnect('%s');"), L"1");
		ExecuteJS(strInfo);
		// ��ֹͣ���ݱ���  һ������һ��idshe'����Ψһ
		if (MessageBox(L"�Ƿ񱣴�����", L"��ʾ", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL)
			return;
		CString sbuf, sy, sx;    // ����һ�������� �ڲ�ͬ���ļ���
		GetDlgItem(IDC_EDITID)->GetWindowTextW(sbuf);
		sx = sbuf + L"_x.txt";
		sy = sbuf + L"_y.txt";
		sx = L"TextData/" + sx;
		sx = OTHERPART + sx;
		sy = L"TextData/" + sy;
		sy = OTHERPART + sy;
		WriteData(sx, sy, m_strTmp, m_strTmp_y);
	}


	GetDlgItem(IDC_BUTTONSTART)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONCONNECT)->SetWindowText(L"����");
	GetDlgItem(IDC_BUTTONCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTONCGABGE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTONSTART)->EnableWindow(FALSE);


	/*CDialogSave *pDlg;  // ���浽MySql���ݿ�
	pDlg = new CDialogSave();
	pDlg->Create(IDD_DIALOGSAVE, this);
	pDlg->GetDlgItem(IDC_EDITPATH)->SetWindowTextW(sbuf);
	pDlg->ShowWindow(SW_SHOW);*/

	//CDialogSaveT *pDlg;  //����һ��������Ա���� �ڲ�ͬ���ļ���
	//pDlg = new CDialogSaveT();
	//pDlg->Create(IDD_DIALOGSAVET, this);
	//pDlg->GetDlgItem(IDC_EDITPATH)->SetWindowTextW(sbuf);
	//pDlg->ShowWindow(SW_SHOW);

	
}

bool CCefMfcDemoDlg::ReadText(CString name_x, CString name_y)
{
	CString strFileName = name_x;
	CString strFileName_Y = name_y;
	if (!PathFileExists(strFileName))
		return FALSE;
	if (!PathFileExists(strFileName_Y))
		return FALSE;

	CStdioFile file, file_Y;
	if (!file.Open(strFileName, CFile::modeRead))
		return FALSE;
	if (!file_Y.Open(strFileName_Y, CFile::modeRead))
		return FALSE;

	std::vector<CString> vecResult, vecResult_Y;
	CString strValue = _T("");
	CString strValue_Y = _T("");
	while (file.ReadString(strValue))
	{
		vecResult.push_back(strValue);
	}
	while (file_Y.ReadString(strValue_Y))
	{
		vecResult_Y.push_back(strValue_Y);
	}
	file.Close();
	file_Y.Close();

	strp_x = vecResult[0];
	strp_y = vecResult_Y[0];

	USES_CONVERSION;
	p_x = T2A(vecResult[0].GetBuffer(0));
	const char *del = ",";

	test_coor = strsplinum(p_x, del);
	 p_y = T2A(vecResult_Y[0].GetBuffer(0));
}


void CCefMfcDemoDlg::OnCbnSelchangeCombopict()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCefMfcDemoDlg::OnBnClickedButtonquery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CDialogQuery *pDlg;    // �������ݿ�
	pDlg = new CDialogQuery();
	pDlg->Create(IDD_DIALOGQUERY,this);
	pDlg->ShowWindow(SW_SHOW);*/

	CDialogQueryT *pDlg;
	pDlg = new CDialogQueryT();
	pDlg->Create(IDD_DIALOGQUERYT,this);
	pDlg->ShowWindow(SW_SHOW);
	//CDialogQueryT dlg;
	//dlg.DoModal();
}


//void CCefMfcDemoDlg::OnBnClickedButtonOpen()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	//CCommdlg *pDlg;
//	/*pDlg = new CCommdlg();
//	pDlg->Create(IDD_DLG_COMM,this);
//	pDlg->ShowWindow(SW_SHOW);*/
//
//}

BEGIN_EVENTSINK_MAP(CCefMfcDemoDlg, CDialogEx)
	
END_EVENTSINK_MAP()



