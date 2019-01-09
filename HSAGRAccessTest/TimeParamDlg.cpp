// TimeParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "TimeParamDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CTimeParamDlg 对话框

IMPLEMENT_DYNAMIC(CTimeParamDlg, CDialogEx)

CTimeParamDlg::CTimeParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeParamDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg *)pParent;
	m_Timer = NULL;
}

CTimeParamDlg::~CTimeParamDlg()
{

}

void CTimeParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ZONE, m_cbTimeZone);
	DDX_Control(pDX, IDC_COMBO_SNTP, m_cbSntpServer);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE, m_dtManuDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIME, m_dtManuTime);
}


BEGIN_MESSAGE_MAP(CTimeParamDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GET, &CTimeParamDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CTimeParamDlg::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_RADIO_MANU, &CTimeParamDlg::OnBnClickedRadioManu)
	ON_BN_CLICKED(IDC_RADIO_COMPU, &CTimeParamDlg::OnBnClickedRadioCompu)
	ON_BN_CLICKED(IDC_RADIO_SNTP, &CTimeParamDlg::OnBnClickedRadioSntp)
END_MESSAGE_MAP()


// CTimeParamDlg 消息处理程序
BOOL CTimeParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimeParamDlg::CheckRadioState()
{
	((CButton*)GetDlgItem(IDC_RADIO_MANU))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_COMPU))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_SNTP))->SetCheck(FALSE);
	switch(m_TimeInfo.ucModel)
	{
	case MANNU:
		((CButton*)GetDlgItem(IDC_RADIO_MANU))->SetCheck(TRUE);
		break;
	case COMPU:
		((CButton*)GetDlgItem(IDC_RADIO_COMPU))->SetCheck(TRUE);
		break;
	case NTP:
		((CButton*)GetDlgItem(IDC_RADIO_SNTP))->SetCheck(TRUE);
		break;
	default:
		break;
	}
}

void CTimeParamDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strLocalDateTime;
	CTime ttime;
	ttime = CTime::GetCurrentTime();
	strLocalDateTime.Format(_T("%d/%02d/%02d %02d:%02d:%02d"),
		ttime.GetYear(),ttime.GetMonth(),ttime.GetDay(),
		ttime.GetHour(),ttime.GetMinute(),ttime.GetSecond());
	GetDlgItem(IDC_EDIT_DATETIME_COMPU)->SetWindowText(strLocalDateTime);

	CString strDateTime;
	CTimeSpan span = ttime - m_tiGetTime;
	CTime ipcTime(m_TimeInfo.usYear, m_TimeInfo.ucMonth, m_TimeInfo.ucDay,
		m_TimeInfo.ucHour, m_TimeInfo.ucMinute, m_TimeInfo.ucSecond);
	ipcTime += span;
	strDateTime.Format("%04d/%02d/%02d %02d:%02d:%02d",
		ipcTime.GetYear(),ipcTime.GetMonth(),ipcTime.GetDay(),
		ipcTime.GetHour(),ipcTime.GetMinute(),ipcTime.GetSecond());
	GetDlgItem(IDC_EDIT_DATETIME_IPC)->SetWindowText(strDateTime);

	CDialog::OnTimer(nIDEvent);
}

void CTimeParamDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_Timer)
	{
		KillTimer(m_Timer);
		m_Timer = NULL;
	}

	memset(&m_TimeInfo, 0, sizeof(HS_TIME_INFO));
	if(HS_NET_GetTimeParam(m_pParent->m_nLoginID, &m_TimeInfo) != 0)
	{
		MessageBox("HS_NET_GetTimeParam failed!");
		return;
	}

	CTime ipcTime(m_TimeInfo.usYear, m_TimeInfo.ucMonth, m_TimeInfo.ucDay,
		m_TimeInfo.ucHour, m_TimeInfo.ucMinute, m_TimeInfo.ucSecond);

	m_tiGetTime = CTime::GetCurrentTime();

	m_emTimeModel = (TIME_MODEL)m_TimeInfo.ucModel;
	CheckRadioState();
	m_dtManuDate.SetTime(&ipcTime);
	m_dtManuTime.SetTime(&ipcTime);
	m_cbSntpServer.SelectString(-1, (char*)m_TimeInfo.ucSNTPServerAddr);
	m_cbTimeZone.SetCurSel(m_TimeInfo.ucTimeZoon);
	((CButton*)GetDlgItem(IDC_CHECK_ALLOW))->SetCheck(m_TimeInfo.ucNVRModify);

	OnTimer(m_Timer);
	m_Timer = SetTimer(1, 1000, NULL);
	

	UpdateData(FALSE);
}

void CTimeParamDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TimeInfo.ucModel = m_emTimeModel;
	m_TimeInfo.ucNVRModify = ((CButton*)GetDlgItem(IDC_CHECK_ALLOW))->GetCheck();
	switch(m_emTimeModel)
	{
	case MANNU:
		{
			CTime tDate;
			CTime tTime;
			m_dtManuDate.GetTime(tDate);
			m_dtManuTime.GetTime(tTime);
			m_TimeInfo.usYear = tDate.GetYear();
			m_TimeInfo.ucMonth = tDate.GetMonth();
			m_TimeInfo.ucDay = tDate.GetDay();
			m_TimeInfo.ucHour = tTime.GetHour();
			m_TimeInfo.ucMinute = tTime.GetMinute();
			m_TimeInfo.ucSecond = tTime.GetSecond();

			m_TimeInfo.ucTimeZoon = m_cbTimeZone.GetCurSel();
		}
		break;
	case COMPU:
		{
			SYSTEMTIME st;
			GetLocalTime(&st);
			m_TimeInfo.usYear = st.wYear;
			m_TimeInfo.ucMonth = st.wMonth;
			m_TimeInfo.ucDay = st.wDay;
			m_TimeInfo.ucHour = st.wHour;
			m_TimeInfo.ucMinute = st.wMinute;
			m_TimeInfo.ucSecond = st.wSecond;

			TIME_ZONE_INFORMATION timezoneinfo;
			GetTimeZoneInformation(&timezoneinfo);

			switch(-timezoneinfo.Bias)
			{
			case -720:
				m_TimeInfo.ucTimeZoon = 0;
				break;
			case -690:
				m_TimeInfo.ucTimeZoon = 1;
				break;
			case -660:
				m_TimeInfo.ucTimeZoon = 2;
				break;
			case -630:
				m_TimeInfo.ucTimeZoon = 3;
				break;
			case -600:
				m_TimeInfo.ucTimeZoon = 4;
				break;
			case -570:
				m_TimeInfo.ucTimeZoon = 5;
				break;
			case -540:
				m_TimeInfo.ucTimeZoon = 6;
				break;
			case -510:
				m_TimeInfo.ucTimeZoon = 7;
				break;
			case -480:
				m_TimeInfo.ucTimeZoon = 8;
				break;
			case -450:
				m_TimeInfo.ucTimeZoon = 9;
				break;
			case -420:
				m_TimeInfo.ucTimeZoon = 10;
				break;
			case -390:
				m_TimeInfo.ucTimeZoon = 11;
				break;
			case -360:
				m_TimeInfo.ucTimeZoon = 12;
				break;
			case -330:
				m_TimeInfo.ucTimeZoon = 13;
				break;
			case -300:
				m_TimeInfo.ucTimeZoon = 14;
				break;
			case -270:
				m_TimeInfo.ucTimeZoon = 15;
				break;
			case -240:
				m_TimeInfo.ucTimeZoon = 16;
				break;
			case -210:
				m_TimeInfo.ucTimeZoon = 17;
				break;
			case -180:
				m_TimeInfo.ucTimeZoon = 18;
				break;
			case -150:
				m_TimeInfo.ucTimeZoon = 19;
				break;
			case -120:
				m_TimeInfo.ucTimeZoon = 20;
				break;
			case -90:
				m_TimeInfo.ucTimeZoon = 21;
				break;
			case -60:
				m_TimeInfo.ucTimeZoon = 22;
				break;
			case -30:
				m_TimeInfo.ucTimeZoon = 23;
				break;
			case 0:
				m_TimeInfo.ucTimeZoon = 24;
				break;
			case 30:
				m_TimeInfo.ucTimeZoon = 25;
				break;
			case 60:
				m_TimeInfo.ucTimeZoon = 26;
				break;
			case 90:
				m_TimeInfo.ucTimeZoon = 27;
				break;
			case 120:
				m_TimeInfo.ucTimeZoon = 28;
				break;
			case 150:
				m_TimeInfo.ucTimeZoon = 29;
				break;
			case 180:
				m_TimeInfo.ucTimeZoon = 30;
				break;
			case 210:
				m_TimeInfo.ucTimeZoon = 31;
				break;
			case 240:
				m_TimeInfo.ucTimeZoon = 32;
				break;
			case 270:
				m_TimeInfo.ucTimeZoon = 33;
				break;
			case 300:
				m_TimeInfo.ucTimeZoon = 34;
				break;
			case 330:
				m_TimeInfo.ucTimeZoon = 35;
				break;
			case 360:
				m_TimeInfo.ucTimeZoon = 36;
				break;
			case 390:
				m_TimeInfo.ucTimeZoon = 37;
				break;
			case 420:
				m_TimeInfo.ucTimeZoon = 38;
				break;
			case 450:
				m_TimeInfo.ucTimeZoon = 39;
				break;
			case 480:
				m_TimeInfo.ucTimeZoon = 40;
				break;
			case 510:
				m_TimeInfo.ucTimeZoon = 41;
				break;
			case 540:
				m_TimeInfo.ucTimeZoon = 42;
				break;
			case 570:
				m_TimeInfo.ucTimeZoon = 43;
				break;
			case 600:
				m_TimeInfo.ucTimeZoon = 44;
				break;
			case 630:
				m_TimeInfo.ucTimeZoon = 45;
				break;
			case 660:
				m_TimeInfo.ucTimeZoon = 46;
				break;
			case 690:
				m_TimeInfo.ucTimeZoon = 47;
				break;
			case 720:
				m_TimeInfo.ucTimeZoon = 48;
				break;

			}
		}
		break;
	case NTP:
		{
			CString strSntpServer;
			m_cbSntpServer.GetLBText(m_cbSntpServer.GetCurSel(), strSntpServer);
			strncpy((char*)m_TimeInfo.ucSNTPServerAddr,strSntpServer, 200);
			m_TimeInfo.ucTimeZoon = m_cbTimeZone.GetCurSel();
		}
		break;
	default:
		break;
	}

	if (HS_NET_SetTimeParam(m_pParent->m_nLoginID, &m_TimeInfo) != 0)
	{
		MessageBox("HS_NET_SetTimeParam failed!");
	}
}

void CTimeParamDlg::OnBnClickedRadioManu()
{
	// TODO: 在此添加控件通知处理程序代码
	m_emTimeModel = MANNU;
}

void CTimeParamDlg::OnBnClickedRadioCompu()
{
	// TODO: 在此添加控件通知处理程序代码
	m_emTimeModel = COMPU;
}

void CTimeParamDlg::OnBnClickedRadioSntp()
{
	// TODO: 在此添加控件通知处理程序代码
	m_emTimeModel = NTP;
}
