// Step19ActiveXControlCtrl.cpp : CStep19ActiveXControlCtrl ActiveX 控件类的实现。

#include "pch.h"
#include "framework.h"
#include "Step19_ActiveXControl.h"
#include "Step19ActiveXControlCtrl.h"
#include "Step19ActiveXControlPropPage.h"
#include "afxdialogex.h"
#include <atltime.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE( CStep19ActiveXControlCtrl, COleControl )

// 消息映射

BEGIN_MESSAGE_MAP( CStep19ActiveXControlCtrl, COleControl )
    ON_OLEVERB( AFX_IDS_VERB_PROPERTIES, OnProperties )
    ON_WM_TIMER( )
    ON_WM_CREATE( )
    ON_WM_DESTROY( )
END_MESSAGE_MAP( )

// 调度映射
// 调用映射是为了让外部的容器可以访问控件的属性和方法

BEGIN_DISPATCH_MAP( CStep19ActiveXControlCtrl, COleControl )
    DISP_FUNCTION_ID( CStep19ActiveXControlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE )
    DISP_STOCKPROP_BACKCOLOR( ) // Add
    DISP_STOCKPROP_FORECOLOR( ) // Add
    DISP_PROPERTY_NOTIFY_ID( CStep19ActiveXControlCtrl, "Interval", dispIdInterval, m_interval, OnIntervalChanged,VT_I4 )
    END_DISPATCH_MAP( )

// 事件映射
// 事件映射是为了让控件向包含他的容器发送事件

BEGIN_EVENT_MAP( CStep19ActiveXControlCtrl, COleControl )
END_EVENT_MAP( )

// 属性页

// TODO: 根据需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS( CStep19ActiveXControlCtrl, 2 )
    PROPPAGEID( CStep19ActiveXControlPropPage::guid )
    PROPPAGEID( CLSID_CColorPropPage )
END_PROPPAGEIDS( CStep19ActiveXControlCtrl )

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX( CStep19ActiveXControlCtrl, "MFCACTIVEXCONTRO.Step19ActiveXControlCtrl.1", 0xca2b8edd, 0x562b, 0x4e6c, 0xb8, 0xe7, 0xf0, 0x83, 0x93, 0x97, 0x94, 0x9c )

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB( CStep19ActiveXControlCtrl, _tlid, _wVerMajor, _wVerMinor )

// 接口 ID

const IID IID_DStep19ActiveXControl = { 0x5a3a3dca, 0x965a, 0x4d7b, { 0xab, 0x92, 0xd4, 0x9c, 0xe8, 0x1d, 0xea, 0x7d } };
const IID IID_DStep19ActiveXControlEvents = { 0xdaf4e232, 0x181d, 0x4a49, { 0xb0, 0x11, 0x2e, 0x07, 0x9d, 0x55, 0xcb, 0xe6 } };

// 控件类型信息

static const DWORD _dwStep19ActiveXControlOleMisc = OLEMISC_ACTIVATEWHENVISIBLE | OLEMISC_SETCLIENTSITEFIRST | OLEMISC_INSIDEOUT | OLEMISC_CANTLINKINSIDE | OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE( CStep19ActiveXControlCtrl, IDS_STEP19ACTIVEXCONTROL, _dwStep19ActiveXControlOleMisc )

// CStep19ActiveXControlCtrl::CStep19ActiveXControlCtrlFactory::UpdateRegistry -
// 添加或移除 CStep19ActiveXControlCtrl 的系统注册表项

BOOL CStep19ActiveXControlCtrl::CStep19ActiveXControlCtrlFactory::UpdateRegistry( BOOL bRegister )
{
    // TODO:  验证您的控件是否符合单元模型线程处理规则。
    // 有关更多信息，请参考 MFC 技术说明 64。
    // 如果您的控件不符合单元模型规则，则
    // 必须修改如下代码，将第六个参数从
    // afxRegApartmentThreading 改为 0。

    if ( bRegister )
        return AfxOleRegisterControlClass( AfxGetInstanceHandle( ),
                                           m_clsid,
                                           m_lpszProgID,
                                           IDS_STEP19ACTIVEXCONTROL,
                                           IDB_STEP19ACTIVEXCONTROL,
                                           afxRegApartmentThreading,
                                           _dwStep19ActiveXControlOleMisc,
                                           _tlid,
                                           _wVerMajor,
                                           _wVerMinor );
    else
        return AfxOleUnregisterClass( m_clsid, m_lpszProgID );
}

