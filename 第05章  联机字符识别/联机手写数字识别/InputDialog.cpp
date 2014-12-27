// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "pattern.h"
#include "InputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InputDialog dialog


InputDialog::InputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(InputDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(InputDialog)
	m_value1 = 0;
	m_value2 = 0;
	//}}AFX_DATA_INIT
}


void InputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InputDialog)
	DDX_Text(pDX, IDC_EDIT1, m_value1);
	DDV_MinMaxUInt(pDX, m_value1, 0, 9);
	DDX_Text(pDX, IDC_EDIT2, m_value2);
	DDV_MinMaxUInt(pDX, m_value2, 0, 9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InputDialog, CDialog)
	//{{AFX_MSG_MAP(InputDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InputDialog message handlers
