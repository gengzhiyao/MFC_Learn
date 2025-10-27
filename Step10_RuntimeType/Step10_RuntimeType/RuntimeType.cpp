#include "RuntimeType.h"
#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <typeindex>

/// @brief ����ʱ����Ϣ����
IMPLEMENT_DYNAMIC(Base,CObject)

//��չ��: IMPLEMENT_DYNAMIC
//IMPLEMENT_DYNAMIC(Derived, Base)
//IMPLEMENT_RUNTIMECLASS(Derived, Base, 0xFFFF, NULL, NULL)
///�����̬�������� Derived::classDerived���������Ϊ��� ��Ψһ���֤������������þ�����Ϊ����ض���ʶ���ȶ���������̬�����ĵ�ַ�������Ͼ����ڱȶ�������� �����֤���롱 �Ƿ���ͬ���Ӷ��ж������Ƿ�Ϊͬһ���ࡣ
//ͨ����̬������Ψһ����ʵ���༶������ʶ�𣬽���֧������ʱ�����жϡ����󴴽��ȷ������ԡ�
AFX_COMDAT const 
CRuntimeClass Derived::classDerived = 
{//Ϊ��̬�����ṹ��CRuntimeClass��Ա��ֵ
	"Derived", 
	sizeof(class Derived),
	0xFFFF,
	NULL,
	const_cast<CRuntimeClass*>(&Base::classBase), //���ﱣ���˸���ľ�̬��Ա����
	NULL, 
	NULL
};

//��ȡ����ͷ��㣬��̬����classDerived�ǽṹ�壬���б�����&Base::classBase
CRuntimeClass* Derived::GetRuntimeClass() const { return (CRuntimeClass*)(&Derived::classDerived); }

int main()
{
	Derived* dy = new Derived();
	dy->IsKindOf(RUNTIME_CLASS(Derived));//���Ÿ��������ͣ���&Derived::classDerived��̬�����ĵ�ַ����������ѭ���ȶ��Ƿ����ڸ�����
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
//	CRuntimeClass* pClassThis = this->GetRuntimeClass();//�õ����ྲ̬�����ĵ�ַ
//
//	ENSURE(pClassThis);
//	return pClassThis->IsDerivedFrom(pClass);
//}