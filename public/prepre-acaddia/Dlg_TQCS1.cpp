// Dlg_TQCS1.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_TQCS1.h"

#include "new1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQCS1 dialog


Dlg_TQCS1::Dlg_TQCS1(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_TQCS1::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_TQCS1)

	m_shortTQCS_TCB = 0;
	m_nTQCS_SynSubStyle = -1;
	m_floatTQCS_Damax = 0.0f;
	m_floatTQCS_DUmax = 0.0f;
	m_floatTQCS_Dfmax = 0.0f;
	m_floatTQCS_Dfptmax = 0.0f;
	m_floatTQCS_Udead = 0.0f;
	m_floatTQCS_TrU1U2 = 0.0f;
	m_floatTQCS_Umin = 0.0f;
	m_floatTQCS_Umax = 0.0f;
	m_floatTQCS_fmax = 0.0f;
	m_floatTQCS_fmin = 0.0f;
	m_floatTQCS_TsynDuration = 0.0f;
	m_floatTQCS_Synchron = 0.0f;
	m_floatTQCS_D_fmax2 = 0.0f;
	m_floatTQCS_D_Umax2 = 0.0f;
	m_floatTQCS_Synchron2 = 0.0f;
	m_BoolTQCS_L1_Dead_Volt_CHECK = FALSE;
	m_BoolTQCS_L2_Dead_Volt_CHECK = FALSE;
	m_BoolTQCS_ALL_Dead_Volt_CHECK = FALSE;
	m_BoolTQCS_Func_Enab_CHECK = TRUE;
	m_IntTQCS_RADIO_Phase_A = -1;
	m_IntTQCS_RADIO_Routine_Auto_Select = -1;
	m_IntTQCS_RADIO_ASYN_Style = -1;
    
    m_IntTQCS_RADIO_Routine_Auto_Select=1;
	m_IntTQCS_RADIO_ASYN_Style=0;
	m_IntTQCS_RADIO_Phase_A=0;
	//m_nTQCS_SynSubStyle=1;
    m_BoolTQCS_L1_Dead_Volt_CHECK=0;//L1的无压选择
    m_BoolTQCS_L2_Dead_Volt_CHECK=0;//
    m_BoolTQCS_ALL_Dead_Volt_CHECK=0;//
	m_shortTQCS_TCB =80;
	m_floatTQCS_Damax =10;
	m_floatTQCS_DUmax =2.0;
	m_floatTQCS_D_Umax2=2.0;
	m_floatTQCS_Dfmax =20;
	m_floatTQCS_D_fmax2=0.10;
	m_floatTQCS_Udead =2.0;
	m_floatTQCS_TrU1U2 =10;
	m_floatTQCS_Dfptmax =0.2;
	m_floatTQCS_Synchron2=0.2;
	m_floatTQCS_Umin =52.0;
	m_floatTQCS_Umax=63.5;
	m_floatTQCS_fmin=47.50;
	m_floatTQCS_fmax =52.50;
	m_floatTQCS_TsynDuration =30;
	m_floatTQCS_Synchron =0.5;
    m_BoolTQCS_Func_Enab_CHECK = TRUE;
//	m_shortTQCS_Synselect=1;
    
	//}}AFX_DATA_INIT
	for(int i=0;i<40;i++)
		ValidData[i]=40-i;
//	MessageBox("constract");
}


