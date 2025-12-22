// Dlg_ZJM.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_ZJM.h"

#include "Dlg_TQCS1.h"
#include "Dlg_TimeSet.h"
#include "Dlg_AD1.h"
//#include "Dlg_Channel.h"
#include "Dlg_Message.h"
#include "Dlg_ADAdjust1.h"
#include "Dlg_TQML.h"
#include "Dlg_ComSet.h"

//#include <CFileDialog.h>

//#include "TeleProcess.h"

#include "new1Dlg.h"
//#include "CListView1.h"
#include <string.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//#define 57.74 57.74
/////////////////////////////////////////////////////////////////////////////
// Dlg_ZJM dialog


Dlg_ZJM::Dlg_ZJM(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_ZJM::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_ZJM)
	m_boolZJM_Line1 = FALSE;
	m_boolZJM_Line2 = FALSE;
	m_boolZJM_DC = FALSE;

	
//	pParent->DC_V_I_select[0]="0";
//	pParent->DC_V_I_select[1]=0??
//	pParent->DC_V_I_select[2]=0??
//	pParent->DC_V_I_select[3]=0??
	

	FETCH_REFRESH=0;
	for(int j=0;j<280;j++)
	ADCacul_ValidData[j]=0;
//	pParent->
//	SentData(TX)
	//}}AFX_DATA_INIT

}


void Dlg_ZJM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(Dlg_ZJM)
	DDX_Control(pDX, IDC_LIST_ZJM_MsgList, m_clistctrlMsgList);
	DDX_Control(pDX, IDC_LIST_ZJM_ADCacul, m_clistctrlADCacul);
	DDX_Check(pDX, IDC_CHECK_ZJM_LINE1, m_boolZJM_Line1);
	DDX_Check(pDX, IDC_CHECK_ZJM_LINE2, m_boolZJM_Line2);
	DDX_Check(pDX, IDC_CHECK_ZJM_DC, m_boolZJM_DC);
//	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlCOM);
	//}}AFX_DATA_MAP



	CNew1Dlg * pParent=(CNew1Dlg *)GetParent();


	m_clistctrlADCacul.DeleteAllItems();
	m_clistctrlMsgList.DeleteAllItems();


//////////////////////////////////////////////////////////////////////////
//     initialization of  ACAD Calculate
//////////////////////////////////////////////////////////////////////////



	int  nListCount_AD=m_clistctrlADCacul.GetItemCount();   
	CString str_Item[14],str_DCItem[12],str_Channel[3],str_Count[14],str_Second[14],str_Percent[14],CHN;
	UCHAR TempData_UCHAR;
	unsigned short TempData_short;
	UINT  TempData_int;
	float TempData_float ,T_float;
	char TempBuffer[10],TempBuffer2[10],Per_TempBuffer[10],Cnt_TempBuffer[10],Per_TempBuffer2[10];
	str_Item[0]="Ua";str_Item[1]="Ub"; str_Item[2]="Uc";str_Item[3]="Uab"; str_Item[4]="Ubc";str_Item[5]="Uca";
	str_Item[6]="Ia";str_Item[7]="Ib";str_Item[8]="Ic";str_Item[9]="P";str_Item[10]="Q";str_Item[11]="S";
	str_Item[12]="f";str_Item[13]="Cos phi";

	str_DCItem[0]="DC1";str_DCItem[1]="DC2";str_DCItem[2]="DC3";str_DCItem[3]="DC4";str_DCItem[4]="DC5";str_DCItem[5]="DC6";str_DCItem[6]="DC7";str_DCItem[7]="DC8";str_DCItem[8]="DC9";str_DCItem[9]="DC10";str_DCItem[10]="DC11";str_DCItem[11]="DC12";

	str_Channel[0]="Line1";str_Channel[1]="Line2";str_Channel[2]="DC";



	//ADCacul_ValidData[20]=0X00;
	//ADCacul_ValidData[21]=0X20;
