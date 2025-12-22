// Dlg_TQML.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_TQML.h"

#include "new1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQML dialog


Dlg_TQML::Dlg_TQML(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_TQML::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_TQML)
	m_nTQML_REC = 0;
	m_DateTimeTQML_REC_DATE = COleDateTime::GetCurrentTime();
	m_DateTimeTQML_SENT_DATE = COleDateTime::GetCurrentTime();
	m_BOOLTQML_REC_OK = FALSE;
	m_BOOLTQML_SENT_OK = FALSE;
	m_BOOLTQML_TIME_OK = FALSE;
	m_floatTQML_REC_DA = 0.0f;
	m_floatTQML_REC_DF = 0.0f;
	m_floatTQML_REC_DU = 0.0f;
	m_floatTQML_REC_F1 = 0.0f;
	m_floatTQML_REC_F2 = 0.0f;
	m_floatTQML_SENT_DA = 0.0f;
	m_floatTQML_SENT_DF = 0.0f;
	m_floatTQML_SENT_DU = 0.0f;
	m_floatTQML_SENT_F1 = 0.0f;
	m_floatTQML_SENT_F2 = 0.0f;
	m_floatTQML_TIME_DA = 0.0f;
	m_floatTQML_TIME_DF = 0.0f;
	m_floatTQML_TIME_DU = 0.0f;
	m_floatTQML_TIME_F1 = 0.0f;
	m_floatTQML_TIME_F2 = 0.0f;
	m_DateTimeTQML_TIME_DATE = COleDateTime::GetCurrentTime();
	m_nTQML_REC_MS = 0;
	m_nTQML_SENT_MS = 0;
	m_nTQML_TIME_MS = 0;
	m_BOOLTQML_UNFINISH = FALSE;
	m_BOOLTQML_RESET = FALSE;
	m_floatTQML_REC_U1 = 0.0f;
	m_floatTQML_TIME_U1 = 0.0f;
	m_floatTQML_REC_DF_DT = 0.0f;
	m_floatTQML_REC_F1_DT = 0.0f;
	m_floatTQML_REC_F2_DT = 0.0f;
	m_floatTQML_REC_U2 = 0.0f;
	m_floatTQML_SENT_F1_DT = 0.0f;
	m_floatTQML_SENT_U1 = 0.0f;
	m_floatTQML_SENT_U2 = 0.0f;
	m_floatTQML_TIME_DF_DT = 0.0f;
	m_floatTQML_TIME_F1_DT = 0.0f;
	m_floatTQML_TIME_F2_DT = 0.0f;
	m_floatTQML_TIME_U2 = 0.0f;
	m_floatTQML_SENT_F2_DT = 0.0f;
	m_floatTQML_SENT_DF_DT = 0.0f;
	//}}AFX_DATA_INIT
}


