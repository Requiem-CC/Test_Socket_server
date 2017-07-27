#pragma once

// CServerSocket command target
#include "Test_Socket_serverDlg.h"
class CTest_Socket_serverDlg;
class CServerSocket : public CSocket
{
public:
	CTest_Socket_serverDlg* m_pDlg;
	CServerSocket();
	virtual ~CServerSocket();
//	virtual void AssertValid() const;
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


