
// SketcherView.cpp : implementation of the CSketcherView class
//

#include "stdafx.h"
#include "Sketcher.h"

#include "SketcherDoc.h"
#include "Elements.h"
#include "SketcherView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CView)

BEGIN_MESSAGE_MAP(CSketcherView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSketcherView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CSketcherView construction/destruction

CSketcherView::CSketcherView()
{
	m_FirstPoint = CPoint(0,0);
	m_SecondPoint = CPoint(0,0);
	m_pTempElement = 0;

}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSketcherView drawing

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	{
		AfxMessageBox("ERROR",MB_OK);	
		return;
	}
}


// CSketcherView printing


void CSketcherView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSketcherView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSketcherView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSketcherView diagnostics

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketcherView message handlers

void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CView::OnLButtonDown(nFlags, point);
	m_FirstPoint = point;
	SetCapture();


}

void CSketcherView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(this == GetCapture())
		ReleaseCapture();
	

	
	if(m_pTempElement)
	{
		delete m_pTempElement;
		m_pTempElement = 0;
	}


}

void CSketcherView::OnMouseMove(UINT nFlags, CPoint point)
{
// Define a Device Context object for the view
	CClientDC aDC(this); // DC is for this

	aDC.SetROP2(R2_NOTXORPEN); // Set the drawing

	if((nFlags&MK_LBUTTON) && (this == GetCapture()))
	{
			m_SecondPoint = point; // Save the current
			if(m_pTempElement)
			{
				// Redraw the old element so it disappears from the view
				m_pTempElement->Draw(&aDC);
				delete m_pTempElement; // Delete the old
				m_pTempElement = 0; // Reset the pointer
			}


		// Create a temporary element of the type and color that
		// is recorded in the document object, and draw it
		m_pTempElement = CreateElement(); // Create a new
		m_pTempElement->Draw(&aDC); // Draw the element
	}
}


	CElement* CSketcherView::CreateElement()
	{
		CSketcherDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		switch(pDoc->GetElementType())
		{
		case RECTANGLE:
			return new CRectangle(m_FirstPoint,m_SecondPoint,pDoc->GetElementColor());
		case CIRCLE:
			return new CCircle(m_FirstPoint,m_SecondPoint,pDoc->GetElementColor());
		case CURVE:
			return new CCurve(pDoc->GetElementColor());
		case LINE:
			return new CLine(m_FirstPoint,m_SecondPoint,pDoc->GetElementColor());

		default: 
			AfxMessageBox("Bad Element Code",MB_OK);
			AfxAbort();
			return NULL;

		}
	}












