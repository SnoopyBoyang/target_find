// work.h : main header file for the WORK application
//

#if !defined(AFX_WORK_H__983E7DBC_00B9_4100_9F92_AA1A21231EB3__INCLUDED_)
#define AFX_WORK_H__983E7DBC_00B9_4100_9F92_AA1A21231EB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWorkApp:
// See work.cpp for the implementation of this class
//

class CWorkApp : public CWinApp
{
public:
	CWorkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWorkApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORK_H__983E7DBC_00B9_4100_9F92_AA1A21231EB3__INCLUDED_)
