#if !defined(AFX_DLG_ADDATA_H__F6AFD9CB_C9FA_4E1E_8249_0D5167752308__INCLUDED_)
#define AFX_DLG_ADDATA_H__F6AFD9CB_C9FA_4E1E_8249_0D5167752308__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_ADData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADData dialog

class Dlg_ADData : public CDialog
{
// Construction
public:
	Dlg_ADData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_ADData)
	enum { IDD = IDD_ADData };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_ADData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_ADData)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ADDATA_H__F6AFD9CB_C9FA_4E1E_8249_0D5167752308__INCLUDED_)
