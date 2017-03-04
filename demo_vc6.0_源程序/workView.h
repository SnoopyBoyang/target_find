// workView.h : interface of the CWorkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKVIEW_H__067CA72D_175C_45C6_B965_E8A452C78942__INCLUDED_)
#define AFX_WORKVIEW_H__067CA72D_175C_45C6_B965_E8A452C78942__INCLUDED_

#include "Cdib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

void target_find(unsigned char *camera_data,int data_height,int data_width,int gray_threshold,
	               int *is_find,int *target_x,int *target_y);
class CWorkView : public CScrollView
{
protected: // create from serialization only
	CWorkView();
	DECLARE_DYNCREATE(CWorkView)

// Attributes
public:
	CWorkDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CDib Dib;
	CString FileName;
	int flag;
	int target_iswork;
	CPoint target_pos;
	virtual ~CWorkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkView)
	afx_msg void OnReadPic();
	afx_msg void OnTarget();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in workView.cpp
inline CWorkDoc* CWorkView::GetDocument()
   { return (CWorkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKVIEW_H__067CA72D_175C_45C6_B965_E8A452C78942__INCLUDED_)
