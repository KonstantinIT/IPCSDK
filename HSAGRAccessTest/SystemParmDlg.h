#pragma once


// CSystemParmDlg 对话框
class CHSAGRAccessTestDlg;

class CSystemParmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemParmDlg)

public:
	CSystemParmDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemParmDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;

	CComboBox m_cbRebootDate;
	CComboBox m_cbRebootTime;

	HS_SYSREBOOT_PROPERTY m_Sysreboot;
	HS_DEV_INFO m_Devinfo;
	CString m_csUpgradeFile;

public:
	afx_msg void OnBnClickedButtonReboot();
	afx_msg void OnBnClickedButtonRestore();
	afx_msg void OnBnClickedButtonSchedReboot();
	afx_msg void OnBnClickedButtonSchedGet();
	afx_msg void OnBnClickedButtonDeviceinfo();
	afx_msg void OnBnClickedButtonScan();
	afx_msg void OnBnClickedButtonUpgrage();
	afx_msg void OnBnClickedButtonSetDeviceinfo();
};
