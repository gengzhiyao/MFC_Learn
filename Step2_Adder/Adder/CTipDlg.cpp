// CTipDlg.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "CTipDlg.h"
#include "resource.h"


// CTipDlg 对话框

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIPS_DIALOG, pParent)
{

}

CTipDlg::~CTipDlg()
{
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
END_MESSAGE_MAP()


// CTipDlg 消息处理程序
