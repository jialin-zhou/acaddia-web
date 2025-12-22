#if !defined(AFX_DLG_ADADJUST_H__B1DE6FD7_9F13_4195_BA3A_901A40F3E466__INCLUDED_)
#define AFX_DLG_ADADJUST_H__B1DE6FD7_9F13_4195_BA3A_901A40F3E466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_ADAdjust.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADAdjust dialog

class Dlg_ADAdjust : public CDialog
{
// Construction
public:
	Dlg_ADAdjust(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_ADAdjust)
	enum { IDD = IDD_ADAdjust };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_ADAdjust)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_ADAdjust)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ADADJUST_H__B1DE6FD7_9F13_4195_BA3A_901A40F3E466__INCLUDED_)
