#include "CDocApp.h"
#include "resource.h"

BOOL CDocApp::InitInstance()
{
	CDocFrame* pFrame = new CDocFrame();
	CDoc* pDoc = new CDoc;

	CCreateContext cct;
	cct.m_pNewViewClass = RUNTIME_CLASS(CDocView);//�����õ���̬����classCDocView
	cct.m_pCurrentDoc = pDoc;

	//1.������ܴ��� 2.�ڴ����ܴ��ڵ�WM_CREATE��Ϣʱ��CFrameWnd��̬������ͼ����󣬲�������ͼ���� 3. �ڴ�����ͼ���ڵ�WM_CREATE��Ϣʱ�����ĵ���������ͼ���������ϵ
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

/// @brief ��ܴ��ڵ�WM_CREATE��Ϣ
///		   ������Լ�����ô����������ø����OnCreate������ʱ��ֻ�ᴴ���ͻ����������ᴴ����ͼ�����
///        ʹ��OnPaint������֤����ͼ��û�д�����ֻ���ڿͻ�����ʾ�˻�����Ϣ
///        �����ø���Ĵ���������ͼ�������˿ͻ�������ʾOnDraw���Ƶ���Ϣ
/// @param pcs 
/// @return 
int CDocFrame::OnCreate(LPCREATESTRUCT pcs)
{
	///return 0;//������CFrameWnd�Ĵ�����
	return CFrameWnd::OnCreate(pcs);//�����OnCreate�����ж�̬��������ͼ����󣬲���������ͼ���ڣ���˻Ḳ�ǿ�ܴ��ڵĿͻ���
}

/// @brief ��ͼ���ڵ�WM_CREATE��Ϣ
/// @param pcs 
/// @return 
int CDocView::OnCreate(LPCREATESTRUCT pcs)
{
	return CView::OnCreate(pcs);//���ཫ�ĵ���������ͼ�������й���
}

void CDocFrame::OnPaint()
{
	PAINTSTRUCT ps = { 0 };
	HDC DC = ::BeginPaint(this->m_hWnd, &ps);
	::TextOut(DC, 1000, 100, _T("��ܴ��ڿͻ���"), wcslen(L"��ܴ��ڿͻ���"));
	::EndPaint(this->m_hWnd, &ps);
}

void CDocView::OnDraw(CDC* pDC) { pDC->TextOut(10, 10, _T("��ͼ����")); }

BOOL CDocFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//���������ͼ����
	split.CreateStatic(this, 1, 2);
	split.CreateView(0, 0, pContext->m_pNewViewClass, CSize(100, 100), pContext);
	split.CreateView(0, 1, RUNTIME_CLASS(CDocView), CSize(100, 100), pContext);
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
