// CSummandPage.cpp: 实现文件
//

#include "pch.h"
#include "Step3_PropertyPage.h"
#include "CSummandPage.h"


// CSummandPage 对话框

IMPLEMENT_DYNCREATE(CSummandPage, CPropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CSummandPage, CPropertyPage)
END_MESSAGE_MAP()



// CSummandPage::CSummandPageFactory::UpdateRegistry -
// 添加或移除 CSummandPage 的系统注册表项



// CSummandPage::CSummandPage - 构造函数

// TODO:  定义页标题的字符串资源；用 ID 替换下面的“0”。

CSummandPage::CSummandPage() :
	CPropertyPage(IDD_SUMMED)
{

}



// CSummandPage::DoDataExchange - 在页和属性间移动数据

void CSummandPage::DoDataExchange(CDataExchange* pDX)
{
	//DDP_PostProcessing(pDX);
	CPropertyPage::DoDataExchange(pDX);
}

// CSummandPage 消息处理程序

//BOOL CSummandPage::OnSetActive()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	CPropertySheet* psheet = (CPropertySheet*)GetParent();
//	psheet->SetWizardButtons(PSWIZB_NEXT);
//	return CPropertyPage::OnSetActive();
//}
