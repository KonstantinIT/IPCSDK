#pragma once


// CLogDlg �Ի���
class CHSAGRAccessTestDlg;

class CLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
