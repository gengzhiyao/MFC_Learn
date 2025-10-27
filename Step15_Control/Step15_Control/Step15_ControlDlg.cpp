
// Step15_ControlDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Step15_Control.h"
#include "Step15_ControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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


// CStep15ControlDlg 对话框



CStep15ControlDlg::CStep15ControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STEP15_CONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStep15ControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	DDX_Control(pDX, IDC_CHECK1, m_checkBox);
	DDX_Control(pDX, IDC_COMBO1, m_comboBox1);
	DDX_Control(pDX, IDC_COMBO2, m_comboBox2);
	DDX_Control(pDX, IDC_COMBO3, m_comboBox3);
	DDX_Control(pDX, IDC_COMBO_ListCtl, m_cbListCtl);
	DDX_Control(pDX, IDC_LIST1, m_listCtl);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CStep15ControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CStep15ControlDlg::OnClickedButton1)
	ON_BN_DOUBLECLICKED(IDC_BUTTON1, &CStep15ControlDlg::OnDoubleclickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CStep15ControlDlg::OnClickedCheck1)
	ON_CBN_SELCHANGE(IDC_COMBO_ListCtl, &CStep15ControlDlg::OnSelchangeComboListctl)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CStep15ControlDlg::OnDblclkList1)
END_MESSAGE_MAP()


// CStep15ControlDlg 消息处理程序

BOOL CStep15ControlDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	m_btn.MoveWindow(0, 0, 200, 100);

	///brief:为combobox添加选项
	for (int i = 0; i < 20; i++)
	{
		char comboxItem[256];
		sprintf_s(comboxItem, "ItemName%d", i);
		m_comboBox1.AddString(comboxItem);
		m_comboBox2.AddString(comboxItem);
		m_comboBox3.AddString(comboxItem);

	}

	m_cbListCtl.AddString("图标");
	m_cbListCtl.AddString("小图标");
	m_cbListCtl.AddString("列表");
	m_cbListCtl.AddString("报表");
	m_cbListCtl.SetCurSel(0);

	//为报表添加列名
	m_listCtl.InsertColumn(0, "名称", LVCFMT_LEFT, 150);
	m_listCtl.InsertColumn(1, "修改日期", LVCFMT_LEFT, 150);
	m_listCtl.InsertColumn(2, "文件类型", LVCFMT_LEFT, 150);
	m_listCtl.SetExtendedStyle(LVS_EX_GRIDLINES);//添加了经纬线，更像一个数据表格

	CImageList* pImgLst = new CImageList;
	pImgLst->Create(IDB_BITMAP1, 24, 1, RGB(255,255,255));
	m_listCtl.SetImageList(pImgLst,LVSIL_NORMAL);//将图标应用在图标风格上

	//添加选项
	m_listCtl.InsertItem(0, "目录", 0);
	m_listCtl.SetItemText(0, 1, "2025.8.31"); 
	m_listCtl.SetItemText(0, 2, "txt");
	m_listCtl.InsertItem(1, "文件", 1); 

	//***********************树形图*************************
	HTREEITEM root = m_tree.InsertItem("这是根节点，双击显示子节点", 0, 0, NULL);
	m_tree.InsertItem("这是由root管理的从属根节点的节点", 0, 0, root);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStep15ControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStep15ControlDlg::OnPaint()
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
HCURSOR CStep15ControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CStep15ControlDlg::OnClickedButton1()
{
	m_checkBox.SetCheck(!m_checkBox.GetCheck());
}

void CStep15ControlDlg::OnDoubleclickedButton1()
{
	AfxMessageBox(_T("鼠标双击，注意开启按钮的Notyfy属性"));
}

void CStep15ControlDlg::OnClickedCheck1()
{
	/// checkbox也有点击消息，在属性中设置推送外观试试，看会发生什么
}

void CStep15ControlDlg::OnSelchangeComboListctl()
{
	switch (m_cbListCtl.GetCurSel())
	{
	case 0://图标
		m_listCtl.ModifyStyle(LVS_SMALLICON | LVS_LIST | LVS_REPORT, LVS_ICON);
		break;
	case 1://小图标
		m_listCtl.ModifyStyle(LVS_ICON | LVS_LIST | LVS_REPORT, LVS_SMALLICON);
		break;
	case 2://列表
		m_listCtl.ModifyStyle(LVS_SMALLICON | LVS_ICON | LVS_REPORT, LVS_LIST);
		break;
	case 3://报表
		m_listCtl.ModifyStyle(LVS_SMALLICON | LVS_LIST | LVS_ICON, LVS_REPORT);
		break;
	}
}

void CStep15ControlDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);//自动生成，得到双击的选项
	//双击了某项数据之后，你去得到选项的附加数据，就可以干别的事了
	AfxMessageBox("双");
	*pResult = 0;
}


