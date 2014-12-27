// Inputdialog.cpp : implementation file
//

#include "stdafx.h"
#include "pattern.h"
#include "Inputdialog.h"

#include "TCHAR.H"


#define   _UNICODE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Inputdialog dialog


Inputdialog::Inputdialog(CWnd* pParent /*=NULL*/)
	: CDialog(Inputdialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(Inputdialog)
	m_input2 = _T("");
	m_input1 = _T("");
	//}}AFX_DATA_INIT
}


void Inputdialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Inputdialog)
	DDX_Text(pDX, IDC_EDIT2, m_input2);
	DDV_MaxChars(pDX, m_input2, 2);
	DDX_Text(pDX, IDC_EDIT1, m_input1);
	DDV_MaxChars(pDX, m_input1, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Inputdialog, CDialog)
	//{{AFX_MSG_MAP(Inputdialog)
	ON_BN_CLICKED(IDC_BUTTON1, Onok)
	ON_BN_CLICKED(IDC_BUTTON2, Oncancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Inputdialog message handlers

void Inputdialog::Onok() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void Inputdialog::Oncancel() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