/*
	pParent->Current_Style=(UINT)(pParent->ZJM_dlg.AD1_dlg.ValidData[55]);
	pParent->DC_V_I_select[0]=(UINT)(pParent->ZJM_dlg.AD1_dlg.ValidData[57]);
	pParent->DC_V_I_select[1]=(UINT)(pParent->ZJM_dlg.AD1_dlg.ValidData[58]);
	pParent->DC_V_I_select[2]=(UINT)(pParent->ZJM_dlg.AD1_dlg.ValidData[59]);
	pParent->DC_V_I_select[3]=(UINT)(pParent->ZJM_dlg.AD1_dlg.ValidData[60]);
*/
	for(int ii=0; ii<3; ii++)
	{
		CHN =str_Channel[ii];

		for(int j=0;j<14;j++)
		{
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                      line 1		
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

			if(ii==0 && m_boolZJM_Line1==TRUE)
			 {
				 TempData_UCHAR =ADCacul_ValidData[20+8+2*j];
				 TempData_short=ADCacul_ValidData[21+8+2*j];
				 TempData_short = TempData_short<<8;
				 TempData_short+=TempData_UCHAR;                     //???16¦Ë??
			//	 TempData_short1=TempData_short;
				 TempData_int = TempData_short *10000;
			//	 TempData_int1=TempData_int;
				 TempData_int = TempData_int/pParent->DIM_public;                   // ??
				 TempData_float =TempData_short;
				 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
			//	 TempData_float1=TempData_float;


	//////////////////////////////////////////////////////////////////////////
	//          Count
	//////////////////////////////////////////////////////////////////////////

				// TempData_short =TempData_short1;
				 _itoa(TempData_short,Cnt_TempBuffer,10);              // count
				 str_Count[j]= Cnt_TempBuffer;
	//MessageBox(str_Count[j]);



	//////////////////////////////////////////////////////////////////////////
	//      %
	//////////////////////////////////////////////////////////////////////////
				 UINT aaa;
				 CString str;
				 char bf[10];
				 char bf2[20];
				 float bbb;
				 bf2[0]=0;
				 bf2[1]=0;
				 if(j==9||j==10)              // /P Q S
				 {
					if(TempData_short>32767)
					{
						bf2[0]='-';
						TempData_short ^=0xffff;
						TempData_short++;
					}
					TempData_int = TempData_short *10000;
				
					TempData_int = TempData_int/pParent->DIM_public;                   // ??
					TempData_float =TempData_short;
					TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
				 }
				 if(j==13)
				 {
					
					 if(TempData_short>32767)
					 {
					     bf2[0]='-';
					//	 TempData_short-=32768;
						 TempData_short ^=0xffff;
						 TempData_short++;
						 TempData_int = TempData_short *10000;
					//	 TempData_int1=TempData_int;
						 TempData_int = TempData_int/pParent->DIM_public;                   // ??
						 TempData_float =TempData_short;
						 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
					 }
				 }
				 aaa= TempData_float*100;
				 _itoa(aaa,Per_TempBuffer,10);                  // %
				 str =Per_TempBuffer;
				 Per_TempBuffer[str.GetLength()]='.';
				 Per_TempBuffer[str.GetLength()+1]=0;
				 bbb= TempData_float*100-aaa;
				 bbb+=1;
				 bbb*=10000;
				 aaa=bbb;
				 _itoa(aaa,bf,10);                  // %	 
				 for(int mm=0;mm<10;mm++)
					 bf[mm]=bf[mm+1];
				 str =bf;
    			 bf[str.GetLength()]='%';
    	 		 bf[str.GetLength()+1]=0;

				
				 
				 strcat(Per_TempBuffer,bf);
				 strcat(bf2,Per_TempBuffer);
				 str_Percent[j]=bf2;
	//MessageBox(str_Second[j]);

	//////////////////////////////////////////////////////////////////////////
	//          Second
	//////////////////////////////////////////////////////////////////////////
				//	TempData_float=TempData_float1;

				 if(j==0 || j==1 || j==2 )      //when the parameter is phase voltage 
				 {
					 TempData_float = TempData_float * (float)57.74;
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int ;
					 T_float=(TempData_float+1)*1000;
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='V';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
	//MessageBox(str_Second[j]);
				 }
				 else if(j==3 ||j==4|| j==5)      //when the parameter is Line voltage
				 {   
					if(pParent->DIM_Line_Vot_style==1)
					 {
					  TempData_float = TempData_float * (float)57.74;
					 }
					 else
					 {
                      TempData_float = TempData_float * (float)100.00;
					 }


					 //TempData_float = TempData_float * (float)100.00;
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int ;
					 T_float=(TempData_float+1)*1000;
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='V';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
	//MessageBox(str_Second[j]);
				 }
				 else if(j==6 || j==7 ||j==8)           //when the parameter is current
				 {
					 
						 if(pParent->Current_Style==0)           //5A
						 {
							 TempData_float *=(float)5;
						 }
						 else if(pParent->Current_Style==1)      //1A
						 { 
							 TempData_float *=(float)1;
						 }
						 else									//1A
						 { 
							 TempData_float *=(float)1;
						 }
						 T_float =TempData_float;
						 TempData_int = (UINT)T_float;
						 _itoa(TempData_int,TempBuffer,10);				 
						 TempBuffer2[0]='.';
						 TempBuffer2[1]='\0';
						 strcat(TempBuffer,TempBuffer2);
						 TempData_float -=TempData_int;
						 T_float=(TempData_float+1)*10000;
						 TempData_int =(UINT)T_float;
						 _itoa(TempData_int,TempBuffer2,10);
						 for(int mm=0;mm<10;mm++)
							TempBuffer2[mm]=TempBuffer2[mm+1];
						 strcat(TempBuffer,TempBuffer2);
						 TempBuffer2[0]='A';
						 TempBuffer2[1]='\0';
						 strcat(TempBuffer,TempBuffer2);
						 str_Second[j]=TempBuffer;
					
					 
	//MessageBox(str_Second[j]);
				 }
				 else if(j==9||j==10||j==11)       //P Q S
				 {
					 TempData_UCHAR =ADCacul_ValidData[20+8+2*j];
					 TempData_short=ADCacul_ValidData[21+8+2*j];
					 TempData_short = TempData_short<<8;
					 TempData_short+=TempData_UCHAR;                     //???16¦Ë??
					 TempData_int = TempData_short *10000;
				//	 TempData_int1=TempData_int;
					 TempData_int = TempData_int/pParent->DIM_public;                   // ??
					 TempData_float =TempData_short;
					 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
   
					 if(((j==9||j==10)&&(TempData_short<32768))||(j==11))
					 {
						 if(pParent->Current_Style==0)           //5A
						 {
							 TempData_float *=(float)865.5;
						 }
						 else if(pParent->Current_Style==1)      //1A
						 { 
							 TempData_float *=(float) 173.1;
						 }
						  else									//1A
						 { 
							 TempData_float *=(float) 173.1;
						 }

						 T_float =TempData_float;
						 TempData_int = (UINT)T_float;
						 _itoa(TempData_int,TempBuffer,10);				 
						 TempBuffer2[0]='.';
						 TempBuffer2[1]='\0';
						 strcat(TempBuffer,TempBuffer2);
						 TempData_float -=TempData_int;
						 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
						 TempData_int =(UINT)T_float;
						 _itoa(TempData_int,TempBuffer2,10);
						 for(int mm=0;mm<10;mm++)
							TempBuffer2[mm]=TempBuffer2[mm+1];
						 strcat(TempBuffer,TempBuffer2);
						 if(j==9)
						 {
							 TempBuffer2[0]='W';
							 TempBuffer2[1]='\0';
						 }
						 else if(j==10)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='a';
							 TempBuffer2[2]='r';
							 TempBuffer2[3]='\0';

						 }
						 else if(j==11)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='A';
							 TempBuffer2[2]='\0';
						 }

						 strcat(TempBuffer,TempBuffer2);
						 str_Second[j]=TempBuffer;
					}
				else if((j==9||j==10)&&(TempData_short>32767))
					 {
						char bf1[20];
					//	 TempData_short-=32768;
						 TempData_short ^=0xffff;
						 TempData_short++;
						 TempData_int = TempData_short *10000;
					//	 TempData_int1=TempData_int;
						 TempData_int = TempData_int/pParent->DIM_public;                   // ??
						 TempData_float =TempData_short;
						 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi

						 if(pParent->Current_Style==0)           //5A
						 {
							 TempData_float *=(float)865.5;
						 }
						 else if(pParent->Current_Style==1)      //1A
						 { 
							 TempData_float *=(float) 173.1;
						 }
						 else								     //1A
						 { 
							 TempData_float *=(float) 173.1;
						 }
						 T_float =TempData_float;
						 TempData_int = (UINT)T_float;
						 _itoa(TempData_int,TempBuffer,10);				 
						 TempBuffer2[0]='.';
						 TempBuffer2[1]='\0';
						 strcat(TempBuffer,TempBuffer2);
						 TempData_float -=TempData_int;
						 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
						 TempData_int =(UINT)T_float;
						 _itoa(TempData_int,TempBuffer2,10);
						 for(int mm=0;mm<10;mm++)
							TempBuffer2[mm]=TempBuffer2[mm+1];
						 strcat(TempBuffer,TempBuffer2);
						 if(j==9)
						 {
							 TempBuffer2[0]='W';
							 TempBuffer2[1]='\0';
						 }
						 else if(j==10)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='a';
							 TempBuffer2[2]='r';
							 TempBuffer2[3]='\0';

						 }
						 else if(j==11)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='A';
							 TempBuffer2[2]='\0';
						 }

						 strcat(TempBuffer,TempBuffer2);
						 bf1[0]='-';
						 bf1[1]=0;
						 strcat(bf1,TempBuffer);
						 str_Second[j]=bf1;
					}
				 }

				 else if(j==12)       //Hz
				 {

					 TempData_float *=(float)50;
					
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);				 
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int;
					 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='H';
					 TempBuffer2[1]='z';
					 TempBuffer2[2]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
				 } 
				 
				 else if(j==13)       //Cos phi
				 {
					char bf4[20];
					bf4[0]=bf4[1]=0;
					 TempData_UCHAR =ADCacul_ValidData[20+8+2*j];
					 TempData_short=ADCacul_ValidData[21+8+2*j];
					 TempData_short = TempData_short<<8;
					 TempData_short+=TempData_UCHAR;                     //???16¦Ë??
					 TempData_int = TempData_short *10000;
				//	 TempData_int1=TempData_int;
					 TempData_int = TempData_int/pParent->DIM_public;                   // ??
					 TempData_float =TempData_short;
					 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi

					 if(TempData_short>32767)
					 {
					     bf4[0]='-';
					//	 TempData_short-=32768;
						 TempData_short ^=0xffff;
						 TempData_short++;
						 TempData_int = TempData_short *10000;
					//	 TempData_int1=TempData_int;
						 TempData_int = TempData_int/pParent->DIM_public;                   // ??
						 TempData_float =TempData_short;
						 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
					 }
					 TempData_float *=(float)1;
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);				 
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int;
					 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 strcat(bf4,TempBuffer);
					 str_Second[j]=bf4;
				 }

