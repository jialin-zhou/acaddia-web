// Dlg_TimeSet.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_TimeSet.h"

#include "new1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_TimeSet dialog


Dlg_TimeSet::Dlg_TimeSet(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_TimeSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_TimeSet)
	m_nTime = COleDateTime::GetCurrentTime();
	m_nData = COleDateTime::GetCurrentTime();
	ENTimer =0;
	m_BOOLSetStatus = FALSE;
	//}}AFX_DATA_INIT
	//MessageBox("Dlg_TimeSet::Dlg_TimeSet(CWnd* pParent /*=NULL*/) : CDialog(Dlg_TimeSet::IDD, pParent)");

//	MessageBox("GZ");
}

void Dlg_TimeSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_TimeSet)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TIME, m_nTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATA, m_nData);
	DDX_Check(pDX, IDC_CHECK_SET, m_BOOLSetStatus);
	//}}AFX_DATA_MAP
	//MessageBox("void Dlg_TimeSet::DoDataExchange(CDataExchange* pDX)");

	unsigned short Temp_short;
	int Temp_int,year,month,day,hour,minute,second,DayofYear_short;
	UCHAR Temp_UCHAR;
	UINT Temp_UINT;

if(m_BOOLSetStatus==FALSE)
{
		m_nTimeData = new SYSTEMTIME;
	::GetLocalTime(m_nTimeData);
	CString str_time = "";
    str_time.Format("%4d-%2d-%2d-%2d-%2d",m_nTimeData->wYear,m_nTimeData->wMonth,m_nTimeData->wDay,m_nTimeData->wHour,m_nTimeData->wMinute);

	 
	 if(ENTimer==0)
	 {
//		 MessageBox(str_time);	 
		 SetTimer(1,1000,NULL);
	 }
	 
	 ENTimer=1;
}


if(Function_ID==IDC_BUTTON_TIMESET_FETCH)
{	

		Temp_UCHAR=ValidData[4];
		Temp_short =ValidData[5];
		Temp_short =Temp_short<<8;
		Temp_short+=Temp_UCHAR;


//////////////////////////////////////////////////////////////////////////
//     计算  年   月   日
//////////////////////////////////////////////////////////////////////////
//Temp_short=0;

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
		m_nData.SetDate(year,month,day);

//////////////////////////////////////////////////////////////////////////
//     计算   时 分  秒
//////////////////////////////////////////////////////////////////////////
		Temp_UCHAR=ValidData[8];
		Temp_short =ValidData[9];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR;  
		Temp_UINT =Temp_short;
		Temp_UINT =Temp_UINT<<16;
		Temp_UCHAR=ValidData[6];
		Temp_short =ValidData[7];
		Temp_short=Temp_short<<8;
		Temp_short+=Temp_UCHAR; 
		Temp_UINT +=Temp_short;              //ms

//////////////////////////////////////////////////////////////////////////
//       hour  minute second
//////////////////////////////////////////////////////////////////////////
//Temp_UINT=0;

		Temp_int =Temp_UINT;
		hour =Temp_int/3600000;
		Temp_int =Temp_UINT %3600000;
		minute =Temp_int/60000;
		Temp_int =Temp_int %60000;
		second =Temp_int/1000;

		m_nTime.SetTime(hour,minute,second);

}
	//MessageBox("DoDataExchange");
Function_ID =NULL;
}


