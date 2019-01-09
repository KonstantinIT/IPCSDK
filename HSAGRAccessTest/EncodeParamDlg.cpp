// EncodeParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "EncodeParamDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CEncodeParamDlg 对话框

IMPLEMENT_DYNAMIC(CEncodeParamDlg, CDialogEx)

CEncodeParamDlg::CEncodeParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncodeParamDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg*)pParent;
	m_CurSelTab = 0; 
}

CEncodeParamDlg::~CEncodeParamDlg()
{
}

void CEncodeParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_cbStreamType);
	DDX_Control(pDX, IDC_COMBO_CODEC, m_cbCodec);
	DDX_Control(pDX, IDC_TAB_STREAM, m_tcStreamTab);
	DDX_Control(pDX, IDC_CHECK_TIME, m_bnShowTime);
	DDX_Control(pDX, IDC_COMBO_DATEFORMAT, m_cbDateFormat);
	DDX_Control(pDX, IDC_COMBO_OSDPOSITION, m_cbOsdPosi);
	DDX_Control(pDX, IDC_CHECK_OSD, m_bnShowOsdText);
	DDX_Control(pDX, IDC_EDIT_OSD_TEXT, m_edOsdText);
	DDX_Control(pDX, IDC_COMBO_MIRRO, m_cbMirro);
	DDX_Control(pDX, IDC_COMBO_IRCUTMODE, m_cbIrcutMode);
}


BEGIN_MESSAGE_MAP(CEncodeParamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CEncodeParamDlg::OnBnClickedButtonGet)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAMTYPE, &CEncodeParamDlg::OnCbnSelchangeComboStreamtype)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CEncodeParamDlg::OnBnClickedButtonSet)
	ON_CBN_SELCHANGE(IDC_COMBO_CODEC, &CEncodeParamDlg::OnCbnSelchangeComboCodec)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_STREAM, &CEncodeParamDlg::OnTcnSelchangeTabStream)
END_MESSAGE_MAP()


// CEncodeParamDlg 消息处理程序
BOOL CEncodeParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//为Tab Control增加两个页面
	m_tcStreamTab.InsertItem(0, _T("stream1"));
	m_tcStreamTab.InsertItem(1, _T("stream2"));
	//m_tcStreamTab.InsertItem(2, _T("stream3"));

	//创建对话框
	m_cParam[0].Create(IDD_DIALOG_STREAM, &m_tcStreamTab);
	m_cParam[1].Create(IDD_DIALOG_STREAM, &m_tcStreamTab);
	//m_cParam[2].Create(IDD_DIALOG_STREAM, &m_tcStreamTab);

	//设定在Tab内显示的范围
	CRect rc;
	m_tcStreamTab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_cParam[0].MoveWindow(&rc);
	m_cParam[1].MoveWindow(&rc);
	//m_cParam[2].MoveWindow(&rc);

	//显示初始页面
	m_cParam[0].ShowWindow(SW_SHOW);
	m_cParam[1].ShowWindow(SW_HIDE);
	//m_cParam[2].ShowWindow(SW_HIDE);

	//保存当前选择
	m_CurSelTab = 0;

	m_csTabSelName[0] = "stream1";
	m_csTabSelName[1] = "stream2";
	//m_csTabSelName[2] = "stream3";

	m_csStreamTypeName[0] = "Single";
	m_csStreamTypeName[1] = "Dual";
	//m_csStreamTypeName[2] = "Tri-Stream";

	m_cbDateFormat.AddString("YYYY/MM/DD");
	m_cbDateFormat.AddString("MM/DD/YYYY");
	m_cbDateFormat.AddString("DD/MM/YYYY");

	m_cbOsdPosi.AddString("Top_left");
	m_cbOsdPosi.AddString("Bottom_left");

	m_cbMirro.AddString("OFF");
	m_cbMirro.AddString("HORIZONTAL");
	m_cbMirro.AddString("VERTICAL");
	m_cbMirro.AddString("BOTH");

	m_cbIrcutMode.AddString("LDR Auto");
	m_cbIrcutMode.AddString("Video Auto");
	m_cbIrcutMode.AddString("Color");
	m_cbIrcutMode.AddString("B/W");

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CEncodeParamDlg::GetStreamTypeCount()
{
	//字符串拆分码流类型
	CString subResn[MAX_STREAM];
	m_nStreamTypeCount = 0;
	CString temp = m_csResolution + "@";
	while(temp.Find('@') != -1 && m_nStreamTypeCount < MAX_STREAM)
	{
		int posi = temp.Find('@');
		subResn[m_nStreamTypeCount] = temp.Left(posi);
		int len = temp.GetLength();
		temp = temp.Right(len - posi - 1);
		m_nStreamTypeCount++;
	}

	//字符串拆分分辨率
	for (int i = 0; i < m_nStreamTypeCount; ++i)
	{
		temp = subResn[i]+";";
		while(temp.Find(';') != -1)
		{
			int posi = temp.Find(';');
			m_vcRelResn[i].push_back(temp.Left(posi));
			int len = temp.GetLength();
			temp = temp.Right(len - posi - 1);
		}
	}
}

