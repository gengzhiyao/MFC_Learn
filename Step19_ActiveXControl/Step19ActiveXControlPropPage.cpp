// Step19ActiveXControlPropPage.cpp : CStep19ActiveXControlPropPage 属性页类的实现。

#include "pch.h"
#include "framework.h"
#include "Step19_ActiveXControl.h"
#include "Step19ActiveXControlPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CStep19ActiveXControlPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CStep19ActiveXControlPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CStep19ActiveXControlPropPage, "MFCACTIVEXCONT.Step19ActiveXControlPropPage.1",
	0xeac76cbf,0xc9a6,0x4c5e,0x89,0xce,0x95,0x8f,0xdb,0x31,0xd2,0x7c)

// CStep19ActiveXControlPropPage::CStep19ActiveXControlPropPageFactory::UpdateRegistry -
// 添加或移除 CStep19ActiveXControlPropPage 的系统注册表项

BOOL CStep19ActiveXControlPropPage::CStep19ActiveXControlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_STEP19ACTIVEXCONTROL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CStep19ActiveXControlPropPage::CStep19ActiveXControlPropPage - 构造函数

CStep19ActiveXControlPropPage::CStep19ActiveXControlPropPage() :
	COlePropertyPage(IDD, IDS_STEP19ACTIVEXCONTROL_PPG_CAPTION)
{
}

// CStep19ActiveXControlPropPage::DoDataExchange - 在页和属性间移动数据

void CStep19ActiveXControlPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CStep19ActiveXControlPropPage 消息处理程序
