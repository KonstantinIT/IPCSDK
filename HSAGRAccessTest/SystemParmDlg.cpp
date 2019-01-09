// SystemParmDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "SystemParmDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CSystemParmDlg 对话框

IMPLEMENT_DYNAMIC(CSystemParmDlg, CDialogEx)

CSystemParmDlg::CSystemParmDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemParmDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg *)pParent;
}

CSystemParmDlg::~CSystemParmDlg()
{
}

void CSystemParmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DATE, m_cbRebootDate);
	DDX_Control(pDX, IDC_COMBO_TIME, m_cbRebootTime);
}


BEGIN_MESSAGE_MAP(CSystemParmDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REBOOT, &CSystemParmDlg::OnBnClickedButtonReboot)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CSystemParmDlg::OnBnClickedButtonRestore)
	ON_BN_CLICKED(IDC_BUTTON_SCHED_REBOOT, &CSystemParmDlg::OnBnClickedButtonSchedReboot)
	ON_BN_CLICKED(IDC_BUTTON_SCHED_GET, &CSystemParmDlg::OnBnClickedButtonSchedGet)
	ON_BN_CLICKED(IDC_BUTTON_DEVICEINFO, &CSystemParmDlg::OnBnClickedButtonDeviceinfo)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, &CSystemParmDlg::OnBnClickedButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_UPGRAGE, &CSystemParmDlg::OnBnClickedButtonUpgrage)
	ON_BN_CLICKED(IDC_BUTTON_SET_DEVICEINFO, &CSystemParmDlg::OnBnClickedButtonSetDeviceinfo)
END_MESSAGE_MAP()


// CSystemParmDlg 消息处理程序
BOOL CSystemParmDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_cbRebootDate.AddString("Never");
	m_cbRebootDate.AddString("Every");
	m_cbRebootDate.AddString("Mon");
	m_cbRebootDate.AddString("Tue");
	m_cbRebootDate.AddString("Wed");
	m_cbRebootDate.AddString("Thu");
	m_cbRebootDate.AddString("Fri");
	m_cbRebootDate.AddString("Sat");
	m_cbRebootDate.AddString("Sun");

	for (int i = 0; i < 24; i++)
	{
		CString temp;
		temp.Format("%02d:00", i);
		m_cbRebootTime.AddString(temp);
	}

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

LRESULT CSystemParmDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_MSG_UPGRADE_POS:
		{
			int nPercent = (int)wParam;
			SetDlgItemInt(IDC_EDIT_PROGRESS, nPercent);
		}
		break;
	case WM_MSG_UPGRADE_OK:
		MessageBox("Upgrade Success!");
		break;
	case WM_MSG_UPGRADE_FAILED:
		MessageBox("Upgrade failed!");
		break;
	default:
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

void CSystemParmDlg::OnBnClickedButtonReboot()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox("Are you sure to reboot?", "Warning",MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
		return;

	HS_NET_Reboot(m_pParent->m_nLoginID);
}


void CSystemParmDlg::OnBnClickedButtonRestore()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox("Are you sure to restore?", "Warning",MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
		return;

	HS_NET_Reset(m_pParent->m_nLoginID);
}


void CSystemParmDlg::OnBnClickedButtonSchedReboot()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCurSel = m_cbRebootDate.GetCurSel();
	if (nCurSel == 0)
	{
		m_Sysreboot.ucEnable = 0;
	}
	else 
	{
		m_Sysreboot.ucEnable = 1;
		switch(nCurSel)
		{
		case 1:
			m_Sysreboot.ucWeekData = 7;
			break;
		case 2:
			m_Sysreboot.ucWeekData = 1;
			break;
		case 3:
			m_Sysreboot.ucWeekData = 2;
			break;
		case 4:
			m_Sysreboot.ucWeekData = 3;
			break;
		case 5:
			m_Sysreboot.ucWeekData = 4;
			break;
		case 6:
			m_Sysreboot.ucWeekData = 5;
			break;
		case 7:
			m_Sysreboot.ucWeekData = 6;
			break;
		case 8:
			m_Sysreboot.ucWeekData = 0;
			break;
		default:
			break;
		}

		m_Sysreboot.ucHour = m_cbRebootTime.GetCurSel();
	}
	
	if(HS_NET_SetTimeReboot(m_pParent->m_nLoginID, &m_Sysreboot) != 0)
	{
		MessageBox("HS_NET_SetTimeReboot failed!");
		return;
	}
}


