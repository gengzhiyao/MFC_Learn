#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
enum class Shape : unsigned char
{
    None=0,
    Rectangle = 1,
    Circle,
    Triangle,
    Polygon
};

class Graph
{
public:
    Graph( Shape shape );
    virtual ~Graph( );
    virtual void Draw( CDC* pDC ) = 0;

    void         AddVertex( CPoint point );

protected:
    COLORREF m_background, m_foreground;
    bool     m_isForeVisible;
    bool     m_isBackVisible;

    unsigned short m_penWidth;

    Shape m_shape;

    std::vector<CPoint> m_vertices;

    unsigned short m_layer;
};

class GraphFactory
{
public:
    using Method = std::function<Graph*( )>;
    static GraphFactory& GetInstance( );    // Singleton

    void   Register( Shape type, Method method );
    Graph* Create( Shape shape ) const;

private:
    std::unordered_map<Shape, Method> m_factoryMap;
};

class GRectangle final : public Graph
{
public:
    GRectangle( );
    void Draw( CDC* pDC ) override;
    static void Register( );
};

class GCircle final : public Graph
{
public:
    GCircle( );
    void        Draw( CDC* pDC ) override;
    static void Register( );
};

class GTriangle final : public Graph
{
public:
    GTriangle( );
    void        Draw( CDC* pDC ) override;
    static void Register( );
};