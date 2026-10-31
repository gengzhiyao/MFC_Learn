#include "pch.h"
#include "cmdobj.h"
LineCmd::LineCmd( )
    : IDrawCommand( new GLine )
{
}

RectangleCmd::RectangleCmd( )
    : IDrawCommand( new GRectangle )
{
}

TriangleCmd::TriangleCmd( )
    : IDrawCommand( new GTriangle )
{
}

CircleCmd::CircleCmd( )
    : IDrawCommand( new GCircle )
{
}

PolylineCmd::PolylineCmd( )
    : IDrawCommand( new GPolyline )
{
}

void LineCmd::Draw( CDC* pDC ) { return IDrawCommand::Draw( pDC ); }
void RectangleCmd::Draw( CDC* pDC ) { return IDrawCommand::Draw( pDC ); }
void TriangleCmd::Draw( CDC* pDC ) { return IDrawCommand::Draw( pDC ); }
void CircleCmd::Draw( CDC* pDC ) { return IDrawCommand::Draw( pDC ); }
void PolylineCmd::Draw( CDC* pDC ) { return IDrawCommand::Draw( pDC ); }