#pragma once

// Step19ActiveXControlPropPage.h: CStep19ActiveXControlPropPage 属性页类的声明。


// CStep19ActiveXControlPropPage : 请参阅 Step19ActiveXControlPropPage.cpp 了解实现。

class CStep19ActiveXControlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CStep19ActiveXControlPropPage)
	DECLARE_OLECREATE_EX(CStep19ActiveXControlPropPage)

// 构造函数
public:
	CStep19ActiveXControlPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_STEP19ACTIVEXCONTROL };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

