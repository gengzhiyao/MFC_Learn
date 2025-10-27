﻿#include "pch.h"
#include "framework.h"
#include "Adder.h"
#include "AdderDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAdderDlg 对话框



CAdderDlg::CAdderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDER_DIALOG, pParent)
	, m_editsummed(0)
	, m_editappend(0)
	, m_editsum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdderDlg::DoDataExchange(CDataExchange* pDX)
{
	//处理MFC默认的数据交换
	CDialogEx::DoDataExchange(pDX);
	//处理控件IDC_SUMMED_EDIT和变量m_editsummed之间的数据交换
	DDX_Text(pDX, IDC_SUMMED_EDIT, m_editsummed);
	//处理控件IDC_APPEND_EDIT和变量m_editappend之间的数据交换
	DDX_Text(pDX, IDC_APPEND_EDIT, m_editappend);
	//处理控件IDC_SUM_EDIT和变量m_editsum之间的数据交换
	DDX_Text(pDX, IDC_SUM_EDIT, m_editsum);
}

BEGIN_MESSAGE_MAP(CAdderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUM_BUTTON, &CAdderDlg::OnBnClickedSumButton)
END_MESSAGE_MAP()


// CAdderDlg 消息处理程序

BOOL CAdderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_pTipDlg = nullptr;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAdderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAdderDlg::OnPaint()
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
HCURSOR CAdderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAdderDlg::OnBnClickedSumButton()
{
	///消息对话框messagebox的返回值是用户所点击的按钮的对应的ID值
	/*INT_PTR nRes;
	CTipDlg tipDlg;
	nRes = tipDlg.DoModal();
	if (nRes==IDCANCEL)
	{
		return;
	}以上代码创建了模态对话框
	*/

	//以下代码实现非模态对话框
	if (m_pTipDlg == nullptr)
	{
		m_pTipDlg = new CTipDlg();
		m_pTipDlg->Create(IDD_TIPS_DIALOG, this);
	}
	m_pTipDlg->ShowWindow(SW_SHOW);
	// Updatedata仅处理已绑定到成员变量的控件   绑定：通过DDX_*宏与成员变量关联
	UpdateData(TRUE);
	m_editsum = m_editsummed + m_editappend;
	UpdateData(FALSE);
}

CAdderDlg::~CAdderDlg(){
	if (!m_pTipDlg)
	{
		delete m_pTipDlg;
	}
	
}