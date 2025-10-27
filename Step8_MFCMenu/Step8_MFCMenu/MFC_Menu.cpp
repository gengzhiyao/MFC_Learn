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
	ON_WM_INITMENUPOPUP()//�ڲ˵�������ǰ����ӶԺ�
	ON_WM_CONTEXTMENU()//�Ҽ����
END_MESSAGE_MAP()

//MFC���й涨�����˵���û�������Ϣ����������ô�ò˵���Ĭ��Ϊ��ɫ���ɵ��״̬
void MFC_MenuFrame::OnMenuItemClick()
{
	AfxMessageBox(_T("�½��˵�����")); 
}

int MFC_MenuFrame::OnCreate(LPCREATESTRUCT pcs)
{
	//CMenu m_CMenu;//����һ���ֲ��������ڴ��ڴ���������֮��ͱ������ˣ��������ز˵��������쳣�����ʹ����Ϊ��Ա
	m_CMenu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_CMenu);
	return CFrameWnd::OnCreate(pcs);
}

//_AFXWIN_INLINE BOOL CMenu::LoadMenu(UINT nIDResource)
//{ Win32�У�LoadMenu�ķ���ֵ�ǲ˵���ľ��
//	return Attach(::LoadMenuW(AfxFindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_MENU),							MAKEINTRESOURCEW(nIDResource)));}

/// @brief ��ON_WM_INITMENUPOPUP��Ӧ�Ĵ�����
/// @param pmenu 
/// @param nPos 
/// @param isChecked 
void MFC_MenuFrame::OnInitMenuPopup(CMenu* pmenu, UINT nPos, BOOL isChecked )
{
	pmenu->CheckMenuItem(ID_NEW, MF_CHECKED);
	::CheckMenuItem(pmenu->m_hMenu, ID_NEW, MF_CHECKED);//Win32������ʽ
}

/// @brief �Ҽ��˵���
/// @param pWnd 
/// @param pt 
void MFC_MenuFrame::OnContextMenu(CWnd* pWnd, CPoint pt)
{
	//Win32��ʽ
	//HMENU hPopUP = ::GetSubMenu(m_CMenu.m_hMenu, 0);
	//::TrackPopupMenu(hPopUP, TPM_LEFTALIGN, pt.x, pt.y, 0, this->m_hWnd, NULL);
	//MFC��ʽ
	CMenu* pPopUp = m_CMenu.GetSubMenu(0);
	pPopUp->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y,this, NULL);
}

