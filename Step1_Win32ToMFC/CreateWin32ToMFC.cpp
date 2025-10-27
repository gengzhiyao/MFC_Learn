#include <afxwin.h>
#include "CreateWin32ToMFC.h"

#define MY_MESSAGE WM_USER+1001
/// @brief 从空项目创建MFC应用程序

CreateWin32ToMFC::CreateWin32ToMFC()
{
}

BOOL CreateWin32ToMFC::InitInstance()
{
	/*mfcFrame* customFrame = new mfcFrame();
	customFrame->Create(NULL, _T("CUSTOMFRAME"));
	m_pMainWnd = customFrame;///m_pMainWnd当前应用程序的主窗口
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
		AfxMessageBox(_T("WM_CREATE消息产生"));
		break;
	}
	return CFrameWnd::WindowProc(msgID, wParam, lParam);
}

/**
* 程序的执行流程：
* 1. 构造全局对象theApp，获取其地址
* 2. 利用theApp调用InitAppllication，初始化当前应用程序的数据
* 3. 利用theApp调用InitInstance，我们重写了该函数，就可以在函数中创建我们的窗口并显示
* 4. 利用theApp调用CWinApp的Run函数进行消息循环
* 5. 没有消息时进行空闲处理
* 6. 程序退出时，利用theApp调用ExitInstance虚函数实现退出前的善后处理工作
*/

///我们以上的代码是通过重写WindowProc函数去处理消息的，跟win32中的消息处理基本没有区别，只是在mfc中使用了实例和句柄双向绑定，实现一个实例代表窗口的功能

BEGIN_MESSAGE_MAP(UseMapFrame, CFrameWnd)
	//ON_MESSAGE(WM_CREATE,OnMyCreate)
	ON_WM_CREATE()//这是以上WM_CREATE的标准消息映射宏
	ON_MESSAGE(MY_MESSAGE, OnMyMessage)
END_MESSAGE_MAP()

//以上ON_MESSAGE代码通过宏展开后是数组的_messageEntries成员，ON_MESSAGE形式为：ON_MESSAGE(message, memberFxn)
//展开后为：{ message, 0, 0, 0, AfxSig_lwl,(AFX_PMSG)(AFX_PMSGW)(static_cast< LRESULT (AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM) > (memberFxn)) }	  其中message形参为消息ID，比如WM_CREATE
//当系统产生了WM_CREATE消息时，会先进入AfxWndProc处理函数，根据已知的窗口句柄，找到和它绑定在一起的框架类对象地址pFrame，并调用虚函数WindowProc，拿着产生的WM_CREATE消息在数组中查找匹配数组的第一个元素，本类找不到找父类，父类找不到找爷爷类，直到找到WM_CREATE消息所在的那个数组，调用那个数组中的最后一个元素，最后一个元素对应的是该消息的消息处理函数，并调用之，完成消息的处理。
//当在数组中找不到该元素时，就调用系统的默认处理函数。

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
* 消息的分类：
* 1. 标准windows消息    ->   使用宏：ON_WM_****  如：ON_WM_CREATE ON_WM_SETCURSOR
* 2. 自定义消息         ->   使用宏：ON_MESSAGE
* 3. 命令消息           ->   使用宏：ON_COMMAND
*/

LRESULT UseMapFrame::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	OutputDebugString(_T("发送了自定义消息，进入了消息处理函数！"));
	return 0;
}