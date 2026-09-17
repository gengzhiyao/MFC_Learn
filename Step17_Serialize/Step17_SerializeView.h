
// Step17_SerializeView.h: CStep17SerializeView 类的接口
//

#pragma once


class CStep17SerializeView : public CView
{
protected: // 仅从序列化创建
	CStep17SerializeView() noexcept;
	DECLARE_DYNCREATE(CStep17SerializeView)

// 特性
public:
	CStep17SerializeDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CStep17SerializeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Step17_SerializeView.cpp 中的调试版本
inline CStep17SerializeDoc* CStep17SerializeView::GetDocument() const
   { return reinterpret_cast<CStep17SerializeDoc*>(m_pDocument); }
#endif

