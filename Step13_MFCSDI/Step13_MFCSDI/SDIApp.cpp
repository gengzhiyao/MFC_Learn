#include "SDIApp.h"
#include "resource.h"

BOOL SDIApp::InitInstance()
{
	///�ĵ�ģ���д�������ĵ���ͼ�Ϳ����ص���Ϣ��Ӧ�ó���ͨ���ĵ�ģ�崴���ĵ����󣬿�ܴ��ں���ͼ����
	CSingleDocTemplate* pTemplte = new CSingleDocTemplate(IDR_MENU1, RUNTIME_CLASS(CMyDoc), RUNTIME_CLASS(CMyFrame), RUNTIME_CLASS(CMyView));
	AddDocTemplate(pTemplte);
	OnFileNew();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

SDIApp theApp;

void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(100,100,_T("������ͼ����"));
}

///MFC�У�Ӧ�ó����ദ�����Ϣ��ONCOMMAND��������Ϣ��������������