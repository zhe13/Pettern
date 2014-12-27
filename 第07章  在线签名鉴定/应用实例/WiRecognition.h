// WiRecognition.h : main header file for the WIRECOGNITION application
//

#if !defined(AFX_WIRECOGNITION_H__02FFADBF_4070_409F_87CD_35C7D19886B4__INCLUDED_)
#define AFX_WIRECOGNITION_H__02FFADBF_4070_409F_87CD_35C7D19886B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWiRecognitionApp:
// See WiRecognition.cpp for the implementation of this class
//

class CWiRecognitionApp : public CWinApp
{
public:
	CWiRecognitionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWiRecognitionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWiRecognitionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIRECOGNITION_H__02FFADBF_4070_409F_87CD_35C7D19886B4__INCLUDED_)
