
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

CStep18MDIWizardView::~CStep18MDIWizardView( )
{
}

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
 * 5. 注意 dcMemory.SetViewportOrg( left, top ) 设置了内存 DC 的视口原点
 * 6. BitBlt 各参数解释：x/y 图像贴到目标 DC 上的左上角的起始坐标
 *                       width/height 位块传输区域的宽和高
 *                       srcDC 包含了原始图像数据的 DC
 *                       srcx/srcy 从源DC srcDC 中截取区域的左上角的坐标
 *                       rop 光栅操作码
 * 7. pDC 使用的一直都是逻辑坐标
 *
 * !重要：
 * 区分：逻辑坐标系/设备坐标系/视口坐标系
 * 其实视口坐标系并不是真正的坐标系，它是一个桥梁，决定了逻辑坐标和设备坐标的映射关系
 * 所有的坐标变换更改的都是只更改视口原点，可以想象为视口坐标的原点发生了变化，但是逻辑坐标系的逻辑原点是稳定不动的
 * 假如说将内存 DC 的视口原点设置为当前视口原点(org.x,org.y)，而内存 DC 的逻辑坐标不变，可以想象从视口坐标上看，图形全都会往右下偏移(org.x,org.y)
 *
 * 假如：1. 现在保存了图形的实际逻辑坐标是(100,200)
 *       2. 窗口往下往右滚动了(100,200) 那么 pDC->GetViewportOrg( ) =  (-100,-200)
 *       3. 图形在绘制时：还是会绘制在逻辑坐标系的(100,200)处，永远不变!!!
 *              情况A: 内存DC不设置视口原点，默认为(0,0)，那么图形还是会画在内存 DC 的(100,200)处，因为内存 DC 的坐标原点就是逻辑坐标原点
 *              内存位图物理像素 = 逻辑坐标 + 视口原点
 *              情况B: 内存DC设置视口原点为(org.x,org.y)，但是由于逻辑坐标原点不变，还是会绘制在(100,200)处，但是会绘制到内存位图的(0,0)点处，至于如何显示，要看Bitblt的规则
 *       4. 内存 DC 创建的位图的 (0,0) 像素点是和 *设备坐标* 的原点对应的
 */

// CStep18MDIWizardView 绘图

// 视口原点的概念：指的是窗口的逻辑坐标的原点映射到设备坐标上的位置

