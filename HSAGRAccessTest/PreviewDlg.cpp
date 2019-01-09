// PreviewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "PreviewDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CPreviewDlg �Ի���

IMPLEMENT_DYNAMIC(CPreviewDlg, CDialogEx)

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPreviewDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg*)pParent;
	m_nCurWnd = 0;
	for (int i = 0; i < MAX_WND; ++i)
	{
		m_nRealplayID[i] = -1;
	}
}

CPreviewDlg::~CPreviewDlg()
{
	OnBnClickedButtonPlayStop();
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_START, &CPreviewDlg::OnBnClickedButtonPlayStart)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_STOP, &CPreviewDlg::OnBnClickedButtonPlayStop)
	ON_BN_CLICKED(IDC_BUTTON_CAP, &CPreviewDlg::OnBnClickedButtonCap)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_START, &CPreviewDlg::OnBnClickedButtonRecordStart)
	ON_BN_CLICKED(IDC_BUTTON_RECORD_STOP, &CPreviewDlg::OnBnClickedButtonRecordStop)
	ON_STN_CLICKED(IDC_STATIC_WND_1, &CPreviewDlg::OnStnClickedStaticWnd1)
	ON_STN_CLICKED(IDC_STATIC_WND_2, &CPreviewDlg::OnStnClickedStaticWnd2)
	ON_STN_CLICKED(IDC_STATIC_WND_3, &CPreviewDlg::OnStnClickedStaticWnd3)
	ON_STN_CLICKED(IDC_STATIC_WND_4, &CPreviewDlg::OnStnClickedStaticWnd4)
END_MESSAGE_MAP()


// CPreviewDlg ��Ϣ�������
BOOL CPreviewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_hPlayWnd[0] = (GetDlgItem(IDC_STATIC_WND_1))->m_hWnd;
	m_hPlayWnd[1] = (GetDlgItem(IDC_STATIC_WND_2))->m_hWnd;
	m_hPlayWnd[2] = (GetDlgItem(IDC_STATIC_WND_3))->m_hWnd;
	m_hPlayWnd[3] = (GetDlgItem(IDC_STATIC_WND_4))->m_hWnd;

	return TRUE;
}

LRESULT CPreviewDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_MSG_UPGRADE_POS:
		break;
	case WM_MSG_RECORD_BEGIN:
		break;
	case WM_MSG_RECORD_WRITE_ERROR:
		break;
	case WM_MSG_RECORD_PACKET_FINISH:
		break;
	case WM_MSG_RECORD_BEGIN_ANOTHER:
		break;
	case WM_MSG_RECORD_WRITE_ERROR_ANOTHER: 
		break;
	case WM_MSG_RECORD_PACKET_FINISH_ANOTHER:
		break;
	case WM_MSG_MOTION_DETECT:
		{
			HS_MOTION_DETECT_INFO *temp = (HS_MOTION_DETECT_INFO*)wParam;
			//
			delete temp;
		}
		break;
	default:
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

void CPreviewDlg::OnBnClickedButtonPlayStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedButtonPlayStop();
	m_pParent->m_channelInfo.hwnd = m_hPlayWnd[m_nCurWnd];
	m_nRealplayID[m_nCurWnd] = HS_NET_RealPlayStart(m_pParent->m_nLoginID, &m_pParent->m_channelInfo, NULL, NULL);
	if (m_nRealplayID[m_nCurWnd] == -1)
	{
		MessageBox("Play failed!");
	}
}

void CPreviewDlg::OnBnClickedButtonPlayStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_nRealplayID[m_nCurWnd] != -1)
	{
		HS_NET_RealPlayStop(m_nRealplayID[m_nCurWnd]);
		m_nRealplayID[m_nCurWnd] = -1;
	}
}

void CPreviewDlg::OnBnClickedButtonCap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime tm = CTime::GetCurrentTime();
	CString filename;
	filename.Format("C:\\Capture\\%d_%d_%d_%d_%d_%d_%d.jpg", tm.GetYear(), 
		tm.GetMonth(),tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond(), m_nCurWnd);
	HS_NET_ClientCapturePicture(m_nRealplayID[m_nCurWnd], filename);
}

void CPreviewDlg::OnBnClickedButtonRecordStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime tm = CTime::GetCurrentTime();

	CString filename;
	filename.Format("E:\\Record\\%d_%d_%d_%d_%d_%d_%d.avi", tm.GetYear(), 
		tm.GetMonth(),tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond(), m_nCurWnd);

	HS_NET_ClientStartRecord(m_nRealplayID[m_nCurWnd], filename.GetBuffer(0));//���Ҫ��¼��ʱ�䣬¼�����ʱ��ͨ����Ϣ�ص�֪ͨ
}

void CPreviewDlg::OnBnClickedButtonRecordStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HS_NET_ClientStopRecord(m_nRealplayID[m_nCurWnd]);
}


void CPreviewDlg::OnStnClickedStaticWnd1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCurWnd = 0;
}

void CPreviewDlg::OnStnClickedStaticWnd2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCurWnd = 1;
}

void CPreviewDlg::OnStnClickedStaticWnd3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCurWnd = 2;
}

void CPreviewDlg::OnStnClickedStaticWnd4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nCurWnd = 3;
}
