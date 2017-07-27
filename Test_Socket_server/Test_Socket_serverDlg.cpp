
// Test_Socket_serverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test_Socket_server.h"
#include "Test_Socket_serverDlg.h"
#include "afxdialogex.h"
#include "ChildThread.h"
#include "winsock.h"
#include "Login.h"
#include <mysql.h>
#include "winsock2.h"
#pragma comment(lib,"libmysql.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CTest_Socket_serverDlg* CTest_Socket_serverDlg::s_dlg = NULL;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTest_Socket_serverDlg dialog




CTest_Socket_serverDlg::CTest_Socket_serverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTest_Socket_serverDlg::IDD, pParent)
	, m_port(0)
	, m_userCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_Socket_serverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_STATIC_UserCount, m_userCount);
	DDX_Control(pDX, IDC_EVentRecord, m_event);
}

BEGIN_MESSAGE_MAP(CTest_Socket_serverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_StartServer, &CTest_Socket_serverDlg::OnBnClickedStartserver)
	ON_BN_CLICKED(IDC_CloseServer, &CTest_Socket_serverDlg::OnBnClickedCloseserver)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CTest_Socket_serverDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_MYSQLTEST_BUTTON, &CTest_Socket_serverDlg::OnBnClickedMysqltestButton)
	ON_BN_CLICKED(IDC_MYSQLSELECT_BUTTON, &CTest_Socket_serverDlg::OnBnClickedMysqlselectButton)
END_MESSAGE_MAP()


// CTest_Socket_serverDlg message handlers

BOOL CTest_Socket_serverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Ԥ������������
// 	listenSocket = new CServerSocket();
// 	listenSocket->m_pDlg=this;
// 	listenSocket->Create();
// 	UpdateEvent(_T("�����ѿ���"));
	m_port=8090;
	UpdateData(FALSE);
	m_connect=FALSE;
	listenSocket=NULL;
// 	�������ݿ�
// 		HRESULT hr;
// 		CoInitialize(NULL);//��ΪConnection��Recordset��Command��ADO�����������ʽ�ṩ�ģ�������Ҫ��ʼ��COM�⣻
// 						   //��ʼ��Ҫ����CoInitialize(NULL)�������Ҫ����CoUninitialize();
// 		try
// 		{
// 			//hr = m_pConnection.CreateInstance(_T("ADODB.Connection"));///����Connection����
// 			hr = m_pConnection.CreateInstance(_uuidof(Connection));///����Connection����
// 			if (SUCCEEDED(hr))
// 			{
// 				hr = m_pConnection->Open("driver={SQL Server};Server=127.0.0.1;DATABASE=Devil;UID=sa;PWD=devil0330+","","",adModeUnknown);
// 				AfxMessageBox(_T("�������ݿ�ɹ���"));
// 			}
// 			CoUninitialize();
// 		}
// 		catch(_com_error e)
// 		{
// 			CString errormessage;
// 			errormessage.Format(_T("�������ݿ�ʧ�ܣ�\r\n������Ϣ��%s"),e.ErrorMessage());
// 			AfxMessageBox(errormessage);
// 		}
	sqlconnect=FALSE;//���ݿ�����״̬��ʼ��Ϊ��
	s_dlg = this;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTest_Socket_serverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTest_Socket_serverDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTest_Socket_serverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTest_Socket_serverDlg::OnBnClickedStartserver()
{

	// 	listenSocket = new CServerSocket();
	// 	if (m_connect)
	// 	{
	// 		delete listenSocket;
	// 		listenSocket = NULL;
	// 		m_connect = FALSE;
	// 		SetDlgItemText(IDC_StartServer,(_T("�򿪷�����")));
	// 		UpdateEvent(_T("ϵͳ�رշ�����"));
	// 		return;
	// 	}
	// 	listenSocket->m_pDlg = this;
	// 	//ָ���Ի���Ϊ���Ի��򣿡������᣿
	// 	UpdateData(TRUE);
	// 	if (!listenSocket->Create(m_port))//�������������׽��֣�ip��ַΪ������ַ
	// 	{
	// 		AfxMessageBox(_T("�����׽��ִ���"));
	// 		listenSocket->Close();
	// 		return;
	// 	}
	// 	if (!listenSocket->Listen())
	// 	{
	// 		AfxMessageBox(_T("����ʧ�ܣ�"));
	// 		listenSocket->Close();
	// 		return;
	// 	}
	// 	m_connect = TRUE;
	// 	SetDlgItemText(IDC_StartServer, _T("�رշ�����"));
	// 	UpdateEvent(_T("ϵͳ�򿪷�����."));
	if (m_connect)
	{
		UpdateEvent(_T("������������."));
		return;
	}
	listenSocket = new CServerSocket();
	listenSocket->m_pDlg=this;
	UpdateData(TRUE);
	//listenSocket->Create(m_port);
// 	if (!AfxSocketInit())
// 	{
// 		AfxMessageBox(_T("�����׳�ʼ��ʧ�ܣ�"));
// 		listenSocket->Close();
// 		return;
// 	}

	if (!listenSocket->Create(m_port))//�������������׽���,IP��ַΪ����
	{
		AfxMessageBox(_T("�����׽��ִ���"));
		listenSocket->Close();
		return;
	}
	if (!listenSocket->Listen())
	{
		AfxMessageBox(_T("����ʧ�ܣ�"));
		listenSocket->Close();
		return;
	}
	m_connect=TRUE;
	UpdateEvent(_T("ϵͳ�򿪷�����."));
	return;

}

