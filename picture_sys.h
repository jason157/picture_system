// picture_sys.h : main header file for the PICTURE_SYS application
//

#if !defined(AFX_PICTURE_SYS_H__6DF2C541_B275_43E2_A02F_7342E750971C__INCLUDED_)
#define AFX_PICTURE_SYS_H__6DF2C541_B275_43E2_A02F_7342E750971C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPicture_sysApp:
// See picture_sys.cpp for the implementation of this class
//

class CPicture_sysApp : public CWinApp
{
public:
	CPicture_sysApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicture_sysApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPicture_sysApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURE_SYS_H__6DF2C541_B275_43E2_A02F_7342E750971C__INCLUDED_)
