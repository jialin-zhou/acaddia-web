// Dlg_AD1.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_AD1.h"

#include "Dlg_ZJM.h"
#include "new1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_AD1 dialog


Dlg_AD1::Dlg_AD1(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_AD1::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_AD1)
	m_shortAD1_C_DC1=m_shortAD1_C_DC2=m_shortAD1_C_DC3=m_shortAD1_C_DC4=m_shortAD1_C_DC5=m_shortAD1_C_DC6=m_shortAD1_C_DC7=m_shortAD1_C_DC8=m_shortAD1_C_DC9=m_shortAD1_C_DC10=m_shortAD1_C_DC11=m_shortAD1_C_DC12=0;
	m_shortAD1_V_DC1=m_shortAD1_V_DC2=m_shortAD1_V_DC3=m_shortAD1_V_DC4=m_shortAD1_V_DC5=m_shortAD1_V_DC6=m_shortAD1_V_DC7=m_shortAD1_V_DC8=m_shortAD1_V_DC9=m_shortAD1_V_DC10=m_shortAD1_V_DC11=m_shortAD1_V_DC12=0;
	m_shortAD1_C_LINE1=m_shortAD1_C_LINE2=m_shortAD1_V_LINE1=m_shortAD1_V_LINE2=0;
	m_shortAD1_I1a=m_shortAD1_I1b=m_shortAD1_I1c=m_shortAD1_I2c=m_shortAD1_I2a=m_shortAD1_I2b=0;
	m_shortAD1_U1a=m_shortAD1_U1b=m_shortAD1_U1c=0;
	m_shortAD1_U2a=m_shortAD1_U2b=m_shortAD1_U2c=0;
	
	m_nAD1_DCSS2=m_nAD1_DCSS3=m_nAD1_DCSS4 =m_nAD1_DCSS5 =m_nAD1_DCSS6=m_nAD1_DCSS7=m_nAD1_DCSS8=m_nAD1_DCSS =m_nAD1_DCSS9 =m_nAD1_DCSS10=m_nAD1_DCSS11=m_nAD1_DCSS12=0;
	m_nAD1_SecVNV =m_nAD1_VoltSTD1=m_nAD1_VoltSTD2=m_nAD1_ActiveCS=0;
	
	m_nAD1_SecCNV= 1;
	m_Channel_Sec1 = 0;
	m_Channel_Sec2 = 1;
	m_Channel_Sec3 = 2;
	m_Channel_SecX = 3;
	m_Model_Sec = 0;
	m_Delay_A = 0;
	m_Delay_B = 0;
	m_Delay_C = 0;
	m_Delay_X = 0;
	m_Delay = 0;
	m_Primary_Current_Scaling = 3000;
	//}}AFX_DATA_INIT
}


void Dlg_AD1::DoDataExchange(CDataExchange* pDX)
{ 
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	//20240618shy
//	m_nAD1_DCSS2=m_nAD1_DCSS3=m_nAD1_DCSS4 =m_nAD1_DCSS5 =m_nAD1_DCSS6=m_nAD1_DCSS7=m_nAD1_DCSS8=m_nAD1_DCSS =1;
    //
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_AD1)
	//DDX_Radio(pDX, IDC_RADIO_AD1_ActiveCS, m_nAD1_ActiveCS);
//	DDX_Radio(pDX, IDC_RADIO_AD1_SecCNV, m_nAD1_SecCNV);
//	DDX_Radio(pDX, IDC_RADIO_AD1_SecVNV, m_nAD1_SecVNV);
//	DDX_Radio(pDX, IDC_RADIO_AD1_VoltSTD1, m_nAD1_VoltSTD1);
//	DDX_Radio(pDX, IDC_RADIO_AD1_VoltSTD2, m_nAD1_VoltSTD2);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS, m_nAD1_DCSS);
	DDX_Text(pDX, IDC_EDIT_AD1_C_DC1, m_shortAD1_C_DC1);
	DDX_Text(pDX, IDC_EDIT_AD1_C_DC2, m_shortAD1_C_DC2);
	DDX_Text(pDX, IDC_EDIT_AD1_C_DC3, m_shortAD1_C_DC3);
	DDX_Text(pDX, IDC_EDIT_AD1_C_DC4, m_shortAD1_C_DC4);

    DDX_Text(pDX, IDC_EDIT_AD1_C_DC5, m_shortAD1_C_DC5);
    DDX_Text(pDX, IDC_EDIT_AD1_C_DC6, m_shortAD1_C_DC6);
    DDX_Text(pDX, IDC_EDIT_AD1_C_DC7, m_shortAD1_C_DC7);
    DDX_Text(pDX, IDC_EDIT_AD1_C_DC8, m_shortAD1_C_DC8);

    DDX_Text(pDX, IDC_EDIT_AD1_C_DC9, m_shortAD1_C_DC9);
    DDX_Text(pDX, IDC_EDIT_AD1_C_DC10, m_shortAD1_C_DC10);
    DDX_Text(pDX, IDC_EDIT_AD1_C_DC11, m_shortAD1_C_DC11);
    DDX_Text(pDX, IDC_EDIT_AD1_C_DC12, m_shortAD1_C_DC12);

	DDX_Text(pDX, IDC_EDIT_AD1_V_DC1, m_shortAD1_V_DC1);
	DDX_Text(pDX, IDC_EDIT_AD1_V_DC2, m_shortAD1_V_DC2);
	DDX_Text(pDX, IDC_EDIT_AD1_V_DC3, m_shortAD1_V_DC3);
	DDX_Text(pDX, IDC_EDIT_AD1_V_DC4, m_shortAD1_V_DC4);
    DDX_Text(pDX, IDC_EDIT_AD1_V_DC5, m_shortAD1_V_DC5);

	DDX_Text(pDX, IDC_EDIT_AD1_V_DC6, m_shortAD1_V_DC6);
	DDX_Text(pDX, IDC_EDIT_AD1_V_DC7, m_shortAD1_V_DC7);
    DDX_Text(pDX, IDC_EDIT_AD1_V_DC8, m_shortAD1_V_DC8);

    DDX_Text(pDX, IDC_EDIT_AD1_V_DC9, m_shortAD1_V_DC9);
	DDX_Text(pDX, IDC_EDIT_AD1_V_DC10, m_shortAD1_V_DC10);
	DDX_Text(pDX, IDC_EDIT_AD1_V_DC11, m_shortAD1_V_DC11);
    DDX_Text(pDX, IDC_EDIT_AD1_V_DC12, m_shortAD1_V_DC12);

	DDX_Text(pDX, IDC_EDIT_AD1_V_LINE1, m_shortAD1_V_LINE1);
	DDX_Text(pDX, IDC_EDIT_AD1_V_LINE2, m_shortAD1_V_LINE2);
	DDX_Text(pDX, IDC_EDIT_AD1_C_LINE1, m_shortAD1_C_LINE1);
	DDX_Text(pDX, IDC_EDIT_AD1_C_LINE2, m_shortAD1_C_LINE2);
	DDX_Text(pDX, IDC_EDIT_AD1_I1a, m_shortAD1_I1a);
	DDX_Text(pDX, IDC_EDIT_AD1_I1b, m_shortAD1_I1b);
	DDX_Text(pDX, IDC_EDIT_AD1_I1c, m_shortAD1_I1c);
	DDX_Text(pDX, IDC_EDIT_AD1_I2a, m_shortAD1_I2a);
	DDX_Text(pDX, IDC_EDIT_AD1_I2b, m_shortAD1_I2b);
	DDX_Text(pDX, IDC_EDIT_AD1_I2c, m_shortAD1_I2c);
	DDX_Text(pDX, IDC_EDIT_AD1_U1a, m_shortAD1_U1a);
	DDX_Text(pDX, IDC_EDIT_AD1_U1b, m_shortAD1_U1b);
	DDX_Text(pDX, IDC_EDIT_AD1_U1c, m_shortAD1_U1c);
	DDX_Text(pDX, IDC_EDIT_AD1_U2a, m_shortAD1_U2a);
	DDX_Text(pDX, IDC_EDIT_AD1_U2b, m_shortAD1_U2b);
	DDX_Text(pDX, IDC_EDIT_AD1_U2c, m_shortAD1_U2c);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS2, m_nAD1_DCSS2);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS3, m_nAD1_DCSS3);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS4, m_nAD1_DCSS4);
    DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS5, m_nAD1_DCSS5);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS6, m_nAD1_DCSS6);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS7, m_nAD1_DCSS7);
    DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS8, m_nAD1_DCSS8);
    DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS9, m_nAD1_DCSS9);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS10, m_nAD1_DCSS10);
	DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS11, m_nAD1_DCSS11);
    DDX_Radio(pDX, IDC_RADIO1_AD1_DCSS12, m_nAD1_DCSS12);

	DDX_CBIndex(pDX, IDC_COMBO1, m_Channel_Sec1);
	DDX_CBIndex(pDX, IDC_COMBO2, m_Channel_Sec2);
	DDX_CBIndex(pDX, IDC_COMBO3, m_Channel_Sec3);
	DDX_CBIndex(pDX, IDC_COMBO4, m_Channel_SecX);
	DDX_CBIndex(pDX, IDC_COMBO5, m_Model_Sec);
	DDX_Text(pDX, IDC_EDIT1, m_Delay_A);
	DDX_Text(pDX, IDC_EDIT2, m_Delay_B);
	DDX_Text(pDX, IDC_EDIT3, m_Delay_C);
	DDX_Text(pDX, IDC_EDIT4, m_Delay_X);
	DDX_Text(pDX, IDC_EDIT5, m_Delay);
	DDX_Text(pDX, IDC_EDIT7, m_Primary_Current_Scaling);
	//}}AFX_DATA_MAP
	

	

