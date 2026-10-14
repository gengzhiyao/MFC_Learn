#pragma once
#include "pch.h"
#include "Shape.h"
class IDrawCommand
{
public:
    IDrawCommand( Graph* thisGraph )
        : m_pGraph( thisGraph )
    {
    }
    virtual ~IDrawCommand( ) { delete m_pGraph; }
    virtual void Draw( CDC* pDC ) = 0;
    Graph*       GetOwnerGraph( ) const { return m_pGraph; }

protected:
    Graph* m_pGraph;
};

inline void IDrawCommand::Draw( CDC* pDC ) { m_pGraph->Draw( pDC ); };
