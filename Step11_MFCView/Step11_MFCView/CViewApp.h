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
	//����ͼ�����м���OnPaint����OnDrawʱ����Ϊ��ʲô��
	void OnPaint();
	void OnDraw(CDC* pDC) override;
	DECLARE_MESSAGE_MAP()
};

///��ͼ��������ͼ���ڣ����ǿ�ܴ��ڵĿͻ���
