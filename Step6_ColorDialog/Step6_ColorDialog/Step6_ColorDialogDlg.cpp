
// Step6_ColorDialogDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Step6_ColorDialog.h"
#include "Step6_ColorDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStep6ColorDialogDlg 对话框



CStep6ColorDialogDlg::CStep6ColorDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STEP6_COLORDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStep6ColorDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStep6ColorDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COLOR_BUTTON, &CStep6ColorDialogDlg::OnBnClickedColorButton)
END_MESSAGE_MAP()


// CStep6ColorDialogDlg 消息处理程序

BOOL CStep6ColorDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStep6ColorDialogDlg::OnPaint()
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
HCURSOR CStep6ColorDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CStep6ColorDialogDlg::OnBnClickedColorButton()
{
	COLORREF color = RGB(255, 0, 0);
	CColorDialog colorDlg(color);
	if (colorDlg.DoModal()==IDOK)
	{
		color = colorDlg.GetColor();
		SetDlgItemInt(IDC_R_EDIT, GetRValue(color));
		SetDlgItemInt(IDC_G_EDIT, GetGValue(color));
		SetDlgItemInt(IDC_B_EDIT, GetBValue(color));
		SetDlgItemInt(IDC_Color_EDIT, color);
		//以上将颜色按照十进制进行输出，接下来我采用16进制输出
		CString colorFormat; colorFormat.Format(_T("#%06X"), color); SetDlgItemText(IDC_Color_EDIT, colorFormat);
	}
}
