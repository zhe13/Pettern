// bwDoc.cpp : implementation of the CBwDoc class
//

#include "stdafx.h"
#include "bw.h"

#include "bwDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBwDoc

IMPLEMENT_DYNCREATE(CBwDoc, CDocument)

BEGIN_MESSAGE_MAP(CBwDoc, CDocument)
	//{{AFX_MSG_MAP(CBwDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBwDoc construction/destruction

CBwDoc::CBwDoc()
{
	// TODO: add one-time construction code here

}

CBwDoc::~CBwDoc()
{
}

BOOL CBwDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBwDoc serialization

void CBwDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBwDoc diagnostics

#ifdef _DEBUG
void CBwDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBwDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBwDoc commands