// CStep19ActiveXControlCtrl::CStep19ActiveXControlCtrl - 构造函数

CStep19ActiveXControlCtrl::CStep19ActiveXControlCtrl( )
{
    InitializeIIDs( &IID_DStep19ActiveXControl, &IID_DStep19ActiveXControlEvents );
    m_interval = 1;
    // this->SetTimer( 1, 1000, nullptr ); 构造函数中，还没有生成窗口句柄，m_hWnd 为空
}

// CStep19ActiveXControlCtrl::~CStep19ActiveXControlCtrl - 析构函数

CStep19ActiveXControlCtrl::~CStep19ActiveXControlCtrl( )
{
    // TODO:  在此清理控件的实例数据。
}

// CStep19ActiveXControlCtrl::OnDraw - 绘图函数

void CStep19ActiveXControlCtrl::OnDraw( CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */ )
{
    if ( !pdc ) return;

    pdc->FillRect( rcBounds, CBrush::FromHandle( ( HBRUSH )GetStockObject( WHITE_BRUSH ) ) );
    pdc->Ellipse( rcBounds );

    CBrush  brush( TranslateColor( GetBackColor( ) ) );
    // CBrush* pOldBrush= pdc->SelectObject( &brush );
    pdc->FillRect( rcBounds, &brush );
    pdc->SetTextColor( TranslateColor( GetForeColor( ) ) );
    pdc->SetBkMode( TRANSPARENT );
    CTime curTime=CTime::GetCurrentTime( );
    CString strTime = curTime.Format(_T("%H:%M:%S"));
    pdc->TextOut( rcBounds.top, rcBounds.left, strTime );
}

// CStep19ActiveXControlCtrl::DoPropExchange - 持久性支持

void CStep19ActiveXControlCtrl::DoPropExchange( CPropExchange* pPX )
{
    ExchangeVersion( pPX, MAKELONG( _wVerMinor, _wVerMajor ) );
    COleControl::DoPropExchange( pPX );

        // TODO: 为每个持久的自定义属性调用 PX_ 函数。
}

// CStep19ActiveXControlCtrl::OnResetState - 将控件重置为默认状态

void CStep19ActiveXControlCtrl::OnResetState( )
{
    COleControl::OnResetState( );  // 重置 DoPropExchange 中找到的默认值

        // TODO:  在此重置任意其他控件状态。
}

// CStep19ActiveXControlCtrl::AboutBox - 向用户显示“关于”框

void CStep19ActiveXControlCtrl::AboutBox( )
{
    CDialogEx dlgAbout( IDD_ABOUTBOX_STEP19ACTIVEXCONTROL );
    dlgAbout.DoModal( );
}

// CStep19ActiveXControlCtrl 消息处理程序

void CStep19ActiveXControlCtrl::OnTimer( UINT_PTR nIDEvent )
{
    if ( nIDEvent==1)
        Invalidate( );
        // InvalidateControl();    // 强制重绘控件自身
    COleControl::OnTimer( nIDEvent );
}

int CStep19ActiveXControlCtrl::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
    if ( COleControl::OnCreate( lpCreateStruct ) == -1 ) return -1;
    this->SetTimer( 1, m_interval, nullptr );
    return 0;
}

void CStep19ActiveXControlCtrl::OnDestroy( )
{
    this->KillTimer( 1 );
    COleControl::OnDestroy( );
}

void CStep19ActiveXControlCtrl::OnIntervalChanged( )
{
    if ( m_interval < 0 ) m_interval = 1;
    KillTimer( 1 );
    SetTimer( 1, m_interval, nullptr );
}
