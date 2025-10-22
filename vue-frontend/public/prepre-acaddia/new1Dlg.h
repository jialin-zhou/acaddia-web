// new1Dlg.h : header file
//
//{{AFX_INCLUDES()
//#include "..\..\..\Á·Ï°\vc\new1\teleprocess.h	// Added by ClassView
#include "mscomm.h"
#include "TeleProcess.h"
#include "Dlg_ZJM.h"

//#include "Dlg_DFUPicture.h"
//}}AFX_INCLUDES

#if !defined(AFX_NEW1DLG_H__F982D38C_1D22_4A9B_89CD_49F69E2F3673__INCLUDED_)
#define AFX_NEW1DLG_H__F982D38C_1D22_4A9B_89CD_49F69E2F3673__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNew1Dlg dialog

class CNew1Dlg : public CDialog
{
// Construction
public:
	int Current_Style;
	int DIM_public;
	int DIM_Line_Vot_style;
	BOOL DC_V_I_select[12];
	int Zero_NR;
//	UCHAR Zero_NR;
	UCHAR * pTXData;
	UCHAR TXDat_Temp[280];
	UINT Msg_Len;
	BOOL RX_Msg_End;
    UINT Down;
//	CPaintDC *dc;
	TeleBlock TQCS_block_35,ACAD_block_33,ADData_block_37,Msg_h_block_12,Channel_block_22,Channel_block_23,Msg_block_13,Msg_block_34,Msg_block_32,ADAdjust_block_38,ADAdjust_block_40,ADAdjust_block_42;
	TeleBlock TQML_block_44,TQML_block_45,TimeSet_block_28,TimeSet_block_29,AC_angle_block_47,Message_block_49,Message_block_50;
	UCHAR TXDATA1[280];                                        //Array of the sent data
	UCHAR RXTele_Nr;                                           //receive order
	//UCHAR TQCS_Data[280];
//	UCHAR RX_Order[5];
	BOOL Fun_Connect(TeleBlock TeleBlock1,int zero_NR);
	volatile UINT Connect_Index;
	UINT ErrorCounter;
//	BOOL ReceiveOK;
	UINT index;
	Dlg_ZJM ZJM_dlg;
//	Dlg_DFUPicture DFUPicture_dlg;
	CTeleProcess Connect_Telegram;
	void SentData(UCHAR TXData[]);
	UCHAR  RXDAT[280];
	CNew1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNew1Dlg)
	enum { IDD = IDD_NEW1_DIALOG };
	CMSComm	m_ctrlCOM;
	CString	m_CStringStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNew1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNew1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOffline();
	afx_msg void OnConnect();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
//	UINT m_nTimerID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEW1DLG_H__F982D38C_1D22_4A9B_89CD_49F69E2F3673__INCLUDED_)
