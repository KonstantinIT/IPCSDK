#pragma once


// CLogDlg 对话框
class CHSAGRAccessTestDlg;

class CLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;
	CDateTimeCtrl m_dcStartDate;
	CDateTimeCtrl m_dcStartTime;
	CDateTimeCtrl m_dcEndDate;
	CDateTimeCtrl m_dcEndTime;
	CListCtrl m_clLogInfoList;

public:
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonClear();
};
