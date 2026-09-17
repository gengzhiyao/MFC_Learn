
// Step18_MDIWizardView.cpp: CStep18MDIWizardView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Step18_MDIWizard.h"
#endif

#include "Step18_MDIWizardDoc.h"
#include "Step18_MDIWizardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStep18MDIWizardView

IMPLEMENT_DYNCREATE(CStep18MDIWizardView, CView)

BEGIN_MESSAGE_MAP(CStep18MDIWizardView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CStep18MDIWizardView 构造/析构

CStep18MDIWizardView::CStep18MDIWizardView() noexcept
{
	// TODO: 在此处添加构造代码

}

CStep18MDIWizardView::~CStep18MDIWizardView()
{
}

BOOL CStep18MDIWizardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CStep18MDIWizardView 绘图

void CStep18MDIWizardView::OnDraw(CDC* /*pDC*/)
{
	CStep18MDIWizardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CStep18MDIWizardView 打印

BOOL CStep18MDIWizardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CStep18MDIWizardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CStep18MDIWizardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CStep18MDIWizardView 诊断

#ifdef _DEBUG
void CStep18MDIWizardView::AssertValid() const
{
	CView::AssertValid();
}

void CStep18MDIWizardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStep18MDIWizardDoc* CStep18MDIWizardView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStep18MDIWizardDoc)));
	return (CStep18MDIWizardDoc*)m_pDocument;
}
#endif //_DEBUG


// CStep18MDIWizardView 消息处理程序
