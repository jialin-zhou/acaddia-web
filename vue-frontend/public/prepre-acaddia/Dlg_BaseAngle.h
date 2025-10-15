#if !defined(AFX_DLG_BASEANGLE_H__2E3224D5_D29F_4D9B_B860_4237FF89A9B3__INCLUDED_)
#define AFX_DLG_BASEANGLE_H__2E3224D5_D29F_4D9B_B860_4237FF89A9B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_BaseAngle.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_BaseAngle dialog

class Dlg_BaseAngle : public CDialog
{
// Construction
public:
	UCHAR DATA[256];
	UCHAR * pTX_DATA;
	UINT ANGLE_FUNCTION;
	UCHAR ValidData[280];
	Dlg_BaseAngle(CWnd* pParent = NULL);   // standard constructor
    
    
// Dialog Data
	//{{AFX_DATA(Dlg_BaseAngle)
	enum { IDD = IDD_BASE_ANGLE };
	float	m_float_da;
	float	m_float_I1a;
	float	m_float_I1b;
	float	m_float_I1c;
	float	m_float_I2a;
	float	m_float_I2b;
	float	m_float_I2c;
	float	m_float_U1a;
	float	m_float_U1b;
	float	m_float_U1c;
	float	m_float_U2a;
	float	m_float_U2c;
	float	m_float_U2b;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_BaseAngle)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_BaseAngle)
	virtual void OnOK();
	afx_msg void OnButtonAngleFetch();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_BASEANGLE_H__2E3224D5_D29F_4D9B_B860_4237FF89A9B3__INCLUDED_)
