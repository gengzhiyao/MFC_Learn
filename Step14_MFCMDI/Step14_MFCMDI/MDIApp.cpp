#include "MDIApp.h"
#include "resource.h"

/**
 * 该程序采用静态连接的方式连接 MFC 在 OnFileNew 中会创建多个文档的选择对话框
 * 该对话框资源在使用静态 MFC 库时不会链接进可执行程序，因此静态链接的方式不会打开对话框，这是一个坑点
 * 如果改用动态 MFC，就可以打开多文档选择对话框
 * 在静态 MFC 下，如果要使用该对话框，需要在 .rc 文件中添加 #include <afxres.h>
 * **并且**需要在资源视图中右键资源，选择资源包括，编译时指令中添加 #include <afxres.rc>
 */

BOOL MDIApp::InitInstance( )
{
    CMultiDocTemplate* pTemplate1 = new CMultiDocTemplate( IDR_MENU2, RUNTIME_CLASS( CMyDoc1 ), RUNTIME_CLASS( CMyChild ), RUNTIME_CLASS( CMyView ) );
    CMultiDocTemplate* pTemplate2 = new CMultiDocTemplate( IDR_MENU3, RUNTIME_CLASS( CMyDoc2 ), RUNTIME_CLASS( CMyChild ), RUNTIME_CLASS( CMyView ) );

    CMyFrame* pFrame = new CMyFrame( );
    pFrame->LoadFrame( IDR_MENU1 );
    m_pMainWnd = pFrame;
    pFrame->ShowWindow( SW_SHOW );
    pFrame->UpdateWindow( );

    AddDocTemplate( pTemplate1 );
    AddDocTemplate( pTemplate2 );
    // OnFileNew( );
    // OnFileNew( );// 每次调用都会创建一个子视图窗口和视图窗口

    return TRUE;
}

BEGIN_MESSAGE_MAP( MDIApp, CWinApp )
ON_COMMAND( ID_NEW, OnFileNew )
ON_COMMAND( ID_OPEN, OnFileOpen )
END_MESSAGE_MAP( )

BEGIN_MESSAGE_MAP( CMyDoc1, CDocument )
ON_COMMAND( ID_SAVE, OnFileSave )

END_MESSAGE_MAP( )

BEGIN_MESSAGE_MAP( CMyFrame, CMDIFrameWnd )
END_MESSAGE_MAP( )

BEGIN_MESSAGE_MAP( CMyView, CView )
ON_WM_LBUTTONDOWN( )
ON_WM_LBUTTONUP( )

ON_COMMAND( ID_DOT, &CMyView::OnDot )
ON_COMMAND( ID_LINE, &CMyView::OnLine )
ON_COMMAND( ID_RECT, &CMyView::OnRect )
ON_COMMAND( ID_ELLIPSE, &CMyView::OnEllipse )
END_MESSAGE_MAP( )

MDIApp theApp;

void CMyView::OnDraw( CDC* pDC )
{
    pDC->TextOut( 100, 100, _T("我是视图窗口") );
    for ( int i = 0; i < m_array.GetCount( ); i++ )
    {
        static_cast<CGraph*>( m_array[i] )->DrawGraph( pDC );
    }
}

void CMyView::OnLButtonDown( UINT key, CPoint downPt )
{
    m_startPt = downPt;
    return CView::OnLButtonDown( key, downPt );
}

void CMyView::OnLButtonUp( UINT key, CPoint upPt )
{
    CClientDC dc( this );
    switch ( m_type )
    {
        case 0:
            dc.SetPixel( upPt, RGB( 0, 0, 0 ) );
            break;
        case 1:
            dc.MoveTo( m_startPt );
            dc.LineTo( upPt );
            break;
        case 2:
            dc.Rectangle( CRect( m_startPt, upPt ) );
            break;
        case 3:
            dc.Ellipse( CRect( m_startPt, upPt ) );
            break;
        default:
            ASSERT( false );
    }
    m_endPt = upPt;
    CGraph* pGraph = new CGraph( m_type, m_startPt, m_endPt );
    m_array.Add( pGraph );
    return CView::OnLButtonUp( key, upPt );
}

CMyView::~CMyView() {
    for ( int i = 0; i < m_array.GetCount(); i++ )
    {
        delete m_array[i];
    }
 }

// CMultiDocTemplate类中有一个成员m_docList保存了多个文档类对象的地址
// theApp中成员m_pDocManager管理文档->m_templateList单文档模板类对象的地址

CMyDoc1::~CMyDoc1( ) { delete m_pStroke; }

 void CMyDoc1::Serialize( CArchive& ar )
 {
    POSITION pos = GetFirstViewPosition( );
    CMyView* view = static_cast<CMyView*>( GetNextView( pos ) );
    if ( ar.IsStoring( ) )
    {
        m_pStroke = new CMyStroke;
        ar.WriteObject( m_pStroke );    // WriteObject -> obj.Serialize
        int nCount =int( view->m_array.GetCount( ));
        ar << nCount;
        for ( int i = 0; i < view->m_array.GetCount( ); i++ )
        {
            ar.WriteObject( view->m_array[i] );
        }
    }
    else
    {
        CMyStroke* m_pStroke = ( CMyStroke* )ar.ReadObject( RUNTIME_CLASS( CMyStroke ) );
        int        nCount;
        ar >> nCount;
        CGraph* graph;
        for ( int i = 0; i < nCount; i++ )
        {
            ar >> graph;
            view->m_array.Add( graph );
        }
    }
}

CGraph::CGraph( char type, CPoint start, CPoint end )
    : m_type( type ),
      m_ptOrigin( start ),
      m_ptEnd( end )
{
}

void CGraph::Serialize( CArchive& ar )
{
    if ( ar.IsStoring( ) )
    {
        ar << m_type << m_ptOrigin << m_ptEnd;
    }
    else
    {
        ar >> m_type >> m_ptOrigin >> m_ptEnd;
    }
}
void CGraph::DrawGraph( CDC* pDC )
{
    switch ( m_type )
    {
        case 0:
            pDC->SetPixel( m_ptEnd, RGB( 0, 0, 0 ) );
            break;
        case 1:
            pDC->MoveTo( m_ptOrigin );
            pDC->LineTo( m_ptEnd );
            break;
        case 2:
            pDC->Rectangle( CRect( m_ptOrigin, m_ptEnd ) );
            break;
        case 3:
            pDC->Ellipse( CRect( m_ptOrigin, m_ptEnd ) );
            break;
        default:
            ASSERT( false );
    }
}
IMPLEMENT_SERIAL( CGraph, CObject, 1 )

void CMyView::OnDot( ) { m_type = 0; }

void CMyView::OnLine( ) { m_type = 1; }

void CMyView::OnRect( ) { m_type = 2; }

void CMyView::OnEllipse( ) { m_type = 3; }
