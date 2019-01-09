
// HSAGRAccessTestDlg.h : 头文件
//

#pragma once


#define WM_MSG_RECORD_BEGIN (WM_USER + MSG_RECORD_BEGIN)
#define WM_MSG_RECORD_WRITE_ERROR  (WM_USER + MSG_RECORD_WRITE_ERROR)
#define WM_MSG_RECORD_PACKET_FINISH  (WM_USER + MSG_RECORD_PACKET_FINISH)
#define WM_MSG_RECORD_BEGIN_ANOTHER  (WM_USER + MSG_RECORD_BEGIN_ANOTHER)
#define WM_MSG_RECORD_WRITE_ERROR_ANOTHER  (WM_USER + MSG_RECORD_WRITE_ERROR_ANOTHER)
#define WM_MSG_RECORD_PACKET_FINISH_ANOTHER  (WM_USER + MSG_RECORD_PACKET_FINISH_ANOTHER)
#define WM_MSG_MOTION_DETECT  (WM_USER + MSG_MOTION_DETECT)
#define WM_MSG_UPGRADE_POS  (WM_USER + MSG_UPGRADE_POS)
#define WM_MSG_UPGRADE_OK  (WM_USER + MSG_UPGRADE_OK)
#define WM_MSG_UPGRADE_FAILED  (WM_USER + MSG_UPGRADE_FAILED)

class CPreviewDlg;
class CConfigureDlg;

// CHSAGRAccessTestDlg 对话框
class CHSAGRAccessTestDlg : public CDialogEx
{
// 构造
public:
	CHSAGRAccessTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HSAGRACCESSTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CString GetExePath();
	void GetParam();

	static void CALLBACK NetMessageCallBack(int nLoginId, long msgType, void *pMsgData, void *pUser);

    static void CALLBACK SearchDeviceCallback(long msgType/*HS_SEARCH_TYPE*/, void *pMsgData/*HS_STREAM_INFO*/, void *pUser);

public:
	CString  m_strExePath;
	CString m_UserName;
	CString m_Password;

	CComboBox m_cbDevType;
	CEdit m_edCH;

	CPreviewDlg *m_pPreviewDlg;
	CConfigureDlg *m_pConfigureDlg;
	HS_CLIENTINFO m_channelInfo;
	int m_nLoginID;

    std::list<HS_SEARCH_INFO> mlist;

public:
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLog();
	afx_msg void OnBnClickedButtonPreview();
	afx_msg void OnBnClickedButtonConfig();
    afx_msg void OnBnClickedButtonStartSearchdevice();
    afx_msg void OnBnClickedButton1();
};
