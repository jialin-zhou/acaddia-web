// Dlg_ADAdjust1.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_ADAdjust1.h"

#include "stdlib.h"
#include "new1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADAdjust1 dialog


Dlg_ADAdjust1::Dlg_ADAdjust1(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_ADAdjust1::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_ADAdjust1)
//	m_boolADAdjust_C_DC1_OK = FALSE;
//	m_boolADAdjust_C_DC2_OK = FALSE;
//	m_boolADAdjust_C_DC3_OK = FALSE;
//	m_boolADAdjust_C_DC4_OK = FALSE;
//	m_boolADAdjust_V_DC1_OK = FALSE;
//	m_boolADAdjust_V_DC2_OK = FALSE;
//	m_boolADAdjust_V_DC3_OK = FALSE;
//	m_boolADAdjust_V_DC4_OK = FALSE;

  


	m_boolADAdjust_Ia_OK = FALSE;
	m_boolADAdjust_Ib_OK = FALSE;
	m_boolADAdjust_Ic_OK = FALSE;
	m_boolADAdjust_Ua_OK = FALSE;
	m_boolADAdjust_Ub_OK = FALSE;
	m_boolADAdjust_Uc_OK = FALSE;
//	m_floatADAdjust_C_DC1_1 = 0.0f;
//	m_CStringADAdjust_C_DC1_2 = _T("");
//	m_CStringADAdjust_C_DC1_3 = _T("");
//	m_CStringADAdjust_C_DC1_4 = _T("");
//	m_CStringADAdjust_C_DC1_5 = _T("");
//	m_CStringADAdjust_C_DC2_2 = _T("");
//	m_CStringADAdjust_C_DC2_3 = _T("");
//	m_CStringADAdjust_C_DC2_4 = _T("");
//	m_CStringADAdjust_C_DC2_5 = _T("");
//	m_CStringADAdjust_C_DC3_2 = _T("");
//	m_CStringADAdjust_C_DC3_3 = _T("");
//	m_CStringADAdjust_C_DC3_4 = _T("");
//	m_CStringADAdjust_C_DC3_5 = _T("");
//	m_CStringADAdjust_C_DC4_2 = _T("");
//	m_CStringADAdjust_C_DC4_3 = _T("");
//	m_CStringADAdjust_C_DC4_4 = _T("");
//	m_CStringADAdjust_C_DC4_5 = _T("");

//	m_CStringADAdjust_V_DC1_2 = _T("");
//	m_CStringADAdjust_V_DC1_3 = _T("");
//	m_CStringADAdjust_V_DC1_4 = _T("");
//	m_CStringADAdjust_V_DC1_5 = _T("");
//	m_CStringADAdjust_V_DC2_2 = _T("");
//	m_CStringADAdjust_V_DC2_3 = _T("");
//	m_CStringADAdjust_V_DC2_4 = _T("");
//	m_CStringADAdjust_V_DC2_5 = _T("");
//	m_CStringADAdjust_V_DC3_2 = _T("");
//	m_CStringADAdjust_V_DC3_3 = _T("");
//	m_CStringADAdjust_V_DC3_4 = _T("");
//	m_CStringADAdjust_V_DC3_5 = _T("");
//	m_CStringADAdjust_V_DC4_2 = _T("");
//	m_CStringADAdjust_V_DC4_3 = _T("");
//	m_CStringADAdjust_V_DC4_4 = _T("");
//	m_CStringADAdjust_V_DC4_5 = _T("");
	m_nADAdjust_ACChannel = -1;
	m_nADAdjust_Channel = -1;
	m_nADAdjust_DCChannel = -1;
	m_CStringADAdjust_Ia_2 = _T("");
	m_CStringADAdjust_Ia_3 = _T("");
	m_CStringADAdjust_Ia_4 = _T("");
	m_CStringADAdjust_Ia_5 = _T("");
	m_CStringADAdjust_Ib_2 = _T("");
	m_CStringADAdjust_Ib_3 = _T("");
	m_CStringADAdjust_Ib_4 = _T("");
	m_CStringADAdjust_Ib_5 = _T("");
	m_CStringADAdjust_Ic_2 = _T("");
	m_CStringADAdjust_Ic_3 = _T("");
	m_CStringADAdjust_Ic_4 = _T("");
	m_CStringADAdjust_Ic_5 = _T("");
	m_CStringADAdjust_Ua_2 = _T("");
	m_CStringADAdjust_Ua_3 = _T("");
	m_CStringADAdjust_Ua_4 = _T("");
	m_CStringADAdjust_Ua_5 = _T("");
	m_CStringADAdjust_Ub_2 = _T("");
	m_CStringADAdjust_Ub_3 = _T("");
	m_CStringADAdjust_Ub_4 = _T("");
	m_CStringADAdjust_Ub_5 = _T("");
	m_CStringADAdjust_Uc_2 = _T("");
	m_CStringADAdjust_Uc_3 = _T("");
	m_CStringADAdjust_Uc_4 = _T("");
	m_CStringADAdjust_Uc_5 = _T("");
//	m_floatADAdjust_C_DC2_1 = 0.0f;
//	m_floatADAdjust_C_DC3_1 = 0.0f;
//	m_floatADAdjust_C_DC4_1 = 0.0f;
//	m_floatADAdjust_V_DC4_1 = 0.0f;
//	m_floatADAdjust_V_DC3_1 = 0.0f;
//	m_floatADAdjust_V_DC2_1 = 0.0f;
//	m_floatADAdjust_V_DC1_1 = 0.0f;
	m_floatADAdjust_Uc_1 = 0.0f;
	m_floatADAdjust_Ub_1 = 0.0f;
	m_floatADAdjust_Ua_1 = 0.0f;
	m_floatADAdjust_Ic_1 = 0.0f;
	m_floatADAdjust_Ib_1 = 0.0f;
	m_floatADAdjust_Ia_1 = 0.0f;
	CHECK_STATUS=0;                          //状态标志位，每个“完成”置1，共20个,最低位(第0位)U1a,……，第20位C_DC4
	//}}AFX_DATA_INIT
	
}


void Dlg_ADAdjust1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_ADAdjust1)
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_C_DC1_OK, m_boolADAdjust_C_DC1_OK);
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_C_DC2_OK, m_boolADAdjust_C_DC2_OK);
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_C_DC3_OK, m_boolADAdjust_C_DC3_OK);
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_C_DC4_OK, m_boolADAdjust_C_DC4_OK);
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_V_DC1_OK, m_boolADAdjust_V_DC1_OK);
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_V_DC2_OK, m_boolADAdjust_V_DC2_OK);
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_V_DC3_OK, m_boolADAdjust_V_DC3_OK);
//	DDX_Check(pDX, IDC_CHECK_ADAdjust_V_DC4_OK, m_boolADAdjust_V_DC4_OK);
	DDX_Check(pDX, IDC_CHECK_ADAdjust_Ia_OK, m_boolADAdjust_Ia_OK);
	DDX_Check(pDX, IDC_CHECK_ADAdjust_Ib_OK, m_boolADAdjust_Ib_OK);
	DDX_Check(pDX, IDC_CHECK_ADAdjust_Ic_OK, m_boolADAdjust_Ic_OK);
	DDX_Check(pDX, IDC_CHECK_ADAdjust_Ua_OK, m_boolADAdjust_Ua_OK);
	DDX_Check(pDX, IDC_CHECK_ADAdjust_Ub_OK, m_boolADAdjust_Ub_OK);
	DDX_Check(pDX, IDC_CHECK_ADAdjust_Uc_OK, m_boolADAdjust_Uc_OK);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC1_1, m_floatADAdjust_C_DC1_1);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC1_2, m_CStringADAdjust_C_DC1_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC1_3, m_CStringADAdjust_C_DC1_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC1_4, m_CStringADAdjust_C_DC1_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC1_5, m_CStringADAdjust_C_DC1_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC2_2, m_CStringADAdjust_C_DC2_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC2_3, m_CStringADAdjust_C_DC2_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC2_4, m_CStringADAdjust_C_DC2_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC2_5, m_CStringADAdjust_C_DC2_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC3_2, m_CStringADAdjust_C_DC3_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC3_3, m_CStringADAdjust_C_DC3_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC3_4, m_CStringADAdjust_C_DC3_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC3_5, m_CStringADAdjust_C_DC3_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC4_2, m_CStringADAdjust_C_DC4_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC4_3, m_CStringADAdjust_C_DC4_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC4_4, m_CStringADAdjust_C_DC4_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC4_5, m_CStringADAdjust_C_DC4_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC1_2, m_CStringADAdjust_V_DC1_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC1_3, m_CStringADAdjust_V_DC1_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC1_4, m_CStringADAdjust_V_DC1_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC1_5, m_CStringADAdjust_V_DC1_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC2_2, m_CStringADAdjust_V_DC2_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC2_3, m_CStringADAdjust_V_DC2_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC2_4, m_CStringADAdjust_V_DC2_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC2_5, m_CStringADAdjust_V_DC2_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC3_2, m_CStringADAdjust_V_DC3_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC3_3, m_CStringADAdjust_V_DC3_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC3_4, m_CStringADAdjust_V_DC3_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC3_5, m_CStringADAdjust_V_DC3_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC4_2, m_CStringADAdjust_V_DC4_2);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC4_3, m_CStringADAdjust_V_DC4_3);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC4_4, m_CStringADAdjust_V_DC4_4);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC4_5, m_CStringADAdjust_V_DC4_5);
	DDX_Radio(pDX, IDC_RADIO_ADAdjust_ACChannel, m_nADAdjust_ACChannel);
	DDX_Radio(pDX, IDC_RADIO_ADAdjust_Channel, m_nADAdjust_Channel);
	DDX_Radio(pDX, IDC_RADIO_ADAdjust_DCChannel, m_nADAdjust_DCChannel);
  //  DDX_Radio(pDX, IDC_RADIO_ADAdjust_DCChannel5, m_nADAdjust_DCChannelC);



	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ia_2, m_CStringADAdjust_Ia_2);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ia_3, m_CStringADAdjust_Ia_3);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ia_4, m_CStringADAdjust_Ia_4);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ia_5, m_CStringADAdjust_Ia_5);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ib_2, m_CStringADAdjust_Ib_2);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ib_3, m_CStringADAdjust_Ib_3);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ib_4, m_CStringADAdjust_Ib_4);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ib_5, m_CStringADAdjust_Ib_5);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ic_2, m_CStringADAdjust_Ic_2);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ic_3, m_CStringADAdjust_Ic_3);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ic_4, m_CStringADAdjust_Ic_4);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ic_5, m_CStringADAdjust_Ic_5);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ua_2, m_CStringADAdjust_Ua_2);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ua_3, m_CStringADAdjust_Ua_3);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ua_4, m_CStringADAdjust_Ua_4);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ua_5, m_CStringADAdjust_Ua_5);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ub_2, m_CStringADAdjust_Ub_2);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ub_3, m_CStringADAdjust_Ub_3);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ub_4, m_CStringADAdjust_Ub_4);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ub_5, m_CStringADAdjust_Ub_5);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Uc_2, m_CStringADAdjust_Uc_2);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Uc_3, m_CStringADAdjust_Uc_3);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Uc_4, m_CStringADAdjust_Uc_4);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Uc_5, m_CStringADAdjust_Uc_5);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC2_1, m_floatADAdjust_C_DC2_1);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC3_1, m_floatADAdjust_C_DC3_1);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_C_DC4_1, m_floatADAdjust_C_DC4_1);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC4_1, m_floatADAdjust_V_DC4_1);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC3_1, m_floatADAdjust_V_DC3_1);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC2_1, m_floatADAdjust_V_DC2_1);
