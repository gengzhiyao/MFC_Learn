
// Step18_MDIWizardView.h: CStep18MDIWizardView 类的接口
//

#pragma once

class CStep18MDIWizardView : public CScrollView
{
protected: // 仅从序列化创建
    CStep18MDIWizardView( ) noexcept;
    DECLARE_DYNCREATE( CStep18MDIWizardView )

// 特性
public:
    CStep18MDIWizardDoc* GetDocument( ) const;

// 操作
public:
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
    afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
    afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
    afx_msg void OnMouseMove( UINT nFlags, CPoint point );

private:
    CPoint m_mouseDownPt;
    CPoint m_oldPt;
    bool   m_isBeginDraw;
};

#ifndef _DEBUG  // Step18_MDIWizardView.cpp 中的调试版本
inline CStep18MDIWizardDoc* CStep18MDIWizardView::GetDocument( ) const { return reinterpret_cast<CStep18MDIWizardDoc*>( m_pDocument ); }
#endif
