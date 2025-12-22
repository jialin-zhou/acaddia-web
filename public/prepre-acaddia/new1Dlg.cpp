// new1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "new1Dlg.h"
#include "Resource.h"
//#include "Dlg_ZJM.h"
//#include "mscomm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
//	MessageBox("")
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNew1Dlg dialog

CNew1Dlg::CNew1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNew1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNew1Dlg)
	m_CStringStatus = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	ErrorCounter=0;                                 //variable of error times
//	ReceiveOK=FALSE;
//	RX_Order[0]='\0';
	Connect_Index=0;
	Zero_NR=0;
	RXDAT[0]='\0';
	index=0;
	Current_Style=1;
	Msg_Len=0;
	Down = IDC_OFFLINE;
	RX_Msg_End =TRUE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNew1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNew1Dlg)
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlCOM);
	DDX_Text(pDX, IDC_STATIC_Status, m_CStringStatus);
	//}}AFX_DATA_MAP
//MessageBox("CNew1Dlg:  dodataexchange");
}

void  CALLBACK   MessageBoxTimer(HWND   hwnd,   UINT   uiMsg,   UINT   idEvent,   DWORD   dwTime)   
{   
	PostQuitMessage(0);   
}  
 
UINT  TimedMessageBox(HWND   hwndParent, LPCTSTR   ptszMessage,LPCTSTR   ptszTitle,UINT   flags, DWORD   dwTimeout)   
{   
	UINT   idTimer;   
	UINT   uiResult;   
	MSG   msg;   
    
	/*   
	*     Set   a   timer   to   dismiss   the   message   box.   
	*/     
	idTimer   =   SetTimer(NULL,   0,   dwTimeout,   (TIMERPROC)MessageBoxTimer);   
    
	uiResult   =   MessageBox(hwndParent,   ptszMessage,   ptszTitle,   flags);   
    
	/*   
	*     Finished   with   the   timer.   
	*/     
	KillTimer(NULL,   idTimer);   
    
	/*   
	*     See   if   there   is   a   WM_QUIT   message   in   the   queue.   If   so,   
	*     then   you   timed   out.   Eat   the   message   so   you   don't   quit   the   
	*     entire   application.   
	*/     
	if   (PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE))   {   
		
	/*   
	*     If   you   timed   out,   then   return   zero.   
	*/     
		uiResult   =   0;   
	}   
    
	return   uiResult;   
}   


BEGIN_MESSAGE_MAP(CNew1Dlg, CDialog)
	//{{AFX_MSG_MAP(CNew1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OFFLINE, OnOffline)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNew1Dlg message handlers

BOOL CNew1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	///////////////////////////////////////////////////////////////////////////////////
	// 
	//              communication  initialization program    --- start
	//
	///////////////////////////////////////////////////////////////////////////////////
/*
	if(m_ctrlCOM.GetPortOpen())                     //is the port opened?
		m_ctrlCOM.SetPortOpen(FALSE);


	 
	m_ctrlCOM.SetCommPort(1);                       //choose port 1;
	if(!m_ctrlCOM.GetPortOpen())                    //if port 1 not opened?
		m_ctrlCOM.SetPortOpen(TRUE);                //open port 1
	else
	AfxMessageBox("cannot open serial port");   //others , show a messagebox "can't open!" 
*/
	//20250801
	CString strPort;
    int nPort = 1;
    BOOL bFound = FALSE;
    
    // 首先关闭已打开的端口
    if(m_ctrlCOM.GetPortOpen())
        m_ctrlCOM.SetPortOpen(FALSE);
    
    // 尝试从COM1到COM16
    for(nPort = 1; nPort <= 16; nPort++)
    {
        strPort.Format(_T("COM%d"), nPort);
        m_ctrlCOM.SetCommPort(nPort);
        
        try
        {
            if(!m_ctrlCOM.GetPortOpen())
            {
                m_ctrlCOM.SetPortOpen(TRUE);
                // 验证端口是否真正打开
                if(m_ctrlCOM.GetPortOpen())
                {
                    bFound = TRUE;
                    break;
                }
            }
        }
        catch(...)
        {
            // 捕获异常，继续尝试下一个端口
            continue;
        }
    }
    
    if(!bFound)
    {
        AfxMessageBox(_T("cannot open serial port!"));
        return FALSE;
    }

	// 在对话框的 OnInitDialog() 中设置按钮样式
    //CButton* pBtn = (CButton*)GetDlgItem(IDC_OFFLINE);
    //pBtn->ModifyStyle(0, BS_CHECKBOX);  // 改为复选框样式
    bool isChecked = ((CButton*)GetDlgItem(IDC_OFFLINE))->GetCheck();
    