//	DDX_Text(pDX, IDC_EDIT_ADAdjust_V_DC1_1, m_floatADAdjust_V_DC1_1);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Uc_1, m_floatADAdjust_Uc_1);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ub_1, m_floatADAdjust_Ub_1);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ua_1, m_floatADAdjust_Ua_1);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ic_1, m_floatADAdjust_Ic_1);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ib_1, m_floatADAdjust_Ib_1);
	DDX_Text(pDX, IDC_EDIT_ADAdjust_Ia_1, m_floatADAdjust_Ia_1);
	//}}AFX_DATA_MAP


	if(Function_ID ==IDC_BUTTON_ADAdjust_Fetch)
	{
//		MessageBox("dodataexchange");
		UCHAR Channel_NR =ValidData[4];
		UCHAR Temp_UCHAR;
		CHAR Temp_Buffer[10];
		unsigned short Temp_short;
		UINT Temp_UINT;
		CString str1,str2,str3,Temp_CString;
		if(ValidData[5]==0x55||ValidData[5]==0xAA)           //wan cheng
		{
			if(ValidData[5]==0x55)
			{
				CHECK_STATUS |=(0x0001<<(Channel_NR-1)); 
			}//set the check status "ok"
            else
			{
				CHECK_STATUS &=(~(0x0001<<(Channel_NR-1)));
                MessageBox("校准失败!请检查校准源及模拟量采集硬件通道连接是否正确?");
			}
				Temp_UCHAR =ValidData[6];                 //xiu zheng xi shu
				Temp_short =ValidData[7];
				ParaData[2*(Channel_NR-1)]=ValidData[6];  //bao cun xiu zheng can shu 
				ParaData[2*(Channel_NR-1)+1]=ValidData[7];
				Temp_short= Temp_short<<8;
				Temp_short +=Temp_UCHAR;  
				_itoa(Temp_short,Temp_Buffer,16);

				Temp_CString =Temp_Buffer;
				Temp_short = Temp_CString.GetLength();
				Temp_Buffer[Temp_short]='H';
				Temp_Buffer[Temp_short+1]='\0';

				Temp_CString =Temp_Buffer;
				Temp_CString.MakeUpper();
				str1 = Temp_CString;

				Temp_UCHAR =ValidData[8];                 //yuan xi shu
				Temp_short =ValidData[9];
				Temp_short= Temp_short<<8;
				Temp_short +=Temp_UCHAR;  
				_itoa(Temp_short,Temp_Buffer,16);

				Temp_CString =Temp_Buffer;
				Temp_short = Temp_CString.GetLength();
				Temp_Buffer[Temp_short]='H';
				Temp_Buffer[Temp_short+1]='\0';

				Temp_CString =Temp_Buffer;
				Temp_CString.MakeUpper();
				str2 = Temp_CString;

				Temp_UCHAR =ValidData[10];                 //ji suan fan hui zhi 
				Temp_short =ValidData[11];
				Temp_short= Temp_short<<8;
				Temp_short +=Temp_UCHAR;  
				_itoa(Temp_short,Temp_Buffer,16);

				Temp_CString =Temp_Buffer;
				Temp_short = Temp_CString.GetLength();
				Temp_Buffer[Temp_short]='H';
				Temp_Buffer[Temp_short+1]='\0';

				Temp_CString =Temp_Buffer;
				Temp_CString.MakeUpper();
				str3 = Temp_CString;


			if(Channel_NR >12)
			{
				m_nADAdjust_Channel =2;     //DC
				m_nADAdjust_DCChannel = Channel_NR-13; 
				
				if(m_nADAdjust_DCChannel==0)
				{
					
				//	m_CStringADAdjust_V_DC1_2 =str1;
				//	m_CStringADAdjust_V_DC1_3 =str2;
				//	m_CStringADAdjust_V_DC1_4 =str3;

// save the data , when radio , can display again.
				//	DC[0].f_para1  = m_floatADAdjust_V_DC1_1;
					DC[0].Cs_para2 = str1;
					DC[0].Cs_para3 = str2;
					DC[0].Cs_para4 = str3;
				//	DC[0].Cs_para5 = m_CStringADAdjust_V_DC1_5;
					DC[0].b_paraOK =TRUE;
					
				}
				if(m_nADAdjust_DCChannel==1)
				{
					//m_CStringADAdjust_V_DC2_2 =str1;
				//	m_CStringADAdjust_V_DC2_3 =str2;
				//	m_CStringADAdjust_V_DC2_4 =str3;

// save the data , when radio , can display again.
					//DC[1].f_para1  = m_floatADAdjust_V_DC2_1;
					DC[1].Cs_para2 = str1;
					DC[1].Cs_para3 = str2;
					DC[1].Cs_para4 = str3;
				//	DC[1].Cs_para5 = m_CStringADAdjust_V_DC2_5;
					DC[1].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==2)
				{
				//	m_CStringADAdjust_V_DC3_2 =str1;
				//	m_CStringADAdjust_V_DC3_3 =str2;
				//	m_CStringADAdjust_V_DC3_4 =str3;

// save the data , when radio , can display again.
				//	DC[2].f_para1  = m_floatADAdjust_V_DC3_1;
					DC[2].Cs_para2 = str1;
					DC[2].Cs_para3 = str2;
					DC[2].Cs_para4 = str3;
				//	DC[2].Cs_para5 = m_CStringADAdjust_V_DC3_5;
					DC[2].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==3)
				{
				//	m_CStringADAdjust_V_DC4_2 =str1;
				//	m_CStringADAdjust_V_DC4_3 =str2;
				//	m_CStringADAdjust_V_DC4_4 =str3;

// save the data , when radio , can display again.
				//	DC[3].f_para1  = m_floatADAdjust_V_DC4_1;
					DC[3].Cs_para2 = str1;
					DC[3].Cs_para3 = str2;
					DC[3].Cs_para4 = str3;
				//	DC[3].Cs_para5 = m_CStringADAdjust_V_DC4_5;
					DC[3].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==4)
				{
					//m_CStringADAdjust_C_DC1_2 =str1;
				//	m_CStringADAdjust_C_DC1_3 =str2;
				//	m_CStringADAdjust_C_DC1_4 =str3;

					// save the data , when radio , can display again.
				//	DC[4].f_para1  = m_floatADAdjust_C_DC1_1;
					DC[4].Cs_para2 = str1;
					DC[4].Cs_para3 = str2;
					DC[4].Cs_para4 = str3;
				//	DC[4].Cs_para5 = m_CStringADAdjust_C_DC1_5;
				//	DC[4].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==5)
				{
				//	m_CStringADAdjust_C_DC2_2 =str1;
				//	m_CStringADAdjust_C_DC2_3 =str2;
				//	m_CStringADAdjust_C_DC2_4 =str3;

					// save the data , when radio , can display again.
				//	DC[5].f_para1  = m_floatADAdjust_C_DC2_1;
					DC[5].Cs_para2 = str1;
					DC[5].Cs_para3 = str2;
					DC[5].Cs_para4 = str3;
				//	DC[5].Cs_para5 = m_CStringADAdjust_C_DC2_5;
				//	DC[5].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==6)
				{
				//	m_CStringADAdjust_C_DC3_2 =str1;
				//	m_CStringADAdjust_C_DC3_3 =str2;
				//	m_CStringADAdjust_C_DC3_4 =str3;

					// save the data , when radio , can display again.
				//	DC[6].f_para1  = m_floatADAdjust_C_DC3_1;
					DC[6].Cs_para2 = str1;
					DC[6].Cs_para3 = str2;
					DC[6].Cs_para4 = str3;
				//	DC[6].Cs_para5 = m_CStringADAdjust_C_DC3_5;
				//	DC[6].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==7)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[7].Cs_para2 = str1;
					DC[7].Cs_para3 = str2;
					DC[7].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[7].b_paraOK =TRUE;

				}
			
							
				if(m_nADAdjust_DCChannel==8)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[8].Cs_para2 = str1;
					DC[8].Cs_para3 = str2;
					DC[8].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
								
				if(m_nADAdjust_DCChannel==9)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[9].Cs_para2 = str1;
					DC[9].Cs_para3 = str2;
					DC[9].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
												
				if(m_nADAdjust_DCChannel==10)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[10].Cs_para2 = str1;
					DC[10].Cs_para3 = str2;
					DC[10].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
								
				if(m_nADAdjust_DCChannel==11)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[11].Cs_para2 = str1;
					DC[11].Cs_para3 = str2;
					DC[11].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
											
				if(m_nADAdjust_DCChannel==12)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[12].Cs_para2 = str1;
					DC[12].Cs_para3 = str2;
					DC[12].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
															
				if(m_nADAdjust_DCChannel==13)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[13].Cs_para2 = str1;
					DC[13].Cs_para3 = str2;
					DC[13].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
																				
				if(m_nADAdjust_DCChannel==14)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[14].Cs_para2 = str1;
					DC[14].Cs_para3 = str2;
					DC[14].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
																								
				if(m_nADAdjust_DCChannel==15)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[15].Cs_para2 = str1;
					DC[15].Cs_para3 = str2;
					DC[15].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==16)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[16].Cs_para2 = str1;
					DC[16].Cs_para3 = str2;
					DC[16].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==17)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[17].Cs_para2 = str1;
					DC[17].Cs_para3 = str2;
					DC[17].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==18)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[18].Cs_para2 = str1;
					DC[18].Cs_para3 = str2;
					DC[18].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==19)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[19].Cs_para2 = str1;
					DC[19].Cs_para3 = str2;
					DC[19].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==20)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[20].Cs_para2 = str1;
					DC[20].Cs_para3 = str2;
					DC[20].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==21)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[21].Cs_para2 = str1;
					DC[21].Cs_para3 = str2;
					DC[21].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==22)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[22].Cs_para2 = str1;
					DC[22].Cs_para3 = str2;
					DC[22].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				if(m_nADAdjust_DCChannel==23)
				{
				//	m_CStringADAdjust_C_DC4_2 =str1;
				//	m_CStringADAdjust_C_DC4_3 =str2;
				//	m_CStringADAdjust_C_DC4_4 =str3;

					// save the data , when radio , can display again.
				//	DC[7].f_para1  = m_floatADAdjust_C_DC4_1;
					DC[23].Cs_para2 = str1;
					DC[23].Cs_para3 = str2;
					DC[23].Cs_para4 = str3;
				//	DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
				//	DC[8].b_paraOK =TRUE;

				}
				
			}
			else if(Channel_NR<13)       //AC
			{
				if(Channel_NR>6)               //line 2
				{
					m_nADAdjust_Channel =1;     //line2
					m_nADAdjust_ACChannel = Channel_NR-7; 					

				}
				else if(Channel_NR<7)          //line 1
				{
					m_nADAdjust_Channel =0;     //DC
					m_nADAdjust_ACChannel = Channel_NR-1;
				}

				if(m_nADAdjust_ACChannel==0)             
					{
						m_CStringADAdjust_Ua_2 =str1;
						m_CStringADAdjust_Ua_3 =str2;
						m_CStringADAdjust_Ua_4 =str3;

						// save the data , when radio , can display again.
						if(Channel_NR<7)                                     // when line1
						{
							Line1[0].f_para1  = m_floatADAdjust_Ua_1;
							Line1[0].Cs_para2 = str1;
							Line1[0].Cs_para3 = str2;
							Line1[0].Cs_para4 = str3;
							Line1[0].Cs_para5 = m_CStringADAdjust_Ua_5;
							Line1[0].b_paraOK =TRUE;
						}
						else                                                 //when line2
						{
							Line2[0].f_para1  = m_floatADAdjust_Ua_1;
							Line2[0].Cs_para2 = str1;
							Line2[0].Cs_para3 = str2;
							Line2[0].Cs_para4 = str3;
							Line2[0].Cs_para5 = m_CStringADAdjust_Ua_5;
							Line2[0].b_paraOK =TRUE;
						}
					}
					if(m_nADAdjust_ACChannel==1)
					{
						m_CStringADAdjust_Ub_2 =str1;
						m_CStringADAdjust_Ub_3 =str2;
						m_CStringADAdjust_Ub_4 =str3;

						// save the data , when radio , can display again.
						if(Channel_NR<7)                                     // when line1
						{
							Line1[1].f_para1  = m_floatADAdjust_Ub_1;
							Line1[1].Cs_para2 = str1;
							Line1[1].Cs_para3 = str2;
							Line1[1].Cs_para4 = str3;
							Line1[1].Cs_para5 = m_CStringADAdjust_Ub_5;
							Line1[1].b_paraOK =TRUE;
						}
						else                                                 //when line2
						{
							Line2[1].f_para1  = m_floatADAdjust_Ub_1;
							Line2[1].Cs_para2 = str1;
							Line2[1].Cs_para3 = str2;
							Line2[1].Cs_para4 = str3;
							Line2[1].Cs_para5 = m_CStringADAdjust_Ub_5;
							Line2[1].b_paraOK =TRUE;
						}

					}
					if(m_nADAdjust_ACChannel==2)
					{
						m_CStringADAdjust_Uc_2 =str1;
						m_CStringADAdjust_Uc_3 =str2;
						m_CStringADAdjust_Uc_4 =str3;

						// save the data , when radio , can display again.
						if(Channel_NR<7)                                     // when line1
						{
							Line1[2].f_para1  = m_floatADAdjust_Uc_1;
							Line1[2].Cs_para2 = str1;
							Line1[2].Cs_para3 = str2;
							Line1[2].Cs_para4 = str3;
							Line1[2].Cs_para5 = m_CStringADAdjust_Uc_5;
							Line1[2].b_paraOK =TRUE;
						}
						else                                                 //when line2
						{
							Line2[2].f_para1  = m_floatADAdjust_Uc_1;
							Line2[2].Cs_para2 = str1;
							Line2[2].Cs_para3 = str2;
							Line2[2].Cs_para4 = str3;
							Line2[2].Cs_para5 = m_CStringADAdjust_Uc_5;
							Line2[2].b_paraOK =TRUE;
						}

					}
					if(m_nADAdjust_ACChannel==3)
					{
						m_CStringADAdjust_Ia_2 =str1;
						m_CStringADAdjust_Ia_3 =str2;
						m_CStringADAdjust_Ia_4 =str3;

						// save the data , when radio , can display again.
						if(Channel_NR<7)                                     // when line1
						{
							Line1[3].f_para1  = m_floatADAdjust_Ia_1;
							Line1[3].Cs_para2 = str1;
							Line1[3].Cs_para3 = str2;
							Line1[3].Cs_para4 = str3;
							Line1[3].Cs_para5 = m_CStringADAdjust_Ia_5;
							Line1[3].b_paraOK =TRUE;
						}
						else                                                 //when line2
						{
							Line2[3].f_para1  = m_floatADAdjust_Ia_1;
							Line2[3].Cs_para2 = str1;
							Line2[3].Cs_para3 = str2;
							Line2[3].Cs_para4 = str3;
							Line2[3].Cs_para5 = m_CStringADAdjust_Ia_5;
							Line2[3].b_paraOK =TRUE;
						}

					}
					if(m_nADAdjust_ACChannel==4)
					{
						m_CStringADAdjust_Ib_2 =str1;
						m_CStringADAdjust_Ib_3 =str2;
						m_CStringADAdjust_Ib_4 =str3;

						// save the data , when radio , can display again.
						if(Channel_NR<7)                                     // when line1
						{
							Line1[4].f_para1  = m_floatADAdjust_Ib_1;
							Line1[4].Cs_para2 = str1;
							Line1[4].Cs_para3 = str2;
							Line1[4].Cs_para4 = str3;
							Line1[4].Cs_para5 = m_CStringADAdjust_Ib_5;
							Line1[4].b_paraOK =TRUE;
						}
						else                                                 //when line2
						{
							Line2[4].f_para1  = m_floatADAdjust_Ib_1;
							Line2[4].Cs_para2 = str1;
							Line2[4].Cs_para3 = str2;
							Line2[4].Cs_para4 = str3;
							Line2[4].Cs_para5 = m_CStringADAdjust_Ib_5;
							Line2[4].b_paraOK =TRUE;
						}	

					}
					if(m_nADAdjust_ACChannel==5)
					{
						m_CStringADAdjust_Ic_2 =str1;
						m_CStringADAdjust_Ic_3 =str2;
						m_CStringADAdjust_Ic_4 =str3;

						// save the data , when radio , can display again.
						if(Channel_NR<7)                                     // when line1
						{
							Line1[5].f_para1  = m_floatADAdjust_Ic_1;
							Line1[5].Cs_para2 = str1;
							Line1[5].Cs_para3 = str2;
							Line1[5].Cs_para4 = str3;
							Line1[5].Cs_para5 = m_CStringADAdjust_Ic_5;
							Line1[5].b_paraOK =TRUE;
						}
						else                                                 //when line2
						{
							Line2[5].f_para1  = m_floatADAdjust_Ic_1;
							Line2[5].Cs_para2 = str1;
							Line2[5].Cs_para3 = str2;
							Line2[5].Cs_para4 = str3;
							Line2[5].Cs_para5 = m_CStringADAdjust_Ic_5;
							Line2[5].b_paraOK =TRUE;
						}

					}
			}

		}
		//else if(ValidData[5]==0x00||ValidData[5]==0xAA)      //wei wan cheng   : data is  0x00
		else if(ValidData[5]==0x00) 
		{
			CHECK_STATUS &=(~(0x0001<<(Channel_NR-1)));
		}
      
	 
        if (m_nADAdjust_Channel==0||m_nADAdjust_Channel==1)
		{
		if((((CHECK_STATUS &0X01)==0X01)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X040)==0X040)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ua_OK =TRUE;
		else
			m_boolADAdjust_Ua_OK=FALSE;
		if((((CHECK_STATUS &0X02)==0X02)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X080)==0X080)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ub_OK =TRUE;
		else
			m_boolADAdjust_Ub_OK=FALSE;
		if((((CHECK_STATUS &0X04)==0X04)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X100)==0X100)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Uc_OK =TRUE;
		else
			m_boolADAdjust_Uc_OK=FALSE;
		if((((CHECK_STATUS &0X08)==0X08)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X200)==0X200)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ia_OK =TRUE;
		else
			m_boolADAdjust_Ia_OK=FALSE;
		if((((CHECK_STATUS &0X10)==0X10)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X400)==0X400)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ib_OK =TRUE;
		else
			m_boolADAdjust_Ib_OK=FALSE;

		if((((CHECK_STATUS &0X20)==0X20)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X800)==0X800)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ic_OK =TRUE;
		else
			m_boolADAdjust_Ic_OK=FALSE;
		}
        /*
		if((((CHECK_STATUS &0X01)==0X01))||(((CHECK_STATUS &0X040)==0X040)))
			m_boolADAdjust_Ua_OK =TRUE;
		else
			m_boolADAdjust_Ua_OK=FALSE;

		if((((CHECK_STATUS &0X02)==0X02))||(((CHECK_STATUS &0X080)==0X080)))
			m_boolADAdjust_Ub_OK =TRUE;
		else
			m_boolADAdjust_Ub_OK=FALSE;
		if((((CHECK_STATUS &0X04)==0X04))||(((CHECK_STATUS &0X100)==0X100)))
			m_boolADAdjust_Uc_OK =TRUE;
		else
			m_boolADAdjust_Uc_OK=FALSE;
		if((((CHECK_STATUS &0X08)==0X08)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X200)==0X200)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ia_OK =TRUE;
		else
			m_boolADAdjust_Ia_OK=FALSE;
		if((((CHECK_STATUS &0X10)==0X10)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X400)==0X400)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ib_OK =TRUE;
		else
			m_boolADAdjust_Ib_OK=FALSE;

		if((((CHECK_STATUS &0X20)==0X20)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X800)==0X800)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ic_OK =TRUE;
		else
			m_boolADAdjust_Ic_OK=FALSE;
        */
		if (m_nADAdjust_Channel==2)
		{
		
		if((CHECK_STATUS &0X1000)==0X1000)
			m_boolADAdjust_V_DC1_OK =TRUE;
		else
			m_boolADAdjust_V_DC1_OK=FALSE;
		if((CHECK_STATUS &0X2000)==0X2000)
			m_boolADAdjust_V_DC2_OK =TRUE;
		else
			m_boolADAdjust_V_DC2_OK=FALSE;
		if((CHECK_STATUS &0X4000)==0X4000)
			m_boolADAdjust_V_DC3_OK =TRUE;
		else
			m_boolADAdjust_V_DC3_OK=FALSE;
		if((CHECK_STATUS &0X8000)==0X8000)
			m_boolADAdjust_V_DC4_OK =TRUE;
		else
			m_boolADAdjust_V_DC4_OK=FALSE;
		if((CHECK_STATUS &0X10000)==0X10000)
			m_boolADAdjust_C_DC1_OK =TRUE;
		else
			m_boolADAdjust_C_DC1_OK=FALSE;
		if((CHECK_STATUS &0X20000)==0X20000)
			m_boolADAdjust_C_DC2_OK =TRUE;
		else
			m_boolADAdjust_C_DC2_OK=FALSE;
		if((CHECK_STATUS &0X40000)==0X40000)
			m_boolADAdjust_C_DC3_OK =TRUE;
		else
			m_boolADAdjust_C_DC3_OK=FALSE;
		if((CHECK_STATUS &0X80000)==0X80000)
			m_boolADAdjust_C_DC4_OK =TRUE;
		else
			m_boolADAdjust_C_DC4_OK=FALSE;
		}
	   
	}
   	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ua_OK))->EnableWindow(m_boolADAdjust_Ua_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ub_OK))->EnableWindow(m_boolADAdjust_Ub_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Uc_OK))->EnableWindow(m_boolADAdjust_Uc_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ia_OK))->EnableWindow(m_boolADAdjust_Ia_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ib_OK))->EnableWindow(m_boolADAdjust_Ib_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ic_OK))->EnableWindow(m_boolADAdjust_Ic_OK);

