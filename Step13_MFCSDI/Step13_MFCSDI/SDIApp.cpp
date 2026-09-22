#include "SDIApp.h"
#include "resource.h"
#include "CMyStroke.h"

// App::m_pDocManager(CDocManager) ->
BOOL SDIApp::InitInstance( )
{
    /// 文档模板中存放了与文档视图和框架相关的信息，应用程序通过文档模板创建文档对象，框架窗口和视图对象
    CSingleDocTemplate* pTemplte = new CSingleDocTemplate( IDR_MENU1, RUNTIME_CLASS( CMyDoc ), RUNTIME_CLASS( CMyFrame ), RUNTIME_CLASS( CMyView ) );
    AddDocTemplate( pTemplte );
    OnFileNew( );
    m_pMainWnd->ShowWindow( SW_SHOW );
    m_pMainWnd->UpdateWindow( );
    return TRUE;
}

SDIApp theApp;

void CMyView::OnDraw( CDC* pDC )
{
    pDC->TextOut( 100, 100, _T("我是视图窗口") );
    if ( m_isDrawing )
    {
        CPen pen( PS_SOLID, 10, COLORREF( RGB(255,0,0) ) );
        CRect clientRc;
        GetClientRect( &clientRc );
        CBitmap cacheBitmap;
        cacheBitmap.CreateCompatibleBitmap( pDC, clientRc.Width( ), clientRc.Height( ) );
        CDC memoryDC;
        memoryDC.CreateCompatibleDC( pDC );
        memoryDC.SelectObject( &cacheBitmap );
        memoryDC.PatBlt( 0, 0, clientRc.Width( ), clientRc.Height( ), WHITENESS );
        memoryDC.SelectObject( &pen );
        CFont font;
        font.CreatePointFont( 2000, _T("微软雅黑") );
        memoryDC.SelectObject( &font );
        memoryDC.SetTextColor( RGB( 0, 255, 0 ) );
        memoryDC.TextOut( 100, 100, _T("我是内存中的视图窗口") );
        //memoryDC.BeginPath( );
        for ( const auto& stroke : m_strokeArray )
        {
            for ( int i = 0; i < stroke->GetSize( ) - 1; i++ )
            {
                if ( i == 0 ) 
                    memoryDC.MoveTo( stroke->GetStrokePt( i ) );
                memoryDC.LineTo( stroke->GetStrokePt( i + 1 ) );
            }
        }
        //memoryDC.EndPath( );
        //memoryDC.StrokePath( );
        pDC->BitBlt( 0, 0, clientRc.Width( ), clientRc.Height( ), &memoryDC, 0, 0, SRCCOPY );
    }
}

CMyView::~CMyView( )
{
    for ( auto p : m_strokeArray )
    {
        delete p;
    }
}

/// MFC中，应用程序类处理的消息是ONCOMMAND，其他消息基本到不了这里
BEGIN_MESSAGE_MAP( CMyFrame, CFrameWnd )
ON_WM_CREATE( )
END_MESSAGE_MAP( )

int CMyFrame::OnCreate( LPCREATESTRUCT cs )
{
    OutputDebugString( L">>>>>>>>CMyFrame::OnCreate\n" );
    return CFrameWnd::OnCreate( cs );
}
BEGIN_MESSAGE_MAP( CMyView, CView )
ON_WM_LBUTTONDOWN( )
ON_WM_MOUSEMOVE( )
ON_WM_LBUTTONUP( )
END_MESSAGE_MAP( )

void CMyView::OnLButtonDown( UINT nFlags, CPoint point )
{
    m_flag = 0x01;
    CMyStroke* stroke = new CMyStroke;
    stroke->PrePoint( point );
    m_strokeArray.push_back( stroke );
    CView::OnLButtonDown( nFlags, point );
}

void CMyView::OnMouseMove( UINT nFlags, CPoint point )
{
    if ( m_flag == 0x01 )
    {
        m_isDrawing = true;
        m_strokeArray.back( )->Store( point );
        m_prePos = m_strokeArray.back( )->GetPrePt( );
        CClientDC dc( this );
        dc.MoveTo( m_prePos );
        dc.LineTo( point );
        m_strokeArray.back( )->SetPrePt( point );
    }
    CView::OnMouseMove( nFlags, point );
}

void CMyView::OnLButtonUp( UINT nFlags, CPoint point )
{
    m_flag = 0x00;
    CView::OnLButtonUp( nFlags, point );
}