void Dlg_TQCS1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_TQCS1)
	DDX_Text(pDX, IDC_EDIT_TQCS_TCB, m_shortTQCS_TCB);
	DDX_Text(pDX, IDC_EDIT_TQCS_D_amax, m_floatTQCS_Damax);
	DDX_Text(pDX, IDC_EDIT_TQCS_D_Umax, m_floatTQCS_DUmax);
	DDX_Text(pDX, IDC_EDIT_TQCS_D_fmax, m_floatTQCS_Dfmax);
	DDX_Text(pDX, IDC_EDIT_TQCS_D_fptmax, m_floatTQCS_Dfptmax);
	DDX_Text(pDX, IDC_EDIT_TQCS_Udead, m_floatTQCS_Udead);
	DDX_Text(pDX, IDC_EDIT_TQCS_TrU1U2, m_floatTQCS_TrU1U2);
	DDX_Text(pDX, IDC_EDIT_TQCS_Umin, m_floatTQCS_Umin);
	DDX_Text(pDX, IDC_EDIT_TQCS_Umax, m_floatTQCS_Umax);
	DDX_Text(pDX, IDC_EDIT_TQCS_fmax, m_floatTQCS_fmax);
	DDX_Text(pDX, IDC_EDIT_TQCS_fmin, m_floatTQCS_fmin);
	DDX_Text(pDX, IDC_EDIT_TQCS_TsynDuration, m_floatTQCS_TsynDuration);
	DDX_Text(pDX, IDC_EDIT_TQCS_Synchron, m_floatTQCS_Synchron);
	DDX_Text(pDX, IDC_EDIT_TQCS_D_fmax2, m_floatTQCS_D_fmax2);
	DDX_Text(pDX, IDC_EDIT_TQCS_D_Umax2, m_floatTQCS_D_Umax2);
	DDX_Text(pDX, IDC_EDIT_TQCS_Synchron2, m_floatTQCS_Synchron2);
	DDX_Check(pDX, IDC_L1_Dead_Volt_CHECK, m_BoolTQCS_L1_Dead_Volt_CHECK);
	DDX_Check(pDX, IDC_L2_Dead_Volt_CHECK, m_BoolTQCS_L2_Dead_Volt_CHECK);
	DDX_Check(pDX, IDC_ALL_Dead_Volt_CHECK, m_BoolTQCS_ALL_Dead_Volt_CHECK);
	DDX_Check(pDX, IDC_Func_Enab_CHECK, m_BoolTQCS_Func_Enab_CHECK);
	DDX_Radio(pDX, IDC_RADIO_Phase_A, m_IntTQCS_RADIO_Phase_A);
	DDX_Radio(pDX, IDC_RADIO_Routine_Auto_Select, m_IntTQCS_RADIO_Routine_Auto_Select);
	DDX_Radio(pDX, IDC_RADIO_ASYN_Style, m_IntTQCS_RADIO_ASYN_Style);
	//}}AFX_DATA_MAP
	unsigned short TempData_short=1;
	UCHAR TempData_UCHAR=1;
	UINT  TempData_UINT=1;
	BOOL  TempData_BOOL=FALSE;
	float TempData_float=0;


