#if !defined(AFX_DLG_MESSAGE_H__1C42C205_B233_492C_81DB_F1D6FF51C4CE__INCLUDED_)
#define AFX_DLG_MESSAGE_H__1C42C205_B233_492C_81DB_F1D6FF51C4CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Message.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Message dialog

class Dlg_Message : public CDialog
{
// Construction
public:
	
    UCHAR DATA[256];
	UCHAR * pTX_DATA;
	UINT Message_FUNCTION;
	UCHAR ValidData[280];
	Dlg_Message(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(Dlg_Message)
	enum { IDD = IDD_Message };
	BOOL	m_Message_CheckChannel1;
	BOOL	m_Message_CheckChannel10;
	BOOL	m_Message_CheckChannel11;
	BOOL	m_Message_CheckChannel12;
	BOOL	m_Message_CheckChannel13;
	BOOL	m_Message_CheckChannel14;
	BOOL	m_Message_CheckChannel15;
	BOOL	m_Message_CheckChannel16;
	BOOL	m_Message_CheckChannel17;
	BOOL	m_Message_CheckChannel18;
	BOOL	m_Message_CheckChannel19;
	BOOL	m_Message_CheckChannel2;
	BOOL	m_Message_CheckChannel20;
	BOOL	m_Message_CheckChannel21;
	BOOL	m_Message_CheckChannel22;
	BOOL	m_Message_CheckChannel3;
	BOOL	m_Message_CheckChannel4;
	BOOL	m_Message_CheckChannel5;
	BOOL	m_Message_CheckChannel6;
	BOOL	m_Message_CheckChannel7;
	BOOL	m_Message_CheckChannel8;
	BOOL	m_Message_CheckChannel9;
	BOOL	m_Message_DataInvalid;
	BOOL	m_Message_Interpolation;
	BOOL	m_Message_Mode;
	BOOL	m_Message_OutputType;
	BOOL	m_Message_PHHealth;
	BOOL	m_Message_RangeFlag;
	BOOL	m_Message_SysInvalid;
	int  	m_Message_DEC;
	CString	m_Message_Channel1;
	CString	m_Message_LDName;
	CString	m_Message_Channel10;
	CString	m_Message_Channel11;
	CString	m_Message_Channel12;
	CString	m_Message_Channel13;
	CString	m_Message_Channel14;
	CString	m_Message_Channel15;
	CString	m_Message_Channel16;
	CString	m_Message_Channel17;
	CString	m_Message_Channel18;
	CString	m_Message_Channel19;
	CString	m_Message_Channel2;
	CString	m_Message_Channel20;
	CString	m_Message_Channel21;
	CString	m_Message_Channel22;
	CString	m_Message_Channel3;
	CString	m_Message_Channel4;
	CString	m_Message_Channel5;
	CString	m_Message_Channel6;
	CString	m_Message_Channel7;
	CString	m_Message_Channel8;
	CString	m_Message_Channel9;
	CString	m_Message_DataSetName;
	CString	m_Message_Lenth;
	CString	m_Message_LNName;
	CString	m_Message_NeutArtg;
	CString	m_Message_PhsAArtg;
	CString	m_Message_PhsAVrtg;
	CString	m_Message_SmpCtr;
	CString	m_Message_StatusWord1;
	CString	m_Message_StatusWord2;
	CString	m_Message_tdr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Message)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dlg_Message)
	afx_msg void OnBUTTONMessageFetch();
	afx_msg void OnRADIOMessageDEC();
	afx_msg void OnRADIOMessageHEX();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_MESSAGE_H__1C42C205_B233_492C_81DB_F1D6FF51C4CE__INCLUDED_)