//m_clistctrlADCacul.SetTextBkColor(255);

				 m_clistctrlADCacul.InsertItem(nListCount_AD,CHN);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,1,str_Item[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,2,str_Second[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,3,str_Percent[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,4,str_Count[j]); 
				 nListCount_AD++;
				 str_Count[j]=str_Percent[j]=str_Second[j]="";
			 }

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//                  line  2
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


		 else if(ii==1 && m_boolZJM_Line2==TRUE)                                     //Line2
			 {

				 TempData_UCHAR =ADCacul_ValidData[48+8+2*j];
				 TempData_short=ADCacul_ValidData[49+8+2*j];
				 TempData_short = TempData_short<<8;
				 TempData_short+=TempData_UCHAR;                     //???16¦Ë??
			//	 TempData_short1=TempData_short;
				 TempData_int = TempData_short *10000;
			//	 TempData_int1=TempData_int;
				 TempData_int = TempData_int/pParent->DIM_public;                   // ??
				 TempData_float =TempData_short;
				 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
			//	 TempData_float1=TempData_float;
	//////////////////////////////////////////////////////////////////////////
	//          Count
	//////////////////////////////////////////////////////////////////////////

				// TempData_short =TempData_short1;
				 _itoa(TempData_short,Cnt_TempBuffer,10);              // count
				 str_Count[j]= Cnt_TempBuffer;
	//MessageBox(str_Count[j]);


	//////////////////////////////////////////////////////////////////////////
	//      %
	//////////////////////////////////////////////////////////////////////////

/*				 UINT aaa;
				 CString str;
				 char bf[10];
				 float bbb;

				 aaa= TempData_float*100;
				 _itoa(aaa,Per_TempBuffer,10);                  // %
				 str =Per_TempBuffer;
				 Per_TempBuffer[str.GetLength()]='.';
				 Per_TempBuffer[str.GetLength()+1]=0;
				 bbb= TempData_float*100-aaa;
				 bbb*=10000;
				 aaa=bbb;
				 _itoa(aaa,bf,10);                  // %
				 str =bf;
				 bf[str.GetLength()]='%';
				 bf[str.GetLength()+1]=0;
				 strcat(Per_TempBuffer,bf);
				 str_Percent[j]=Per_TempBuffer;
	//MessageBox(str_Second[j]);
	*/
				 UINT aaa;
				 CString str;
				 char bf[10];
				 char bf2[20];
				 float bbb;
				 bf2[0]=0;
				 bf2[1]=0;
				 if(j==9||j==10)              // /P Q S
				 {
					if(TempData_short>32767)
					{
						bf2[0]='-';
						TempData_short ^=0xffff;
						TempData_short++;
					}
					TempData_int = TempData_short *10000;
				
					TempData_int = TempData_int/pParent->DIM_public;                   // ??
					TempData_float =TempData_short;
					TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
				 }
				 if(j==13)
				 {
					
					 if(TempData_short>32767)
					 {
					     bf2[0]='-';
					//	 TempData_short-=32768;
						 TempData_short ^=0xffff;
						 TempData_short++;
						 TempData_int = TempData_short *10000;
					//	 TempData_int1=TempData_int;
						 TempData_int = TempData_int/pParent->DIM_public;                   // ??
						 TempData_float =TempData_short;
						 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
					 }
				 }
				 aaa= TempData_float*100;
				 _itoa(aaa,Per_TempBuffer,10);                  // %
				 str =Per_TempBuffer;
				 Per_TempBuffer[str.GetLength()]='.';
				 Per_TempBuffer[str.GetLength()+1]=0;
				 bbb= TempData_float*100-aaa;
				 bbb+=1;
				 bbb*=10000;
				 
				 aaa=bbb;
				 _itoa(aaa,bf,10);                  // %
				 for(int mm=0;mm<10;mm++)
					 bf[mm]=bf[mm+1];
				 str =bf;
				 bf[str.GetLength()]='%';
				 bf[str.GetLength()+1]=0;
				 bf[str.GetLength()+2]=0;
				 strcat(Per_TempBuffer,bf);
				 strcat(bf2,Per_TempBuffer);
				 str_Percent[j]=bf2;




	//////////////////////////////////////////////////////////////////////////
	//          Second
	//////////////////////////////////////////////////////////////////////////
				//	TempData_float=TempData_float1;

				 if(j==0 || j==1 || j==2 )      //when the parameter is voltage
				 {
					 TempData_float = TempData_float * (float)57.74;
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int ;
					 T_float=(TempData_float+1)*1000;
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='V';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
	//MessageBox(str_Second[j]);
				 }
				 else if(j==3 ||j==4|| j==5)      //when the parameter is voltage
				 {
					 if(pParent->DIM_Line_Vot_style==1)
					 {
					  TempData_float = TempData_float * (float)57.74;
					 }
					 else
					 {
                      TempData_float = TempData_float * (float)100.00;
					 }
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int ;
					 T_float=(TempData_float+1)*1000;
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='V';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
				 }
				 else if(j==6 || j==7 ||j==8)
				 {
					 if(pParent->Current_Style==0)           //5A
					 {
						 TempData_float *=(float)5;
					 }
					 else if(pParent->Current_Style==1)      //1A
					 { 
						 TempData_float *=(float)1;
					 }
					 else								     //1A
					 { 
						 TempData_float *=(float)1;
					 }
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);				 
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int;
					 T_float=(TempData_float+1)*10000;
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='A';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
	//MessageBox(str_Second[j]);
				 }



				 else if(j==9||j==10||j==11)       //P Q S
				 {
					 TempData_UCHAR =ADCacul_ValidData[48+8+2*j];
					 TempData_short=ADCacul_ValidData[49+8+2*j];
					 TempData_short = TempData_short<<8;
					 TempData_short+=TempData_UCHAR;                     //???16¦Ë??
					 TempData_int = TempData_short *10000;
				//	 TempData_int1=TempData_int;
					 TempData_int = TempData_int/pParent->DIM_public;                   // ??
					 TempData_float =TempData_short;
					 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi

					 
					 if(((j==9||j==10)&&(TempData_short<32768))||(j==11))
					 {
						 if(pParent->Current_Style==0)           //5A
						 {
							 TempData_float *=(float)865.5;
						 }
						 else if(pParent->Current_Style==1)      //1A
						 { 
							 TempData_float *=(float) 173.1;
						 }
						 else  //1A
						 { 
							 TempData_float *=(float) 173.1;
						 }

						 T_float =TempData_float;
						 TempData_int = (UINT)T_float;
						 _itoa(TempData_int,TempBuffer,10);				 
						 TempBuffer2[0]='.';
						 TempBuffer2[1]='\0';
						 strcat(TempBuffer,TempBuffer2);
						 TempData_float -=TempData_int;
						 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
						 TempData_int =(UINT)T_float;
						 _itoa(TempData_int,TempBuffer2,10);
						 for(int mm=0;mm<10;mm++)
							TempBuffer2[mm]=TempBuffer2[mm+1];
						 strcat(TempBuffer,TempBuffer2);
						 if(j==9)
						 {
							 TempBuffer2[0]='W';
							 TempBuffer2[1]='\0';
						 }
						 else if(j==10)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='a';
							 TempBuffer2[2]='r';
							 TempBuffer2[3]='\0';

						 }
						 else if(j==11)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='A';
							 TempBuffer2[2]='\0';
						 }

						 strcat(TempBuffer,TempBuffer2);
						 str_Second[j]=TempBuffer;
					}
				else if((j==9||j==10)&&(TempData_short>32767))
					 {
						char bf1[20];
					//	 TempData_short-=32768;
						 TempData_short ^=0xffff;
						 TempData_short++;
						 TempData_int = TempData_short *10000;
					//	 TempData_int1=TempData_int;
						 TempData_int = TempData_int/pParent->DIM_public;                   // ??
						 TempData_float =TempData_short;
						 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi

						 if(pParent->Current_Style==0)           //5A
						 {
							 TempData_float *=(float)865.5;
						 }
						 else if(pParent->Current_Style==1)      //1A
						 { 
							 TempData_float *=(float) 173.1;
						 }
						 else								    //1A
						 { 
							 TempData_float *=(float) 173.1;
						 }
						 T_float =TempData_float;
						 TempData_int = (UINT)T_float;
						 _itoa(TempData_int,TempBuffer,10);				 
						 TempBuffer2[0]='.';
						 TempBuffer2[1]='\0';
						 strcat(TempBuffer,TempBuffer2);
						 TempData_float -=TempData_int;
						 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
						 TempData_int =(UINT)T_float;
						 _itoa(TempData_int,TempBuffer2,10);
						 for(int mm=0;mm<10;mm++)
							 TempBuffer2[mm]=TempBuffer2[mm+1];
						 strcat(TempBuffer,TempBuffer2);
						 if(j==9)
						 {
							 TempBuffer2[0]='W';
							 TempBuffer2[1]='\0';
						 }
						 else if(j==10)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='a';
							 TempBuffer2[2]='r';
							 TempBuffer2[3]='\0';

						 }
						 else if(j==11)
						 {
							 TempBuffer2[0]='V';
							 TempBuffer2[1]='A';
							 TempBuffer2[2]='\0';
						 }

						 strcat(TempBuffer,TempBuffer2);
						 bf1[0]='-';
						 bf1[1]=0;
						 strcat(bf1,TempBuffer);
						 str_Second[j]=bf1;
					}
				 }


				 else if(j==12)       //Hz
				 {

					 TempData_float *=(float)50;
					
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);				 
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int;
					 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='H';
					 TempBuffer2[1]='z';
					 TempBuffer2[2]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
				 } 
				 


				  else if(j==13)       //Cos phi
				 {
					char bf4[20];
					bf4[0]=bf4[1]=0;
					TempData_UCHAR =ADCacul_ValidData[48+8+2*j];
					 TempData_short=ADCacul_ValidData[49+8+2*j];
					 TempData_short = TempData_short<<8;
					 TempData_short+=TempData_UCHAR;                     //???16¦Ë??
					 TempData_int = TempData_short *10000;
				//	 TempData_int1=TempData_int;
					 TempData_int = TempData_int/pParent->DIM_public;                   // ??
					 TempData_float =TempData_short;
					 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi

					 if(TempData_short>32767)
					 {
					     bf4[0]='-';
					//	 TempData_short-=32768;
						 TempData_short ^=0xffff;
						 TempData_short++;
						 TempData_int = TempData_short *10000;
					//	 TempData_int1=TempData_int;
						 TempData_int = TempData_int/pParent->DIM_public;                   // ??
						 TempData_float =TempData_short;
						 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
					 }
					 TempData_float *=(float)1;
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);				 
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int;
					 T_float=(TempData_float+1)*10000;                     //????4 ¦Ë§³??
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 strcat(bf4,TempBuffer);
					 str_Second[j]=bf4;
				 }

				 m_clistctrlADCacul.InsertItem(nListCount_AD,CHN);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,1,str_Item[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,2,str_Second[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,3,str_Percent[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,4,str_Count[j]); 
				 nListCount_AD++;
				 str_Count[j]=str_Percent[j]=str_Second[j]="";
			 }




			 
//////////////////////////////////////////////////////////////////////////
//
//                    dc
//////////////////////////////////////////////////////////////////////////

		else if(ii==2 && m_boolZJM_DC==TRUE && j<12)                                     //DC
	//  else if(ii==2 && m_boolZJM_DC==TRUE && j<4) 
			 {


				 TempData_UCHAR =ADCacul_ValidData[4+2*j];
				 TempData_short=ADCacul_ValidData[5+2*j];
				 TempData_short = TempData_short<<8;
				 TempData_short+=TempData_UCHAR;                     //???16¦Ë??
			//	 TempData_short1=TempData_short;
				 TempData_int = TempData_short *10000;
			//	 TempData_int1=TempData_int;
				 TempData_int = TempData_int/pParent->DIM_public;                   // ??
				 TempData_float =TempData_short;
				 TempData_float =TempData_float/pParent->DIM_public;                // shi ji zhi
			//	 TempData_float1=TempData_float;


	//////////////////////////////////////////////////////////////////////////
	//      %
	//////////////////////////////////////////////////////////////////////////
				 UINT aaa;
				 CString str;
				 char bf[10];
				 char bf5[10];
				 float bbb;
				// float ccc;

                // float TempData_float=1.0001;
     			 aaa= TempData_float*100;
				 _itoa(aaa,Per_TempBuffer,10);                  // %
				 str =Per_TempBuffer;
				 Per_TempBuffer[str.GetLength()]='.';
//20240529	yuanshi			 Per_TempBuffer[str.GetLength()+1]=0;{
				 Per_TempBuffer[str.GetLength()+1]='\0';
             


				 bbb= TempData_float*100-aaa;
				 bbb=(bbb+1)*10000;
				 //ccc=(float)aaa+bbb;
				 aaa=bbb;
				 _itoa(aaa,bf,10);                 // %
				 for(int mn=0;mn<10;mn++)
						 bf[mn]=bf[mn+1];
				 //strcat(Per_TempBuffer,bf);
				 str =bf;
				 bf[str.GetLength()]='%';
//20240529	yuanshi			 bf[str.GetLength()+1]=0;
                 bf[str.GetLength()+1]='\0';
//20240529	yuanshi			 Per_TempBuffer[str.GetLength()+1]=0;}
				 strcat(Per_TempBuffer,bf);
				 str_Percent[j]=Per_TempBuffer;
	//MessageBox(str_Second[j]);

	//////////////////////////////////////////////////////////////////////////
	//          Count
	//////////////////////////////////////////////////////////////////////////

				// TempData_short =TempData_short1;
				 char Cnt_TempBuffer2[10];
				 _itoa(TempData_short,Cnt_TempBuffer,10);              // count
				 str_Count[j]= Cnt_TempBuffer;
	//			 str_Count[j]= Cnt_TempBuffer;
	//MessageBox(str_Count[j]);
	/////////////////////////////////////////////////////////////////////////
    //    second
	//////////////////////////////////////////////////////////////////////////
		/*20240618shy		  if(pParent->DC_V_I_select[j]==1)
					 TempData_float = TempData_float * (float)10;	 
				  else 
                     TempData_float = TempData_float * (float)5;
*/
		
                  if(pParent->DC_V_I_select[j]==0)
					  TempData_float = TempData_float * (float)5;	 
				  else 
				     TempData_float = TempData_float * (float)10;


				  
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);				 
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int;
					 T_float=(TempData_float+1)*10000;
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 /*20240618shy
                     if(pParent->DC_V_I_select[j]==1)
					 {
					 
					 TempBuffer2[0]='m';
					 TempBuffer2[1]='A';
					 TempBuffer2[2]='\0';
					 }
				     else 
					 {
					 TempBuffer2[0]='V';
					 TempBuffer2[1]='\0';
					 }
					 */
                     if(pParent->DC_V_I_select[j]==0)
					 {
					 
					 TempBuffer2[0]='V';
					 TempBuffer2[1]='\0';
					 }
				     else 
					 {
					 TempBuffer2[0]='m';
					 TempBuffer2[1]='A';
					 TempBuffer2[2]='\0';
					 }

					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;
/*                 
  
 	 else if(j==6 || j==7 ||j==8)
				 {
					 if(pParent->Current_Style==0)           //5A
					 {
						 TempData_float *=(float)5;
					 }
					 else if(pParent->Current_Style==1)      //1A
					 { 
						 TempData_float *=(float)1;
					 }
					 T_float =TempData_float;
					 TempData_int = (UINT)T_float;
					 _itoa(TempData_int,TempBuffer,10);				 
					 TempBuffer2[0]='.';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 TempData_float -=TempData_int;
					 T_float=(TempData_float+1)*10000;
					 TempData_int =(UINT)T_float;
					 _itoa(TempData_int,TempBuffer2,10);
					 for(int mm=0;mm<10;mm++)
						 TempBuffer2[mm]=TempBuffer2[mm+1];
					 strcat(TempBuffer,TempBuffer2);
					 TempBuffer2[0]='A';
					 TempBuffer2[1]='\0';
					 strcat(TempBuffer,TempBuffer2);
					 str_Second[j]=TempBuffer;

*/
	//////////////////////////////////////////////////////////////////////////
	//          Second
	//////////////////////////////////////////////////////////////////////////
				//	TempData_float=TempData_float1;


		
				 m_clistctrlADCacul.InsertItem(nListCount_AD,CHN);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,1,str_DCItem[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,2,str_Second[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,3,str_Percent[j]);   
				 m_clistctrlADCacul.SetItemText(nListCount_AD,4,str_Count[j]); 
				 nListCount_AD++;
				 str_Count[j]=str_Percent[j]=str_Second[j]="";
			 }
		//	else 		
		}
	//		  m_clistctrlADCacul.InsertItem(nListCount_AD,"");   
			//  m_clistctrlADCacul.SetItemText(nListCount_AD,1,"");   
	//		  nListCount_AD++;
		
	}





