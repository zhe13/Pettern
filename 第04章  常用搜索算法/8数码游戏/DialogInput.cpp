// DialogInput.cpp : implementation file
//

#include "stdafx.h"
#include "Jiugong.h"
#include "DialogInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogInput dialog


CDialogInput::CDialogInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogInput)
	m_int00 = 0;
	m_int01 = 0;
	m_int02 = 0;
	m_int10 = 0;
	m_int11 = 0;
	m_int12 = 0;
	m_int20 = 0;
	m_int21 = 0;
	m_int22 = 0;
	//}}AFX_DATA_INIT
}


void CDialogInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogInput)
	DDX_Text(pDX, IDC_EDIT1, m_int00);
	DDX_Text(pDX, IDC_EDIT2, m_int01);
	DDX_Text(pDX, IDC_EDIT3, m_int02);
	DDX_Text(pDX, IDC_EDIT4, m_int10);
	DDX_Text(pDX, IDC_EDIT5, m_int11);
	DDX_Text(pDX, IDC_EDIT6, m_int12);
	DDX_Text(pDX, IDC_EDIT7, m_int20);
	DDX_Text(pDX, IDC_EDIT8, m_int21);
	DDX_Text(pDX, IDC_EDIT9, m_int22);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogInput, CDialog)
	//{{AFX_MSG_MAP(CDialogInput)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogInput message handlers
