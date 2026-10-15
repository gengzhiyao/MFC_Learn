#include "pch.h"
#include "Shape.h"
#include "cmdobj.h"
Graph::Graph( Shape shape )
    : m_background( RGB( 255, 255, 255 ) ),
      m_foreground( RGB( 0, 0, 0 ) ),
      m_shapeType( shape ),
      m_penWidth( 1 ),
      m_layer( 1 )
{
}

Graph::~Graph( ) {}

Shape Graph::GetType( ) const { return m_shapeType; }

void Graph::AddVertex( CPoint point ) { m_vertices.push_back( point ); }

GRectangle::GRectangle( )
    : Graph( Shape::Rectangle ) /// 子类构造函数初始化列表中只能初始化子类自己的成员变量 不能 m_shape(Shape::Rectangle) 可以在构造函数体中赋值，但那已经是二次赋值了
{
}

void GRectangle::Draw( CDC* pDC )
{
    // CPen pen=CPen::CreatePen
    CPoint startPt = m_vertices.front( );
    CPoint endPt = m_vertices.back( );
    pDC->Rectangle( startPt.x, startPt.y, endPt.x, endPt.y );
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
    : Graph( Shape::Circle )
{
}

void GCircle::Draw( CDC* pDC )
{
    CPoint startPt = m_vertices.front( );
    CPoint endPt = m_vertices.back( );
    pDC->Ellipse( startPt.x, startPt.y, endPt.x, endPt.y );
}

void GCircle::Register( )
{
    GraphFactory::GetInstance( ).Register( Shape::Circle, []( ) -> Graph* { return new GCircle; } );
}

GTriangle::GTriangle( )
    : Graph( Shape::Triangle )
{
}

void GTriangle::Draw( CDC* pDC )
{
    // --- 三角形绘制开始 ---
    CPoint startPt = m_vertices.front( );
    CPoint endPt = m_vertices.back( );
    CPoint top( startPt.x + ( endPt.x - startPt.x ) / 2, startPt.y );
    pDC->MoveTo( top );  // 顶点
    pDC->LineTo( startPt.x, endPt.y );    // 左
    pDC->LineTo( endPt.x, endPt.y );    // 右
    pDC->LineTo( top );
    // --- 三角形绘制结束 ---
}

void GTriangle::Register( )
{
    GraphFactory::GetInstance( ).Register( Shape::Triangle, []( ) -> Graph* { return new GTriangle; } );
}

GLine::GLine( )
    : Graph( Shape::Line )
{
}

void GLine::Draw( CDC* pDC )
{
    // --- 绘制开始 ---
    CPoint startPt = m_vertices.front( );
    CPoint endPt = m_vertices.back( );
    pDC->MoveTo( startPt.x, startPt.y );
    pDC->LineTo( endPt.x, endPt.y );
    // --- 绘制结束 ---
}

void GLine::Register( )
{
    GraphFactory::GetInstance( ).Register( Shape::Line, []( ) -> Graph* { return new GLine; } );
}

void GPolyline::Register( )
{
    GraphFactory::GetInstance( ).Register( Shape::Polyline, []( ) -> Graph* { return new GPolyline; } );
}

GPolyline::GPolyline( )
    : Graph( Shape::Polyline ),
      m_isEditing( false )
{
}

void GPolyline::Draw( CDC* pDC )
{
    // --- 绘制开始 ---
    pDC->MoveTo( m_vertices[0].x, m_vertices[0].y );
    for ( size_t i = 1; i < m_vertices.size( ); i++ )
    {
        TRACE( "---%d\n", m_vertices.size( ) );
        pDC->LineTo( m_vertices[i].x, m_vertices[i].y );
    }
    // --- 绘制结束 ---
}
