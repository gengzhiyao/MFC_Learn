#pragma once
#include <afxwin.h>

class Base :public CObject
{
	DECLARE_DYNAMIC(Base)
};

// 动态创建机制不需要父类声明 DECLARE_DYNCREATE 但是父类必须有 DECLARE_DYNAMIC
class Derived :public Base
{
	// DECLARE_DYNCREATE(Derived)
	// DECLARE_DYNAMIC(Derived)
public: 
	static const CRuntimeClass classDerived;
	virtual CRuntimeClass* GetRuntimeClass() const; 
	static CObject* PASCAL CreateObject();//相比运行时类型信息多了这个静态函数
};

//struct CRuntimeClass
//{
//	LPCSTR m_lpszClassName;
//	int m_nObjectSize;
//	UINT m_wSchema; //类版本 都是0xFFFF
//  CObject* (PASCAL* m_pfnCreateObject)();/******动态创建机制******/
//  CRuntimeClass* m_pBaseClass;
//	CRuntimeClass* m_pNextClass;
//	const AFX_CLASSINIT* m_pClassInit;
//};