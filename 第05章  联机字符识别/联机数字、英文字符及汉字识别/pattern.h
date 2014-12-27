// pattern.h : main header file for the PATTERN application
//

#if !defined(AFX_PATTERN_H__C5FAF1EF_9CC9_4154_B23F_3FD1C8A0F692__INCLUDED_)
#define AFX_PATTERN_H__C5FAF1EF_9CC9_4154_B23F_3FD1C8A0F692__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#define   _MBCS

#include "resource.h"		// main symbols
#include "Pattern_i.h"

/////////////////////////////////////////////////////////////////////////////
// CPatternApp:
// See pattern.cpp for the implementation of this class
//

class CPatternApp : public CWinApp
{
public:
	CPatternApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatternApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPatternApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERN_H__C5FAF1EF_9CC9_4154_B23F_3FD1C8A0F692__INCLUDED_)