void Dlg_TQML::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_TQML)
	DDX_Radio(pDX, IDC_RADIO_TQML_REC, m_nTQML_REC);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_DATE, m_DateTimeTQML_REC_DATE);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_DATE, m_DateTimeTQML_SENT_DATE);
	DDX_Check(pDX, IDC_CHECK_TQML_REC_OK, m_BOOLTQML_REC_OK);
	DDX_Check(pDX, IDC_CHECK_TQML_SENT_OK, m_BOOLTQML_SENT_OK);
	DDX_Check(pDX, IDC_CHECK_TQML_TIME_OK, m_BOOLTQML_TIME_OK);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_DA, m_floatTQML_REC_DA);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_DF, m_floatTQML_REC_DF);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_DU, m_floatTQML_REC_DU);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_F1, m_floatTQML_REC_F1);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_F2, m_floatTQML_REC_F2);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_DA, m_floatTQML_SENT_DA);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_DF, m_floatTQML_SENT_DF);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_DU, m_floatTQML_SENT_DU);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_F1, m_floatTQML_SENT_F1);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_F2, m_floatTQML_SENT_F2);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_DA, m_floatTQML_TIME_DA);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_DF, m_floatTQML_TIME_DF);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_DU, m_floatTQML_TIME_DU);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_F1, m_floatTQML_TIME_F1);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_F2, m_floatTQML_TIME_F2);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_DATE, m_DateTimeTQML_TIME_DATE);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_ms, m_nTQML_REC_MS);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_ms, m_nTQML_SENT_MS);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_ms, m_nTQML_TIME_MS);
	DDX_Check(pDX, IDC_CHECK_TQML_UNFINSH, m_BOOLTQML_UNFINISH);
	DDX_Check(pDX, IDC_CHECK_TQML_RESET, m_BOOLTQML_RESET);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_U1, m_floatTQML_REC_U1);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_U1, m_floatTQML_TIME_U1);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_DF_DT, m_floatTQML_REC_DF_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_F1_DT, m_floatTQML_REC_F1_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_F2_DT, m_floatTQML_REC_F2_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_REC_U2, m_floatTQML_REC_U2);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_F1_DT, m_floatTQML_SENT_F1_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_U1, m_floatTQML_SENT_U1);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_U2, m_floatTQML_SENT_U2);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_DF_DT, m_floatTQML_TIME_DF_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_F1_DT, m_floatTQML_TIME_F1_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_F2_DT, m_floatTQML_TIME_F2_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_TIME_U2, m_floatTQML_TIME_U2);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_F2_DT, m_floatTQML_SENT_F2_DT);
	DDX_Text(pDX, IDC_EDIT_TQML_SENT_DF_DT, m_floatTQML_SENT_DF_DT);
	//}}AFX_DATA_MAP

	if(Function_ID==IDC_BUTTON_TQML_FETCH)
	{
		UCHAR Temp_UCHAR;
		UINT Temp_UINT,millisecond;
		int year = 0,month =0, day =0, hour =0, minute =0, second =0, Temp_int;
		unsigned short Temp_short,DayofYear_short;
		float f1,f2,u1,u2,f1dt,f2dt,Dfdt,Df,Da,DU,Temp_float;

		Temp_UCHAR=ValidData[5];
		Temp_short =ValidData[6];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR;              //day

//////////////////////////////////////////////////////////////////////////
//      计算出  年 月 日
//////////////////////////////////////////////////////////////////////////
//Temp_short++;

		for(year=1984; Temp_short>365; year++)
		{ 
			if(((year%4==0)&&(year%100!=0))||(year%400==0))    //yun nian
			{
					Temp_short-=366;
			}
			else
				Temp_short-=365;
		}
		if(Temp_short==0)                        //yun nian shi 
		{
			year--;                                     //nian 
			DayofYear_short=366; 
			for(int mm=1;mm<=12;mm++)
			{
				if(mm==1 || mm==3 ||mm ==5 ||mm==7|| mm==8 || mm==10 || mm==12)                     
				{
					if(DayofYear_short>31)
						DayofYear_short-=31;
					else
						break;
				}
				else if(mm==2)
				{
					if(DayofYear_short>29)
						DayofYear_short-=29;
					else
						break;
				}
				else if(mm==4 ||mm==6 ||mm==9 ||mm==11)
				{
					if(DayofYear_short>30)
						DayofYear_short-=30;
					else
						break;
				}

			}
			month =mm;
			day = (int)DayofYear_short;
		}
		else if(Temp_short>0)
		{
			DayofYear_short= Temp_short;                          //
			for(int mm=1;mm<=12;mm++)
			{
				if(mm==1 || mm==3 ||mm ==5 ||mm==7|| mm==8 || mm==10 || mm==12)                     
				{
					if(DayofYear_short>31)
						DayofYear_short-=31;
					else
						break;
				}
				else if(mm==2)
				{
					
					if(((year%4==0)&&(year%100!=0))||(year%400==0))    //yun nian
					{
						if(DayofYear_short>29)
							DayofYear_short-=29;
						else
							break;
					}
					else if(DayofYear_short>28)
						DayofYear_short-=28;					
					else
						break;
					
				}
				else if(mm==4 ||mm==6 ||mm==9 ||mm==11)
				{
					if(DayofYear_short>30)
						DayofYear_short-=30;
					else
						break;
				}

			}
			month = mm;
			day= (int)DayofYear_short;
		}
//////////////////////////////////////////////////////////////////////////
//       end
//////////////////////////////////////////////////////////////////////////
		Temp_UCHAR=ValidData[9];
		Temp_short =ValidData[10];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR;  
		Temp_UINT =Temp_short;
		Temp_UINT =Temp_UINT<<16;
		Temp_UCHAR=ValidData[7];
		Temp_short =ValidData[8];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_UINT +=Temp_short;              //ms

//////////////////////////////////////////////////////////////////////////
//       hour  minute second
//////////////////////////////////////////////////////////////////////////

		Temp_int =Temp_UINT;
		hour =Temp_int/3600000;
		Temp_int =Temp_UINT %3600000;
		minute =Temp_int/60000;
		Temp_int =Temp_int %60000;
		second =Temp_int/1000;
		millisecond = Temp_int %1000;
//hour =second =minute =0;
		
//////////////////////////////////////////////////////////////////////////
//       end
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//       f1    f2   Df   Da   DU
//////////////////////////////////////////////////////////////////////////
	    Temp_UCHAR=ValidData[11];
		Temp_short =ValidData[12];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
	    u1 =Temp_float/100;                     //u1

        Temp_UCHAR=ValidData[13];
		Temp_short =ValidData[14];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		u2 =Temp_float/100;                     //u2

		Temp_UCHAR=ValidData[15];
		Temp_short =ValidData[16];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		f1 =Temp_float/1000;                     //f1

		Temp_UCHAR=ValidData[17];
		Temp_short =ValidData[18];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		f2 =Temp_float/1000;                     //f2

		Temp_UCHAR=ValidData[19];
		Temp_short =ValidData[20];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		f1dt =Temp_float/100;                     //f1/dt

		Temp_UCHAR=ValidData[21];
		Temp_short =ValidData[22];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		f2dt =Temp_float/100;                     //f2/dt
		
		Temp_UCHAR=ValidData[23];
		Temp_short =ValidData[24];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		DU =Temp_float/100;                     //DU

		Temp_UCHAR=ValidData[25];
		Temp_short =ValidData[26];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		Df =Temp_float/1000;                     //Df
			
		Temp_UCHAR=ValidData[27];
		Temp_short =ValidData[28];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		Dfdt =Temp_float/100;                     //Df/dt

		Temp_UCHAR=ValidData[29];
		Temp_short =ValidData[30];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_float= Temp_short;
		Da =Temp_float/100;                     //Da		
//////////////////////////////////////////////////////////////////////////
//       end
//////////////////////////////////////////////////////////////////////////

		if(ValidData[4]==1)           //when 1,
		{
			m_DateTimeTQML_REC_DATE.SetDateTime(year,month,day,hour,minute,second);
			m_nTQML_REC=0;
			m_nTQML_REC_MS =millisecond;
			m_floatTQML_REC_F1 =f1;
			m_floatTQML_REC_F2 =f2;
			m_floatTQML_REC_DF =Df;
			m_floatTQML_REC_DA =Da;
			m_floatTQML_REC_DU =DU;
			m_floatTQML_REC_U1=u1;
			m_floatTQML_REC_U2=u2;
			m_floatTQML_REC_F1_DT=f1dt;
			m_floatTQML_REC_F2_DT=f2dt;
			m_floatTQML_REC_DF_DT=Dfdt;

			m_BOOLTQML_UNFINISH =0;
			m_BOOLTQML_RESET =0;
			m_BOOLTQML_REC_OK =TRUE;
			
		}
		else if(ValidData[4]==2)      //when 2,
		{
			m_DateTimeTQML_SENT_DATE.SetDateTime(year,month,day,hour,minute,second);
			m_nTQML_REC=1;
			m_nTQML_SENT_MS =millisecond;
			m_floatTQML_SENT_F1 =f1;
			m_floatTQML_SENT_F2 =f2;
			m_floatTQML_SENT_DF =Df;
			m_floatTQML_SENT_DA =Da;
			m_floatTQML_SENT_DU =DU;
			m_floatTQML_SENT_U1=u1;
			m_floatTQML_SENT_U2=u2;
			m_floatTQML_SENT_F1_DT=f1dt;
			m_floatTQML_SENT_F2_DT=f2dt;
			m_floatTQML_SENT_DF_DT=Dfdt;

			m_BOOLTQML_UNFINISH =0;
			m_BOOLTQML_RESET =0;
			m_BOOLTQML_SENT_OK =TRUE;
		}
		else if(ValidData[4]==3)      //when 3
		{
			m_DateTimeTQML_TIME_DATE.SetDateTime(year,month,day,hour,minute,second);
			m_nTQML_REC=2;
			m_nTQML_TIME_MS =millisecond;
			m_floatTQML_TIME_F1 =f1;
			m_floatTQML_TIME_F2 =f2;
			m_floatTQML_TIME_DF =Df;
			m_floatTQML_TIME_DA =Da;
			m_floatTQML_TIME_DU =DU;
			m_floatTQML_TIME_U1=u1;
			m_floatTQML_TIME_U2=u2;
			m_floatTQML_TIME_F1_DT=f1dt;
			m_floatTQML_TIME_F2_DT=f2dt;
			m_floatTQML_TIME_DF_DT=Dfdt;

			m_BOOLTQML_UNFINISH =0;
			m_BOOLTQML_RESET =0;

			m_BOOLTQML_TIME_OK =TRUE;
		}
		else if(ValidData[4]==4)      //when 4  FU GUI
		{
			m_BOOLTQML_RESET =1;
			m_BOOLTQML_UNFINISH =0;
//////////////////////////////////////////////////////////////////////////
//            clear
//////////////////////////////////////////////////////////////////////////

	m_DateTimeTQML_REC_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_SENT_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_TIME_DATE.SetDateTime(1000,10,10,10,10,10);
	m_BOOLTQML_TIME_OK =m_BOOLTQML_SENT_OK=m_BOOLTQML_REC_OK =FALSE;
	m_floatTQML_REC_DA = 0.0f;
	m_floatTQML_REC_DF = 0.0f;
	m_floatTQML_REC_DU = 0.0f;
	m_floatTQML_REC_F1 = 0.0f;
	m_floatTQML_REC_F2 = 0.0f;
	m_floatTQML_SENT_DA = 0.0f;
	m_floatTQML_SENT_DF = 0.0f;
	m_floatTQML_SENT_DU = 0.0f;
	m_floatTQML_SENT_F1 = 0.0f;
	m_floatTQML_SENT_F2 = 0.0f;
	m_floatTQML_TIME_DA = 0.0f;
	m_floatTQML_TIME_DF = 0.0f;
	m_floatTQML_TIME_DU = 0.0f;
	m_floatTQML_TIME_F1 = 0.0f;
	m_floatTQML_TIME_F2 = 0.0f;
	m_nTQML_REC_MS =0;
	m_nTQML_SENT_MS =0;
	m_nTQML_TIME_MS =0;


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
		}
		else if(ValidData[4]==5)      //when 5   WEI WAN CHENG
		{
			m_BOOLTQML_UNFINISH =1;
			m_BOOLTQML_RESET =0;

//////////////////////////////////////////////////////////////////////////
//            clear
//////////////////////////////////////////////////////////////////////////

	m_DateTimeTQML_REC_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_SENT_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_TIME_DATE.SetDateTime(1000,10,10,10,10,10);
	m_BOOLTQML_TIME_OK =m_BOOLTQML_SENT_OK=m_BOOLTQML_REC_OK =FALSE;
	m_floatTQML_REC_DA = 0.0f;
	m_floatTQML_REC_DF = 0.0f;
	m_floatTQML_REC_DU = 0.0f;
	m_floatTQML_REC_F1 = 0.0f;
	m_floatTQML_REC_F2 = 0.0f;
	m_floatTQML_SENT_DA = 0.0f;
	m_floatTQML_SENT_DF = 0.0f;
	m_floatTQML_SENT_DU = 0.0f;
	m_floatTQML_SENT_F1 = 0.0f;
	m_floatTQML_SENT_F2 = 0.0f;
	m_floatTQML_TIME_DA = 0.0f;
	m_floatTQML_TIME_DF = 0.0f;
	m_floatTQML_TIME_DU = 0.0f;
	m_floatTQML_TIME_F1 = 0.0f;
	m_floatTQML_TIME_F2 = 0.0f;
	m_nTQML_REC_MS =0;
	m_nTQML_SENT_MS =0;
	m_nTQML_TIME_MS =0;


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
		}
	}

	
	Function_ID =NULL;

}


