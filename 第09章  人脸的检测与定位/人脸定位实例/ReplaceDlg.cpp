// ReplaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "ReplaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ReplaceDlg dialog


ReplaceDlg::ReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ReplaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ReplaceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ReplaceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ReplaceDlg, CDialog)
	//{{AFX_MSG_MAP(ReplaceDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ReplaceDlg message handlers
