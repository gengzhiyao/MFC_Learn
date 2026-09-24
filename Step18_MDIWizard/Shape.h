#pragma once
#include <afx.h>
enum class Shape : unsigned char
{
    Rectangle = 1,
    Circle,

};

class Graph
{
public:
    Graph( );
    virtual ~Graph( );

protected:
    COLORREF m_background;
    COLORREF m_foreground;
};

class GRectangle : public Graph
{
};

class GCircle : public Graph
{
};