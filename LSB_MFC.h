// LSB_MFC.h : main header file for the LSB_MFC application
//

#if !defined(AFX_LSB_MFC_H__60475499_8479_4ACF_A2C1_F65E024F6E4F__INCLUDED_)
#define AFX_LSB_MFC_H__60475499_8479_4ACF_A2C1_F65E024F6E4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLSB_MFCApp:
// See LSB_MFC.cpp for the implementation of this class
//

class CLSB_MFCApp : public CWinApp
{
public:
	CLSB_MFCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSB_MFCApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLSB_MFCApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSB_MFC_H__60475499_8479_4ACF_A2C1_F65E024F6E4F__INCLUDED_)
