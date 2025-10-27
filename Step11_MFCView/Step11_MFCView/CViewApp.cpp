#include "CViewApp.h"

BOOL CViewApp::InitInstance()
{
	MyFrame* pFrame = new MyFrame();
	pFrame->Create(NULL, _T("FrameForView "));
	this->m_pMainWnd = pFrame;///m_pMainWnd��ǰӦ�ó����������
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
	//���뺯���ڲ������Կ�����������ͼ���ڵĹ��̺ʹ����ܴ����ߵ�·����һ����
	myview->Create(nullptr, _T(""), WS_CHILD | WS_VISIBLE|WS_BORDER, CRect(0, 0, 200, 200), this, 1001);//AFX_IDW_PANE_FIRST���ID�Ƚ����⣬�Ὣ��ͼ����ƽ���ڿ�ܴ��ڵĿͻ�����
	return CFrameWnd::OnCreate(pcs);
}

/// @brief ������OnDraw����ͼ������Ϊʲô����OnPaint�أ�
///			OnDraw�������Լ��������Ϊ������ȴ�Ǹ���CView�ڲ������ڵ��ã���OnDraw��OnPaint��������ʱ�������OnPaint����ΪOnPaint�������Լ�����Ļ�ͼ��Ϣ���������Լ������Լ�����
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

///ȫ�ֶ���theApp����һ����Ա����Ϊm_pMainFrame���ǿ�������ĵ�ַ����m_pMainFrame��������������һ����Ա����Ϊm_pViewActive������ͼ�����ĵ�ַ
/**
*     theApp
*	    |-> m_pMainFrame
*                 |->m_pViewActive  ��������ͼʱ��ϵͳ���Զ����ò�����ֵ
*                          |->m_pDocument   �ĵ������ĵ�ַ
*                                 |->m_viewList    ������ͼ�����ĵ�ַ�����Ǹ�����
*/

//ʹ�õ������õ�ĳһ����ͼ��GetFirstViewPosition()���ص���POSITION����
//POSITION pos = GetFirstViewPosition();//����������ָ���λ���ǵ�һ���ڵ���Ϸ�
//CView* view=this->GetNextView(pos);//������������õ���ͷ��㣬����һ��view��ͼ����
//ʹ��Doc���UpdateAllViews(NULL)���ĵ������ݸ���ʱ��֪ͨ��ͼ�����ˢ��

//GetDocument();��ȡ����m_pDocument��Ա