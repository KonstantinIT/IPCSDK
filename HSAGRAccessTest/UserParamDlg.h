#pragma once


// CUserParamDlg �Ի���
class CHSAGRAccessTestDlg;

class CUserParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserParamDlg)

public:
	CUserParamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserParamDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;

	CComboBox m_cbRole;
	CListCtrl m_lcUsrList;

	HS_USER_INFOR *m_pUserInfo;
	int m_nUserCount;
	CString m_csRoleName[3];
public:
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnHdnItemclickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);
};