//////////////////////////////////////////////////////////////////////////
//             FUNCTION CHOOSE
//////////////////////////////////////////////////////////////////////////
/*
short TypeByteToShort(UCHAR CH1, UCHAR CH2)
{
	short Result;
	Result = CH2;
	Result = Result<<8;
	Result += CH1;
	return(Result);
}

*/
//////////////////////////////////////////////////////////////////////////
//            DISPLAY THE DATA
//////////////////////////////////////////////////////////////////////////
if(AD1_FUNCTION==IDC_BUTTON_AD1_FETCH ||AD1_FUNCTION ==IDC_BUTTON_ZJM_OPEN ||AD1_FUNCTION ==IDC_ZJM_AD1)
{
	unsigned short TempData_short=0;
	UCHAR TempData_UCHAR=0;
	UINT  TempData_UINT=0;
	BOOL  TempData_BOOL=FALSE;

     
	TempData_UCHAR =ValidData[4];           //U1a
	TempData_short= ValidData[5];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_U1a = TempData_short;

	
	TempData_UCHAR =ValidData[6];           //U1b
	TempData_short= ValidData[7];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_U1b = TempData_short;

	TempData_UCHAR =ValidData[8];           //U1c
	TempData_short= ValidData[9];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_U1c = TempData_short;

	TempData_UCHAR =ValidData[10];           //I1a
	TempData_short= ValidData[11];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_I1a = TempData_short;

	TempData_UCHAR =ValidData[12];           //I1b
	TempData_short= ValidData[13];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_I1b = TempData_short;

	TempData_UCHAR =ValidData[14];           //I1c
	TempData_short= ValidData[15];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_I1c = TempData_short;

	TempData_UCHAR =ValidData[16];           //U2a
	TempData_short= ValidData[17];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_U2a = TempData_short;

	TempData_UCHAR =ValidData[18];           //U2b
	TempData_short= ValidData[19];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_U2b = TempData_short;

	TempData_UCHAR =ValidData[20];           //U2c
	TempData_short= ValidData[21];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_U2c = TempData_short;

	TempData_UCHAR =ValidData[22];           //I2a
	TempData_short= ValidData[23];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_I2a = TempData_short;

	TempData_UCHAR =ValidData[24];           //I2b
	TempData_short= ValidData[25];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_I2b = TempData_short;

	TempData_UCHAR =ValidData[26];           //I2c
	TempData_short= ValidData[27];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_I2c = TempData_short;

	TempData_UCHAR =ValidData[28];           //V DC1
	TempData_short= ValidData[29];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC1 = TempData_short;

	//m_shortAD1_V_DC1 = *(short int*)(&ValidData[28]);
	TempData_UCHAR =ValidData[30];           //V DC2
	TempData_short= ValidData[31];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC2 = TempData_short;


	TempData_UCHAR =ValidData[32];           //V DC3
	TempData_short= ValidData[33];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC3 = TempData_short;

	TempData_UCHAR =ValidData[34];           //V DC4
	TempData_short= ValidData[35];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC4 = TempData_short;

   // m_shortAD1_V_DC4 = *(short*)(&ValidData[34]);

    TempData_UCHAR =ValidData[36];           //V DC5
	TempData_short= ValidData[37];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC5 = TempData_short;

	TempData_UCHAR =ValidData[38];           //V DC6
	TempData_short= ValidData[39];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC6 = TempData_short;

	TempData_UCHAR =ValidData[40];           //V DC7
	TempData_short= ValidData[41];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC7 = TempData_short;

    TempData_UCHAR =ValidData[42];           //V DC8
	TempData_short= ValidData[43];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC8 = TempData_short;
//shy20250303
    TempData_UCHAR =ValidData[44];           //V DC9
	TempData_short= ValidData[45];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC9 = TempData_short;

	TempData_UCHAR =ValidData[46];           //V DC10
	TempData_short= ValidData[47];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC10 = TempData_short;

	TempData_UCHAR =ValidData[48];           //V DC11
	TempData_short= ValidData[49];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC11 = TempData_short;

    TempData_UCHAR =ValidData[50];           //V DC12
	TempData_short= ValidData[51];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC12 = TempData_short;


	TempData_UCHAR =ValidData[52];           //C DC1
	TempData_short= ValidData[53];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC1 = TempData_short;

	TempData_UCHAR =ValidData[54];           //C DC2
	TempData_short= ValidData[55];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC2 = TempData_short;

	TempData_UCHAR =ValidData[56];           //C DC3
	TempData_short= ValidData[57];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC3 = TempData_short;

	TempData_UCHAR =ValidData[58];           //C DC4
	TempData_short= ValidData[59];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC4 = TempData_short;

		
	TempData_UCHAR =ValidData[60];           //C DC5
	TempData_short= ValidData[61];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC5 = TempData_short;
	
	TempData_UCHAR =ValidData[62];           //C DC6
	TempData_short= ValidData[63];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC6 = TempData_short;
		
	TempData_UCHAR =ValidData[64];           //C DC7
	TempData_short= ValidData[65];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC7 = TempData_short;
		
	TempData_UCHAR =ValidData[66];           //C DC8
	TempData_short= ValidData[67];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC8 = TempData_short;

	TempData_UCHAR =ValidData[68];           //C DC9
	TempData_short= ValidData[69];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC9 = TempData_short;
	
	TempData_UCHAR =ValidData[70];           //C DC10
	TempData_short= ValidData[71];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC10 = TempData_short;
		
	TempData_UCHAR =ValidData[72];           //C DC11
	TempData_short= ValidData[73];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC11 = TempData_short;
		
	TempData_UCHAR =ValidData[74];           //C DC12
	TempData_short= ValidData[75];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC12 = TempData_short;


	TempData_UCHAR =ValidData[76];           //V_LINE1
	TempData_short= ValidData[77];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_LINE1 = TempData_short;

	TempData_UCHAR =ValidData[78];           //V_LINE2
	TempData_short= ValidData[79];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_LINE2 = TempData_short;

	TempData_UCHAR =ValidData[80];           //C_LINE1
	TempData_short= ValidData[81];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_LINE1 = TempData_short;

	TempData_UCHAR =ValidData[82];           //C_LINE2
	TempData_short= ValidData[83];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_LINE2 = TempData_short;
/*
	TempData_UCHAR= ValidData[52];           //Active Channel Select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_ActiveCS = TempData_UINT;

	TempData_UCHAR = ValidData[53];          //Voltage Sent TO DP1
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_VoltSTD1 = TempData_UINT;

	TempData_UCHAR = ValidData[54];          //Voltage Sent To DP2
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_VoltSTD2 = TempData_UINT;

	TempData_UCHAR = ValidData[55];          //Second Current Nom Value
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_SecCNV = TempData_UINT;
    pParent->Current_Style=m_nAD1_SecCNV;
*/
	TempData_UCHAR= ValidData[84];           //Interpolation Model Select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_Model_Sec = TempData_UINT;

	TempData_UCHAR = ValidData[85];          //Common Delay 
	TempData_short = ValidData[86];
	TempData_short = TempData_short<<8;
	TempData_short+= TempData_UCHAR;
	m_Delay = TempData_short;

	TempData_UCHAR = ValidData[87];          //Scaling
	TempData_UINT =(UINT)TempData_UCHAR*25;
	m_Primary_Current_Scaling = TempData_UINT;
    //pParent->Current_Style=m_nAD1_SecCNV;

	TempData_UCHAR = ValidData[88];         //Second Voltage Nom Value
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_SecVNV = TempData_UINT;

	TempData_UCHAR = ValidData[89];         //DC1 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS = TempData_UINT;

	TempData_UCHAR = ValidData[90];         //DC2 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS2 = TempData_UINT;

	TempData_UCHAR = ValidData[91];         //DC3 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS3 = TempData_UINT;

	TempData_UCHAR = ValidData[92];         //DC4 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS4 = TempData_UINT;

    TempData_UCHAR = ValidData[93];         //DC5 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS5 = TempData_UINT;

		
	TempData_UCHAR = ValidData[94];         //DC6 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS6 = TempData_UINT;

    TempData_UCHAR = ValidData[95];         //DC7 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS7 = TempData_UINT;

	TempData_UCHAR = ValidData[96];         //DC8 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS8 = TempData_UINT;

    TempData_UCHAR = ValidData[97];         //DC9 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS9 = TempData_UINT;

		
	TempData_UCHAR = ValidData[98];         //DC10 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS10 = TempData_UINT;

    TempData_UCHAR = ValidData[99];         //DC11 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS11 = TempData_UINT;

	TempData_UCHAR = ValidData[100];         //DC12 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS12 = TempData_UINT;


	TempData_UCHAR = ValidData[101];         //Channel Seclect IA
	TempData_UINT =(UINT)TempData_UCHAR;
	m_Channel_Sec1 = TempData_UINT;

	TempData_UCHAR = ValidData[102];         //Channel Seclect IB
	TempData_UINT =(UINT)TempData_UCHAR;
	m_Channel_Sec2 = TempData_UINT;

	TempData_UCHAR = ValidData[103];         //Channel Seclect IC
	TempData_UINT =(UINT)TempData_UCHAR;
	m_Channel_Sec3 = TempData_UINT;

	TempData_UCHAR = ValidData[104];         //Channel Seclect IX
	TempData_UINT =(UINT)TempData_UCHAR;
	m_Channel_SecX = TempData_UINT;

	TempData_UCHAR =ValidData[105];          //Channel Delay IA
	TempData_short= ValidData[106];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_Delay_A = TempData_short;

	TempData_UCHAR =ValidData[107];          //Channel Delay IA
	TempData_short= ValidData[108];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_Delay_B = TempData_short;

	TempData_UCHAR =ValidData[109];          //Channel Delay IC
	TempData_short= ValidData[110];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_Delay_C = TempData_short;

	TempData_UCHAR =ValidData[111];          //Channel Delay IX
	TempData_short= ValidData[112];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_Delay_X = TempData_short;
/*  
	
    TempData_UCHAR = ValidData[73];         //DC5 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS5 = TempData_UINT;

    TempData_UCHAR =ValidData[74];           //V DC5
	TempData_short= ValidData[75];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC5 = TempData_short;

	TempData_UCHAR =ValidData[76];           //C DC5
	TempData_short= ValidData[77];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC5 = TempData_short;


	TempData_UCHAR = ValidData[78];         //DC6 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS6 = TempData_UINT;

    TempData_UCHAR = ValidData[79];         //DC7 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS7 = TempData_UINT;

	TempData_UCHAR = ValidData[80];         //DC8 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_nAD1_DCSS8 = TempData_UINT;

	TempData_UCHAR =ValidData[81];           //V DC6
	TempData_short= ValidData[82];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC6 = TempData_short;

	TempData_UCHAR =ValidData[83];           //V DC7
	TempData_short= ValidData[84];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC7 = TempData_short;

    TempData_UCHAR =ValidData[85];           //V DC8
	TempData_short= ValidData[86];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_V_DC8 = TempData_short;

		
	TempData_UCHAR =ValidData[87];           //C DC6
	TempData_short= ValidData[88];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC6 = TempData_short;
		
	TempData_UCHAR =ValidData[89];           //C DC7
	TempData_short= ValidData[90];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC7 = TempData_short;
		
	TempData_UCHAR =ValidData[91];           //C DC8
	TempData_short= ValidData[92];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	m_shortAD1_C_DC8 = TempData_short;
*/
	AD1_FUNCTION =NULL;
}

}


