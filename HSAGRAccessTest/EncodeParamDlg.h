#pragma once
#include <vector>
#include "StreamParamDlg.h"

#define MAX_STREAM 2

// CEncodeParamDlg 对话框
class CHSAGRAccessTestDlg;

class CEncodeParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEncodeParamDlg)

public:
	CEncodeParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEncodeParamDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ENCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	void GetStreamTypeCount();
	void GetCurStreamType();
	void SetCurStreamType();

private:
	CHSAGRAccessTestDlg *m_pParent;

	CComboBox m_cbStreamType;
	int m_nStreamTypeCount;
	int m_nCurStreamType;
	CComboBox m_cbCodec;
	CString m_csCurCodec;
	CTabCtrl m_tcStreamTab;

	CButton m_bnShowTime;
	CComboBox m_cbDateFormat;
	CComboBox m_cbOsdPosi;
	CButton m_bnShowOsdText;
	CEdit m_edOsdText;
	CComboBox m_cbMirro;

	CComboBox m_cbIrcutMode;

	int m_CurSelTab;
	CString m_csTabSelName[MAX_STREAM];
	CString m_csStreamTypeName[MAX_STREAM];
	std::vector<CString> m_vcRelResn[MAX_STREAM];
	CStreamParamDlg m_cParam[MAX_STREAM];
	HS_ENCODING_PROPERTY clientParam[MAX_STREAM];
	int m_nParamCount;

	int m_nMaxFrameRate;
	CString m_csResolution;

	HS_DISPLAY_PROPERTY m_Displayprty;
public:
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnCbnSelchangeComboStreamtype();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnCbnSelchangeComboCodec();
	afx_msg void OnTcnSelchangeTabStream(NMHDR *pNMHDR, LRESULT *pResult);
};
