// ConfigureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "ConfigureDlg.h"
#include "afxdialogex.h"
#include "ImageParamDlg.h"
#include "MotionDlg.h"
#include "PrivacyDlg.h"
#include "EncodeParamDlg.h"
#include "ServiceParamDlg.h"
#include "TimeParamDlg.h"
#include "NetworkDlg.h"
#include "UserParamDlg.h"
#include "SystemParmDlg.h"
#include "HSAGRAccessTestDlg.h"

// CConfigureDlg 对话框

IMPLEMENT_DYNAMIC(CConfigureDlg, CDialogEx)

CConfigureDlg::CConfigureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigureDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg*)pParent;
	m_pCurWindow = NULL;
	m_emCurType = WINDOW_NULL;
	for (int i = 0; i < WINDOW_ALL; ++i)
	{
		m_pSubWindow[i] = NULL;
	}
}

CConfigureDlg::~CConfigureDlg()
{
	if (m_pCurWindow != NULL)
	{
		delete m_pCurWindow;
	}
}

void CConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigureDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ALARM, &CConfigureDlg::OnBnClickedButtonAlarm)
	ON_BN_CLICKED(IDC_BUTTON_PRIVACY, &CConfigureDlg::OnBnClickedButtonPrivacy)
	ON_BN_CLICKED(IDC_BUTTON_IMAGE, &CConfigureDlg::OnBnClickedButtonImage)
	ON_BN_CLICKED(IDC_BUTTON_ENCODE, &CConfigureDlg::OnBnClickedButtonEncode)
	ON_BN_CLICKED(IDC_BUTTON_SERVICE, &CConfigureDlg::OnBnClickedButtonService)
	ON_BN_CLICKED(IDC_BUTTON_TIME, &CConfigureDlg::OnBnClickedButtonTime)
	ON_BN_CLICKED(IDC_BUTTON_NET, &CConfigureDlg::OnBnClickedButtonNet)
	ON_BN_CLICKED(IDC_BUTTON_USER, &CConfigureDlg::OnBnClickedButtonUser)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM, &CConfigureDlg::OnBnClickedButtonSystem)
END_MESSAGE_MAP()


// CConfigureDlg 消息处理程序
BOOL CConfigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	OnBnClickedButtonImage();

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

LRESULT CConfigureDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurWindow != NULL)
	{
		switch(message)
		{
		case WM_MSG_UPGRADE_POS:
		case WM_MSG_UPGRADE_OK:
		case WM_MSG_UPGRADE_FAILED:
			::PostMessage(m_pCurWindow->m_hWnd, message, wParam, lParam);
			break;
		default:
			break;
		}
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}

