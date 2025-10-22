#if !defined(AFX_DLG_AD1_H__1AAB4831_E8EE_4202_8C5A_B6A8E8B1B97E__INCLUDED_)
#define AFX_DLG_AD1_H__1AAB4831_E8EE_4202_8C5A_B6A8E8B1B97E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "Resource.h" 
#endif // _MSC_VER > 1000
// Dlg_AD1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_AD1 dialog
#define DIM_U   0x6EDC //0x24F3*0x6EDC/0x4000H=0x4000H
//#define DIM_UL  0xC000
//#define DIM_UL  0x6EDC
#if 1
/*
	1A-3.5V	  --0x5B74
	1A-1V(1A) --0x15D87
	1A-1V(5A) --0x45E8
*/
#define DIM_I   0x45E8 //0x2553*0x6DBF/0x4000H=0x4000H
#else
#define DIM_I   0x6DBF //0x2553*0x6DBF/0x4000H=0x4000H
#endif
#define DIM_DC  0x9FD8

#define DIM_US   0x1BB7 //0x24F3*0x1BB7/0x2000H=0x2000H
//#define DIM_UL  0x3000
//#define DIM_UL  0x1BB7
#define DIM_IS   0x1B70 //0x2553*0x1B70/0x2000H=0x2000H
#define DIM_DCS  0x4FEC
class Dlg_AD1 : public CDialog
{
// Construction
public:
//	int Zero_NR;
	UCHAR DATA[256];
	UCHAR * pTX_DATA;
	UINT AD1_FUNCTION;
	UCHAR ValidData[280];
//	UCHAR AD1_ValidData[256];
	Dlg_AD1(CWnd* pParent = NULL);   // standard constructor

//	short	m_shortAD1_V_DC1_1;
// Dialog Data
	//{{AFX_DATA(Dlg_AD1)
	enum { IDD = IDD_AD1 };
	int		m_nAD1_ActiveCS;
	int		m_nAD1_SecCNV;
	int		m_nAD1_SecVNV;
	int		m_nAD1_VoltSTD1;
	int		m_nAD1_VoltSTD2;
	int		m_nAD1_DCSS;
	int		m_shortAD1_C_DC1;
	int		m_shortAD1_C_DC2;
	int		m_shortAD1_C_DC3;
	int     m_shortAD1_C_DC4;

    int		m_shortAD1_C_DC5;
    int		m_shortAD1_C_DC6;    
	int		m_shortAD1_C_DC7;    
	int  	m_shortAD1_C_DC8;

    int		m_shortAD1_C_DC9;
    int		m_shortAD1_C_DC10;    
	int		m_shortAD1_C_DC11;    
	int  	m_shortAD1_C_DC12;

	short	m_shortAD1_V_DC1;
	short	m_shortAD1_V_DC2;
	short	m_shortAD1_V_DC3;
	short	m_shortAD1_V_DC4;

    short	m_shortAD1_V_DC5;
    short	m_shortAD1_V_DC6;    
	short	m_shortAD1_V_DC7;
	short	m_shortAD1_V_DC8;

    short	m_shortAD1_V_DC9;
    short	m_shortAD1_V_DC10;    
	short	m_shortAD1_V_DC11;
	short	m_shortAD1_V_DC12;

	short	m_shortAD1_V_LINE1;
	short	m_shortAD1_V_LINE2;
	short	m_shortAD1_C_LINE1;
	short	m_shortAD1_C_LINE2;
	short	m_shortAD1_I1a;
	short	m_shortAD1_I1b;
	short	m_shortAD1_I1c;
	short	m_shortAD1_I2a;
	short	m_shortAD1_I2b;
	short	m_shortAD1_I2c;
	short	m_shortAD1_U1a;
	short	m_shortAD1_U1b;
	short	m_shortAD1_U1c;
	short	m_shortAD1_U2a;
	short	m_shortAD1_U2b;
	short	m_shortAD1_U2c;
	int		m_nAD1_DCSS2;
	int		m_nAD1_DCSS3;
	int		m_nAD1_DCSS4;

    int		m_nAD1_DCSS5;
    int		m_nAD1_DCSS6;
    int		m_nAD1_DCSS7;
    int		m_nAD1_DCSS8;
    int		m_nAD1_DCSS9;
    int		m_nAD1_DCSS10;
    int		m_nAD1_DCSS11;
    int		m_nAD1_DCSS12;



	int		m_Channel_Sec1;
	int		m_Channel_Sec2;
	int		m_Channel_Sec3;
	int		m_Channel_SecX;
	int		m_Model_Sec;
	int		m_Delay_A;
	int		m_Delay_B;
	int		m_Delay_C;
	int		m_Delay_X;
	int		m_Delay;
	int		m_Primary_Current_Scaling;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_AD1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_AD1)
	afx_msg void OnButtonAd1Default();
	afx_msg void OnButtonAd1Fetch();
	afx_msg void OnButtonAd1Apply();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnRADIOAD1ActiveCS();
	afx_msg void OnRADIOAD1ActiveCS1();
	afx_msg void OnRADIOAD1SecCNV();
	afx_msg void OnRADIOAD1SecCNV1();
	afx_msg void OnRADIOAD1SecVNV();
	afx_msg void OnRADIOAD1SecVNV1();
	afx_msg void OnRADIOAD1VoltSTD1();
	afx_msg void OnRADIOAD1VoltSTD11();
	afx_msg void OnRADIOAD1VoltSTD2();
	afx_msg void OnRADIOAD1VoltSTD21();
	afx_msg void OnRadio1Ad1Dcss();
	afx_msg void OnRadio1Ad1Dcss1();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnRadio1Ad1Dcss2();
	afx_msg void OnRadio1Ad1Dcss22();
	afx_msg void OnRadio1Ad1Dcss3();
	afx_msg void OnRadio1Ad1Dcss33();
	afx_msg void OnRadio1Ad1Dcss4();
	afx_msg void OnRadio1Ad1Dcss44();
	afx_msg void OnRadio1Ad1Dcss5();
	afx_msg void OnRadio1Ad1Dcss55();
	afx_msg void OnRadio1Ad1Dcss6();
	afx_msg void OnRadio1Ad1Dcss66();
	afx_msg void OnRadio1Ad1Dcss7();
	afx_msg void OnRadio1Ad1Dcss77();
	afx_msg void OnRadio1Ad1Dcss8();
	afx_msg void OnRadio1Ad1Dcss88();
	afx_msg void OnChangeEditAd1VDc1();
	afx_msg void OnRadio1Ad1Dcss9();
	afx_msg void OnRadio1Ad1Dcss99();
	afx_msg void OnRadio1Ad1Dcss10();
	afx_msg void OnRadio1Ad1Dcss1010();
	afx_msg void OnRadio1Ad1Dcss11();
	afx_msg void OnRadio1Ad1Dcss1111();
	afx_msg void OnRadio1Ad1Dcss12();
	afx_msg void OnRadio1Ad1Dcss1212();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_AD1_H__1AAB4831_E8EE_4202_8C5A_B6A8E8B1B97E__INCLUDED_)
