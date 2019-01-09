// ServiceParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "ServiceParamDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CServiceParamDlg 对话框

IMPLEMENT_DYNAMIC(CServiceParamDlg, CDialogEx)

CServiceParamDlg::CServiceParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServiceParamDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg *)pParent;
}

CServiceParamDlg::~CServiceParamDlg()
{
}

void CServiceParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SMTP_ENCRYP, m_cbSmtpEncyp);
	DDX_Control(pDX, IDC_CHECK_DDNS, m_bnDDNSEnable);
	DDX_Control(pDX, IDC_COMBO_DDNS_TYPE, m_cbDDNSType);
	DDX_Control(pDX, IDC_CHECK_ALARM, m_bnAlarmEnable);
	DDX_Control(pDX, IDC_COMBO_ALARM_DUR, m_cbDurTime);
	DDX_Control(pDX, IDC_COMBO_FTP_FORMAT, m_cbFTPFormat);
	DDX_Control(pDX, IDC_COMBO_SMTP_FORMAT, m_cbSMTPFormat);
	DDX_Control(pDX, IDC_CHECK_ALARM_FTP, m_bnFTPUpload);
	DDX_Control(pDX, IDC_CHECK_ALARM_SMTP, m_bnSMTPUpload);
	DDX_Control(pDX, IDC_CHECK_AUDIO, m_bnAudioEnable);
	DDX_Control(pDX, IDC_COMBO_AUDIO_MODEL, m_cbInputModel);
}


