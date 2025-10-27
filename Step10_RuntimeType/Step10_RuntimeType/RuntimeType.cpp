#include "RuntimeType.h"
#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <typeindex>

/// @brief 运行时类信息机制
IMPLEMENT_DYNAMIC(Base,CObject)

//宏展开: IMPLEMENT_DYNAMIC
//IMPLEMENT_DYNAMIC(Derived, Base)
//IMPLEMENT_RUNTIMECLASS(Derived, Base, 0xFFFF, NULL, NULL)
///这个静态变量（如 Derived::classDerived）可以理解为类的 “唯一身份证”，其核心作用就是作为类的特定标识。比对这两个静态变量的地址，本质上就是在比对两个类的 “身份证号码” 是否相同，从而判断它们是否为同一个类。
//通过静态变量的唯一性来实现类级别的身份识别，进而支持运行时类型判断、对象创建等反射特性。
AFX_COMDAT const 
CRuntimeClass Derived::classDerived = 
{//为静态变量结构体CRuntimeClass成员赋值
	"Derived", 
	sizeof(class Derived),
	0xFFFF,
	NULL,
	const_cast<CRuntimeClass*>(&Base::classBase), //这里保存了父类的静态成员变量
	NULL, 
	NULL
};

//获取链表头结点，静态变量classDerived是结构体，其中保存着&Base::classBase
CRuntimeClass* Derived::GetRuntimeClass() const { return (CRuntimeClass*)(&Derived::classDerived); }

int main()
{
	Derived* dy = new Derived();
	dy->IsKindOf(RUNTIME_CLASS(Derived));//拿着给定的类型，是&Derived::classDerived静态变量的地址，到链表中循环比对是否属于该类型
	printf("%d\n",static_cast<int>(dy->IsKindOf(RUNTIME_CLASS(Derived))));
	std::type_index ti= typeid(*dy);
	std::cout << ti.name() << std::endl;
	return 0;
}

//BOOL Derived::IsKindOf(const CRuntimeClass* pClass) const
//{
//	ENSURE(this != NULL);
//	// it better be in valid memory, at least for CObject size
//	ASSERT(AfxIsValidAddress(this, sizeof(CObject)));
//
//	// simple SI case
//	CRuntimeClass* pClassThis = this->GetRuntimeClass();//得到本类静态变量的地址
//
//	ENSURE(pClassThis);
//	return pClassThis->IsDerivedFrom(pClass);
//}