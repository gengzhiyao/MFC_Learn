// StartDlg.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "StartDlg.h"
#include "resource.h"

// StartDlg 对话框

IMPLEMENT_DYNAMIC( StartDlg, CDialog )

StartDlg::StartDlg( CWnd* pParent /*=nullptr*/ )
    : CDialog( IDD_StartDlg, pParent )
{
}

StartDlg::~StartDlg( ) {}

void StartDlg::DoDataExchange( CDataExchange* pDX ) { CDialog::DoDataExchange( pDX ); }

BEGIN_MESSAGE_MAP( StartDlg, CDialog )
END_MESSAGE_MAP( )

// StartDlg 消息处理程序
