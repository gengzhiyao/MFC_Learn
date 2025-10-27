#include "CMFCToolBar.h"
#include "resource.h"

BOOL C_MFCToolBar::InitInstance()
{
	CMFCToolBarFrame* pFrame = new CMFCToolBarFrame();
	pFrame->Create(nullptr, _T("MFCToolBar"), WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault, nullptr, reinterpret_cast<LPCTSTR>(IDR_MENU1));
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

C_MFCToolBar theApp;

BEGIN_MESSAGE_MAP(CMFCToolBarFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_New,OnNew)
END_MESSAGE_MAP()

int CMFCToolBarFrame::OnCreate(LPCREATESTRUCT pcs)
{
	ptoolBar = new CToolBar();
	ptoolBar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP|CBRS_GRIPPER);//先Create再Load
	//CWnd* a=AfxGetMainWnd();//此处窗口尚未创建成功,AfxGetMainWnd()返回的是CWinApp::m_pMainWnd，OnCreate函数在调用时，主窗口还未创建成功
	ptoolBar->LoadToolBar(IDR_TOOLBAR1);
	ptoolBar->EnableDocking(CBRS_ALIGN_ANY);
	this->EnableDocking(CBRS_ALIGN_ANY);
	this->DockControlBar(ptoolBar, AFX_IDW_DOCKBAR_TOP);
	return CFrameWnd::OnCreate(pcs);
}

void CMFCToolBarFrame::OnNew()
{
	AfxMessageBox(_T(" "));
}

