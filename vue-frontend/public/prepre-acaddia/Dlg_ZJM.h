//{{AFX_INCLUDES()
//#include "listview.h"
#include "Dlg_TQCS1.h"
#include "Dlg_AD1.h"
#include "Dlg_TimeSet.h"
#include "Dlg_ADAdjust1.h"
#include "Dlg_TQML.h"
//#include "Dlg_Channel.h"
#include "Dlg_Message.h"
#include "DLg_DIMset.h"
#include "Dlg_BaseAngle.h"
//#include "mscomm.h"
//#include "new1Dlg.h"
//#include "All.h"
//#include "TeleProcess.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLG_ZJM_H__58BB99E2_A860_4121_9763_E467D085293E__INCLUDED_)
#define AFX_DLG_ZJM_H__58BB99E2_A860_4121_9763_E467D085293E__INCLUDED_

#include "listview.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_ZJM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_ZJM dialog

class Dlg_ZJM : public CDialog
{
// Construction
public:
	int m_nComPortMb;
	UCHAR FETCH_REFRESH;
//	UINT Connect_Index;
//	UINT ErrorCounter;
//	CTeleProcess Apply_Telegram, Fetch_Telegram,Connect_Telegram;
//	UINT index;
//	UCHAR RXDAT[280];
//	CNew1Dlg Parent;
//	CNew1Dlg *pp;
//	CDialog *pParent;
	

	UCHAR MsgList_ValidData[280];
	UCHAR MsgList_h_ValidData[280];
	UCHAR ADCacul_ValidData[280];
//	CListView1 Tst_ListView;
	SYSTEMTIME m_nTime;
	Dlg_TQML TQML_dlg;
	//Dlg_Channel Channel_dlg;
	Dlg_Message Message_dlg;
	Dlg_AD1 AD1_dlg;
	Dlg_TQCS1 TQCS_dlg;
	Dlg_ADAdjust1 ADAdjust_dlg;
	Dlg_ZJM(CWnd* pParent = NULL);   // standard constructor
	Dlg_TimeSet TimeSet_dlg;
	DLg_DIMset  DimSet_dlg;
	Dlg_BaseAngle BaseAngle_dlg;
//	virtual void SentData(UCHAR TX[]) : public CNew1Dlg
// Dialog Data
	//{{AFX_DATA(Dlg_ZJM)
	enum { IDD = IDD_ZJM };
	CListCtrl	m_clistctrlMsgList;
	CListCtrl	m_clistctrlADCacul;
	BOOL	m_boolZJM_Line1;
	BOOL	m_boolZJM_Line2;
	BOOL	m_boolZJM_DC;
//	CMSComm	m_ctrlCOM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_ZJM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_ZJM)
	afx_msg void OnZjmTqcs();
	afx_msg void OnZjmAd1();
	afx_msg void OnZJMTimeSet();
	afx_msg void OnZJMADAdjust();
	afx_msg void OnZjmTqml();
	//afx_msg void OnZjmChannel();
	afx_msg void OnZjmMessage();
	afx_msg void OnZJMCOMSet();
	afx_msg void OnBaseAngle();
	afx_msg void OnCheckZjmDc();
	afx_msg void OnCheckZjmLine1();
	afx_msg void OnCheckZjmLine2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButtonZjmFetch();
	afx_msg void OnButtonZjmSave();
	afx_msg void OnButtonZjmOpen();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnVIEWSet();
	
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_ZJM_H__58BB99E2_A860_4121_9763_E467D085293E__INCLUDED_)
