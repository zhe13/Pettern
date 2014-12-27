// patternDlg.h : header file
//
#include <afxwin.h>
#include "Afx.h"
#include  "Inputdialog.h"
#include   "AFXPRIV.H"
#include "TCHAR.H"
#include "Store.h"
#include <afx.h>
//#define   _MBCS

#if !defined(AFX_PATTERNDLG_H__B6F25445_4850_4981_8D91_7D63973BBB61__INCLUDED_)
#define AFX_PATTERNDLG_H__B6F25445_4850_4981_8D91_7D63973BBB61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPatternDlg dialog

class CPatternDlg : public CDialog
{
// Construction
public:
	void Inorder();
	void OnSaveMenu1();
    int   OnRecogch();
	int mouseDown;
	CPatternDlg(CWnd* pParent = NULL);
	// standard constructor
    
     

// Dialog Data
	//{{AFX_DATA(CPatternDlg)
	enum { IDD = IDD_PATTERN_DIALOG };
	CEdit	m_edit2;
	CEdit	m_edit1;
	CButton	m_escape;
	CButton	m_clear;
	CButton	m_recog;
	CButton	m_study;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatternDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;

//CFile cf;
	// Generated message map functions
	//{{AFX_MSG(CPatternDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEsp();
	afx_msg void OnRecog();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClear();
	afx_msg void OnStudy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int Ridnoise(int j);
	afx_msg int  Getarc(int j);
	afx_msg void Save(int k);
	afx_msg void  DealData();
	afx_msg void OnExitMenu();
	afx_msg void OnAboutMenu();
	afx_msg void OnSaveMenu();
	afx_msg void OnOpenMenu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERNDLG_H__B6F25445_4850_4981_8D91_7D63973BBB61__INCLUDED_)
