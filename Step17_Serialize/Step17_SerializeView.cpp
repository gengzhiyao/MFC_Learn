
// Step17_SerializeView.cpp: CStep17SerializeView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Step17_Serialize.h"
#endif

#include "Step17_SerializeDoc.h"
#include "Step17_SerializeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStep17SerializeView

IMPLEMENT_DYNCREATE(CStep17SerializeView, CView)

BEGIN_MESSAGE_MAP(CStep17SerializeView, CView)
END_MESSAGE_MAP()

// CStep17SerializeView 构造/析构

CStep17SerializeView::CStep17SerializeView() noexcept
{
	// TODO: 在此处添加构造代码

}

CStep17SerializeView::~CStep17SerializeView()
{
}

BOOL CStep17SerializeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CStep17SerializeView 绘图

void CStep17SerializeView::OnDraw(CDC* /*pDC*/)
{
	CStep17SerializeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CStep17SerializeView 诊断

#ifdef _DEBUG
void CStep17SerializeView::AssertValid() const
{
	CView::AssertValid();
}

void CStep17SerializeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStep17SerializeDoc* CStep17SerializeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStep17SerializeDoc)));
	return (CStep17SerializeDoc*)m_pDocument;
}
#endif //_DEBUG


// CStep17SerializeView 消息处理程序
