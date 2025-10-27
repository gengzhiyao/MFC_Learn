
// Step7_WidgetsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Step7_Widgets.h"
#include "Step7_WidgetsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWidgetsDlg 对话框



CWidgetsDlg::CWidgetsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STEP7_WIDGETS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CWidgetsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWidgetsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SETCURSOR()//这行将 WM_SETCURSOR 消息映射到 OnSetCursor 函数
END_MESSAGE_MAP()


// CWidgetsDlg 消息处理程序

BOOL CWidgetsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cStatic = new CStatic();
	RECT rect = { 0 };
	rect.left = 10;
	rect.right = 100;
	rect.top = 10;
	rect.bottom = 100;
	cStatic->Create(_T("静态文本框"), WS_VISIBLE|WS_CHILD|SS_NOTIFY, rect, this, NULL);
	m_hCustomCursor = ::LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));
	cStatic->SetCursor(m_hCustomCursor);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWidgetsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWidgetsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CWidgetsDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// 检查是否是我们的静态文本框
	if (pWnd == cStatic && m_hCustomCursor != NULL)
	{
		::SetCursor(m_hCustomCursor);
		return TRUE;
	}

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


