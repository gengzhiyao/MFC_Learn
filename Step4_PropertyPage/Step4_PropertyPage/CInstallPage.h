#pragma once
#include "afxdialogex.h"


// CInstallPage 对话框

class CInstallPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CInstallPage)

public:
	CInstallPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInstallPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
