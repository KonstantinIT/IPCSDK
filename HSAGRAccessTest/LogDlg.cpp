// LogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "LogDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CLogDlg 对话框

IMPLEMENT_DYNAMIC(CLogDlg, CDialogEx)

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg*)pParent;
}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATE_START, m_dcStartDate);
	DDX_Control(pDX, IDC_TIME_START, m_dcStartTime);
	DDX_Control(pDX, IDC_DATE_END, m_dcEndDate);
	DDX_Control(pDX, IDC_TIME_END, m_dcEndTime);
	DDX_Control(pDX, IDC_LIST_LOG, m_clLogInfoList);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CLogDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CLogDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CLogDlg 消息处理程序
BOOL CLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_clLogInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
	m_clLogInfoList.InsertColumn(0,"ID",LVCFMT_LEFT,50);
	m_clLogInfoList.InsertColumn(1,"Time",LVCFMT_LEFT,140);
	m_clLogInfoList.InsertColumn(2,"Detail",LVCFMT_LEFT,500);
	CTime temp = CTime::GetCurrentTime();
	CTime temp1(temp.GetYear(), temp.GetMonth(), temp.GetDay(), 0, 0, 0);
	m_dcStartTime.SetTime(&temp1);
	CTime temp2(temp.GetYear(), temp.GetMonth(), temp.GetDay(), 23, 59, 59);
	m_dcEndTime.SetTime(&temp2);

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CLogDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(FALSE);
	CTime startDate;
	CTime startTime;
	CTime endDate;
	CTime endTime;
	m_dcStartDate.GetTime(startDate);
	m_dcStartTime.GetTime(startTime);
	m_dcEndDate.GetTime(endDate);
	m_dcEndTime.GetTime(endTime);

	CTime startDateTime(startDate.GetYear(), startDate.GetMonth(), startDate.GetDay(), startTime.GetHour(), startTime.GetMinute(), startTime.GetSecond());
	CTime endDateTime(endDate.GetYear(), endDate.GetMonth(), endDate.GetDay(), endTime.GetHour(), endTime.GetMinute(), endTime.GetSecond());

	TIME_ZONE_INFORMATION timezoneinfo;
	GetTimeZoneInformation(&timezoneinfo);
	int nTimeZoon = (float)timezoneinfo.Bias/60;
	startDateTime -= CTimeSpan(0, nTimeZoon, 0, 0);
	endDateTime -= CTimeSpan(0, nTimeZoon, 0, 0);

	HS_LOG_GREP_INFO loggrepinfo;
	HS_LOG_INFO loginfo;
	memset(&loggrepinfo, 0, sizeof(HS_LOG_GREP_INFO));
	memset(&loginfo, 0, sizeof(HS_LOG_INFO));

	loggrepinfo.ulStartTime = startDateTime.GetTime();
	loggrepinfo.ulEndTime = endDateTime.GetTime();
	if (loggrepinfo.ulStartTime >= loggrepinfo.ulEndTime)
	{
		//The start time must be losser than end time;
		//so far, only surpport searching by time 
		MessageBox("start time must be lesser than end time!");
		return ;
	}

	HS_LOG_EVENT_INFO logeventinfo[1000];
	int nbufNum = 1000;
	int nCount;
	if(HS_NET_GetLogFile(m_pParent->m_nLoginID, &loggrepinfo, logeventinfo, nbufNum, &nCount) == -1)
	{
		MessageBox("Get log file failed!");
		return;
	}

	m_clLogInfoList.DeleteAllItems();

	for (int i = 0; i< nCount; ++i)
	{
		int nListCount  = m_clLogInfoList.GetItemCount();
		CString str;
		str.Format(_T("%d"), logeventinfo[i].ulNo);
		int Index = m_clLogInfoList.InsertItem(nListCount,str);

		struct tm *tm;
		time_t tt =logeventinfo[i].ulTIme;

		tm  = gmtime(&tt);
		char out[255];
		memset(out, 0, sizeof(out));
		strftime(out, 255, "%Y-%m-%d %H:%M:%S", tm);
		m_clLogInfoList.SetItemText(Index, 1, (CString)out);
		m_clLogInfoList.SetItemText(Index, 2, (CString)(logeventinfo[i].ucMes));
	}
}


void CLogDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_clLogInfoList.DeleteAllItems();
}
