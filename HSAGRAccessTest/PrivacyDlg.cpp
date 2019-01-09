// PrivacyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "PrivacyDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CPrivacyDlg 对话框

IMPLEMENT_DYNAMIC(CPrivacyDlg, CDialogEx)

CPrivacyDlg::CPrivacyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrivacyDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg*)pParent;
	m_bPress = false;
	m_nIndex = -1;
}

CPrivacyDlg::~CPrivacyDlg()
{
	StopRealPlay();
}

void CPrivacyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PY_PLAY, m_PlayStatic);
}


BEGIN_MESSAGE_MAP(CPrivacyDlg, CDialogEx)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CPrivacyDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CPrivacyDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CPrivacyDlg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CPrivacyDlg 消息处理程序
BOOL CPrivacyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_PlayStatic.GetWindowRect(&m_PlayRect);
	ScreenToClient(&m_PlayRect);

	return TRUE;
}


void CALLBACK CPrivacyDlg::DrawCallbackFun( int nRealPlayId, HDC hDC, void *lpContext )
{
	CPrivacyDlg *pThis = (CPrivacyDlg*)lpContext;
	if (pThis == NULL || hDC == NULL)
	{
		return;
	}

	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	SelectObject(hDC, hBrush);
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(hDC, hPen);

	for (int i = 0; i < MAX_PRIVACY_REGION; ++i)
	{
		Rectangle(hDC, 
			pThis->m_PrivacyRegion[i].left, 
			pThis->m_PrivacyRegion[i].top, 
			pThis->m_PrivacyRegion[i].right, 
			pThis->m_PrivacyRegion[i].bottom);
	}
	DeleteObject(hPen);
	DeleteObject(hBrush); 
}

int CPrivacyDlg::StartRealPlay()
{
	m_pParent->m_channelInfo.hwnd = m_PlayStatic.m_hWnd;
	m_nRealplayId = HS_NET_RealPlayStart(m_pParent->m_nLoginID, &m_pParent->m_channelInfo, NULL, NULL);
	if (m_nRealplayId == -1)
	{
		MessageBox("Play failed!");
		return -1;
	}

	HS_NET_ClientSetDrawCallback(m_nRealplayId, (fNetDrawCallback)CPrivacyDlg::DrawCallbackFun, this);

	return 0;
}

void CPrivacyDlg::StopRealPlay()
{
	if (m_nRealplayId != -1)
	{
		HS_NET_RealPlayStop(m_nRealplayId);
		m_nRealplayId = -1;
	}
}

afx_msg void CPrivacyDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_PlayRect.PtInRect(point) && m_nIndex < 2)
	{
		m_nIndex++;
		m_bPress = TRUE;
		m_ptStartPoint = point;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

afx_msg void CPrivacyDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bPress)
	{
		if(m_PlayRect.PtInRect(point))
		{
			m_ptEndPoint = point;

			int x1 = m_ptStartPoint.x < m_ptEndPoint.x ? m_ptStartPoint.x : m_ptEndPoint.x;
			int y1 = m_ptStartPoint.y < m_ptEndPoint.y ? m_ptStartPoint.y : m_ptEndPoint.y;

			int x2 = m_ptStartPoint.x > m_ptEndPoint.x ? m_ptStartPoint.x : m_ptEndPoint.x;
			int y2 = m_ptStartPoint.y > m_ptEndPoint.y ? m_ptStartPoint.y : m_ptEndPoint.y;

			m_PrivacyRegion[m_nIndex].left = x1 - m_PlayRect.left;
			m_PrivacyRegion[m_nIndex].top = y1 - m_PlayRect.top;
			m_PrivacyRegion[m_nIndex].right = x2 - m_PlayRect.left;
			m_PrivacyRegion[m_nIndex].bottom = y2 - m_PlayRect.top;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

afx_msg void CPrivacyDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bPress = FALSE;
	
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CPrivacyDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nIndex = -1;
	for (int i = 0; i<MAX_PRIVACY_REGION; ++i)
	{
		m_PrivacyRegion[i].left = 0;
		m_PrivacyRegion[i].top = 0;
		m_PrivacyRegion[i].right = 0;
		m_PrivacyRegion[i].bottom = 0;
	}
}


void CPrivacyDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
// 	unsigned long ulBitRate, ulFrameRate, ulWidth, ulHeight;
// 	if(HS_NET_ClientGetBitStreamInfo(m_nRealplayId, &ulBitRate, &ulFrameRate, &ulWidth, &ulHeight) != 0)
// 	{
// 		MessageBox("HS_NET_ClientGetBitStreamInfo failed!");
// 		return;
// 	}

	HS_VIDEOCOVER_PROPERTY vcInfo;
	memset(&vcInfo, 0, sizeof(HS_VIDEOCOVER_PROPERTY));
	if (HS_NET_GetVideoCover(m_nRealplayId, &vcInfo) != 0)
	{
		MessageBox("HS_NET_GetVideoCover failed!");
		return;
	}

	for (int i = 0; i < MAX_PRIVACY_REGION; ++i)
	{
		m_PrivacyRegion[i].left = vcInfo.ucArea[i].x1*m_PlayRect.Width()/100;
		m_PrivacyRegion[i].top = vcInfo.ucArea[i].y1*m_PlayRect.Height()/100;
		m_PrivacyRegion[i].right = vcInfo.ucArea[i].x2*m_PlayRect.Width()/100;
		m_PrivacyRegion[i].bottom = vcInfo.ucArea[i].y2*m_PlayRect.Height()/100;
	}
}


void CPrivacyDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
// 	unsigned long ulBitRate, ulFrameRate, ulWidth, ulHeight;
// 	if(HS_NET_ClientGetBitStreamInfo(m_nRealplayId, &ulBitRate, &ulFrameRate, &ulWidth, &ulHeight) != 0)
// 	{
// 		MessageBox("HS_NET_ClientGetBitStreamInfo failed!");
// 		return;
// 	}

	HS_VIDEOCOVER_PROPERTY vcInfo;
	memset(&vcInfo, 0, sizeof(HS_VIDEOCOVER_PROPERTY));
	vcInfo.ucEnable = 0;
	vcInfo.ucType = 0;
	for (int i = 0; i < MAX_PRIVACY_REGION; ++i)
	{
		vcInfo.ucArea[i].x1 = m_PrivacyRegion[i].left  * 100 / m_PlayRect.Width();
		vcInfo.ucArea[i].y1 = m_PrivacyRegion[i].top  * 100 / m_PlayRect.Height();
		vcInfo.ucArea[i].x2 = m_PrivacyRegion[i].right  * 100 / m_PlayRect.Width();
		vcInfo.ucArea[i].y2 = m_PrivacyRegion[i].bottom  * 100 / m_PlayRect.Height();
	}

	if (HS_NET_SetVideoCover(m_nRealplayId, &vcInfo) != 0)
	{
		MessageBox("HS_NET_GetVideoCover failed!");
		return;
	}

	
}
