// Dlg_Message.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_Message.h"
#include "Dlg_ZJM.h"
#include "new1Dlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_Message dialog


Dlg_Message::Dlg_Message(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_Message::IDD, pParent)
{

	//{{AFX_DATA_INIT(Dlg_Message)
	m_Message_CheckChannel1 = FALSE;
	m_Message_CheckChannel10 = FALSE;
	m_Message_CheckChannel11 = FALSE;
	m_Message_CheckChannel12 = FALSE;
	m_Message_CheckChannel13 = FALSE;
	m_Message_CheckChannel14 = FALSE;
	m_Message_CheckChannel15 = FALSE;
	m_Message_CheckChannel16 = FALSE;
	m_Message_CheckChannel17 = FALSE;
	m_Message_CheckChannel18 = FALSE;
	m_Message_CheckChannel19 = FALSE;
	m_Message_CheckChannel2 = FALSE;
	m_Message_CheckChannel20 = FALSE;
	m_Message_CheckChannel21 = FALSE;
	m_Message_CheckChannel22 = FALSE;
	m_Message_CheckChannel3 = FALSE;
	m_Message_CheckChannel4 = FALSE;
	m_Message_CheckChannel5 = FALSE;
	m_Message_CheckChannel6 = FALSE;
	m_Message_CheckChannel7 = FALSE;
	m_Message_CheckChannel8 = FALSE;
	m_Message_CheckChannel9 = FALSE;
	m_Message_DataInvalid = FALSE;
	m_Message_Interpolation = FALSE;
	m_Message_Mode = FALSE;
	m_Message_OutputType = FALSE;
	m_Message_PHHealth = FALSE;
	m_Message_RangeFlag = FALSE;
	m_Message_SysInvalid = FALSE;
	m_Message_DEC=0;
	m_Message_Channel1 = _T("");
	m_Message_LDName = _T("");
	m_Message_Channel10 = _T("");
	m_Message_Channel11 = _T("");
	m_Message_Channel12 = _T("");
	m_Message_Channel13 = _T("");
	m_Message_Channel14 = _T("");
	m_Message_Channel15 = _T("");
	m_Message_Channel16 = _T("");
	m_Message_Channel17 = _T("");
	m_Message_Channel18 = _T("");
	m_Message_Channel19 = _T("");
	m_Message_Channel2 = _T("");
	m_Message_Channel20 = _T("");
	m_Message_Channel21 = _T("");
	m_Message_Channel22 = _T("");
	m_Message_Channel3 = _T("");
	m_Message_Channel4 = _T("");
	m_Message_Channel5 = _T("");
	m_Message_Channel6 = _T("");
	m_Message_Channel7 = _T("");
	m_Message_Channel8 = _T("");
	m_Message_Channel9 = _T("");
	m_Message_DataSetName = _T("");
	m_Message_Lenth = _T("");
	m_Message_LNName = _T("");
	m_Message_NeutArtg = _T("");
	m_Message_PhsAArtg = _T("");
	m_Message_PhsAVrtg = _T("");
	m_Message_SmpCtr = _T("");
	m_Message_StatusWord1 = _T("");
	m_Message_StatusWord2 = _T("");
	m_Message_tdr = _T("");
	//}}AFX_DATA_INIT
}

