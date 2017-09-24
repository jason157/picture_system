// picture_sysDoc.h : interface of the CPicture_sysDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_SYSDOC_H__78086854_631C_437C_9B97_AFB3925C1058__INCLUDED_)
#define AFX_PICTURE_SYSDOC_H__78086854_631C_437C_9B97_AFB3925C1058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ImgCenterDib.h"

class CPicture_sysDoc : public CDocument
{
protected: // create from serialization only
	CPicture_sysDoc();
	DECLARE_DYNCREATE(CPicture_sysDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicture_sysDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
   protected:
	//}}AFX_VIRTUAL

// Implementation
public:

	//COLORREF m_refColorBKG;
	//void InitDIBData();
	virtual ~CPicture_sysDoc();
	//返回m_dib的指针
    ImgCenterDib *GetPDib()
	{
		return &m_dib;
	}

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
private:

	//ImgCenterDib类的对象
	ImgCenterDib m_dib;
	
protected:
	//{{AFX_MSG(CPicture_sysDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURE_SYSDOC_H__78086854_631C_437C_9B97_AFB3925C1058__INCLUDED_)