BEGIN_MESSAGE_MAP(Dlg_AD1, CDialog)
	//{{AFX_MSG_MAP(Dlg_AD1)
	ON_BN_CLICKED(IDC_BUTTON_AD1_DEFAULT, OnButtonAd1Default)
	ON_BN_CLICKED(IDC_BUTTON_AD1_FETCH, OnButtonAd1Fetch)
	ON_BN_CLICKED(IDC_BUTTON_AD1_APPLY, OnButtonAd1Apply)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_AD1_VoltSTD2, OnRADIOAD1VoltSTD2)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS, OnRadio1Ad1Dcss)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS_1, OnRadio1Ad1Dcss1)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS2, OnRadio1Ad1Dcss2)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS22, OnRadio1Ad1Dcss22)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS3, OnRadio1Ad1Dcss3)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS33, OnRadio1Ad1Dcss33)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS4, OnRadio1Ad1Dcss4)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS44, OnRadio1Ad1Dcss44)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS5, OnRadio1Ad1Dcss5)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS55, OnRadio1Ad1Dcss55)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS6, OnRadio1Ad1Dcss6)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS66, OnRadio1Ad1Dcss66)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS7, OnRadio1Ad1Dcss7)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS77, OnRadio1Ad1Dcss77)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS8, OnRadio1Ad1Dcss8)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS88, OnRadio1Ad1Dcss88)
	ON_EN_CHANGE(IDC_EDIT_AD1_V_DC1, OnChangeEditAd1VDc1)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS9, OnRadio1Ad1Dcss9)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS99, OnRadio1Ad1Dcss99)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS10, OnRadio1Ad1Dcss10)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS1010, OnRadio1Ad1Dcss1010)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS11, OnRadio1Ad1Dcss11)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS1111, OnRadio1Ad1Dcss1111)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS12, OnRadio1Ad1Dcss12)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS22, OnRadio1Ad1Dcss2)
	ON_BN_CLICKED(IDC_RADIO1_AD1_DCSS1212, OnRadio1Ad1Dcss1212)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_AD1 message handlers

