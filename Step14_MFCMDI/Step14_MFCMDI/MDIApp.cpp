#include "MDIApp.h"
#include "resource.h"

BOOL MDIApp::InitInstance()
{
	CMyFrame* pFrame = new CMyFrame();
	pFrame->LoadFrame(IDR_MENU1);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	CMultiDocTemplate* pTemplate = new CMultiDocTemplate(IDR_MENU2, RUNTIME_CLASS(CMyDoc), RUNTIME_CLASS(CMyChild), RUNTIME_CLASS(CMyView));

	AddDocTemplate(pTemplate);
	OnFileNew();
	OnFileNew();//ÿ�ε��ö��ᴴ��һ������ͼ���ں���ͼ����

	return TRUE;
}

MDIApp theApp;

void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(100, 100, _T("������ͼ����"));
}

//CMultiDocTemplate������һ����Աm_docList�����˶���ĵ������ĵ�ַ
//theApp�г�Աm_pDocManager�����ĵ�->m_templateList���ĵ�ģ�������ĵ�ַ