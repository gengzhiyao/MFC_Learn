#pragma once
#include <afxwin.h>

class MDIApp:public CWinApp
{
	BOOL InitInstance();
};

class CMyDoc :public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
};

IMPLEMENT_DYNCREATE(CMyDoc, CDocument)

class CMyView :public CView
{
public:
	virtual void OnDraw(CDC* pDC);
	DECLARE_DYNCREATE(CMyView)

};

IMPLEMENT_DYNCREATE(CMyView, CView)

class CMyChild :public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMyChild)
};

IMPLEMENT_DYNCREATE(CMyChild, CMDIChildWnd)

//����ܲ�֧�ֶ�̬����
class CMyFrame :public CMDIFrameWnd
{

};


