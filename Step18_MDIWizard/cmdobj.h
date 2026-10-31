#pragma once
#include "DrawCommand.h"
class LineCmd : public IDrawCommand
{
public:
    LineCmd( );
    virtual void Draw( CDC* pDC ) override;
};

class RectangleCmd : public IDrawCommand
{
public:
    RectangleCmd( );
    virtual void Draw( CDC* pDC ) override;
};

class TriangleCmd : public IDrawCommand
{
public:
    TriangleCmd( );
    virtual void Draw( CDC* pDC ) override;
};

class CircleCmd : public IDrawCommand
{
public:
    CircleCmd( );
    virtual void Draw( CDC* pDC ) override;
};

class PolylineCmd : public IDrawCommand
{
public:
    PolylineCmd( );
    virtual void Draw( CDC* pDC ) override;
};
