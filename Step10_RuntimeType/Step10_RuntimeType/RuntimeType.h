#pragma once
#include <afxwin.h>

class Base:public CObject
{
	DECLARE_DYNAMIC(Base)
};

class Derived :public Base
{
	//DECLARE_DYNAMIC(Derived)
	///��չ��������
public: 
	static const CRuntimeClass classDerived;//����һ����̬�������ṹ������
	virtual CRuntimeClass* GetRuntimeClass() const;///�麯����
};

//struct CRuntimeClass
//{
//	LPCSTR m_lpszClassName;
//	int m_nObjectSize;
//	UINT m_wSchema; //��汾 ����0xFFFF
//  CObject* (PASCAL* m_pfnCreateObject)();/******��̬��������******/
//  CRuntimeClass* m_pBaseClass;
//	CRuntimeClass* m_pNextClass;
//	const AFX_CLASSINIT* m_pClassInit;
//};