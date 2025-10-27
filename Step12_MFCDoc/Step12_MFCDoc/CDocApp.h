#pragma once
#include <afxwin.h>
#include <afxext.h>

class CDocApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CDocFrame :public CFrameWnd
{
private:
	CSplitterWnd split;//为什么放在这里？不作为局部变量？
public:
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};

class CDocView :public CView
{
	DECLARE_DYNCREATE(CDocView)
public:
	virtual void OnDraw(CDC* pDC) override;
	afx_msg int OnCreate(LPCREATESTRUCT pcs);
	DECLARE_MESSAGE_MAP()
};

class CDoc :public CDocument
{

};