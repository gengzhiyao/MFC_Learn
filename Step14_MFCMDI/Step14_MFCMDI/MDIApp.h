#pragma once
#include <afxwin.h>

class MDIApp : public CWinApp
{
    BOOL InitInstance( );

    DECLARE_MESSAGE_MAP( )
};

class CMyStroke;

class CMyDoc1 : public CDocument
{
private:
    CMyStroke* m_pStroke;

public:
    CMyDoc1( )
        : m_pStroke( nullptr )
    {
    }
    ~CMyDoc1( );
    virtual void Serialize( CArchive& ar ) override;
    DECLARE_DYNCREATE( CMyDoc1 )
    DECLARE_MESSAGE_MAP( )
};

class CMyDoc2 : public CDocument
{
    DECLARE_DYNCREATE( CMyDoc2 )
};

IMPLEMENT_DYNCREATE( CMyDoc1, CDocument )
IMPLEMENT_DYNCREATE( CMyDoc2, CDocument )

class CMyView : public CView
{
private:
    CPoint m_startPt;
    CPoint m_endPt;
    char   m_type;

public:
    CObArray m_array;

public:
    ~CMyView( );
    virtual void OnDraw( CDC* pDC );
    void         OnLButtonDown( UINT, CPoint );
    void         OnLButtonUp( UINT, CPoint );
    DECLARE_DYNCREATE( CMyView )
    DECLARE_MESSAGE_MAP( )
    afx_msg void OnDot( );
    afx_msg void OnLine( );
    afx_msg void OnRect( );
    afx_msg void OnEllipse( );
};

IMPLEMENT_DYNCREATE( CMyView, CView )

class CMyChild : public CMDIChildWnd
{
    DECLARE_DYNCREATE( CMyChild )
};

IMPLEMENT_DYNCREATE( CMyChild, CMDIChildWnd )

// 父框架不支持动态创建
class CMyFrame : public CMDIFrameWnd
{
    DECLARE_MESSAGE_MAP( )
};

class CMyStroke : public CObject
{
private:
    CString m_str;
    int     m_i;
    CRect   m_rect;

public:
    CMyStroke( )
        : m_str( "This is a test string" ),
          m_i( 4 ),
          m_rect( 0, 0, 10, 10 )
    {
    }
    virtual void Serialize( CArchive& ar ) override;
    // --- DECLARE_SERIAL( CMyStroke ) ---
public:
    static CRuntimeClass    classCMyStroke;
    virtual CRuntimeClass*  GetRuntimeClass( ) const;
    static CObject* PASCAL  CreateObject( );
    friend CArchive& AFXAPI operator>>( CArchive& ar, CMyStroke*& pOb );
    //! --- DECLARE_SERIAL( CMyStroke ) ---
};

// --- IMPLEMENT_SERIAL( CMyStroke,CObject,1 ) ---
CObject* PASCAL CMyStroke::CreateObject( ) { return new CMyStroke; }

AFX_CLASSINIT _init_CMyStroke( ( CRuntimeClass* )( &CMyStroke::classCMyStroke ) );

AFX_COMDAT CRuntimeClass CMyStroke::classCMyStroke = { "CMyStroke", //
                                                       sizeof( class CMyStroke ),
                                                       1,
                                                       CMyStroke::CreateObject,
                                                       ( CRuntimeClass* )( &CObject::classCObject ),
                                                       NULL,
                                                       &_init_CMyStroke };

CRuntimeClass* CMyStroke::GetRuntimeClass( ) const { return ( CRuntimeClass* )( &CMyStroke::classCMyStroke ); }

CArchive& AFXAPI operator>>( CArchive& ar, CMyStroke*& pOb )
{
    pOb = ( CMyStroke* )ar.ReadObject( &CMyStroke::classCMyStroke );
    return ar;
}
//! --- IMPLEMENT_SERIAL( CMyStroke,CObject,1 ) ---

void CMyStroke::Serialize( CArchive& ar )
{
    if ( ar.IsStoring( ) )
    {
        ar << m_str << m_i << m_rect;
    }
    else
    {
        ar >> m_str >> m_i >> m_rect;
    }
}

class CGraph : public CObject
{
    DECLARE_SERIAL( CGraph )
public:
    CGraph( ) = default;
    CGraph( char type, CPoint start, CPoint end );
    virtual void Serialize( CArchive& ar ) override;
    void         DrawGraph( CDC* pDC );

public:
    char   m_type;
    CPoint m_ptOrigin;
    CPoint m_ptEnd;
};