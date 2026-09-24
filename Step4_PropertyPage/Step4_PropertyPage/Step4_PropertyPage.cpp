
#include "pch.h"
#include "framework.h"
#include "Step4_PropertyPage.h"
#include "Step4_PropertyPageDlg.h"
#include "CGuideSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP( CStep4PropertyPageApp, CWinApp )
ON_COMMAND( ID_HELP, &CWinApp::OnHelp )
END_MESSAGE_MAP( )


CStep4PropertyPageApp::CStep4PropertyPageApp( )
{
}

// 唯一的 CStep4PropertyPageApp 对象

CStep4PropertyPageApp theApp;

// CStep4PropertyPageApp 初始化

BOOL CStep4PropertyPageApp::InitInstance( )
{
    CWinApp::InitInstance( );

    CShellManager* pShellManager = new CShellManager;

    CMFCVisualManager::SetDefaultManager( RUNTIME_CLASS( CMFCVisualManagerWindows ) );

    SetRegistryKey( _T("应用程序向导生成的本地应用程序") );

    m_pSplashThread = ( CSplashThread* )AfxBeginThread( RUNTIME_CLASS( CSplashThread ), 0, 0 );
    Sleep( 1000 );

    CGuideSheet dlg( _T("向导程序") );
    dlg.SetWizardMode( );
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal( );
    if ( nResponse == IDOK )
    {

    }
    else if ( nResponse == IDCANCEL )
    {

    }
    else if ( nResponse == -1 )
    {
        TRACE( traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n" );
        TRACE( traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n" );
    }


    if ( pShellManager != nullptr )
    {
        delete pShellManager;
    }

#if !defined( _AFXDLL ) && !defined( _AFX_NO_MFC_CONTROLS_IN_DIALOGS )
    ControlBarCleanUp( );
#endif

    // 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
    //  而不是启动应用程序的消息泵。
    return FALSE;
}