//	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC1_OK))->EnableWindow(m_boolADAdjust_V_DC1_OK);
//	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC2_OK))->EnableWindow(m_boolADAdjust_V_DC2_OK);
//    ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC3_OK))->EnableWindow(m_boolADAdjust_V_DC3_OK);
 //   ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC4_OK))->EnableWindow(m_boolADAdjust_V_DC4_OK);
    
//	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC1_OK))->EnableWindow(m_boolADAdjust_C_DC1_OK);
//	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC2_OK))->EnableWindow(m_boolADAdjust_C_DC2_OK);
 //   ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC3_OK))->EnableWindow(m_boolADAdjust_C_DC3_OK);
 //   ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC4_OK))->EnableWindow(m_boolADAdjust_C_DC4_OK);

//////////////////////////////////////////////////////////////////////////
//
//             SAVE  the DATA 
//
//////////////////////////////////////////////////////////////////////////
/*
	if(Function_ID == IDC_RADIO_ADAdjust_Channel)                  //LINE1
	{ 
		//////////////////////////////////////////////////////////////////////////
	//           save Line 2  parameter
    //////////////////////////////////////////////////////////////////////////
	if(Line2[0].Index==0)
	{
		Line2[0].f_para1  = m_floatADAdjust_Ua_1 ;
		Line2[0].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[0].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[0].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[0].Cs_para5 = m_CStringADAdjust_Ua_5;
		Line2[0].b_paraOK = m_boolADAdjust_Ua_OK;

		Line2[1].f_para1 = m_floatADAdjust_Ub_1 ;
		Line2[1].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[1].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[1].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[1].Cs_para5 = m_CStringADAdjust_Ub_5;
		Line2[1].b_paraOK = m_boolADAdjust_Ub_OK;

		Line2[2].f_para1 = m_floatADAdjust_Uc_1 ;
		Line2[2].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[2].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[2].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[2].Cs_para5 = m_CStringADAdjust_Uc_5;
		Line2[2].b_paraOK = m_boolADAdjust_Uc_OK;

		Line2[3].f_para1 = m_floatADAdjust_Ia_1 ;
		Line2[3].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[3].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[3].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[3].Cs_para5 = m_CStringADAdjust_Ia_5;
		Line2[3].b_paraOK = m_boolADAdjust_Ia_OK;

		Line2[4].f_para1 = m_floatADAdjust_Ib_1 ;
		Line2[4].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[4].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[4].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[4].Cs_para5 =m_CStringADAdjust_Ib_5;
		Line2[4].b_paraOK = m_boolADAdjust_Ib_OK;

		Line2[5].f_para1 =m_floatADAdjust_Ic_1 ;
		Line2[5].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[5].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[5].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[5].Cs_para5 =m_CStringADAdjust_Ic_5;
		Line2[5].b_paraOK = m_boolADAdjust_Ic_OK;

		Line2[0].Index++;
	}


		Line1[0].Index=0;
		//////////////////////////////////////////////////////////////////////////
		//           save DC   parameter
		//////////////////////////////////////////////////////////////////////////
	//VOTAGE
		DC[0].f_para1 = m_floatADAdjust_V_DC1_1;
		DC[0].Cs_para2 = m_CStringADAdjust_V_DC1_2;
		DC[0].Cs_para3 = m_CStringADAdjust_V_DC1_3;
		DC[0].Cs_para4 = m_CStringADAdjust_V_DC1_4;
		DC[0].Cs_para5 = m_CStringADAdjust_V_DC1_5;
		DC[0].b_paraOK = m_boolADAdjust_V_DC1_OK;

		DC[1].f_para1 = m_floatADAdjust_V_DC2_1;
		DC[1].Cs_para2 = m_CStringADAdjust_V_DC2_2;
		DC[1].Cs_para3 = m_CStringADAdjust_V_DC2_3;
		DC[1].Cs_para4 = m_CStringADAdjust_V_DC2_4;
		DC[1].Cs_para5 = m_CStringADAdjust_V_DC2_5;
		DC[1].b_paraOK = m_boolADAdjust_V_DC2_OK;

		DC[2].f_para1 = m_floatADAdjust_V_DC3_1;
		DC[2].Cs_para2 = m_CStringADAdjust_V_DC3_2;
		DC[2].Cs_para3 = m_CStringADAdjust_V_DC3_3;
		DC[2].Cs_para4 = m_CStringADAdjust_V_DC3_4;
		DC[2].Cs_para5 = m_CStringADAdjust_V_DC3_5;
		DC[2].b_paraOK = m_boolADAdjust_V_DC3_OK;

		DC[3].f_para1 = m_floatADAdjust_V_DC4_1;
		DC[3].Cs_para2 = m_CStringADAdjust_V_DC4_2;
		DC[3].Cs_para3 = m_CStringADAdjust_V_DC4_3;
		DC[3].Cs_para4 = m_CStringADAdjust_V_DC4_4;
		DC[3].Cs_para5 = m_CStringADAdjust_V_DC4_5;
		DC[3].b_paraOK = m_boolADAdjust_V_DC4_OK;
	// CURRENT
		DC[4].f_para1 = m_floatADAdjust_C_DC1_1;
		DC[4].Cs_para2 = m_CStringADAdjust_C_DC1_2;
		DC[4].Cs_para3 = m_CStringADAdjust_C_DC1_3;
		DC[4].Cs_para4 = m_CStringADAdjust_C_DC1_4;
		DC[4].Cs_para5 = m_CStringADAdjust_C_DC1_5;
		DC[4].b_paraOK = m_boolADAdjust_C_DC1_OK;

		DC[5].f_para1 = m_floatADAdjust_C_DC2_1;
		DC[5].Cs_para2 = m_CStringADAdjust_C_DC2_2;
		DC[5].Cs_para3 = m_CStringADAdjust_C_DC2_3;
		DC[5].Cs_para4 = m_CStringADAdjust_C_DC2_4;
		DC[5].Cs_para5 = m_CStringADAdjust_C_DC2_5;
		DC[5].b_paraOK = m_boolADAdjust_C_DC2_OK;

		DC[6].f_para1 = m_floatADAdjust_C_DC3_1;
		DC[6].Cs_para2 = m_CStringADAdjust_C_DC3_2;
		DC[6].Cs_para3 = m_CStringADAdjust_C_DC3_3;
		DC[6].Cs_para4 = m_CStringADAdjust_C_DC3_4;
		DC[6].Cs_para5 = m_CStringADAdjust_C_DC3_5;
		DC[6].b_paraOK = m_boolADAdjust_C_DC3_OK;

		DC[7].f_para1 = m_floatADAdjust_C_DC4_1;
		DC[7].Cs_para2 = m_CStringADAdjust_C_DC4_2;
		DC[7].Cs_para3 = m_CStringADAdjust_C_DC4_3;
		DC[7].Cs_para4 = m_CStringADAdjust_C_DC4_4;
		DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
		DC[7].b_paraOK = m_boolADAdjust_C_DC4_OK;


	}

	if(Function_ID == IDC_RADIO_ADAdjust_Channel_line2)    //line2 
	{
	//////////////////////////////////////////////////////////////////////////
	//           save Line 1  parameter
    //////////////////////////////////////////////////////////////////////////
		if(Line1[0].Index ==0)
		{
			Line1[0].f_para1  = m_floatADAdjust_Ua_1 ;
			Line1[0].Cs_para2 = m_CStringADAdjust_Ua_2;
			Line1[0].Cs_para3 = m_CStringADAdjust_Ua_3;
			Line1[0].Cs_para4 = m_CStringADAdjust_Ua_4;
			Line1[0].Cs_para5 = m_CStringADAdjust_Ua_5;
			Line1[0].b_paraOK = m_boolADAdjust_Ua_OK;

			Line1[1].f_para1 = m_floatADAdjust_Ub_1 ;
			Line1[1].Cs_para2 = m_CStringADAdjust_Ua_2;
			Line1[1].Cs_para3 = m_CStringADAdjust_Ua_3;
			Line1[1].Cs_para4 = m_CStringADAdjust_Ua_4;
			Line1[1].Cs_para5 = m_CStringADAdjust_Ub_5;
			Line1[1].b_paraOK = m_boolADAdjust_Ub_OK;

			Line1[2].f_para1 = m_floatADAdjust_Uc_1 ;
			Line1[2].Cs_para2 = m_CStringADAdjust_Ua_2;
			Line1[2].Cs_para3 = m_CStringADAdjust_Ua_3;
			Line1[2].Cs_para4 = m_CStringADAdjust_Ua_4;
			Line1[2].Cs_para5 = m_CStringADAdjust_Uc_5;
			Line1[2].b_paraOK = m_boolADAdjust_Uc_OK;

			Line1[3].f_para1 = m_floatADAdjust_Ia_1 ;
			Line1[3].Cs_para2 = m_CStringADAdjust_Ua_2;
			Line1[3].Cs_para3 = m_CStringADAdjust_Ua_3;
			Line1[3].Cs_para4 = m_CStringADAdjust_Ua_4;
			Line1[3].Cs_para5 = m_CStringADAdjust_Ia_5;
			Line1[3].b_paraOK = m_boolADAdjust_Ia_OK;

			Line1[4].f_para1 = m_floatADAdjust_Ib_1 ;
			Line1[4].Cs_para2 = m_CStringADAdjust_Ua_2;
			Line1[4].Cs_para3 = m_CStringADAdjust_Ua_3;
			Line1[4].Cs_para4 = m_CStringADAdjust_Ua_4;
			Line1[4].Cs_para5 =m_CStringADAdjust_Ib_5;
			Line1[4].b_paraOK = m_boolADAdjust_Ib_OK;

			Line1[5].f_para1 =m_floatADAdjust_Ic_1 ;
			Line1[5].Cs_para2 = m_CStringADAdjust_Ua_2;
			Line1[5].Cs_para3 = m_CStringADAdjust_Ua_3;
			Line1[5].Cs_para4 = m_CStringADAdjust_Ua_4;
			Line1[5].Cs_para5 =m_CStringADAdjust_Ic_5;
			Line1[5].b_paraOK = m_boolADAdjust_Ic_OK;

			Line1[0].Index++;
		}

			Line2[0].Index=0;
			//////////////////////////////////////////////////////////////////////////
			//           save DC   parameter
			//////////////////////////////////////////////////////////////////////////
		//VOTAGE
			DC[0].f_para1 = m_floatADAdjust_V_DC1_1;
			DC[0].Cs_para2 = m_CStringADAdjust_V_DC1_2;
			DC[0].Cs_para3 = m_CStringADAdjust_V_DC1_3;
			DC[0].Cs_para4 = m_CStringADAdjust_V_DC1_4;
			DC[0].Cs_para5 = m_CStringADAdjust_V_DC1_5;
			DC[0].b_paraOK = m_boolADAdjust_V_DC1_OK;

			DC[1].f_para1 = m_floatADAdjust_V_DC2_1;
			DC[1].Cs_para2 = m_CStringADAdjust_V_DC2_2;
			DC[1].Cs_para3 = m_CStringADAdjust_V_DC2_3;
			DC[1].Cs_para4 = m_CStringADAdjust_V_DC2_4;
			DC[1].Cs_para5 = m_CStringADAdjust_V_DC2_5;
			DC[1].b_paraOK = m_boolADAdjust_V_DC2_OK;

			DC[2].f_para1 = m_floatADAdjust_V_DC3_1;
			DC[2].Cs_para2 = m_CStringADAdjust_V_DC3_2;
			DC[2].Cs_para3 = m_CStringADAdjust_V_DC3_3;
			DC[2].Cs_para4 = m_CStringADAdjust_V_DC3_4;
			DC[2].Cs_para5 = m_CStringADAdjust_V_DC3_5;
			DC[2].b_paraOK = m_boolADAdjust_V_DC3_OK;

			DC[3].f_para1 = m_floatADAdjust_V_DC4_1;
			DC[3].Cs_para2 = m_CStringADAdjust_V_DC4_2;
			DC[3].Cs_para3 = m_CStringADAdjust_V_DC4_3;
			DC[3].Cs_para4 = m_CStringADAdjust_V_DC4_4;
			DC[3].Cs_para5 = m_CStringADAdjust_V_DC4_5;
			DC[3].b_paraOK = m_boolADAdjust_V_DC4_OK;
		// CURRENT
			DC[4].f_para1 = m_floatADAdjust_C_DC1_1;
			DC[4].Cs_para2 = m_CStringADAdjust_C_DC1_2;
			DC[4].Cs_para3 = m_CStringADAdjust_C_DC1_3;
			DC[4].Cs_para4 = m_CStringADAdjust_C_DC1_4;
			DC[4].Cs_para5 = m_CStringADAdjust_C_DC1_5;
			DC[4].b_paraOK = m_boolADAdjust_C_DC1_OK;

			DC[5].f_para1 = m_floatADAdjust_C_DC2_1;
			DC[5].Cs_para2 = m_CStringADAdjust_C_DC2_2;
			DC[5].Cs_para3 = m_CStringADAdjust_C_DC2_3;
			DC[5].Cs_para4 = m_CStringADAdjust_C_DC2_4;
			DC[5].Cs_para5 = m_CStringADAdjust_C_DC2_5;
			DC[5].b_paraOK = m_boolADAdjust_C_DC2_OK;

			DC[6].f_para1 = m_floatADAdjust_C_DC3_1;
			DC[6].Cs_para2 = m_CStringADAdjust_C_DC3_2;
			DC[6].Cs_para3 = m_CStringADAdjust_C_DC3_3;
			DC[6].Cs_para4 = m_CStringADAdjust_C_DC3_4;
			DC[6].Cs_para5 = m_CStringADAdjust_C_DC3_5;
			DC[6].b_paraOK = m_boolADAdjust_C_DC3_OK;

			DC[7].f_para1 = m_floatADAdjust_C_DC4_1;
			DC[7].Cs_para2 = m_CStringADAdjust_C_DC4_2;
			DC[7].Cs_para3 = m_CStringADAdjust_C_DC4_3;
			DC[7].Cs_para4 = m_CStringADAdjust_C_DC4_4;
			DC[7].Cs_para5 = m_CStringADAdjust_C_DC4_5;
			DC[7].b_paraOK = m_boolADAdjust_C_DC4_OK;

	}

	if(Function_ID == IDC_RADIO_ADAdjust_Channel_DC)             // when DC
	{
			//////////////////////////////////////////////////////////////////////////
	//           save Line 2  parameter
    //////////////////////////////////////////////////////////////////////////
 if(Line2[0].Index==0)
	{
		Line2[0].f_para1  = m_floatADAdjust_Ua_1 ;
		Line2[0].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[0].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[0].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[0].Cs_para5 = m_CStringADAdjust_Ua_5;
		Line2[0].b_paraOK = m_boolADAdjust_Ua_OK;

		Line2[1].f_para1 = m_floatADAdjust_Ub_1 ;
		Line2[1].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[1].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[1].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[1].Cs_para5 = m_CStringADAdjust_Ub_5;
		Line2[1].b_paraOK = m_boolADAdjust_Ub_OK;

		Line2[2].f_para1 = m_floatADAdjust_Uc_1 ;
		Line2[2].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[2].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[2].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[2].Cs_para5 = m_CStringADAdjust_Uc_5;
		Line2[2].b_paraOK = m_boolADAdjust_Uc_OK;

		Line2[3].f_para1 = m_floatADAdjust_Ia_1 ;
		Line2[3].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[3].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[3].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[3].Cs_para5 = m_CStringADAdjust_Ia_5;
		Line2[3].b_paraOK = m_boolADAdjust_Ia_OK;

		Line2[4].f_para1 = m_floatADAdjust_Ib_1 ;
		Line2[4].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[4].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[4].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[4].Cs_para5 =m_CStringADAdjust_Ib_5;
		Line2[4].b_paraOK = m_boolADAdjust_Ib_OK;

		Line2[5].f_para1 =m_floatADAdjust_Ic_1 ;
		Line2[5].Cs_para2 = m_CStringADAdjust_Ua_2;
		Line2[5].Cs_para3 = m_CStringADAdjust_Ua_3;
		Line2[5].Cs_para4 = m_CStringADAdjust_Ua_4;
		Line2[5].Cs_para5 =m_CStringADAdjust_Ic_5;
		Line2[5].b_paraOK = m_boolADAdjust_Ic_OK;

		Line2[0].Index++;
	}

	//////////////////////////////////////////////////////////////////////////
	//           save Line1  parameter
    //////////////////////////////////////////////////////////////////////////
if(Line1[0].Index ==0)
{
	Line1[0].f_para1  = m_floatADAdjust_Ua_1 ;
	Line1[0].Cs_para2 = m_CStringADAdjust_Ua_2;
	Line1[0].Cs_para3 = m_CStringADAdjust_Ua_3;
	Line1[0].Cs_para4 = m_CStringADAdjust_Ua_4;
	Line1[0].Cs_para5 = m_CStringADAdjust_Ua_5;
	Line1[0].b_paraOK = m_boolADAdjust_Ua_OK;

	Line1[1].f_para1 = m_floatADAdjust_Ub_1 ;
	Line1[1].Cs_para2 = m_CStringADAdjust_Ua_2;
	Line1[1].Cs_para3 = m_CStringADAdjust_Ua_3;
	Line1[1].Cs_para4 = m_CStringADAdjust_Ua_4;
	Line1[1].Cs_para5 = m_CStringADAdjust_Ub_5;
	Line1[1].b_paraOK = m_boolADAdjust_Ub_OK;

	Line1[2].f_para1 = m_floatADAdjust_Uc_1 ;
	Line1[2].Cs_para2 = m_CStringADAdjust_Ua_2;
	Line1[2].Cs_para3 = m_CStringADAdjust_Ua_3;
	Line1[2].Cs_para4 = m_CStringADAdjust_Ua_4;
	Line1[2].Cs_para5 = m_CStringADAdjust_Uc_5;
	Line1[2].b_paraOK = m_boolADAdjust_Uc_OK;

	Line1[3].f_para1 = m_floatADAdjust_Ia_1 ;
	Line1[3].Cs_para2 = m_CStringADAdjust_Ua_2;
	Line1[3].Cs_para3 = m_CStringADAdjust_Ua_3;
	Line1[3].Cs_para4 = m_CStringADAdjust_Ua_4;
	Line1[3].Cs_para5 = m_CStringADAdjust_Ia_5;
	Line1[3].b_paraOK = m_boolADAdjust_Ia_OK;

	Line1[4].f_para1 = m_floatADAdjust_Ib_1 ;
	Line1[4].Cs_para2 = m_CStringADAdjust_Ua_2;
	Line1[4].Cs_para3 = m_CStringADAdjust_Ua_3;
	Line1[4].Cs_para4 = m_CStringADAdjust_Ua_4;
	Line1[4].Cs_para5 =m_CStringADAdjust_Ib_5;
	Line1[4].b_paraOK = m_boolADAdjust_Ib_OK;

	Line1[5].f_para1 =m_floatADAdjust_Ic_1 ;
	Line1[5].Cs_para2 = m_CStringADAdjust_Ua_2;
	Line1[5].Cs_para3 = m_CStringADAdjust_Ua_3;
	Line1[5].Cs_para4 = m_CStringADAdjust_Ua_4;
	Line1[5].Cs_para5 =m_CStringADAdjust_Ic_5;
	Line1[5].b_paraOK = m_boolADAdjust_Ic_OK;

	Line1[0].Index++;
}

	}
*/
	Function_ID =0;
