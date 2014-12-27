#if !defined(AFX_STORE_H__5E2BD89A_794B_4B5F_8107_4FE19D1EC4F1__INCLUDED_)
#define AFX_STORE_H__5E2BD89A_794B_4B5F_8107_4FE19D1EC4F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
 #include "Afx.h"
 #include  "Inputdialog.h"
#include   "AFXPRIV.H"
#include "TCHAR.H"

//#define   _MBCS



// _MSC_VER > 1000
// Store.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Store window

class Store : public CEdit
{
// Construction
public:
	

// Attributes
public:

// Operations
public:

// Overrides
   int total;
    int dian[15];
    CString zifu;
 struct{int relate;
        int region;
       int arc  ;}detail[15][20];
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Store)
	//}}AFX_VIRTUAL

// Implementation
public:


	// Generated message map functions
protected:
	//{{AFX_MSG(Store)
    


		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STORE_H__5E2BD89A_794B_4B5F_8107_4FE19D1EC4F1__INCLUDED_)
