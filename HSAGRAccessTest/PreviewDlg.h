#pragma once


// CPreviewDlg �Ի���
class CHSAGRAccessTestDlg;
#define MAX_WND  4

class CPreviewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPreviewDlg)

public:
	CPreviewDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPreviewDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PREVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;

	int m_nRealplayID[MAX_WND];
	HWND m_hPlayWnd[MAX_WND];
	int m_nCurWnd;

public:
	afx_msg void OnBnClickedButtonPlayStart();
	afx_msg void OnBnClickedButtonPlayStop();
	afx_msg void OnBnClickedButtonCap();
	afx_msg void OnBnClickedButtonRecordStart();
	afx_msg void OnBnClickedButtonRecordStop();
	afx_msg void OnStnClickedStaticWnd1();
	afx_msg void OnStnClickedStaticWnd2();
	afx_msg void OnStnClickedStaticWnd3();
	afx_msg void OnStnClickedStaticWnd4();
};
