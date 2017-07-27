
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


	CServerSocket* listenSocket;     // ���ڴ򿪷�����
	CPtrList m_clientList;                 // �������ڴ洢�û�
	BOOL m_connect;                       // ���ڱ�Ƿ�����״̬
	void AddClient();                       // �����û�����Ӧ�û�����
	void RemoveClient(CServerSocket* pSocket);          // �Ƴ����ߵ��û�
	void RecvData(CServerSocket* pSocket);                 // ��ȡ����
	void UpdateEvent(CString str);  // �����¼���־
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);        
	//�ַ�ת��
	void SendMSG(CString str);       // ������Ϣ�������ͻ���
	void ControlPC(CString AndroidControl);  // �ֻ�����PC����Ӧ����
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	UINT m_userCount;
	CEdit m_event;
	afx_msg void OnBnClickedCloseserver();
	afx_msg void OnBnClickedButtonOpen();
	_ConnectionPtr m_pConnection;//ָ��Connection�����ָ��
	afx_msg void OnBnClickedMysqltestButton();
	afx_msg void OnBnClickedMysqlselectButton();
	afx_msg void OnBnClickedLoginButton();
	int countsql;//������
	MYSQL* mysql;
	MYSQL_RES * result;
	MYSQL_ROW row;
	BOOL sqlconnect;//�ж����ݿ��Ƿ�����
	static CTest_Socket_serverDlg* s_dlg;
};