void Dlg_AD1::OnButtonAd1Default() 
{
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	if(pParent->DIM_public==8192)
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	AD1_FUNCTION =IDC_BUTTON_AD1_DEFAULT;
	m_nAD1_ActiveCS = 0;
	m_nAD1_SecCNV = 1;
	m_nAD1_SecVNV = 0;
	m_nAD1_VoltSTD1 = 0;
	m_nAD1_VoltSTD2 = 0;
	//shy20240618
	m_nAD1_DCSS = 1;
	m_nAD1_DCSS2 = 1;
	m_nAD1_DCSS3 = 1;
	m_nAD1_DCSS4 = 1;
    m_nAD1_DCSS5 = 1;
	m_nAD1_DCSS6 = 1;
	m_nAD1_DCSS7 = 1;
	m_nAD1_DCSS8 = 1;
    m_nAD1_DCSS9 = 1;
	m_nAD1_DCSS10 = 1;
	m_nAD1_DCSS11 = 1;
	m_nAD1_DCSS12 = 1;
//
	m_Channel_Sec1 = 0;
	m_Channel_Sec2 = 1;
	m_Channel_Sec3 = 2;
	m_Channel_SecX = 3;
	m_Model_Sec = 0;
	m_Delay_A = 0;
	m_Delay_B = 0;
	m_Delay_C = 0;
	m_Delay_X = 0;
	m_Delay = 0;
	m_Primary_Current_Scaling = 3000;
	if(pParent->DIM_public==8192)
	{
	m_shortAD1_C_DC1 = DIM_DCS;
	m_shortAD1_C_DC2 = DIM_DCS;
	m_shortAD1_C_DC4 = DIM_DCS;

	m_shortAD1_C_DC5 = DIM_DCS;
	m_shortAD1_C_DC6 = DIM_DCS;
	m_shortAD1_C_DC7 = DIM_DCS;
	m_shortAD1_C_DC8 = DIM_DCS;

	m_shortAD1_C_DC9 = DIM_DCS;
	m_shortAD1_C_DC10 = DIM_DCS;
	m_shortAD1_C_DC11 = DIM_DCS;
	m_shortAD1_C_DC12 = DIM_DCS;

	m_shortAD1_V_DC1 = DIM_DCS;
	m_shortAD1_V_DC2 = DIM_DCS;
	m_shortAD1_V_DC3 = DIM_DCS;
	m_shortAD1_V_DC4 = DIM_DCS;

    m_shortAD1_V_DC5 = DIM_DCS;

	m_shortAD1_V_DC6 = DIM_DCS;
	m_shortAD1_V_DC7 = DIM_DCS;
    m_shortAD1_V_DC8 = DIM_DCS;

    m_shortAD1_V_DC9 = DIM_DCS;

	m_shortAD1_V_DC10 = DIM_DCS;
	m_shortAD1_V_DC11 = DIM_DCS;
    m_shortAD1_V_DC12 = DIM_DCS;

	m_shortAD1_I1a = DIM_IS;
	m_shortAD1_I1b = DIM_IS;
	m_shortAD1_I1c = DIM_IS;
	m_shortAD1_I2a = DIM_IS;
	m_shortAD1_I2b = DIM_IS;
	m_shortAD1_I2c = DIM_IS;
	m_shortAD1_U1a = DIM_US;
	m_shortAD1_U1b = DIM_US;
	m_shortAD1_U1c = DIM_US;
	m_shortAD1_U2a = DIM_US;
	m_shortAD1_U2b = DIM_US;
	m_shortAD1_U2c = DIM_US;
	}
	else if(pParent->DIM_public==16384)
	{
  /*  m_shortAD1_C_DC1 = DIM_DC;
	m_shortAD1_C_DC2 = DIM_DC;
	m_shortAD1_C_DC3 = DIM_DC;
	m_shortAD1_C_DC4 = DIM_DC;

    m_shortAD1_C_DC5 = DIM_DC;
    m_shortAD1_C_DC6 = DIM_DC;
    m_shortAD1_C_DC7 = DIM_DC;
    m_shortAD1_C_DC8 = DIM_DC;

	m_shortAD1_V_DC1 = DIM_DC;
	m_shortAD1_V_DC2 = DIM_DC;
	m_shortAD1_V_DC3 = DIM_DC;
	m_shortAD1_V_DC4 = DIM_DC;

    m_shortAD1_V_DC5 = DIM_DC;

	
	m_shortAD1_V_DC6 = DIM_DC;

	m_shortAD1_V_DC7 = DIM_DC;

	m_shortAD1_V_DC8 = DIM_DC;
*/


	m_shortAD1_C_DC1 = 50360;
	m_shortAD1_C_DC2 = 50360;
	m_shortAD1_C_DC3 = 50360;
	m_shortAD1_C_DC4 = 50360;

    m_shortAD1_C_DC5 = 50360;
    m_shortAD1_C_DC6 = 50360;
    m_shortAD1_C_DC7 = 50360;
    m_shortAD1_C_DC8 = 50360;

    m_shortAD1_C_DC9 = 50360;
    m_shortAD1_C_DC10 = 50360;
    m_shortAD1_C_DC11 = 50360;
    m_shortAD1_C_DC12 = 50360;

	m_shortAD1_V_DC1 = 0;
	m_shortAD1_V_DC2 = 0;
	m_shortAD1_V_DC3 = 0;
	m_shortAD1_V_DC4 = 0;

    m_shortAD1_V_DC5 = 0;

	
	m_shortAD1_V_DC6 = 0;

	m_shortAD1_V_DC7 = 0;

	m_shortAD1_V_DC8 = 0;

    m_shortAD1_V_DC9 = 0;	
	m_shortAD1_V_DC10 = 0;
	m_shortAD1_V_DC11 = 0;
	m_shortAD1_V_DC12 = 0;


	m_shortAD1_I1a = DIM_I;
	m_shortAD1_I1b = DIM_I;
	m_shortAD1_I1c = DIM_I;
	m_shortAD1_I2a = DIM_I;
	m_shortAD1_I2b = DIM_I;
	m_shortAD1_I2c = DIM_I;
	m_shortAD1_U1a = DIM_U;
	m_shortAD1_U1b = DIM_U;
	m_shortAD1_U1c = DIM_U;
	m_shortAD1_U2a = DIM_U;
	m_shortAD1_U2b = DIM_U;
	m_shortAD1_U2c = DIM_U;
	}
	m_shortAD1_V_LINE1 = 500;
	m_shortAD1_V_LINE2 = 500;
	m_shortAD1_C_LINE1 = 3000;
	m_shortAD1_C_LINE2 = 3000;
	UpdateData(FALSE);
}