//	MessageBox("dodataexchange2");

}


BEGIN_MESSAGE_MAP(Dlg_ADAdjust1, CDialog)
	//{{AFX_MSG_MAP(Dlg_ADAdjust1)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_ACChannel, OnRADIOADAdjustACChannel)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_Channel, OnRADIOADAdjustChannel)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_Channel_line2, OnRADIOADAdjustChannelline2)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_Channel_DC, OnRADIOADAdjustChannelDC)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_ACChannel_Ub, OnRADIOADAdjustACChannelUb)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_ACChannel_Uc, OnRADIOADAdjustACChannelUc)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_ACChannel_Ia, OnRADIOADAdjustACChannelIa)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_ACChannel_Ib, OnRADIOADAdjustACChannelIb)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_ACChannel_Ic, OnRADIOADAdjustACChannelIc)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel, OnRADIOADAdjustDCChannel)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC1, OnRADIOADAdjustDCChannelCDC1)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC2, OnRADIOADAdjustDCChannelCDC2)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC3, OnRADIOADAdjustDCChannelCDC3)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC4, OnRADIOADAdjustDCChannelCDC4)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_VDC2, OnRADIOADAdjustDCChannelVDC2)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_VDC3, OnRADIOADAdjustDCChannelVDC3)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_VDC4, OnRADIOADAdjustDCChannelVDC4)
	ON_EN_KILLFOCUS(IDC_EDIT_ADAdjust_Ua_1, OnKillfocusEDITADAdjustUa1)
	ON_EN_KILLFOCUS(IDC_EDIT_ADAdjust_Ub_1, OnKillfocusEDITADAdjustUb1)
	ON_EN_KILLFOCUS(IDC_EDIT_ADAdjust_Uc_1, OnKillfocusEDITADAdjustUc1)
	ON_EN_KILLFOCUS(IDC_EDIT_ADAdjust_Ia_1, OnKillfocusEDITADAdjustIa1)
	ON_EN_KILLFOCUS(IDC_EDIT_ADAdjust_Ib_1, OnKillfocusEDITADAdjustIb1)
	ON_EN_KILLFOCUS(IDC_EDIT_ADAdjust_Ic_1, OnKillfocusEDITADAdjustIc1)
	ON_BN_CLICKED(IDC_BUTTON_ADAdjust_Apply, OnBUTTONADAdjustApply)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ADAdjust_NewParApply, OnBUTTONADAdjustNewParApply)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC5, OnRADIOADAdjustDCChannelCDC5)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC6, OnRADIOADAdjustDCChannelCDC6)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC7, OnRADIOADAdjustDCChannelCDC7)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC8, OnRADIOADAdjustDCChannelCDC8)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel5, OnRADIOADAdjustDCChannel5)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_VDC6, OnRADIOADAdjustDCChannelVDC6)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_VDC7, OnRADIOADAdjustDCChannelVDC7)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_VDC8, OnRADIOADAdjustDCChannelVDC8)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC9, OnRADIOADAdjustDCChannelCDC9)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC10, OnRADIOADAdjustDCChannelCDC10)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC11, OnRADIOADAdjustDCChannelCDC11)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC12, OnRADIOADAdjustDCChannelCDC12)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC13, OnRADIOADAdjustDCChannelCDC13)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC14, OnRADIOADAdjustDCChannelCDC14)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC15, OnRADIOADAdjustDCChannelCDC15)
	ON_BN_CLICKED(IDC_RADIO_ADAdjust_DCChannel_CDC16, OnRADIOADAdjustDCChannelCDC16)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADAdjust1 message handlers

