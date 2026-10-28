
// Step18_MDIWizardView.h: CStep18MDIWizardView 类的接口
//

#pragma once
#include <memory>
#include "DrawCommand.h"
#include <vector>
class CStep18MDIWizardView : public CScrollView
{
protected: // 仅从序列化创建
    CStep18MDIWizardView( ) noexcept;
    DECLARE_DYNCREATE( CStep18MDIWizardView )

// 特性
public:
    CStep18MDIWizardDoc* GetDocument( ) const;

    class utils
    {
    public:
        static void LPtoDP( CView* pWnd, CPoint& src );
        static void DPtoLP( CView* pWnd, CPoint& src );

        enum class MouseStatus
        {
            Drawing = 1,
            Selecting
        };
    };
// 操作
private:
    CRect HitTest( CPoint pt );
// 重写
public:
    virtual void OnDraw( CDC* pDC );  // 重写以绘制该视图
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );

protected:
    virtual BOOL OnPreparePrinting( CPrintInfo* pInfo );
    virtual void OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo );
    virtual void OnEndPrinting( CDC* pDC, CPrintInfo* pInfo );
    virtual void OnInitialUpdate( ) override;
    afx_msg void OnSelectRect( );
// 实现
public:
    virtual ~CStep18MDIWizardView( );
#ifdef _DEBUG
    virtual void AssertValid( ) const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

protected:
// 生成的消息映射函数
protected:
    DECLARE_MESSAGE_MAP( )
public:
    void DrawSelectionRubberband( const CPoint& point );        // !拖动预览，最好返回一个当前选中的图形
    void OnLButtonDown( UINT nFlags, CPoint point );

    afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
    afx_msg void OnMouseMove( UINT nFlags, CPoint point );

private:
    CPoint m_lButtonDownPt;
    CPoint m_deltaPt;
    CRect  m_hitRect;

    std::vector<Graph*> m_graphs;   // !应该用一个 map 存储图形以及其对应的外接矩形

    Graph*             m_pCurGraph;
    Shape              m_curTool;
    utils::MouseStatus m_mouseStatus;

public:
    afx_msg void OnSelectCircle( );
    afx_msg void OnSelectPolyline( );
    afx_msg void OnSelectTriangle( );
    afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
    afx_msg void OnSelectLine( );
    afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
};

#ifndef _DEBUG  // Step18_MDIWizardView.cpp 中的调试版本
inline CStep18MDIWizardDoc* CStep18MDIWizardView::GetDocument( ) const
{
    return reinterpret_cast<CStep18MDIWizardDoc*>( m_pDocument );
}
#endif
