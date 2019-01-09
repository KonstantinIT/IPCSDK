#pragma once


// CImageParamDlg 对话框
class CHSAGRAccessTestDlg;

class CImageParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageParamDlg)

public:
	CImageParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CImageParamDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CComboBox m_cbWihteBal;
	CComboBox m_cbBLCStrength;
	CComboBox m_cbFCModel;
	CComboBox m_cbWDLevel;
	CComboBox m_cbDNRModel;
	CComboBox m_cbDefogModel;

	CButton m_bnBLCEnable;
	CButton m_bnExposureCtrl;
	CButton m_bnWideDyn;	
	CButton m_bnFlickerCtrl;
	CButton m_bnSLInhibition;

private:
	CHSAGRAccessTestDlg *m_pParent;
	int m_nRealplayId;

	HS_IMAGE_PROPERTY m_Imageprty;
public:
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonSet();
};
