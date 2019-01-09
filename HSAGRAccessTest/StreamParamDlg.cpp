// StreamParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "StreamParamDlg.h"
#include "afxdialogex.h"


// CStreamParamDlg 对话框

IMPLEMENT_DYNAMIC(CStreamParamDlg, CDialogEx)

CStreamParamDlg::CStreamParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStreamParamDlg::IDD, pParent)
{
	m_emCodecType = NONE;
	m_pEncPrty = NULL;
	m_nMaxFrameRate = 0;
}

CStreamParamDlg::~CStreamParamDlg()
{
}

void CStreamParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FRAMERATE, m_cbFrameRate);
	DDX_Control(pDX, IDC_STATIC_QUA, m_scQua);
	DDX_Control(pDX, IDC_EDIT_QUA, m_etQua);
	DDX_Control(pDX, IDC_STATIC_BITRATE, m_scBitRate);
	DDX_Control(pDX, IDC_EDIT_BITRATE, m_etBitRate);
	DDX_Control(pDX, IDC_STATIC_BITCTR, m_scBitCtrol);
	DDX_Control(pDX, IDC_COMBO_BITCTR, m_cbBitCtrol);
	DDX_Control(pDX, IDC_STATIC_IFRAME, m_scIFrame);
	DDX_Control(pDX, IDC_COMBO_IFRAME, m_cbIFrame);
}


BEGIN_MESSAGE_MAP(CStreamParamDlg, CDialogEx)
END_MESSAGE_MAP()


// CStreamParamDlg 消息处理程序

void CStreamParamDlg::SetParam(CODEC_TYPE codecType, int maxFrameRare, HS_ENCODING_PROPERTY *encPrty)
{
	m_emCodecType = codecType;
	m_nMaxFrameRate = maxFrameRare;
	m_pEncPrty = encPrty;

	//init
	m_cbFrameRate.ResetContent();
	for (int i = 0; i < maxFrameRare; ++i)
	{
		CString temp;
		temp.Format("%d", i+1);
		m_cbFrameRate.AddString(temp);
	}

	m_cbBitCtrol.ResetContent();
	m_cbBitCtrol.AddString("VBR");
	m_cbBitCtrol.AddString("CBR");

	m_cbIFrame.ResetContent();
	for(int i = 0; i < 5; ++i)
	{
		CString temp;
		temp.Format("%d", i+1);
		m_cbIFrame.AddString(temp);
	}

	//show data
	m_cbFrameRate.SetCurSel(m_pEncPrty->property.video.ucFrameRate-1);
	if (m_emCodecType == MJPEG)
	{
		m_scQua.ShowWindow(SW_SHOW);
		m_etQua.ShowWindow(SW_SHOW);
		m_scBitRate.ShowWindow(SW_HIDE);
		m_etBitRate.ShowWindow(SW_HIDE);
		m_scBitCtrol.ShowWindow(SW_HIDE);
		m_cbBitCtrol.ShowWindow(SW_HIDE);
		m_scIFrame.ShowWindow(SW_HIDE);
		m_cbIFrame.ShowWindow(SW_HIDE);

		SetDlgItemInt(IDC_EDIT_QUA, m_pEncPrty->property.video.ucPicQuality);
	}
	else
	{
		m_scQua.ShowWindow(SW_HIDE);
		m_etQua.ShowWindow(SW_HIDE);
		m_scBitRate.ShowWindow(SW_SHOW);
		m_etBitRate.ShowWindow(SW_SHOW);
		m_scBitCtrol.ShowWindow(SW_SHOW);
		m_cbBitCtrol.ShowWindow(SW_SHOW);
		m_scIFrame.ShowWindow(SW_SHOW);
		m_cbIFrame.ShowWindow(SW_SHOW);

		SetDlgItemInt(IDC_EDIT_BITRATE, m_pEncPrty->property.video.ucBitRate);
		m_cbBitCtrol.SetCurSel( m_pEncPrty->property.video.ucBitrateType);
		m_cbIFrame.SetCurSel( m_pEncPrty->property.video.ucKeyFrameInterval/10 -1 );
	}
}

int CStreamParamDlg::GetParam()
{
	m_pEncPrty->property.video.ucFrameRate = m_cbFrameRate.GetCurSel()+1;
	if (m_emCodecType == MJPEG)
	{
		m_pEncPrty->property.video.ucPicQuality = GetDlgItemInt(IDC_EDIT_QUA);
	}
	else
	{
		SetDlgItemInt(IDC_EDIT_BITRATE, m_pEncPrty->property.video.ucBitRate);
		m_pEncPrty->property.video.ucBitrateType = m_cbBitCtrol.GetCurSel();
		m_pEncPrty->property.video.ucKeyFrameInterval = (m_cbIFrame.GetCurSel()+1)*10;
	}

	return 0;
}