//	for(int i=0; i<40;i++)
//		ValidData[i]= GetParent()->this-> TQCS_Data[i];
//	for(int i=0;i<40;i++)
//		ValidData[i]=40-i;
//	ValidData[4]=30;
//	ValidData[5]=40;Q
if(TQCS_FUNCTION==IDC_BUTTON_TQCS_Fetch ||TQCS_FUNCTION==IDC_BUTTON_ZJM_OPEN ||TQCS_FUNCTION==IDC_ZJM_TQCS)
{
	m_IntTQCS_RADIO_Routine_Auto_Select=!ValidData[4];//自动和手动模式选择
	m_IntTQCS_RADIO_ASYN_Style=ValidData[5];//同频非同频选择
	m_BoolTQCS_L1_Dead_Volt_CHECK=ValidData[6];//
	m_BoolTQCS_L2_Dead_Volt_CHECK=ValidData[7];//
	m_BoolTQCS_ALL_Dead_Volt_CHECK=ValidData[8];//
	m_IntTQCS_RADIO_Phase_A=ValidData[9];//
	/*
	TempData_UCHAR=ValidData[4];
//	m_boolTQCS_DeadVlotEn =(BOOL)TempData_UCHAR;
	TempData_UCHAR=ValidData[5];
	if(TempData_UCHAR==1)
	{
		m_nTQCS_SynSubStyle=1;
	}
	else if(ValidData[6]==1)
	{
		m_nTQCS_SynSubStyle=0;
	}
    */
	
	TempData_UCHAR =ValidData[10];           //TCB
	TempData_short= ValidData[11];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortTQCS_TCB =TempData_short;

	TempData_UCHAR =ValidData[12];           //amax
	TempData_short= ValidData[13];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_Damax =TempData_float/100;

	TempData_UCHAR =ValidData[14];           //syn DUmax
	TempData_short= ValidData[15];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_DUmax =TempData_float/100;

	TempData_UCHAR =ValidData[16];           //syn Dfmax
	TempData_short= ValidData[17];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_Dfmax =TempData_float;
    
    TempData_UCHAR =ValidData[18];           //asyn DUmax
	TempData_short= ValidData[19];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
    m_floatTQCS_D_Umax2=TempData_float/100;
    
	TempData_UCHAR =ValidData[20];           //asyn Dfmax
	TempData_short= ValidData[21];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_D_fmax2=TempData_float/100;                               


	TempData_UCHAR =ValidData[22];           //Udead
	TempData_short= ValidData[23];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_Udead =TempData_float/100;

	TempData_UCHAR =ValidData[24];           //Tr.U1 U2
	TempData_short= ValidData[25];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_TrU1U2 =TempData_float/100;

	TempData_UCHAR =ValidData[26];           //Dfptmax
	TempData_short= ValidData[27];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_Dfptmax =TempData_float/100;
    m_floatTQCS_Synchron2=m_floatTQCS_Dfptmax;

	TempData_UCHAR =ValidData[28];           //Umin
	TempData_short= ValidData[29];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_Umin =TempData_float/100;

	TempData_UCHAR =ValidData[30];           //Umax
	TempData_short= ValidData[31];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_Umax =TempData_float/100;

	TempData_UCHAR =ValidData[32];           //fmin
	TempData_short= ValidData[33];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_fmin =TempData_float/100;

	TempData_UCHAR =ValidData[34];           //fmax
	TempData_short= ValidData[35];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_fmax =TempData_float/100;

	TempData_UCHAR =ValidData[36];           //T-syn.Duration (2-30s)
	TempData_short= ValidData[37];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_TsynDuration =TempData_float/10;

	TempData_UCHAR =ValidData[38];           //Synchron (0-60s)
	TempData_short= ValidData[39];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	TempData_float =TempData_short;
	m_floatTQCS_Synchron =TempData_float/10;
    
	m_BoolTQCS_Func_Enab_CHECK=ValidData[40];
	

//	TempData_UCHAR =ValidData[33];            //Syn select (1-47)
//	m_shortTQCS_Synselect =(short)TempData_UCHAR;
}
//	m_shortTQCS_TCB =55;

//MessageBox("TQCS DODATAEXCHANGE");		
}


