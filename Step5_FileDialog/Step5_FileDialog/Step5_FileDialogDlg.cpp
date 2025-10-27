
// Step5_FileDialogDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Step5_FileDialog.h"
#include "Step5_FileDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStep5FileDialogDlg 对话框



CStep5FileDialogDlg::CStep5FileDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STEP5_FILEDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStep5FileDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX,)
}

BEGIN_MESSAGE_MAP(CStep5FileDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CStep5FileDialogDlg::OnBnClickedOpenButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CStep5FileDialogDlg::OnBnClickedSaveButton)
END_MESSAGE_MAP()


// CStep5FileDialogDlg 消息处理程序

BOOL CStep5FileDialogDlg::OnInitDialog()
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

void CStep5FileDialogDlg::OnPaint()
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
HCURSOR CStep5FileDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//打开文件
void CStep5FileDialogDlg::OnBnClickedOpenButton()
{
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|All Files(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString filePath;
	if (fileDlg.DoModal() == IDOK)
	{
		filePath = fileDlg.GetPathName();
		//UpdateData(FALSE);前提是使用DDX_*进行了数据绑定
		SetDlgItemText(IDC_OPEN_EDIT, filePath);
	}
}

//保存文件
void CStep5FileDialogDlg::OnBnClickedSaveButton()
{
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|All Files(*.*)|*.*||");
	CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString filePath;

	if (fileDlg.DoModal()==IDOK)
	{
		filePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_SAVE_EDIT, filePath);
	}
}
