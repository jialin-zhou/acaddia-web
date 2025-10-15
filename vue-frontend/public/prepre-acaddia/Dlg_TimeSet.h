#if !defined(AFX_DLG_TIMESET_H__A60C473B_3061_4F16_A07E_7031E03A67A9__INCLUDED_)
#define AFX_DLG_TIMESET_H__A60C473B_3061_4F16_A07E_7031E03A67A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_TimeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_TimeSet dialog

class Dlg_TimeSet : public CDialog
{
// Construction
public:
	UINT Function_ID;
	UCHAR ValidData[280];
	SYSTEMTIME * m_nTimeData;
	//CString str_time;
	Dlg_TimeSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_TimeSet)
	enum { IDD = IDD_TimeSet };
	COleDateTime	m_nTime;
	COleDateTime	m_nData;
	BOOL	m_BOOLSetStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_TimeSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_TimeSet)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckSet();
	afx_msg void OnDatetimechangeDatetimepickerTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonTimesetApply();
	afx_msg void OnDatetimechangeDatetimepickerData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonTimesetFetch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ENTimer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TIMESET_H__A60C473B_3061_4F16_A07E_7031E03A67A9__INCLUDED_)