int buffer[100];
void Dlg_Message::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_Message)
	DDX_Check(pDX, IDC_Channel1_CHECK, m_Message_CheckChannel1);
	DDX_Check(pDX, IDC_Channel10_CHECK, m_Message_CheckChannel10);
	DDX_Check(pDX, IDC_Channel11_CHECK, m_Message_CheckChannel11);
	DDX_Check(pDX, IDC_Channel12_CHECK, m_Message_CheckChannel12);
	DDX_Check(pDX, IDC_Channel13_CHECK, m_Message_CheckChannel13);
	DDX_Check(pDX, IDC_Channel14_CHECK, m_Message_CheckChannel14);
	DDX_Check(pDX, IDC_Channel15_CHECK, m_Message_CheckChannel15);
	DDX_Check(pDX, IDC_Channel16_CHECK, m_Message_CheckChannel16);
	DDX_Check(pDX, IDC_Channel17_CHECK, m_Message_CheckChannel17);
	DDX_Check(pDX, IDC_Channel18_CHECK, m_Message_CheckChannel18);
	DDX_Check(pDX, IDC_Channel19_CHECK, m_Message_CheckChannel19);
	DDX_Check(pDX, IDC_Channel2_CHECK, m_Message_CheckChannel2);
	DDX_Check(pDX, IDC_Channel20_CHECK, m_Message_CheckChannel20);
	DDX_Check(pDX, IDC_Channel21_CHECK, m_Message_CheckChannel21);
	DDX_Check(pDX, IDC_Channel22_CHECK, m_Message_CheckChannel22);
	DDX_Check(pDX, IDC_Channel3_CHECK, m_Message_CheckChannel3);
	DDX_Check(pDX, IDC_Channel4_CHECK, m_Message_CheckChannel4);
	DDX_Check(pDX, IDC_Channel5_CHECK, m_Message_CheckChannel5);
	DDX_Check(pDX, IDC_Channel6_CHECK, m_Message_CheckChannel6);
	DDX_Check(pDX, IDC_Channel7_CHECK, m_Message_CheckChannel7);
	DDX_Check(pDX, IDC_Channel8_CHECK, m_Message_CheckChannel8);
	DDX_Check(pDX, IDC_Channel9_CHECK, m_Message_CheckChannel9);
	DDX_Check(pDX, IDC_DataInvalid_CHECK, m_Message_DataInvalid);
	DDX_Check(pDX, IDC_Interpolation_CHECK, m_Message_Interpolation);
	DDX_Check(pDX, IDC_Mode_CHECK, m_Message_Mode);
	DDX_Check(pDX, IDC_OutputType_CHECK, m_Message_OutputType);
	DDX_Check(pDX, IDC_PHHealth_CHECK, m_Message_PHHealth);
	DDX_Check(pDX, IDC_RangeFlag_CHECK, m_Message_RangeFlag);
	DDX_Check(pDX, IDC_SysInvalid_CHECK, m_Message_SysInvalid);
	DDX_Radio(pDX, IDC_RADIO_Message_DEC, m_Message_DEC);
	DDX_Text(pDX, IDC_EDIT_Message_Channel1, m_Message_Channel1);
	DDX_Text(pDX, IDC_EDIT_LDName, m_Message_LDName);
	DDX_Text(pDX, IDC_EDIT_Message_Channel10, m_Message_Channel10);
	DDX_Text(pDX, IDC_EDIT_Message_Channel11, m_Message_Channel11);
	DDX_Text(pDX, IDC_EDIT_Message_Channel12, m_Message_Channel12);
	DDX_Text(pDX, IDC_EDIT_Message_Channel13, m_Message_Channel13);
	DDX_Text(pDX, IDC_EDIT_Message_Channel14, m_Message_Channel14);
	DDX_Text(pDX, IDC_EDIT_Message_Channel15, m_Message_Channel15);
	DDX_Text(pDX, IDC_EDIT_Message_Channel16, m_Message_Channel16);
	DDX_Text(pDX, IDC_EDIT_Message_Channel17, m_Message_Channel17);
	DDX_Text(pDX, IDC_EDIT_Message_Channel18, m_Message_Channel18);
	DDX_Text(pDX, IDC_EDIT_Message_Channel19, m_Message_Channel19);
	DDX_Text(pDX, IDC_EDIT_Message_Channel2, m_Message_Channel2);
	DDX_Text(pDX, IDC_EDIT_Message_Channel20, m_Message_Channel20);
	DDX_Text(pDX, IDC_EDIT_Message_Channel21, m_Message_Channel21);
	DDX_Text(pDX, IDC_EDIT_Message_Channel22, m_Message_Channel22);
	DDX_Text(pDX, IDC_EDIT_Message_Channel3, m_Message_Channel3);
	DDX_Text(pDX, IDC_EDIT_Message_Channel4, m_Message_Channel4);
	DDX_Text(pDX, IDC_EDIT_Message_Channel5, m_Message_Channel5);
	DDX_Text(pDX, IDC_EDIT_Message_Channel6, m_Message_Channel6);
	DDX_Text(pDX, IDC_EDIT_Message_Channel7, m_Message_Channel7);
	DDX_Text(pDX, IDC_EDIT_Message_Channel8, m_Message_Channel8);
	DDX_Text(pDX, IDC_EDIT_Message_Channel9, m_Message_Channel9);
	DDX_Text(pDX, IDC_EDIT_Message_DataSetName, m_Message_DataSetName);
	DDX_Text(pDX, IDC_EDIT_Message_Lenth, m_Message_Lenth);
	DDX_Text(pDX, IDC_EDIT_Message_LNName, m_Message_LNName);
	DDX_Text(pDX, IDC_EDIT_Message_NeutArtg, m_Message_NeutArtg);
	DDX_Text(pDX, IDC_EDIT_Message_PhsAArtg, m_Message_PhsAArtg);
	DDX_Text(pDX, IDC_EDIT_Message_PhsAVrtg, m_Message_PhsAVrtg);
	DDX_Text(pDX, IDC_EDIT_Message_SmpCtr, m_Message_SmpCtr);
	DDX_Text(pDX, IDC_EDIT_Message_StatusWord1, m_Message_StatusWord1);
	DDX_Text(pDX, IDC_EDIT_Message_StatusWord2, m_Message_StatusWord2);
	DDX_Text(pDX, IDC_EDIT_Message_tdr, m_Message_tdr);
	//}}AFX_DATA_MAP

	unsigned short TempData_short=1;
	UCHAR TempData_UCHAR=1;
	UINT  TempData_UINT=1;
	BOOL  TempData_BOOL=FALSE;
	float TempData_float=0;
	
	
	if(Message_FUNCTION==IDC_BUTTON_Message_Fetch ||Message_FUNCTION==IDC_BUTTON_ZJM_OPEN||Message_FUNCTION==IDC_ZJM_Message)
	{

	TempData_UCHAR =ValidData[4];          //Lenth
	TempData_short= ValidData[5];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	char Cnt_TempBuffer[10];
	buffer[0]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Lenth= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Lenth="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Lenth+="0";
	}
}
m_Message_Lenth+=Cnt_TempBuffer;
	}

	TempData_UCHAR = ValidData[6];         //LNName
	TempData_UINT =(UINT)TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[1]=TempData_UINT;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_UINT,Cnt_TempBuffer,10); 
	m_Message_LNName= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_UINT;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=1;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_LNName="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_LNName+="0";
	}
}
m_Message_LNName+=Cnt_TempBuffer;
	}

	TempData_UCHAR = ValidData[7];         //DataSetName
	TempData_UINT =(UINT)TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[2]=TempData_UINT;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_UINT,Cnt_TempBuffer,10); 
	m_Message_DataSetName= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_UINT;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=1;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_DataSetName="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_DataSetName+="0";
	}
}
m_Message_DataSetName+=Cnt_TempBuffer;
	}
	

	TempData_UCHAR =ValidData[8];          //LDName
	TempData_short= ValidData[9];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[3]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_LDName= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_LDName="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_LDName+="0";
	}
}
m_Message_LDName+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[10];          //m_Message_PhsAArtg
	TempData_short= ValidData[11];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[4]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_PhsAArtg= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_PhsAArtg="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_PhsAArtg+="0";
	}
}
m_Message_PhsAArtg+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[12];          //m_Message_NeutArtg
	TempData_short= ValidData[13];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[5]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_NeutArtg= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_NeutArtg="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_NeutArtg+="0";
	}
}
m_Message_NeutArtg+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[14];          //m_Message_PhsAVrtg
	TempData_short= ValidData[15];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[6]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_PhsAVrtg= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_PhsAVrtg="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_PhsAVrtg+="0";
	}
}
m_Message_PhsAVrtg+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[16];          //m_Message_tdr
	TempData_short= ValidData[17];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[7]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_tdr= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_tdr="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_tdr+="0";
	}
}
m_Message_tdr+=Cnt_TempBuffer;
	}


	TempData_UCHAR =ValidData[18];          //m_Message_SmpCtr
	TempData_short= ValidData[19];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[8]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_SmpCtr= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_SmpCtr="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_SmpCtr+="0";
	}
}
m_Message_SmpCtr+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[20];          //Channel1
	TempData_short= ValidData[21];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	
	buffer[9]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel1= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel1="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel1+="0";
	}
}
m_Message_Channel1+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[22];          //Channel2
	TempData_short= ValidData[23];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
    buffer[10]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel2= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel2="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel2+="0";
	}
}
m_Message_Channel2+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[24];          //Channel3
	TempData_short= ValidData[25];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[11]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel3= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel3="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel3+="0";
	}
}
m_Message_Channel3+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[26];          //Channel4
	TempData_short= ValidData[27];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	buffer[12]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel4= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel4="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel4+="0";
	}
}
m_Message_Channel4+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[28];          //Channel5
	TempData_short= ValidData[29];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[13]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel5= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel5="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel5+="0";
	}
}
m_Message_Channel5+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[30];          //Channel6
	TempData_short= ValidData[31];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[14]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel6= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel6="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel6+="0";
	}
}
m_Message_Channel6+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[32];          //Channel7
	TempData_short= ValidData[33];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[15]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel7= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel7="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel7+="0";
	}
}
m_Message_Channel7+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[34];          //Channel8
	TempData_short= ValidData[35];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[16]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel8= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel8="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel8+="0";
	}
}
m_Message_Channel8+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[36];          //Channel9
	TempData_short= ValidData[37];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[17]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel9= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel9="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel9+="0";
	}
}
m_Message_Channel9+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[38];          //Channel10
	TempData_short= ValidData[39];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[18]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel10= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel10="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel10+="0";
	}
}
m_Message_Channel10+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[40];          //Channel11
	TempData_short= ValidData[41];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[19]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel11= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel11="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel11+="0";
	}
}
m_Message_Channel11+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[42];          //Channel12
	TempData_short= ValidData[43];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[20]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel12= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel12="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel12+="0";
	}
}
m_Message_Channel12+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[44];          //Channel13
	TempData_short= ValidData[45];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[21]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel13= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel13="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel13+="0";
	}
}
m_Message_Channel13+=Cnt_TempBuffer;
	}
	
	TempData_UCHAR =ValidData[46];          //Channel14
	TempData_short= ValidData[47];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[22]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel14= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel14="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel14+="0";
	}
}
m_Message_Channel14+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[48];          //Channel15
	TempData_short= ValidData[49];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[23]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel15= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel15="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel15+="0";
	}
}
m_Message_Channel15+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[50];          //Channel16
	TempData_short= ValidData[51];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[24]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel16= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel16="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel16+="0";
	}
}
m_Message_Channel16+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[52];          //Channel17
	TempData_short= ValidData[53];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[25]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel17= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel17="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel17+="0";
	}
}
m_Message_Channel17+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[54];          //Channel18
	TempData_short= ValidData[55];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[26]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel18= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel18="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel18+="0";
	}
}
m_Message_Channel18+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[56];          //Channel19
	TempData_short= ValidData[57];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[27]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel19= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel19="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel19+="0";
	}
}
m_Message_Channel19+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[58];          //Channel20
	TempData_short= ValidData[59];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[28]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel20= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel20="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel20+="0";
	}
}
m_Message_Channel20+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[60];          //Channel21
	TempData_short= ValidData[61];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[29]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel21= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel21="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel21+="0";
	}
}
m_Message_Channel21+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[62];          //Channel22
	TempData_short= ValidData[63];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[30]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_Channel22= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel22="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel22+="0";
	}
}
m_Message_Channel22+=Cnt_TempBuffer;
	}

	       

	TempData_UCHAR =ValidData[64];          //m_Message_StatusWord1
	TempData_short= ValidData[65];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[31]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_StatusWord1= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_StatusWord1="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_StatusWord1+="0";
	}
}
m_Message_StatusWord1+=Cnt_TempBuffer;
	}

	TempData_UCHAR =ValidData[66];          //m_Message_StatusWord2
	TempData_short= ValidData[67];
	TempData_short= TempData_short<<8;
	TempData_short +=TempData_UCHAR;
	memset(Cnt_TempBuffer,'\0',10);
	buffer[32]=TempData_short;
	if (m_Message_DEC==0)
	{
	_itoa(TempData_short,Cnt_TempBuffer,10); 
	m_Message_StatusWord2= Cnt_TempBuffer;
	}
	else
	{
	int dec=TempData_short;
	_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_StatusWord2="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_StatusWord2+="0";
	}
}
m_Message_StatusWord2+=Cnt_TempBuffer;
	}
	
	
	
	int x,i,a;
	x=buffer[31];
	for(i=31;i>=0;i--) 
	x>>i&1;

	a=x&0x0001;
	m_Message_PHHealth=a;

	a=x&0x0002;
	m_Message_Mode=a>>1;
	
	a=x&0x0004;
	m_Message_DataInvalid=a>>2;

    a=x&0x0008;
	m_Message_Interpolation=a>>3;

	a=x&0x0010;
	m_Message_SysInvalid=a>>4;

	a=x&0x0020;
	m_Message_CheckChannel1=a>>5;

	a=x&0x0040;
	m_Message_CheckChannel2=a>>6;

	a=x&0x0080;
	m_Message_CheckChannel3=a>>7;

	a=x&0x0100;
	m_Message_CheckChannel4=a>>8;

	a=x&0x0200;
	m_Message_CheckChannel5=a>>9;

	a=x&0x0400;
	m_Message_CheckChannel6=a>>10;

	a=x&0x0800;
	m_Message_CheckChannel7=a>>11;

	a=x&0x1000;
	m_Message_OutputType=a>>12;

	a=x&0x2000;
	m_Message_RangeFlag=a>>13;

	
	int y,j,b;
	y=buffer[32];
	for(j=31;j>=0;j--) 
	y>>j&1;

	b=y&0x0001;
    m_Message_CheckChannel8=b;
	

	b=y&0x0002;
	m_Message_CheckChannel9=b>>1;

	b=y&0x0004;
	m_Message_CheckChannel10=b>>2;

	b=y&0x0008;
	m_Message_CheckChannel11=b>>3;

	b=y&0x0010;
	m_Message_CheckChannel12=b>>4;

	b=y&0x0020;
	m_Message_CheckChannel13=b>>5;

	b=y&0x0040;
	m_Message_CheckChannel14=b>>6;

	b=y&0x0080;
	m_Message_CheckChannel15=b>>7;

	b=y&0x0100;
	m_Message_CheckChannel16=b>>8;

	b=y&0x0200;
	m_Message_CheckChannel17=b>>9;

	b=y&0x0400;
	m_Message_CheckChannel18=b>>10;

	b=y&0x0800;
	m_Message_CheckChannel19=b>>11;

	b=y&0x1000;
	m_Message_CheckChannel20=b>>12;

	b=y&0x2000;
	m_Message_CheckChannel21=b>>13;

	b=y&0x4000;
	m_Message_CheckChannel22=b>>14;

	
	/*TempData_UCHAR = ValidData[68];         //DC1 source select
	TempData_UINT =(UINT)TempData_UCHAR;
	m_Message_HEX = TempData_UINT;*/
	}
    Message_FUNCTION=NULL;

}

