// CGuideSheet.cpp: 实现文件
//

#include "pch.h"
#include "Step4_PropertyPage.h"
#include "CGuideSheet.h"


// CGuideSheet

IMPLEMENT_DYNAMIC(CGuideSheet, CMFCPropertySheet)

CGuideSheet::CGuideSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CMFCPropertySheet(pszCaption,pParentWnd,iSelectPage)
{
	AddPage(&m_CSynopsisPage);
	AddPage(&m_CConfirmPage);
	AddPage(&m_CInstallPage);
}

CGuideSheet::~CGuideSheet()
{
}


BEGIN_MESSAGE_MAP(CGuideSheet, CMFCPropertySheet)
END_MESSAGE_MAP()

BOOL CGuideSheet::OnInitDialog()
{
	BOOL bResult = CMFCPropertySheet::OnInitDialog();
	SetTitle(_T("init"));
	GetDlgItem(IDHELP)->ShowWindow(SW_HIDE);
	// TODO:  在此添加您的专用代码

	return bResult;
}
