#pragma once

// Step19ActiveXControlCtrl.h : CStep19ActiveXControlCtrl ActiveX 控件类的声明。


// CStep19ActiveXControlCtrl : 请参阅 Step19ActiveXControlCtrl.cpp 了解实现。

class CStep19ActiveXControlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CStep19ActiveXControlCtrl)

// 构造函数
public:
	CStep19ActiveXControlCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CStep19ActiveXControlCtrl();

	DECLARE_OLECREATE_EX(CStep19ActiveXControlCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CStep19ActiveXControlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CStep19ActiveXControlCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CStep19ActiveXControlCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
	};
    afx_msg void OnTimer( UINT_PTR nIDEvent );
        afx_msg int  OnCreate( LPCREATESTRUCT lpCreateStruct );
    afx_msg void OnDestroy( );
};

