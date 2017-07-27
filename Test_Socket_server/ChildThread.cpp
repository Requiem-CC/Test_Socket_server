// ChildThread.cpp : implementation file
//

#include "stdafx.h"
#include "Test_Socket_server.h"
#include "ChildThread.h"
#include "afxdialogex.h"
#include "Test_Socket_serverDlg.h"


// ChildThread dialog

IMPLEMENT_DYNAMIC(ChildThread, CDialogEx)

ChildThread::ChildThread(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChildThread::IDD, pParent)
{

}

ChildThread::~ChildThread()
{
}

void ChildThread::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_a);
	DDX_Control(pDX, IDC_EDIT2, m_b);
}


BEGIN_MESSAGE_MAP(ChildThread, CDialogEx)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BUTTON_THREAD, &ChildThread::OnBnClickedButtonThread)
END_MESSAGE_MAP()


// ChildThread message handlers


void ChildThread::OnMouseHover(UINT nFlags, CPoint point)
{
	 
	AfxMessageBox(_T("捕获成功"));
	CRect rect;
	this->GetWindowRect(&rect);
	if (rect.PtInRect(point))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));  
	}

	CDialogEx::OnMouseHover(nFlags, point);
}


void ChildThread::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* pWnd = GetDlgItem(IDC_BUTTON_THREAD);
	CRect rect;
	pWnd->GetWindowRect(&rect);
	CPoint pt;
	::GetCursorPos(&pt);
	if (rect.PtInRect(pt))
	{
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));  
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL ChildThread::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


BOOL ChildThread::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_MOUSEMOVE)  //判断消息响应类型
	{  
		OnMouseMove(pMsg->wParam,pMsg->pt);  
	}  
	if(pMsg->message == WM_MOUSEHOVER)  
	{    
		OnMouseHover(pMsg->wParam,pMsg->pt); 
	}  

	return CDialogEx::PreTranslateMessage(pMsg);
}


void ChildThread::OnBnClickedButtonThread()
{
	GetDlgItemText(IDC_EDIT1,a);
	GetDlgItemText(IDC_EDIT2,b);
	thread_transmit p;
	p.thread_a = _tstoi(a);
	p.thread_b = _tstoi(b);
	
	HANDLE hThread;
	//hThread =AfxBeginThread();
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread1, &p, 0, NULL);
	WaitForSingleObject(Thread, INFINITE);
	Sleep(50);
	UpdateData(FALSE);

	sum.Format(_T("%d"),p.thread_sum);
	SetDlgItemText(IDC_EDIT3,sum);
	return ;
	
// 	char str[]="Hello";
// 	char stra[]="ABCDEFGHIGKLMNOPQRSTUVWXYZ";
// 	char stra1[]="ABCDEFGHIGKLMNOPQRSTUVWXYZ/0";
// 	char *p = str;
// 	int n = 10;
// 	/*e[100]="hello";*/
// 	int t;
// 	CString str1;
// 	//str1.StrCpy(str1,t);
// 	t = sizeof(str);
// 	char strover;
// 	strover = stra - stra1;
// 	for (int i=0;i<3;i++)
// 	{
// 		if (i==0)
// 		{
// 			t = sizeof(str);
// 			CString str1 ;
// 			str1.Format(_T("%d"),t);
// 			AfxMessageBox(str1);
// 		}
// 		if (i==1)
// 		{
// 			t = sizeof(p);
// 			CString str1 ;
// 			str1.Format(_T("%d"),t);
// 			AfxMessageBox(str1);
// 		}
// 		if (i==2)
// 		{
// 			t = sizeof(n);
// 			CString str1 ;
// 			str1.Format(_T("%d"),t);
// 			AfxMessageBox(str1);
// 		}
// 	}
	//AfxBeginThread(Thread1(),NULL,NULL,NULL,NULL,NULL);
 }
DWORD WINAPI  ChildThread::Thread1(LPVOID lpParameter)
{

	thread_transmit *thread_calculate =(thread_transmit*)lpParameter;
	thread_calculate->thread_sum=thread_calculate->thread_a+thread_calculate->thread_b;
	ChildThread a = new ChildThread;
	a.calculate();
	return 0;
}
void ChildThread::calculate()
{
	//UpdateData(FALSE);
	AfxMessageBox(_T("子线程输出"));
	//UpdateData(TRUE);
}
