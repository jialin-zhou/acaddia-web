// Dlg_ComSet.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_ComSet.h"
#include "stdio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_ComSet dialog


Dlg_ComSet::Dlg_ComSet(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_ComSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_ComSet)
	m_nComSetBaud = 0;
	m_nComSetCheck = 0;
	m_nComSetData = 0;
	m_nComSetStop = 0;
	//settingpara="19200,n,8,1";
	m_nComSetCom = 0;
	//}}AFX_DATA_INIT
}


void Dlg_ComSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_ComSet)
	DDX_CBIndex(pDX, IDC_COMBO_BAUD, m_nComSetBaud);
	DDX_CBIndex(pDX, IDC_COMBO_CHECK, m_nComSetCheck);
	DDX_CBIndex(pDX, IDC_COMBO_DATA, m_nComSetData);
	DDX_CBIndex(pDX, IDC_COMBO_STOP, m_nComSetStop);
	DDX_CBIndex(pDX, IDC_COMBO_COM, m_nComSetCom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_ComSet, CDialog)
	//{{AFX_MSG_MAP(Dlg_ComSet)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(GetCom, OnGetCom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_ComSet message handlers

void Dlg_ComSet::OnOK() 
{
	CString  com_port;
	CString para;
	// TODO: Add your message handler code here
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
    para =pParent->m_ctrlCOM.GetSettings();
	// TODO: Add extra validation here
	m_nComSetBaud =((CComboBox *)GetDlgItem(IDC_COMBO_BAUD)) ->GetCurSel();   //取得各个复选框对应的参数，第一个对应0，第二个对应1。。。 
	m_nComSetCheck =((CComboBox *)GetDlgItem(IDC_COMBO_CHECK)) ->GetCurSel();
	m_nComSetData =((CComboBox *)GetDlgItem(IDC_COMBO_DATA)) ->GetCurSel();
	m_nComSetStop =((CComboBox *)GetDlgItem(IDC_COMBO_STOP)) ->GetCurSel();
    m_nComSetCom =((CComboBox *)GetDlgItem(IDC_COMBO_COM)) ->GetCurSel();
    

   


	switch(m_nComSetCom)
	{
    case 0:
			com_port="COM1:";
			break;
    case 1:
			com_port="COM2:";
			break;
	case 2:
			com_port="COM3:";
			break;
	case 3:
			com_port="COM4:";
			break;

//shy20240407
    case 4:
			com_port="COM5:";
			break;
    case 5:
			com_port="COM6:";
			break;
	case 6:
			com_port="COM7:";
			break;
	case 7:
			com_port="COM8:";
			break;
    case 8:
			com_port="COM9:";
			break;
    case 9:
			com_port="COM10:";
			break;
	case 10:
			com_port="COM11:";
			break;
	case 11:
			com_port="COM12:";
			break;

    case 12:
			com_port="COM13:";
			break;
    case 13:
			com_port="COM14:";
			break;
	case 14:
			com_port="COM15:";
			break;
	case 15:
			com_port="COM16:";
			break;
	case 16:
			com_port="COM17:";
			break;
    case 17:
			com_port="COM18:";
			break;
	case 18:
			com_port="COM19:";
			break;
	case 19:
			com_port="COM20:";
			break;

	}
	switch(m_nComSetBaud)
	{
	case 0:
		settingpara ="4800,";
		break;
	case 1: 
		settingpara ="9600,";
		break;
	case 2:
		settingpara ="19200,";
		break;
	case 3:
		settingpara ="38400,";
		break;
	default:
		settingpara = "9600,";
		break;
	}
/////////////////校验位///////////////////////
		switch(m_nComSetCheck)
	{
	case 0:
		settingpara+="n,";
		break;
	case 1:
		settingpara +="o,";
		break;
	case 2:
		settingpara+="e,";
		break;
	default:
		settingpara+="n,";
		break;
	}
//////////////////////数据位///////////////////
		switch(m_nComSetData)
	{
	case 0:
		settingpara +="8,";
		break;
	case 1:
		settingpara +="7,";
		break;
	case 2:
		settingpara +="6,";
		break;
	default:
		settingpara +="8,";
		break;
	}

/////////////停止位///////////////////////
		switch(m_nComSetStop)
	{
	case 0:
		settingpara +="1";
		break;
	case 1:
		settingpara +="2";
		break;
	default:
		settingpara += "1";
		break;
	}
	if(pParent->m_ctrlCOM.GetPortOpen())                     //is the port opened?
	   pParent->m_ctrlCOM.SetPortOpen(FALSE);
	   pParent->m_ctrlCOM.SetCommPort(m_nComSetCom+1);                       //choose port 1;
		if(!pParent->m_ctrlCOM.GetPortOpen())                    //if port 1 not opened?
			pParent->m_ctrlCOM.SetPortOpen(TRUE);                //open port 1
		else
			AfxMessageBox("cannot open serial port");   //others , show a messagebox "can't open!" 
		pParent->m_ctrlCOM.SetSettings(settingpara);           //set the parameters of  port 1;
		pParent->m_ctrlCOM.SetInputMode(1);                      //data input mode. 1: binary / 0: text
		pParent->m_ctrlCOM.SetRThreshold(1);                     //when receive 1 bit, the OnComm() function is active.
		pParent->m_ctrlCOM.SetInputLen(0);                       //set the length of the current receive block is 0;
		pParent->m_ctrlCOM.GetInput();   

	MessageBox(com_port+settingpara,"ComSetting");
//	MessageBox(str+settingpara,"ComSetting");

	CDialog::OnOK();
}

