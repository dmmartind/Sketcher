#if !defined(Elements_h)
#define Elements_h

class CElement: public CObject
{
protected:
	COLORREF m_Color;
	CRect m_EnclosingRect;
	int m_Pen;

public:
	virtual ~CElement(){}

	virtual void Draw(CDC* pDC) const{}
	CRect GetBoundRect() const;
protected:
	CElement(){}
};

class CLine: public CElement
{
public:
	virtual void Draw(CDC* pDC) const;

	CLine(const CPoint& Start, const CPoint& END,const COLORREF& Color);

protected:
	CPoint m_StartPoint;
	CPoint m_EndPoint;

	CLine(){}

};

class CRectangle:public CElement
{
public:
	virtual void Draw(CDC* pDC) const;

	CRectangle(const CPoint& Start, const CPoint& End, const COLORREF& Color);

protected:
	CRectangle(){}
	

};

class CCircle : public CElement
{
public:
	virtual void Draw(CDC* pDC) const;
	CCircle(const CPoint& Start, const CPoint& End, const COLORREF& Color);

protected:
	CCircle(){}


};

class CCurve : public CElement
{
public:
	virtual void Draw(CDC* pDC) const;

	CCurve(const COLORREF& Color);

protected:
	CCurve(){}

};

#endif



