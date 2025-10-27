#include "pch.h"
#include "CAddSheet.h"

IMPLEMENT_DYNAMIC(CAddSheet,CPropertySheet)

CAddSheet::CAddSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_summandPage);
	AddPage(&m_appendPage);
	AddPage(&m_addPage);
}

CAddSheet::CAddSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_summandPage);
	AddPage(&m_appendPage);
	AddPage(&m_addPage);
}
