#pragma once
#include <afxctl.h>    ///自己添加，不然报错
#ifdef _WIN32_WCE
#error "Windows CE 不支持 COlePropertyPage。"
#endif 

// CSummandPage: 属性页对话框

class CSummandPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSummandPage)

// 构造函数
public:
	CSummandPage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUMMED };
#endif

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);        // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
public:
};
