// DLg_DIMset.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "DLg_DIMset.h"

#include "Dlg_ZJM.h"
#include "new1Dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DLg_DIMset dialog


DLg_DIMset::DLg_DIMset(CWnd* pParent /*=NULL*/)
	: CDialog(DLg_DIMset::IDD, pParent)
{
	//{{AFX_DATA_INIT(DLg_DIMset)
	m_public_dim_select = 0;
	m_line_volt_view_select = 0;
	//}}AFX_DATA_INIT
}


void DLg_DIMset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DLg_DIMset)
	DDX_Radio(pDX, IDC_RADIO1, m_public_dim_select);
	DDX_Radio(pDX, IDC_RADIO3, m_line_volt_view_select);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DLg_DIMset, CDialog)
	//{{AFX_MSG_MAP(DLg_DIMset)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLg_DIMset message handlers

void DLg_DIMset::OnRadio1() 
{
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->DIM_public=16384;
	m_public_dim_select=0;
     
	// TODO: Add your control notification handler code here	
}

void DLg_DIMset::OnRadio2() 
{
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->DIM_public=8192;
	m_public_dim_select=1;
	// TODO: Add your control notification handler code here	
}

void DLg_DIMset::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->DIM_Line_Vot_style=0;
	m_line_volt_view_select = 0;
}

void DLg_DIMset::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->DIM_Line_Vot_style=1;
	m_line_volt_view_select = 1;
}


void DLg_DIMset::OnOK() 
{
	// TODO: Add extra validation here
	Dlg_ZJM * pParent_ZJM = (Dlg_ZJM *)GetParent();
	CNew1Dlg * pParent =(CNew1Dlg *)pParent_ZJM->GetParent();
	pParent->DIM_public=16384;
	pParent->DIM_Line_Vot_style=0;
	
	m_public_dim_select=0;
	m_line_volt_view_select = 0;
	UpdateData(FALSE);
	//CDialog::OnOK();
}