BEGIN_MESSAGE_MAP(Dlg_Message, CDialog)
	//{{AFX_MSG_MAP(Dlg_Message)
	ON_BN_CLICKED(IDC_BUTTON_Message_Fetch, OnBUTTONMessageFetch)
	ON_BN_CLICKED(IDC_RADIO_Message_DEC, OnRADIOMessageDEC)
	ON_BN_CLICKED(IDC_RADIO_Message_HEX, OnRADIOMessageHEX)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_Message message handlers

void Dlg_Message::OnBUTTONMessageFetch() 
{
	// TODO: Add your control notification handler code here
	Message_FUNCTION =IDC_BUTTON_Message_Fetch;
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
//	pParent->
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->Connect_Index=0;
	pParent->ErrorCounter=0;
	pParent->Down =IDC_BUTTON_Message_Fetch;

	pParent->Message_block_49.Station_adr=0;
	pParent->Message_block_49.Telegram_Nr=49;
	pParent->Message_block_49.F1_field=0;
	pParent->Message_block_49.F2_field=0x80;
	pParent->Message_block_49.Data=(UCHAR *)"";

	pParent->Fun_Connect(pParent->Message_block_49,0);


//	UpdateData(FALSE);
//	ValidData[4]=ValidData[5]=0;ValidData[6]=ValidData[7]=0;ValidData[8]=ValidData[9]=0;
	SetTimer(IDC_BUTTON_Message_Fetch,666,NULL);
//	pParent->Down =IDC_BUTTON_Message_FETCH;	
	
}



