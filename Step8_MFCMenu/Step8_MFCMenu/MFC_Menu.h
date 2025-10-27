#pragma once
#include <afxwin.h>
#include "resource.h"
class MFC_MenuApp:public CWinApp
{
public:
	virtual BOOL InitInstance() override;
};

class MFC_MenuFrame :public CFrameWnd
{
public:
	CMenu m_CMenu;
	afx_msg void OnMenuItemClick();
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnInitMenuPopup(CMenu*, UINT, BOOL);
	afx_msg void OnContextMenu(CWnd*, CPoint);
	DECLARE_MESSAGE_MAP()
};

