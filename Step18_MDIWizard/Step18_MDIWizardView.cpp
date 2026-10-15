
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

#include "Shape.h"
#include "cmdobj.h"

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
ON_COMMAND( IDS_CIRCUL, &CStep18MDIWizardView::OnSelectCircle )
ON_COMMAND( IDS_POLYLINE, &CStep18MDIWizardView::OnSelectPolyline )
ON_COMMAND( IDS_TRIANGLE, &CStep18MDIWizardView::OnSelectTriangle )
ON_COMMAND( IDS_LINE, &CStep18MDIWizardView::OnSelectLine )
ON_WM_KEYDOWN( )
ON_WM_LBUTTONDBLCLK( )
END_MESSAGE_MAP( )

// CStep18MDIWizardView 构造/析构

CStep18MDIWizardView::CStep18MDIWizardView( ) noexcept
    : m_oldPt( 0, 0 ),
      m_mouseDownPt( 0, 0 ),
      m_curTool( Shape::None ),
      m_pCurGraph( nullptr )
{
}

CStep18MDIWizardView::~CStep18MDIWizardView( ) {}

BOOL CStep18MDIWizardView::PreCreateWindow( CREATESTRUCT& cs )
{
    // Windows 中维护一批可复用的DC，每次调用 GetDC 都会拿一个，ReleaseDC 归还
    /// 当窗口注册时带 CS_OWNDC 时，表明自己私有 DC ，每次调用 GetDC 时返回同一个DC
    cs.lpszClass = AfxRegisterWndClass( /*CS_OWNDC |*/ CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, NULL, ( HBRUSH )( COLOR_WINDOW + 1 ), NULL );
    return CScrollView::PreCreateWindow( cs );
}

/**
 * --- 滚动与内存 DC 绘图 ---
 * 1. 鼠标响应函数中，得到的鼠标按下的位置是设备坐标，不是逻辑坐标，存储图形时，应该按照逻辑坐标存储
 * 2. GetClientRect 函数得到的是实际窗口的大小，而不是所设置的逻辑坐标系的大小或者显示器的大小
 * 3. GetClipBox 获取到的矩形区域是逻辑坐标系下的矩形区域，意味着已经经过了 LPtoDP 的转换
 * 4. LPtoDP/DPtoLP 两个函数都是 DC 的成员函数，在 Win32 中，也需要 DC 的句柄，没有 DC 就无法调用，因此设置了一个 utils 工具类
 * 5. 注意 dcMemory.SetWindowOrg( rc.left, rc.top ) 设置了内存 DC 的视口原点
 * 6. BitBlt 各参数解释：x/y 图像贴到目标 DC 上的左上角的起始坐标
 *                       width/height 位块传输区域的宽和高
 *                       srcDC 包含了原始图像数据的 DC
 *                       srcx/srcy 从 srcDC 中截取区域的左上角的坐标
 *                       rop 光栅操作码
 * 7. pDC 使用的一直都是逻辑坐标
 */

// CStep18MDIWizardView 绘图

void CStep18MDIWizardView::OnDraw( CDC* pDC )
{
    CStep18MDIWizardDoc* pDoc = GetDocument( );
    ASSERT_VALID( pDoc );
    if ( !pDoc ) return;
#if 0
    CBitmap bmp;
    CRect   clientSize;
    GetClientRect( &clientSize );
    CRect rc;
    pDC->GetClipBox( &rc );
    CDC dcMemory;
    dcMemory.CreateCompatibleDC( pDC );
    bmp.CreateCompatibleBitmap( pDC, /*clientSize.Width( )*/ rc.Width( ), /*clientSize.Height( )*/rc.Height() );
    // CBitmap* pOldBitmap = dcMemory.SelectObject( &bmp );
    CBitmap* pOldBitmap = dcMemory.SelectObject( &bmp );
    dcMemory.SetWindowOrg( rc.left, rc.top );
    // ========== 填充整张位图为纯白色 ==========
    dcMemory.FillSolidRect( /*&clientSize*/&rc , RGB( 255, 255, 255 ) );
    //dcMemory.FillSolidRect( CRect( clientSize.cx,clientSize.cy), RGB( 255, 255, 255 ) );
    for ( auto it : m_graphs )
    {
        it->Draw( &dcMemory );
    }
    // pDC 使用逻辑坐标，那么如果前两个参数为0的话，会将图像贴到左上角，窗口滚动到下面自然看不到
    pDC->BitBlt( rc.left /*0*/, rc.top /*0*/, clientSize.Width( ), clientSize.Height( ), &dcMemory, rc.left, rc.top, SRCCOPY );
    dcMemory.SelectObject( pOldBitmap );
#else
    // --- begin ---
    CSize   clientSize = GetTotalSize( );
    CBitmap cBmp;
    cBmp.CreateCompatibleBitmap( pDC, clientSize.cx, clientSize.cy );

    // 将当前设备坐标转为逻辑坐标
    CRect rc;
    pDC->GetClipBox( &rc );
    CDC dcMemory;
    dcMemory.CreateCompatibleDC( pDC );
    CBitmap* pOldBitmap = dcMemory.SelectObject( &cBmp );
    dcMemory.SetWindowOrg( rc.left, rc.top );
    // ========== 填充整张位图为纯白色 ==========
    dcMemory.FillSolidRect( /*&clientSize*/ &rc, RGB( 255, 255, 255 ) );
    // dcMemory.FillSolidRect( CRect( clientSize.cx,clientSize.cy), RGB( 255, 255, 255 ) );
    for ( auto it : m_graphs )
    {
        it->Draw( &dcMemory );
    }
    pDC->BitBlt( rc.left, rc.top, clientSize.cx, clientSize.cy, &dcMemory, rc.left, rc.top, SRCCOPY );
    dcMemory.SelectObject( pOldBitmap );
    // --- end ---
#endif
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
    if ( m_curTool == Shape::None ) return;
    SetCapture( );

    if ( m_curTool != Shape::Polyline || ( m_curTool == Shape::Polyline && static_cast<GPolyline*>( m_pCurGraph )->m_isEditing == true ) ) // 需要设置 Done
    {
        m_pCurGraph = GraphFactory::GetInstance( ).Create( m_curTool );   // 根据当前点击 创建图形
    }
    utils::DPtoLP( this, point );
    m_pCurGraph->AddVertex( point );
    m_pCurGraph->AddVertex( point );
    m_mouseDownPt = point;
    m_oldPt = point;
    CScrollView::OnLButtonDown( nFlags, point );
}

