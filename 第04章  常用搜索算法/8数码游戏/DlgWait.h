#if !defined(AFX_DLGWAIT_H__5545D6B6_C716_43E5_A7DB_1BF06B727609__INCLUDED_)
#define AFX_DLGWAIT_H__5545D6B6_C716_43E5_A7DB_1BF06B727609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWait.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWait dialog

class CDlgWait : public CDialog
{
// Construction
public:
	CDlgWait(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgWait)
	enum { IDD = IDD_DIALOG_WAIT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWait)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWait)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWAIT_H__5545D6B6_C716_43E5_A7DB_1BF06B727609__INCLUDED_)