void CEncodeParamDlg::GetCurStreamType()
{
	//构造当前分辨率, 计算码流类型（enable为true的数量）
	CString temp2;
	m_nCurStreamType = 0;
	for (int i = 0; i < m_nParamCount; ++i)
	{
		if (clientParam[i].ucEnable)
		{
			m_nCurStreamType++;

			if (clientParam[i].property.video.ucEncodingType == HS_ENCODING_H264)
			{
				m_csCurCodec += "H264:";
			}
			else if (clientParam[i].property.video.ucEncodingType == HS_ENCODING_H265)
			{
				m_csCurCodec += "H265:";
			}
			else if (clientParam[i].property.video.ucEncodingType == HS_ENCODING_MPEG)
			{
				m_csCurCodec += "MPEG:";
			}
			else if (clientParam[i].property.video.ucEncodingType == HS_ENCODING_JPEG)
			{
				m_csCurCodec += "JPEG:";
			}

			temp2.Format("%dx%d,", clientParam[i].property.video.usWidth, clientParam[i].property.video.usHeight);
			m_csCurCodec += temp2;
		}
	}
	m_csCurCodec = m_csCurCodec.Left(m_csCurCodec.GetLength()-1);
}

void CEncodeParamDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	HS_ENCODING_SCOPE encscope;
	memset(&encscope, 0, sizeof(HS_ENCODING_SCOPE));
	if( HS_NET_GetEncodingScope(m_pParent->m_nLoginID, &encscope) != 0 )
	{
		MessageBox("HS_NET_GetEncodingScope failed!\n");
		return ;
	}

	m_nMaxFrameRate = encscope.ucMaxFrameRate;
	m_csResolution = encscope.ucResolutions;

	GetStreamTypeCount();

	//初始化码流类型选项
	m_cbStreamType.ResetContent();
	for (int i = 0; i < m_nStreamTypeCount; ++i)
	{
		m_cbStreamType.AddString(m_csStreamTypeName[i]);
	}


	if(HS_NET_GetEncodingProperty(m_pParent->m_nLoginID, HS_STREAM_VIDEO_ALL, clientParam, MAX_STREAM, &m_nParamCount) != 0)
	{
		return;
	}

	GetCurStreamType();
	m_cbStreamType.SetCurSel(m_nCurStreamType-1);

	//init codec combox and tab item
	OnCbnSelchangeComboStreamtype();

	int nsize = m_vcRelResn[m_nCurStreamType-1].size();
	for (int i = 0; i < nsize; ++i)
	{
		if(m_vcRelResn[m_nCurStreamType-1][i].Compare(m_csCurCodec) == 0)
		{
			m_cbCodec.SetCurSel(i);
		}
	}

	//init tab item dlg param
	OnCbnSelchangeComboCodec();

	memset(&m_Displayprty, 0, sizeof(HS_DISPLAY_PROPERTY));
	if(HS_NET_GetOSD(m_pParent->m_nLoginID, &m_Displayprty) != 0)
	{
		MessageBox("HS_NET_GetOSD failed!\n");
		return;
	}

	m_bnShowTime.SetCheck(m_Displayprty.ucDateVisiable);
	m_bnShowOsdText.SetCheck(m_Displayprty.ucIPCNameVisiable);
	m_edOsdText.SetWindowText((char*)m_Displayprty.ucOSDText);
	m_cbDateFormat.SetCurSel(m_Displayprty.ucDateFormat);
	m_cbOsdPosi.SetCurSel(m_Displayprty.ucOSDPostion);
	m_cbMirro.SetCurSel(m_Displayprty.ucMirrorMode);
	SetDlgItemInt(IDC_EDIT_IRCUT_SWICTH_TIME, m_Displayprty.ucIRCutSwitchTime);
	m_cbIrcutMode.SetCurSel(m_Displayprty.ucIRCutMode);
}

