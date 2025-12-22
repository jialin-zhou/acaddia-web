#if !defined(AFX_DLG_ADADJUST1_H__5768214D_D3BE_4C72_8010_92533C34B45B__INCLUDED_)
#define AFX_DLG_ADADJUST1_H__5768214D_D3BE_4C72_8010_92533C34B45B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_ADAdjust1.h : header file
//

//////////////////////////////////////////////////////////////////////////
//
//		struct
//
//////////////////////////////////////////////////////////////////////////
#ifndef LINEPARA
#define LINEPARA
typedef struct 
{
	int Index;
	float f_para1;
	CString  Cs_para2;
	CString  Cs_para3;
	CString  Cs_para4;
	CString  Cs_para5;
	BOOL     b_paraOK;
}LinePara;
#endif






/////////////////////////////////////////////////////////////////////////////
// Dlg_ADAdjust1 dialog

class Dlg_ADAdjust1 : public CDialog
{
// Construction
public:
	LinePara Line1[6];
	LinePara Line2[6];
	LinePara DC[24];
//	float LinePara[2][6];   //Dimension1 [2]: Line1 and Line 2;//// Dimension2 [6]:m_floatADAdjust_Ua_X ;
	UCHAR ParaData[50];
	UINT CHECK_STATUS;
	UINT Function_ID;
//	int Zero_NR;
	CString FormChang(float INPUT_float);
//	UCHAR TXDATA[50];
	UCHAR ValidData[280];
	Dlg_ADAdjust1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dlg_ADAdjust1)
	enum { IDD = IDD_ADAdjust1 };
	BOOL	m_boolADAdjust_C_DC1_OK;
	BOOL	m_boolADAdjust_C_DC2_OK;
	BOOL	m_boolADAdjust_C_DC3_OK;
	BOOL	m_boolADAdjust_C_DC4_OK;
	BOOL	m_boolADAdjust_V_DC1_OK;
	BOOL	m_boolADAdjust_V_DC2_OK;
	BOOL	m_boolADAdjust_V_DC3_OK;
	BOOL	m_boolADAdjust_V_DC4_OK;
	BOOL	m_boolADAdjust_Ia_OK;
	BOOL	m_boolADAdjust_Ib_OK;
	BOOL	m_boolADAdjust_Ic_OK;
	BOOL	m_boolADAdjust_Ua_OK;
	BOOL	m_boolADAdjust_Ub_OK;
	BOOL	m_boolADAdjust_Uc_OK;

  //  BOOL    m_nADAdjust_DCChannelC;

	float	m_floatADAdjust_C_DC1_1;
	CString	m_CStringADAdjust_C_DC1_2;
	CString	m_CStringADAdjust_C_DC1_3;
	CString	m_CStringADAdjust_C_DC1_4;
	CString	m_CStringADAdjust_C_DC1_5;
	CString	m_CStringADAdjust_C_DC2_2;
	CString	m_CStringADAdjust_C_DC2_3;
	CString	m_CStringADAdjust_C_DC2_4;
	CString	m_CStringADAdjust_C_DC2_5;
	CString	m_CStringADAdjust_C_DC3_2;
	CString	m_CStringADAdjust_C_DC3_3;
	CString	m_CStringADAdjust_C_DC3_4;
	CString	m_CStringADAdjust_C_DC3_5;
	CString	m_CStringADAdjust_C_DC4_2;
	CString	m_CStringADAdjust_C_DC4_3;
	CString	m_CStringADAdjust_C_DC4_4;
	CString	m_CStringADAdjust_C_DC4_5;
	CString	m_CStringADAdjust_V_DC1_2;
	CString	m_CStringADAdjust_V_DC1_3;
	CString	m_CStringADAdjust_V_DC1_4;
	CString	m_CStringADAdjust_V_DC1_5;
	CString	m_CStringADAdjust_V_DC2_2;
	CString	m_CStringADAdjust_V_DC2_3;
	CString	m_CStringADAdjust_V_DC2_4;
	CString	m_CStringADAdjust_V_DC2_5;
	CString	m_CStringADAdjust_V_DC3_2;
	CString	m_CStringADAdjust_V_DC3_3;
	CString	m_CStringADAdjust_V_DC3_4;
	CString	m_CStringADAdjust_V_DC3_5;
	CString	m_CStringADAdjust_V_DC4_2;
	CString	m_CStringADAdjust_V_DC4_3;
	CString	m_CStringADAdjust_V_DC4_4;
	CString	m_CStringADAdjust_V_DC4_5;
	int		m_nADAdjust_ACChannel;
	int		m_nADAdjust_Channel;
	int		m_nADAdjust_DCChannel;
	CString	m_CStringADAdjust_Ia_2;
	CString	m_CStringADAdjust_Ia_3;
	CString	m_CStringADAdjust_Ia_4;
	CString	m_CStringADAdjust_Ia_5;
	CString	m_CStringADAdjust_Ib_2;
	CString	m_CStringADAdjust_Ib_3;
	CString	m_CStringADAdjust_Ib_4;
	CString	m_CStringADAdjust_Ib_5;
	CString	m_CStringADAdjust_Ic_2;
	CString	m_CStringADAdjust_Ic_3;
	CString	m_CStringADAdjust_Ic_4;
	CString	m_CStringADAdjust_Ic_5;
	CString	m_CStringADAdjust_Ua_2;
	CString	m_CStringADAdjust_Ua_3;
	CString	m_CStringADAdjust_Ua_4;
	CString	m_CStringADAdjust_Ua_5;
	CString	m_CStringADAdjust_Ub_2;
	CString	m_CStringADAdjust_Ub_3;
	CString	m_CStringADAdjust_Ub_4;
	CString	m_CStringADAdjust_Ub_5;
	CString	m_CStringADAdjust_Uc_2;
	CString	m_CStringADAdjust_Uc_3;
	CString	m_CStringADAdjust_Uc_4;
	CString	m_CStringADAdjust_Uc_5;
	float	m_floatADAdjust_C_DC2_1;
	float	m_floatADAdjust_C_DC3_1;
	float	m_floatADAdjust_C_DC4_1;
	float	m_floatADAdjust_V_DC4_1;
	float	m_floatADAdjust_V_DC3_1;
	float	m_floatADAdjust_V_DC2_1;
	float	m_floatADAdjust_V_DC1_1;
	float	m_floatADAdjust_Uc_1;
	float	m_floatADAdjust_Ub_1;
	float	m_floatADAdjust_Ua_1;
	float	m_floatADAdjust_Ic_1;
	float	m_floatADAdjust_Ib_1;
	float	m_floatADAdjust_Ia_1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_ADAdjust1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_ADAdjust1)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRADIOADAdjustACChannel();
	afx_msg void OnRADIOADAdjustChannel();
	afx_msg void OnRADIOADAdjustChannelline2();
	afx_msg void OnRADIOADAdjustChannelDC();
	afx_msg void OnRADIOADAdjustACChannelUb();
	afx_msg void OnRADIOADAdjustACChannelUc();
	afx_msg void OnRADIOADAdjustACChannelIa();
	afx_msg void OnRADIOADAdjustACChannelIb();
	afx_msg void OnRADIOADAdjustACChannelIc();
	afx_msg void OnRADIOADAdjustDCChannel();
	afx_msg void OnRADIOADAdjustDCChannelCDC1();
	afx_msg void OnRADIOADAdjustDCChannelCDC2();
	afx_msg void OnRADIOADAdjustDCChannelCDC3();
	afx_msg void OnRADIOADAdjustDCChannelCDC4();
	afx_msg void OnRADIOADAdjustDCChannelVDC2();
	afx_msg void OnRADIOADAdjustDCChannelVDC3();
	afx_msg void OnRADIOADAdjustDCChannelVDC4();
	afx_msg void OnKillfocusEDITADAdjustUa1();
	afx_msg void OnKillfocusEDITADAdjustUb1();
	afx_msg void OnKillfocusEDITADAdjustUc1();
	afx_msg void OnKillfocusEDITADAdjustIa1();
	afx_msg void OnKillfocusEDITADAdjustIb1();
	afx_msg void OnKillfocusEDITADAdjustIc1();
	afx_msg void OnKillfocusEDITADAdjustVDC11();
	afx_msg void OnKillfocusEDITADAdjustVDC21();
	afx_msg void OnKillfocusEDITADAdjustVDC31();
	afx_msg void OnKillfocusEDITADAdjustVDC41();
	afx_msg void OnKillfocusEDITADAdjustCDC11();
	afx_msg void OnKillfocusEDITADAdjustCDC21();
	afx_msg void OnKillfocusEDITADAdjustCDC31();
	afx_msg void OnKillfocusEDITADAdjustCDC41();
	afx_msg void OnBUTTONADAdjustApply();
	afx_msg void OnBUTTONADAdjustFetch();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBUTTONADAdjustNewParApply();
	afx_msg void OnRADIOADAdjustDCChannelCDC5();
	afx_msg void OnRADIOADAdjustDCChannelCDC6();
	afx_msg void OnRADIOADAdjustDCChannelCDC7();
	afx_msg void OnRADIOADAdjustDCChannelCDC8();
	afx_msg void OnRADIOADAdjustDCChannel5();
	afx_msg void OnRADIOADAdjustDCChannelVDC6();
	afx_msg void OnRADIOADAdjustDCChannelVDC7();
	afx_msg void OnRADIOADAdjustDCChannelVDC8();
	afx_msg void OnRADIOADAdjustDCChannelCDC9();
	afx_msg void OnRADIOADAdjustDCChannelCDC10();
	afx_msg void OnRADIOADAdjustDCChannelCDC11();
	afx_msg void OnRADIOADAdjustDCChannelCDC12();
	afx_msg void OnRADIOADAdjustDCChannelCDC13();
	afx_msg void OnRADIOADAdjustDCChannelCDC14();
	afx_msg void OnRADIOADAdjustDCChannelCDC15();
	afx_msg void OnRADIOADAdjustDCChannelCDC16();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ADADJUST1_H__5768214D_D3BE_4C72_8010_92533C34B45B__INCLUDED_)
