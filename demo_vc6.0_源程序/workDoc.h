// workDoc.h : interface of the CWorkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKDOC_H__C18C0771_D80F_4B15_ACC5_EB48023BE78B__INCLUDED_)
#define AFX_WORKDOC_H__C18C0771_D80F_4B15_ACC5_EB48023BE78B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWorkDoc : public CDocument
{
protected: // create from serialization only
	CWorkDoc();
	DECLARE_DYNCREATE(CWorkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKDOC_H__C18C0771_D80F_4B15_ACC5_EB48023BE78B__INCLUDED_)
