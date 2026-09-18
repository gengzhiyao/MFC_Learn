#pragma once
#include <afxwin.h>
#include <vector>
#include "CMyStroke.h"
class CMyDoc : public CDocument
{
    DECLARE_DYNCREATE( CMyDoc )
};

IMPLEMENT_DYNCREATE( CMyDoc, CDocument )

class CMyView : public CView
{
public:
    virtual void OnDraw( CDC* pDC );
    ~CMyView( );

private:
    char m_flag;
    bool m_isDrawing;
    std::vector<CMyStroke*> m_strokeArray;
    CPoint              m_prePos;
    DECLARE_DYNCREATE( CMyView )
    DECLARE_MESSAGE_MAP( )
    afx_msg void OnLButtonDown( UINT nFlags, CPoint point );

public:
    afx_msg void OnMouseMove( UINT nFlags, CPoint point );
    afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
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