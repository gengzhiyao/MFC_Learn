#pragma once
#include "afxdialogex.h"


// CConfirmPage 对话框

class CConfirmPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CConfirmPage)

public:
	CConfirmPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CConfirmPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
};
