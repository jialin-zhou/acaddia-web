// Dlg_DFUPicture.cpp : implementation file
//

#include "stdafx.h"
#include "new1.h"
#include "Dlg_DFUPicture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dlg_DFUPicture dialog


Dlg_DFUPicture::Dlg_DFUPicture(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_DFUPicture::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dlg_DFUPicture)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Dlg_DFUPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dlg_DFUPicture)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dlg_DFUPicture, CDialog)
	//{{AFX_MSG_MAP(Dlg_DFUPicture)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dlg_DFUPicture message handlers
