// Dlg_TQCS.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_TQCS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQCS dialog


Dlg_TQCS::Dlg_TQCS(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_TQCS::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_TQCS)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_TQCS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_TQCS)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_TQCS, CDialog)
	//{{AFX_MSG_MAP(Dlg_TQCS)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_TQCS message handlers
