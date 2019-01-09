// UserParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HSAGRAccessTest.h"
#include "UserParamDlg.h"
#include "afxdialogex.h"
#include "HSAGRAccessTestDlg.h"

// CUserParamDlg 对话框

IMPLEMENT_DYNAMIC(CUserParamDlg, CDialogEx)

CUserParamDlg::CUserParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserParamDlg::IDD, pParent)
{
	m_pParent = (CHSAGRAccessTestDlg *)pParent;
	m_pUserInfo = NULL;
}

CUserParamDlg::~CUserParamDlg()
{
}

void CUserParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROLE, m_cbRole);
	DDX_Control(pDX, IDC_LIST_USER, m_lcUsrList);
}


BEGIN_MESSAGE_MAP(CUserParamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CUserParamDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CUserParamDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CUserParamDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CUserParamDlg::OnBnClickedButtonEdit)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CUserParamDlg::OnHdnItemclickListUser)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USER, &CUserParamDlg::OnLvnItemchangedListUser)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, &CUserParamDlg::OnNMClickListUser)
END_MESSAGE_MAP()


// CUserParamDlg 消息处理程序
BOOL CUserParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_cbRole.AddString("Admin");
	m_cbRole.AddString("Operater");
	m_cbRole.AddString("Ordinary");
	m_csRoleName[0] = "Admin";
	m_csRoleName[1] = "Operator";
	m_csRoleName[2] = "Viewer";

	m_lcUsrList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lcUsrList.InsertColumn(0, "User Name", LVCFMT_LEFT, 200);
	m_lcUsrList.InsertColumn(1, "Role", LVCFMT_LEFT, 150);

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CUserParamDlg::OnBnClickedButtonGet()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCount = 0;
	if(HS_NET_GetUserInfo(m_pParent->m_nLoginID, NULL, 0, &nCount) == 0)
	{
		if (nCount == 0)
		{
			return;
		}

		if (m_pUserInfo != NULL)
		{
			delete[] m_pUserInfo;
		}
		m_pUserInfo = new HS_USER_INFOR[nCount];
		m_nUserCount = nCount;

		if(HS_NET_GetUserInfo(m_pParent->m_nLoginID, m_pUserInfo, m_nUserCount, &nCount) != 0)
		{
			return;
		}
	}
	else
	{
		return;
	}

	m_lcUsrList.DeleteAllItems();
	for (int i = 0; i < nCount; ++i)
	{
		m_lcUsrList.InsertItem(i, "");
		m_lcUsrList.SetItemText(i, 0, (char*)m_pUserInfo[i].ucUsername);
		m_lcUsrList.SetItemText(i, 1, m_csRoleName[m_pUserInfo[i].ucRole]);
	}
}

void CUserParamDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	HS_USER_INFOR usrInfo;
	memset(&usrInfo, 0, sizeof(HS_USER_INFOR));
	CString temp;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(temp);
	strncpy((char*)usrInfo.ucUsername, temp, 32);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(temp);
	strncpy((char*)usrInfo.ucPassWord, temp, 32);
	usrInfo.ucRole = m_cbRole.GetCurSel();

	if (HS_NET_UserConfig(m_pParent->m_nLoginID, &usrInfo, HS_USER_ADD) != 0)
	{
		MessageBox("HS_NET_UserConfig failed!");
		return;
	}

	OnBnClickedButtonGet();
}

void CUserParamDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	HS_USER_INFOR usrInfo;
	memset(&usrInfo, 0, sizeof(HS_USER_INFOR));
	CString temp;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(temp);
	strncpy((char*)usrInfo.ucUsername, temp, 32);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(temp);
	strncpy((char*)usrInfo.ucPassWord, temp, 32);
	usrInfo.ucRole = m_cbRole.GetCurSel();

	if (HS_NET_UserConfig(m_pParent->m_nLoginID, &usrInfo, HS_USER_DEL) != 0)
	{
		MessageBox("HS_NET_UserConfig failed!");
		return;
	}

	OnBnClickedButtonGet();
}

void CUserParamDlg::OnBnClickedButtonEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	HS_USER_INFOR usrInfo;
	memset(&usrInfo, 0, sizeof(HS_USER_INFOR));
	CString temp;
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(temp);
	strncpy((char*)usrInfo.ucUsername, temp, 32);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(temp);
	strncpy((char*)usrInfo.ucPassWord, temp, 32);
	usrInfo.ucRole = m_cbRole.GetCurSel();

	if (HS_NET_UserConfig(m_pParent->m_nLoginID, &usrInfo, HS_USER_EDIT) != 0)
	{
		MessageBox("HS_NET_UserConfig failed!");
		return;
	}

	OnBnClickedButtonGet();
}


void CUserParamDlg::OnHdnItemclickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUserParamDlg::OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CUserParamDlg::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION Pos = m_lcUsrList.GetFirstSelectedItemPosition();
	int nSelect = -1;

	while ( Pos )
	{
		nSelect = m_lcUsrList.GetNextSelectedItem(Pos);    //nSelect能获得第几行
	}

	if (m_pUserInfo != NULL && m_nUserCount > nSelect)
	{
		GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText((char*)m_pUserInfo[nSelect].ucUsername);
		GetDlgItem(IDC_EDIT_PASSWORD)->SetWindowText((char*)m_pUserInfo[nSelect].ucPassWord);
		m_cbRole.SetCurSel(m_pUserInfo[nSelect].ucRole);
	}
	
	*pResult = 0;
}
