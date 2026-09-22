#pragma once
#include "pch.h"
#include "StartDlg.h"

// CSplashThread

class CSplashThread : public CWinThread
{
    DECLARE_DYNCREATE( CSplashThread )

protected:
    CSplashThread( );           // 动态创建所使用的受保护的构造函数
    virtual ~CSplashThread( );

public:
    virtual BOOL InitInstance( );
    virtual int  ExitInstance( );
    afx_msg void HideStartDlg( );

protected:
    DECLARE_MESSAGE_MAP( )

private:
    StartDlg* m_pStartDlg;
};