void CStep18MDIWizardView::OnDraw( CDC* pDC )
{
    CStep18MDIWizardDoc* pDoc = GetDocument( );
    ASSERT_VALID( pDoc );
    if ( !pDoc )
        return;
#if 1
    CBitmap bmp;
    CRect   clientSize;
    GetClientRect( &clientSize );
    CRect rc;
    pDC->GetClipBox( &rc );
    CDC dcMemory;
    dcMemory.CreateCompatibleDC( pDC );
    bmp.CreateCompatibleBitmap( pDC, clientSize.Width( ), clientSize.Height( ) );
    CBitmap* pOldBitmap = dcMemory.SelectObject( &bmp );
    // ========== 填充整张位图为纯白色 ==========
    // dcMemory.FillSolidRect( &rc, RGB( 255, 255, 255 ) );    // 创建出来的位图只有800*600 而rc又是逻辑坐标，其他区域填充不到 放在下面就好了
    // 让内存 DC 的坐标系和屏幕 DC 一致
    // OnPrepareDC中更改了屏幕 DC 的滚动方向，新建立的内存 DC 没有，所以要实时同步
    CPoint p = pDC->GetViewportOrg( );
    dcMemory.SetViewportOrg( p );
    dcMemory.FillSolidRect( &rc, RGB( 255, 255, 255 ) );
    for ( auto it : m_graphs )
    {
        it->Draw( &dcMemory );
    }
    // pDC 使用逻辑坐标，那么如果前两个参数为0的话，会将图像贴到左上角，窗口滚动到下面自然看不到
    pDC->BitBlt( rc.left, rc.top, clientSize.Width( ), clientSize.Height( ), &dcMemory, rc.left, rc.top, SRCCOPY );
    dcMemory.SelectObject( pOldBitmap );
#else
    #if 1
    CSize   clientRect = GetTotalSize( );
    CBitmap cBmp;
    cBmp.CreateCompatibleBitmap( pDC, clientRect.cx, clientRect.cy );
    CRect rc;
    pDC->GetClipBox( &rc ); // 在这之前调用 Invalidate 将客户区标记为无效区域，那么他返回的就是客户区的逻辑坐标
    CDC dcMemory;
    dcMemory.CreateCompatibleDC( pDC );
    CBitmap* pOldBitmap = dcMemory.SelectObject( &cBmp );
    dcMemory.FillSolidRect( &rc, RGB( 255, 255, 255 ) );
    // --- begin ---
    for ( auto it : m_graphs )
    {
        it->Draw( &dcMemory );
    }
    pDC->BitBlt( rc.left, rc.top, clientRect.cx, clientRect.cy, &dcMemory, rc.left, rc.top, SRCCOPY );
    dcMemory.SelectObject( pOldBitmap );
    // --- end ---
    #else
    CSize   cSize = GetTotalSize( );
    CBitmap cBmp;
    cBmp.CreateCompatibleBitmap( pDC, cSize.cx, cSize.cy ); // 位图没有坐标原点的概念，只有像素点的概念，可以认为位图永远是以坐标 (0,0) 为原点，所以设置的大一点
    CDC dcMemory;
    dcMemory.CreateCompatibleDC( pDC );
    CBitmap* pOldBitmap = dcMemory.SelectObject( &cBmp );
    CRect    rect( 0, 0, cSize.cx, cSize.cy );
    dcMemory.FillSolidRect( &rect, RGB( 255, 255, 255 ) );
    // --- begin ---
    // SetViewportOrg 指定了逻辑坐标系中的原点对应到设备坐标系中的哪个点，并且在设置之后，后续所有的绘图操作都会以该点为基准点
    // 设置了SetViewportOrg(x,y)之后，TextOut(0,0,...) 就会在屏幕的(x,y)处输出文件
    // 这也就意味着，当TextOut(0,0)时，会在屏幕的(x,y)处开始绘制
    // 一定记住：位图的(0,0)像素点和设备坐标点永远一致
    // 如果切换到位图中输出文字 TextOut(0,0)，那么会在位图的(x,y)处输出文字。因而有以下公式：
    // 位图像素点的坐标 = 逻辑坐标 + 视口原点 就是这么来的
    CPoint org = pDC->GetViewportOrg( );
        #ifdef SET_VIEWPORT
    dcMemory.SetViewportOrg( org.x, org.y );    // 将逻辑坐标系的原点映射到内存 DC 的设备坐标的 (org.x, org.y)，后续所有绘图都以此为基准点，绘制到位图中，因为位图的原点和设备坐标永远一致
        #endif
    for ( auto it : m_graphs )
    {
        it->Draw( &dcMemory );  // 将图案绘制逻辑坐标中，那么点 (m,n) 在内存 DC 的位图中对应的像素点就是 (m+org.x,n+org.y)
    }

        #ifdef SET_VIEWPORT
    dcMemory.SetViewportOrg( 0, 0 );
    // BitBlt 的坐标参数说明了从源 DC 的位置 (xSrc,ySrc) 拷贝 Width*Height 个像素到目标 DC 中
    // 分析一下 DC 设置了 ViewPort 之后，为什么要将源 DC 的坐标改为 org.x/y (最好自己手绘一下理解)
    // 1. 设置内存 DC 的视口原点后，意味着所有的逻辑坐标点都需要平移 (org.x,org.y)       ||因为 SetViewportOrg 就是在改变逻辑坐标和设备坐标之间的映射关系
    // 2. 在内存 DC 的位图中绘制图形：图形的顶点是逻辑坐标 -> 逻辑坐标的（0,0)点映射到设备坐标的 (org.x,org.y) 所有的图形都带有偏移量
    // 3. 在 BitBlt 之前将坐标恢复到(0,0)，逻辑坐标点和设备坐标点一致了，但是所绘制的图形仍然在以 (org.x,org.y) 为基准点的位图中
    // 4. 所以裁剪的源 DC 的坐标应该是以 (org.x,org.y) 为基准点
    /// 设备坐标 = (逻辑坐标 - 窗口原点) * 缩放比例 + 视口原点
    pDC->BitBlt( 0, 0, cSize.cx, cSize.cy, &dcMemory, org.x, org.y, SRCCOPY );  // BitBlt 使用逻辑坐标 目标 DC 的 (0,0)对应设备坐标(org.x,org.y)
    // 将源 DC 的逻辑坐标点(xSrc,ySrc) 复制到目标 DC 的逻辑坐标点(xDst,yDst) 中，BitBlt 函数中会再次将逻辑坐标转为设备坐标以确定拷贝的矩形区域
        #else
    pDC->BitBlt( 0, 0, cSize.cx, cSize.cy, &dcMemory, /* org.x*/ 0, /*org.y*/ 0, SRCCOPY );
        #endif
    dcMemory.SelectObject( pOldBitmap );
    // --- end ---
    #endif
#endif
    return CView::OnDraw( pDC );
}

