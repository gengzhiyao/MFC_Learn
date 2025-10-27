#pragma once
#include <afxwin.h>
#include <afxtoolbar.h>
class C_MFCToolBar:public CWinApp
{
public:
	virtual BOOL InitInstance() override;
};

class CMFCToolBarFrame :public CFrameWnd
{
public:
	CToolBar* ptoolBar;
public:
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnNew();
	DECLARE_MESSAGE_MAP()
};

