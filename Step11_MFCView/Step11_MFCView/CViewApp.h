#pragma once
#include <afxwin.h>

class CViewApp:public CWinApp
{
public:
	virtual BOOL InitInstance() override;
};

class MyFrame :public CFrameWnd
{
public:
	int OnCreate(LPCREATESTRUCT pcs);
	void OnPaint();
	DECLARE_MESSAGE_MAP()
};

class MyView :public CView
{
public:
	//在视图窗口中既有OnPaint又有OnDraw时，行为是什么？
	void OnPaint();
	void OnDraw(CDC* pDC) override;
	DECLARE_MESSAGE_MAP()
};

///视图窗口是视图窗口，不是框架窗口的客户区