// CStep18MDIWizardView 打印

BOOL CStep18MDIWizardView::OnPreparePrinting( CPrintInfo* pInfo )
{
    // 默认准备
    return DoPreparePrinting( pInfo );
}

void CStep18MDIWizardView::OnBeginPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
}

void CStep18MDIWizardView::OnEndPrinting( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ )
{
}

void CStep18MDIWizardView::OnInitialUpdate( )
{
    SetScrollSizes( MM_TEXT, CSize( 1000, 1000 ) );
    return CScrollView::OnInitialUpdate( );
}

// CStep18MDIWizardView 诊断

#ifdef _DEBUG
void CStep18MDIWizardView::AssertValid( ) const
{
    CScrollView::AssertValid( );
}

void CStep18MDIWizardView::Dump( CDumpContext& dc ) const
{
    CScrollView::Dump( dc );
}

CStep18MDIWizardDoc* CStep18MDIWizardView::GetDocument( ) const // 非调试版本是内联的
{
    ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CStep18MDIWizardDoc ) ) );
    return ( CStep18MDIWizardDoc* )m_pDocument;
}
#endif //_DEBUG

// CStep18MDIWizardView 消息处理程序

void CStep18MDIWizardView::OnLButtonDown( UINT nFlags, CPoint point )
{
    if ( m_curTool == Shape::None )
        return;
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
    if ( m_curTool == Shape::None )
        return;
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
    if ( nFlags != MK_LBUTTON && m_curTool == Shape::None )
        return;

    CClientDC clientDC( this ); // CDC* pDC = GetDC( );    // pDC = CDC::FromHandle( ::GetDC( this->GetSafeHwnd( ) ) );
    CPen      pen;
    pen.CreatePen( PS_SOLID, 5, COLORREF( RGB( 0, 0, 0 ) ) );
    CPen*   pOldPen = ( CPen* )clientDC.SelectObject( &pen );
    CBrush* pOldBrush = ( CBrush* )clientDC.SelectStockObject( NULL_BRUSH );
    if ( m_pCurGraph )
    {
        utils::DPtoLP( this, point );
        CPoint scroPos = GetScrollPosition( );
        clientDC.SetViewportOrg( -scroPos );
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
    Invalidate( FALSE ); // TRUE/FALSE 决定是否擦除背景重绘 双缓冲绘图中，不需要Invalidate擦除背景，因为是一次性拷贝位图，由FillSolidRect擦除背景
    CScrollView::OnMouseMove( nFlags, point );
}

void CStep18MDIWizardView::OnSelectRect( )
{
    m_curTool = Shape::Rectangle;
}
void CStep18MDIWizardView::OnSelectCircle( )
{
    m_curTool = Shape::Circle;
}
void CStep18MDIWizardView::OnSelectPolyline( )
{
    m_curTool = Shape::Polyline;
}
void CStep18MDIWizardView::OnSelectTriangle( )
{
    m_curTool = Shape::Triangle;
}
void CStep18MDIWizardView::OnSelectLine( )
{
    m_curTool = Shape::Line;
}

void CStep18MDIWizardView::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if ( nChar == VK_F5 )
        Invalidate( );
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
