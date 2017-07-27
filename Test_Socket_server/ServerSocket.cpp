// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Test_Socket_server.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket member functions


//void CServerSocket::AssertValid() const
//{
//	CSocket::AssertValid();
//
//	// TODO: Add your specialized code here and/or call the base class
//}


void CServerSocket::OnAccept(int nErrorCode)
{
	m_pDlg->AddClient();  
	CSocket::OnAccept(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	m_pDlg->RemoveClient(this);
	CSocket::OnClose(nErrorCode);
}


void CServerSocket::OnReceive(int nErrorCode)
{
	m_pDlg->RecvData(this);    
	CSocket::OnReceive(nErrorCode);
}
