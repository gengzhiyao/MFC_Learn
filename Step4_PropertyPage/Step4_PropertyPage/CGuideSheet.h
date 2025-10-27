#pragma once
#include "CSynopsisPage.h"
#include "CInstallPage.h"
#include "CConfirmPage.h"

// CGuideSheet

class CGuideSheet : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(CGuideSheet)

public:
	CGuideSheet(LPCTSTR pszCaption,CWnd* pParentWnd=nullptr,UINT iSelectPage=0);
	virtual ~CGuideSheet();

protected:
	DECLARE_MESSAGE_MAP()

	CSynopsisPage m_CSynopsisPage;
	CInstallPage m_CInstallPage;
	CConfirmPage m_CConfirmPage;
public:
	virtual BOOL OnInitDialog();
};