void Dlg_ADAdjust1::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
//MessageBox("show window");
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();

//////////////////////////////////////////////////////////////////////////
		UpdateData(TRUE);
//////////////////////////////////////////////////////////////////////////
	//  Line1 initialization
	for(int tt=0;tt<6;tt++)
	{
		Line1[tt].Index =tt;
		Line1[tt].f_para1 =57.74;
		if(tt>2)
		{
			Line1[tt].f_para1 =5;
			if(pParent->Current_Style==1)
			Line1[tt].f_para1 =1;
		}
		Line1[tt].Cs_para2 ="0H";
		Line1[tt].Cs_para3 ="0H";
		Line1[tt].Cs_para4 ="0H";
		if(pParent->DIM_public==8192)
		Line1[tt].Cs_para5 ="2000H";
		else if(pParent->DIM_public==16384)
		Line1[tt].Cs_para5 ="4000H";
		Line1[tt].b_paraOK =FALSE;
	

	//////////////////////////////////////////////////////////////////////////
	//  Line2 initialization

		Line2[tt].Index =tt;
		Line2[tt].f_para1 =57.74;
		if(tt>2)
		{
			Line2[tt].f_para1 =5;
			if(pParent->Current_Style==1)
			Line2[tt].f_para1 =1;
		}
		Line2[tt].Cs_para2 ="0H";
		Line2[tt].Cs_para3 ="0H";
		Line2[tt].Cs_para4 ="0H";
		if(pParent->DIM_public==8192)
		Line2[tt].Cs_para5 ="2000H";
		else if(pParent->DIM_public==16384)
		Line2[tt].Cs_para5 ="4000H";
		Line2[tt].b_paraOK =FALSE;
	}
	//////////////////////////////////////////////////////////////////////////
	for(int kk=0;kk<24;kk++)
	{
		DC[kk].Index =kk;
		DC[kk].f_para1 =5;
		if(kk>3)
		DC[kk].f_para1 =10;
		DC[kk].Cs_para2 ="0H";
		DC[kk].Cs_para3 ="0H";
		DC[kk].Cs_para4 ="0H";
		if(pParent->DIM_public==8192)
		DC[kk].Cs_para5 ="2000H";
		else if(pParent->DIM_public==16384)
		DC[kk].Cs_para5 ="4000H";
		DC[kk].b_paraOK =FALSE;
	}




//////////////////////////////////////////////////////////////////////////


	m_floatADAdjust_Ua_1 =57.74;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_Ua_5="2000H";
    else if(pParent->DIM_public==16384)
    m_CStringADAdjust_Ua_5="4000H";
	
	m_floatADAdjust_Ub_1 =57.74;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_Ub_5="2000H";
    else if(pParent->DIM_public==16384)
	m_CStringADAdjust_Ub_5="4000H";
	
	m_floatADAdjust_Uc_1 =57.74;
    if(pParent->DIM_public==8192)
	m_CStringADAdjust_Uc_5="2000H";
	else if(pParent->DIM_public==16384)
    m_CStringADAdjust_Uc_5="4000H";

	if(pParent->Current_Style==0)
		m_floatADAdjust_Ia_1 =5;
	else if(pParent->Current_Style==1)
		m_floatADAdjust_Ia_1=1;

	if(pParent->DIM_public==8192)
	m_CStringADAdjust_Ia_5="2000H";
	else if(pParent->DIM_public==16384)
    m_CStringADAdjust_Ia_5="4000H";

	if(pParent->Current_Style==0)
		m_floatADAdjust_Ib_1 =5;
	else if(pParent->Current_Style==1)
		m_floatADAdjust_Ib_1=1;

	if(pParent->DIM_public==8192)
	m_CStringADAdjust_Ib_5="2000H";
    else if(pParent->DIM_public==16384)
    m_CStringADAdjust_Ib_5="4000H";

	if(pParent->Current_Style==0)
		m_floatADAdjust_Ic_1 =5;
	else if(pParent->Current_Style==1)
		m_floatADAdjust_Ic_1=1;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_Ic_5="2000H";
	else if(pParent->DIM_public==16384)
	m_CStringADAdjust_Ic_5="4000H";
	/* 
	m_floatADAdjust_V_DC1_1 =2.5;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_V_DC1_5="2000H";
    else if(pParent->DIM_public==16384)
    m_CStringADAdjust_V_DC1_5="4000H";

	m_floatADAdjust_V_DC2_1 =2.5;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_V_DC2_5="2000H";
    else if(pParent->DIM_public==16384)
    m_CStringADAdjust_V_DC2_5="4000H";
	
	m_floatADAdjust_V_DC3_1 =2.5;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_V_DC3_5="2000H";
    else if(pParent->DIM_public==16384)
    m_CStringADAdjust_V_DC3_5="4000H";

	m_floatADAdjust_V_DC4_1 =2.5;
    if(pParent->DIM_public==8192)
	m_CStringADAdjust_V_DC4_5="2000H";
    else if(pParent->DIM_public==16384)
    m_CStringADAdjust_V_DC4_5="4000H";

	m_floatADAdjust_C_DC1_1 =10;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_C_DC1_5 ="2000H";
	else if(pParent->DIM_public==16384)
    m_CStringADAdjust_C_DC1_5="4000H";
	
	m_floatADAdjust_C_DC2_1 =10;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_C_DC2_5 ="2000H";
	else if(pParent->DIM_public==16384)
	m_CStringADAdjust_C_DC2_5="4000H";

	m_floatADAdjust_C_DC3_1 =10;
	if(pParent->DIM_public==8192)
	m_CStringADAdjust_C_DC3_5 ="2000H";
    else if(pParent->DIM_public==16384)
    m_CStringADAdjust_C_DC3_5 ="4000H";

	m_floatADAdjust_C_DC4_1 =10;
    if(pParent->DIM_public==8192)
	m_CStringADAdjust_C_DC4_5 ="2000H";
	else if(pParent->DIM_public==16384)
    m_CStringADAdjust_C_DC4_5 ="4000H";
	*/
/*
//	m_floatADAdjust_V_DC1_1 =5;
	if(pParent->DIM_public==8192)
		m_CStringADAdjust_V_DC1_5="4000H";
    else if(pParent->DIM_public==16384)
		m_CStringADAdjust_V_DC1_5="8000H";
	
//	m_floatADAdjust_V_DC2_1 =5;
	if(pParent->DIM_public==8192)
		m_CStringADAdjust_V_DC2_5="4000H";
    else if(pParent->DIM_public==16384)
		m_CStringADAdjust_V_DC2_5="8000H";
	
//	m_floatADAdjust_V_DC3_1 =5;
	if(pParent->DIM_public==8192)
		m_CStringADAdjust_V_DC3_5="4000H";
    else if(pParent->DIM_public==16384)
		m_CStringADAdjust_V_DC3_5="8000H";
	
//	m_floatADAdjust_V_DC4_1 =5;
    if(pParent->DIM_public==8192)
		m_CStringADAdjust_V_DC4_5="4000H";
    else if(pParent->DIM_public==16384)
		m_CStringADAdjust_V_DC4_5="8000H";

//	m_floatADAdjust_C_DC1_1 =20;
	if(pParent->DIM_public==8192)
		m_CStringADAdjust_C_DC1_5 ="4000H";
	else if(pParent->DIM_public==16384)
		m_CStringADAdjust_C_DC1_5="8000H";
	
//	m_floatADAdjust_C_DC2_1 =20;
	if(pParent->DIM_public==8192)
		m_CStringADAdjust_C_DC2_5 ="4000H";
	else if(pParent->DIM_public==16384)
		m_CStringADAdjust_C_DC2_5="8000H";
	
//	m_floatADAdjust_C_DC3_1 =20;
	if(pParent->DIM_public==8192)
		m_CStringADAdjust_C_DC3_5 ="4000H";
    else if(pParent->DIM_public==16384)
		m_CStringADAdjust_C_DC3_5 ="8000H";
	
//	m_floatADAdjust_C_DC4_1 =20;
    if(pParent->DIM_public==8192)
		m_CStringADAdjust_C_DC4_5 ="4000H";
	else if(pParent->DIM_public==16384)
    m_CStringADAdjust_C_DC4_5 ="8000H";

	m_CStringADAdjust_C_DC4_2 =m_CStringADAdjust_C_DC4_3 =m_CStringADAdjust_C_DC4_4 ="0H";
	m_CStringADAdjust_C_DC3_2 =m_CStringADAdjust_C_DC3_3 =m_CStringADAdjust_C_DC3_4 ="0H";
	m_CStringADAdjust_C_DC2_2 =m_CStringADAdjust_C_DC2_3 =m_CStringADAdjust_C_DC2_4 ="0H";
	m_CStringADAdjust_C_DC1_2 =m_CStringADAdjust_C_DC1_3 =m_CStringADAdjust_C_DC1_4 ="0H";
*/
//	m_CStringADAdjust_V_DC4_2 =m_CStringADAdjust_V_DC4_3 =m_CStringADAdjust_V_DC4_4 ="0H";
//	m_CStringADAdjust_V_DC3_2 =m_CStringADAdjust_V_DC3_3 =m_CStringADAdjust_V_DC3_4 ="0H";
//	m_CStringADAdjust_V_DC2_2 =m_CStringADAdjust_V_DC2_3 =m_CStringADAdjust_V_DC2_4 ="0H";
//	m_CStringADAdjust_V_DC1_2 =m_CStringADAdjust_V_DC1_3 =m_CStringADAdjust_V_DC1_4 ="0H";

	m_CStringADAdjust_Ua_4 =m_CStringADAdjust_Ua_3=m_CStringADAdjust_Ua_2 ="0H";
	m_CStringADAdjust_Ub_4 =m_CStringADAdjust_Ub_3=m_CStringADAdjust_Ub_2 ="0H";
	m_CStringADAdjust_Uc_4 =m_CStringADAdjust_Uc_3=m_CStringADAdjust_Uc_2 ="0H";
	m_CStringADAdjust_Ia_4 =m_CStringADAdjust_Ia_3=m_CStringADAdjust_Ia_2 ="0H";
	m_CStringADAdjust_Ib_4 =m_CStringADAdjust_Ib_3=m_CStringADAdjust_Ib_2 ="0H";
	m_CStringADAdjust_Ic_4 =m_CStringADAdjust_Ic_3=m_CStringADAdjust_Ic_2 ="0H";
	m_boolADAdjust_Ua_OK =m_boolADAdjust_Ub_OK=m_boolADAdjust_Uc_OK =FALSE;
	m_boolADAdjust_Ia_OK =m_boolADAdjust_Ib_OK=m_boolADAdjust_Ic_OK =FALSE;
	m_boolADAdjust_V_DC1_OK =m_boolADAdjust_V_DC2_OK =m_boolADAdjust_V_DC3_OK =m_boolADAdjust_V_DC4_OK = FALSE;
	m_boolADAdjust_C_DC1_OK =m_boolADAdjust_C_DC2_OK =m_boolADAdjust_C_DC3_OK =m_boolADAdjust_C_DC4_OK = FALSE;
	



	m_nADAdjust_Channel =0;
	m_nADAdjust_ACChannel =0;
	m_nADAdjust_DCChannel =-1;

	UpdateData(FALSE);

	
}

