#pragma once
#include "afxwin.h"


// ChildThread dialog

class ChildThread : public CDialogEx
{
	DECLARE_DYNAMIC(ChildThread)

public:
	ChildThread(CWnd* pParent = NULL);   // standard constructor
	virtual ~ChildThread();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL PreTranslateMessage(MSG* pMsg);//÷ÿ‘ÿ–È∫Ø ˝
	afx_msg void OnBnClickedButtonThread();
	void calculate();
	static  DWORD WINAPI  Thread1(LPVOID lpParameter);
	static  DWORD WINAPI  Thread1(CString Thread);
	  HANDLE Thread;
	  CEdit m_a;
	  CEdit m_b;
	  CString a,b,sum;
	  BOOL judeg;
	  struct thread_transmit
	  {
		  int thread_a;
		  int thread_b;
		  int thread_sum;
	  };
};