void CTest_Socket_serverDlg::AddClient()
{
	CServerSocket *pSocket = new CServerSocket;
	pSocket->m_pDlg = this;
	listenSocket->Accept(*pSocket);
	pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
	m_clientList.AddTail(pSocket);
	m_userCount = m_clientList.GetCount();
	UpdateData(FALSE);
	UpdateEvent(_T("�û����ӷ�����."));
	SendMSG(_T("���ӳɹ�!"));
}

void CTest_Socket_serverDlg::RemoveClient(CServerSocket* pSocket)
{
	POSITION nPos = m_clientList.GetHeadPosition();
	POSITION nTmpPos = nPos;
	while (nPos)
	{
		CServerSocket* pSockItem = (CServerSocket*)m_clientList.GetNext(nPos);
		if (pSockItem->m_hSocket == pSocket->m_hSocket)
		{                          
			pSockItem->Close();
			delete pSockItem;
			m_clientList.RemoveAt(nTmpPos);
			m_userCount = m_clientList.GetCount();
			UpdateData(FALSE);
			UpdateEvent(_T("�û��뿪."));
			return;
		}
		nTmpPos = nPos;
	}
}
void CTest_Socket_serverDlg::RecvData(CServerSocket* pSocket)//��������
{
	char* pData = NULL;
	pData = new char[1024];
	memset(pData, 0, sizeof(char)* 1024);
	UCHAR leng = 0;
	CString str;
	if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR)
	{
		str = pData;
		ControlPC(str);     // ����ָ����Ƶ���
		SendMSG(str);     // ת�����ݸ������û��������������ݵ��û�
	}
	delete pData;
	pData = NULL;
}

void CTest_Socket_serverDlg::UpdateEvent(CString str)
{
	CString string;
	CTime time = CTime::GetCurrentTime();                  
	// ��ȡϵͳ��ǰʱ��
	str += _T("\r\n");                                                             
	// ���ڻ�����ʾ��־
	string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;         
	// ��ʽ����ǰʱ��
	int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);
	//��ȡ�༭�����һ������
	m_event.SetSel(lastLine+1,lastLine+2,0);                                     
	//ѡ��༭�����һ��
	m_event.ReplaceSel(string);  //�滻��ѡ��һ�е�����
}


