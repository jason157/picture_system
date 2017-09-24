#if !defined SPLASH_H
#define SPLASH_H

// WzdSplsh.h : header file
//
#include "Cbtmap.h"
/////////////////////////////////////////////////////////////////////////////
// CWzdSplash window
class Csplash : public CWnd
{
// Construction
public:
    Csplash();
// Attributes
public:
// Operations
public:
    void Create( UINT nBitmapID );
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWzdSplash)
    //}}AFX_VIRTUAL
// Implementation
public:
    virtual ~Csplash();
    // Generated message map functions
protected:
    //{{AFX_MSG(CWzdSplash)
    afx_msg void OnPaint();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    Cbtmap m_bitmap;
};
/////////////////////////////////////////////////////////////////////////////
#endif
