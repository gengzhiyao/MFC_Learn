// CInstallPage.cpp: 实现文件
//

#include "pch.h"
#include "Step4_PropertyPage.h"
#include "afxdialogex.h"
#include "CInstallPage.h"


// CInstallPage 对话框

IMPLEMENT_DYNAMIC(CInstallPage, CMFCPropertyPage)

CInstallPage::CInstallPage(CWnd* pParent /*=nullptr*/)
	: CMFCPropertyPage(IDD_INSTALL)
{

}

CInstallPage::~CInstallPage()
{
}

void CInstallPage::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInstallPage, CMFCPropertyPage)
END_MESSAGE_MAP()


// CInstallPage 消息处理程序

BOOL CInstallPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CMFCPropertySheet* psheet = (CMFCPropertySheet*)GetParent();
	psheet->SetFinishText(_T("finish install"));
	return CMFCPropertyPage::OnSetActive();
}
