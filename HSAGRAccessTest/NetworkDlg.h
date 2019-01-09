#pragma once


// CNetworkDlg �Ի���
class CHSAGRAccessTestDlg;

class CNetworkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNetworkDlg)

public:
	CNetworkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNetworkDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_NETWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;

	CButton m_bnDHCPEnable;
	CButton m_bnOnvifAuth;

	HS_NET_PROPERTY m_NetInfo;
	HS_AGREEMENT_PROPERTY m_Onvif;
	HS_AGREEMENT_PROPERTY m_HTTP;

public:
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonSet();
};
