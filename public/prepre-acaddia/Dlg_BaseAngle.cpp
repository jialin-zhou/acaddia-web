// Dlg_BaseAngle.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_BaseAngle.h"
#include "Dlg_ZJM.h"
#include "new1Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_BaseAngle dialog


Dlg_BaseAngle::Dlg_BaseAngle(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_BaseAngle::IDD, pParent)
{
	for(int j=0;j<280;j++)
	ValidData[j]=0;
	//{{AFX_DATA_INIT(Dlg_BaseAngle)
	m_float_da = 0.0f;
	m_float_I1a = 0.0f;
	m_float_I1b = 0.0f;
	m_float_I1c = 0.0f;
	m_float_I2a = 0.0f;
	m_float_I2b = 0.0f;
	m_float_I2c = 0.0f;
	m_float_U1a = 0.0f;
	m_float_U1b = 0.0f;
	m_float_U1c = 0.0f;
	m_float_U2a = 0.0f;
	m_float_U2c = 0.0f;
	m_float_U2b = 0.0f;
	//}}AFX_DATA_INIT
}


void Dlg_BaseAngle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_BaseAngle)
	DDX_Text(pDX, IDC_da, m_float_da);
	DDX_Text(pDX, IDC_I1a, m_float_I1a);
	DDX_Text(pDX, IDC_I1b, m_float_I1b);
	DDX_Text(pDX, IDC_I1c, m_float_I1c);
	DDX_Text(pDX, IDC_I2a, m_float_I2a);
	DDX_Text(pDX, IDC_I2b, m_float_I2b);
	DDX_Text(pDX, IDC_I2c, m_float_I2c);
	DDX_Text(pDX, IDC_U1a, m_float_U1a);
	DDX_Text(pDX, IDC_U1b, m_float_U1b);
	DDX_Text(pDX, IDC_U1c, m_float_U1c);
	DDX_Text(pDX, IDC_U2a, m_float_U2a);
	DDX_Text(pDX, IDC_U2c, m_float_U2c);
	DDX_Text(pDX, IDC_U2b, m_float_U2b);
	//}}AFX_DATA_MAP
	
	unsigned short TempData_short=1;
	UCHAR TempData_UCHAR=1;
	UINT  TempData_UINT=1;
	BOOL  TempData_BOOL=FALSE;
	float TempData_float=0;
	
    
	if(ANGLE_FUNCTION==IDC_BUTTON_ANGLE_FETCH ||ANGLE_FUNCTION==IDC_BUTTON_ZJM_OPEN||ANGLE_FUNCTION==IDC_ZJM_Angle)
	{
	TempData_UCHAR =ValidData[4];           //UA1
	TempData_short= ValidData[5];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_U1a =TempData_float/100;

	TempData_UCHAR =ValidData[6];           //UB1
	TempData_short= ValidData[7];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_U1b =TempData_float/100;

	TempData_UCHAR =ValidData[8];           //UC1
	TempData_short= ValidData[9];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_U1c =TempData_float/100;

	TempData_UCHAR =ValidData[10];           //IA1
	TempData_short= ValidData[11];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_I1a =TempData_float/100;

	TempData_UCHAR =ValidData[12];           //IB1
	TempData_short= ValidData[13];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_I1b =TempData_float/100;
	
	TempData_UCHAR =ValidData[14];           //IC1
	TempData_short= ValidData[15];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_I1c =TempData_float/100;
	
	TempData_UCHAR =ValidData[16];           //UA2
	TempData_short= ValidData[17];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_U2a =TempData_float/100;

	TempData_UCHAR =ValidData[18];           //UB2
	TempData_short= ValidData[19];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_U2b =TempData_float/100;

	TempData_UCHAR =ValidData[20];           //UC2
	TempData_short= ValidData[21];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_U2c =TempData_float/100;

	TempData_UCHAR =ValidData[22];           //IA2
	TempData_short= ValidData[23];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_I2a =TempData_float/100;

	TempData_UCHAR =ValidData[24];           //IB2
	TempData_short= ValidData[25];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_I2b =TempData_float/100;
	
	TempData_UCHAR =ValidData[26];           //IC2
	TempData_short= ValidData[27];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_I2c =TempData_float/100;

	TempData_UCHAR =ValidData[28];           //da
	TempData_short= ValidData[29];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_float_da =TempData_float/100;
	//UpdateData(FALSE);
	}
	ANGLE_FUNCTION=NULL;
	
}


BEGIN_MESSAGE_MAP(Dlg_BaseAngle, CDialog)
	//{{AFX_MSG_MAP(Dlg_BaseAngle)
	ON_BN_CLICKED(IDC_BUTTON_ANGLE_FETCH, OnButtonAngleFetch)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_BaseAngle message handlers



void Dlg_BaseAngle::OnButtonAngleFetch() 
{
	// TODO: Add your control notification handler code here
		ANGLE_FUNCTION =IDC_BUTTON_ANGLE_FETCH;
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
//	pParent->
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_ANGLE_FETCH;

	pParent->AC_angle_block_47.Station_adr=0;
	pParent->AC_angle_block_47.Telegram_Nr=47;
	pParent->AC_angle_block_47.F1_field=0;
	pParent->AC_angle_block_47.F2_field=0x80;
	pParent->AC_angle_block_47.Data=(UCHAR *)"";

	pParent->Fun_Connect(pParent->AC_angle_block_47,0);
	
	SetTimer(IDC_BUTTON_ANGLE_FETCH,666,NULL);
}

void Dlg_BaseAngle::OnOK() 
{

	CDialog::OnOK();
}




void Dlg_BaseAngle::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==IDC_BUTTON_ANGLE_FETCH)
	{
		KillTimer(IDC_BUTTON_ANGLE_FETCH);
		UpdateData(TRUE);
		UpdateData(FALSE);
//		MessageBox("dd");
	}
	CDialog::OnTimer(nIDEvent);
}

void Dlg_BaseAngle::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	UpdateData(FALSE);
	// TODO: Add your message handler code here	
}
