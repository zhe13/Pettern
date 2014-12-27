// FaceDetectDlg.h : header file
//

#ifndef __FACEDETECTDLG_H
#define __FACEDETECTDLG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dib.h"
#include "LikelyHood.h"
#include "HairFace.h"
#include <afxtempl.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectDlg dialog

class CFaceDetectDlg : public CDialog
{
// Construction
public:
	CFaceDetectDlg(CWnd* pParent = NULL);	// standard constructor

	//公共变量
public:
	void MyDraw();
	void DoLOG(int left,int right,int top,int bottom,RGBQUAD** source,RGBQUAD** target);
	void SetPixelArray(RGBQUAD** target,int Val);
	void LoadOriPixel(CDib* pDib);
	void MakeBitMap();
	bool CopyBitMap(RGBQUAD** dest,RGBQUAD** source);
	void DrawCross(CDC* pDC,CPoint point,COLORREF crColor);

	CDC *pDCShow;//用来画图的区域
	CDib *m_pMainDib;//位图
	RGBQUAD** m_tOriPixelArray;//原始位图数据
	RGBQUAD** m_tResPixelArray;//参考位图数据

	CBitmap* 	m_pResMap;

	int m_nWndWidth;//图像宽度
	int m_nWndHeight;//图像高度
	CString m_sFileName;//位图名称

	bool m_bFaceOK;//脸部已经确定标志位
	bool m_bShowFace;
	CRect m_rFaceRegion;//脸部区域

	bool m_bSelectByMan;
	bool m_bLBottonDown;
	int m_ManLeft;
	int m_ManRight;
	int m_ManTop;
	int m_ManBottom;

	//下面是一些标志位
	bool m_bManualMarkFacial;
	bool m_bLeftEyeOK;//左眼确定标志位
	bool m_bRightEyeOK;//右眼确定标志位
	bool m_bLeftEyeLeftCornerOK;//左眼左角
	bool m_bLeftEyeRightCornerOK;//左眼右角
	bool m_bRightEyeLeftCornerOK;//右眼左角
	bool m_bRightEyeRightCornerOK;//右眼右角
	bool m_bLeftNostrilOK;//左鼻角
	bool m_bRightNostrilOK;//右鼻角
	bool m_bLeftMouthCornerOK;//左嘴角
	bool m_bRightMouthCornerOK;//右嘴角
	bool m_bMidMouthOK;//嘴中部
	bool m_bMidNoseOK;//鼻尖
	//下面是上那些特征点的位置
	CPoint m_LeftEye;
	CPoint m_LeftEyeLeftCorner;
	CPoint m_LeftEyeRightCorner;
	CPoint m_RightEye;
	CPoint m_RightEyeLeftCorner;
	CPoint m_RightEyeRightCorner;
	CPoint m_LeftNostril;
	CPoint m_RightNostril;
	CPoint m_LeftMouthCorner;
	CPoint m_RightMouthCorner;
	CPoint m_MidMouth;
	CPoint m_MidNose;

	//两种方法
	CLikelyHood	*method1;
	CHairFace   *method2;

// Dialog Data
	//{{AFX_DATA(CFaceDetectDlg)
	enum { IDD = IDD_FACEDETECT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFaceDetectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBinary();
	afx_msg void OnBtnEdge();
	afx_msg void OnBtnFacehair();
	afx_msg void OnBtnHistogramFace();
	afx_msg void OnBtnHistogramH();
	afx_msg void OnBtnHistogramHair();
	afx_msg void OnBtnHistogramV();
	afx_msg void OnBtnLikehood();
	afx_msg void OnBtnMarkEye();
	afx_msg void OnBtnMarkFace1();
	afx_msg void OnBtnMarkFace2();
	afx_msg void OnBtnMarkMouse();
	afx_msg void OnBtnMarkNose();
	afx_msg void OnBtnOpenfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // #ifndef __FACEDETECTDLG_H
