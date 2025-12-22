// Dlg_ADData.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_ADData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADData dialog


Dlg_ADData::Dlg_ADData(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_ADData::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_ADData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_ADData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_ADData)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_ADData, CDialog)
	//{{AFX_MSG_MAP(Dlg_ADData)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADData message handlers
