
// HSAGRAccessTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "HSAGRAccessTestDlg.h"
#include "afxdialogex.h"
#include "PreviewDlg.h"
#include "LogDlg.h"
#include "ConfigureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHSAGRAccessTestDlg 对话框




CHSAGRAccessTestDlg::CHSAGRAccessTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHSAGRAccessTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nLoginID = -1;
}

void CHSAGRAccessTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_cbDevType);
}

BEGIN_MESSAGE_MAP(CHSAGRAccessTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CHSAGRAccessTestDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &CHSAGRAccessTestDlg::OnBnClickedButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CHSAGRAccessTestDlg::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CHSAGRAccessTestDlg::OnBnClickedButtonConfig)
    ON_BN_CLICKED(IDC_BUTTON_SearchDevice, &CHSAGRAccessTestDlg::OnBnClickedButtonStartSearchdevice)
    ON_BN_CLICKED(IDC_BUTTON1, &CHSAGRAccessTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHSAGRAccessTestDlg 消息处理程序

BOOL CHSAGRAccessTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_strExePath = GetExePath();
	m_strExePath += _T("\\AGR_ip.ini");

	char ip[128];
	GetPrivateProfileString(_T("NET"), _T("ip"),_T(""), ip, 128, m_strExePath);
	int port = GetPrivateProfileInt(_T("NET"), _T("port"), 0 , m_strExePath);
	int streamtype = GetPrivateProfileInt(_T("NET"), _T("streamtype"), 0 , m_strExePath);
	int devtype =  GetPrivateProfileInt(_T("NET"), _T("devtype"), 0 , m_strExePath);
	int channel =  GetPrivateProfileInt(_T("NET"), _T("channel"), 0 , m_strExePath);

	char userName[32];
	char password[32];
	GetPrivateProfileString(_T("NET"), _T("username"),_T(""), userName,32, m_strExePath);
	GetPrivateProfileString(_T("NET"), _T("password"),_T(""), password,32, m_strExePath);

	SetDlgItemText(IDC_EDIT_IP, ip);
	SetDlgItemInt(IDC_EDIT_PORT, port);
	SetDlgItemText(IDC_EDIT_USERNAME, userName);
	SetDlgItemText(IDC_EDIT_PASSWORD, password);
	SetDlgItemInt(IDC_EDIT_CH, 1);
	SetDlgItemInt(IDC_EDIT_STREAM_TYPE, streamtype);

	m_cbDevType.ResetContent();
	m_cbDevType.AddString("IPCAM");
	m_cbDevType.AddString("NVR");
	m_cbDevType.SetCurSel(devtype);

	CRect rect1, rect2;
	CWnd * temp = GetDlgItem(IDC_STATIC_MAIN_WINDOW);
	temp->GetWindowRect(&rect1);

	m_pPreviewDlg = new CPreviewDlg(this);
	m_pPreviewDlg->Create(CPreviewDlg::IDD, this);
	m_pPreviewDlg->GetClientRect(&rect2);

	int x = rect1.left+(rect1.Width() - rect2.Width())/2;
	int y = rect1.top;
	m_pPreviewDlg->MoveWindow(x, y, rect2.Width(), rect2.Height());
	m_pPreviewDlg->ShowWindow(SW_SHOW);

	m_pConfigureDlg = new CConfigureDlg(this);
	m_pConfigureDlg->Create(CConfigureDlg::IDD, this);
	m_pConfigureDlg->GetClientRect(&rect2);
	m_pConfigureDlg->MoveWindow(rect1.left, rect1.top, rect2.Width(), rect2.Height());

	HS_NET_Startup();
	HS_NET_SetMessageCallBack(CHSAGRAccessTestDlg::NetMessageCallBack, this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHSAGRAccessTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHSAGRAccessTestDlg::OnPaint()
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHSAGRAccessTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CHSAGRAccessTestDlg::GetExePath()
{
	TCHAR szExePath[ MAX_PATH ] = { 0 };
	GetModuleFileName( AfxGetApp()->m_hInstance, szExePath, MAX_PATH );
	int i = ( int )_tcslen( szExePath ) - 1;
	for ( ; i >= 0 && szExePath[i] != _T('\\'); i-- );
	szExePath[ i + 1 ] = 0;

	return szExePath;
}


void CHSAGRAccessTestDlg::GetParam()
{
	UpdateData(FALSE);
	memset(&m_channelInfo, 0, sizeof(HS_CLIENTINFO));

	CString temp;
	GetDlgItemText(IDC_EDIT_IP, (LPTSTR)(LPCTSTR)temp, MAX_PATH);
	sprintf(m_channelInfo.host, "%s", temp);
	WritePrivateProfileString(_T("NET"), _T("ip"), m_channelInfo.host, m_strExePath);

	GetDlgItemText(IDC_EDIT_PORT, (LPTSTR)(LPCTSTR)temp, MAX_PATH);
	m_channelInfo.port = atoi(temp);
	WritePrivateProfileString(_T("NET"), _T("port"), temp, m_strExePath);

	GetDlgItemText(IDC_EDIT_USERNAME, (LPTSTR)(LPCTSTR)temp, MAX_USER_NAME_LEN);
	sprintf(m_channelInfo.username,  "%s", temp);
	WritePrivateProfileString(_T("NET"), _T("username"), temp, m_strExePath);

	GetDlgItemText(IDC_EDIT_PASSWORD, (LPTSTR)(LPCTSTR)temp, MAX_PASSWORD_LEN);
	sprintf(m_channelInfo.password,  "%s", temp);
	WritePrivateProfileString(_T("NET"), _T("password"), temp, m_strExePath);

	int devtype = m_cbDevType.GetCurSel();
	temp.Format("%d", devtype);
	WritePrivateProfileStringA(_T("NET"), _T("devtype"), (LPTSTR)(LPCTSTR)temp, m_strExePath);

	m_channelInfo.channel = (GetDlgItemInt(IDC_EDIT_CH)-1);
	m_channelInfo.streamtype = GetDlgItemInt(IDC_EDIT_STREAM_TYPE);
	m_channelInfo.model = devtype;
}

void CALLBACK CHSAGRAccessTestDlg::NetMessageCallBack(int nLoginId, long msgType, void *pMsgData, void *pUser)
{
	CHSAGRAccessTestDlg *pThis = (CHSAGRAccessTestDlg*)pUser;
	switch(msgType)
	{
	case MSG_RECORD_BEGIN:
		::PostMessage(pThis->m_pPreviewDlg->m_hWnd, WM_MSG_RECORD_BEGIN, NULL, NULL);
		break;
	case MSG_RECORD_WRITE_ERROR:
		::PostMessage(pThis->m_pPreviewDlg->m_hWnd, WM_MSG_RECORD_WRITE_ERROR, NULL, NULL);
		break;
	case MSG_RECORD_PACKET_FINISH:
		::PostMessage(pThis->m_pPreviewDlg->m_hWnd, WM_MSG_RECORD_PACKET_FINISH, NULL, NULL);
		break;
	case MSG_RECORD_BEGIN_ANOTHER:
		::PostMessage(pThis->m_pPreviewDlg->m_hWnd, WM_MSG_RECORD_BEGIN_ANOTHER, NULL, NULL);
		break;
	case MSG_RECORD_WRITE_ERROR_ANOTHER:
		::PostMessage(pThis->m_pPreviewDlg->m_hWnd, WM_MSG_RECORD_WRITE_ERROR_ANOTHER, NULL, NULL);
		break;
	case MSG_RECORD_PACKET_FINISH_ANOTHER:
		::PostMessage(pThis->m_pPreviewDlg->m_hWnd, WM_MSG_RECORD_PACKET_FINISH_ANOTHER, NULL, NULL);
		break;
	case MSG_MOTION_DETECT:
		{
			HS_MOTION_DETECT_INFO *temp = new HS_MOTION_DETECT_INFO;
			memcpy(temp, pMsgData, sizeof(HS_MOTION_DETECT_INFO));
			::PostMessage(pThis->m_pPreviewDlg->m_hWnd, WM_MSG_MOTION_DETECT, (WPARAM)temp, NULL);
		}
		break;
	case MSG_UPGRADE_POS:
		{
			int nPercent = *(int*)pMsgData;
			::PostMessage(pThis->m_pConfigureDlg->m_hWnd, WM_MSG_UPGRADE_POS, (WPARAM)nPercent, NULL);
		}	
		break;
	case MSG_UPGRADE_OK:
		::PostMessage(pThis->m_pConfigureDlg->m_hWnd, WM_MSG_UPGRADE_POS, NULL, NULL);
		break;
	case MSG_UPGRADE_FAILED:
		::PostMessage(pThis->m_pConfigureDlg->m_hWnd, WM_MSG_UPGRADE_POS, NULL, NULL);
		break;
	default:
		break;
	}
}

void CHSAGRAccessTestDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nLoginID == -1)
	{
		GetParam();

		if((m_nLoginID = HS_NET_Login(&m_channelInfo)) > 0)
		{
			GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowTextA("Logout");
			MessageBox("login success!");
		}
		else
		{
			CString msg;
			msg.Format("login failed! error: %d", m_nLoginID);
			MessageBox(msg);
		}
	}
	else
	{
		HS_NET_Logout(m_nLoginID);
		m_nLoginID = -1;
		GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowTextA("Login");
	}
}

