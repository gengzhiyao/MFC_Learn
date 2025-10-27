#pragma once
#include <afxwin.h>

class Base:public CObject
{
	DECLARE_DYNAMIC(Base)
};

class Derived :public Base
{
	//DECLARE_DYNAMIC(Derived)
	///宏展开的内容
public: 
	static const CRuntimeClass classDerived;//定义一个静态变量，结构体类型
	virtual CRuntimeClass* GetRuntimeClass() const;///虚函数？
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