// 判断是否被选中
   // Down = IDC_OFFLINE;
	if(isChecked)
	{
		
		//shy202507
		if(m_ctrlCOM.GetPortOpen())
            m_ctrlCOM.SetPortOpen(FALSE);
		
	}
   
//shy


	m_ctrlCOM.SetSettings("9600,n,8,1");           //set the parameters of  port 1;
	m_ctrlCOM.SetInputMode(1);                      //data input mode. 1: binary / 0: text
	m_ctrlCOM.SetRThreshold(1);                     //when receive 1 bit, the OnComm() function is active.
	m_ctrlCOM.SetInputLen(0);                       //set the length of the current receive block is 0;
	m_ctrlCOM.GetInput();                           //read the receive block, clear the receive block!

//MessageBox("port set successful");
    ///////////////////////////////////////////////////////////////////////////////////
	// 
	//              communication  initialization program    --- end
	//
	///////////////////////////////////////////////////////////////////////////////////

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNew1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNew1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
//MessageBox("ONPAINT :  ISICONIC");
	}
	else
	{
//MessageBox("ONPAINT : ");
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNew1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNew1Dlg::OnOffline() 
{
	// TODO: Add your control notification handler code here
	Down = IDC_OFFLINE;

	//shy202507
	if(m_ctrlCOM.GetPortOpen())
        m_ctrlCOM.SetPortOpen(FALSE);
	//
	
	if(Down==IDC_OFFLINE)
	{
		m_CStringStatus="Loading......";
		UpdateData(FALSE);
//ShowWindow(SW_HIDE);
		for(int kk=0;kk<255;kk++)
		{
			ZJM_dlg.AD1_dlg.ValidData[kk]=0;
			ZJM_dlg.TQCS_dlg.ValidData[kk]=0;
		}
		DIM_public=16384;
		ZJM_dlg.DoModal();
		DestroyWindow();
	}
	
}

void CNew1Dlg::OnConnect()         //Function:  initialize the TeleBlock, and sent the first order(TQCS 35)
{
	// TODO: Add your control notification handler code here
//	m_nTimerID=SetTimer(2,2000,NULL);
	UpdateData(TRUE);
	Down =IDC_CONNECT;
	Msg_Len=0;
	UINT T1,T2=0;T1=0;                                        //timer
//	UCHAR TXDat_Temp[280];
//	UCHAR RXTele_Nr=0;
//MessageBox("1");
	UCHAR *pTXDATA1;
	TQCS_block_35.Telegram_Nr=35;                              //同期参数回读
	TQCS_block_35.Station_adr=0;
	TQCS_block_35.F1_field=0;
	TQCS_block_35.F2_field=0x80;
	TQCS_block_35.Data=(UCHAR *)"";
//	TQCS_block_35.Data[0]='\0';

	ACAD_block_33.Telegram_Nr=33;                              //交流AD参数回读
	ACAD_block_33.Station_adr=0;
	ACAD_block_33.F1_field=0;
	ACAD_block_33.F2_field=0x80;
	ACAD_block_33.Data=(UCHAR*)"";
//	ACAD_block_33.Data[0]='\0';

	ADData_block_37.Telegram_Nr=37;                            //AD计算值回读
	ADData_block_37.Station_adr=0;
	ADData_block_37.F1_field=0;
	ADData_block_37.F2_field=0x80;
	ADData_block_37.Data=(UCHAR*)"";
    
	AC_angle_block_47.Telegram_Nr=47;                            //交流AD角度回读
	AC_angle_block_47.Station_adr=0;
	AC_angle_block_47.F1_field=0;
	AC_angle_block_47.F2_field=0x80;
	AC_angle_block_47.Data=(UCHAR*)"";

	Message_block_49.Telegram_Nr=49;                            //message回读
	Message_block_49.Station_adr=0;
	Message_block_49.F1_field=0;
	Message_block_49.F2_field=0x80;
	Message_block_49.Data=(UCHAR*)"";
//	ADData_block_37.Data[0]='\0';
    /*yyp
	Msg_h_block_12.Telegram_Nr=12;                             //pc请求告警信息（有head）
	Msg_h_block_12.Station_adr=0;
	Msg_h_block_12.F1_field=0;
	Msg_h_block_12.F2_field=0x80;
	*/
//	*(Msg_h_block_12.Data)=1;
//	TXDat_Temp[0]=0;
//	TXDat_Temp[1]='\0';
//	pTXData =TXDat_Temp;
//	Msg_h_block_12.Data=pTXData;
//	Msg_h_block_12.Data[0] = 0;
//	Msg_h_block_12.Data[1]='\0';
	Connect_Telegram.ValidDataToPack[0]=0;
	Connect_Telegram.ValidDataToPack[1]=0;
	Connect_Telegram.ValidDataToPack[2]=0;
	Connect_Telegram.ValidDataToPack[3]=0;
	Connect_Telegram.ValidDataToPack[4]=0;
	Connect_Telegram.ValidDataToPack[5]=0;
	Connect_Telegram.ValidDataToPack[6]='\0';

/*
	Msg_block_13.Telegram_Nr=13;                               //PC 请求告警信息（无head）
	Msg_block_13.Station_adr=0;
	Msg_block_13.F1_field=0;
	Msg_block_13.F2_field=0x80;
	Msg_block_13.Data=(UCHAR*)"";
//	Msg_block_13.Data[0]='\0';
*/


	if(ErrorCounter<5 && Connect_Index==0)
	{
    // MessageBox("发送同期参数命令");
		Fun_Connect(TQCS_block_35,0); //发送同期参数命令              //yyp
	}
/*yyp
    if(ErrorCounter<5 && Connect_Index==1)
	{
    //MessageBox("发送AD参数命令");
		Fun_Connect(ACAD_block_33,0); //发送AD参数命令
	//	Connect_Index++;			  //yyp
	}
	if(ErrorCounter<5 && Connect_Index==2)
	{
    //MessageBox("发送AD计算值命令");
		Fun_Connect(ADData_block_37,0); //发送AD计算值命令
	//	Connect_Index++;			  //yyp
	}
	if(ErrorCounter<5 && Connect_Index==3)
	{
    // MessageBox("发送AD Base Angle");
		Fun_Connect(AC_angle_block_47,0); //发送AD计算值命令
	//	Connect_Index++;			  //yyp
	}
*/


//	DestroyWindow();
//	CPaintDC.
	m_CStringStatus="Connecting...... Please waitting!";
	UpdateData(FALSE);
//	m_CButton_OFFLINE.SetButtonStyle(WS_DISABLED,TRUE);
//	this->
//	ShowWindow(SW_HIDE);
//	
//	DFUPicture_dlg.DoModal();
//	::ShowWindow();
//	MessageBox("INITIAL",NULL,NULL);
	
//CBitmap a;
//a.CreateBitmap(100,100,10,10,NULL);
//a.
//MessageBox("2");

//	while(Connect_Order ==1);
//UpdateData(TRUE);
//CString ss;
//for(int i=0;i<40;i++)

//{	ZJM_dlg.TQCS_dlg.ValidData[i]=i;
//    TQCS_Data[i]=i;

//ss.Format("%x",ZJM_dlg.TQCS_dlg.ValidData[i]);
//MessageBox(ss);
//}
//ZJM_dlg.DoModal();
//LOOP1:	T1=50000;
//	while(T1--);
//    goto LOOP1;
//LOOP2: MessageBox("ok");

//yyp
/*
	for(;ErrorCounter<5;ErrorCounter++)
	{
		pTXDATA1=Connect_Telegram.TelePack(0,TQCS_block_35.Telegram_Nr,TQCS_block_35,0);
		for(int tt=0;tt<(Connect_Telegram.Block_len+6);tt++)
			TXDATA1[tt]=*pTXDATA1++;
		TXDATA1[tt]='\0';
		SentData(TXDATA1);
		index=0;
	//	while(ReceiveOK==FALSE)
		//if(ReceiveOK==TRUE)
//		{
          MessageBox("VALID DATA");
//			index=0;
			if(Connect_Telegram.ACK1==FALSE && Connect_Telegram.ACK2==FALSE)                    //有参数返回;
			{
				
				RXTele_Nr= (UCHAR)Connect_Telegram.Telegarm_Array[3];
				if(RXTele_Nr==34)                             //同期参数回读命令 相应
				{
					for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.TQCS_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 同期参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
				}
				else if(RXTele_Nr==32)                        //交流AD参数回读命令  相应
				{
					for(int len=0;len<((UCHAR)Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.AD1_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
				}
				else if(RXTele_Nr==36)                        //AD计算值回读命令  相应
				{
				    for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.ADCacul_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
				}
				else if(RXTele_Nr==2)                         //PC请求告警信息(有Head)命令  相应
				{
					for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.MsgList_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
				}
				else if(RXTele_Nr==3)                         //PC请求告警信息(无head)命令   相应
				{
					for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.MsgList_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);  
				}
				else                                          //返回命令错误时
					continue;
				
			}
		}
	//	else
	//		continue;		
//	}

*/
//for(;ErrorCounter<5;ErrorCounter++)
//{
//	for(;ErrorCounter<5;ErrorCounter++)
//	{
//		pTXDATA1=Connect_Telegram.TelePack(0,TQCS_block_35.Telegram_Nr,TQCS_block_35,0);
//		for(int tt=0;tt<(Connect_Telegram.Block_len+6);tt++)
//			TXDATA1[tt]=*pTXDATA1++;
//		    TXDATA1[tt]='\0';
//		SentData(TXDATA1);
//		index=0;
//		while(ReceiveOK==TRUE)
//		if(ReceiveOK==TRUE)
//		{
//TimedMessageBox(NULL,"Loading Data Please waitting!","", MB_YESNO,1000);  
for(int ii=0; ii<2500; ii++)
{for(int jj=0; jj<65535; jj++);};
MessageBox("Loading Data Please Waitting!");
//			index=0;
			if(Connect_Telegram.ACK1==FALSE && Connect_Telegram.ACK2==FALSE)                    //有参数返回;
			{
			for(;ErrorCounter<5;ErrorCounter++)
				{ 
				RXTele_Nr= (UCHAR)Connect_Telegram.Telegarm_Array[3];
				if(RXTele_Nr==34)                             //同期参数回读命令 相应
				{
					for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.TQCS_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 同期参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
				//	MessageBox("同期参数回读命令");
					
				//	m_CStringStatus="Loading...syn parameter";
				//	UpdateData(FALSE);
					ErrorCounter=0;
				//	ReceiveOK=FALSE;
			    //	Connect_Index=0;
					continue;

				}
				else if(RXTele_Nr==32)                        //交流AD参数回读命令  相应
				{
					for(int len=0;len<((UCHAR)Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.AD1_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
					//MessageBox("交流AD参数回读命令");
			       ErrorCounter=0; 
				//	m_CStringStatus="Loading...AD parameter";
					UpdateData(FALSE);
					
				//	ReceiveOK=FALSE;
                   // Connect_Index++;
					continue;
				}
				else if(RXTele_Nr==48)                        //AD angle命令  相应
				{
				    for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.BaseAngle_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
					//MessageBox("Loading...Base angle");
					ErrorCounter=0;
                    m_CStringStatus="All data has been loaded!";
					UpdateData(FALSE);
                    MessageBox("All data has been loaded!");
				//	ReceiveOK=TRUE;
					break;
					//ErrorCounter=0;
                 //   Connect_Index++;
				}

				else if(RXTele_Nr==50)                        //Message命令  相应
				{
				    for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.Message_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
					//MessageBox("Loading...Base angle");
					ErrorCounter=0;
                    m_CStringStatus="All data has been loaded!";
					UpdateData(FALSE);
                    MessageBox("All data has been loaded!");
				//	ReceiveOK=TRUE;
					break;
					//ErrorCounter=0;
                 //   Connect_Index++;
				}
				
				else if(RXTele_Nr==36)                        //AD计算值回读命令  相应
				{
				    for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.ADCacul_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
					//MessageBox("Loading...AD Value");
                   // m_CStringStatus="Loading...AD parameter";
					UpdateData(FALSE);
				//	ReceiveOK=FALSE;
					ErrorCounter=0;
                  // Connect_Index++;
					continue;
				}
				else 
				{
				//	ErrorCounter++;//返回命令错误时
					continue;
				}
			}		
			}
		//}

	if(ErrorCounter==5)
	{
		MessageBox("communication error!");
		DestroyWindow();
	}
    else
	{
	DIM_public=16384;

    Current_Style=(UINT)(ZJM_dlg.AD1_dlg.ValidData[55]);
/*	DC_V_I_select[0]=(UINT)(ZJM_dlg.AD1_dlg.ValidData[57]);
	DC_V_I_select[1]=(UINT)(ZJM_dlg.AD1_dlg.ValidData[58]);
	DC_V_I_select[2]=(UINT)(ZJM_dlg.AD1_dlg.ValidData[59]);
	DC_V_I_select[3]=(UINT)(ZJM_dlg.AD1_dlg.ValidData[60]);*/
	//20240618
	DC_V_I_select[0]= 1;
	DC_V_I_select[1]= 1;
	DC_V_I_select[2]= 1;
	DC_V_I_select[3]= 1;
	DC_V_I_select[4]= 1;
	DC_V_I_select[5]= 1;
	DC_V_I_select[6]= 1;
	DC_V_I_select[7]= 1;
	DC_V_I_select[8]= 1;
	DC_V_I_select[9]= 1;
	DC_V_I_select[10]= 1;
	DC_V_I_select[11]= 1;
	//
    ZJM_dlg.DoModal();
	DestroyWindow();
	}
		

}


BEGIN_EVENTSINK_MAP(CNew1Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CNew1Dlg)
	ON_EVENT(CNew1Dlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CNew1Dlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
//MessageBox("receive start");
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
 
    BYTE rxdata[2048];                                       //设置BYTE数组 An 8-bit integerthat is not signed.
    CString strtemp;
//MessageBox("1");
    if(m_ctrlCOM.GetCommEvent()==2)                          //事件值为2表示接收缓冲区内有字符
    {                                                        ////////以下你可以根据自己的通信协议加入处理代码
        variant_inp=m_ctrlCOM.GetInput();                    //读缓冲区
        safearray_inp=variant_inp;                           //VARIANT型变量转换为ColeSafeArray型变量
        len=safearray_inp.GetOneDimSize();                   //得到有效数据长度
//MessageBox("2");
		for(k=0;k<len;k++)
			safearray_inp.GetElement(&k,rxdata+k);           //转换为BYTE型数组
        for(k=0;k<len;k++)									 //将数组转换为Cstring型变量
        {		
//MessageBox("3");
			BYTE bt= *(char*)(rxdata+k);					    	 //字符型
//MessageBox("4");
			RXDAT[index ++]=(UCHAR)bt;                             //将接收到的数据存储   ,(UCHAR )RXDAT[]
//MessageBox("5");
//			strtemp.Format("strtemp: %x",bt);
//MessageBox(strtemp);
        }
	}
//MessageBox("receive end");
//	UpdateData(FALSE);
	SetTimer(11,100,NULL);                                         //等待接收数据完毕
//MessageBox("receive data successful");
}

void CNew1Dlg::SentData( UCHAR TXData[])
{
	//	CString TXstring="";
	//MessageBox("senddata before true");
	UpdateData(TRUE);										//读取编辑框内容
	//MessageBox("sentdata ture");
	CByteArray array;
	
	array.RemoveAll();
	
	if(TXData[1]!='\0')
		
	{
		array.SetSize((TXData[2]+6));
		
		for(int i=0;i<(TXData[2]+6);i++)
			
			array.SetAt(i, (BYTE)TXData[i]);
		
		m_ctrlCOM.SetOutput(COleVariant(array)); // 发送数据
	}
	else if(TXData[1]=='\0')                             //master -> slave
	{
		array.SetSize(1);	
		
		array.SetAt(0, (BYTE)TXData[0]);
		
		m_ctrlCOM.SetOutput(COleVariant(array)); // 发送数据
		
	}
	//MessageBox("sent data successful");
	//	OnOnCommMscomm1();
	if(Connect_Index==0)
	{
		SetTimer(12,3333,NULL);
	}
	
}

void CNew1Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	
	UCHAR TXDATA1[280];
//	UpdateData(TRUE);
	RXDAT[index]='\0';
	if(nIDEvent==11)
	{
		KillTimer(11);
		if(Connect_Index==0)
		KillTimer(12);
//MessageBox("ontimer start");
		if(Connect_Telegram.TeleUnpack(RXDAT))
		{
		//	MessageBox("unpack ok");
//	 	    ReceiveOK =TRUE;
		//	RX_Order[(Connect_Index++)%5]=Connect_Telegram.Telegarm_Array[3];
			Connect_Index++;
			index=0;
		}
	//MessageBox("unpack telegram successful");

	//////////////////////////////////////////////////////////////////////////
	//               save  the  valid  data  into  the array
	//////////////////////////////////////////////////////////////////////////

		if(Connect_Telegram.ACK1==FALSE && Connect_Telegram.ACK2==FALSE)                    //有参数返回;
		{
//MessageBox("Valid data");
			RXTele_Nr= (UCHAR)Connect_Telegram.Telegarm_Array[3];
			if(RXTele_Nr==(UCHAR)0x22)                             //同期参数回读命令 相应
			{
	//MessageBox("TQCS ");
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.TQCS_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 同期参数回读数组ValidData[]
				}
				TXDATA1[0]=0xa2; TXDATA1[1]='\0';
//MessageBox("34:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}
			else if(RXTele_Nr==(UCHAR)0x20)                        //交流AD参数回读命令  相应
			{
				for(int len=0;len<((UCHAR)Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.AD1_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("32:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}
			else if(RXTele_Nr==(UCHAR)0x24)                        //AD计算值回读命令  相应
			{
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.ADCacul_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("36:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}
			else if(RXTele_Nr==(UCHAR)0x2)                         //PC请求告警信息(有Head)命令  相应
			{
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.MsgList_h_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
				}
				if(Connect_Telegram.Telegarm_Array[13]==0)          //// //判断Head时是否读完信息//////
					RX_Msg_End=TRUE;
				else
					RX_Msg_End=FALSE;
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("2:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}
			
			else if(RXTele_Nr==41)                         //AD采样通道自校准回读   相应
			{
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.ADAdjust_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("41:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}


			else if(RXTele_Nr==46)                         //同期合闸 Fetch   相应
			{
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.TQML_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("46:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}


			else if(RXTele_Nr==28)                         //时间测试 Fetch   相应
			{
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.TimeSet_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("28:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}	
			else if(RXTele_Nr==(UCHAR)0x3)                         //PC请求告警信息(无head)命令   相应
			{
				UINT len=Msg_Len;
				for(;len<(Connect_Telegram.Block_len+Msg_Len);len++)
				{
					ZJM_dlg.MsgList_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
				}
				Msg_Len =len;
				if(Connect_Telegram.Telegarm_Array[4]==0)    //判断是否读完信息
				{	
					RX_Msg_End=TRUE; //UpdateData(FALSE);
//MessageBox("receive end!!!");
				}
				else
				{
					RX_Msg_End=FALSE; 
					if(Down==IDC_CONNECT)
						Connect_Index=4;
					else if(Down==IDC_BUTTON_ZJM_FETCH)
						Connect_Index=2;
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("3:  A2");
				SentData(TXDATA1);  
			}
///////////////////////////////////////////////////////////////////////////////////////////////			
			else if(RXTele_Nr==48)                         //Base_angle回应
			{
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.BaseAngle_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("46:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}
			else if(RXTele_Nr==50)                         //Message回应
			{
				for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
				{
					ZJM_dlg.Message_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     
				}
				TXDATA1[0]=0xa2;TXDATA1[1]='\0';
//MessageBox("46:  A2");
				SentData(TXDATA1);                        //master -> slave:     A2
			}

			
///////////////////////////////////////////////////////////////////////////////////////////////			
			else                                          //返回命令错误时
			{
				ErrorCounter++;
				Connect_Index=0;
			}
					
		}
		else if(Connect_Telegram.ACK1==TRUE ||Connect_Telegram.ACK2==TRUE)
		{
			if(Down ==IDC_CONNECT)
			{
				ErrorCounter++;
				Connect_Index=0;
			}
			if (Down==IDC_BUTTON_AD1_APPLY && Connect_Telegram.ACK1==TRUE) 
			{
//MessageBox("IDC_BUTTON_AD1_APPLY : SET SUCCESSFUL");
			}
			if (Down==IDC_BUTTON_TQCS_Apply && Connect_Telegram.ACK1==TRUE) 
			{
//MessageBox("IDC_BUTTON_TQCS_Apply : SET SUCCESSFUL");
			}
			if (Down==IDC_BUTTON_ADAdjust_Apply && Connect_Telegram.ACK1==TRUE) 
			{
//MessageBox("IDC_BUTTON_ADAdjust_Apply : SET SUCCESSFUL");
			}
			if (Down==IDC_BUTTON_ADAdjust_NewParApply && Connect_Telegram.ACK1==TRUE) 
			{
//MessageBox("IDC_BUTTON_ADAdjust_NewParApply : SET SUCCESSFUL");
			}
		}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
		/*
if(Down==IDC_CONNECT)
		{
           // MessageBox("Loading Data Please waitting!");
//			index=0;
			if(Connect_Telegram.ACK1==FALSE && Connect_Telegram.ACK2==FALSE)                    //有参数返回;
			{
			for(;ErrorCounter<5;ErrorCounter++)
				{ 
				RXTele_Nr= (UCHAR)Connect_Telegram.Telegarm_Array[3];
				if(RXTele_Nr==34)                             //同期参数回读命令 相应
				{
					for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.TQCS_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 同期参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
				//	MessageBox("同期参数回读命令");
					m_CStringStatus="Loading...syn parameter";
					UpdateData(FALSE);
					ErrorCounter=0;
				//	Connect_Index++;
					continue;

				}
				else if(RXTele_Nr==32)                        //交流AD参数回读命令  相应
				{
					for(int len=0;len<((UCHAR)Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.AD1_dlg.ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
					//MessageBox("交流AD参数回读命令");
			
					m_CStringStatus="Loading...AD parameter";
					ErrorCounter=0;
                   //  Connect_Index++;
					continue;
				}
				else if(RXTele_Nr==48)                        //AD angle命令  相应
				{
				    for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.ADCacul_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
					//MessageBox("Loading...Base angle");
                    m_CStringStatus="Loading...Base angle";
                    ErrorCounter=0;
					break;
					//ErrorCounter=0;
                 //   Connect_Index++;
				}
				
				else if(RXTele_Nr==36)                        //AD计算值回读命令  相应
				{
				    for(int len=0;len<(UCHAR)(Connect_Telegram.Block_len);len++)
					{
						ZJM_dlg.ADCacul_ValidData[len]=(UCHAR)Connect_Telegram.Telegarm_Array[len];     //将有效数据传递给 AD参数回读数组ValidData[]
					}
					TXDATA1[0]=0xa2;
					SentData(TXDATA1);                        //master -> slave:     A2
					//MessageBox("Loading...AD Value");
                    m_CStringStatus="Loading...AD parameter";
					ErrorCounter=0;
                 //   Connect_Index++;
					continue;
				}
				else 
				{
				//	ErrorCounter++;//返回命令错误时
					continue;
				}
			}		
	}

}
*/		
		
		if((Down==IDC_CONNECT && Connect_Index==0) && ErrorCounter<5)        //TQCS_block_35  其中Down用于表示第一次当Connect时的相应
		{
//MessageBox("TQCS_block_35");
			Fun_Connect(TQCS_block_35,0);
		}
		if((Down==IDC_CONNECT && Connect_Index==1)&&ErrorCounter<5 )        //ACAD_block_33
		{
//MessageBox("ACAD_block_33");
			Fun_Connect(ACAD_block_33,0);		
		}
		if(((Down==IDC_CONNECT && Connect_Index==2)||(Down==IDC_BUTTON_ZJM_FETCH &&Connect_Index==0))&& ErrorCounter<5)        //ADData_block_37
		{
//MessageBox("ADData_block_37");
			Fun_Connect(ADData_block_37,0);		
		}
		if(((Down==IDC_CONNECT  && Connect_Index==3)||(Down==IDC_BUTTON_ZJM_FETCH &&Connect_Index==1))&& ErrorCounter<5)         //Msg_h_block_12
		{
			Fun_Connect(AC_angle_block_47,0);
//MessageBox("AC_angle_block_47");
//MessageBo/x("Msg_h_block_12");
//			Connect_Telegram.TelegramBlock =Msg_h_block_12;
//			Fun_Connect(Connect_Telegram.TelegramBlock);
		/*	Connect_Telegram.PACK_SELECT=TRUE;
			Zero_NR=1;

			Fun_Connect(Msg_h_block_12,Zero_NR);
			*/
		}
		if(((Down==IDC_CONNECT  && Connect_Index==4)||(Down==IDC_BUTTON_ZJM_FETCH &&Connect_Index==2)) && ErrorCounter<5 &&RX_Msg_End==FALSE)         //Msg_block_13
		{
//MessageBox("Msg_block_13");
			Fun_Connect(AC_angle_block_47,0);
		/*	Connect_Telegram.PACK_SELECT=FALSE;
			Fun_Connect(Msg_block_13,0);*/
		//	Connect_Index=3;	
		}
		if(((Down==IDC_CONNECT  && Connect_Index==6)||(Down==IDC_BUTTON_ZJM_FETCH &&Connect_Index==3)) && ErrorCounter<5 &&RX_Msg_End==FALSE)         //Msg_block_13
		{
//MessageBox("Msg_block_13");
			Fun_Connect(Message_block_49,0);
		/*	Connect_Telegram.PACK_SELECT=FALSE;
			Fun_Connect(Msg_block_13,0);*/
		//	Connect_Index=3;	
		}
		if(Down==IDC_CONNECT && ErrorCounter<5 && Connect_Index==5)         //
		{
			Down =FALSE;
			if(IDCANCEL== ZJM_dlg.DoModal())
				DestroyWindow();
			Connect_Index=0;
		}
	}
else if(nIDEvent==12 || ErrorCounter>4)
	{
		KillTimer(12);
		MessageBox("communication error");
		if(Down==IDC_CONNECT)
		DestroyWindow();
	}

//////////////////////////////////////////////////////////////////////////

	CDialog::OnTimer(nIDEvent);
//	MessageBox("ontimer end");
//	UpdateData(FALSE);

}

BOOL CNew1Dlg::Fun_Connect(TeleBlock TeleBlock1 ,int zero_NR)       //function: generate the telegram ,and then sent them.
{
	UCHAR *pTXDATA1;                                              //Pointer of the sent data
//	if(Connect_Telegram.PACK_SELECT==FALSE)
		pTXDATA1=Connect_Telegram.TelePack(TeleBlock1.Station_adr,TeleBlock1.Telegram_Nr,TeleBlock1,zero_NR);
//	else if(Connect_Telegram.PACK_SELECT ==TRUE)
//		pTXDATA1=Connect_Telegram.TelePack1(TeleBlock1.Station_adr,TeleBlock1.Telegram_Nr,TeleBlock1,0);
//MessageBox("FUN_Connect");
	Connect_Telegram.Block_len=pTXDATA1[1];//block len
	for(int tt=0;tt<(Connect_Telegram.Block_len+6);tt++)
	TXDATA1[tt]=*pTXDATA1++;
	TXDATA1[tt]='\0';
	SentData(TXDATA1);

	return TRUE;
}