void Dlg_Message::OnRADIOMessageDEC() 
{
m_Message_DEC=0;
UpdateData(TRUE);

char Cnt_TempBuffer[10];
_itoa(buffer[0],Cnt_TempBuffer,10);    
m_Message_Lenth= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[1],Cnt_TempBuffer,10);    
m_Message_LNName= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[2],Cnt_TempBuffer,10);    
m_Message_DataSetName= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[3],Cnt_TempBuffer,10);    
m_Message_LDName= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[4],Cnt_TempBuffer,10);    
m_Message_PhsAArtg= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[5],Cnt_TempBuffer,10);    
m_Message_NeutArtg= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[6],Cnt_TempBuffer,10);    
m_Message_PhsAVrtg= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[7],Cnt_TempBuffer,10);    
m_Message_tdr= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[8],Cnt_TempBuffer,10);    
m_Message_SmpCtr= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[9],Cnt_TempBuffer,10);    
m_Message_Channel1=Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[10],Cnt_TempBuffer,10);    
m_Message_Channel2= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[11],Cnt_TempBuffer,10);    
m_Message_Channel3= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[12],Cnt_TempBuffer,10);    
m_Message_Channel4= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[13],Cnt_TempBuffer,10);    
m_Message_Channel5= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[14],Cnt_TempBuffer,10);    
m_Message_Channel6= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[15],Cnt_TempBuffer,10);    
m_Message_Channel7= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[16],Cnt_TempBuffer,10);    
m_Message_Channel8= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[17],Cnt_TempBuffer,10);    
m_Message_Channel9= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[18],Cnt_TempBuffer,10);    
m_Message_Channel10= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[19],Cnt_TempBuffer,10);    
m_Message_Channel11= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[20],Cnt_TempBuffer,10);    
m_Message_Channel12= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[21],Cnt_TempBuffer,10);    
m_Message_Channel13= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[22],Cnt_TempBuffer,10);    
m_Message_Channel14= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[23],Cnt_TempBuffer,10);    
m_Message_Channel15= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[24],Cnt_TempBuffer,10);    
m_Message_Channel16= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[25],Cnt_TempBuffer,10);    
m_Message_Channel17= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[26],Cnt_TempBuffer,10);    
m_Message_Channel18= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[27],Cnt_TempBuffer,10);    
m_Message_Channel19= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[28],Cnt_TempBuffer,10);    
m_Message_Channel20= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[29],Cnt_TempBuffer,10);    
m_Message_Channel21= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[30],Cnt_TempBuffer,10);    
m_Message_Channel22= Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[31],Cnt_TempBuffer,10);    
m_Message_StatusWord1=Cnt_TempBuffer;