BOOL CTest_Socket_serverDlg::WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, 0, 0, FALSE);
	if (n<nlen)return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, srcBuff, -1, destBuff, nlen, 0, FALSE);
	return TRUE;
}
void CTest_Socket_serverDlg::SendMSG(CString str)
{
	//CPtrList m_clientList;
	char *pSend = new char[str.GetLength()*2];
	memset(pSend, 0, str.GetLength()*sizeof(char));
	if (!WChar2MByte(str.GetBuffer(0), pSend, str.GetLength()*2))
	{
		AfxMessageBox(_T("�ַ�ת��ʧ��"));
		delete pSend;
		return;
	}
	POSITION nPos = m_clientList.GetHeadPosition();
	while (nPos)
	{
		CServerSocket* pTemp = (CServerSocket*)m_clientList.GetNext(nPos);
		pTemp->Send(pSend, str.GetLength() * 2);
	}
	delete pSend;
}

void CTest_Socket_serverDlg::ControlPC(CString AndroidControl)
{
	if (AndroidControl == "����������")             //�򿪲�����
	{
		ShellExecute(NULL, _T("open"), _T("cloudmusic.exe"), NULL, NULL, SW_SHOWNORMAL);
	}
	if (AndroidControl == "�ȸ�")             //�򿪲�����
	{
		ShellExecute(this->m_hWnd,_T("open"),_T("http://www.google.com"),NULL,NULL, SW_SHOW );
	}
	if (AndroidControl == "�ٶ�")             //�򿪲�����
	{
		ShellExecute(this->m_hWnd,_T("open"),_T("http://www.baidu.com"),NULL,NULL, SW_SHOW );
	}
	if (AndroidControl == "���±�")             //�򿪲�����
	{
		ShellExecuteW(NULL,_T("open"),_T("notepad.exe") , NULL, NULL, SW_SHOWNORMAL);
	}
	else if (AndroidControl == "mcl")         //�رղ�����
	{
		DWORD id_num;
		HWND hWnd = ::FindWindow(_T("kugou_ui"), NULL);
		GetWindowThreadProcessId(hWnd, &id_num);                      
		//ע�⣺�ڶ��������ǽ��̵�ID������ֵ���̵߳�ID��
		HANDLE hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id_num);
		TerminateProcess(hd, 0);
	}
	else if (AndroidControl == "mpl" || AndroidControl == "mpa") //����/��ͣ
	{
		keybd_event(VK_LMENU, 0, 0, 0);
		keybd_event(VK_F5, 0, 0, 0);
		keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
	}
}

