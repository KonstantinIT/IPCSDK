// MotionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "MotionDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CMotionDlg 对话框

IMPLEMENT_DYNAMIC(CMotionDlg, CDialogEx)

CMotionDlg::CMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMotionDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg*)pParent;
	m_bPress = FALSE;

	for (int i = 0; i < TIMBLOCKMAX_NY_ACT; ++i)
	{
		for (int j = 0; j < TIMBLOCKMAX_NX_ACT; ++j)
		{
			m_MBlock[i][j] = 0;
		}
	}
}

CMotionDlg::~CMotionDlg()
{
	StopRealPlay();
}

void CMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SENSITIVE, m_etSensiEdit);
}


BEGIN_MESSAGE_MAP(CMotionDlg, CDialogEx)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_ALL, &CMotionDlg::OnBnClickedButtonSelectAll)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMotionDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_MT_GET, &CMotionDlg::OnBnClickedButtonMtGet)
	ON_BN_CLICKED(IDC_BUTTON_MT_SET, &CMotionDlg::OnBnClickedButtonMtSet)
END_MESSAGE_MAP()


// CMotionDlg 消息处理程序
BOOL CMotionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_STATIC_PLAY)->GetClientRect(m_PlayRect);
	m_PlayRect.right -= m_PlayRect.Width()%TIMBLOCKMAX_NX_ACT;
	m_PlayRect.bottom -= m_PlayRect.Height()%TIMBLOCKMAX_NY_ACT;
	GetDlgItem(IDC_STATIC_PLAY)->MoveWindow(m_PlayRect);

	GetDlgItem(IDC_STATIC_PLAY)->GetWindowRect(m_PlayRect);
	ScreenToClient(&m_PlayRect);

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CALLBACK CMotionDlg::DrawCallbackFun( int nRealPlayId, HDC hDC, void *lpContext )
{
	CMotionDlg *pThis = (CMotionDlg*)lpContext;
	if (pThis == NULL || hDC == NULL)
	{
		return;
	}

	int i,j;
	int rectW = (pThis->m_PlayRect.right - pThis->m_PlayRect.left) / TIMBLOCKMAX_NX_ACT;
	int rectH = (pThis->m_PlayRect.bottom - pThis->m_PlayRect.top) / TIMBLOCKMAX_NY_ACT;


	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	SelectObject(hDC, hBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(hDC, hPen);

	for(int k=0;k<TIMBLOCKMAX_NY_ACT;k++)
	{
		for(int l=0;l<TIMBLOCKMAX_NX_ACT;l++)
		{
			if (pThis->m_MBlock[k][l])
			{
				j = k % TIMBLOCKMAX_NY_ACT;
				i = l % TIMBLOCKMAX_NX_ACT;
				Rectangle(hDC,(i* rectW), j * rectH, (i * rectW) + rectW, (j * rectH) + rectH);							        					
			}
		}
	}


	DeleteObject(hPen);
	DeleteObject(hBrush); 
}

int CMotionDlg::StartRealPlay()
{
	m_pParent->m_channelInfo.hwnd = GetDlgItem(IDC_STATIC_PLAY)->m_hWnd;
	m_nRealplayId = HS_NET_RealPlayStart(m_pParent->m_nLoginID, &m_pParent->m_channelInfo, NULL, NULL);
	if (m_nRealplayId == -1)
	{
		MessageBox("Play failed!");
		return -1;
	}

	HS_NET_ClientSetDrawCallback(m_nRealplayId, (fNetDrawCallback)CMotionDlg::DrawCallbackFun, this);

	return 0;
}

void CMotionDlg::StopRealPlay()
{
	if (m_nRealplayId != -1)
	{
		HS_NET_RealPlayStop(m_nRealplayId);
		m_nRealplayId = -1;
	}
}

afx_msg void CMotionDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_PlayRect.PtInRect(point))
	{
		m_bPress = TRUE;
		m_ptStartPoint = point;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

afx_msg void CMotionDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bPress)
	{
		if(m_PlayRect.PtInRect(point))
		{
			m_ptEndPoint = point;

			int rectW = (m_PlayRect.right - m_PlayRect.left) / TIMBLOCKMAX_NX_ACT;
			int rectH = (m_PlayRect.bottom - m_PlayRect.top) / TIMBLOCKMAX_NY_ACT;

			int x1 = m_ptStartPoint.x < m_ptEndPoint.x ? m_ptStartPoint.x : m_ptEndPoint.x;
			int y1 = m_ptStartPoint.y < m_ptEndPoint.y ? m_ptStartPoint.y : m_ptEndPoint.y;

			int x2 = m_ptStartPoint.x > m_ptEndPoint.x ? m_ptStartPoint.x : m_ptEndPoint.x;
			int y2 = m_ptStartPoint.y > m_ptEndPoint.y ? m_ptStartPoint.y : m_ptEndPoint.y;

			int xBeginPos = (x1 - m_PlayRect.left) / rectW;
			int yBeginPos = (y1 - m_PlayRect.top) / rectH;

			int xEndPos = (x2 - m_PlayRect.left) / rectW;
			if(((x2 - m_PlayRect.left) % rectW) > 0)
				xEndPos += 1;
			int yEndPos	= (y2 - m_PlayRect.top) / rectH;
			if(((y2 - m_PlayRect.top) % rectH) > 0)
				yEndPos += 1;

			
				for (int i = yBeginPos; i < yEndPos; i++)
				{
					for(int j = xBeginPos; j < xEndPos; j++)
					{
						m_MBlock[i][j] = 1;
					}
				}
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

afx_msg void CMotionDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bPress = FALSE;

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMotionDlg::OnBnClickedButtonSelectAll()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = 0; i < TIMBLOCKMAX_NY_ACT; i++)
	{
		for (int j = 0; j < TIMBLOCKMAX_NX_ACT; j++)
		{
			m_MBlock[i][j] = 1;
		}
	}
}


void CMotionDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = 0; i < TIMBLOCKMAX_NY_ACT; i++)
	{
		for (int j = 0; j < TIMBLOCKMAX_NX_ACT; j++)
		{
			m_MBlock[i][j] = 0;
		}
	}
}


void CMotionDlg::OnBnClickedButtonMtGet()
{
	// TODO: 在此添加控件通知处理程序代码
	HS_MOTIONDETECTION_EX_PROPERTY motionInfo;
	memset(&motionInfo, 0, sizeof(HS_MOTIONDETECTION_EX_PROPERTY));
	if(HS_NET_GetMDInfo(m_pParent->m_nLoginID, &motionInfo) != 0)
	{
		MessageBox("Get Motion Info failed!\n");
	}

	SetDlgItemInt(IDC_EDIT_SENSITIVE, motionInfo.ucSensitivity);
	((CButton*)GetDlgItem(IDC_CHECK_MT_ENABLE))->SetCheck(motionInfo.ucEnable);

	for(int i = 0; i < TIMBLOCKMAX_NY_ACT; i++)
	{
		for (int j = 0; j < TIMBLOCKMAX_NX_ACT; j++)
		{
			m_MBlock[i][j] = (motionInfo.region.area.ulBlock[i]>>j)&0x01;
		}
	}
}


void CMotionDlg::OnBnClickedButtonMtSet()
{
	// TODO: 在此添加控件通知处理程序代码
	HS_MOTIONDETECTION_EX_PROPERTY motionInfo;
	memset(&motionInfo, 0, sizeof(HS_MOTIONDETECTION_EX_PROPERTY));

	motionInfo.ucEnable = ((CButton*)GetDlgItem(IDC_CHECK_MT_ENABLE))->GetCheck();
	motionInfo.ucSensitivity = GetDlgItemInt(IDC_EDIT_SENSITIVE);

	for(int i = 0; i < TIMBLOCKMAX_NY_ACT; i++)
	{
		for (int j = 0; j < TIMBLOCKMAX_NX_ACT; j++)
		{
			motionInfo.region.area.ulBlock[i] |= m_MBlock[i][j] << j; 
		}
	}

	if(HS_NET_SetMDInfo(m_pParent->m_nLoginID, &motionInfo) != 0)
	{
		MessageBox("Set Motion Info failed!\n");
	}
	else
	{
		MessageBox("Set Motion Info Success!\n");
	}
}
