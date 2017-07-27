// Login.cpp : implementation file
//

#include "stdafx.h"
#include "Test_Socket_server.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Test_Socket_serverDlg.h"


// CLogin dialog

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, strUsername(_T(""))
	, strPassword(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAME_EDIT, strUsername);
	DDX_Text(pDX, IDC_PASSWORD_EDIT, strPassword);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN_BUTTON, &CLogin::OnBnClickedLoginButton)
END_MESSAGE_MAP()


// CLogin message handlers


void CLogin::OnBnClickedLoginButton()
{
	GetDlgItemText(IDC_USERNAME_EDIT,strUsername);
	GetDlgItemText(IDC_PASSWORD_EDIT,strPassword);
	UpdateData(TRUE);
	CTest_Socket_serverDlg* serverDlg = CTest_Socket_serverDlg::s_dlg;
	//CTest_Socket_serverDlg* serverDlg = new CTest_Socket_serverDlg;
	if (serverDlg->sqlconnect == FALSE)
	{
		AfxMessageBox(_T("数据库未连接!"));
		return;
	}
	mysql_query(serverDlg->mysql,"SET NAMES 'GB2312'");
	char* sql = "SELECT * FROM log_in /*WHERE username='test'*/";//储存SQL语句

	mysql_query(serverDlg->mysql,sql);
	serverDlg->result = mysql_use_result(serverDlg->mysql);//逐行查询
	if (login_succeed == TRUE)
	{
		AfxMessageBox(_T("已登录"));
		return ;
	}
	if (NULL==serverDlg->result)
	{
		AfxMessageBox(_T("表中数据为空！"));
		return;
	}
	while (serverDlg->row = mysql_fetch_row(serverDlg->result))
	{
		CString strName,strPWD;
		strName = serverDlg->row[0];
		strPWD  = serverDlg->row[1];
		if (strName ==strUsername&&strPWD ==strPassword)
		{
			AfxMessageBox(_T("登陆成功！"));
			login_succeed = TRUE;
			return;
		}	
	}
	AfxMessageBox(_T("登录失败！"));
}
