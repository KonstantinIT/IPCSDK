#pragma once

#define  TIMBLOCKMAX_NX    32
#define  TIMBLOCKMAX_NY    32

#define  TIMBLOCKMAX_NX_ACT   22
#define  TIMBLOCKMAX_NY_ACT   18

// CMotionDlg 对话框
class CHSAGRAccessTestDlg;
class CRect;
class CEdit;

class CMotionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMotionDlg)

public:
	CMotionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMotionDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MOTION };

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

	CEdit m_etSensiEdit;
	int m_nRealplayId;

	CRect m_PlayRect;

	bool m_bPress;
	CPoint m_ptStartPoint;
	CPoint m_ptEndPoint;

	char m_MBlock[TIMBLOCKMAX_NY_ACT][TIMBLOCKMAX_NX_ACT];
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonSelectAll();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonMtGet();
	afx_msg void OnBnClickedButtonMtSet();
};
