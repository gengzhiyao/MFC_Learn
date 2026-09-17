
// Step17_SerializeDoc.cpp: CStep17SerializeDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Step17_Serialize.h"
#endif

#include "Step17_SerializeDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStep17SerializeDoc

IMPLEMENT_DYNCREATE( CStep17SerializeDoc, CDocument )

BEGIN_MESSAGE_MAP( CStep17SerializeDoc, CDocument )
END_MESSAGE_MAP( )

// CStep17SerializeDoc 构造/析构

CStep17SerializeDoc::CStep17SerializeDoc( ) noexcept
{
        // TODO: 在此添加一次性构造代码
}

CStep17SerializeDoc::~CStep17SerializeDoc( ) {}

BOOL CStep17SerializeDoc::OnNewDocument( )
{
    if ( !CDocument::OnNewDocument( ) ) return FALSE;

    return TRUE;
}

// CStep17SerializeDoc 序列化

void CStep17SerializeDoc::Serialize( CArchive& ar )
{
    if ( ar.IsStoring( ) )
    {
        // TODO: 在此添加存储代码
        int a = 1;
        ar << a;
        ar << CString( "just fun" );
    }
    else
    {
        // TODO: 在此添加加载代码
        int a;
        CString s;
        ar >> a;
        ar >> s;
    }
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CStep17SerializeDoc::OnDrawThumbnail( CDC& dc, LPRECT lprcBounds )
{
        // 修改此代码以绘制文档数据
    dc.FillSolidRect( lprcBounds, RGB( 255, 255, 255 ) );

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle( ( HFONT )GetStockObject( DEFAULT_GUI_FONT ) );
    pDefaultGUIFont->GetLogFont( &lf );
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect( &lf );

    CFont* pOldFont = dc.SelectObject( &fontDraw );
    dc.DrawText( strText, lprcBounds, DT_CENTER | DT_WORDBREAK );
    dc.SelectObject( pOldFont );
}

// 搜索处理程序的支持
void CStep17SerializeDoc::InitializeSearchContent( )
{
    CString strSearchContent;
        // 从文档数据设置搜索内容。
        // 内容部分应由“;”分隔

        // 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
    SetSearchContent( strSearchContent );
}

void CStep17SerializeDoc::SetSearchContent( const CString& value )
{
    if ( value.IsEmpty( ) )
    {
        RemoveChunk( PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid );
    }
    else
    {
        CMFCFilterChunkValueImpl* pChunk = nullptr;
        ATLTRY( pChunk = new CMFCFilterChunkValueImpl );
        if ( pChunk != nullptr )
        {
            pChunk->SetTextValue( PKEY_Search_Contents, value, CHUNK_TEXT );
            SetChunkValue( pChunk );
        }
    }
}

#endif // SHARED_HANDLERS

// CStep17SerializeDoc 诊断

#ifdef _DEBUG
void CStep17SerializeDoc::AssertValid( ) const { CDocument::AssertValid( ); }

void CStep17SerializeDoc::Dump( CDumpContext& dc ) const { CDocument::Dump( dc ); }
#endif //_DEBUG

// CStep17SerializeDoc 命令
