#if !defined(AFX_DLG_TQML_H__9F129D10_9681_444D_9C03_55F75EF51A4F__INCLUDED_)
#define AFX_DLG_TQML_H__9F129D10_9681_444D_9C03_55F75EF51A4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_TQML.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQML dialog

class Dlg_TQML : public CDialog
{
// Construction
public:
	UINT Function_ID;
	UCHAR ValidData[280];
	Dlg_TQML(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_TQML)
	enum { IDD = IDD_TQML };
	int		m_nTQML_REC;
	COleDateTime	m_DateTimeTQML_REC_DATE;
	COleDateTime	m_DateTimeTQML_SENT_DATE;
	BOOL	m_BOOLTQML_REC_OK;
	BOOL	m_BOOLTQML_SENT_OK;
	BOOL	m_BOOLTQML_TIME_OK;
	float	m_floatTQML_REC_DA;
	float	m_floatTQML_REC_DF;
	float	m_floatTQML_REC_DU;
	float	m_floatTQML_REC_F1;
	float	m_floatTQML_REC_F2;
	float	m_floatTQML_SENT_DA;
	float	m_floatTQML_SENT_DF;
	float	m_floatTQML_SENT_DU;
	float	m_floatTQML_SENT_F1;
	float	m_floatTQML_SENT_F2;
	float	m_floatTQML_TIME_DA;
	float	m_floatTQML_TIME_DF;
	float	m_floatTQML_TIME_DU;
	float	m_floatTQML_TIME_F1;
	float	m_floatTQML_TIME_F2;
	COleDateTime	m_DateTimeTQML_TIME_DATE;
	UINT	m_nTQML_REC_MS;
	UINT	m_nTQML_SENT_MS;
	UINT	m_nTQML_TIME_MS;
	BOOL	m_BOOLTQML_UNFINISH;
	BOOL	m_BOOLTQML_RESET;
	float	m_floatTQML_REC_U1;
	float	m_floatTQML_TIME_U1;
	float	m_floatTQML_REC_DF_DT;
	float	m_floatTQML_REC_F1_DT;
	float	m_floatTQML_REC_F2_DT;
	float	m_floatTQML_REC_U2;
	float	m_floatTQML_SENT_F1_DT;
	float	m_floatTQML_SENT_U1;
	float	m_floatTQML_SENT_U2;
	float	m_floatTQML_TIME_DF_DT;
	float	m_floatTQML_TIME_F1_DT;
	float	m_floatTQML_TIME_F2_DT;
	float	m_floatTQML_TIME_U2;
	float	m_floatTQML_SENT_F2_DT;
	float	m_floatTQML_SENT_DF_DT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_TQML)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_TQML)
	afx_msg void OnButtonTqmlApply();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadioTqmlSent();
	afx_msg void OnRadioTqmlTime();
	afx_msg void OnButtonTqmlFetch();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRadioTqmlRec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TQML_H__9F129D10_9681_444D_9C03_55F75EF51A4F__INCLUDED_)
