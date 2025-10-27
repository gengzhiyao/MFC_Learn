#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include "RuntimeCreate.h"

IMPLEMENT_DYNAMIC(Base, CObject)

//IMPLEMENT_DYNCREATE(Derived,Base)
//CObject* PASCAL Derived::CreateObject() { return new Derived; } 
////IMPLEMENT_RUNTIMECLASS(Derived, Base, 0xFFFF, Derived::CreateObject, NULL)
//CRuntimeClass* PASCAL Derived::_GetBaseClass(){ return RUNTIME_CLASS(Base); }
//AFX_COMDAT const CRuntimeClass Derived::classDerived = { 
//	"Derived", 
//	sizeof(class Derived), 
//	0xFFFF, 
//	NULL, 
//	&Derived::_GetBaseClass, 
//	NULL,
//	NULL }; 
//CRuntimeClass* PASCAL Derived::GetThisClass() { return _RUNTIME_CLASS(Derived); } 
//CRuntimeClass* Derived::GetRuntimeClass() const { return _RUNTIME_CLASS(Derived); }


CObject* PASCAL Derived::CreateObject() { return new Derived; }    //virtual

AFX_COMDAT const CRuntimeClass Derived::classDerived = { 
	"Derived", 
	sizeof(class Derived),
	0xFFFF, 
	Derived::CreateObject,
	RUNTIME_CLASS(Base),
	NULL, 
	NULL 
}; 
CRuntimeClass* Derived::GetRuntimeClass() const { return RUNTIME_CLASS(Derived); }

int main()
{
	//(CRuntimeClass*)(&Derived::classDerived)
	//CObject* pob = ((CRuntimeClass*)(&Derived::classDerived))->CreateObject();
	CObject* pob = RUNTIME_CLASS(Derived)->CreateObject();//这个createobject和上面的createobject是两个函数，不要弄混，这个会调用静态函数，这个函数是CRUNTIMECLASS中的函数
	if (pob)//pob是Derived类型对象的地址
	{
		std::cout << "dynamic create successful " << std::endl;
	}
	/**
	* 执行过程：
	* 1. 利用本类对象的静态变量(CRuntimeClass)类型，调用CRuntimeClass的成员函数CreateObject函数
	* 2. 获取静态变量的第四个成员，并调用之(函数指针)
	* 3. 新增加的静态函数内部，完成了类对象的创建，返回给我们了对象的地址
	*/

	//源码中，pObject = (*m_pfnCreateObject)();展开为：pObject = (*(this->m_pfnCreateObject))();访问的是当前结构体实例中的函数指针
	// 当调用 Derived::classDerived.CreateObject() 时
    // 函数内部的 this 指向 &Derived::classDerived
    // m_pfnCreateObject 等价于 this->m_pfnCreateObject
    // 也就是 Derived::classDerived.m_pfnCreateObject（即 Derived::CreateObject）
	//结构体初始化后，其成员变量仍然可以通过结构体实例 + 成员名的方式访问。
}