void Dlg_AD1::OnButtonAd1Fetch() 
{
	// TODO: Add your control notification handler code here
	AD1_FUNCTION =IDC_BUTTON_AD1_FETCH;
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
//	pParent->
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_AD1_FETCH;

	pParent->ACAD_block_33.Station_adr=0;
	pParent->ACAD_block_33.Telegram_Nr=33;
	pParent->ACAD_block_33.F1_field=0;
	pParent->ACAD_block_33.F2_field=0x80;
	pParent->ACAD_block_33.Data=(UCHAR *)"";

	pParent->Fun_Connect(pParent->ACAD_block_33,0);


//	UpdateData(FALSE);
//	ValidData[4]=ValidData[5]=0;ValidData[6]=ValidData[7]=0;ValidData[8]=ValidData[9]=0;
	SetTimer(IDC_BUTTON_AD1_FETCH,666,NULL);
}

void Dlg_AD1::OnButtonAd1Apply() 
{
	
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	AD1_FUNCTION=IDC_BUTTON_AD1_FETCH;
//	UpdateData(FALSE);
	AD1_FUNCTION =IDC_BUTTON_AD1_APPLY;

	


	UINT Temp_UINT=0;
	unsigned short Temp_short=0;
	UCHAR Temp_UCHAR=0;
	BOOL  Temp_BOOL=FALSE;

	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_AD1_APPLY;

	UpdateData(TRUE);

//////////////////////////////////////////////////////////////////////////
//            数据转换   到数组ValidData[]中
//////////////////////////////////////////////////////////////////////////

	Temp_short =m_shortAD1_U1a;                  //U1a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[0]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[1]=Temp_UCHAR;

	Temp_short =m_shortAD1_U1b;                  //U1b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[2]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[3]=Temp_UCHAR;

	Temp_short =m_shortAD1_U1c;                  //U1c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[4]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[5]=Temp_UCHAR;

	Temp_short =m_shortAD1_I1a;                  //I1a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[6]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[7]=Temp_UCHAR;

	Temp_short =m_shortAD1_I1b;                  //I1b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[8]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[9]=Temp_UCHAR;

	Temp_short =m_shortAD1_I1c;                  //I1c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[10]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[11]=Temp_UCHAR;

	Temp_short =m_shortAD1_U2a;                  //U2a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[12]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[13]=Temp_UCHAR;

	Temp_short =m_shortAD1_U2b;                  //U2b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[14]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[15]=Temp_UCHAR;

	Temp_short =m_shortAD1_U2c;                  //U2c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[16]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[17]=Temp_UCHAR;

	Temp_short =m_shortAD1_I2a;                  //I2a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[18]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[19]=Temp_UCHAR;

	Temp_short =m_shortAD1_I2b;                  //I2b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[20]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[21]=Temp_UCHAR;

	Temp_short =m_shortAD1_I2c;                  //I2c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[22]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[23]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC1;                  //V DC1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[24]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[25]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC2;                  //V DC2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[26]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[27]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC3;                  //V DC3
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[28]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[29]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC4;                  //V DC4
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[30]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[31]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC5;                  //V DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[32]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[33]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC6;                  //V DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[34]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[35]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC7;                  //V DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[36]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[37]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC8;                  //V DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[38]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[39]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC9;                  //V DC9
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[40]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[41]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC10;                  //V DC10
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[42]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[43]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC11;                  //V DC11
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[44]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[45]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC12;                  //V DC12
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[46]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[47]=Temp_UCHAR;


	Temp_short =m_shortAD1_C_DC1;                  //C DC1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[48]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[49]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC2;                  //C DC2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[50]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[51]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC3;                  //C DC3
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[52]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[53]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC4;                  //C DC4
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[54]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[55]=Temp_UCHAR;


	Temp_short =m_shortAD1_C_DC5;                  //C DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[56]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[57]=Temp_UCHAR;


	Temp_short =m_shortAD1_C_DC6;                  //C DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[58]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[59]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC7;                  //C DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[60]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[61]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC8;                  //C DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[62]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[63]=Temp_UCHAR;

    Temp_short =m_shortAD1_C_DC9;                  //C DC9
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[64]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[65]=Temp_UCHAR;


	Temp_short =m_shortAD1_C_DC10;                  //C DC10
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[66]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[67]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC11;                  //C DC11
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[68]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[69]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC12;                  //C DC12
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[70]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[71]=Temp_UCHAR;


	Temp_short =m_shortAD1_V_LINE1;                  //V LINE1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[72]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[73]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_LINE2;                  //V LINE2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[74]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[75]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_LINE1;                  //C LINE1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[76]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[77]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_LINE2;                  //C LINE2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[78]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[79]=Temp_UCHAR;

/*	Temp_UCHAR =(UCHAR)m_nAD1_ActiveCS;                     //Active Channel Select
	DATA[48]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_VoltSTD1;                     //Voltage sent to dp1
	DATA[49]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_VoltSTD2;                     //Voltage Sent To DP2
	DATA[50]=Temp_UCHAR;

    
	Temp_UCHAR =(UCHAR)m_nAD1_SecCNV;                       //Second Current Nom Value
	DATA[51]=Temp_UCHAR;
    pParent->Current_Style=m_nAD1_SecCNV;
*/

	Temp_UCHAR =(UCHAR)m_Model_Sec;                         //Interpolation Model Select
	DATA[80]=Temp_UCHAR;

    Temp_short =m_Delay;                                    //Common Delay 
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[81]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[82]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)(m_Primary_Current_Scaling/25);      //Scaling
	DATA[83]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_SecVNV;                       //Second Voltage Nom Value
	DATA[84]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS;                         //DC1 Source Select
	DATA[85]=Temp_UCHAR;
    pParent->DC_V_I_select[0]=m_nAD1_DCSS;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS2;                         //DC2 Source Select
	DATA[86]=Temp_UCHAR;
    pParent->DC_V_I_select[1]=m_nAD1_DCSS2;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS3;                         //DC3 Source Select
	DATA[87]=Temp_UCHAR;
	pParent->DC_V_I_select[2]=m_nAD1_DCSS3;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS4;                         //DC4 Source Select
	DATA[88]=Temp_UCHAR;
    pParent->DC_V_I_select[3]=m_nAD1_DCSS4;


	Temp_UCHAR =(UCHAR)m_nAD1_DCSS5;                         //DC5 Source Select
	DATA[89]=Temp_UCHAR;
    pParent->DC_V_I_select[4]=m_nAD1_DCSS5;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS6;                         //DC6 Source Select
	DATA[90]=Temp_UCHAR;
    pParent->DC_V_I_select[5]=m_nAD1_DCSS6;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS7;                         //DC7 Source Select
	DATA[91]=Temp_UCHAR;
    pParent->DC_V_I_select[6]=m_nAD1_DCSS7;


	Temp_UCHAR =(UCHAR)m_nAD1_DCSS8;                         //DC8 Source Select
	DATA[92]=Temp_UCHAR;
    pParent->DC_V_I_select[7]=m_nAD1_DCSS8;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS9;                         //DC9 Source Select
	DATA[93]=Temp_UCHAR;
    pParent->DC_V_I_select[8]=m_nAD1_DCSS9;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS10;                         //DC10 Source Select
	DATA[94]=Temp_UCHAR;
    pParent->DC_V_I_select[9]=m_nAD1_DCSS10;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS11;                         //DC11 Source Select
	DATA[95]=Temp_UCHAR;
    pParent->DC_V_I_select[10]=m_nAD1_DCSS11;


	Temp_UCHAR =(UCHAR)m_nAD1_DCSS12;                         //DC12 Source Select
	DATA[96]=Temp_UCHAR;
    pParent->DC_V_I_select[11]=m_nAD1_DCSS12;



	Temp_UCHAR =(UCHAR)m_Channel_Sec1;                       //Channel Seclect IA
	DATA[97]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_Channel_Sec2;                       //Channel Seclect IB
	DATA[98]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_Channel_Sec3;                       //Channel Seclect IC
	DATA[99]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_Channel_SecX;                       //Channel Seclect IX
	DATA[100]=Temp_UCHAR;

	Temp_short = m_Delay_A;                                   //Channel Delay IA
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[101]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[102]=Temp_UCHAR;

	Temp_short = m_Delay_B;                                   //Channel Delay IB
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[103]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[104]=Temp_UCHAR;

	Temp_short = m_Delay_C;                                   //Channel Delay IC
	Temp_UCHAR = Temp_short & 0x00ff; 
	DATA[105]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[106]=Temp_UCHAR;

	Temp_short = m_Delay_X;                                   //Channel Delay IX
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[107]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[108]=Temp_UCHAR;
/*

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS5;                         //DC5 Source Select
	DATA[69]=Temp_UCHAR;
    pParent->DC_V_I_select[4]=m_nAD1_DCSS5;

	Temp_short =m_shortAD1_V_DC5;                  //V DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[72]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[73]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC5;                  //C DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[74]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[75]=Temp_UCHAR;



	Temp_UCHAR =(UCHAR)m_nAD1_DCSS6;                         //DC6 Source Select
	DATA[76]=Temp_UCHAR;
    pParent->DC_V_I_select[5]=m_nAD1_DCSS6;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS7;                         //DC7 Source Select
	DATA[77]=Temp_UCHAR;
    pParent->DC_V_I_select[6]=m_nAD1_DCSS7;


	Temp_UCHAR =(UCHAR)m_nAD1_DCSS8;                         //DC8 Source Select
	DATA[78]=Temp_UCHAR;
    pParent->DC_V_I_select[7]=m_nAD1_DCSS8;

	Temp_short =m_shortAD1_V_DC6;                  //V DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[79]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[80]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC7;                  //V DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[81]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[82]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC8;                  //V DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[83]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[84]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC6;                  //C DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[85]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[86]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC7;                  //C DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[87]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[88]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC8;                  //C DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[89]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[90]=Temp_UCHAR;
*/

	DATA[109]=0;                                            //bak
	DATA[110]='\0';
	
