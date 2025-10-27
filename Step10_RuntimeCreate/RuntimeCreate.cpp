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
	CObject* pob = RUNTIME_CLASS(Derived)->CreateObject();//���createobject�������createobject��������������ҪŪ�죬�������þ�̬���������������CRUNTIMECLASS�еĺ���
	if (pob)//pob��Derived���Ͷ���ĵ�ַ
	{
		std::cout << "dynamic create successful " << std::endl;
	}
	/**
	* ִ�й��̣�
	* 1. ���ñ������ľ�̬����(CRuntimeClass)���ͣ�����CRuntimeClass�ĳ�Ա����CreateObject����
	* 2. ��ȡ��̬�����ĵ��ĸ���Ա��������֮(����ָ��)
	* 3. �����ӵľ�̬�����ڲ�������������Ĵ��������ظ������˶���ĵ�ַ
	*/

	//Դ���У�pObject = (*m_pfnCreateObject)();չ��Ϊ��pObject = (*(this->m_pfnCreateObject))();���ʵ��ǵ�ǰ�ṹ��ʵ���еĺ���ָ��
	// ������ Derived::classDerived.CreateObject() ʱ
    // �����ڲ��� this ָ�� &Derived::classDerived
    // m_pfnCreateObject �ȼ��� this->m_pfnCreateObject
    // Ҳ���� Derived::classDerived.m_pfnCreateObject���� Derived::CreateObject��
	//�ṹ���ʼ�������Ա������Ȼ����ͨ���ṹ��ʵ�� + ��Ա���ķ�ʽ���ʡ�
}
