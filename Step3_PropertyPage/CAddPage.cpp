// CAddPage.cpp: 实现文件
//

#include "pch.h"
#include "Step3_PropertyPage.h"
#include "CAddPage.h"


// CAddPage 对话框

IMPLEMENT_DYNCREATE(CAddPage, CPropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CAddPage, CPropertyPage)
END_MESSAGE_MAP()

// CAddPage::CAddPage - 构造函数

// TODO:  定义页标题的字符串资源；用 ID 替换下面的“0”。

CAddPage::CAddPage() :
	CPropertyPage(IDD_SUM)
{

}



// CAddPage::DoDataExchange - 在页和属性间移动数据

void CAddPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}



// CAddPage 消息处理程序
//
//BOOL CAddPage::OnSetActive()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	CPropertySheet* psheet = (CPropertySheet*)GetParent();
//	psheet->SetFinishText(_T("完成"));
//	return CPropertyPage::OnSetActive();
//}
//
//BOOL CAddPage::OnWizardFinish()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	MessageBox(_T("向导完毕"));
//	return CPropertyPage::OnWizardFinish();
//}
