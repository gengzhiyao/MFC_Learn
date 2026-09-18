#include "CMyStroke.h"

void CMyStroke::Store( const CPoint& pt ) { m_ptArray.push_back( pt ); }

void CMyStroke::PrePoint( const CPoint& pt ) { m_prePt = pt; }
