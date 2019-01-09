#pragma once


// CServiceParamDlg 对话框
class CHSAGRAccessTestDlg;

class CServiceParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServiceParamDlg)

public:
	CServiceParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServiceParamDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SERVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;

	CComboBox m_cbSmtpEncyp;
	CComboBox m_cbDDNSType;
	CButton m_bnDDNSEnable;
	CButton m_bnAlarmEnable;
	CComboBox m_cbDurTime;
	CButton m_bnFTPUpload;
	CButton m_bnSMTPUpload;
	CComboBox m_cbFTPFormat;
	CComboBox m_cbSMTPFormat;
	CButton m_bnAudioEnable;
	CComboBox m_cbInputModel;

	HS_SMTP_PROPERTY m_SmtpPrty;
	HS_FTP_PROPERTY m_FtpPrty;
	HS_DDNSSERVER_PROPERTY m_DdnsPrty;
	HS_ALARM_SCOPE_V2 m_AlarmScope;
	HS_ALARM_PROPERTY_V2 m_AlarmPrty;
	HS_AUDIO_PROPERTY m_AudioPrty;

public:
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonSet();
};
