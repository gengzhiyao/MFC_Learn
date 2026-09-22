#include "CMyStroke.h"

void CMyStroke::Store( CPoint pt ) { m_ptArray.push_back( pt ); }

void CMyStroke::PrePoint( const CPoint& pt ) { m_prePt = pt; }
