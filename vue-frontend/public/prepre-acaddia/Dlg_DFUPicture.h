#if !defined(AFX_DLG_DFUPICTURE_H__30B30C0A_BC27_47BA_B34E_94BADD6A81E6__INCLUDED_)
#define AFX_DLG_DFUPICTURE_H__30B30C0A_BC27_47BA_B34E_94BADD6A81E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_DFUPicture.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_DFUPicture dialog

class Dlg_DFUPicture : public CDialog
{
// Construction
public:
	Dlg_DFUPicture(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_DFUPicture)
//	enum { IDD = IDD_DIALOG_DFU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_DFUPicture)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_DFUPicture)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_DFUPICTURE_H__30B30C0A_BC27_47BA_B34E_94BADD6A81E6__INCLUDED_)
