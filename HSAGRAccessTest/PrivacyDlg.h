#pragma once

#define MAX_PRIVACY_REGION 3

// CPrivacyDlg 对话框
class CHSAGRAccessTestDlg;
class CRect;

class CPrivacyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrivacyDlg)

public:
	CPrivacyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPrivacyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PRIVACY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	static void CALLBACK DrawCallbackFun( int nRealPlayId, HDC hDC, void *lpContext );

	int StartRealPlay();
	void StopRealPlay();

private:
	CHSAGRAccessTestDlg *m_pParent;

	int m_nRealplayId;
	CRect m_PlayRect;
	CStatic m_PlayStatic;
	bool m_bPress;

	CRect m_PrivacyRegion[MAX_PRIVACY_REGION];
	int m_nIndex;

	CPoint m_ptStartPoint;
	CPoint m_ptEndPoint;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonSet();
};