//	pTX_DATA = DATA;

	UpdateData(FALSE);
//////////////////////////////////////////////////////////////////////////
//                   end
//////////////////////////////////////////////////////////////////////////

	

pParent->Connect_Telegram.PACK_SELECT=TRUE;
pParent->Zero_NR=0;
for(int tt=0; tt<110;tt++)
{
	pParent->Connect_Telegram.ValidDataToPack[tt] =DATA[tt];
	if(DATA[tt]==0)
		pParent->Zero_NR++;
}
pParent->Zero_NR--;
pParent->Msg_block_32.Station_adr =0;
pParent->Msg_block_32.Telegram_Nr=32;
pParent->Msg_block_32.F1_field =0;
pParent->Msg_block_32.F2_field =0X80;
//pParent->Msg_block_34.Data=(UCHAR *)pTX_DATA;
pParent->Fun_Connect(pParent->Msg_block_32,pParent->Zero_NR);
	




}



void Dlg_AD1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==IDC_BUTTON_AD1_FETCH)
	{
		KillTimer(IDC_BUTTON_AD1_FETCH);
		UpdateData(TRUE);
		UpdateData(FALSE);
//		MessageBox("dd");
	}
	CDialog::OnTimer(nIDEvent);
}

void Dlg_AD1::OnCancel() 
{	
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();

	// TODO: Add extra cleanup here

	UINT Temp_UINT=0;
	unsigned short Temp_short=0;
	UCHAR Temp_UCHAR=0;
	BOOL  Temp_BOOL=FALSE;

	UpdateData(TRUE);
	Temp_short =m_shortAD1_U1a;                  //U1a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[0]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[1]=Temp_UCHAR;

	Temp_short =m_shortAD1_U1b;                  //U1b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[2]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[3]=Temp_UCHAR;

	Temp_short =m_shortAD1_U1c;                  //U1c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[4]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[5]=Temp_UCHAR;

	Temp_short =m_shortAD1_I1a;                  //I1a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[6]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[7]=Temp_UCHAR;

	Temp_short =m_shortAD1_I1b;                  //I1b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[8]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[9]=Temp_UCHAR;

	Temp_short =m_shortAD1_I1c;                  //I1c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[10]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[11]=Temp_UCHAR;

	Temp_short =m_shortAD1_U2a;                  //U2a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[12]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[13]=Temp_UCHAR;

	Temp_short =m_shortAD1_U2b;                  //U2b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[14]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[15]=Temp_UCHAR;

	Temp_short =m_shortAD1_U2c;                  //U2c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[16]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[17]=Temp_UCHAR;

	Temp_short =m_shortAD1_I2a;                  //I2a
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[18]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[19]=Temp_UCHAR;

	Temp_short =m_shortAD1_I2b;                  //I2b
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[20]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[21]=Temp_UCHAR;

	Temp_short =m_shortAD1_I2c;                  //I2c
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[22]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[23]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC1;                  //V DC1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[24]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[25]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC2;                  //V DC2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[26]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[27]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC3;                  //V DC3
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[28]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[29]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC4;                  //V DC4
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[30]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[31]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_V_DC5;                  //V DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[32]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[33]=Temp_UCHAR;


	
	Temp_short =m_shortAD1_V_DC6;                  //V DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[34]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[35]=Temp_UCHAR;


	Temp_short =m_shortAD1_V_DC7;                  //V DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[36]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[37]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC8;                  //V DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[38]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[39]=Temp_UCHAR;


		
	Temp_short =m_shortAD1_V_DC9;                  //V DC9
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[40]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[41]=Temp_UCHAR;


	
	Temp_short =m_shortAD1_V_DC10;                  //V DC10
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[42]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[43]=Temp_UCHAR;


	Temp_short =m_shortAD1_V_DC11;                  //V DC11
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[44]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[45]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC12;                  //V DC12
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[46]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[47]=Temp_UCHAR;


	Temp_short =m_shortAD1_C_DC1;                  //C DC1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[48]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[49]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC2;                  //C DC2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[50]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[51]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC3;                  //C DC3
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[52]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[53]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC4;                  //C DC4
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[54]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[55]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC5;                  //C DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[56]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[57]=Temp_UCHAR;

	
	Temp_short =m_shortAD1_C_DC6;                  //C DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[58]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[59]=Temp_UCHAR;
	
	Temp_short =m_shortAD1_C_DC7;                  //C DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[60]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[61]=Temp_UCHAR;
	
	Temp_short =m_shortAD1_C_DC8;                  //C DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[62]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[63]=Temp_UCHAR;


	Temp_short =m_shortAD1_C_DC9;                  //C DC9
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[64]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[65]=Temp_UCHAR;

	
	Temp_short =m_shortAD1_C_DC10;                  //C DC10
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[66]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[67]=Temp_UCHAR;
	
	Temp_short =m_shortAD1_C_DC11;                  //C DC11
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[68]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[69]=Temp_UCHAR;
	
	Temp_short =m_shortAD1_C_DC12;                  //C DC12
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[70]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[71]=Temp_UCHAR;


	Temp_short =m_shortAD1_V_LINE1;                  //V LINE1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[72]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[73]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_LINE2;                  //V LINE2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[74]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[75]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_LINE1;                  //C LINE1
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[76]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[77]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_LINE2;                  //C LINE2
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[78]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[79]=Temp_UCHAR;
/*
	Temp_UCHAR =(UCHAR)m_nAD1_ActiveCS;                     //Active Channel Select
	DATA[48]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_VoltSTD1;                     //Voltage sent to dp1
	DATA[49]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_VoltSTD2;                     //Voltage Sent To DP2
	DATA[50]=Temp_UCHAR;
    
	Temp_UCHAR =(UCHAR)m_nAD1_SecCNV;                       //Second Current Nom Value
	DATA[51]=Temp_UCHAR;
    pParent->Current_Style=m_nAD1_SecCNV;
*/	

	Temp_UCHAR =(UCHAR)m_Model_Sec;                         //Interpolation Model Select
	DATA[80]=Temp_UCHAR;

	Temp_short =m_Delay;                                    //Common Delay
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[81]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[82]=Temp_UCHAR;
    
	Temp_UCHAR =(UCHAR)(m_Primary_Current_Scaling/25);      //Scaling
	DATA[83]=Temp_UCHAR;
    pParent->Current_Style=m_nAD1_SecCNV;

	Temp_UCHAR =(UCHAR)m_nAD1_SecVNV;                       //Second Voltage Nom Value
	DATA[84]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS;                         //DC1 Source Select
	DATA[85]=Temp_UCHAR;
   	pParent->DC_V_I_select[0]=m_nAD1_DCSS;
	
	Temp_UCHAR =(UCHAR)m_nAD1_DCSS2;                         //DC2 Source Select
	DATA[86]=Temp_UCHAR;
    pParent->DC_V_I_select[1]=m_nAD1_DCSS2;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS3;                         //DC3 Source Select
	DATA[87]=Temp_UCHAR;
    pParent->DC_V_I_select[2]=m_nAD1_DCSS3;


	Temp_UCHAR =(UCHAR)m_nAD1_DCSS4;                         //DC4 Source Select
	DATA[88]=Temp_UCHAR;
    pParent->DC_V_I_select[3]=m_nAD1_DCSS4;

		
	Temp_UCHAR =(UCHAR)m_nAD1_DCSS5;                         //DC5 Source Select
	DATA[89]=Temp_UCHAR;
    pParent->DC_V_I_select[4]=m_nAD1_DCSS5;

	
	Temp_UCHAR =(UCHAR)m_nAD1_DCSS6;                         //DC6 Source Select
	DATA[90]=Temp_UCHAR;
    pParent->DC_V_I_select[5]=m_nAD1_DCSS6;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS7;                         //DC7 Source Select
	DATA[91]=Temp_UCHAR;
    pParent->DC_V_I_select[6]=m_nAD1_DCSS7;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS8;                         //DC8 Source Select
	DATA[92]=Temp_UCHAR;
    pParent->DC_V_I_select[7]=m_nAD1_DCSS8;


	Temp_UCHAR =(UCHAR)m_nAD1_DCSS9;                         //DC9 Source Select
	DATA[93]=Temp_UCHAR;
    pParent->DC_V_I_select[8]=m_nAD1_DCSS9;

	
	Temp_UCHAR =(UCHAR)m_nAD1_DCSS10;                         //DC10 Source Select
	DATA[94]=Temp_UCHAR;
    pParent->DC_V_I_select[9]=m_nAD1_DCSS10;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS11;                         //DC11 Source Select
	DATA[95]=Temp_UCHAR;
    pParent->DC_V_I_select[10]=m_nAD1_DCSS11;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS12;                         //DC12 Source Select
	DATA[96]=Temp_UCHAR;
    pParent->DC_V_I_select[11]=m_nAD1_DCSS12;


	Temp_UCHAR =(UCHAR)m_Channel_Sec1;                       //Channel Seclect IA
	DATA[97]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_Channel_Sec2;                       //Channel Seclect IB
	DATA[98]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_Channel_Sec3;                       //Channel Seclect IC
	DATA[99]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_Channel_SecX;                       //Channel Seclect IX
	DATA[100]=Temp_UCHAR;

    Temp_short =m_Delay_A;                                   //Channel Delay IA
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[101]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[102]=Temp_UCHAR;

	Temp_short =m_Delay_B;                                   //Channel Delay IB
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[103]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[104]=Temp_UCHAR;

	Temp_short =m_Delay_C;                                   //Channel Delay IC
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[105]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[106]=Temp_UCHAR;

	Temp_short =m_Delay_X;                                   //Channel Delay IX
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[107]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[108]=Temp_UCHAR;
/*

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS5;                         //DC5 Source Select
	DATA[69]=Temp_UCHAR;
    pParent->DC_V_I_select[4]=m_nAD1_DCSS5;


	Temp_short =m_shortAD1_V_DC5;                  //V DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[71]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[72]=Temp_UCHAR;

	Temp_short =m_shortAD1_C_DC5;                  //C DC5
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[73]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[74]=Temp_UCHAR;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS6;                         //DC6 Source Select
	DATA[75]=Temp_UCHAR;
    pParent->DC_V_I_select[5]=m_nAD1_DCSS6;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS7;                         //DC7 Source Select
	DATA[76]=Temp_UCHAR;
    pParent->DC_V_I_select[6]=m_nAD1_DCSS7;

	Temp_UCHAR =(UCHAR)m_nAD1_DCSS8;                         //DC8 Source Select
	DATA[77]=Temp_UCHAR;
    pParent->DC_V_I_select[7]=m_nAD1_DCSS8;


	Temp_short =m_shortAD1_V_DC6;                  //V DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[78]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[79]=Temp_UCHAR;


	Temp_short =m_shortAD1_V_DC7;                  //V DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[80]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[81]=Temp_UCHAR;

	Temp_short =m_shortAD1_V_DC8;                  //V DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[82]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[83]=Temp_UCHAR;

		
	Temp_short =m_shortAD1_C_DC6;                  //C DC6
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[84]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[85]=Temp_UCHAR;
	
	Temp_short =m_shortAD1_C_DC7;                  //C DC7
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[86]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[87]=Temp_UCHAR;
	
	Temp_short =m_shortAD1_C_DC8;                  //C DC8
	Temp_UCHAR = Temp_short & 0x00ff;
	DATA[88]=Temp_UCHAR;
	Temp_UCHAR = Temp_short>>8;
	DATA[89]=Temp_UCHAR;
*/
	DATA[109]=0;												//bak
	DATA[110]='\0';


	CDialog::OnCancel();
}
/*
void Dlg_AD1::OnRADIOAD1ActiveCS() 
{
	// TODO: Add your control notification handler code here
//		UpdateData(TRUE);
	m_nAD1_ActiveCS=0;
//	UpdateData(FALSE);
}

void Dlg_AD1::OnRADIOAD1ActiveCS1() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_ActiveCS=1;
//	UpdateData(FALSE);
}
*/
void Dlg_AD1::OnRADIOAD1SecCNV() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_SecCNV =0;
//	UpdateData(FALSE);
}

