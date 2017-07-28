#include "stdafx.h"
#include "OurConstants.h"
#include "Elements.h"
#include <math.h>

CLine::CLine(const CPoint &Start, const CPoint &End, const COLORREF &Color)
{
	m_StartPoint = Start;
	m_EndPoint = End;
	m_Color = Color;
	m_Pen = 1;

	m_EnclosingRect = CRect(Start,End);
	m_EnclosingRect.NormalizeRect();

}

void CLine::Draw(CDC *pDC) const
{
	CPen aPen;
	if(!aPen.CreatePen(PS_SOLID,m_Pen,m_Color))
	{
		AfxMessageBox("Pen creation failed drawing a line", MB_OK,0);
		AfxAbort();
	}

	CPen* pOldPen  = pDC->SelectObject(&aPen);

	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	pDC->SelectObject(pOldPen);
}

CRect CElement::GetBoundRect() const
{
	CRect BoundingRect;
	BoundingRect = m_EnclosingRect;
	BoundingRect.InflateRect(m_Pen,m_Pen);

	return BoundingRect;
}

CRectangle::CRectangle(const CPoint &Start, const CPoint &End, const COLORREF &Color)
{
	m_Color = Color;
	m_Pen = 1;

	m_EnclosingRect = CRect(Start,End);
	m_EnclosingRect.NormalizeRect();
}

void CRectangle::Draw(CDC *pDC) const
{
	CPen aPen;
	if(!aPen.CreatePen(PS_SOLID,m_Pen,m_Color))
	{
		AfxMessageBox("Pen creation failed drawing a rectangle",MB_OK);
		AfxAbort();
	}

	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	pDC->Rectangle(m_EnclosingRect);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

CCircle::CCircle(const CPoint &Start, const CPoint &End, const COLORREF &Color)
{
	long Radius = static_cast<long>(sqrt(static_cast<double>((End.x - Start.x)*(End.x - Start.x)+(End.y - Start.y)*(End.y - Start.y))));
	m_EnclosingRect = CRect(Start.x - Radius,Start.y - Radius,Start.y - Radius,Start.y + Radius);
	m_Color = Color;
	m_Pen = 1;
}

void CCircle::Draw(CDC *pDC) const
{
	CPen aPen;
	if(!aPen.CreatePen(PS_SOLID,m_Pen,m_Color))
	{
		AfxMessageBox("Pen creation failed drawing a rectangle",MB_OK,0);
		AfxAbort();
	}

	CPen* pOldPen = pDC->SelectObject(&aPen);
	CBrush* pOldBrush = static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	pDC->Ellipse(m_EnclosingRect);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CCurve::CCurve(const COLORREF &Color)
{
	m_Color= Color;
	m_EnclosingRect;
	m_Pen = 1;
}

void CCurve::Draw(CDC *pDC) const
{

}






	








