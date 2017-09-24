// picture_sysView.h : interface of the CPicture_sysView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_SYSVIEW_H__367B60E0_0D1D_4D53_9C4D_1A6F0B604F1E__INCLUDED_)
#define AFX_PICTURE_SYSVIEW_H__367B60E0_0D1D_4D53_9C4D_1A6F0B604F1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPicture_sysView : public CScrollView
{
protected: // create from serialization only
	CPicture_sysView();
	DECLARE_DYNCREATE(CPicture_sysView)

// Attributes
public:
	CPicture_sysDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicture_sysView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	protected:
	virtual void OnInitialUpdate();

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPicture_sysView();
	//int m_ipzLeft,m_ipzRight,m_ipzBottom,m_ipzTop;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPicture_sysView)
	afx_msg void Onscan();
	afx_msg void Onslide();
	afx_msg void OnFadein();
	afx_msg LRESULT OnDoRealize(WPARAM wParam, LPARAM lParam); 
	afx_msg void OnTempSubrect();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnTogray();
	afx_msg void OnGraytocolor();
	afx_msg void OnBinTwo();
	afx_msg void OnClock180();
	afx_msg void OnClock90();
	afx_msg void OnXmirror();
	afx_msg void OnYmirror();
	afx_msg void OnAnticClock90();
	afx_msg void OnRuihua();
	afx_msg void OnCloseOperation();
	afx_msg void OnOpenOperation();
	afx_msg void OnOutline();
	afx_msg void OnRoberts();
	afx_msg void OnTwoExpand();
	afx_msg void OnTwoRot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in picture_sysView.cpp
inline CPicture_sysDoc* CPicture_sysView::GetDocument()
   { return (CPicture_sysDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURE_SYSVIEW_H__367B60E0_0D1D_4D53_9C4D_1A6F0B604F1E__INCLUDED_)