BEGIN_MESSAGE_MAP(Dlg_TQCS1, CDialog)
	//{{AFX_MSG_MAP(Dlg_TQCS1)
	ON_BN_CLICKED(IDC_BUTTON_TQCS_Apply, OnBUTTONTQCSApply)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_TQCS_Fetch, OnBUTTONTQCSFetch)
	ON_BN_CLICKED(IDC_BUTTON_TQCS_Defult, OnBUTTONTQCSDefult)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_TQCS_SynSubStyle, OnRADIOTQCSSynSubStyle)
	ON_BN_CLICKED(IDC_RADIO_TQCS_Asy, OnRADIOTQCSAsy)
	ON_BN_CLICKED(IDC_Func_Enab_CHECK, OnFuncEnabCHECK)
	ON_BN_CLICKED(IDC_RADIO_Phase_A, OnRADIOPhaseA)
	ON_BN_CLICKED(IDC_RADIO_Phase_B, OnRADIOPhaseB)
	ON_BN_CLICKED(IDC_RADIO_Phase_C, OnRADIOPhaseC)
	ON_BN_CLICKED(IDC_RADIO_Routine_Auto_Select, OnRADIORoutineAutoSelect)
	ON_BN_CLICKED(IDC_RADIO_SYN_Style, OnRADIOSYNStyle)
	ON_BN_CLICKED(IDC_RADIO_ASYN_Style, OnRADIOASYNStyle)
	ON_BN_CLICKED(IDC_L1_Dead_Volt_CHECK, OnL1DeadVoltCHECK)
	ON_BN_CLICKED(IDC_L2_Dead_Volt_CHECK, OnL2DeadVoltCHECK)
	ON_BN_CLICKED(IDC_ALL_Dead_Volt_CHECK, OnALLDeadVoltCHECK)
	ON_BN_CLICKED(IDC_RADIO_Manual_Select, OnRADIOManualSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQCS1 message handlers

void Dlg_TQCS1::OnBUTTONTQCSApply() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(FALSE);
	
	Zero_NR=0;
	UINT Temp_UINT=0;
	unsigned short Temp_short=0;
	UCHAR Temp_UCHAR=0;
	float Temp_float;
	BOOL  Temp_BOOL=FALSE;

	TQCS_FUNCTION=IDC_BUTTON_TQCS_Apply;
	
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_TQCS_Apply;


	UpdateData(TRUE);

//////////////////////////////////////////////////////////////////////////
//                数据转换程序 -- 开始
//////////////////////////////////////////////////////////////////////////

//	if(m_boolTQCS_DeadVlotEn==FALSE)
//		DATA[0]=0;
//	else if(m_boolTQCS_DeadVlotEn==TRUE)
//		DATA[0]=1;
/*
	if(m_IntTQCS_RADIO_Routine_Auto_Select==0)
	{
		DATA[2]=1;
		DATA[1]=0;
	}
	else if(m_IntTQCS_RADIO_Routine_Auto_Select==1)
	{
		DATA[2]=0;
		DATA[1]=1;
	}
	*/
    DATA[0]=!m_IntTQCS_RADIO_Routine_Auto_Select;//自动手动选择

	DATA[1]=m_IntTQCS_RADIO_ASYN_Style;//同频非同频选择
    
	DATA[2]=m_BoolTQCS_L1_Dead_Volt_CHECK;//L1的无压选择
    DATA[3]=m_BoolTQCS_L2_Dead_Volt_CHECK;//
	DATA[4]=m_BoolTQCS_ALL_Dead_Volt_CHECK;//
	DATA[5]=m_IntTQCS_RADIO_Phase_A;//相序选择

	Temp_short=m_shortTQCS_TCB;                  //TCB
	Temp_UCHAR =Temp_short &0xff;
	DATA[6]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[7]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Damax;               //a Max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[8]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[9]=Temp_UCHAR;

    Temp_float= m_floatTQCS_DUmax;               //syn U max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[10]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[11]=Temp_UCHAR;
    
    Temp_float= m_floatTQCS_Dfmax;               //syn df max
	Temp_short = Temp_float;
	Temp_UCHAR =Temp_short &0xff;
	DATA[12]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[13]=Temp_UCHAR;

	Temp_float= m_floatTQCS_D_Umax2;              //asyn dU max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[14]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[15]=Temp_UCHAR;

	Temp_float= m_floatTQCS_D_fmax2;              //asyn df max
	Temp_short = Temp_float*100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[16]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[17]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Udead;               //U dead
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[18]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[19]=Temp_UCHAR;

	Temp_float= m_floatTQCS_TrU1U2;               //Tru1u2
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[20]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[21]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Dfptmax;               //Dfptmax
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[22]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[23]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Umin;               //U min
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[24]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[25]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Umax;               //U max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[26]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[27]=Temp_UCHAR;

	Temp_float= m_floatTQCS_fmin;               //f min
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[28]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[29]=Temp_UCHAR;

	Temp_float= m_floatTQCS_fmax;               //f max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[30]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[31]=Temp_UCHAR;

	Temp_float= m_floatTQCS_TsynDuration;               //TsynDuration
	Temp_short = Temp_float * 10;
	Temp_UCHAR =Temp_short &0xff;
	DATA[32]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[33]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Synchron;                   //Synchron
	Temp_short = Temp_float * 10;
	Temp_UCHAR =Temp_short &0xff;
	DATA[34]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[35]=Temp_UCHAR;

//	Temp_short=m_shortTQCS_Synselect;                    //Synselect
//	Temp_UCHAR =Temp_short &0xff;
//	DATA[29]=Temp_UCHAR;
    DATA[36]=m_BoolTQCS_Func_Enab_CHECK;
	//DATA[36]=0;
	DATA[37]=0;
	DATA[38]=0;
	DATA[39]=0;
	DATA[40]='\0';
	
	

//////////////////////////////////////////////////////////////////////////
//                数据转换程序 -- 结束
//////////////////////////////////////////////////////////////////////////
	UpdateData(FALSE);

	pParent->Connect_Telegram.PACK_SELECT=TRUE;
for(int tt=0; tt<41;tt++)
{
	pParent->Connect_Telegram.ValidDataToPack[tt] =DATA[tt];
	if(DATA[tt]==0)
		Zero_NR++;
}
Zero_NR--;



	pParent->Msg_block_34.Station_adr =0;
	pParent->Msg_block_34.Telegram_Nr=34;
	pParent->Msg_block_34.F1_field =0;
	pParent->Msg_block_34.F2_field =0X80;
	pParent->Fun_Connect(pParent->Msg_block_34,Zero_NR);

	
}


