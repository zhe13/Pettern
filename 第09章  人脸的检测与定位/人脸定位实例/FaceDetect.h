// FaceDetect.h : main header file for the FACEDETECT application
//

#if !defined(AFX_FACEDETECT_H__886D028A_D9CC_4C74_BC90_F3DE1357CED5__INCLUDED_)
#define AFX_FACEDETECT_H__886D028A_D9CC_4C74_BC90_F3DE1357CED5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectApp:
// See FaceDetect.cpp for the implementation of this class
//

class CFaceDetectApp : public CWinApp
{
public:
	CFaceDetectApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFaceDetectApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECT_H__886D028A_D9CC_4C74_BC90_F3DE1357CED5__INCLUDED_)
