#include "pch.h"
#include "Shape.h"

Graph::Graph( Shape shape )
    : m_background( RGB( 255, 255, 255 ) ),
      m_foreground( RGB( 0, 0, 0 ) ),
      m_shape( shape ),
      m_penWidth( 1 ),
      m_layer( 1 )
{
}

Graph::~Graph( ) {}

void Graph::AddVertex( CPoint point ) { m_vertices.push_back( point ); }

GRectangle::GRectangle( )
    : Graph( Shape::Rectangle ) /// 子类构造函数初始化列表中只能初始化子类自己的成员变量 不能 m_shape(Shape::Rectangle) 可以在构造函数体中赋值，但那已经是二次赋值了
{
}

void GRectangle::Draw( CDC* pDC )
{
    // CPen pen=CPen::CreatePen
    pDC->Rectangle( m_vertices[0].x, m_vertices[0].y, m_vertices[1].x, m_vertices[1].y );
}

void GRectangle::Register( )
{
    GraphFactory::GetInstance( ).Register( Shape::Rectangle, []( ) -> Graph* { return new GRectangle; } );
}

GraphFactory& GraphFactory::GetInstance( )
{
    static GraphFactory theOnlyFactory;
    return theOnlyFactory;
}

void GraphFactory::Register( Shape type, Method method ) { m_factoryMap[type] = method; }

Graph* GraphFactory::Create( Shape shape ) const
{
    auto it = m_factoryMap.find( shape );
    if ( it == m_factoryMap.end( ) ) return nullptr;
    return it->second( );
}

GCircle::GCircle( )
    : Graph( Shape::Circle)
{
}

void GCircle::Draw( CDC* pDC ) { pDC->Ellipse( m_vertices[0].x, m_vertices[0].y, m_vertices[1].x, m_vertices[1].y ); }

void GCircle::Register( )
{
    GraphFactory::GetInstance( ).Register( Shape::Circle, []( ) -> Graph* { return new GCircle; } );
}

GTriangle::GTriangle( ) 
: Graph( Shape::Triangle)
{
    
}

void GTriangle::Draw( CDC* pDC ) { 
    
    // --- 三角形绘制开始 ---
    CPoint top( m_vertices[0].x+( m_vertices[1].x - m_vertices[0].x ) / 2, m_vertices[0].y );
    pDC->MoveTo( top );  // 顶点
    pDC->LineTo( m_vertices[0].x, m_vertices[1].y );    // 左
    pDC->LineTo( m_vertices[1].x, m_vertices[1].y );    // 右
    pDC->LineTo( top );
    // --- 三角形绘制结束 ---
}

void GTriangle::Register( ) {
    GraphFactory::GetInstance( ).Register( Shape::Triangle, []( ) -> Graph* { return new GTriangle; } );
}
