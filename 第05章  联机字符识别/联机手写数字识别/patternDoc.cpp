// patternDoc.cpp : implementation of the CPatternDoc class
//

#include "stdafx.h"
#include "pattern.h"

#include "patternDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatternDoc

IMPLEMENT_DYNCREATE(CPatternDoc, CDocument)

BEGIN_MESSAGE_MAP(CPatternDoc, CDocument)
	//{{AFX_MSG_MAP(CPatternDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatternDoc construction/destruction

CPatternDoc::CPatternDoc()
{
	// TODO: add one-time construction code here

}

CPatternDoc::~CPatternDoc()
{
}

BOOL CPatternDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPatternDoc serialization

void CPatternDoc::Serialize(CArchive& ar)
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
// CPatternDoc diagnostics

#ifdef _DEBUG
void CPatternDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPatternDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPatternDoc commands
