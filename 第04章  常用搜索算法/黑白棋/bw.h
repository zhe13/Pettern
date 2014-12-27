// bw.h : main header file for the BW application
//

#if !defined(AFX_BW_H__A0F5FD24_AB23_4B37_8CF5_9E60170E9A19__INCLUDED_)
#define AFX_BW_H__A0F5FD24_AB23_4B37_8CF5_9E60170E9A19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBwApp:
// See bw.cpp for the implementation of this class
//

class CBwApp : public CWinApp
{
public:
	CBwApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBwApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBwApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BW_H__A0F5FD24_AB23_4B37_8CF5_9E60170E9A19__INCLUDED_)