void Dlg_TQCS1::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
//	MessageBox("OnShowWindow");
//	m_nTQCS_SynSubStyle=1;
		UpdateData(FALSE);
    
	// TODO: Add your message handler code here
	
}

void Dlg_TQCS1::OnBUTTONTQCSFetch() 
{
	// TODO: Add your control notification handler code here
	TQCS_FUNCTION=IDC_BUTTON_TQCS_Fetch;
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_TQCS_Fetch;


	pParent->TQCS_block_35.Station_adr=0;
	pParent->TQCS_block_35.Telegram_Nr=35;
	pParent->TQCS_block_35.F1_field=0;
	pParent->TQCS_block_35.F2_field=0x80;
	pParent->TQCS_block_35.Data=(UCHAR *)"";
	pParent->Fun_Connect(pParent->TQCS_block_35,0);
	SetTimer(IDC_BUTTON_TQCS_Fetch,666,NULL);

	
}

void Dlg_TQCS1::OnBUTTONTQCSDefult() 
{
	// TODO: Add your control notification handler code here
	TQCS_FUNCTION=IDC_BUTTON_TQCS_Defult;
	UpdateData(TRUE);

//	m_boolTQCS_DeadVlotEn =TRUE;
	m_IntTQCS_RADIO_Routine_Auto_Select=1;
	m_IntTQCS_RADIO_ASYN_Style=0;
	m_IntTQCS_RADIO_Phase_A=0;
	//m_nTQCS_SynSubStyle=1;
    m_BoolTQCS_L1_Dead_Volt_CHECK=FALSE;//L1的无压选择
    m_BoolTQCS_L2_Dead_Volt_CHECK=FALSE;//
    m_BoolTQCS_ALL_Dead_Volt_CHECK=FALSE;//
	m_shortTQCS_TCB =80;
	m_floatTQCS_Damax =10;
	m_floatTQCS_DUmax =2.0;
	m_floatTQCS_D_Umax2=2.0;
	m_floatTQCS_Dfmax =20;
	m_floatTQCS_D_fmax2=0.10;
	m_floatTQCS_Udead =2.0;
	m_floatTQCS_TrU1U2 =0;
	m_floatTQCS_Dfptmax =0.2;
	m_floatTQCS_Synchron2=0.2;
	m_floatTQCS_Umin =52.0;
	m_floatTQCS_Umax=63.5;
	m_floatTQCS_fmin=47.50;
	m_floatTQCS_fmax =52.50;
	m_floatTQCS_TsynDuration =30;
	m_floatTQCS_Synchron =0.5;
    m_BoolTQCS_Func_Enab_CHECK = TRUE;
//	m_shortTQCS_Synselect=1;
   ((CButton*)GetDlgItem(IDC_RADIO_SYN_Style))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK&&m_IntTQCS_RADIO_Routine_Auto_Select);
   ((CButton*)GetDlgItem(IDC_RADIO_ASYN_Style))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK&&m_IntTQCS_RADIO_Routine_Auto_Select);
   ((CButton*)GetDlgItem(IDC_RADIO_Manual_Select))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Routine_Auto_Select))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_L1_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_L2_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_ALL_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_A))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_B))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_C))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TCB))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Udead))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_amax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TrU1U2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_Umax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fptmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_Umax2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_fmin))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_fmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fmax2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TsynDuration))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Umin))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Synchron))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Umax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Synchron2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   //((CButton*)GetDlgItem(IDC_RADIO_SYN_Style))->EnableWindow(m_IntTQCS_RADIO_Routine_Auto_Select);
   //((CButton*)GetDlgItem(IDC_RADIO_ASYN_Style))->EnableWindow(m_IntTQCS_RADIO_Routine_Auto_Select);
	UpdateData(FALSE);	
}

