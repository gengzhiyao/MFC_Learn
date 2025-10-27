// CSynopsisPage.cpp: 实现文件
//

#include "pch.h"
#include "Step4_PropertyPage.h"
#include "afxdialogex.h"
#include "CSynopsisPage.h"


// CSynopsisPage 对话框

IMPLEMENT_DYNAMIC(CSynopsisPage, CMFCPropertyPage)

CSynopsisPage::CSynopsisPage(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_SYNOPSIS)
{

}

CSynopsisPage::~CSynopsisPage()
{
}

void CSynopsisPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSynopsisPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CSynopsisPage 消息处理程序

BOOL CSynopsisPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CMFCPropertySheet* psheet = (CMFCPropertySheet*)GetParent();
	psheet->SetWizardButtons(PSWIZB_NEXT);
	return CMFCPropertyPage::OnSetActive();
}
