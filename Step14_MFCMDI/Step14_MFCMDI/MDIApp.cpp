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
END_MESSAGE_MAP( )

BEGIN_MESSAGE_MAP( CMyDoc1, CDocument )
ON_COMMAND( ID_SAVE, OnFileSave )
END_MESSAGE_MAP( )

BEGIN_MESSAGE_MAP( CMyFrame, CMDIFrameWnd )
END_MESSAGE_MAP( )


MDIApp theApp;

void CMyView::OnDraw( CDC* pDC ) { pDC->TextOut( 100, 100, _T("我是视图窗口") ); }

// CMultiDocTemplate类中有一个成员m_docList保存了多个文档类对象的地址
// theApp中成员m_pDocManager管理文档->m_templateList单文档模板类对象的地址

void CMyDoc1::Serialize( CArchive& ar )
{
    m_pStroke = new CMyStroke;
    ar.WriteObject( m_pStroke );    // WriteObject -> obj.Serialize
}
