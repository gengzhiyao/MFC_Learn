// CConfirmPage.cpp: 实现文件
//

#include "pch.h"
#include "Step4_PropertyPage.h"
#include "afxdialogex.h"
#include "CConfirmPage.h"


// CConfirmPage 对话框

IMPLEMENT_DYNAMIC(CConfirmPage, CMFCPropertyPage)

CConfirmPage::CConfirmPage(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_COMFIRM)
{

}

CConfirmPage::~CConfirmPage()
{
}

void CConfirmPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfirmPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CConfirmPage 消息处理程序

BOOL CConfirmPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CMFCPropertySheet* psheet = (CMFCPropertySheet*)GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);
	return CMFCPropertyPage::OnSetActive();
}

LRESULT CConfirmPage::OnWizardNext()
{
	// TODO: 在此添加专用代码和/或调用基类
	LRESULT result = CMFCPropertyPage::OnWizardNext();
	if (MessageBoxW(_T("install"), L"wizard", MB_ICONQUESTION | MB_YESNO) == IDNO)
	{
		((CMFCPropertySheet*)GetParent())->PressButton(PSBTN_BACK);
	}
	return result;
}
