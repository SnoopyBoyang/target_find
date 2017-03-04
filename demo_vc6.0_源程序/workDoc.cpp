// workDoc.cpp : implementation of the CWorkDoc class
//

#include "stdafx.h"
#include "work.h"

#include "workDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkDoc

IMPLEMENT_DYNCREATE(CWorkDoc, CDocument)

BEGIN_MESSAGE_MAP(CWorkDoc, CDocument)
	//{{AFX_MSG_MAP(CWorkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkDoc construction/destruction

CWorkDoc::CWorkDoc()
{
	// TODO: add one-time construction code here

}

CWorkDoc::~CWorkDoc()
{
}

BOOL CWorkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWorkDoc serialization

void CWorkDoc::Serialize(CArchive& ar)
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
// CWorkDoc diagnostics

#ifdef _DEBUG
void CWorkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWorkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkDoc commands
