#if !defined(AFX_DLG_COMSET_H__1E43EC14_0DEC_492E_98A9_208F3E6B87AA__INCLUDED_)
#define AFX_DLG_COMSET_H__1E43EC14_0DEC_492E_98A9_208F3E6B87AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "new1Dlg.h"
// Dlg_ComSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_ComSet dialog

class Dlg_ComSet : public CDialog
{
// Construction
public:
	CString settingpara;
	Dlg_ComSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_ComSet)
	enum { IDD = IDD_COMSet };
	int		m_nComSetBaud;
	int		m_nComSetCheck;
	int		m_nComSetData;
	int		m_nComSetStop;
	int		m_nComSetCom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_ComSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_ComSet)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnGetCom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_COMSET_H__1E43EC14_0DEC_492E_98A9_208F3E6B87AA__INCLUDED_)