void CSystemParmDlg::OnBnClickedButtonSchedGet()
{
	// TODO: 在此添加控件通知处理程序代码
	memset(&m_Sysreboot, 0, sizeof(HS_SYSREBOOT_PROPERTY));
	if (HS_NET_GetTimeReboot(m_pParent->m_nLoginID, &m_Sysreboot) != 0)
	{
		MessageBox("HS_NET_GetTimeReboot failed!");
		return;
	}

	
	if(m_Sysreboot.ucEnable)
	{
		int week;
		switch(m_Sysreboot.ucWeekData)
		{
		case 0:
			week = 8;
			break;
		case 1:
			week = 2;
			break;
		case 2:
			week = 3;
			break;
		case 3:
			week = 4;
			break;
		case 4:
			week = 5;
			break;
		case 5:
			week = 6;
			break;
		case 6:
			week = 7;
			break;
		case 7:
			week = 1;
			break;
		}

		m_cbRebootDate.SetCurSel(week);
		m_cbRebootTime.SetCurSel(m_Sysreboot.ucHour);
	}
	else
	{
		m_cbRebootDate.SetCurSel(0);
		m_cbRebootTime.SetCurSel(0);
	}
}

void CSystemParmDlg::OnBnClickedButtonDeviceinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	memset(&m_Devinfo, 0, sizeof(HS_DEV_INFO));
	
	if(HS_NET_GetDeviceInfo(m_pParent->m_nLoginID, &m_Devinfo) != 0)
	{
		MessageBox("HS_NET_GetDeviceInfo failed!");
		return;
	}

	GetDlgItem(IDC_EDIT_FIRMVER)->SetWindowText((char*)m_Devinfo.ucFirmwareVersion);
	GetDlgItem(IDC_EDIT_SOFTVER)->SetWindowText((char*)m_Devinfo.ucSoftwareVersion);
	GetDlgItem(IDC_EDIT_IPC_NAME)->SetWindowText((char*)m_Devinfo.ucDevName);
}


void CSystemParmDlg::OnBnClickedButtonScan()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR filter[] = _T("所有文件 (*.*)|*.*|图片 (*.gif;*.jpg)|*.gif;*.jpg|HTML (*.HTM;*.HTML)|*.HTM;*.HTML|PACKAGE (*.package)|*.package|FLS (*.FLS)|*.FLS||");
	CFileDialog fdlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_EXPLORER | OFN_NOCHANGEDIR,filter,this);
	if(fdlg.DoModal() == IDOK) 
	{
		m_csUpgradeFile = fdlg.GetPathName();
		GetDlgItem(IDC_EDIT_UPGRAGE)->SetWindowText(m_csUpgradeFile);
	}
}


void CSystemParmDlg::OnBnClickedButtonUpgrage()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox("Are you sure to upgrade?", "Warning",MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)
		return;

	if (m_csUpgradeFile.IsEmpty())
	{
		MessageBox("file path empty!");
		return;
	}

	if(HS_NET_Upgrade(m_pParent->m_nLoginID, m_csUpgradeFile) != 0)
	{
		MessageBox("HS_NET_Upgrade failed!");
	}
}


void CSystemParmDlg::OnBnClickedButtonSetDeviceinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	GetDlgItem(IDC_EDIT_IPC_NAME)->GetWindowText(temp);
	strncpy((char*)m_Devinfo.ucDevName, temp, 64);

	if(HS_NET_SetDeviceInfo(m_pParent->m_nLoginID, &m_Devinfo) != 0)
	{
		MessageBox("HS_NET_SetDeviceInfo failed!");
		return;
	}
}