void Dlg_TQCS1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==IDC_BUTTON_TQCS_Fetch)
	{
		KillTimer(IDC_BUTTON_TQCS_Fetch);
		UpdateData(TRUE);
		UpdateData(FALSE);
//		MessageBox("dd");
   ((CButton*)GetDlgItem(IDC_RADIO_SYN_Style))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK&&m_IntTQCS_RADIO_Routine_Auto_Select);
   ((CButton*)GetDlgItem(IDC_RADIO_ASYN_Style))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK&&m_IntTQCS_RADIO_Routine_Auto_Select);
   ((CButton*)GetDlgItem(IDC_RADIO_Manual_Select))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Routine_Auto_Select))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_L1_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_L2_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_ALL_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_A))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_B))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_C))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TCB))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Udead))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_amax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TrU1U2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_Umax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fptmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_Umax2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_fmin))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_fmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fmax2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TsynDuration))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Umin))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Synchron))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Umax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Synchron2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
	}
	CDialog::OnTimer(nIDEvent);
}

void Dlg_TQCS1::OnCancel() 
{
	// TODO: Add extra cleanup here
	Zero_NR=0;
	UINT Temp_UINT=0;
	unsigned short Temp_short=0;
	UCHAR Temp_UCHAR=0;
	float Temp_float;
	BOOL  Temp_BOOL=FALSE;
//	UCHAR DATA[256];
	//////////////////////////////////////////////////////////////////////////
//                数据转换程序 -- 开始
//////////////////////////////////////////////////////////////////////////
UpdateData(TRUE);
//	if(m_boolTQCS_DeadVlotEn==FALSE)
//		DATA[0]=0;
//	else if(m_boolTQCS_DeadVlotEn==TRUE)
//		DATA[0]=1;
    /*
	if(m_nTQCS_SynSubStyle==0)
	{
		DATA[2]=1;
		DATA[1]=0;
	}
	else if(m_nTQCS_SynSubStyle==1)
	
	Temp_short=m_shortTQCS_TCB;                  //TCB
	Temp_UCHAR =Temp_short &0xff;
	DATA[3]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[4]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Damax;               //a Max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[5]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[6]=Temp_UCHAR;

	Temp_float= m_floatTQCS_DUmax;               //U max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[7]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[8]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Dfmax;               //f max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[9]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[10]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Udead;               //U dead
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[11]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[12]=Temp_UCHAR;

	Temp_float= m_floatTQCS_TrU1U2;               //Tru1u2
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[13]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[14]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Dfptmax;               //Dfptmax
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[15]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[16]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Umin;               //U min
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[17]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[18]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Umax;               //U max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[19]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[20]=Temp_UCHAR;

	Temp_float= m_floatTQCS_fmin;               //f min
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[21]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[22]=Temp_UCHAR;

	Temp_float= m_floatTQCS_fmax;               //f max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[23]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[24]=Temp_UCHAR;

	Temp_float= m_floatTQCS_TsynDuration;               //TsynDuration
	Temp_short = Temp_float * 10;
	Temp_UCHAR =Temp_short &0xff;
	DATA[25]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[26]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Synchron;                   //Synchron
	Temp_short = Temp_float * 10;
	Temp_UCHAR =Temp_short &0xff;
	DATA[27]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[28]=Temp_UCHAR;

//	Temp_short=m_shortTQCS_Synselect;                    //Synselect
//	Temp_UCHAR =Temp_short &0xff;
//	DATA[29]=Temp_UCHAR;

	DATA[30]=0;
	DATA[31]=0;
	DATA[32]=0;
	DATA[33]='\0';
	*/
	DATA[0]=!m_IntTQCS_RADIO_Routine_Auto_Select;//自动手动选择

	DATA[1]=m_IntTQCS_RADIO_ASYN_Style;//同频非同频选择
    
	DATA[2]=m_BoolTQCS_L1_Dead_Volt_CHECK;//L1的无压选择
    DATA[3]=m_BoolTQCS_L2_Dead_Volt_CHECK;//
	DATA[4]=m_BoolTQCS_ALL_Dead_Volt_CHECK;//
	DATA[5]=m_IntTQCS_RADIO_Phase_A;//相序选择

	Temp_short=m_shortTQCS_TCB;                  //TCB
	Temp_UCHAR =Temp_short &0xff;
	DATA[6]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[7]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Damax;               //a Max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[8]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[9]=Temp_UCHAR;

    Temp_float= m_floatTQCS_DUmax;               //syn U max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[10]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[11]=Temp_UCHAR;
    
    Temp_float= m_floatTQCS_Dfmax;               //syn f max
	Temp_short = Temp_float ;
	Temp_UCHAR =Temp_short &0xff;
	DATA[12]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[13]=Temp_UCHAR;

	Temp_float= m_floatTQCS_D_Umax2;              //asyn U max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[14]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[15]=Temp_UCHAR;

	Temp_float= m_floatTQCS_D_fmax2;              //asyn f max
	Temp_short = Temp_float*100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[16]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[17]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Udead;               //U dead
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[18]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[19]=Temp_UCHAR;

	Temp_float= m_floatTQCS_TrU1U2;               //Tru1u2
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[20]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[21]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Dfptmax;               //Dfptmax
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[22]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[23]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Umin;               //U min
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[24]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[25]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Umax;               //U max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[26]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[27]=Temp_UCHAR;

	Temp_float= m_floatTQCS_fmin;               //f min
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[28]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[29]=Temp_UCHAR;

	Temp_float= m_floatTQCS_fmax;               //f max
	Temp_short = Temp_float * 100;
	Temp_UCHAR =Temp_short &0xff;
	DATA[30]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[31]=Temp_UCHAR;

	Temp_float= m_floatTQCS_TsynDuration;               //TsynDuration
	Temp_short = Temp_float * 10;
	Temp_UCHAR =Temp_short &0xff;
	DATA[32]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[33]=Temp_UCHAR;

	Temp_float= m_floatTQCS_Synchron;                   //Synchron
	Temp_short = Temp_float * 10;
	Temp_UCHAR =Temp_short &0xff;
	DATA[34]=Temp_UCHAR;
	Temp_UCHAR= Temp_short>>8;
	DATA[35]=Temp_UCHAR;

//	Temp_short=m_shortTQCS_Synselect;                    //Synselect
//	Temp_UCHAR =Temp_short &0xff;
//	DATA[29]=Temp_UCHAR;
    DATA[36]=m_BoolTQCS_Func_Enab_CHECK;
	//DATA[36]=0;
	DATA[37]=0;
	DATA[38]=0;
	DATA[39]=0;
	DATA[40]='\0';
	

//////////////////////////////////////////////////////////////////////////
//                数据转换程序 -- 结束
//////////////////////////////////////////////////////////////////////////
	
	CDialog::OnCancel();
}

