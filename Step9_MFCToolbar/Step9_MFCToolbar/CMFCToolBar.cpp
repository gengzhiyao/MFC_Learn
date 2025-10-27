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
	ptoolBar->CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP|CBRS_GRIPPER);//��Create��Load
	//CWnd* a=AfxGetMainWnd();//�˴�������δ�����ɹ�,AfxGetMainWnd()���ص���CWinApp::m_pMainWnd��OnCreate�����ڵ���ʱ�������ڻ�δ�����ɹ�
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

