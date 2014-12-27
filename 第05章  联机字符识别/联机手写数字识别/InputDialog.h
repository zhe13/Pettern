#if !defined(AFX_INPUTDIALOG_H__B0B0D872_FF9A_40E6_9A62_C7DDC51DA244__INCLUDED_)
#define AFX_INPUTDIALOG_H__B0B0D872_FF9A_40E6_9A62_C7DDC51DA244__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// InputDialog dialog

class InputDialog : public CDialog
{
// Construction
public:
	InputDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(InputDialog)
	enum { IDD = IDD_DIALOG_INPUT };
	UINT	m_value1;
	UINT	m_value2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InputDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDIALOG_H__B0B0D872_FF9A_40E6_9A62_C7DDC51DA244__INCLUDED_)
