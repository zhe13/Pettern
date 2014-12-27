// bwView.h : interface of the CBwView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BWVIEW_H__A8176727_C457_4237_A1AB_4B5371366E7A__INCLUDED_)
#define AFX_BWVIEW_H__A8176727_C457_4237_A1AB_4B5371366E7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WHITE -1;
#define BLACK 1;
#define EMPTY 0;
#include "math.h"
#include "bwfind.h"
class CBwView : public CView
{
public:
	int ManChoice,ManTurn,ComChoice,ComTurn;
	CBitmap m_black;
	CBitmap m_white;
	CBitmap m_board;
	CBitmap m_last;
	CBwfind m_find;
private:
	BOOL play;
	BOOL start;
	BOOL think;
	BOOL wrong;
	BOOL tie;
	BOOL msg,pass,comw,manw;
	int pointy;
	int pointx;
	BOOL draw;
protected: // create from serialization only
	CBwView();
	DECLARE_DYNCREATE(CBwView)

// Attributes
public:
	CBwDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBwView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBwView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBwView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBlack();
	afx_msg void OnWhite();
	afx_msg void OnReg();
	afx_msg void OnThree();
	afx_msg void OnTwo();
	afx_msg void OnOne();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in bwView.cpp
inline CBwDoc* CBwView::GetDocument()
   { return (CBwDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BWVIEW_H__A8176727_C457_4237_A1AB_4B5371366E7A__INCLUDED_)