BEGIN_MESSAGE_MAP(Dlg_TQML, CDialog)
	//{{AFX_MSG_MAP(Dlg_TQML)
	ON_BN_CLICKED(IDC_BUTTON_TQML_APPLY, OnButtonTqmlApply)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_TQML_SENT, OnRadioTqmlSent)
	ON_BN_CLICKED(IDC_RADIO_TQML_TIME, OnRadioTqmlTime)
	ON_BN_CLICKED(IDC_BUTTON_TQML_FETCH, OnButtonTqmlFetch)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_TQML_REC, OnRadioTqmlRec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQML message handlers

void Dlg_TQML::OnButtonTqmlApply() 
{
	// TODO: Add your control notification handler code here
	
	Function_ID =IDC_BUTTON_TQML_APPLY;

	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_TQML_APPLY;


//////////////////////////////////////////////////////////////////////////
//            clear
//////////////////////////////////////////////////////////////////////////

	m_DateTimeTQML_REC_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_SENT_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_TIME_DATE.SetDateTime(1000,10,10,10,10,10);
	m_BOOLTQML_TIME_OK =m_BOOLTQML_SENT_OK=m_BOOLTQML_REC_OK =m_BOOLTQML_UNFINISH=m_BOOLTQML_RESET=FALSE;
	m_floatTQML_REC_DA = 0.0f;
	m_floatTQML_REC_DF = 0.0f;
	m_floatTQML_REC_DU = 0.0f;
	m_floatTQML_REC_F1 = 0.0f;
	m_floatTQML_REC_F2 = 0.0f;
    m_floatTQML_REC_U1 = 0.0f;
	m_floatTQML_REC_U2 = 0.0f;
	m_floatTQML_REC_DF_DT=0.0f;
	m_floatTQML_REC_F1_DT=0.0f;
	m_floatTQML_REC_F2_DT=0.0f;
	m_floatTQML_SENT_DA = 0.0f;
	m_floatTQML_SENT_DF = 0.0f;
	m_floatTQML_SENT_DU = 0.0f;
	m_floatTQML_SENT_F1 = 0.0f;
	m_floatTQML_SENT_F2 = 0.0f;
	m_floatTQML_SENT_U1=0.0f;
	m_floatTQML_SENT_U2=0.0f;
	m_floatTQML_SENT_DF_DT=0.0f;
	m_floatTQML_SENT_F1_DT=0.0f;
	m_floatTQML_SENT_F2_DT=0.0f;
	m_floatTQML_TIME_DA = 0.0f;
	m_floatTQML_TIME_DF = 0.0f;
	m_floatTQML_TIME_DU = 0.0f;
	m_floatTQML_TIME_F1 = 0.0f;
	m_floatTQML_TIME_F2 = 0.0f;
	m_floatTQML_TIME_U1=0.0f;
	m_floatTQML_TIME_U2=0.0f;
	m_floatTQML_TIME_DF_DT=0.0f;
	m_floatTQML_TIME_F1_DT=0.0f;
	m_floatTQML_TIME_F2_DT=0.0f;
	m_nTQML_REC_MS =0;
	m_nTQML_SENT_MS =0;
	m_nTQML_TIME_MS =0;


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

	pParent->TQML_block_44.Station_adr =0;
	pParent->TQML_block_44.Telegram_Nr=44;
	pParent->TQML_block_44.F1_field =0;
	pParent->TQML_block_44.F2_field =0X80;
	pParent->Connect_Telegram.ValidDataToPack[0]=0x55;
	pParent->Connect_Telegram.ValidDataToPack[1]=0xaa;
	pParent->Connect_Telegram.ValidDataToPack[2]=0;
	pParent->Connect_Telegram.PACK_SELECT=TRUE;
	pParent->Fun_Connect(pParent->TQML_block_44,0);

	UpdateData(FALSE);
}