void Dlg_ADAdjust1::OnRADIOADAdjustACChannel() //UA1
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==0 ||m_nADAdjust_Channel==1)
	{
		m_nADAdjust_ACChannel =0;
	//	((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ua_1))->EnableWindow(TRUE);
	}
	else if (m_nADAdjust_Channel==2)
	{
		m_nADAdjust_ACChannel =-1;
	//	((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ua_1))->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustChannel()                     //line1
{
	// TODO: Add your control notification handler code here
	//////////////////////////////////////////////////////////////////////////
	//  Line1 该块完成的工作： 1、保存Line2和 DC 的参数；
	//                         2、装载Line1 的参数；
	//						   3、updatedata；
	//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//    STEP 1    SAVE PARAMETRER
//////////////////////////////////////////////////////////////////////////
	Function_ID = IDC_RADIO_ADAdjust_Channel;
	UpdateData(TRUE);
	
//////////////////////////////////////////////////////////////////////////
//
//  STEP 2
//////////////////////////////////////////////////////////////////////////
	
//UpdateData(TRUE);
	m_nADAdjust_Channel=0;
	m_nADAdjust_DCChannel=-1;
	m_nADAdjust_ACChannel=0;

	m_floatADAdjust_Ua_1 =Line1[0].f_para1;
	m_CStringADAdjust_Ua_2=Line1[0].Cs_para2;
	m_CStringADAdjust_Ua_3=Line1[0].Cs_para3;
	m_CStringADAdjust_Ua_4=Line1[0].Cs_para4;
	m_CStringADAdjust_Ua_5=Line1[0].Cs_para5;
	m_boolADAdjust_Ua_OK  =Line1[0].b_paraOK;

	m_floatADAdjust_Ub_1 =Line1[1].f_para1;
	m_CStringADAdjust_Ub_2=Line1[1].Cs_para2;
	m_CStringADAdjust_Ub_3=Line1[1].Cs_para3;
	m_CStringADAdjust_Ub_4=Line1[1].Cs_para4;
	m_CStringADAdjust_Ub_5=Line1[1].Cs_para5;
	m_boolADAdjust_Ub_OK  =Line1[1].b_paraOK;

	m_floatADAdjust_Uc_1 =Line1[2].f_para1;
	m_CStringADAdjust_Uc_2=Line1[2].Cs_para2;
	m_CStringADAdjust_Uc_3=Line1[2].Cs_para3;
	m_CStringADAdjust_Uc_4=Line1[2].Cs_para4;
	m_CStringADAdjust_Uc_5=Line1[2].Cs_para5;
	m_boolADAdjust_Uc_OK  =Line1[2].b_paraOK;

	m_floatADAdjust_Ia_1 =Line1[3].f_para1;
	m_CStringADAdjust_Ia_2=Line1[3].Cs_para2;
	m_CStringADAdjust_Ia_3=Line1[3].Cs_para3;
	m_CStringADAdjust_Ia_4=Line1[3].Cs_para4;
	m_CStringADAdjust_Ia_5=Line1[3].Cs_para5;
	m_boolADAdjust_Ia_OK  =Line1[3].b_paraOK;

	m_floatADAdjust_Ib_1 =Line1[4].f_para1;
	m_CStringADAdjust_Ib_2=Line1[4].Cs_para2;
	m_CStringADAdjust_Ib_3=Line1[4].Cs_para3;
	m_CStringADAdjust_Ib_4=Line1[4].Cs_para4;
	m_CStringADAdjust_Ib_5=Line1[4].Cs_para5;
	m_boolADAdjust_Ib_OK  =Line1[4].b_paraOK;

	m_floatADAdjust_Ic_1 =Line1[5].f_para1;
	m_CStringADAdjust_Ic_2=Line1[5].Cs_para2;
	m_CStringADAdjust_Ic_3=Line1[5].Cs_para3;
	m_CStringADAdjust_Ic_4=Line1[5].Cs_para4;
	m_CStringADAdjust_Ic_5=Line1[5].Cs_para5;
	m_boolADAdjust_Ic_OK  =Line1[5].b_paraOK;
	


//////////////////////////////////////////////////////////////////////////
//               start
//////////////////////////////////////////////////////////////////////////
/*
	    if((((CHECK_STATUS &0X01)==0X01)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X040)==0X040)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ua_OK =TRUE;
		else
			m_boolADAdjust_Ua_OK=FALSE;
		if((((CHECK_STATUS &0X02)==0X02)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X080)==0X080)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ub_OK =TRUE;
		else
			m_boolADAdjust_Ub_OK=FALSE;
		if((((CHECK_STATUS &0X04)==0X04)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X100)==0X100)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Uc_OK =TRUE;
		else
			m_boolADAdjust_Uc_OK=FALSE;
		if((((CHECK_STATUS &0X08)==0X08)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X200)==0X200)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ia_OK =TRUE;
		else
			m_boolADAdjust_Ia_OK=FALSE;
		if((((CHECK_STATUS &0X10)==0X10)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X400)==0X400)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ib_OK =TRUE;
		else
			m_boolADAdjust_Ib_OK=FALSE;

		if((((CHECK_STATUS &0X20)==0X20)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X800)==0X800)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ic_OK =TRUE;
		else
			m_boolADAdjust_Ic_OK=FALSE;

		if((CHECK_STATUS &0X1000)==0X1000)
			m_boolADAdjust_V_DC1_OK =TRUE;
		else
			m_boolADAdjust_V_DC1_OK=FALSE;
		if((CHECK_STATUS &0X2000)==0X2000)
			m_boolADAdjust_V_DC2_OK =TRUE;
		else
			m_boolADAdjust_V_DC2_OK=FALSE;
		if((CHECK_STATUS &0X4000)==0X4000)
			m_boolADAdjust_V_DC3_OK =TRUE;
		else
			m_boolADAdjust_V_DC3_OK=FALSE;
		if((CHECK_STATUS &0X8000)==0X8000)
			m_boolADAdjust_V_DC4_OK =TRUE;
		else
			m_boolADAdjust_V_DC4_OK=FALSE;
		if((CHECK_STATUS &0X10000)==0X10000)
			m_boolADAdjust_C_DC1_OK =TRUE;
		else
			m_boolADAdjust_C_DC1_OK=FALSE;
		if((CHECK_STATUS &0X20000)==0X20000)
			m_boolADAdjust_C_DC2_OK =TRUE;
		else
			m_boolADAdjust_C_DC2_OK=FALSE;
		if((CHECK_STATUS &0X40000)==0X40000)
			m_boolADAdjust_C_DC3_OK =TRUE;
		else
			m_boolADAdjust_C_DC3_OK=FALSE;
		if((CHECK_STATUS &0X80000)==0X80000)
			m_boolADAdjust_C_DC4_OK =TRUE;
		else
			m_boolADAdjust_C_DC4_OK=FALSE;
*/		

//////////////////////////////////////////////////////////////////////////
//              end
//////////////////////////////////////////////////////////////////////////
	/*
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ua_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ub_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Uc_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ia_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ib_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ic_1))->EnableWindow(TRUE);
*/

	UpdateData(FALSE);

}

void Dlg_ADAdjust1::OnRADIOADAdjustChannelline2()              //LINE2
{
	// TODO: Add your control notification handler code here
	//////////////////////////////////////////////////////////////////////////
	//  Line2 该块完成的工作： 1、保存Line1和 DC 的参数；
	//                         2、装载Line2 的参数；
	//						   3、updatedata；
	//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//    STEP 1    SAVE PARAMETRER
//////////////////////////////////////////////////////////////////////////

//BOOL Click =FALSE;
	Function_ID == IDC_RADIO_ADAdjust_Channel_line2;

//////////////////////////////////////////////////////////////////////////
//
//  STEP 2
//////////////////////////////////////////////////////////////////////////
	UpdateData(TRUE);
	
	m_nADAdjust_Channel=1;
	m_nADAdjust_ACChannel=0;
	m_nADAdjust_DCChannel=-1;

	m_floatADAdjust_Ua_1 =Line2[0].f_para1;
	m_CStringADAdjust_Ua_2=Line2[0].Cs_para2;
	m_CStringADAdjust_Ua_3=Line2[0].Cs_para3;
	m_CStringADAdjust_Ua_4=Line2[0].Cs_para4;
	m_CStringADAdjust_Ua_5=Line2[0].Cs_para5;
	m_boolADAdjust_Ua_OK  =Line2[0].b_paraOK;

	m_floatADAdjust_Ub_1 =Line2[1].f_para1;
	m_CStringADAdjust_Ub_2=Line2[1].Cs_para2;
	m_CStringADAdjust_Ub_3=Line2[1].Cs_para3;
	m_CStringADAdjust_Ub_4=Line2[1].Cs_para4;
	m_CStringADAdjust_Ub_5=Line2[1].Cs_para5;
	m_boolADAdjust_Ub_OK  =Line2[1].b_paraOK;

	m_floatADAdjust_Uc_1 =Line2[2].f_para1;
	m_CStringADAdjust_Uc_2=Line2[2].Cs_para2;
	m_CStringADAdjust_Uc_3=Line2[2].Cs_para3;
	m_CStringADAdjust_Uc_4=Line2[2].Cs_para4;
	m_CStringADAdjust_Uc_5=Line2[2].Cs_para5;
	m_boolADAdjust_Uc_OK  =Line2[2].b_paraOK;

	m_floatADAdjust_Ia_1 =Line2[3].f_para1;
	m_CStringADAdjust_Ia_2=Line2[3].Cs_para2;
	m_CStringADAdjust_Ia_3=Line2[3].Cs_para3;
	m_CStringADAdjust_Ia_4=Line2[3].Cs_para4;
	m_CStringADAdjust_Ia_5=Line2[3].Cs_para5;
	m_boolADAdjust_Ia_OK  =Line2[3].b_paraOK;

	m_floatADAdjust_Ib_1 =Line2[4].f_para1;
	m_CStringADAdjust_Ib_2=Line2[4].Cs_para2;
	m_CStringADAdjust_Ib_3=Line2[4].Cs_para3;
	m_CStringADAdjust_Ib_4=Line2[4].Cs_para4;
	m_CStringADAdjust_Ib_5=Line2[4].Cs_para5;
	m_boolADAdjust_Ib_OK  =Line2[4].b_paraOK;

	m_floatADAdjust_Ic_1 =Line2[5].f_para1;
	m_CStringADAdjust_Ic_2=Line2[5].Cs_para2;
	m_CStringADAdjust_Ic_3=Line2[5].Cs_para3;
	m_CStringADAdjust_Ic_4=Line2[5].Cs_para4;
	m_CStringADAdjust_Ic_5=Line2[5].Cs_para5;
	m_boolADAdjust_Ic_OK  =Line2[5].b_paraOK;


//////////////////////////////////////////////////////////////////////////
//               start
//////////////////////////////////////////////////////////////////////////
/*
		if((((CHECK_STATUS &0X01)==0X01)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X040)==0X040)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ua_OK =TRUE;
		else
			m_boolADAdjust_Ua_OK=FALSE;
		if((((CHECK_STATUS &0X02)==0X02)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X080)==0X080)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ub_OK =TRUE;
		else
			m_boolADAdjust_Ub_OK=FALSE;
		if((((CHECK_STATUS &0X04)==0X04)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X100)==0X100)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Uc_OK =TRUE;
		else
			m_boolADAdjust_Uc_OK=FALSE;
		if((((CHECK_STATUS &0X08)==0X08)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X200)==0X200)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ia_OK =TRUE;
		else
			m_boolADAdjust_Ia_OK=FALSE;
		if((((CHECK_STATUS &0X10)==0X10)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X400)==0X400)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ib_OK =TRUE;
		else
			m_boolADAdjust_Ib_OK=FALSE;

		if((((CHECK_STATUS &0X20)==0X20)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X800)==0X800)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ic_OK =TRUE;
		else
			m_boolADAdjust_Ic_OK=FALSE;

		if((CHECK_STATUS &0X1000)==0X1000)
			m_boolADAdjust_V_DC1_OK =TRUE;
		else
			m_boolADAdjust_V_DC1_OK=FALSE;
		if((CHECK_STATUS &0X2000)==0X2000)
			m_boolADAdjust_V_DC2_OK =TRUE;
		else
			m_boolADAdjust_V_DC2_OK=FALSE;
		if((CHECK_STATUS &0X4000)==0X4000)
			m_boolADAdjust_V_DC3_OK =TRUE;
		else
			m_boolADAdjust_V_DC3_OK=FALSE;
		if((CHECK_STATUS &0X8000)==0X8000)
			m_boolADAdjust_V_DC4_OK =TRUE;
		else
			m_boolADAdjust_V_DC4_OK=FALSE;
		if((CHECK_STATUS &0X10000)==0X10000)
			m_boolADAdjust_C_DC1_OK =TRUE;
		else
			m_boolADAdjust_C_DC1_OK=FALSE;
		if((CHECK_STATUS &0X20000)==0X20000)
			m_boolADAdjust_C_DC2_OK =TRUE;
		else
			m_boolADAdjust_C_DC2_OK=FALSE;
		if((CHECK_STATUS &0X40000)==0X40000)
			m_boolADAdjust_C_DC3_OK =TRUE;
		else
			m_boolADAdjust_C_DC3_OK=FALSE;
		if((CHECK_STATUS &0X80000)==0X80000)
			m_boolADAdjust_C_DC4_OK =TRUE;
		else
			m_boolADAdjust_C_DC4_OK=FALSE;
		
*/
//////////////////////////////////////////////////////////////////////////
//              end
//////////////////////////////////////////////////////////////////////////
	/*
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ua_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ub_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Uc_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ia_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ib_1))->EnableWindow(TRUE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ic_1))->EnableWindow(TRUE);
*/
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustChannelDC()   //DC
{
	// TODO: Add your control notification handler code here
	//////////////////////////////////////////////////////////////////////////
	//  DC该块完成的工作： 1、保存Line2和 line1 的参数；
	//                         2、装载dc 的参数；
	//						   3、updatedata；
	//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//    STEP 1    SAVE PARAMETRER
//////////////////////////////////////////////////////////////////////////
	Function_ID = IDC_RADIO_ADAdjust_Channel_DC;
	
   // Function_ID = IDC_RADIO_ADAdjust_DCChannel2
	UpdateData(TRUE);

   

//////////////////////////////////////////////////////////////////////////
//
//  STEP 2
//////////////////////////////////////////////////////////////////////////
	
	m_nADAdjust_Channel=2;
	m_nADAdjust_DCChannel=0;
	m_nADAdjust_ACChannel=-1;
/*	((CButton*)GetDlgItem(IDC_RADIO_ADAdjust_DCChannel))->SetCheck(TRUE);
    ((CButton*)GetDlgItem(IDC_RADIO_ADAdjust_DCChannel))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_ADAdjust_DCChannel))->SetCheck(TRUE);
	m_nADAdjust_DCChannel=0;
	*/   
/*
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ua_1))->EnableWindow(FALSE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ub_1))->EnableWindow(FALSE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Uc_1))->EnableWindow(FALSE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ia_1))->EnableWindow(FALSE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ib_1))->EnableWindow(FALSE);
((CButton*)GetDlgItem(IDC_EDIT_ADAdjust_Ic_1))->EnableWindow(FALSE);
*/
//////////////////////////////////////////////////////////////////////////
//               start
//////////////////////////////////////////////////////////////////////////
/*
		if((((CHECK_STATUS &0X01)==0X01)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X040)==0X040)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ua_OK =TRUE;
		else
			m_boolADAdjust_Ua_OK=FALSE;
		if((((CHECK_STATUS &0X02)==0X02)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X080)==0X080)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ub_OK =TRUE;
		else
			m_boolADAdjust_Ub_OK=FALSE;
		if((((CHECK_STATUS &0X04)==0X04)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X100)==0X100)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Uc_OK =TRUE;
		else
			m_boolADAdjust_Uc_OK=FALSE;
		if((((CHECK_STATUS &0X08)==0X08)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X200)==0X200)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ia_OK =TRUE;
		else
			m_boolADAdjust_Ia_OK=FALSE;
		if((((CHECK_STATUS &0X10)==0X10)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X400)==0X400)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ib_OK =TRUE;
		else
			m_boolADAdjust_Ib_OK=FALSE;

		if((((CHECK_STATUS &0X20)==0X20)&&m_nADAdjust_Channel==0)||(((CHECK_STATUS &0X800)==0X800)&&m_nADAdjust_Channel==1))
			m_boolADAdjust_Ic_OK =TRUE;
		else
			m_boolADAdjust_Ic_OK=FALSE;

		if((CHECK_STATUS &0X1000)==0X1000)
			m_boolADAdjust_V_DC1_OK =TRUE;
		else
			m_boolADAdjust_V_DC1_OK=FALSE;
		if((CHECK_STATUS &0X2000)==0X2000)
			m_boolADAdjust_V_DC2_OK =TRUE;
		else
			m_boolADAdjust_V_DC2_OK=FALSE;
		if((CHECK_STATUS &0X4000)==0X4000)
			m_boolADAdjust_V_DC3_OK =TRUE;
		else
			m_boolADAdjust_V_DC3_OK=FALSE;
		if((CHECK_STATUS &0X8000)==0X8000)
			m_boolADAdjust_V_DC4_OK =TRUE;
		else
			m_boolADAdjust_V_DC4_OK=FALSE;
		if((CHECK_STATUS &0X10000)==0X10000)
			m_boolADAdjust_C_DC1_OK =TRUE;
		else
			m_boolADAdjust_C_DC1_OK=FALSE;
		if((CHECK_STATUS &0X20000)==0X20000)
			m_boolADAdjust_C_DC2_OK =TRUE;
		else
			m_boolADAdjust_C_DC2_OK=FALSE;
		if((CHECK_STATUS &0X40000)==0X40000)
			m_boolADAdjust_C_DC3_OK =TRUE;
		else
			m_boolADAdjust_C_DC3_OK=FALSE;
		if((CHECK_STATUS &0X80000)==0X80000)
			m_boolADAdjust_C_DC4_OK =TRUE;
		else
			m_boolADAdjust_C_DC4_OK=FALSE;
		
*/
//////////////////////////////////////////////////////////////////////////
//              end
//////////////////////////////////////////////////////////////////////////
/*	    m_boolADAdjust_Ua_OK=FALSE;
		m_boolADAdjust_Ub_OK=FALSE;
		m_boolADAdjust_Uc_OK=FALSE;
		m_boolADAdjust_Ia_OK=FALSE;
		m_boolADAdjust_Ib_OK=FALSE;
		m_boolADAdjust_Ic_OK=FALSE;
    ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ua_OK))->EnableWindow(m_boolADAdjust_Ua_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ub_OK))->EnableWindow(m_boolADAdjust_Ub_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Uc_OK))->EnableWindow(m_boolADAdjust_Uc_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ia_OK))->EnableWindow(m_boolADAdjust_Ia_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ib_OK))->EnableWindow(m_boolADAdjust_Ib_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ic_OK))->EnableWindow(m_boolADAdjust_Ic_OK);
/*
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC1_OK))->EnableWindow(m_boolADAdjust_V_DC1_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC2_OK))->EnableWindow(m_boolADAdjust_V_DC2_OK);
    ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC3_OK))->EnableWindow(m_boolADAdjust_V_DC3_OK);
    ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC4_OK))->EnableWindow(m_boolADAdjust_V_DC3_OK);
    
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC1_OK))->EnableWindow(m_boolADAdjust_C_DC1_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC2_OK))->EnableWindow(m_boolADAdjust_C_DC2_OK);
    ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC3_OK))->EnableWindow(m_boolADAdjust_C_DC3_OK);
    ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC4_OK))->EnableWindow(m_boolADAdjust_C_DC3_OK);
*/
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustACChannelUb() //UB
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==0 ||m_nADAdjust_Channel==1)
		m_nADAdjust_ACChannel =1;
	else
		m_nADAdjust_ACChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustACChannelUc() //UC
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==0 ||m_nADAdjust_Channel==1)
		m_nADAdjust_ACChannel =2;
	else
		m_nADAdjust_ACChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustACChannelIa() //IA
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==0 ||m_nADAdjust_Channel==1)
		m_nADAdjust_ACChannel =3;
	else
		m_nADAdjust_ACChannel =-1;
	UpdateData(FALSE);
	
}