CWnd *CConfigureDlg::CreatWindows(WINDOW_TYPE windowType)
{
	if (m_emCurType == windowType)
	{
		return NULL;
	}

	if (m_pCurWindow != NULL)
	{
		m_pCurWindow->DestroyWindow();
		delete m_pCurWindow;
		m_pCurWindow = NULL;
	}

	CWnd *pNewWindow = NULL;
	switch(windowType)
	{
	case WINDOW_IMAGE:
		{
			CImageParamDlg* pImageParamDlg = new CImageParamDlg((CWnd*)m_pParent);
			pImageParamDlg->Create(CImageParamDlg::IDD, this);
			pNewWindow = pImageParamDlg;
		}
		break;
	case WINDOW_ENCODE:
		{
			CEncodeParamDlg* pEncodeParamDlg = new CEncodeParamDlg((CWnd*)m_pParent);
			pEncodeParamDlg->Create(CEncodeParamDlg::IDD, this);
			pNewWindow = pEncodeParamDlg;
		}
		break;
	case WINDOW_MOTION:
		{
			CMotionDlg* pMotionDlg = new CMotionDlg((CWnd*)m_pParent);
			pMotionDlg->Create(CMotionDlg::IDD, this);
			pNewWindow = pMotionDlg;
		}
		break;
	case WINDOW_PRIVACY:
		{
			CPrivacyDlg* pPrivacyDlg = new CPrivacyDlg((CWnd*)m_pParent);
			pPrivacyDlg->Create(CPrivacyDlg::IDD, this);
			pNewWindow = pPrivacyDlg;
		}
		break;
	case WINDOW_TIME:
		{
			CTimeParamDlg* pTimeParamDlg = new CTimeParamDlg((CWnd*)m_pParent);
			pTimeParamDlg->Create(CTimeParamDlg::IDD, this);
			pNewWindow = pTimeParamDlg;
		}
		break;
	case WINDOW_NET:
		{
			CNetworkDlg* pNetworkDlg = new CNetworkDlg((CWnd*)m_pParent);
			pNetworkDlg->Create(CNetworkDlg::IDD, this);
			pNewWindow = pNetworkDlg;
		}
		break;
	case WINDOW_USER:
		{
			CUserParamDlg* pUserParamDlg= new CUserParamDlg((CWnd*)m_pParent);
			pUserParamDlg->Create(CUserParamDlg::IDD, this);
			pNewWindow = pUserParamDlg;
		}
		break;
	case WINDOW_SERVICE:
		{
			CServiceParamDlg* pServiceParamDlg = new CServiceParamDlg((CWnd*)m_pParent);
			pServiceParamDlg->Create(CServiceParamDlg::IDD, this);
			pNewWindow = pServiceParamDlg;
		}
		break;
	case WINDOW_SYSTEM:
		{
			CSystemParmDlg* pSystemParmDlg = new CSystemParmDlg((CWnd*)m_pParent);
			pSystemParmDlg->Create(CSystemParmDlg::IDD, this);
			pNewWindow = pSystemParmDlg;
		}
		break;
	default:
		break;
	}

	if (pNewWindow)
	{
		CRect rect1, rect2, rect3;
		CWnd * temp1 = GetDlgItem(IDC_STATIC_CONFIG);
		temp1->GetWindowRect(&rect1);

		this->GetWindowRect(&rect2);

		pNewWindow->GetClientRect(&rect3);
		pNewWindow->MoveWindow(rect1.left - rect2.left + 10, rect1.top - rect2.top + 10, rect3.Width(), rect3.Height());

		pNewWindow->ShowWindow(SW_SHOW);

		m_pCurWindow = pNewWindow;
		m_emCurType = windowType;
	}

	return pNewWindow;
}

void CConfigureDlg::OnBnClickedButtonAlarm()
{
	// TODO: 在此添加控件通知处理程序代码
	CMotionDlg *pMotionDlg = (CMotionDlg*)CreatWindows(WINDOW_MOTION);
	if (pMotionDlg == NULL)
	{
		return;
	}
	pMotionDlg->StartRealPlay();
}

void CConfigureDlg::OnBnClickedButtonPrivacy()
{
	// TODO: 在此添加控件通知处理程序代码
	CPrivacyDlg *pPrivacyDlg = (CPrivacyDlg*)CreatWindows(WINDOW_PRIVACY);
	if (pPrivacyDlg == NULL)
	{
		return;
	}

	pPrivacyDlg->StartRealPlay();
}


void CConfigureDlg::OnBnClickedButtonImage()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pDlg = CreatWindows(WINDOW_IMAGE);
	if (pDlg == NULL)
	{
		return;
	}
}


void CConfigureDlg::OnBnClickedButtonEncode()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pDlg = CreatWindows(WINDOW_ENCODE);
	if (pDlg == NULL)
	{
		return;
	}
}


void CConfigureDlg::OnBnClickedButtonService()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pDlg = CreatWindows(WINDOW_SERVICE);
	if (pDlg == NULL)
	{
		return;
	}
}


void CConfigureDlg::OnBnClickedButtonTime()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pDlg = CreatWindows(WINDOW_TIME);
	if (pDlg == NULL)
	{
		return;
	}
}


void CConfigureDlg::OnBnClickedButtonNet()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pDlg = CreatWindows(WINDOW_NET);
	if (pDlg == NULL)
	{
		return;
	}
}

void CConfigureDlg::OnBnClickedButtonUser()
{
	// TODO: 在此添加控件通知处理程序代码

	CWnd *pDlg = CreatWindows(WINDOW_USER);
	if (pDlg == NULL)
	{
		return;
	}
}


void CConfigureDlg::OnBnClickedButtonSystem()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pDlg = CreatWindows(WINDOW_SYSTEM);
	if (pDlg == NULL)
	{
		return;
	}
}
