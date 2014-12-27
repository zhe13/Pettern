// bwDoc.h : interface of the CBwDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BWDOC_H__1BFCDB30_6474_466A_89CB_DA4F4E036602__INCLUDED_)
#define AFX_BWDOC_H__1BFCDB30_6474_466A_89CB_DA4F4E036602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBwDoc : public CDocument
{
public:
	
protected: // create from serialization only
	CBwDoc();
	DECLARE_DYNCREATE(CBwDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBwDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBwDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBwDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BWDOC_H__1BFCDB30_6474_466A_89CB_DA4F4E036602__INCLUDED_)
