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
// AFX_CLASSINIT 构造函数中调用AfxClassInit 该函数的作用就是将该模块中所有的类串成一张大网
// AFX_MODULE_STATE::m_classList 是一个CSimpleList 这是一张侵入式链表，通过AddHead将CRuntimeClass类注册到链表中，该链表的构造方式为 m_classList.Construct(offsetof(CRuntimeClass, m_pNextClass));
// 其中 offsetof(CRuntimeClass, m_pNextClass) 是利用编译期求值的方式计算 m_pNextClass 在结构体中的偏移量 在64位系统中，offset的确是 32
// 值得注意的是 CRuntimeClass 的 m_pNextClass 在初始化时是初始化为NULL 而在程序运行时，进入main函数之前被赋值
// 赋值的顺序依靠 AFX_CLASSINIT 的构造顺序，因为这是一个全局变量，并且不同翻译单元内全局变量的赋值顺序是不确定的，因此链表中的元素顺序也是不确定的 但是因为链表使用头插法插入元素，因此后注册的类在链表头

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