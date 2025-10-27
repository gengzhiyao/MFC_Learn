
// Step15_Control.cpp: 定义应用程序的类行为。
//

/**
* 控件和对象的绑定：
* 对象分为两种，分别是数据类对象和控制类对象，因此有控件和数据类对象绑定、控件和控件类对象绑定
* 1. 数据类对象如CString，int等类型，这种绑定一般涉及到数据交换，使用DDX_***进行绑定，使用UpdateData(TRUE/FALSE)进行数据交换,TRUE是向数据类对象传递数据，FALSE是向控件类传递数据，控件和数据类型绑定无非就是做他们之间的数据交换
* 2. 控件类对象和控件进行绑定，使用DDX_Control等进行绑定，绑定之后处理消息
*/

//在处理控件的消息时，要注意使用什么样的宏处理消息，比如处理按钮的点击消息，可以使用ON_COMMAND(IDC_BUTTON1,OnClick),但推荐使用ON_BN_CLICKED,推荐使用类向导生成

#include "pch.h"
#include "framework.h"
#include "Step15_Control.h"
#include "Step15_ControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStep15ControlApp

BEGIN_MESSAGE_MAP(CStep15ControlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CStep15ControlApp 构造

CStep15ControlApp::CStep15ControlApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CStep15ControlApp 对象

CStep15ControlApp theApp;


// CStep15ControlApp 初始化

BOOL CStep15ControlApp::InitInstance()
{
	CWinApp::InitInstance();


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CStep15ControlDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

//对于RadioBox，默认不可创建控件对象，在属性中，更改其组为true，在类向导中就能为其添加控件对象了，它属于CButton类。因为这种控件一旦出现，就一般是成组出现的，比如男女

///IDC_STATIC这个ID比较特殊，一旦对应着一个UI控件，那么这个控件在类向导的成员变量中将不会存在  静态控件对应CStatic类型

///MFC思想，创建控件资源的时候都有一个ID，用这个ID代表各种UI资源，如对话框，按钮等等，在程序中将该ID与控件类型进行绑定，该控件类型就能够代表这个资源了

///Combobox三种风格；通过AddString添加，DeleteString删除，获取选项索引：GetSurSel()，设置索引项GetSurSel()，获取选项内容GetLBText，SetLBData，GetItemData

///combobox的command消息：文本内容改变消息和选项改变消息

///ListBox和ComboBox差不多，只是没有了那个选项头

///滑块和进度条

///文件搜索类：CFileFind类，封装了关于文件遍历的各种操作，可以在某个目录中寻找某个文件
///CFileFind::FindFile   CFileFind::FindNextFile（找到当前文件，并判断下一个文件是否存在）  CFileFind::GetXXX
/// CFileFind::IsXXX  IsDirectory判断是否是目录  CFileFind::Close

/// ListControl 类似文件资源管理器，有多种显示资源的风格，如小图标，列表，报表等