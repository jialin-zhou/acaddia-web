#if !defined(AFX_DLG_TQCS1_H__6F31EC2E_BD12_4EC9_9A39_E17A71D0A898__INCLUDED_)
#define AFX_DLG_TQCS1_H__6F31EC2E_BD12_4EC9_9A39_E17A71D0A898__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_TQCS1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQCS1 dialog

class Dlg_TQCS1 : public CDialog
{
// Construction
public:
	UCHAR DATA[256];
	int Zero_NR;
	UINT TQCS_FUNCTION;
	UCHAR ValidData[280];
	Dlg_TQCS1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_TQCS1)
	enum { IDD = IDD_TQCS1 };
	short	m_shortTQCS_TCB;
	int		m_nTQCS_SynSubStyle;
	float	m_floatTQCS_Damax;
	float	m_floatTQCS_DUmax;
	float	m_floatTQCS_Dfmax;
	float	m_floatTQCS_Dfptmax;
	float	m_floatTQCS_Udead;
	float	m_floatTQCS_TrU1U2;
	float	m_floatTQCS_Umin;
	float	m_floatTQCS_Umax;
	float	m_floatTQCS_fmax;
	float	m_floatTQCS_fmin;
	float	m_floatTQCS_TsynDuration;
	float	m_floatTQCS_Synchron;
	float	m_floatTQCS_D_fmax2;
	float	m_floatTQCS_D_Umax2;
	float	m_floatTQCS_Synchron2;
	BOOL	m_BoolTQCS_L1_Dead_Volt_CHECK;
	BOOL	m_BoolTQCS_L2_Dead_Volt_CHECK;
	BOOL	m_BoolTQCS_ALL_Dead_Volt_CHECK;
	BOOL	m_BoolTQCS_Func_Enab_CHECK;
	int		m_IntTQCS_RADIO_Phase_A;
	int		m_IntTQCS_RADIO_Routine_Auto_Select;
	int		m_IntTQCS_RADIO_ASYN_Style;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_TQCS1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_TQCS1)
	afx_msg void OnBUTTONTQCSApply();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBUTTONTQCSFetch();
	afx_msg void OnBUTTONTQCSDefult();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnRADIOTQCSSynSubStyle();
	afx_msg void OnRADIOTQCSAsy();
	afx_msg void OnCHECKTQCSDeadVoltEn();
	afx_msg void OnFuncEnabCHECK();
	afx_msg void OnRADIOPhaseA();
	afx_msg void OnRADIOPhaseB();
	afx_msg void OnRADIOPhaseC();
	afx_msg void OnRADIORoutineAutoSelect();
	afx_msg void OnRADIOSYNStyle();
	afx_msg void OnRADIOASYNStyle();
	afx_msg void OnL1DeadVoltCHECK();
	afx_msg void OnL2DeadVoltCHECK();
	afx_msg void OnALLDeadVoltCHECK();
	afx_msg void OnRADIOManualSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_TQCS1_H__6F31EC2E_BD12_4EC9_9A39_E17A71D0A898__INCLUDED_)
