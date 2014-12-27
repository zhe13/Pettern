// PatternView.cpp : implementation file
//

#include "stdafx.h"
#include "pattern.h"
#include "PatternView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define Startx 30
#define Starty 190
#define wid  160
#define lon 192
/////////////////////////////////////////////////////////////////////////////
// CPatternView

IMPLEMENT_DYNCREATE(CPatternView, CView)

CPatternView::CPatternView()
{
	EnableAutomation();
}

CPatternView::~CPatternView()
{
}

void CPatternView::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CView::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CPatternView, CView)
	//{{AFX_MSG_MAP(CPatternView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPatternView, CView)
	//{{AFX_DISPATCH_MAP(CPatternView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IPatternView to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {0E3CDA46-A735-4F99-8D38-F0C983BF920A}
static const IID IID_IPatternView =
{ 0xe3cda46, 0xa735, 0x4f99, { 0x8d, 0x38, 0xf0, 0xc9, 0x83, 0xbf, 0x92, 0xa } };

BEGIN_INTERFACE_MAP(CPatternView, CView)
	INTERFACE_PART(CPatternView, IID_IPatternView, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatternView drawing

void CPatternView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}



void CPatternView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDC *pDC=GetDC();

	CRgn Rgn;
	Rgn.CreateRectRgn(Startx,Starty,Startx+wid,Starty+lon);
	pDC->SelectClipRgn(&Rgn);
	if((point.x>=Startx)&&(point.x<Startx+wid)&&(point.y>=Starty)&&(point.y<Starty+lon)){
		HCURSOR m_HCross;
		m_HCross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);
		::SetCursor(m_HCross);
	}
	//int i=(point.x-startX)/stepX;
	//int j=(point.y-startY)/stepY;
	//if((mouseDown==1)&&(point.x>=startX)&&(point.x<startX+stepX*16)&&(point.y>=startY)&&(point.y<startY+stepY*16)){
		/*WNDCLASS winclass;
		wndclass.hCursor=::LoadCursor(IDC_CROSS);
		::SetCursor(hCursor);*/
	//}
}

/////////////////////////////////////////////////////////////////////////////
// CPatternView diagnostics

#ifdef _DEBUG
void CPatternView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPatternView message handlers