void Dlg_TQML::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here

	m_DateTimeTQML_REC_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_SENT_DATE.SetDateTime(1000,10,10,10,10,10);
	m_DateTimeTQML_TIME_DATE.SetDateTime(1000,10,10,10,10,10);
	m_BOOLTQML_TIME_OK =m_BOOLTQML_SENT_OK=m_BOOLTQML_REC_OK =m_BOOLTQML_UNFINISH=m_BOOLTQML_RESET=FALSE;
	m_floatTQML_REC_DA = 0.0f;
	m_floatTQML_REC_DF = 0.0f;
	m_floatTQML_REC_DU = 0.0f;
	m_floatTQML_REC_F1 = 0.0f;
	m_floatTQML_REC_F2 = 0.0f;
	m_floatTQML_SENT_DA = 0.0f;
	m_floatTQML_SENT_DF = 0.0f;
	m_floatTQML_SENT_DU = 0.0f;
	m_floatTQML_SENT_F1 = 0.0f;
	m_floatTQML_SENT_F2 = 0.0f;
	m_floatTQML_TIME_DA = 0.0f;
	m_floatTQML_TIME_DF = 0.0f;
	m_floatTQML_TIME_DU = 0.0f;
	m_floatTQML_TIME_F1 = 0.0f;
	m_floatTQML_TIME_F2 = 0.0f;
	m_nTQML_REC_MS =0;
	m_nTQML_SENT_MS =0;
	m_nTQML_TIME_MS =0;
	UpdateData(FALSE);
}

