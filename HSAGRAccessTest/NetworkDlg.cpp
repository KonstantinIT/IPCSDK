// NetworkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "NetworkDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CNetworkDlg 对话框

IMPLEMENT_DYNAMIC(CNetworkDlg, CDialogEx)

CNetworkDlg::CNetworkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNetworkDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg *)pParent;
}

CNetworkDlg::~CNetworkDlg()
{
}

void CNetworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_DHCP, m_bnDHCPEnable);
	DDX_Control(pDX, IDC_CHECK_AUTH, m_bnOnvifAuth);
}


BEGIN_MESSAGE_MAP(CNetworkDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CNetworkDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CNetworkDlg::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CNetworkDlg 消息处理程序
BOOL CNetworkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CNetworkDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	memset(&m_NetInfo, 0, sizeof(HS_NET_PROPERTY));
	if(HS_NET_GetNetParam(m_pParent->m_nLoginID, &m_NetInfo) != 0)
	{
		MessageBox("HS_NET_GetNetParam failed!");
		return;
	}

	m_bnDHCPEnable.SetCheck(m_NetInfo.ucEnDHCP);
	SetDlgItemText(IDC_EDIT_IP, (char*)m_NetInfo.ucIP);
	SetDlgItemText(IDC_EDIT_MASK, (char*)m_NetInfo.ucSubNetMask);
	SetDlgItemText(IDC_EDIT_GATEWAY, (char*)m_NetInfo.ucGateway);
	SetDlgItemText(IDC_EDIT_DNS, (char*)m_NetInfo.ucDNS1Ip);
	
	int nCount;
	if(HS_NET_GetAgreementProperty(m_pParent->m_nLoginID, HS_AGREEMENT_ONVIF, &m_Onvif, 1, &nCount) != 0 ||
		HS_NET_GetAgreementProperty(m_pParent->m_nLoginID, HS_AGREEMENT_HTTP, &m_HTTP, 1, &nCount) != 0 )
	{
		MessageBox("HS_NET_GetAgreementProperty failed!");
		return;
	}
	
	m_bnOnvifAuth.SetCheck(m_Onvif.property.onvifPro.ucAuthentication);
	SetDlgItemInt(IDC_EDIT_HTTPPORT, m_HTTP.property.httpPro.usPort);

}

void CNetworkDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码

	m_NetInfo.ucEnDHCP = m_bnDHCPEnable.GetCheck();
	CString temp;
	GetDlgItemText(IDC_EDIT_IP, temp);
	strncpy((char*)m_NetInfo.ucIP, temp, MAX_IPSTR_LEN);
	GetDlgItemText(IDC_EDIT_MASK, temp);
	strncpy((char*)m_NetInfo.ucSubNetMask, temp, MAX_IPSTR_LEN);
	GetDlgItemText(IDC_EDIT_GATEWAY, temp);
	strncpy((char*)m_NetInfo.ucGateway, temp, MAX_IPSTR_LEN);
	GetDlgItemText(IDC_EDIT_DNS, temp);
	strncpy((char*)m_NetInfo.ucDNS1Ip, temp, MAX_IPSTR_LEN);

	if(HS_NET_SetNetParam(m_pParent->m_nLoginID, &m_NetInfo) != 0)
	{
		MessageBox("HS_NET_GetNetParam failed!");
		return;
	}

	m_Onvif.property.onvifPro.ucAuthentication = m_bnOnvifAuth.GetCheck();
	m_HTTP.property.httpPro.usPort = GetDlgItemInt(IDC_EDIT_HTTPPORT);

	int nCount;
	if(HS_NET_SetAgreementProperty(m_pParent->m_nLoginID, &m_Onvif, 1) != 0 ||
		HS_NET_SetAgreementProperty(m_pParent->m_nLoginID, &m_HTTP, 1) != 0 )
	{
		MessageBox("HS_NET_GetAgreementProperty failed!");
		return;
	}
}
