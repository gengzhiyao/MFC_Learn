
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

IMPLEMENT_DYNCREATE( CStep18MDIWizardView, CScrollView )

BEGIN_MESSAGE_MAP( CStep18MDIWizardView, CScrollView )
        // 标准打印命令
ON_COMMAND( ID_FILE_PRINT, &CScrollView::OnFilePrint )
ON_COMMAND( ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint )
ON_COMMAND( ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview )
ON_WM_LBUTTONDOWN( )
ON_WM_LBUTTONUP( )
ON_WM_MOUSEMOVE( )
ON_COMMAND( IDS_RECT, &CStep18MDIWizardView::OnSelectRect )
END_MESSAGE_MAP( )

// CStep18MDIWizardView 构造/析构

CStep18MDIWizardView::CStep18MDIWizardView( ) noexcept
    : m_isBeginDraw( false )
{
}

CStep18MDIWizardView::~CStep18MDIWizardView( ) {}

BOOL CStep18MDIWizardView::PreCreateWindow( CREATESTRUCT& cs ) { return CScrollView::PreCreateWindow( cs ); }

// CStep18MDIWizardView 绘图

void CStep18MDIWizardView::OnDraw( CDC* pDC )
{
    CStep18MDIWizardDoc* pDoc = GetDocument( );
    ASSERT_VALID( pDoc );
    if ( !pDoc ) return;

    return CView::OnDraw( pDC );
}

// CStep18MDIWizardView 打印

BOOL CStep18MDIWizardView::OnPreparePrinting( CPrintInfo* pInfo )
{
        // 默认准备
    return DoPreparePrinting( pInfo );
}

void CStep18MDIWizardView::OnBeginPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ ) {}

void CStep18MDIWizardView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ ) {}

void CStep18MDIWizardView::OnInitialUpdate( )
{
    SetScrollSizes( MM_TEXT, CSize( 1000, 1000 ) );
    return CScrollView::OnInitialUpdate( );
}

void CStep18MDIWizardView::OnSelectRect( )
{
    // Do
}

// CStep18MDIWizardView 诊断

#ifdef _DEBUG
void CStep18MDIWizardView::AssertValid( ) const { CScrollView::AssertValid( ); }

void CStep18MDIWizardView::Dump( CDumpContext& dc ) const { CScrollView::Dump( dc ); }

CStep18MDIWizardDoc* CStep18MDIWizardView::GetDocument( ) const // 非调试版本是内联的
{
    ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CStep18MDIWizardDoc ) ) );
    return ( CStep18MDIWizardDoc* )m_pDocument;
}
#endif //_DEBUG

// CStep18MDIWizardView 消息处理程序

void CStep18MDIWizardView::OnLButtonDown( UINT nFlags, CPoint point )
{
    SetCapture( );
    m_isBeginDraw = true;
    m_mouseDownPt = point;
    CScrollView::OnLButtonDown( nFlags, point );
}

void CStep18MDIWizardView::OnLButtonUp( UINT nFlags, CPoint point )
{
    ReleaseCapture( );
    m_isBeginDraw = false;
    CScrollView::OnLButtonUp( nFlags, point );
}

void CStep18MDIWizardView::OnMouseMove( UINT nFlags, CPoint point )
{
    CClientDC clientDC( this );
    CPen      pen;
    pen.CreatePen( PS_SOLID, 2, COLORREF( RGB( 255, 0, 0 ) ) );
    CPen* pOldPen = ( CPen* )clientDC.SelectObject( &pen );
    // 设置异或绘图模式：画一次显示，再画一次就擦掉
    int nOldRop = clientDC.SetROP2( R2_XORPEN );
    if ( m_isBeginDraw ) clientDC.Rectangle( m_mouseDownPt.x, m_mouseDownPt.y, point.x, point.y );
    clientDC.SetROP2( nOldRop );
    clientDC.SelectObject( pOldPen );
    pen.DeleteObject( );
    CScrollView::OnMouseMove( nFlags, point );
}