//////////////////////////////////////////////////////////////////////////
//   
//         ////     //         //////
//         // //    //       //      //
//         //  //   //      //        //
//         //   //  //      ////////////
//         //    // //      //
//         //     ////       //       //
//         //      ///        /////////
//
//
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//     initialization of  MsgList
/////////////////////////////////////////////////////////////////////////
if(pParent->Down==IDC_BUTTON_ZJM_FETCH)
{
	int  nListCount_Msg=m_clistctrlMsgList.GetItemCount();
	UINT Temp_MS,Temp_UINT,ms_UINT;
	unsigned short MsgID,Temp_Date_short,Year_short,DayofYear_short,Temp_short;   //DayofYear_short:???????§Ö?????
	UCHAR Temp_UCHAR,Msg_NR,Temp_Date_UCHAR,Day_UCHAR,Month_UCHAR,Hour_UCHAR,Minute_UCHAR,Second_UCHAR;
	char Temp_String[12],Temp_String1[10];
	CString MsgID_CString,Date_CString,Time_CString,ms_CString,Event_CString;
	//MsgList_h_ValidData[13]=12;

	//////////////////////////////////////////////////////////////////////////
	//               MsgList_h_ValidData[]
	//////////////////////////////////////////////////////////////////////////

	Msg_NR =MsgList_h_ValidData[13];
	Msg_NR &=0X7F;
	//nListCount_Msg +=Msg_NR;
	//nListCount_Msg +=MsgList_ValidData[4];
	for(int k=0;k<Msg_NR;k++)
	{
		Temp_UCHAR=MsgList_h_ValidData[14+8*k];
		MsgID =MsgList_h_ValidData[15+8*k];
		MsgID = MsgID<<8;
		MsgID +=Temp_UCHAR;
		_itoa((MsgID-32768),Temp_String,10);
		MsgID_CString = Temp_String;
		m_clistctrlMsgList.InsertItem(nListCount_Msg,MsgID_CString);                              //MsgID

	//////////////////////////////////////////////////////////////////////////
	//            date
	//////////////////////////////////////////////////////////////////////////


		Temp_Date_UCHAR =MsgList_h_ValidData[16+8*k];
		Temp_Date_short =MsgList_h_ValidData[17+8*k];
		Temp_Date_short =Temp_Date_short<<8;
		Temp_Date_short +=Temp_Date_UCHAR;          //??1984.1.1??????????
		Temp_Date_short++;
		Temp_short =Temp_Date_short;
	/*	Year_short = Temp_Date_short /365;
		DayofYear_short = Temp_Date_short%365;
		Year_short +=1984;                          //year 
		for(int year=1984; year<=Year_short; year++)
		{
			if(((year%4==0)&&(year%100!=0))||(year%400==0))
			{
				if(DayofYear_short>0)
					DayofYear_short --;
				else
				{
					Year_short--;
					DayofYear_short +=365;
				}
			}
		}
	*/
		for(int year=1984; Temp_short>365; year++)
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
			Year_short =year;                                     //nian 
			Year_short--;
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
			Month_UCHAR =(UCHAR)mm;
			Day_UCHAR = (UCHAR)DayofYear_short;
		}
		else if(Temp_short>0)
		{
			Year_short =year;                                     //nian 
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
					if(DayofYear_short>28)
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
			Month_UCHAR = (UCHAR)mm;
			Day_UCHAR = (UCHAR)DayofYear_short;
		}

		_itoa(Year_short,Temp_String,10);                  //nian
		Temp_String1[0]='-';
		Temp_String1[1]='\0';
		strcat(Temp_String,Temp_String1);                  //nian -
		_itoa(Month_UCHAR,Temp_String1,10);
		if(Month_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
		strcat(Temp_String,Temp_String1);
		Temp_String1[0]='-';
		Temp_String1[1]='\0';
		strcat(Temp_String,Temp_String1);                  //nian - yue -
		_itoa(Day_UCHAR,Temp_String1,10);
		if(Day_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
		strcat(Temp_String,Temp_String1);                  //nian - yue - ri

		Date_CString =Temp_String;
		
		m_clistctrlMsgList.SetItemText(nListCount_Msg,1,Date_CString);                              //Data

	//////////////////////////////////////////////////////////////////////////
	//                Time
	//////////////////////////////////////////////////////////////////////////
	Temp_UCHAR =MsgList_h_ValidData[20+8*k];
	Temp_short =MsgList_h_ValidData[21+8*k];
	Temp_short = Temp_short<< 8;
	Temp_short +=Temp_UCHAR;
	Temp_MS =Temp_short<<16;

	Temp_UCHAR =MsgList_h_ValidData[18+8*k];
	Temp_short =MsgList_h_ValidData[19+8*k];
	Temp_short = Temp_short<< 8;
	Temp_short +=Temp_UCHAR;
	Temp_MS +=Temp_short;                                  //ms ???
	Temp_UINT =Temp_MS;

	Hour_UCHAR =(UCHAR)(Temp_MS/3600000);                //???????24 ???????????
	Temp_UINT =Temp_MS %3600000;
	Minute_UCHAR = (UCHAR)(Temp_UINT /60000);
	Temp_UINT =Temp_UINT %60000;
	Second_UCHAR =(UCHAR)(Temp_UINT/1000);
	Temp_UINT =Temp_UINT %1000;
	ms_UINT =Temp_UINT;

	_itoa(Hour_UCHAR,Temp_String,10);
	if(Hour_UCHAR<10)
	{
			Temp_String[1]=Temp_String[0];
			Temp_String[0]='0';
			Temp_String[2]='\0';
	}
	Temp_String1[0]=':';
	Temp_String1[1]='\0';
	strcat(Temp_String,Temp_String1);          //shi:
	_itoa(Minute_UCHAR,Temp_String1,10);
		if(Minute_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
	strcat(Temp_String,Temp_String1);
	Temp_String1[0]=':';
	Temp_String1[1]='\0';                  
	strcat(Temp_String,Temp_String1);          //shi : fen :
	_itoa(Second_UCHAR,Temp_String1,10);
		if(Second_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
	strcat(Temp_String,Temp_String1);          //shi : fen : miao
	Time_CString = Temp_String;
		m_clistctrlMsgList.SetItemText(nListCount_Msg,2,Time_CString);                                        //Time

	//////////////////////////////////////////////////////////////////////////
	//                             ms
	//////////////////////////////////////////////////////////////////////////
	_itoa(ms_UINT,Temp_String,10);
	ms_CString =Temp_String;

		m_clistctrlMsgList.SetItemText(nListCount_Msg,3,ms_CString);                                            //ms

	//////////////////////////////////////////////////////////////////////////
	//                          Event
	//////////////////////////////////////////////////////////////////////////
	if(MsgID>32767)
	Event_CString ="+";
	else
	Event_CString="-";
//	Event_CString-=32768;
		m_clistctrlMsgList.SetItemText(nListCount_Msg,4,Event_CString);                                         //Event
		nListCount_Msg ++;
	}








//////////////////////////////////////////////////////////////////////////
//               MsgList_ValidData[]
//////////////////////////////////////////////////////////////////////////


	for(int kk=0;kk<(MsgList_ValidData[4]-128);kk++)
	{
		Temp_UCHAR=MsgList_ValidData[5+8*kk];
		MsgID =MsgList_h_ValidData[6+8*kk];
		MsgID = MsgID<<8;
		MsgID +=Temp_UCHAR;
		_itoa((MsgID-32768),Temp_String,10);
		MsgID_CString = Temp_String;
		m_clistctrlMsgList.InsertItem(nListCount_Msg,MsgID_CString);                              //MsgID

	//////////////////////////////////////////////////////////////////////////
	//            date
	//////////////////////////////////////////////////////////////////////////


		Temp_Date_UCHAR =MsgList_h_ValidData[7+8*kk];
		Temp_Date_short =MsgList_h_ValidData[8+8*kk];
		Temp_Date_short =Temp_Date_short<<8;
		Temp_Date_short +=Temp_Date_UCHAR;          //??1984.1.1??????????
		Temp_short =Temp_Date_short;
	/*	Year_short = Temp_Date_short /365;
		DayofYear_short = Temp_Date_short%365;
		Year_short +=1984;                          //year 
		for(int year=1984; year<=Year_short; year++)
		{
			if(((year%4==0)&&(year%100!=0))||(year%400==0))
			{
				if(DayofYear_short>0)
					DayofYear_short --;
				else
				{
					Year_short--;
					DayofYear_short +=365;
				}
			}
		}
	*/
		for(int year=1984; Temp_short>365; year++)
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
			Year_short =year;                                     //nian 
			Year_short--;
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
			Month_UCHAR =(UCHAR)mm;
			Day_UCHAR = (UCHAR)DayofYear_short;
		}
		else if(Temp_short>0)
		{
			Year_short =year;                                     //nian 
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
					if(DayofYear_short>28)
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
			Month_UCHAR = (UCHAR)mm;
			Day_UCHAR = (UCHAR)DayofYear_short;
		}

		_itoa(Year_short,Temp_String,10);                  //nian
		Temp_String1[0]='-';
		Temp_String1[1]='\0';
		strcat(Temp_String,Temp_String1);                  //nian -
		_itoa(Month_UCHAR,Temp_String1,10);
		if(Month_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
		strcat(Temp_String,Temp_String1);
		Temp_String1[0]='-';
		Temp_String1[1]='\0';
		strcat(Temp_String,Temp_String1);                  //nian - yue -
		_itoa(Day_UCHAR,Temp_String1,10);
		if(Day_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
		strcat(Temp_String,Temp_String1);                  //nian - yue - ri

		Date_CString =Temp_String;
		
		m_clistctrlMsgList.SetItemText(nListCount_Msg,1,Date_CString);                              //Data

	//////////////////////////////////////////////////////////////////////////
	//                Time
	//////////////////////////////////////////////////////////////////////////
	Temp_UCHAR =MsgList_h_ValidData[11+8*kk];
	Temp_short =MsgList_h_ValidData[12+8*kk];
	Temp_short = Temp_short<< 8;
	Temp_short +=Temp_UCHAR;
	Temp_MS =Temp_short<<16;

	Temp_UCHAR =MsgList_h_ValidData[9+8*kk];
	Temp_short =MsgList_h_ValidData[10+8*kk];
	Temp_short = Temp_short<< 8;
	Temp_short +=Temp_UCHAR;
	Temp_MS +=Temp_short;                                  //ms ???
	Temp_UINT =Temp_MS;

	Hour_UCHAR =(UCHAR)(Temp_MS/3600000);                //???????24 ???????????
	Temp_UINT =Temp_MS %3600000;
	Minute_UCHAR = (UCHAR)(Temp_UINT /60000);
	Temp_UINT =Temp_UINT %60000;
	Second_UCHAR =(UCHAR)(Temp_UINT/1000);
	Temp_UINT =Temp_UINT %1000;
	ms_UINT =Temp_UINT;

	_itoa(Hour_UCHAR,Temp_String,10);
		if(Hour_UCHAR<10)
		{
			Temp_String[1]=Temp_String[0];
			Temp_String[0]='0';
			Temp_String[2]='\0';
		}
	Temp_String1[0]=':';
	Temp_String1[1]='\0';
	strcat(Temp_String,Temp_String1);          //shi:
	_itoa(Minute_UCHAR,Temp_String1,10);
		if(Minute_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
	strcat(Temp_String,Temp_String1);
	Temp_String1[0]=':';
	Temp_String1[1]='\0';                  
	strcat(Temp_String,Temp_String1);          //shi : fen :
	_itoa(Second_UCHAR,Temp_String1,10);
		if(Second_UCHAR<10)
		{
			Temp_String1[1]=Temp_String1[0];
			Temp_String1[0]='0';
			Temp_String1[2]='\0';
		}
	strcat(Temp_String,Temp_String1);          //shi : fen : miao
	Time_CString = Temp_String;
		m_clistctrlMsgList.SetItemText(nListCount_Msg,2,Time_CString);                                        //Time

	//////////////////////////////////////////////////////////////////////////
	//                             ms
	//////////////////////////////////////////////////////////////////////////
	_itoa(ms_UINT,Temp_String,10);
	ms_CString =Temp_String;

		m_clistctrlMsgList.SetItemText(nListCount_Msg,3,ms_CString);                                            //ms

	//////////////////////////////////////////////////////////////////////////
	//                          Event
	//////////////////////////////////////////////////////////////////////////
	if(MsgID>32767)
	Event_CString ="+";
	else
	Event_CString="-";
//	Event_CString-=32768;
		m_clistctrlMsgList.SetItemText(nListCount_Msg,4,Event_CString);                                         //Event
		nListCount_Msg ++;
	}

}

}

BEGIN_MESSAGE_MAP(Dlg_ZJM, CDialog)
	//{{AFX_MSG_MAP(Dlg_ZJM)
	ON_BN_CLICKED(IDC_ZJM_TQCS, OnZjmTqcs)
	ON_BN_CLICKED(IDC_ZJM_AD1, OnZjmAd1)
	ON_BN_CLICKED(IDC_ZJM_TimeSet, OnZJMTimeSet)
	ON_BN_CLICKED(IDC_ZJM_ADAdjust, OnZJMADAdjust)
	ON_BN_CLICKED(IDC_ZJM_TQML, OnZjmTqml)
	//ON_BN_CLICKED(IDC_ZJM_Channel, OnZjmChannel)
	ON_BN_CLICKED(IDC_ZJM_Message, OnZjmMessage)
	ON_BN_CLICKED(IDC_ZJM_COMSet, OnZJMCOMSet)
	ON_BN_CLICKED(IDC_ZJM_Angle, OnBaseAngle)
	ON_BN_CLICKED(IDC_CHECK_ZJM_DC, OnCheckZjmDc)
	ON_BN_CLICKED(IDC_CHECK_ZJM_LINE1, OnCheckZjmLine1)
	ON_BN_CLICKED(IDC_CHECK_ZJM_LINE2, OnCheckZjmLine2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_ZJM_FETCH, OnButtonZjmFetch)
	ON_BN_CLICKED(IDC_BUTTON_ZJM_SAVE, OnButtonZjmSave)
	ON_BN_CLICKED(IDC_BUTTON_ZJM_OPEN, OnButtonZjmOpen)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_VIEW_Set, OnVIEWSet)
   
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_ZJM message handlers

void Dlg_ZJM::OnZjmTqcs() 
{
	// TODO: Add your control notification handler code here
	TQCS_dlg.TQCS_FUNCTION=IDC_ZJM_TQCS;
	TQCS_dlg.DoModal();
}

void Dlg_ZJM::OnZjmAd1() 
{
	// TODO: Add your control notification handler code here
	AD1_dlg.AD1_FUNCTION =IDC_ZJM_AD1;
	AD1_dlg.DoModal();
}
void Dlg_ZJM::OnBaseAngle()
{
	// TODO: Add your control notification handler code here
	BaseAngle_dlg.ANGLE_FUNCTION=IDC_ZJM_Angle;
    BaseAngle_dlg.DoModal();
}
//DEL void Dlg_ZJM::OnZJMADData() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	Dlg_ADData dlg;
//DEL 	dlg.DoModal();
//DEL }

void Dlg_ZJM::OnZJMTimeSet() 
{
	// TODO: Add your control notification handler code here
	
	::GetLocalTime(&m_nTime);
	TimeSet_dlg.DoModal();
}

void Dlg_ZJM::OnZJMADAdjust() 
{
	// TODO: Add your control notification handler code here
	
	ADAdjust_dlg.DoModal();
}

void Dlg_ZJM::OnZjmTqml() 
{
	// TODO: Add your control notification handler code here
	
	TQML_dlg.DoModal();
}

/*void Dlg_ZJM::OnZjmChannel() 
{
	// TODO: Add your control notification handler code here
	
	Channel_dlg.DoModal();
}*/

void Dlg_ZJM::OnZjmMessage() 
{
	// TODO: Add your control notification handler code here
	Message_dlg.Message_FUNCTION=IDC_ZJM_Message;
	Message_dlg.DoModal();
}

void Dlg_ZJM::OnZJMCOMSet() 
{
	// TODO: Add your control notification handler code here
	Dlg_ComSet  dlg;
	CNew1Dlg * pParent=(CNew1Dlg *)GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_ZJM_COMSet;	
	dlg.DoModal();
	m_nComPortMb =dlg.m_nComSetCom;
		if(pParent->m_ctrlCOM.GetPortOpen())                     //is the port opened?
		pParent->m_ctrlCOM.SetPortOpen(FALSE);
	    pParent->m_ctrlCOM.SetCommPort(m_nComPortMb+1);                       //choose port 1;
	if(!pParent->m_ctrlCOM.GetPortOpen())                    //if port 1 not opened?
		pParent->m_ctrlCOM.SetPortOpen(TRUE);                //open port 1
	else
	AfxMessageBox("cannot open serial port");   //others , show a messagebox "can't open!"
		//pParent->m_ctrlCOM.SetCommPort(m_nComPortMb*5+1);
		pParent->m_ctrlCOM.SetSettings((LPCTSTR)dlg.settingpara);
		
}

BEGIN_EVENTSINK_MAP(Dlg_ZJM, CDialog)
    //{{AFX_EVENTSINK_MAP(Dlg_ZJM)
//	ON_EVENT(Dlg_ZJM, IDC_MSCOMM2, 1 /* OnComm */, OnOnCommMscomm2, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void Dlg_ZJM::OnCheckZjmDc() 
{
	// TODO: Add your control notification handler code here
//UpdateData(TRUE);
	m_boolZJM_DC ^=TRUE;
	UpdateData(FALSE);
	//20240618
//    AD1_dlg.AD1_FUNCTION =IDC_ZJM_AD1;
//	AD1_dlg.DoModal();

}

void Dlg_ZJM::OnCheckZjmLine1() 
{
	// TODO: Add your control notification handler code here
	m_boolZJM_Line1 ^=TRUE;
		UpdateData(FALSE);
}

void Dlg_ZJM::OnCheckZjmLine2() 
{
	// TODO: Add your control notification handler code here
	m_boolZJM_Line2 ^=TRUE;
		UpdateData(FALSE);
}

void Dlg_ZJM::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

//	(CNew1Dlg *)GetParent()->ShowWindow(HIDE_WINDOW);
	
	// TODO: Add your message handler code here
	m_clistctrlADCacul.InsertColumn(0,"Channel",LVCFMT_LEFT,80,-1);
	m_clistctrlADCacul.InsertColumn(1,"ShowItem",LVCFMT_LEFT,80,-1);
	m_clistctrlADCacul.InsertColumn(2,"Second",LVCFMT_LEFT,80,-1);
	m_clistctrlADCacul.InsertColumn(3,"%",LVCFMT_LEFT,80,-1);
	m_clistctrlADCacul.InsertColumn(4,"Count",LVCFMT_LEFT,80,-1);
	m_clistctrlMsgList.InsertColumn(0,"MsgID",LVCFMT_LEFT,80,-1);
	m_clistctrlMsgList.InsertColumn(1,"Data",LVCFMT_LEFT,80,-1);
	m_clistctrlMsgList.InsertColumn(2,"Time",LVCFMT_LEFT,80,-1);
	m_clistctrlMsgList.InsertColumn(3,"ms",LVCFMT_LEFT,80,-1);
	m_clistctrlMsgList.InsertColumn(4,"Events",LVCFMT_LEFT,80,-1);

//	ShowWindow(SW_SHOW);
	CNew1Dlg * pParent=(CNew1Dlg *)GetParent();
    pParent->ErrorCounter=0;
	pParent->Connect_Index=0;
	UpdateData(FALSE);
	
	
}

void Dlg_ZJM::OnButtonZjmFetch() 
{
	// TODO: Add your control notification handler code here
 //   TeleBlock ADData_block_37;
	UCHAR TX[280];
	TX[0]=0XA2;
	TX[1]='\0';

CNew1Dlg * pParent=(CNew1Dlg *)GetParent();
pParent->Connect_Index=0;
pParent->ErrorCounter=0;
pParent->Down =IDC_BUTTON_ZJM_FETCH;
pParent->RX_Msg_End=FALSE;
pParent->Msg_Len=0;


if(FETCH_REFRESH==0)
{
	/*
	pParent->ADData_block_37.Telegram_Nr=37;                            //AD????????
	pParent->ADData_block_37.Station_adr=0;
	pParent->ADData_block_37.F1_field=0;
	pParent->ADData_block_37.F2_field=0x80;
	pParent->ADData_block_37.Data=(UCHAR*)"";

	pParent->AC_angle_block_47.Telegram_Nr=47;                            //AD???????
	pParent->AC_angle_block_47.Station_adr=0;
	pParent->AC_angle_block_47.F1_field=0;
	pParent->AC_angle_block_47.F2_field=0x80;
	pParent->AC_angle_block_47.Data=(UCHAR*)"";

	pParent->Msg_h_block_12.Telegram_Nr=12;                             //pc????????????head??
	pParent->Msg_h_block_12.Station_adr=0;
	pParent->Msg_h_block_12.F1_field=0;
	pParent->Msg_h_block_12.F2_field=0x80;
//	*(Msg_h_block_12.Data)=1;
//	TX[0]=1;
//	pParent->Msg_h_block_12.Data=(UCHAR*)"";
	pParent->Connect_Telegram.ValidDataToPack[0]=0;
	pParent->Connect_Telegram.ValidDataToPack[1]=0;

	pParent->Msg_block_13.Telegram_Nr=13;                               //PC ????????????head??
	pParent->Msg_block_13.Station_adr=0;
	pParent->Msg_block_13.F1_field=0;
	pParent->Msg_block_13.F2_field=0x80;
	pParent->Msg_block_13.Data=(UCHAR*)"";
*/

	    pParent->TQCS_block_35.Telegram_Nr=35;                              //?????????
		pParent->TQCS_block_35.Station_adr=0;
		pParent->TQCS_block_35.F1_field=0;
		pParent->TQCS_block_35.F2_field=0x80;
		pParent->TQCS_block_35.Data=(UCHAR *)"";
	//	TQCS_block_35.Data[0]='\0';

		pParent->ACAD_block_33.Telegram_Nr=33;                              //????AD???????
		pParent->ACAD_block_33.Station_adr=0;
		pParent->ACAD_block_33.F1_field=0;
		pParent->ACAD_block_33.F2_field=0x80;
		pParent->ACAD_block_33.Data=(UCHAR*)"";
	//	ACAD_block_33.Data[0]='\0';

		pParent->ADData_block_37.Telegram_Nr=37;                            //AD????????
		pParent->ADData_block_37.Station_adr=0;
		pParent->ADData_block_37.F1_field=0;
		pParent->ADData_block_37.F2_field=0x80;
		pParent->ADData_block_37.Data=(UCHAR*)"";
    
		pParent->AC_angle_block_47.Telegram_Nr=47;                            //????AD?????
		pParent->AC_angle_block_47.Station_adr=0;
		pParent->AC_angle_block_47.F1_field=0;
		pParent->AC_angle_block_47.F2_field=0x80;
		pParent->AC_angle_block_47.Data=(UCHAR*)"";

		pParent->Message_block_49.Telegram_Nr=49;                            //message???
		pParent->Message_block_49.Station_adr=0;
		pParent->Message_block_49.F1_field=0;
		pParent->Message_block_49.F2_field=0x80;
		pParent->Message_block_49.Data=(UCHAR*)"";

		pParent->Msg_h_block_12.Telegram_Nr=12;                             //pc????????????head??
		pParent->Msg_h_block_12.Station_adr=0;
		pParent->Msg_h_block_12.F1_field=0;
		pParent->Msg_h_block_12.F2_field=0x80;
		pParent->Msg_h_block_12.Data=(UCHAR*)"";

		pParent->Msg_block_13.Telegram_Nr=13;                               //PC ????????????head??
		pParent->Msg_block_13.Station_adr=0;
		pParent->Msg_block_13.F1_field=0;
		pParent->Msg_block_13.F2_field=0x80;
		pParent->Msg_block_13.Data=(UCHAR*)"";

		pParent->Connect_Telegram.ValidDataToPack[0]=0;
		pParent->Connect_Telegram.ValidDataToPack[1]=0;
		pParent->Connect_Telegram.ValidDataToPack[2]=0;
		pParent->Connect_Telegram.ValidDataToPack[3]=0;
		pParent->Connect_Telegram.ValidDataToPack[4]=0;
		pParent->Connect_Telegram.ValidDataToPack[5]=0;
		pParent->Connect_Telegram.ValidDataToPack[6]='\0';



//	pParent->Connect_Telegram.ValidDataToPack[0]=1;
//	pParent->Connect_Telegram.PACK_SELECT =TRUE;
//	pParent->Zero_NR=0;
//	pParent->SentData(TX);
//	if(ErrorCounter<5 && Connect_Index==0)
//	{

		pParent->Fun_Connect(pParent->ADData_block_37,0);
//		Fun_Connect(TQCS_block_35);
//	}
//		while(pParent->RX_Msg_End==FALSE);
//		MessageBox("UPDATA");
//		UpdateData(FALSE);


		FETCH_REFRESH=1;
		SetTimer(IDC_BUTTON_ZJM_FETCH,999,NULL);
}

}


void Dlg_ZJM::OnButtonZjmSave() 
{
	// TODO: Add your control notification handler code here
	UCHAR *Save_Data;
	Save_Data =(UCHAR*)malloc(93);
	for(int tt=0;tt<93;tt++)
	{
		if(tt<59)
			*(Save_Data+tt)= AD1_dlg.DATA[tt];
		else
			*(Save_Data+tt)=TQCS_dlg.DATA[tt-59];
	}

	CFileDialog Save_dlg(FALSE);
	Save_dlg.m_ofn.lpstrTitle ="?????????";
	Save_dlg.m_ofn.lpstrFilter="Binary File(*.bin)\0*.bin\0Text File(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	Save_dlg.m_ofn.lpstrDefExt="bin";
	if(IDOK==Save_dlg.DoModal())
	{
		CFile file(Save_dlg.GetFileName(),CFile::modeCreate|CFile::modeWrite);
		file.Write(Save_Data,93);
		file.Close();
	}
}

void Dlg_ZJM::OnButtonZjmOpen() 
{
	// TODO: Add your control notification handler code here
	CFileDialog Open_dlg(TRUE);
	Open_dlg.m_ofn.lpstrTitle ="??????";
	Open_dlg.m_ofn.lpstrFilter="Binary File(*.bin)\0*.bin\0Text File(*.txt)\0*.txt\0All Files(*.*)\0*.*\0\0";
	if(IDOK==Open_dlg.DoModal())
	{
		CFile file(Open_dlg.GetFileName(),CFile::modeRead);
		UCHAR *pDATA;
	//	DWORD Lenth;
	//	Lenth = file.GetLength();
		pDATA = new UCHAR[93];
		file.Read(pDATA,93);
		file.Close();
		for(int tt=0 ;tt<93;tt++)
		{
			if(tt<59)
			{
				AD1_dlg.AD1_FUNCTION =IDC_BUTTON_ZJM_OPEN;
				AD1_dlg.ValidData[4+tt]= *(pDATA+tt);
			}
			else
			{
				TQCS_dlg.TQCS_FUNCTION=IDC_BUTTON_ZJM_OPEN;
				TQCS_dlg.ValidData[tt-55]=*(pDATA+tt);
			}
		}
		
	}
	
}


void Dlg_ZJM::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==IDC_BUTTON_ZJM_FETCH)
	{
		
		UpdateData(TRUE);
//		if((FETCH_REFRESH--)==0)
			KillTimer(IDC_BUTTON_ZJM_FETCH);
			FETCH_REFRESH=0;
	}
	CDialog::OnTimer(nIDEvent);
}

void Dlg_ZJM::OnVIEWSet() 
{
// TODO: Add your control notification handler code here
	DimSet_dlg.DoModal();
//BaseAngle_dlg.DoModal();
}
