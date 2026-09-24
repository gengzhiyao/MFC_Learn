// CSplashThread.cpp: 实现文件
//

#include "pch.h"
#include "CSplashThread.h"
#include "resource.h"

// CSplashThread

IMPLEMENT_DYNCREATE( CSplashThread, CWinThread )

CSplashThread::CSplashThread( ) {}

CSplashThread::~CSplashThread( ) {}

BOOL CSplashThread::InitInstance( )
{
    m_pStartDlg = new StartDlg;
    m_pStartDlg->Create( IDD_StartDlg );
    m_pStartDlg->ShowWindow( SW_SHOW );
    m_pStartDlg->UpdateWindow( );
    return TRUE;
}

int CSplashThread::ExitInstance( )
{
    return CWinThread::ExitInstance( );
}

void CSplashThread::HideStartDlg( ) { m_pStartDlg->SendMessage( WM_CLOSE ); }

BEGIN_MESSAGE_MAP( CSplashThread, CWinThread )
END_MESSAGE_MAP( )

// CSplashThread 消息处理程序
