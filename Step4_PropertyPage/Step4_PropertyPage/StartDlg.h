#pragma once
#include "afxdialogex.h"

// StartDlg 对话框

class StartDlg : public CDialog
{
    DECLARE_DYNAMIC( StartDlg )

public:
    StartDlg( CWnd* pParent = nullptr );   // 标准构造函数
    virtual ~StartDlg( );

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum
    {
        IDD = IDD_StartDlg
    };
#endif

protected:
    virtual void DoDataExchange( CDataExchange* pDX );    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP( )
};
