#include "CViewApp.h"

BOOL CViewApp::InitInstance()
{
	MyFrame* pFrame = new MyFrame();
	pFrame->Create(NULL, _T("FrameForView "));
	this->m_pMainWnd = pFrame;///m_pMainWnd当前应用程序的主窗口
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(MyView, CView)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CViewApp theApp;

int MyFrame::OnCreate(LPCREATESTRUCT pcs)
{
	MyView* myview = new MyView();
	//进入函数内部，可以看到，创建视图窗口的过程和创造框架窗口走的路径是一样的
	myview->Create(nullptr, _T(""), WS_CHILD | WS_VISIBLE|WS_BORDER, CRect(0, 0, 200, 200), this, 1001);//AFX_IDW_PANE_FIRST这个ID比较特殊，会将视图窗口平铺在框架窗口的客户区上
	return CFrameWnd::OnCreate(pcs);
}

/// @brief 这里是OnDraw，绘图，想想为什么不是OnPaint呢？
///			OnDraw是我们自己定义的行为，但是却是父类CView内部代码在调用，当OnDraw和OnPaint函数共存时，会调用OnPaint，因为OnPaint是我们自己定义的绘图消息处理函数，自己定义自己消化
/// @param pDC 
void MyView::OnDraw(CDC* pDC)
{
	pDC->TextOutW(50, 50, CString(_T("MyView::OnDraw")));
}

void MyView::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC dc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(dc, 0, 0, CString(_T("MyView::OnPaint")), strlen("MyView::OnPaint"));
	::EndPaint(this->m_hWnd, &ps);
}

void MyFrame::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC dc = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(dc, 350, 350, CString(_T("MyFrame::OnPaint")), strlen("MyFrame::OnPaint"));
	::EndPaint(this->m_hWnd, &ps);
}

///全局对象theApp中有一个成员变量为m_pMainFrame，是框架类对象的地址；而m_pMainFrame框架类对象中又有一个成员变量为m_pViewActive，是视图类对象的地址
/**
*     theApp
*	    |-> m_pMainFrame
*                 |->m_pViewActive  鼠标点击活动视图时，系统会自动给该参数赋值
*                          |->m_pDocument   文档类对象的地址
*                                 |->m_viewList    所有视图类对象的地址，这是个链表
*/

//使用迭代器得到某一个视图：GetFirstViewPosition()返回的是POSITION类型
//POSITION pos = GetFirstViewPosition();//迭代器首先指向的位置是第一个节点的上方
//CView* view=this->GetNextView(pos);//这里才是真正拿到了头结点，即第一个view视图对象
//使用Doc类的UpdateAllViews(NULL)在文档类数据更改时，通知视图类对象刷新

//GetDocument();获取的是m_pDocument成员