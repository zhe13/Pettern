// DlgDepth.cpp : implementation file
//

#include "stdafx.h"
#include "Jiugong.h"
#include "DlgDepth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDepth dialog


CDlgDepth::CDlgDepth(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDepth::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDepth)
	m_depth = 0;
	//}}AFX_DATA_INIT
}


void CDlgDepth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDepth)
	DDX_Text(pDX, IDC_EDIT1, m_depth);
	DDV_MinMaxInt(pDX, m_depth, 25, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDepth, CDialog)
	//{{AFX_MSG_MAP(CDlgDepth)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDepth message handlers