void Dlg_TQML::OnRadioTqmlSent() 
{
	// TODO: Add your control notification handler code here
	m_nTQML_REC=1;
}

void Dlg_TQML::OnRadioTqmlTime() 
{
	// TODO: Add your control notification handler code here
	m_nTQML_REC=2;
}

void Dlg_TQML::OnButtonTqmlFetch() 
{
	// TODO: Add your control notification handler code here

	Function_ID =IDC_BUTTON_TQML_FETCH;

	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_TQML_FETCH;

	pParent->TQML_block_45.Station_adr =0;
	pParent->TQML_block_45.Telegram_Nr=45;
	pParent->TQML_block_45.F1_field =0;
	pParent->TQML_block_45.F2_field =0X80;
	pParent->Connect_Telegram.ValidDataToPack[0]=(UCHAR)(m_nTQML_REC+1);
	pParent->Connect_Telegram.ValidDataToPack[1]=0;
	pParent->Connect_Telegram.PACK_SELECT=TRUE;

	pParent->Fun_Connect(pParent->TQML_block_45,0);

	SetTimer(IDC_BUTTON_TQML_FETCH,666,NULL);
//	ValidData[4]=2;
//	ValidData[5]=ValidData[6]=ValidData[10]=ValidData[11]=0;
//	ValidData[7]=ValidData[8]=ValidData[9]=0;
}

void Dlg_TQML::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==IDC_BUTTON_TQML_FETCH)
	{
//		MessageBox("t");
		KillTimer(IDC_BUTTON_TQML_FETCH);
		UpdateData(TRUE);
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

void Dlg_TQML::OnRadioTqmlRec() 
{
	// TODO: Add your control notification handler code here
	m_nTQML_REC=0;
}
