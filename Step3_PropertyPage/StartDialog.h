#pragma once
#include "afxctl.h"
#ifdef _WIN32_WCE
#error "Windows CE 不支持 COlePropertyPage。"
#endif 

// StartDialog: 属性页对话框

class StartDialog : public CPropertyPage
{
	DECLARE_DYNCREATE(StartDialog)

// 构造函数
public:
	StartDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
