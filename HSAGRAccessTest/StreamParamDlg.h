#pragma once

enum CODEC_TYPE
{
	NONE,
	H264,
	MJPEG
};

// StreamParamDlg 对话框
struct HS_ENCODING_PROPERTY;

class CStreamParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStreamParamDlg)

public:
	CStreamParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStreamParamDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_STREAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void SetParam(CODEC_TYPE codecType, int maxFrameRate, HS_ENCODING_PROPERTY *encPrty);
	int  GetParam();

private:
	CComboBox m_cbFrameRate;
	CStatic m_scQua;
	CEdit m_etQua;
	CStatic m_scBitRate;
	CEdit m_etBitRate;
	CStatic m_scBitCtrol;
	CComboBox m_cbBitCtrol;
	CStatic m_scIFrame;
	CComboBox m_cbIFrame;

	CODEC_TYPE m_emCodecType;
	int m_nMaxFrameRate;
	HS_ENCODING_PROPERTY *m_pEncPrty;
};
