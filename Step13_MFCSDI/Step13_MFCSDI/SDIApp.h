#pragma once
#include <afxwin.h>

class CMyDoc : public CDocument
{
    DECLARE_DYNCREATE( CMyDoc )
};

IMPLEMENT_DYNCREATE( CMyDoc, CDocument )

class CMyView : public CView
{
public:
    virtual void OnDraw( CDC* pDC );
    DECLARE_DYNCREATE( CMyView )
};

IMPLEMENT_DYNCREATE( CMyView, CView )

class CMyFrame : public CFrameWnd
{
    DECLARE_DYNCREATE( CMyFrame )

public:
    afx_msg int OnCreate( LPCREATESTRUCT cs );

    DECLARE_MESSAGE_MAP( )
};

IMPLEMENT_DYNCREATE( CMyFrame, CFrameWnd )

class SDIApp : public CWinApp
{
public:
    virtual BOOL InitInstance( );
};