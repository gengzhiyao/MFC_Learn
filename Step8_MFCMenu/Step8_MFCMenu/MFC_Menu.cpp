#include "MFC_Menu.h"

BOOL MFC_MenuApp::InitInstance()
{
	MFC_MenuFrame* pFrame = new MFC_MenuFrame();
	//pFrame->Create(nullptr, _T("MFCMenu"), WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault, nullptr,MAKEINTRESOURCE(IDR_MENU1)/*reinterpret_cast<LPCTSTR>(IDR_MENU1);*/);
	pFrame->Create(nullptr, _T("MFCMenu"));
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

MFC_MenuApp theApp;

BEGIN_MESSAGE_MAP(MFC_MenuFrame, CFrameWnd)
	ON_COMMAND(ID_NEW,OnMenuItemClick)
	ON_WM_CREATE()
	ON_WM_INITMENUPOPUP()//在菜单项名称前面添加对号
	ON_WM_CONTEXTMENU()//右键点击
END_MESSAGE_MAP()

//MFC库中规定，若菜单项没有添加消息处理函数，那么该菜单项默认为灰色不可点击状态
void MFC_MenuFrame::OnMenuItemClick()
{
	AfxMessageBox(_T("新建菜单项被点击")); 
}

int MFC_MenuFrame::OnCreate(LPCREATESTRUCT pcs)
{
	//CMenu m_CMenu;//这是一个局部变量，在窗口处理函数调用之后就被销毁了，这样挂载菜单会引起异常，因此使他作为成员
	m_CMenu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_CMenu);
	return CFrameWnd::OnCreate(pcs);
}

//_AFXWIN_INLINE BOOL CMenu::LoadMenu(UINT nIDResource)
//{ Win32中，LoadMenu的返回值是菜单项的句柄
//	return Attach(::LoadMenuW(AfxFindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_MENU),							MAKEINTRESOURCEW(nIDResource)));}

/// @brief 宏ON_WM_INITMENUPOPUP对应的处理函数
/// @param pmenu 
/// @param nPos 
/// @param isChecked 
void MFC_MenuFrame::OnInitMenuPopup(CMenu* pmenu, UINT nPos, BOOL isChecked )
{
	pmenu->CheckMenuItem(ID_NEW, MF_CHECKED);
	::CheckMenuItem(pmenu->m_hMenu, ID_NEW, MF_CHECKED);//Win32调用形式
}

/// @brief 右键菜单项
/// @param pWnd 
/// @param pt 
void MFC_MenuFrame::OnContextMenu(CWnd* pWnd, CPoint pt)
{
	//Win32形式
	//HMENU hPopUP = ::GetSubMenu(m_CMenu.m_hMenu, 0);
	//::TrackPopupMenu(hPopUP, TPM_LEFTALIGN, pt.x, pt.y, 0, this->m_hWnd, NULL);
	//MFC形式
	CMenu* pPopUp = m_CMenu.GetSubMenu(0);
	pPopUp->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y,this, NULL);
}