void Dlg_TQCS1::OnRADIOTQCSSynSubStyle() 
{
	// TODO: Add your control notification handler code here
	m_nTQCS_SynSubStyle=0;
}

void Dlg_TQCS1::OnRADIOTQCSAsy() 
{
	// TODO: Add your control notification handler code here
	m_nTQCS_SynSubStyle=1;
}



void Dlg_TQCS1::OnFuncEnabCHECK() 
{
	// TODO: Add your control notification handler code here
	m_BoolTQCS_Func_Enab_CHECK = !m_BoolTQCS_Func_Enab_CHECK;
   ((CButton*)GetDlgItem(IDC_RADIO_SYN_Style))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_ASYN_Style))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Manual_Select))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Routine_Auto_Select))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_L1_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_L2_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_ALL_Dead_Volt_CHECK))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_A))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_B))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CButton*)GetDlgItem(IDC_RADIO_Phase_C))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TCB))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Udead))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_amax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TrU1U2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_Umax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fptmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_Umax2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_fmin))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_fmax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_D_fmax2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_TsynDuration))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Umin))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Synchron))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Umax))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
   ((CEdit*)GetDlgItem(IDC_EDIT_TQCS_Synchron2))->EnableWindow(m_BoolTQCS_Func_Enab_CHECK);
}

