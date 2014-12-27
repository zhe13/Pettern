// TextureDlg.h : header file
//

#if !defined(AFX_TEXTUREDLG_H_INCLUDED_)
#define AFX_TEXTUREDLG_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GrayShow.h"

/////////////////////////////////////////////////////////////////////////////
// CTextureDlg dialog

class CTextureDlg : public CDialog
{
// Construction
public:
	void MyDraw();
	void MakeBitmap();
	CTextureDlg(CWnd* pParent = NULL);	// standard constructor

	CGrayShow m_grayShow; //定义一个灰度共现矩阵类
	CBitmap* 	m_pResMap;//用来画位图
	CDC *pDCShow;

// Dialog Data
	//{{AFX_DATA(CTextureDlg)
	enum { IDD = IDD_TEXTURE_DIALOG };
	double	m_dCorrelation;
	double	m_dEnergy;
	double	m_dEntropy;
	double	m_dInertiaQuadrature;
	double	m_dLocalCalm;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTextureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnOpenFile();
	afx_msg void OnBtnComputeTexture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTUREDLG_H_INCLUDED_)
