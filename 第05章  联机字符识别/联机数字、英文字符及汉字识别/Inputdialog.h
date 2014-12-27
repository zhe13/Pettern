#if !defined(AFX_INPUTDIALOG_H__C9846DE6_B240_4899_9A19_5A316DF6FBFB__INCLUDED_)
#define AFX_INPUTDIALOG_H__C9846DE6_B240_4899_9A19_5A316DF6FBFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "TCHAR.H"

//#define   _MBCS
 // _MSC_VER > 1000
// Inputdialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Inputdialog dialog

class Inputdialog : public CDialog
{
// Construction
public:
	Inputdialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Inputdialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_input2;
	CString	m_input1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Inputdialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Inputdialog)
	afx_msg void Onok();
	afx_msg void Oncancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDIALOG_H__C9846DE6_B240_4899_9A19_5A316DF6FBFB__INCLUDED_)
