#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

enum class Shape : unsigned char
{
    None = 0,
    Rectangle = 1,
    Circle,
    Triangle,
    Polyline,
    Line
};

class Graph
{
public:
    Graph( Shape shape );
    virtual ~Graph( );
    virtual void Draw( CDC* pDC ) = 0;
    Shape        GetType( ) const;
    void         AddVertex( CPoint point );

protected:
    COLORREF m_background, m_foreground;
    bool     m_isForeVisible;
    bool     m_isBackVisible;

    unsigned short m_penWidth;

    Shape m_shapeType;

    std::vector<CPoint> m_vertices;

    unsigned short m_layer;
};
class IDrawCommand;
class GraphFactory
{
public:
    using Method = std::function<IDrawCommand*( )>;
    static GraphFactory& GetInstance( );    // Singleton

    void          Register( Shape type, Method method );
    IDrawCommand* Create( Shape shape ) const;

private:
    std::unordered_map<Shape, Method> m_factoryMap;
};

class GRectangle final : public Graph
{
public:
    GRectangle( );
    void        Draw( CDC* pDC ) override;
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

class GLine final : public Graph
{
public:
    GLine( );
    void        Draw( CDC* pDC ) override;
    static void Register( );
};

/* 可以提供一个Clone方法，绘制完成时直接将所有点拷贝 原型模式 */
class GPolyline final : public Graph
{
public:
    enum class status : unsigned char
    {
        Start,
        Editing,
        End
    };

    mutable status m_status;

public:
    GPolyline( );
    void        Draw( CDC* pDC ) override;
    static void Register( );
};  