// CAppendPage.cpp: 实现文件
//

#include "pch.h"
#include "Step3_PropertyPage.h"
#include "CAppendPage.h"


// CAppendPage 对话框

IMPLEMENT_DYNCREATE(CAppendPage, CPropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CAppendPage, CPropertyPage)
END_MESSAGE_MAP()




// CAppendPage::CAppendPage - 构造函数

// TODO:  定义页标题的字符串资源；用 ID 替换下面的“0”。

CAppendPage::CAppendPage() :
	CPropertyPage(IDD_APPEND)
{

}



// CAppendPage::DoDataExchange - 在页和属性间移动数据

void CAppendPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}



// CAppendPage 消息处理程序
//
//BOOL CAppendPage::OnSetActive()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	CPropertySheet* psheet = (CPropertySheet*)GetParent();
//	psheet->SetWizardButtons(PSWIZB_NEXT);
//	return CPropertyPage::OnSetActive();
//}
