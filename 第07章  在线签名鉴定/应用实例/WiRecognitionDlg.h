// WiRecognitionDlg.h : header file
//

#if !defined(AFX_WIRECOGNITIONDLG_H__74619567_138C_4B14_A42C_A74BC24ACF3B__INCLUDED_)
#define AFX_WIRECOGNITIONDLG_H__74619567_138C_4B14_A42C_A74BC24ACF3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWiRecognitionDlg dialog

#include "Wi.h"
#include "AddSampleDlg.h"

class CWiRecognitionDlg : public CDialog
{
// Construction
public:
	CWiRecognitionDlg(CWnd* pParent = NULL);// standard constructor
	void DrawPicture(CWi::Sample* s,HDC hDC);
	void DrawPress(CWi::Sample *s,HDC hDC);
	CWi wi;
	int numOfTrain,numOfTest,currTrain,currTest;
	int pressPos;
	int m_Method;
	int m_TestTrain;
// Dialog Data
	//{{AFX_DATA(CWiRecognitionDlg)
	enum { IDD = IDD_WIRECOGNITION_DIALOG };
	CScrollBar	m_ctrlScroll;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWiRecognitionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWiRecognitionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExit();
	afx_msg void OnInputTrain();
 	afx_msg void OnShow1();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	afx_msg void OnInputTest();
	afx_msg void OnShow2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
 	afx_msg void OnGentemp();
	afx_msg void OnRecognition();
	afx_msg void OnSaveTemp();
	afx_msg void OnLoadTemp();
 	afx_msg void OnSelchangeMethod();
	afx_msg void OnRadioTest();
	afx_msg void OnRadioTrain();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIRECOGNITIONDLG_H__74619567_138C_4B14_A42C_A74BC24ACF3B__INCLUDED_)
