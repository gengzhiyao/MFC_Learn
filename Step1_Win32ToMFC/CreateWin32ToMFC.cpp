#include <afxwin.h>
#include "CreateWin32ToMFC.h"

#define MY_MESSAGE WM_USER+1001
/// @brief �ӿ���Ŀ����MFCӦ�ó���

CreateWin32ToMFC::CreateWin32ToMFC()
{
}

BOOL CreateWin32ToMFC::InitInstance()
{
	/*mfcFrame* customFrame = new mfcFrame();
	customFrame->Create(NULL, _T("CUSTOMFRAME"));
	m_pMainWnd = customFrame;///m_pMainWnd��ǰӦ�ó����������
	customFrame->ShowWindow(SW_SHOW);
	customFrame->UpdateWindow();*/
	 
	auto usemapframe = new UseMapFrame();
	usemapframe->Create(NULL, _T("CUSTOMFRAME"));
	
	return TRUE;
}

CreateWin32ToMFC theApp;

LRESULT mfcFrame::WindowProc(UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_CREATE:
		AfxMessageBox(_T("WM_CREATE��Ϣ����"));
		break;
	}
	return CFrameWnd::WindowProc(msgID, wParam, lParam);
}

/**
* �����ִ�����̣�
* 1. ����ȫ�ֶ���theApp����ȡ���ַ
* 2. ����theApp����InitAppllication����ʼ����ǰӦ�ó��������
* 3. ����theApp����InitInstance��������д�˸ú������Ϳ����ں����д������ǵĴ��ڲ���ʾ
* 4. ����theApp����CWinApp��Run����������Ϣѭ��
* 5. û����Ϣʱ���п��д���
* 6. �����˳�ʱ������theApp����ExitInstance�麯��ʵ���˳�ǰ���ƺ�����
*/

///�������ϵĴ�����ͨ����дWindowProc����ȥ������Ϣ�ģ���win32�е���Ϣ�������û������ֻ����mfc��ʹ����ʵ���;��˫��󶨣�ʵ��һ��ʵ�������ڵĹ���

BEGIN_MESSAGE_MAP(UseMapFrame, CFrameWnd)
	//ON_MESSAGE(WM_CREATE,OnMyCreate)
	ON_WM_CREATE()//��������WM_CREATE�ı�׼��Ϣӳ���
	ON_MESSAGE(MY_MESSAGE, OnMyMessage)
END_MESSAGE_MAP()

//����ON_MESSAGE����ͨ����չ�����������_messageEntries��Ա��ON_MESSAGE��ʽΪ��ON_MESSAGE(message, memberFxn)
//չ����Ϊ��{ message, 0, 0, 0, AfxSig_lwl,(AFX_PMSG)(AFX_PMSGW)(static_cast< LRESULT (AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM) > (memberFxn)) }	  ����message�β�Ϊ��ϢID������WM_CREATE
//��ϵͳ������WM_CREATE��Ϣʱ�����Ƚ���AfxWndProc��������������֪�Ĵ��ھ�����ҵ���������һ��Ŀ��������ַpFrame���������麯��WindowProc�����Ų�����WM_CREATE��Ϣ�������в���ƥ������ĵ�һ��Ԫ�أ������Ҳ����Ҹ��࣬�����Ҳ�����үү�ֱ࣬���ҵ�WM_CREATE��Ϣ���ڵ��Ǹ����飬�����Ǹ������е����һ��Ԫ�أ����һ��Ԫ�ض�Ӧ���Ǹ���Ϣ����Ϣ��������������֮�������Ϣ�Ĵ���
//�����������Ҳ�����Ԫ��ʱ���͵���ϵͳ��Ĭ�ϴ�������

LRESULT UseMapFrame::OnMyCreate(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T("OnMyCreate"));
	return 0;
}

int UseMapFrame::OnCreate(LPCREATESTRUCT tag)
{
	AfxMessageBox(_T("OnCreate"));
	::PostMessage(GetSafeHwnd()/*this->m_hWnd*/, MY_MESSAGE, NULL, NULL);
	return CFrameWnd::OnCreate(tag);
}

/**
* ��Ϣ�ķ��ࣺ
* 1. ��׼windows��Ϣ    ->   ʹ�ú꣺ON_WM_****  �磺ON_WM_CREATE ON_WM_SETCURSOR
* 2. �Զ�����Ϣ         ->   ʹ�ú꣺ON_MESSAGE
* 3. ������Ϣ           ->   ʹ�ú꣺ON_COMMAND
*/

LRESULT UseMapFrame::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	OutputDebugString(_T("�������Զ�����Ϣ����������Ϣ��������"));
	return 0;
}