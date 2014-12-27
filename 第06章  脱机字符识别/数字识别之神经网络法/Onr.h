// Onr.h : main header file for the ONR application
//

#if !defined(AFX_ONR_H__B68A5325_43B0_11D3_96EE_F0A5A92B9882__INCLUDED_)
#define AFX_ONR_H__B68A5325_43B0_11D3_96EE_F0A5A92B9882__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COnrApp:
// See Onr.cpp for the implementation of this class
//

class COnrApp : public CWinApp
{
public:
	COnrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COnrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONR_H__B68A5325_43B0_11D3_96EE_F0A5A92B9882__INCLUDED_)
