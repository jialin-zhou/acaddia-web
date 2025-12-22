#if !defined(AFX_DLG_DIMSET_H__88766A94_D384_447A_95DE_725BBC462145__INCLUDED_)
#define AFX_DLG_DIMSET_H__88766A94_D384_447A_95DE_725BBC462145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLg_DIMset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DLg_DIMset dialog

class DLg_DIMset : public CDialog
{
// Construction
public:
	DLg_DIMset(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DLg_DIMset)
	enum { IDD = IDD_DIM_SET };
	int		m_public_dim_select;
	int		m_line_volt_view_select;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DLg_DIMset)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DLg_DIMset)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual void OnOK();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_DIMSET_H__88766A94_D384_447A_95DE_725BBC462145__INCLUDED_)