memset(Cnt_TempBuffer,'\0',10);
_itoa(buffer[32],Cnt_TempBuffer,10);    
m_Message_StatusWord2= Cnt_TempBuffer;

UpdateData(FALSE);
//((CButton*)GetDlgItem(IDC_RADIO_Message_HEX))->EnableWindow(FALSE);
}

void Dlg_Message::OnRADIOMessageHEX() 
{
if(m_Message_DEC==0)
{
m_Message_DEC=1;
 UpdateData(TRUE);

int dec=atoi(m_Message_Channel1);
char Cnt_TempBuffer[10];
_itoa(dec,Cnt_TempBuffer,16);  
  
int i,n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel1="0x";
int j;
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel1+="0";
	}
}
m_Message_Channel1+=Cnt_TempBuffer;


dec=atoi(m_Message_LDName);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_LDName="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_LDName+="0";
	}
}
m_Message_LDName+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel10);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel10="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel10+="0";
	}
}
m_Message_Channel10+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel11);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel11="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel11+="0";
	}
}
m_Message_Channel11+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel12);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel12="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel12+="0";
	}
}
m_Message_Channel12+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel13);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel13="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel13+="0";
	}
}
m_Message_Channel13+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel14);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel14="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel14+="0";
	}
}
m_Message_Channel14+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel15);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel15="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel15+="0";
	}
}
m_Message_Channel15+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel16);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel16="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel16+="0";
	}
}
m_Message_Channel16+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel17);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel17="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel17+="0";
	}
}
m_Message_Channel17+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel18);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel18="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel18+="0";
	}
}
m_Message_Channel18+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel19);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16); 


