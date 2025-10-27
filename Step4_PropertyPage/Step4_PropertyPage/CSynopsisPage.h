#pragma once
#include "afxdialogex.h"


// CSynopsisPage 对话框

class CSynopsisPage : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CSynopsisPage)

public:
	CSynopsisPage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSynopsisPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYNOPSIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
