#pragma once

enum TIME_MODEL
{
	MANNU,
	COMPU,
	NTP
};
// CTimeParamDlg �Ի���
class CHSAGRAccessTestDlg;

class CTimeParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeParamDlg)

public:
	CTimeParamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTimeParamDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CHSAGRAccessTestDlg *m_pParent;

	CComboBox m_cbTimeZone;
	CComboBox m_cbSntpServer;
	CDateTimeCtrl m_dtManuDate;
	CDateTimeCtrl m_dtManuTime;

	HS_TIME_INFO m_TimeInfo;
	UINT_PTR m_Timer;

	CTime m_tiGetTime;
	TIME_MODEL m_emTimeModel;
private:
	void CheckRadioState();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedRadioManu();
	afx_msg void OnBnClickedRadioCompu();
	afx_msg void OnBnClickedRadioSntp();
};