void CEncodeParamDlg::SetCurStreamType()
{
	int nstreamtype = m_cbStreamType.GetCurSel();
	CString curresn = m_vcRelResn[nstreamtype][m_cbCodec.GetCurSel()];
	curresn += ",";

	CString temp, temp1;
	int i = 0;
	while(curresn.Find(',') != -1)
	{
		clientParam[i].ucEnable = true;

		int posi = curresn.Find(',');
		temp = curresn.Left(posi);
		int len = curresn.GetLength();
		curresn = curresn.Right(len - posi - 1);

		posi = temp.Find(':');
		if (temp.Left(posi) == "H264")
		{
			clientParam[i].property.video.ucEncodingType = HS_ENCODING_H264;
		}
		else if (temp.Left(posi) == "H265")
		{
			clientParam[i].property.video.ucEncodingType = HS_ENCODING_H265;
		}
		else if (temp.Left(posi) == "MPEG")
		{
			clientParam[i].property.video.ucEncodingType = HS_ENCODING_MPEG;
		}
		else if (temp.Left(posi) == "JPEG")
		{
			clientParam[i].property.video.ucEncodingType = HS_ENCODING_JPEG;
		}

		temp1 = temp.Right(temp.GetLength() - posi -1);
		posi = temp1.Find('x');

		clientParam[i].property.video.usWidth = atoi(temp1.Left(posi));
		clientParam[i].property.video.usHeight = atoi(temp1.Right(temp1.GetLength() - posi -1));

		m_cParam[i].GetParam();

		i++;
	}

	for(; i<m_nParamCount;++i)
	{
		clientParam[i].ucEnable = false;
	}
}

void CEncodeParamDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	SetCurStreamType();

	HS_NET_SetEncodingProperty(m_pParent->m_nLoginID, clientParam, m_nParamCount);


	m_Displayprty.ucDateVisiable = m_bnShowTime.GetCheck();
	m_Displayprty.ucIPCNameVisiable = m_bnShowOsdText.GetCheck();
	CString temp;
	m_edOsdText.GetWindowText(temp);
	strncpy((char*)m_Displayprty.ucOSDText, temp, 200);
	m_Displayprty.ucDateFormat = m_cbDateFormat.GetCurSel();
	m_Displayprty.ucOSDPostion = m_cbOsdPosi.GetCurSel();
	m_Displayprty.ucMirrorMode = m_cbMirro.GetCurSel();
	m_Displayprty.ucIRCutSwitchTime = GetDlgItemInt(IDC_EDIT_IRCUT_SWICTH_TIME);
	m_Displayprty.ucIRCutMode = m_cbIrcutMode.GetCurSel();

	HS_NET_SetOSD(m_pParent->m_nLoginID, &m_Displayprty);
}

void CEncodeParamDlg::OnCbnSelchangeComboStreamtype()
{
	// TODO: 在此添加控件通知处理程序代码
	int ntype = m_cbStreamType.GetCurSel();

	m_cbCodec.ResetContent();
	int nsize = m_vcRelResn[ntype].size();
	int i;
	for (i = 0; i < nsize; ++i)
	{
		m_cbCodec.AddString(m_vcRelResn[ntype][i]);
	}
	m_cbCodec.SetCurSel(0);

	CRect rc;
	m_tcStreamTab.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;

	m_tcStreamTab.DeleteAllItems();
	for(i = 0; i<= ntype; ++i)
	{
		//为Tab Control增加页面
		m_tcStreamTab.InsertItem(i, m_csTabSelName[i]);
	}

	//显示初始页面
	m_CurSelTab = 0;
	m_cParam[0].ShowWindow(SW_SHOW);
	m_cParam[1].ShowWindow(SW_HIDE);
	//m_cParam[2].ShowWindow(SW_HIDE);

}

void CEncodeParamDlg::OnCbnSelchangeComboCodec()
{
	// TODO: 在此添加控件通知处理程序代码
	int nstreamtype = m_cbStreamType.GetCurSel();
	int ncodec = m_cbCodec.GetCurSel();
	CString curresn = m_vcRelResn[nstreamtype][ncodec];
	curresn += ",";

	CString temp, temp1;
	int i = 0;
	while(curresn.Find(',') != -1)
	{
		int posi = curresn.Find(',');
		temp = curresn.Left(posi);
		int len = curresn.GetLength();
		curresn = curresn.Right(len - posi - 1);

		posi = temp.Find(':');
		if (temp.Left(posi) == "JPEG")
		{
			m_cParam[i].SetParam(MJPEG, m_nMaxFrameRate, &clientParam[i]);
		}
		else
		{
			m_cParam[i].SetParam(H264, m_nMaxFrameRate, &clientParam[i]);
		}

		i++;
	}
}

void CEncodeParamDlg::OnTcnSelchangeTabStream(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//把当前的页面隐藏起来
	m_cParam[m_CurSelTab].ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = m_tcStreamTab.GetCurSel();
	//把新的页面显示出来
	m_cParam[m_CurSelTab].ShowWindow(SW_SHOW);

	*pResult = 0;
}