void Dlg_ADAdjust1::OnRADIOADAdjustACChannelIb() //IB
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==0 ||m_nADAdjust_Channel==1)
		m_nADAdjust_ACChannel =4;
	else
		m_nADAdjust_ACChannel =-1;
	UpdateData(FALSE);
	
}

void Dlg_ADAdjust1::OnRADIOADAdjustACChannelIc() //IC
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==0 ||m_nADAdjust_Channel==1)
		m_nADAdjust_ACChannel =5;
	else
		m_nADAdjust_ACChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannel() //dc1
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =0;
	else if(m_nADAdjust_Channel==0 ||m_nADAdjust_Channel==1)
		m_nADAdjust_DCChannel =-1;


	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC1() //cdc1
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =4;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
	
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC2() //cdc2
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =5;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC3() //cdc3
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =6;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC4() //cdc4
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =7;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC2() //dc2
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =1;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC3() //dc3
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =2;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC4() //dc4
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =3;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

CString Dlg_ADAdjust1::FormChang(float INPUT_float)
{
	unsigned short Temp_short;
	UINT Temp_UINT;
	UCHAR Temp_UCHAR;
	char Temp_Buffer[10];
	BOOL Temp_BOOL;
	float Temp_float;
	CString Temp_CString;

	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();

//	UpdateData(TRUE);
	if(m_nADAdjust_ACChannel==0 ||m_nADAdjust_ACChannel==1||m_nADAdjust_ACChannel==2 )
	{
		Temp_short = (INPUT_float*pParent->DIM_public)/57.74;
		_itoa(Temp_short,Temp_Buffer,16);
		Temp_CString =Temp_Buffer;
		Temp_UINT = Temp_CString.GetLength();
		Temp_Buffer[Temp_UINT]='H';
		Temp_Buffer[Temp_UINT+1]='\0';
		Temp_CString =Temp_Buffer;
		Temp_CString.MakeUpper();
	}
	else if(m_nADAdjust_DCChannel ==0||m_nADAdjust_DCChannel ==1||m_nADAdjust_DCChannel ==2||m_nADAdjust_DCChannel ==3||m_nADAdjust_DCChannel ==8||m_nADAdjust_DCChannel ==9||m_nADAdjust_DCChannel ==10||m_nADAdjust_DCChannel ==11||m_nADAdjust_DCChannel ==16||m_nADAdjust_DCChannel ==17||m_nADAdjust_DCChannel ==18||m_nADAdjust_DCChannel ==19)  //Voltage
	{
		Temp_short = (INPUT_float*pParent->DIM_public)/2.5;
		_itoa(Temp_short,Temp_Buffer,16);
		Temp_CString =Temp_Buffer;
		Temp_UINT = Temp_CString.GetLength();
		Temp_Buffer[Temp_UINT]='H';
		Temp_Buffer[Temp_UINT+1]='\0';
		Temp_CString =Temp_Buffer;
		Temp_CString.MakeUpper();
	}
	else if(m_nADAdjust_ACChannel==3||m_nADAdjust_ACChannel==4||m_nADAdjust_ACChannel==5) //Current
	{
		if(pParent->Current_Style==0)
		{
			Temp_short = Temp_short = (INPUT_float*pParent->DIM_public)/5;
		}
		else if (pParent->Current_Style==1)
		{
			Temp_short = Temp_short = (INPUT_float*pParent->DIM_public)/1;
		}
		_itoa(Temp_short,Temp_Buffer,16);
		Temp_CString =Temp_Buffer;
//		Temp_CString.MakeUpper();
		Temp_UINT = Temp_CString.GetLength();
		Temp_Buffer[Temp_UINT]='H';
		Temp_Buffer[Temp_UINT+1]='\0';
		Temp_CString =Temp_Buffer;
		Temp_CString.MakeUpper();
		
	}
	else if(m_nADAdjust_DCChannel==4||m_nADAdjust_DCChannel==5||m_nADAdjust_DCChannel==6||m_nADAdjust_DCChannel==7||m_nADAdjust_DCChannel==12||m_nADAdjust_DCChannel==13||m_nADAdjust_DCChannel==14||m_nADAdjust_DCChannel==15||m_nADAdjust_DCChannel==20||m_nADAdjust_DCChannel==21||m_nADAdjust_DCChannel==22||m_nADAdjust_DCChannel==23) //Current
	{
		Temp_short = (INPUT_float*pParent->DIM_public)/10;
		_itoa(Temp_short,Temp_Buffer,16);
		Temp_CString =Temp_Buffer;
//		Temp_CString.MakeUpper();
		Temp_UINT = Temp_CString.GetLength();
		Temp_Buffer[Temp_UINT]='H';
		Temp_Buffer[Temp_UINT+1]='\0';
		Temp_CString =Temp_Buffer;
		Temp_CString.MakeUpper();

	}
	return Temp_CString;

}




void Dlg_ADAdjust1::OnKillfocusEDITADAdjustUa1() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_ACChannel==0)
	{
		UpdateData(TRUE);
		m_CStringADAdjust_Ua_5=FormChang(m_floatADAdjust_Ua_1);
		UpdateData(FALSE);
	}
}



