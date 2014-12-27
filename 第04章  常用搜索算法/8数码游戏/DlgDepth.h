#if !defined(AFX_DLGDEPTH_H__E7EB8246_506E_4C23_A0C5_91A423218CF9__INCLUDED_)
#define AFX_DLGDEPTH_H__E7EB8246_506E_4C23_A0C5_91A423218CF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDepth.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDepth dialog

class CDlgDepth : public CDialog
{
// Construction
public:
	CDlgDepth(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDepth)
	enum { IDD = IDD_DIALOG_DEPTH };
	int		m_depth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDepth)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDepth)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEPTH_H__E7EB8246_506E_4C23_A0C5_91A423218CF9__INCLUDED_)