void CHSAGRAccessTestDlg::OnBnClickedButtonLog()
{
	// TODO: 在此添加控件通知处理程序代码
	CLogDlg logDlg(this);
	logDlg.DoModal();
}


void CHSAGRAccessTestDlg::OnBnClickedButtonPreview()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pPreviewDlg->ShowWindow(SW_SHOW);
	m_pConfigureDlg->ShowWindow(SW_HIDE);
}


void CHSAGRAccessTestDlg::OnBnClickedButtonConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pPreviewDlg->ShowWindow(SW_HIDE);
	m_pConfigureDlg->ShowWindow(SW_SHOW);
}

void CALLBACK CHSAGRAccessTestDlg::SearchDeviceCallback(long msgType/*HS_SEARCH_TYPE*/, void *pMsgData/*HS_STREAM_INFO*/, void *pUser)
{
    CHSAGRAccessTestDlg *pThis = (CHSAGRAccessTestDlg*)pUser;
    if ( nullptr != pThis )
    {
        switch (msgType)
        {
        case HS_Searchall_Device:	
            {
                HS_SEARCH_INFO *info = static_cast<HS_SEARCH_INFO*>(pMsgData);
                if ( nullptr != info )
                {
                    HS_SEARCH_INFO _info;
                    memcpy(&_info,info,sizeof(HS_SEARCH_INFO));
                    pThis->mlist.push_back(_info);
                }
            }
            break;
        default: break;	
        }
    }
}

void CHSAGRAccessTestDlg::OnBnClickedButtonStartSearchdevice()
{
    HS_NET_StartSearchDevice(SearchDeviceCallback,this);
}


void CHSAGRAccessTestDlg::OnBnClickedButton1()
{
    HS_NET_StopSearchDevice();
}