n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel19="0x";
if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel19+="0";
	}
}
m_Message_Channel19+=Cnt_TempBuffer;


dec=atoi(m_Message_Channel2);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel2="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel2+="0";
	}
}
m_Message_Channel2+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel20);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel20="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel20+="0";
	}
}
m_Message_Channel20+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel21);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel21="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel21+="0";
	}
}
m_Message_Channel21+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel22);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel22="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel22+="0";
	}
}
m_Message_Channel22+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel3);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel3="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel3+="0";
	}
}
m_Message_Channel3+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel4);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel4="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel4+="0";
	}
}
m_Message_Channel4+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel5);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel5="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel5+="0";
	}
}
m_Message_Channel5+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel6);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel6="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel6+="0";
	}
}
m_Message_Channel6+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel7);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel7="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel7+="0";
	}
}
m_Message_Channel7+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel8);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel8="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel8+="0";
	}
}
m_Message_Channel8+=Cnt_TempBuffer;

dec=atoi(m_Message_Channel9);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Channel9="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Channel9+="0";
	}
}
m_Message_Channel9+=Cnt_TempBuffer;

dec=atoi(m_Message_DataSetName);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=1;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_DataSetName="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_DataSetName+="0";
	}
}
m_Message_DataSetName+=Cnt_TempBuffer;

