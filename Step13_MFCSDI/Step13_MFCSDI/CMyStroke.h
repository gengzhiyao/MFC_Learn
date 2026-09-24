#pragma once
#include <vector>
#include <afx.h>
class CMyStroke
{
public:
    void Store( const CPoint& pt );
    void PrePoint( const CPoint& pt );
    CPoint GetPrePt( ) { return m_prePt; }
    void   SetPrePt( const CPoint& pt ) { m_prePt = pt; }
    size_t GetSize( ) { return m_ptArray.size( ); }
    const CPoint& GetStrokePt( size_t idx ) { return m_ptArray.at( idx ); }

//private:
    std::vector<CPoint> m_ptArray;
    CPoint              m_prePt;
};
