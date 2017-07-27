
// Test_Socket_server.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTest_Socket_serverApp:
// See Test_Socket_server.cpp for the implementation of this class
//

class CTest_Socket_serverApp : public CWinApp
{
public:
	CTest_Socket_serverApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTest_Socket_serverApp theApp;