dec=atoi(m_Message_Lenth);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_Lenth="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_Lenth+="0";
	}
}
m_Message_Lenth+=Cnt_TempBuffer;

dec=atoi(m_Message_LNName);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=1;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_LNName="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_LNName+="0";
	}
}
m_Message_LNName+=Cnt_TempBuffer;

dec=atoi(m_Message_NeutArtg);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_NeutArtg="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_NeutArtg+="0";
	}
}
m_Message_NeutArtg+=Cnt_TempBuffer;

dec=atoi(m_Message_PhsAArtg);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_PhsAArtg="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_PhsAArtg+="0";
	}
}
m_Message_PhsAArtg+=Cnt_TempBuffer;

dec=atoi(m_Message_PhsAVrtg);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_PhsAVrtg="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_PhsAVrtg+="0";
	}
}
m_Message_PhsAVrtg+=Cnt_TempBuffer;

dec=atoi(m_Message_SmpCtr);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_SmpCtr="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_SmpCtr+="0";
	}
}
m_Message_SmpCtr+=Cnt_TempBuffer;

dec=atoi(m_Message_StatusWord1);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_StatusWord1="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_StatusWord1+="0";
	}
}
m_Message_StatusWord1+=Cnt_TempBuffer;

dec=atoi(m_Message_StatusWord2);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_StatusWord2="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_StatusWord2+="0";
	}
}
m_Message_StatusWord2+=Cnt_TempBuffer;

dec=atoi(m_Message_tdr);
memset(Cnt_TempBuffer,'\0',10);
_itoa(dec,Cnt_TempBuffer,16);    
n=0;
for(i=3;Cnt_TempBuffer[i]==0&&i>=0;i--)
{
	n++;
}
m_Message_tdr="0x";

if (n>0)
{
	for(j=1;j<=n;j++)
	{
		m_Message_tdr+="0";
	}
}
m_Message_tdr+=Cnt_TempBuffer;

UpdateData(FALSE);
}
	
}

void Dlg_Message::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==IDC_BUTTON_Message_Fetch)
	{
		KillTimer(IDC_BUTTON_Message_Fetch);
		UpdateData(TRUE);
		UpdateData(FALSE);
		//MessageBox("test");
	}
	CDialog::OnTimer(nIDEvent);
}

void Dlg_Message::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	UpdateData(FALSE);
	// TODO: Add your message handler code here	
}