BEGIN_MESSAGE_MAP(CServiceParamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CServiceParamDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CServiceParamDlg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CServiceParamDlg 消息处理程序
BOOL CServiceParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//m_cbSmtpEncyp.AddString("None");
	//m_cbSmtpEncyp.AddString("SSL");

	m_cbDDNSType.AddString("Oray");
	m_cbDDNSType.AddString("No-IP");
	m_cbDDNSType.AddString("Dyp");

	m_cbDurTime.AddString("10 sec");
	m_cbDurTime.AddString("30 sec");
	m_cbDurTime.AddString("1 min");
	m_cbDurTime.AddString("5 min");
	m_cbDurTime.AddString("10 min");
	m_cbDurTime.AddString("No-stop");

	m_cbInputModel.AddString("Mic in");

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CServiceParamDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	memset(&m_SmtpPrty, 0, sizeof(HS_SMTP_PROPERTY));
	if(HS_NET_GetSmtp(m_pParent->m_nLoginID, &m_SmtpPrty) != 0)
	{
		MessageBox("HS_NET_GetSmtp failed!");
		return;
	}

	SetDlgItemText(IDC_EDIT_SMTP_USER, (char*)m_SmtpPrty.ucUserName);
	SetDlgItemText(IDC_EDIT_SMPT_PASS, (char*)m_SmtpPrty.ucPasswd);
	((CButton*)GetDlgItem(IDC_CHECK_SMTP_ENCRYP))->SetCheck(m_SmtpPrty.ulEncryptionType);
	SetDlgItemText(IDC_EDIT_SMTP_SENDER, (char*)m_SmtpPrty.ucSenderAddr);
	SetDlgItemInt(IDC_EDIT_SMTP_PORT, m_SmtpPrty.ulPort);
	SetDlgItemText(IDC_EDIT_SMTP_SERVER, (char*)m_SmtpPrty.ucServerAddr);
	SetDlgItemText(IDC_EDIT_EMAIL, (char*)m_SmtpPrty.ucRecverAddr1);

	memset(&m_FtpPrty, 0, sizeof(HS_FTP_PROPERTY));
	if (HS_NET_GetFtp(m_pParent->m_nLoginID, &m_FtpPrty) != 0)
	{
		MessageBox("HS_NET_GetFtp failed!");
		return;
	}

	SetDlgItemText(IDC_EDIT_FTP_SERVER, (char*)m_FtpPrty.ucServerAddr);
	SetDlgItemInt(IDC_EDIT_FTP_PORT, m_FtpPrty.ulPort);
	SetDlgItemText(IDC_EDIT_FTP_USER, (char*)m_FtpPrty.ucUserName);
	SetDlgItemText(IDC_EDIT_FTP_PASS, (char*)m_FtpPrty.ucPasswd);
	SetDlgItemText(IDC_EDIT_FTP_PATH, (char*)m_FtpPrty.ucPath);

	memset(&m_DdnsPrty, 0, sizeof(HS_DDNSSERVER_PROPERTY));
	if (HS_NET_GetDDNS(m_pParent->m_nLoginID, &m_DdnsPrty) != 0)
	{
		MessageBox("HS_NET_GetDDNS failed!");
		return;
	}

	m_bnDDNSEnable.SetCheck(m_DdnsPrty.ucEnable);
	m_cbDDNSType.SetCurSel(m_DdnsPrty.ucServerType);
	SetDlgItemText(IDC_EDIT_DDNS_DOMAIN, (char*)m_DdnsPrty.ucDomainName);
	SetDlgItemText(IDC_EDIT_DDNS_ACCOUNT, (char*)m_DdnsPrty.ucUserName);
	SetDlgItemText(IDC_EDIT_DDNS_PASS, (char*)m_DdnsPrty.ucPasswd);

	memset(&m_AlarmScope, 0, sizeof(HS_ALARM_SCOPE_V2));
	if(HS_NET_GetAlarmScopeV2(m_pParent->m_nLoginID, &m_AlarmScope) != 0)
	{
		MessageBox("HS_NET_GetAlarmScopeV2 failed!");
		return;
	}

	m_cbFTPFormat.ResetContent();
	m_cbSMTPFormat.ResetContent();

	if (m_AlarmScope.ucFtpActionScope & HS_ACTION_AVI)
	{
		m_cbFTPFormat.AddString("AVI");
	}
	
	if (m_AlarmScope.ucFtpActionScope & HS_ACTION_JPEG)
	{
		m_cbFTPFormat.AddString("JPEG");
	}
	
	if (m_AlarmScope.ucFtpActionScope & HS_ACTION_MESSAGE)
	{
		m_cbFTPFormat.AddString("MESSAGE");
	}

	if (m_AlarmScope.ucSmtpActionScope & HS_ACTION_AVI)
	{
		m_cbSMTPFormat.AddString("AVI");
	}
	
	if (m_AlarmScope.ucSmtpActionScope & HS_ACTION_JPEG)
	{
		m_cbSMTPFormat.AddString("JPEG");
	}
	
	if (m_AlarmScope.ucSmtpActionScope & HS_ACTION_MESSAGE)
	{
		m_cbSMTPFormat.AddString("MESSAGE");
	}

	memset(&m_AlarmPrty, 0, sizeof(HS_ALARM_PROPERTY_V2));
	if(HS_NET_GetAlarmPropertyV2(m_pParent->m_nLoginID, &m_AlarmPrty) != 0)
	{
		MessageBox("HS_NET_GetAlarmPropertyV2 failed!");
		return;
	}

	m_bnAlarmEnable.SetCheck(m_AlarmPrty.ucEnable);
	m_cbDurTime.SetCurSel(m_AlarmPrty.ucDuration);
	m_bnFTPUpload.SetCheck(m_AlarmPrty.ucFtpActionEnable);
	m_bnSMTPUpload.SetCheck(m_AlarmPrty.ucSmtpActionEnable);
	if (m_AlarmPrty.ucFtpActionType == HS_ACTION_AVI)
	{
		m_cbFTPFormat.SelectString(-1, "AVI");
	}
	else if (m_AlarmPrty.ucFtpActionType == HS_ACTION_JPEG)
	{
		m_cbFTPFormat.SelectString(-1, "JPEG");
	}
	else if (m_AlarmPrty.ucFtpActionType == HS_ACTION_MESSAGE)
	{
		m_cbFTPFormat.SelectString(-1, "MESSAGE");
	}

	if (m_AlarmPrty.ucSmtpActionType == HS_ACTION_AVI)
	{
		m_cbSMTPFormat.SelectString(-1, "AVI");
	}
	else if (m_AlarmPrty.ucSmtpActionType == HS_ACTION_JPEG)
	{
		m_cbSMTPFormat.SelectString(-1, "JPEG");
	}
	else if (m_AlarmPrty.ucSmtpActionType == HS_ACTION_MESSAGE)
	{
		m_cbSMTPFormat.SelectString(-1, "MESSAGE");
	}

	memset(&m_AudioPrty, 0, sizeof(HS_AUDIO_PROPERTY));
	if(HS_NET_GetAudio(m_pParent->m_nLoginID, &m_AudioPrty) != 0)
	{
		MessageBox("HS_NET_GetAudio failed!");
		return;
	}

	m_bnAlarmEnable.SetCheck(m_AudioPrty.ucEnable);
	m_cbInputModel.SetCurSel(m_AudioPrty.ucInputModel);
	SetDlgItemInt(IDC_EDIT_AUDIO_VOL, m_AudioPrty.ucInputVolume);
}


void CServiceParamDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp;
	GetDlgItemText(IDC_EDIT_SMTP_USER, temp);
	strncpy((char*)m_SmtpPrty.ucUserName, temp, 64);
	GetDlgItemText(IDC_EDIT_SMPT_PASS, temp);
	strncpy((char*)m_SmtpPrty.ucPasswd, temp, 64);
	m_SmtpPrty.ulEncryptionType = ((CButton*)GetDlgItem(IDC_CHECK_SMTP_ENCRYP))->GetCheck();
	GetDlgItemText(IDC_EDIT_SMTP_SENDER, temp);
	strncpy((char*)m_SmtpPrty.ucSenderAddr, temp, 200);
	m_SmtpPrty.ulPort = GetDlgItemInt(IDC_EDIT_SMTP_PORT);
	GetDlgItemText(IDC_EDIT_SMTP_SERVER, temp);
	strncpy((char*)m_SmtpPrty.ucServerAddr, temp, 200);
	GetDlgItemText(IDC_EDIT_EMAIL, temp);
	strncpy((char*)m_SmtpPrty.ucRecverAddr1, temp, 200);

	if(HS_NET_SetSmtp(m_pParent->m_nLoginID, &m_SmtpPrty) != 0)
	{
		MessageBox("HS_NET_SetSmtp failed!");
		return;
	}

	//
	GetDlgItemText(IDC_EDIT_FTP_SERVER, temp);
	strncpy((char*)m_FtpPrty.ucServerAddr, temp, 200);
	m_FtpPrty.ulPort = GetDlgItemInt(IDC_EDIT_FTP_PORT);
	GetDlgItemText(IDC_EDIT_FTP_USER, temp);
	strncpy((char*)m_FtpPrty.ucUserName, temp, 32);
	GetDlgItemText(IDC_EDIT_FTP_PASS, temp);
	strncpy((char*)m_FtpPrty.ucPasswd, temp, 32);
	GetDlgItemText(IDC_EDIT_FTP_PATH, temp);
	strncpy((char*)m_FtpPrty.ucPath, temp, 200);

	if (HS_NET_SetFtp(m_pParent->m_nLoginID, &m_FtpPrty) != 0)
	{
		MessageBox("HS_NET_SetFtp failed!");
		return;
	}

	//
	m_DdnsPrty.ucEnable = m_bnDDNSEnable.GetCheck();
	m_DdnsPrty.ucServerType = m_cbDDNSType.GetCurSel();
	GetDlgItemText(IDC_EDIT_DDNS_DOMAIN, temp);
	strncpy((char*)m_DdnsPrty.ucDomainName, temp, 32);
	GetDlgItemText(IDC_EDIT_DDNS_ACCOUNT, temp);
	strncpy((char*)m_DdnsPrty.ucDomainName, temp, 32);
	GetDlgItemText(IDC_EDIT_DDNS_PASS, temp);
	strncpy((char*)m_DdnsPrty.ucDomainName, temp, 32);
	
	if (HS_NET_SetDDNS(m_pParent->m_nLoginID, &m_DdnsPrty) != 0)
	{
		MessageBox("HS_NET_SetDDNS failed!");
		return;
	}

	//
	m_AlarmPrty.ucEnable = m_bnAlarmEnable.GetCheck();
	m_AlarmPrty.ucDuration = m_cbDurTime.GetCurSel();
	m_AlarmPrty.ucFtpActionEnable = m_bnFTPUpload.GetCheck();
	m_AlarmPrty.ucSmtpActionEnable = m_bnSMTPUpload.GetCheck();

	int nCurSel = m_cbFTPFormat.GetCurSel();
	m_cbFTPFormat.GetLBText(nCurSel, temp);
	if (temp.Compare("AVI") == 0)
	{
		m_AlarmPrty.ucFtpActionType = HS_ACTION_AVI;
	}
	else if (temp.Compare("JPEG") == 0)
	{
		m_AlarmPrty.ucFtpActionType = HS_ACTION_JPEG;
	}
	else if (temp.Compare("MESSAGE") == 0)
	{
		m_AlarmPrty.ucFtpActionType = HS_ACTION_MESSAGE;
	}
	
	nCurSel = m_cbSMTPFormat.GetCurSel();
	m_cbSMTPFormat.GetLBText(nCurSel, temp);
	if (temp.Compare("AVI") == 0)
	{
		m_AlarmPrty.ucSmtpActionType = HS_ACTION_AVI;
	}
	else if (temp.Compare("JPEG") == 0)
	{
		m_AlarmPrty.ucSmtpActionType = HS_ACTION_JPEG;
	}
	else if (temp.Compare("MESSAGE") == 0)
	{
		m_AlarmPrty.ucSmtpActionType = HS_ACTION_MESSAGE;
	}
	
	if(HS_NET_SetAlarmPropertyV2(m_pParent->m_nLoginID, &m_AlarmPrty) != 0)
	{
		MessageBox("HS_NET_SetAlarmPropertyV2 failed!");
		return;
	}
	
	//
	m_AudioPrty.ucEnable = m_bnAlarmEnable.GetCheck();
	m_AudioPrty.ucInputModel = m_cbInputModel.GetCurSel();
	m_AudioPrty.ucInputVolume = GetDlgItemInt(IDC_EDIT_AUDIO_VOL);
	
	if(HS_NET_SetAudio(m_pParent->m_nLoginID, &m_AudioPrty) != 0)
	{
		MessageBox("HS_NET_SetAudio failed!");
		return;
	}
}
