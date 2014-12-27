#if !defined(AFX_REPLACEDLG_H__57EAD515_910B_4509_9484_B2E75BA8B11D__INCLUDED_)
#define AFX_REPLACEDLG_H__57EAD515_910B_4509_9484_B2E75BA8B11D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplaceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ReplaceDlg dialog

class ReplaceDlg : public CDialog
{
// Construction
public:
	ReplaceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ReplaceDlg)
	enum { IDD = IDD_DIALOG_REPLACE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ReplaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ReplaceDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACEDLG_H__57EAD515_910B_4509_9484_B2E75BA8B11D__INCLUDED_)
