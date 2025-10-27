#pragma once
#include "CSummandPage.h"
#include "CAppendPage.h"
#include "CAddPage.h"

class CAddSheet:public CPropertySheet
{
	DECLARE_DYNAMIC(CAddSheet)
public:
	CAddSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage);
	CAddSheet(LPCTSTR pszCaption, CWnd* pParentWnd=NULL, UINT iSelectPage=0);

	CSummandPage m_summandPage;
	CAppendPage m_appendPage;
	CAddPage m_addPage;
protected:
	//DECLARE_MESSAGE_MAP()
};

