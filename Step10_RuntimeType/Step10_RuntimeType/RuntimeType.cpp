#include "RuntimeType.h"
#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <typeindex>

/// @brief 运行时类信息机制
IMPLEMENT_DYNAMIC( Base, CObject )

// 宏展开: IMPLEMENT_DYNAMIC
// IMPLEMENT_DYNAMIC(Derived, Base) \
// IMPLEMENT_RUNTIMECLASS(Derived, Base, 0xFFFF, NULL, NULL)
/// 这个静态变量（如 Derived::classDerived）可以理解为类的 “唯一身份证”，其核心作用就是作为类的特定标识。比对这两个静态变量的地址，本质上就是在比对两个类的 “身份证号码”
/// 是否相同，从而判断它们是否为同一个类。
// 通过静态变量的唯一性来实现类级别的身份识别，进而支持运行时类型判断、对象创建等反射特性。

/// --- Macro IMPLEMENT_DYNAMIC(Derived, Base) Begin ---
AFX_COMDAT const CRuntimeClass Derived::classDerived =    // 为静态变量结构体CRuntimeClass成员赋值
    { "Derived",
      sizeof( class Derived ),
      0xFFFF,
      NULL,
      const_cast<CRuntimeClass*>( &Base::classBase ),    /* CRuntimeClass* m_pBaseClass; */
      NULL,
      NULL };
// 获取链表头结点，静态变量classDerived是结构体，其中保存着&Base::classBase
CRuntimeClass* Derived::GetRuntimeClass( ) const { return const_cast<CRuntimeClass*>( &Derived::classDerived ); }   // Just ConstCast
/// --- Macro IMPLEMENT_DYNAMIC(Derived, Base) End ---

/// --- Macro RUNTIME_CLASS( Derived ) Begin ---
// const_cast<CRuntimeClass*>( &Derived::classDerived );
/// --- Macro RUNTIME_CLASS( Derived ) End ---

int main( )
{
    Derived* dy = new Derived( );
    bool     b1 = dy->IsKindOf( RUNTIME_CLASS( Derived ) );    // 拿着给定的类型，是&Derived::classDerived静态变量的地址，到链表中循环比对是否属于该类型
    bool     b2 = dy->IsKindOf( RUNTIME_CLASS( Base ) );
    printf( "%d\n", static_cast<int>( dy->IsKindOf( RUNTIME_CLASS( Derived ) ) ) );
    std::type_index ti = typeid( *dy );
    std::cout << ti.name( ) << std::endl;
    return 0;
}

/*
 BOOL Derived::IsKindOf(const CRuntimeClass* pClass) const
{
	CRuntimeClass* pClassThis = this->GetRuntimeClass();    // 拿链表头
	return pClassThis->IsDerivedFrom(pClass);
 }
*/

/*
BOOL CRuntimeClass::IsDerivedFrom( const CRuntimeClass* pBaseClass ) const
{
    const CRuntimeClass* pClassThis = this;
    while ( pClassThis != NULL )
    {
        if ( pClassThis == pBaseClass )
            return TRUE;
        pClassThis = pClassThis->m_pBaseClass;
    }
    return FALSE;
}
*/