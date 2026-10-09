#pragma once
#include "Shape.h"

class CStep18MDIWizardDoc : public CDocument
{
protected: // 仅从序列化创建
    CStep18MDIWizardDoc( ) noexcept;
    DECLARE_DYNCREATE( CStep18MDIWizardDoc )

public:
    virtual BOOL OnNewDocument( );
    virtual void Serialize( CArchive& ar );
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent( );
    virtual void OnDrawThumbnail( CDC& dc, LPRECT lprcBounds );
#endif // SHARED_HANDLERS

// 实现
public:
    virtual ~CStep18MDIWizardDoc( );
#ifdef _DEBUG
    virtual void AssertValid( ) const;
    virtual void Dump( CDumpContext& dc ) const;
#endif

    DECLARE_MESSAGE_MAP( )

#ifdef SHARED_HANDLERS
        // 用于为搜索处理程序设置搜索内容的 Helper 函数
    void SetSearchContent( const CString& value );
#endif // SHARED_HANDLERS
};