BEGIN_MESSAGE_MAP(Dlg_TimeSet, CDialog)
	//{{AFX_MSG_MAP(Dlg_TimeSet)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_SET, OnCheckSet)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_TIME, OnDatetimechangeDatetimepickerTime)
	ON_BN_CLICKED(IDC_BUTTON_TIMESET_APPLY, OnButtonTimesetApply)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATA, OnDatetimechangeDatetimepickerData)
	ON_BN_CLICKED(IDC_BUTTON_TIMESET_FETCH, OnButtonTimesetFetch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_TimeSet message handlers

//DEL void Dlg_TimeSet::OnCloseupDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult) 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	SYSTEMTIME *time1;
//DEL 	::GetLocalTime(time1);
//DEL 	if(0==((CComboBox *)GetDlgItem(IDC_DATETIMEPICKER_TIME)->SetTime(time1)))
//DEL 		MessageBox("time setting error!");
//DEL 	UpdateData(true);
//DEL 	*pResult = 0;
//DEL }

void Dlg_TimeSet::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	

	if(nIDEvent==1)
	{
		m_nData.SetDate(m_nTimeData->wYear,m_nTimeData->wMonth,m_nTimeData->wDay);        //设置时间。取系统时间
		m_nTime.SetTime(m_nTimeData->wHour,m_nTimeData->wMinute,m_nTimeData->wSecond);    //设置时间。取系统时间
//	m_nMS=m_nTimeData->wMilliseconds;
		UpdateData(FALSE);
	}
	if(nIDEvent==IDC_BUTTON_TIMESET_FETCH)
	{
		KillTimer(IDC_BUTTON_TIMESET_FETCH);
UpdateData(TRUE);
UpdateData(FALSE);
		
//		UpdateData(FALSE);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void Dlg_TimeSet::OnCheckSet() 
{
	// TODO: Add your control notification handler code here
///////复选框功能实现程序：选择不取系统时间，不选取系统时间////////////	
	if(FALSE==m_BOOLSetStatus)
	{
		KillTimer(1);
	//	MessageBox("FALSE");
	}
	else
	{
	//	MessageBox("ture");
		SetTimer(1,1000,NULL);
	}
	m_BOOLSetStatus ^=TRUE;
//////////////////////////////////////////////////////////////////////
	





}

void Dlg_TimeSet::OnDatetimechangeDatetimepickerTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	 MessageBox("SS");
	if(0==UpdateData(TRUE))
		MessageBox("error!");
	//MessageBox("updatedata successful");

	*pResult = 0;
}

void Dlg_TimeSet::OnButtonTimesetApply() 
{
	// TODO: Add your control notification handler code here
//	CString NEWTIME="";
//	CString NEWDATA="";
//	CString NEWDATATIME ="";
//	NEWDATA.Format("new data:%4d-%2d-%2d",m_nData.GetYear(),m_nData.GetMonth(),m_nData.GetDay());
//	NEWTIME.Format("new time:%2d-%2d-%2d",m_nTime.GetHour(),m_nTime.GetMinute(),m_nTime.GetSecond());
//	NEWDATATIME = NEWDATA;
//	NEWDATATIME +="\n";
//	NEWDATATIME +=NEWTIME;
//	MessageBox(NEWDATATIME);

//////////////////////////////////////////////////////////////////////////
//         start   
//
//     注意； 1984.1.1按照第1天计算的;;;
//////////////////////////////////////////////////////////////////////////

	Function_ID=IDC_BUTTON_TIMESET_APPLY;

//	UINT Temp_UINT;
	int  Temp_int,year, month, day, hour,minute,second,Temp_days, Temp_ms;
	UCHAR Temp_UCHAR, DATA[10];
	unsigned short Temp_short;

	year =m_nData.GetYear();
	month =m_nData.GetMonth();
	day =m_nData.GetDay();
	hour =m_nTime.GetHour();
	minute =m_nTime.GetMinute();
	second=m_nTime.GetSecond();

	Temp_UCHAR=0;
	Temp_days=0;
	for(int tt=1984;tt<year;tt++)
	{
//		MessageBox("1984");
		if((tt%4==0 &&tt%100 !=0)|| (tt%400==0))
			Temp_UCHAR++;
		Temp_days +=365;
	}
	Temp_days +=Temp_UCHAR;        
	for(int mm=1;mm<month;mm++)
	{
		if(mm==1 || mm==3 ||mm==5 ||mm==7 ||mm==8 ||mm==10 ||mm==12)
			Temp_days +=31;
		if(mm==4 ||mm==6 ||mm==9 ||mm==11)
			Temp_days +=30;
		if(mm==2)
			Temp_days +=28;	
	}
	if(((year%4==0 &&year%100!=0)||(year%400==0))&&mm>2)
			Temp_days ++;	
		Temp_days +=day;            //the number of days from 1984.1.1

		Temp_short=Temp_days;
		DATA[0] =0xff&Temp_short;
		DATA[1]=Temp_short>>8;

		Temp_ms=0;
		Temp_ms +=second;
		Temp_int =minute *60;
		Temp_ms += Temp_int;
		Temp_int= hour *3600;
		Temp_ms +=Temp_int;
		Temp_int =Temp_ms;
		Temp_ms =Temp_int*1000;               //ms
		Temp_int=Temp_ms;

		Temp_short =Temp_int &0xffff;
		DATA[2] =0xff&Temp_short;
		DATA[3]=Temp_short>>8;
		Temp_short =Temp_int>>16;
		DATA[4] =0xff&Temp_short;
		DATA[5]=Temp_short>>8;

if(m_BOOLSetStatus==TRUE)
{		
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_TIMESET_APPLY;

	pParent->TimeSet_block_28.Station_adr=0;
	pParent->TimeSet_block_28.Telegram_Nr=28;
	pParent->TimeSet_block_28.F1_field=0;
	pParent->TimeSet_block_28.F2_field=0x80;

	Temp_UCHAR=0;
	for(int jj=0;jj<6;jj++)
	{
		pParent->Connect_Telegram.ValidDataToPack[jj]=DATA[jj];
		if (DATA[jj]==0)
			Temp_UCHAR++;		
	}
	pParent->Connect_Telegram.ValidDataToPack[jj]=0;
	pParent->Connect_Telegram.PACK_SELECT=TRUE;
	pParent->Fun_Connect(pParent->TimeSet_block_28,Temp_UCHAR);
}	


//////////////////////////////////////////////////////////////////////////
//          end
//////////////////////////////////////////////////////////////////////////
}

void Dlg_TimeSet::OnDatetimechangeDatetimepickerData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(0==UpdateData(TRUE))
		MessageBox("error!");
	*pResult = 0;
}


void Dlg_TimeSet::OnButtonTimesetFetch() 
{
	// TODO: Add your control notification handler code here
//	CString MS;
//	MS.Format("%ld",m_nTimeData->wMilliseconds);
//	MessageBox(MS);
	Function_ID=IDC_BUTTON_TIMESET_FETCH;

if(m_BOOLSetStatus==TRUE)
{		
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_TIMESET_FETCH;

	pParent->TimeSet_block_29.Station_adr=0;
	pParent->TimeSet_block_29.Telegram_Nr=29;
	pParent->TimeSet_block_29.F1_field=0;
	pParent->TimeSet_block_29.F2_field=0x80;
	pParent->TimeSet_block_29.Data=(UCHAR*)"";
	pParent->Fun_Connect(pParent->TimeSet_block_29,0);

	SetTimer(IDC_BUTTON_TIMESET_FETCH,666,NULL);
}	


}