void Dlg_TQCS1::OnRADIOPhaseA() 
{
	// TODO: Add your control notification handler code here
	m_IntTQCS_RADIO_Phase_A=0;
}

void Dlg_TQCS1::OnRADIOPhaseB() 
{
	// TODO: Add your control notification handler code here
	m_IntTQCS_RADIO_Phase_A=1;
}

void Dlg_TQCS1::OnRADIOPhaseC() 
{
	// TODO: Add your control notification handler code here
	m_IntTQCS_RADIO_Phase_A=2;
}

void Dlg_TQCS1::OnRADIORoutineAutoSelect() 
{
	// TODO: Add your control notification handler code here
	m_IntTQCS_RADIO_Routine_Auto_Select=0;
	((CButton*)GetDlgItem(IDC_RADIO_SYN_Style))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_ASYN_Style))->EnableWindow(FALSE);
}

void Dlg_TQCS1::OnRADIOSYNStyle() 
{
	// TODO: Add your control notification handler code here
//m_IntTQCS_RADIO_SYN_Style=0;
		m_IntTQCS_RADIO_ASYN_Style=1;
}

void Dlg_TQCS1::OnRADIOASYNStyle() 
{
	// TODO: Add your control notification handler code here
	m_IntTQCS_RADIO_ASYN_Style=0;
}

void Dlg_TQCS1::OnL1DeadVoltCHECK() 
{
	// TODO: Add your control notification handler code here
	
}

void Dlg_TQCS1::OnL2DeadVoltCHECK() 
{
	// TODO: Add your control notification handler code here
	
}

void Dlg_TQCS1::OnALLDeadVoltCHECK() 
{
	// TODO: Add your control notification handler code here
	
}

void Dlg_TQCS1::OnRADIOManualSelect() 
{
	// TODO: Add your control notification handler code here
	m_IntTQCS_RADIO_Routine_Auto_Select=1;
	((CButton*)GetDlgItem(IDC_RADIO_SYN_Style))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_ASYN_Style))->EnableWindow(TRUE);
}
