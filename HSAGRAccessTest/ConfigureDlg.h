#pragma once


// CConfigureDlg 对话框
class CHSAGRAccessTestDlg;
class CMotionDlg;

enum WINDOW_TYPE
{
	WINDOW_NULL,
	WINDOW_IMAGE,
	WINDOW_ENCODE,
	WINDOW_MOTION,
	WINDOW_PRIVACY,
	WINDOW_TIME,
	WINDOW_NET,
	WINDOW_USER,
	WINDOW_SERVICE,
	WINDOW_SYSTEM,
	WINDOW_ALL
};
class CConfigureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigureDlg)

public:
	CConfigureDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigureDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_COFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;

	CWnd *m_pSubWindow[WINDOW_ALL];

	CWnd *m_pCurWindow;
	WINDOW_TYPE m_emCurType;

private:
	CWnd *CreatWindows(WINDOW_TYPE windowType);

public:
	afx_msg void OnBnClickedButtonAlarm();
	afx_msg void OnBnClickedButtonPrivacy();
	afx_msg void OnBnClickedButtonImage();
	afx_msg void OnBnClickedButtonEncode();
	afx_msg void OnBnClickedButtonService();
	afx_msg void OnBnClickedButtonTime();
	afx_msg void OnBnClickedButtonNet();
	afx_msg void OnBnClickedButtonUser();
	afx_msg void OnBnClickedButtonSystem();
};