void Dlg_ComSet::OnCancel() 
{
	// TODO: Add extra cleanup here
	//settingpara="9600,n,8,1";
	//m_nComSetCom = 2;
	//MessageBox("COM2:"+settingpara,"ComSetting");
	CDialog::OnCancel();

}

void Dlg_ComSet::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	CString para;
	// TODO: Add your message handler code here
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
    para =pParent->m_ctrlCOM.GetSettings();
//////////////////////////////////////////////////////////////////////////


	m_nComSetCom = pParent_ZJM->m_nComPortMb;

	if(para.GetAt(0)=='4')
		m_nComSetBaud = 0;
	if(para.GetAt(0)=='9')
		m_nComSetBaud = 1;
	if(para.GetAt(0)=='1')
		m_nComSetBaud = 2;
	if(para.GetAt(0)=='3')
		m_nComSetBaud = 3;
//////////////////////////////////////////////////////////////////////// = 0;
	if(para.GetAt(0)=='4'||para.GetAt(0)=='9')
	{
		if(para.GetAt(5)=='n')
			m_nComSetCheck = 0;
		if(para.GetAt(5)=='o')
			m_nComSetCheck = 1;
		if(para.GetAt(5)=='e')
			m_nComSetCheck = 2;
	}
	if(para.GetAt(0)=='1'||para.GetAt(0)=='3')
	{
		if(para.GetAt(6)=='n')
			m_nComSetCheck = 0;
		if(para.GetAt(6)=='o')
			m_nComSetCheck = 1;
		if(para.GetAt(6)=='e')
			m_nComSetCheck = 2;
	}

////////////////////////////////////////////////////////////////////////
	if(para.GetAt(0)=='4'||para.GetAt(0)=='9')
	{
		if(para.GetAt(7)=='8')
			m_nComSetData = 0;
		if(para.GetAt(7)=='7')
			m_nComSetData = 1;
		if(para.GetAt(7)=='6')
			m_nComSetData = 2;
	}
	if(para.GetAt(0)=='1'||para.GetAt(0)=='3')
	{
		if(para.GetAt(8)=='8')
			m_nComSetData = 0;
		if(para.GetAt(8)=='7')
			m_nComSetData = 1;
		if(para.GetAt(8)=='6')
			m_nComSetData = 2;
	}

////////////////////////////////////////////////////////////////////////
	if(para.GetAt(0)=='4'||para.GetAt(0)=='9')
	{
		if(para.GetAt(9)=='1')
			m_nComSetStop = 0;
		if(para.GetAt(9)=='2')
			m_nComSetStop = 1;
	}
	if(para.GetAt(0)=='1'||para.GetAt(0)=='3')
	{
		if(para.GetAt(10)=='1')
			m_nComSetStop = 0;
		if(para.GetAt(10)=='2')
			m_nComSetStop = 1;
	}
//////////////////////////////////////////////////////////////////////////



	UpdateData(FALSE);
}


void Dlg_ComSet::OnGetCom() 
{
	// TODO: Add your control notification handler code here
	//程序启动时获取全部可用串口     
	HANDLE  hCom;
    int i,num,k;
    CString str;
    BOOL flag;
   
    ((CComboBox *)GetDlgItem(IDC_COMBO_COM2))->ResetContent();
    flag = FALSE;
    num = 0;
    
/*	if(i >= 0 && i< 10)
	{
		sprintf(str, "COM%d", i);
	}
	else if(i >= 10)
	{
		sprintf(str, "\\\\.\\COM%d", i);
	}

*/	
//shy	
	
	for (i = 1;i <= 100;i++)
	{//此程序支持16个串口
        str.Format("\\\\.\\COM%d",i);
        hCom = CreateFile(str, GENERIC_READ | GENERIC_WRITE, 0, NULL, 
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
        if(hCom == INVALID_HANDLE_VALUE)
        {//能打开该串口，则添加该串口
            /*CloseHandle(hCom);
            str = str.Mid(4);
            ((CComboBox *)GetDlgItem(IDC_COMBO_COM2))->AddString(str);*/
            if (flag == FALSE)
            {
                flag = TRUE;
                num = i;
            }
        }
		else{
			CloseHandle(hCom);
            str = str.Mid(4);
            ((CComboBox *)GetDlgItem(IDC_COMBO_COM2))->AddString(str);

		}
    }
    i = ((CComboBox *)GetDlgItem(IDC_COMBO_COM2))->GetCount();
    if (i == 0 || i >100)
    {//若找不到可用串口则禁用“打开串口”功能
        ((CComboBox *)GetDlgItem(IDC_COMBO_COM2))->EnableWindow(FALSE);
    }
    else
    {
        k = ((CComboBox *)GetDlgItem((IDC_COMBO_COM2)))->GetCount();
        ((CComboBox *)GetDlgItem(IDC_COMBO_COM2))->SetCurSel(k - 1);
        //mCom.BindCommPort(num);
    }
}