void Dlg_AD1::OnRADIOAD1SecCNV1() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
//	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
//	pParent->Current_Style=1;
	m_nAD1_SecCNV =1;
//	UpdateData(FALSE);
}
/*
void Dlg_AD1::OnRADIOAD1SecVNV() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_SecVNV =0;
//	UpdateData(FALSE);
}
*/
/*
void Dlg_AD1::OnRADIOAD1SecVNV1() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_SecVNV =1;
//	UpdateData(FALSE);
}
*/
/*
void Dlg_AD1::OnRADIOAD1VoltSTD1() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_VoltSTD1 =0;
//	UpdateData(FALSE);
}
*/
void Dlg_AD1::OnRADIOAD1VoltSTD11() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_VoltSTD1 =1;
//	UpdateData(FALSE);
}

void Dlg_AD1::OnRADIOAD1VoltSTD2() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_VoltSTD2 =0;
//	UpdateData(FALSE);
}
/*
void Dlg_AD1::OnRADIOAD1VoltSTD21() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_VoltSTD2 =1;
//	UpdateData(FALSE);
}
*/
void Dlg_AD1::OnRadio1Ad1Dcss() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	m_nAD1_DCSS =0;
//	UpdateData(FALSE);
}

void Dlg_AD1::OnRadio1Ad1Dcss1() 
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	
	m_nAD1_DCSS =1;
