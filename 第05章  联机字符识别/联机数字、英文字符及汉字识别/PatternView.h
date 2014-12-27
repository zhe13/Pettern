#if !defined(AFX_PATTERNVIEW_H__A3806B11_AC72_465D_BB38_6A47D635CBF4__INCLUDED_)
#define AFX_PATTERNVIEW_H__A3806B11_AC72_465D_BB38_6A47D635CBF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
#define   _MBCS

// _MSC_VER > 1000
// PatternView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPatternView view

class CPatternView : public CView
{
protected:
	CPatternView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPatternView)
  void OnMouseMove(UINT nFlags, CPoint point);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatternView)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPatternView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPatternView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CPatternView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERNVIEW_H__A3806B11_AC72_465D_BB38_6A47D635CBF4__INCLUDED_)