BOOL CTest_Socket_serverDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->wParam)
	{
	case VK_RETURN:
	case VK_ESCAPE:
		return true; break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTest_Socket_serverDlg::OnBnClickedCloseserver()
{
	//listenSocket=NULL;
	if (!listenSocket)
	{
		UpdateEvent(_T("������δ����."));
		return;
	}
	if (listenSocket)
	{
		//listenSocket=NULL;
		listenSocket->Close();
		UpdateEvent(_T("ϵͳ�رշ�����."));
		listenSocket=NULL;
		m_connect=FALSE;
		return;
	}
	//delete listenSocket;

}


void CTest_Socket_serverDlg::OnBnClickedButtonOpen()
{
	ChildThread* m_pTipDlg=NULL;
	if (NULL == m_pTipDlg)
	{
		m_pTipDlg = new ChildThread;
		m_pTipDlg->Create(IDD_DIALOG1,this);
	}
	m_pTipDlg->ShowWindow(SW_SHOW);
	UpdateData(TRUE);


// 	ChildThread dlg;//ģ̬
// 	dlg.DoModal();
}


void CTest_Socket_serverDlg::OnBnClickedMysqltestButton()
{
	char *host = "127.0.0.1"; 
	char *user = "root";  
	char *passwd= "root";  
	char *db = "account_management";  
// 	MYSQL m_sqlCon;
// 	mysql_init(&m_sqlCon);
//  	if(!mysql_real_connect(&m_sqlCon,"127.0.0.1","root","root","Devil",3306,NULL,0))    
//  	{    
//  		AfxMessageBox(_T("�������ݿ�ʧ��!"));  
// //   		CString e=mysql_error(&m_sqlCon);//��Ҫ����Ŀ�������ַ����޸�Ϊ��ʹ�ö��ֽ��ַ�������δ���á�  
// //   		MessageBox(e);  
//  		return;  
//  	}  
//  	else  
//  	{    
//  		AfxMessageBox(_T("�ɹ�!"));  
//  		mysql_query(&m_sqlCon,"SET NAMES 'GB2312'");//��������ݿ��ж�ȡ���ݺ���������ʾ������  
//  	}  

	mysql = mysql_init(NULL);//��ʼ��mysql
	char* sql = "SELECT * FROM log_in /*WHERE username='test'*/";//����SQL���
	if (!mysql_real_connect(mysql,host,user,passwd,db,3306,NULL,0))
	{
		CString strError;
		strError.Format(_T("���ݿ�����ʧ��: Error: %s\n"),mysql_error(mysql));
		AfxMessageBox(strError); 
		return;
	}
	if (sqlconnect == TRUE)
	{
		AfxMessageBox(_T("���ݿ������ӣ�"));
		return;
	}
	if (mysql_real_connect(mysql,host,user,passwd,db,3306,NULL,0))
	{
		
		AfxMessageBox(_T("���ݿ����ӳɹ���")); 
		sqlconnect = TRUE;
		return;
	}

	//mysql_query(mysql,"set character set gbk");//��������ݿ��ж�ȡ���ݺ���������ʾ������  
	mysql_query(mysql,"SET NAMES 'GB2312'");//��������ݿ��ж�ȡ���ݺ���������ʾ������  
	mysql_query(mysql,sql);
// 	result = mysql_store_result(mysql);//һ���Բ�ѯ
// 	if (NULL==result)
// 	{
// 		AfxMessageBox(_T("��������Ϊ�գ�"));
// 		return;
// 	}
// 	countsql=1;//��������ʼ��
// 	while (row = mysql_fetch_row(result))
// 	{
// 		if (NULL ==result)
// 		{
// 			break;
// 		}
// 		
// 		CString str;
// 		str.Format(_T("��%d����\n�˺ţ�%S���룺%SȨ�޵ȼ���%S"),countsql,LPCTSTR(row[0]),LPCTSTR(row[1]),LPCTSTR(row[2]));
// 		AfxMessageBox(str);
// 		countsql++;//ÿѭ��һ�μ�������1
// 		
// 		
// 	}
// // 	mysql_free_result(result);
// // 	mysql_close(mysql);
// 
// 	AfxMessageBox(_T("���Գɹ�"));
// 	return;



// 	result = mysql_use_result(mysql);//���в�ѯ
// 	countsql=1;//��������ʼ��
// 	if (NULL==result)
// 	{
// 		AfxMessageBox(_T("��������Ϊ�գ�"));
// 		return;
// 	}
// 	while (row = mysql_fetch_row(result))
// 	{
// 		if (NULL ==result)
// 		{
// 			break;
// 		}
// 		
// 		CString str,str0,str1,str2;
// 		str2 = row[2];
//  		if (str2 == "0")
//  		{
// 			row[2] = "��������Ա";
// 		}
// 		if (str2 == "1")
// 		{
// 			row[2] = "�߼�����Ա";
// 		}
// 		if (str2 == "2")
// 		{
// 			row[2] = "����Ա";
// 		}
// 		if (str2 == "3")
// 		{
// 			row[2] = "��Ա\0";
// 		}
// 		str0 = row[0];
// 		str1 = row[1];
// 		str2 = row[2];
// 		str.Format(_T("��%d����\n�˺ţ�%s\n���룺%s\nȨ�޵ȼ���%s"),countsql,str0,str1,str2);
// 		AfxMessageBox(str);
// 		countsql++;//ÿѭ��һ�μ�������1
// 	}

	return;
}


void CTest_Socket_serverDlg::OnBnClickedMysqlselectButton()
{
	CLogin* m_loginDlg = NULL;
	if (NULL == m_loginDlg)
	{
 		m_loginDlg = new CLogin;
		m_loginDlg->Create(IDD_LOGIN_DIALOG,this);
	}
	m_loginDlg->ShowWindow(SW_SHOW);

	return;
}
