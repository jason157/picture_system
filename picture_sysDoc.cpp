// picture_sysDoc.cpp : implementation of the CPicture_sysDoc class
//

#include "stdafx.h"
#include "picture_sys.h"

#include "picture_sysDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysDoc

IMPLEMENT_DYNCREATE(CPicture_sysDoc, CDocument)

BEGIN_MESSAGE_MAP(CPicture_sysDoc, CDocument)
	//{{AFX_MSG_MAP(CPicture_sysDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysDoc construction/destruction

CPicture_sysDoc::CPicture_sysDoc()
{
	// TODO: add one-time construction code here

}

CPicture_sysDoc::~CPicture_sysDoc()
{
}

BOOL CPicture_sysDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPicture_sysDoc serialization

void CPicture_sysDoc::Serialize(CArchive& ar)
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
// CPicture_sysDoc diagnostics

#ifdef _DEBUG
void CPicture_sysDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPicture_sysDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysDoc commands
BOOL CPicture_sysDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (m_dib.Read(lpszPathName) == TRUE) {	
		SetModifiedFlag(FALSE);     // start off with unmodified
		return TRUE;
	}
	else 
		return FALSE;
}
BOOL CPicture_sysDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if(m_dib.Write(lpszPathName) == TRUE)	{
		SetModifiedFlag(FALSE);     // have saved
		return TRUE;
	}
	else 
		return FALSE;
}
