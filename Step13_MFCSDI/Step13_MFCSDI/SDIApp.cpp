#include "SDIApp.h"
#include "resource.h"

BOOL SDIApp::InitInstance()
{
	///文档模板中存放了与文档视图和框架相关的信息，应用程序通过文档模板创建文档对象，框架窗口和视图对象
	CSingleDocTemplate* pTemplte = new CSingleDocTemplate(IDR_MENU1, RUNTIME_CLASS(CMyDoc), RUNTIME_CLASS(CMyFrame), RUNTIME_CLASS(CMyView));
	AddDocTemplate(pTemplte);
	OnFileNew();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

SDIApp theApp;

void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(100,100,_T("我是视图窗口"));
}

///MFC中，应用程序类处理的消息是ONCOMMAND，其他消息基本到不了这里