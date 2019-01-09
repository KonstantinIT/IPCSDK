#pragma once


// CImageParamDlg �Ի���
class CHSAGRAccessTestDlg;

class CImageParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageParamDlg)

public:
	CImageParamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CImageParamDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
