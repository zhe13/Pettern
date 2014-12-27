#if !defined(AFX_DIALOGINPUT_H__EA117138_BD44_4579_8172_ECEED94E2C3B__INCLUDED_)
#define AFX_DIALOGINPUT_H__EA117138_BD44_4579_8172_ECEED94E2C3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogInput dialog

class CDialogInput : public CDialog
{
// Construction
public:
	CDialogInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogInput)
	enum { IDD = IDD_DIALOG_INPUT };
	int		m_int00;
	int		m_int01;
	int		m_int02;
	int		m_int10;
	int		m_int11;
	int		m_int12;
	int		m_int20;
	int		m_int21;
	int		m_int22;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogInput)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGINPUT_H__EA117138_BD44_4579_8172_ECEED94E2C3B__INCLUDED_)