void Dlg_ADAdjust1::OnKillfocusEDITADAdjustUb1() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_ACChannel==1)
	{
		UpdateData(TRUE);
		m_CStringADAdjust_Ub_5=FormChang(m_floatADAdjust_Ub_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustUc1() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_ACChannel==2)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_Uc_5=FormChang(m_floatADAdjust_Uc_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustIa1() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_ACChannel==3)
	{
		UpdateData(TRUE);	
		m_CStringADAdjust_Ia_5=FormChang(m_floatADAdjust_Ia_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustIb1() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_ACChannel==4)
	{
		UpdateData(TRUE);
		m_CStringADAdjust_Ib_5=FormChang(m_floatADAdjust_Ib_1);
		UpdateData(FALSE);
	}
	
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustIc1() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_ACChannel==5)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_Ic_5=FormChang(m_floatADAdjust_Ic_1);
		UpdateData(FALSE);
	}
}
/*
void Dlg_ADAdjust1::OnKillfocusEDITADAdjustVDC11() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==0)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_V_DC1_5=FormChang(m_floatADAdjust_V_DC1_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustVDC21() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==1)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_V_DC2_5=FormChang(m_floatADAdjust_V_DC2_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustVDC31() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==2)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_V_DC3_5=FormChang(m_floatADAdjust_V_DC3_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustVDC41() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==3)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_V_DC4_5=FormChang(m_floatADAdjust_V_DC4_1);
		UpdateData(FALSE);
	}
	
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustCDC11() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==4)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_C_DC1_5=FormChang(m_floatADAdjust_C_DC1_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustCDC21() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==5)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_C_DC2_5=FormChang(m_floatADAdjust_C_DC2_1);
		UpdateData(FALSE);
	}
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustCDC31() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==6)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_C_DC3_5=FormChang(m_floatADAdjust_C_DC3_1);
		UpdateData(FALSE);
	}
	
}

void Dlg_ADAdjust1::OnKillfocusEDITADAdjustCDC41() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_DCChannel==7)
	{	
		UpdateData(TRUE);
		m_CStringADAdjust_C_DC4_5=FormChang(m_floatADAdjust_C_DC4_1);
		UpdateData(FALSE);
	}
	
}*/

void Dlg_ADAdjust1::OnBUTTONADAdjustApply() //通道校准
{
	// TODO: Add your control notification handler code here
//	AD1_FUNCTION =IDC_BUTTON_AD1_FETCH;

	UCHAR DATA[5];
	UCHAR Temp_UCHAR;
	unsigned short Temp_short;
	float Temp_float;
	
	Function_ID =IDC_BUTTON_ADAdjust_Apply;
//UpdateData(FALSE);
//UpdateData(TRUE);


	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
//	pParent->
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_ADAdjust_Apply;


//////////////////////////////////////////////////////////////////////////
//
	Line1[0].Index =0;
	Line2[0].Index =0;

//	pParent->ADAdjust_block_38.Data
	if(m_nADAdjust_Channel==0||m_nADAdjust_Channel==1)
		Temp_UCHAR= (m_nADAdjust_Channel *6)+m_nADAdjust_ACChannel;
	else if(m_nADAdjust_Channel==2)
		Temp_UCHAR = 12 +m_nADAdjust_DCChannel;
	DATA[0]=Temp_UCHAR+1;

	if(m_nADAdjust_ACChannel==0)
	{
		m_boolADAdjust_Ua_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
		Temp_float=m_floatADAdjust_Ua_1;
		Temp_short = (Temp_float*pParent->DIM_public)/57.74;
	}
	if(m_nADAdjust_ACChannel==1)
	{
		m_boolADAdjust_Ub_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
		Temp_float=m_floatADAdjust_Ub_1;
		Temp_short = (Temp_float*pParent->DIM_public)/57.74;
	}
	if(m_nADAdjust_ACChannel==2)
	{
		m_boolADAdjust_Uc_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
		Temp_float=m_floatADAdjust_Uc_1;
		Temp_short = (Temp_float*pParent->DIM_public)/57.74;
	}
	if(m_nADAdjust_ACChannel==3)
	{
		m_boolADAdjust_Ia_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
		Temp_float=m_floatADAdjust_Ia_1;
/*		Temp_short = (Temp_float/5)*8192;*/
		if(pParent->Current_Style==0)
		{
			Temp_short = (Temp_float*pParent->DIM_public)/5;
		}
		else if (pParent->Current_Style==1)
		{
			Temp_short = (Temp_float*pParent->DIM_public)/1;
		}
	}
	if(m_nADAdjust_ACChannel==4)
	{
		m_boolADAdjust_Ib_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
		Temp_float=m_floatADAdjust_Ib_1;
		if(pParent->Current_Style==0)
		{
			Temp_short = (Temp_float*pParent->DIM_public)/5;
		}
		else if (pParent->Current_Style==1)
		{
			Temp_short = (Temp_float*pParent->DIM_public)/1;
		}
	}
	if(m_nADAdjust_ACChannel==5)
	{
		m_boolADAdjust_Ic_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
		Temp_float=m_floatADAdjust_Ic_1;
		if(pParent->Current_Style==0)
		{
			Temp_short = (Temp_float*pParent->DIM_public)/5;
		}
		else if (pParent->Current_Style==1)
		{
			Temp_short = (Temp_float*pParent->DIM_public)/1;
		}
	}
	if(m_nADAdjust_DCChannel==0)
	{
		m_boolADAdjust_V_DC1_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_V_DC1_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==1)
	{
		m_boolADAdjust_V_DC2_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_V_DC2_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==2)
	{
		m_boolADAdjust_V_DC3_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_V_DC3_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==3)
	{
		m_boolADAdjust_V_DC4_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_V_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==4)
	{
		m_boolADAdjust_C_DC1_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC1_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==5)
	{
		m_boolADAdjust_C_DC2_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC2_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==6)
	{
		m_boolADAdjust_C_DC3_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC3_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==7)
	{
		m_boolADAdjust_C_DC4_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}

	if(m_nADAdjust_DCChannel==8)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==9)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==10)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==11)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==12)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==13)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==14)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==15)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==16)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==17)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==18)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
	if(m_nADAdjust_DCChannel==19)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/2.5;
	}
 
	if(m_nADAdjust_DCChannel==20)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==21)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==22)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}
	if(m_nADAdjust_DCChannel==23)
	{
	//	m_boolADAdjust_C_DC5_OK =FALSE;                                //CLEAR THE CHECK SYMBOL   2008.1.23
	//	Temp_float=m_floatADAdjust_C_DC4_1;
		Temp_short = (Temp_float*pParent->DIM_public)/10;
	}



	DATA[1] = Temp_short & 0xff;
	DATA[2] = Temp_short>>8;
	DATA[3] =0;
	DATA[4] = '\0';

	pParent->Connect_Telegram.PACK_SELECT=TRUE;
	pParent->Zero_NR=0;
	for(int tt=0; tt<4;tt++)
	{
		pParent->Connect_Telegram.ValidDataToPack[tt] =DATA[tt];
		if(DATA[tt]==0)
		pParent->Zero_NR++;		
	}
//	Zero_NR--;
	pParent->Zero_NR--;
	pParent->ADAdjust_block_38.Station_adr=0;
	pParent->ADAdjust_block_38.Telegram_Nr=38;
	pParent->ADAdjust_block_38.F1_field=0;
	pParent->ADAdjust_block_38.F2_field=0x80;
	pParent->Fun_Connect(pParent->ADAdjust_block_38,pParent->Zero_NR);

	
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ua_OK))->EnableWindow(m_boolADAdjust_Ua_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ub_OK))->EnableWindow(m_boolADAdjust_Ub_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Uc_OK))->EnableWindow(m_boolADAdjust_Uc_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ia_OK))->EnableWindow(m_boolADAdjust_Ia_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ib_OK))->EnableWindow(m_boolADAdjust_Ib_OK);
	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_Ic_OK))->EnableWindow(m_boolADAdjust_Ic_OK);
	
//	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC1_OK))->EnableWindow(m_boolADAdjust_V_DC1_OK);
//	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC2_OK))->EnableWindow(m_boolADAdjust_V_DC2_OK);
 //   ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC3_OK))->EnableWindow(m_boolADAdjust_V_DC3_OK);
 //   ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_V_DC4_OK))->EnableWindow(m_boolADAdjust_V_DC3_OK);
    
//	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC1_OK))->EnableWindow(m_boolADAdjust_C_DC1_OK);
// 	((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC2_OK))->EnableWindow(m_boolADAdjust_C_DC2_OK);
 //   ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC3_OK))->EnableWindow(m_boolADAdjust_C_DC3_OK);
  //  ((CButton*)GetDlgItem(IDC_CHECK_ADAdjust_C_DC4_OK))->EnableWindow(m_boolADAdjust_C_DC3_OK);
	UpdateData(FALSE);
	
}

void Dlg_ADAdjust1::OnBUTTONADAdjustFetch() //校准动态
{
	// TODO: Add your control notification handler code here
	UCHAR Temp_UCHAR;
//	unsigned short Temp_short;
//	float Temp_float;
	Function_ID =IDC_BUTTON_ADAdjust_Fetch;
	if(m_nADAdjust_Channel==0||m_nADAdjust_Channel==1)
		Temp_UCHAR= (m_nADAdjust_Channel *6)+m_nADAdjust_ACChannel;
	else if(m_nADAdjust_Channel==2)
		Temp_UCHAR = 12 +m_nADAdjust_DCChannel;
	Temp_UCHAR++;


//////////////////////////////////////////////////////////////////////////
//
	Line1[0].Index =0;
	Line2[0].Index =0;

	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_ADAdjust_Fetch;
	pParent->ADAdjust_block_40.Station_adr=0;
	pParent->ADAdjust_block_40.Telegram_Nr=40;
	pParent->ADAdjust_block_40.F1_field =0;
	pParent->ADAdjust_block_40.F2_field =0x80;
	pParent->Connect_Telegram.ValidDataToPack[0]=Temp_UCHAR;
	pParent->Connect_Telegram.ValidDataToPack[1]=0;
	pParent->Connect_Telegram.ValidDataToPack[2]='\0';
	pParent->Connect_Telegram.PACK_SELECT=TRUE;
	pParent->Fun_Connect(pParent->ADAdjust_block_40,0);

//	ValidData[4]=10;ValidData[5]=0x55;ValidData[6]=0x55;ValidData[7]=0x00;

	SetTimer(IDC_BUTTON_ADAdjust_Fetch,666,NULL);
}

void Dlg_ADAdjust1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==IDC_BUTTON_ADAdjust_Fetch)
	{
		KillTimer(IDC_BUTTON_ADAdjust_Fetch);
		UpdateData(TRUE);
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

void Dlg_ADAdjust1::OnBUTTONADAdjustNewParApply() 
{
	// TODO: Add your control notification handler code here
	UCHAR Temp_UCHAR;
//	unsigned short Temp_short;
//	float Temp_float;
//	CHECK_STATUS =0xffff0;	ParaData[0]=0x55;	ParaData[1]=0xaa;	ParaData[2]=0;	ParaData[3]=0xff;

//////////////////////////////////////////////////////////////////////////
//
	Line1[0].Index =0;
	Line2[0].Index =0;

	Function_ID =IDC_BUTTON_ADAdjust_NewParApply;
	if(CHECK_STATUS==0X0FFFFF)      //可以下参数
	{ 
		if(IDOK==MessageBox("确认下载新参数吗？","ADAdjust Para. Download",MB_OKCANCEL))
		{
			Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
			CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
			pParent->Connect_Index=0;
			pParent->ErrorCounter=0;
			pParent->Down =IDC_BUTTON_ADAdjust_NewParApply;
			pParent->ADAdjust_block_42.Station_adr=0;
			pParent->ADAdjust_block_42.Telegram_Nr=42;
			pParent->ADAdjust_block_42.F1_field =0;
			pParent->ADAdjust_block_42.F2_field =0x80;
			Temp_UCHAR=0;
			for(int tt=0; tt<40;tt++)
			{
				pParent->Connect_Telegram.ValidDataToPack[tt] = ParaData[tt];
				if(ParaData[tt]==0)
					Temp_UCHAR++;
			}
			pParent->Connect_Telegram.ValidDataToPack[tt]='\0';
			pParent->Connect_Telegram.PACK_SELECT=TRUE;
			pParent->Fun_Connect(pParent->ADAdjust_block_42,Temp_UCHAR);
		}
		else
			MessageBox("参数下载失败！");

	}
	else 
		MessageBox("校准未完成！");

}
/*
void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC6() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =8;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC5() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =9;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC7() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =10;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC8() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =11;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}
*/
void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =12;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC6() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =13;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC7() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =14;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC8() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =15;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}



void Dlg_ADAdjust1::OnRADIOADAdjustDCChannel5() 
{
	// TODO: Add your control notification handler code here
		
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =8;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}
void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC6() 
{
	// TODO: Add your control notification handler code here
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =9;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}
void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC7() 
{
	// TODO: Add your control notification handler code here
		
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =10;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelVDC8() 
{
	// TODO: Add your control notification handler code here
		
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =11;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}


void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC9() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =16;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC10() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =17;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC11() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =18;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC12() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =19;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC13() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =20;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC14() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =21;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC15() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =22;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}

void Dlg_ADAdjust1::OnRADIOADAdjustDCChannelCDC16() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_nADAdjust_Channel==2)
		m_nADAdjust_DCChannel =23;
	else
		m_nADAdjust_DCChannel =-1;
	UpdateData(FALSE);
}