//	UpdateData(FALSE);
}

void Dlg_AD1::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	//20240618shy

  

//	m_nAD1_DCSS2=-1;
    m_nAD1_DCSS2=m_nAD1_DCSS3=m_nAD1_DCSS4 =m_nAD1_DCSS5 =m_nAD1_DCSS6=m_nAD1_DCSS7=m_nAD1_DCSS8=m_nAD1_DCSS=m_nAD1_DCSS9 =m_nAD1_DCSS10=m_nAD1_DCSS11=m_nAD1_DCSS12 =1;
	//
	// TODO: Add your message handler code here

	/*m_nAD1_DCSS2=m_nAD1_DCSS3=m_nAD1_DCSS4=m_nAD1_DCSS =m_nAD1_SecVNV =m_nAD1_VoltSTD1=m_nAD1_VoltSTD2=m_nAD1_SecCNV=m_nAD1_ActiveCS=0;
	m_shortAD1_C_LINE1=m_shortAD1_C_LINE2=m_shortAD1_V_LINE1=m_shortAD1_V_LINE2=0;
	m_shortAD1_C_DC1=m_shortAD1_C_DC2=m_shortAD1_C_DC3=m_shortAD1_C_DC4=0;
	m_shortAD1_V_DC1=m_shortAD1_V_DC2=m_shortAD1_V_DC3=m_shortAD1_V_DC4=0;
	m_shortAD1_I1a=m_shortAD1_I1b=m_shortAD1_I1c=m_shortAD1_I2c=m_shortAD1_I2a=m_shortAD1_I2b=0;
	m_shortAD1_U1a=m_shortAD1_U1b=m_shortAD1_U1c=0;
	m_shortAD1_U2a=m_shortAD1_U2b=m_shortAD1_U2c=0;
*/
	UpdateData(FALSE);
}






void Dlg_AD1::OnRadio1Ad1Dcss2() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS2 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss22() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS2 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss3() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS3 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss33() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS3 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss4() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS4 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss44() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS4 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss5() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS5 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss55() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS5 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss6() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS6 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss66() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS6 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss7() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS7 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss77() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS7 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss8() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS8 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss88() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS8 = 1;
}

void Dlg_AD1::OnChangeEditAd1VDc1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void Dlg_AD1::OnRadio1Ad1Dcss9() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS9 = 0;
}



void Dlg_AD1::OnRadio1Ad1Dcss99() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS9 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss10() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS10 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss1010() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS10 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss11() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS11 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss1111() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS11 = 1;
}

void Dlg_AD1::OnRadio1Ad1Dcss12() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS12 = 0;
}

void Dlg_AD1::OnRadio1Ad1Dcss1212() 
{
	// TODO: Add your control notification handler code here
	m_nAD1_DCSS12 = 1;
}
