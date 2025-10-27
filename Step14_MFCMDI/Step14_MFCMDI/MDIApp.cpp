#include "MDIApp.h"
#include "resource.h"

BOOL MDIApp::InitInstance()
{
	CMyFrame* pFrame = new CMyFrame();
	pFrame->LoadFrame(IDR_MENU1);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	CMultiDocTemplate* pTemplate = new CMultiDocTemplate(IDR_MENU2, RUNTIME_CLASS(CMyDoc), RUNTIME_CLASS(CMyChild), RUNTIME_CLASS(CMyView));

	AddDocTemplate(pTemplate);
	OnFileNew();
	OnFileNew();//每次调用都会创建一个子视图窗口和视图窗口

	return TRUE;
}

MDIApp theApp;

void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(100, 100, _T("我是视图窗口"));
}

//CMultiDocTemplate类中有一个成员m_docList保存了多个文档类对象的地址
//theApp中成员m_pDocManager管理文档->m_templateList单文档模板类对象的地址