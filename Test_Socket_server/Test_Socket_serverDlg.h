
// Test_Socket_serverDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ServerSocket.h"
#include "afxcoll.h"
#include "mysql.h"


// CTest_Socket_serverDlg dialog
class CServerSocket;
class CTest_Socket_serverDlg : public CDialogEx
{
// Construction
public:
	CTest_Socket_serverDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TEST_SOCKET_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCreate();
	UINT m_port;
	//CString m_event;
	//UINT m_userCount;
	afx_msg void OnBnClickedStartserver();


	CServerSocket* listenSocket;     // 用于打开服务器
	CPtrList m_clientList;                 // 链表用于存储用户
	BOOL m_connect;                       // 用于标记服务器状态
	void AddClient();                       // 增加用户，响应用户请求
	void RemoveClient(CServerSocket* pSocket);          // 移除下线的用户
	void RecvData(CServerSocket* pSocket);                 // 获取数据
	void UpdateEvent(CString str);  // 更新事件日志
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);        
	//字符转换
	void SendMSG(CString str);       // 发送消息给各个客户端
	void ControlPC(CString AndroidControl);  // 手机控制PC的响应函数
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	UINT m_userCount;
	CEdit m_event;
	afx_msg void OnBnClickedCloseserver();
	afx_msg void OnBnClickedButtonOpen();
	_ConnectionPtr m_pConnection;//指向Connection对象的指针
	afx_msg void OnBnClickedMysqltestButton();
	afx_msg void OnBnClickedMysqlselectButton();
	afx_msg void OnBnClickedLoginButton();
	int countsql;//计数器
	MYSQL* mysql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	BOOL sqlconnect;//判断数据库是否连接
	static CTest_Socket_serverDlg* s_dlg;
};

