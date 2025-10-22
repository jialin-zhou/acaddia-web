// Dlg_ADAdjust.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_ADAdjust.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADAdjust dialog


Dlg_ADAdjust::Dlg_ADAdjust(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_ADAdjust::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_ADAdjust)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_ADAdjust::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_ADAdjust)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_ADAdjust, CDialog)
	//{{AFX_MSG_MAP(Dlg_ADAdjust)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_ADAdjust message handlers
