#include "CDocApp.h"
#include "resource.h"

BOOL CDocApp::InitInstance()
{
	CDocFrame* pFrame = new CDocFrame();
	CDoc* pDoc = new CDoc;

	CCreateContext cct;
	cct.m_pNewViewClass = RUNTIME_CLASS(CDocView);//可以拿到静态变量classCDocView
	cct.m_pCurrentDoc = pDoc;

	//1.创建框架窗口 2.在处理框架窗口的WM_CREATE消息时，CFrameWnd动态创建视图类对象，并创建视图窗口 3. 在处理视图窗口的WM_CREATE消息时，将文档类对象和视图类对象建立联系
	pFrame->LoadFrame(IDR_MENU1, WS_OVERLAPPEDWINDOW, NULL, &cct);
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDocFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDocView,CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CDocView, CView)

CDocApp theApp;

/// @brief 框架窗口的WM_CREATE消息
///		   如果你自己定义该处理函数不调用父类的OnCreate处理函数时，只会创建客户区，而不会创建视图类对象
///        使用OnPaint可以验证，视图并没有创建，只是在客户区显示了绘制信息
///        若调用父类的处理函数，视图区覆盖了客户区，显示OnDraw绘制的信息
/// @param pcs 
/// @return 
int CDocFrame::OnCreate(LPCREATESTRUCT pcs)
{
	///return 0;//会屏蔽CFrameWnd的处理函数
	return CFrameWnd::OnCreate(pcs);//父类的OnCreate函数中动态创建了视图类对象，并创建了视图窗口，因此会覆盖框架窗口的客户区
}

/// @brief 视图窗口的WM_CREATE消息
/// @param pcs 
/// @return 
int CDocView::OnCreate(LPCREATESTRUCT pcs)
{
	return CView::OnCreate(pcs);//父类将文档类对象和视图类对象进行关联
}

void CDocFrame::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC DC = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(DC, 1000, 100, _T("框架窗口客户区"), wcslen(L"框架窗口客户区"));
	::EndPaint(this->m_hWnd, &ps);
}

void CDocView::OnDraw(CDC* pDC) { pDC->TextOut(10, 10, _T("视图窗口")); }

BOOL CDocFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//创建多个视图窗口
	split.CreateStatic(this, 1, 2);
	split.CreateView(0, 0, pContext->m_pNewViewClass, CSize(100, 100), pContext);
	split.CreateView(0, 1, RUNTIME_CLASS(CDocView), CSize(100, 100), pContext);
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
