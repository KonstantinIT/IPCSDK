// ImageParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "ImageParamDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"


// CImageParamDlg 对话框

IMPLEMENT_DYNAMIC(CImageParamDlg, CDialogEx)

CImageParamDlg::CImageParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageParamDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg *)pParent;
	m_nRealplayId = -1;
}

CImageParamDlg::~CImageParamDlg()
{
	HS_NET_RealPlayStop(m_nRealplayId);
}

void CImageParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WBALA, m_cbWihteBal);
	DDX_Control(pDX, IDC_CHECK_BLC, m_bnBLCEnable);
	DDX_Control(pDX, IDC_COMBO_BLC_STREN, m_cbBLCStrength);
	DDX_Control(pDX, IDC_CHECK_EXC, m_bnExposureCtrl);
	DDX_Control(pDX, IDC_CHECK_WD, m_bnWideDyn);
	DDX_Control(pDX, IDC_COMBO_WDLEVEL, m_cbWDLevel);
	DDX_Control(pDX, IDC_CHECK_FC, m_bnFlickerCtrl);
	DDX_Control(pDX, IDC_COMBO_FCMODEL, m_cbFCModel);
	DDX_Control(pDX, IDC_COMBO_DNRMODEL, m_cbDNRModel);
	DDX_Control(pDX, IDC_COMBO_DFMODEL, m_cbDefogModel);
	DDX_Control(pDX, IDC_CHECK_SL, m_bnSLInhibition);
}


BEGIN_MESSAGE_MAP(CImageParamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CImageParamDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CImageParamDlg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CImageParamDlg 消息处理程序
BOOL CImageParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_cbWihteBal.AddString("Auto");
	m_cbWihteBal.AddString("Manu");

	m_cbBLCStrength.AddString("Min");
	m_cbBLCStrength.AddString("Mid");
	m_cbBLCStrength.AddString("Max");

	m_cbFCModel.AddString("Indoor NTSC");
	m_cbFCModel.AddString("Indoor PAL");
	m_cbFCModel.AddString("Outdoor");

	m_cbWDLevel.AddString("Close");
	m_cbWDLevel.AddString("Auto");
	m_cbWDLevel.AddString("Weak");
	m_cbWDLevel.AddString("Medium");
	m_cbWDLevel.AddString("Strength");
	m_cbWDLevel.AddString("Super");

	m_cbDNRModel.AddString("Both Auto");
	m_cbDNRModel.AddString("2D Manual");
	m_cbDNRModel.AddString("3D Manual");
	m_cbDNRModel.AddString("Both manual");

	m_cbDefogModel.AddString("Close");
	m_cbDefogModel.AddString("Open");
	m_cbDefogModel.AddString("Auto");

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageParamDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_nRealplayId == -1)
	{
		m_pParent->m_channelInfo.hwnd = GetDlgItem(IDC_STATIC_IMAGE)->m_hWnd;
		m_nRealplayId = HS_NET_RealPlayStart(m_pParent->m_nLoginID, &m_pParent->m_channelInfo, NULL, NULL);
		if (m_nRealplayId == -1)
		{
			MessageBox("Play failed!");
			return;
		}
	}

	memset(&m_Imageprty, 0, sizeof(HS_IMAGE_PROPERTY));
	if(HS_NET_GetImageProperty(m_pParent->m_nLoginID, &m_Imageprty) != 0)
	{
		MessageBox("HS_NET_GetImageProperty failed!");
		return;
	}

	SetDlgItemInt(IDC_EDIT_BRIGHTNESS, m_Imageprty.ucBrightness);
	SetDlgItemInt(IDC_EDIT_CONTRAST, m_Imageprty.ucContrast);
	SetDlgItemInt(IDC_EDIT_SATURATION, m_Imageprty.ucSaturation);
	SetDlgItemInt(IDC_EDIT_HUE, m_Imageprty.ucHue);

	m_cbWihteBal.SetCurSel(m_Imageprty.ucWhiteBalance);
	SetDlgItemInt(IDC_EDIT_RCTRL, m_Imageprty.ucGainRCtrl);
	SetDlgItemInt(IDC_EDIT_GCTRL, m_Imageprty.ucGainGCtrl);
	SetDlgItemInt(IDC_EDIT_BCTRL, m_Imageprty.ucGainBCtrl);

	m_bnBLCEnable.SetCheck(m_Imageprty.ucBLCEable);
	m_cbBLCStrength.SetCurSel(m_Imageprty.ucBLCStrength);
	SetDlgItemInt(IDC_EDIT_GAINCTROL, m_Imageprty.ucGainCtrl);
	m_bnExposureCtrl.SetCheck(m_Imageprty.ucExposureCtrl);

	//m_bnWideDyn.SetCheck(m_Imageprty.ucWideDynamicEnable);
	m_cbWDLevel.SetCurSel(m_Imageprty.ucWideDynamicLevel);
	//m_bnFlickerCtrl.SetCheck(m_Imageprty.ucFlickerCtrlEnable);
	m_cbFCModel.SetCurSel(m_Imageprty.ucFlickerCtrlModel);

	m_cbDNRModel.SetCurSel(m_Imageprty.ucDNRModel);
	SetDlgItemInt(IDC_EDIT_2D, m_Imageprty.ucDNR2DStrength);
	SetDlgItemInt(IDC_EDIT_3D, m_Imageprty.ucDNR3DStrength);

	m_cbDefogModel.SetCurSel(m_Imageprty.ucDefogEnable);
	SetDlgItemInt(IDC_EDIT_DFSTREN, m_Imageprty.ucDefogStrength);
	m_bnSLInhibition.SetCheck(m_Imageprty.ucSLInhibition);
	SetDlgItemInt(IDC_EDIT_SLSTREN, m_Imageprty.ucSLInhibitionStreangth);

}


void CImageParamDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Imageprty.ucBrightness = GetDlgItemInt(IDC_EDIT_BRIGHTNESS);
	m_Imageprty.ucContrast = GetDlgItemInt(IDC_EDIT_CONTRAST);
	m_Imageprty.ucSaturation = GetDlgItemInt(IDC_EDIT_SATURATION);
	m_Imageprty.ucHue = GetDlgItemInt(IDC_EDIT_HUE);

	m_Imageprty.ucWhiteBalance = m_cbWihteBal.GetCurSel();
	m_Imageprty.ucGainRCtrl = GetDlgItemInt(IDC_EDIT_RCTRL);
	m_Imageprty.ucGainGCtrl = GetDlgItemInt(IDC_EDIT_GCTRL);
	m_Imageprty.ucGainBCtrl = GetDlgItemInt(IDC_EDIT_BCTRL);

	m_Imageprty.ucBLCEable = m_bnBLCEnable.GetCheck();
	m_Imageprty.ucBLCStrength = m_cbBLCStrength.GetCurSel();
	m_Imageprty.ucGainCtrl = GetDlgItemInt(IDC_EDIT_GAINCTROL);
	m_Imageprty.ucExposureCtrl = m_bnExposureCtrl.GetCheck();

	//m_Imageprty.ucWideDynamicEnable = m_bnWideDyn.GetCheck();
	m_Imageprty.ucWideDynamicLevel = m_cbWDLevel.GetCurSel();
	//m_Imageprty.ucFlickerCtrlEnable = m_bnFlickerCtrl.GetCheck();
	m_Imageprty.ucFlickerCtrlModel = m_cbFCModel.GetCurSel();

	m_Imageprty.ucDNRModel = m_cbDNRModel.GetCurSel();
	m_Imageprty.ucDNR2DStrength = GetDlgItemInt(IDC_EDIT_2D);
	m_Imageprty.ucDNR3DStrength = GetDlgItemInt(IDC_EDIT_3D);

	m_Imageprty.ucDefogEnable = m_cbDefogModel.GetCurSel();
	m_Imageprty.ucDefogStrength = GetDlgItemInt(IDC_EDIT_DFSTREN);
	m_Imageprty.ucSLInhibition = m_bnSLInhibition.GetCheck();
	m_Imageprty.ucSLInhibitionStreangth = GetDlgItemInt(IDC_EDIT_SLSTREN);

	if(HS_NET_SetImageProperty(m_pParent->m_nLoginID, &m_Imageprty) != 0)
	{
		MessageBox("HS_NET_SetImageProperty failed!");
	}
}
