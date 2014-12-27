// patternDoc.h : interface of the CPatternDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATTERNDOC_H__BF2B2994_C029_4E97_9A64_57A1EE7E031C__INCLUDED_)
#define AFX_PATTERNDOC_H__BF2B2994_C029_4E97_9A64_57A1EE7E031C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPatternDoc : public CDocument
{
protected: // create from serialization only
	CPatternDoc();
	DECLARE_DYNCREATE(CPatternDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatternDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPatternDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPatternDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERNDOC_H__BF2B2994_C029_4E97_9A64_57A1EE7E031C__INCLUDED_)