void CStep18MDIWizardView::OnLButtonUp( UINT nFlags, CPoint point )
{
    if ( m_curTool == Shape::None ) return;
    ReleaseCapture( );
    utils::DPtoLP( this, point );
    m_pCurGraph->m_vertices.back( ) = point;
    if ( m_curTool != Shape::Polyline )
    {
        m_graphs.push_back( m_pCurGraph );
    }
    m_pCurGraph = nullptr;
    CScrollView::OnLButtonUp( nFlags, point );
}

void CStep18MDIWizardView::OnMouseMove( UINT nFlags, CPoint point )
{
    if ( nFlags != MK_LBUTTON && m_curTool == Shape::None ) return;

    CClientDC clientDC( this ); // CDC* pDC = GetDC( );    // pDC = CDC::FromHandle( ::GetDC( this->GetSafeHwnd( ) ) );
    CPen      pen;
    pen.CreatePen( PS_SOLID, 5, COLORREF( RGB( 255, 0, 0 ) ) );
    CPen*   pOldPen = ( CPen* )clientDC.SelectObject( &pen );
    CBrush* pOldBrush = ( CBrush* )clientDC.SelectStockObject( NULL_BRUSH );
    if ( m_pCurGraph )
    {
        utils::DPtoLP( this, point );
        m_pCurGraph->m_vertices.back( ) = point;
        m_pCurGraph->Draw( &clientDC );
    }

    // 设置异或绘图模式：画一次显示，再画一次就擦掉
    // int nOldRop = clientDC.SetROP2( R2_XORPEN );
    // clientDC.Rectangle( m_mouseDownPt.x, m_mouseDownPt.y, m_oldPt.x, m_oldPt.y );
    // clientDC.Rectangle( m_mouseDownPt.x, m_mouseDownPt.y, point.x, point.y );
    // m_oldPt = point;

    // clientDC.SetROP2( nOldRop );
    clientDC.SelectObject( pOldPen );
    clientDC.SelectObject( pOldBrush );
    pen.DeleteObject( );
    Invalidate( TRUE ); // TRUE/FALSE 决定是否擦除背景重绘
    CScrollView::OnMouseMove( nFlags, point );
}

void CStep18MDIWizardView::OnSelectRect( ) { m_curTool = Shape::Rectangle; }
void CStep18MDIWizardView::OnSelectCircle( ) { m_curTool = Shape::Circle; }
void CStep18MDIWizardView::OnSelectPolyline( ) { m_curTool = Shape::Polyline; }
void CStep18MDIWizardView::OnSelectTriangle( ) { m_curTool = Shape::Triangle; }
void CStep18MDIWizardView::OnSelectLine( ) { m_curTool = Shape::Line; }

void CStep18MDIWizardView::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if ( nChar == VK_F5 ) Invalidate( );
    CScrollView::OnKeyDown( nChar, nRepCnt, nFlags );
}

void CStep18MDIWizardView::OnLButtonDblClk( UINT nFlags, CPoint point )
{
    // clang-format of
    if ( m_curTool == Shape::Polyline )
    {
        m_graphs.push_back( m_pCurGraph );
        static_cast<GPolyline*>( m_pCurGraph )->m_isEditing = false;
    }
    // clang-format on
    CScrollView::OnLButtonDblClk( nFlags, point );
}

void CStep18MDIWizardView::utils::LPtoDP( CView* pWnd, CPoint& src )
{
    CClientDC dc( pWnd );
    pWnd->OnPrepareDC( &dc );
    dc.LPtoDP( &src );
}

void CStep18MDIWizardView::utils::DPtoLP( CView* pWnd, CPoint& src )
{
    CClientDC dc( pWnd );
    pWnd->OnPrepareDC( &dc );
    dc.DPtoLP( &src );
}
