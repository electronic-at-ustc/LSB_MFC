// LSB_MFCDlg.h : header file
//

#if !defined(AFX_LSB_MFCDLG_H__835C8BCB_F99E_4D3A_9C2E_37241E42E950__INCLUDED_)
#define AFX_LSB_MFCDLG_H__835C8BCB_F99E_4D3A_9C2E_37241E42E950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLSB_MFCDlg dialog

class CLSB_MFCDlg : public CDialog
{
// Construction
public:
	CLSB_MFCDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	//{{AFX_DATA(CLSB_MFCDlg)
	enum { IDD = IDD_LSB_MFC_DIALOG };
	CString	m_edit_dir;
	CString	m_edit_printf;
	CString	m_RMS;
	CString	m_diff_rms;
	CString	m_edit_syn_apd_diff;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSB_MFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	public:
		char GetChannelNum( char *buf);
		int GetFine( char *buf);
		__int64 QSHENQITDCTime(char *pdata);
		int QSHENQIGetCoarse(char *pdata);
		int QSHENQIGetFine(char *pdata);
		void TimeSort(int cnt, __int64 *pTime, unsigned char *pChannel);
		void TimeSortSub(int start,int end, __int64 *pTime, unsigned char *pChannel);
		int TimeAscend(__int64 time1, __int64 time2);
	public:
		float LSB[6];
		char writefilepath[256];
		float b[6][400];
		int N[6];
		double FineNUM[6][280];
		#define TDC_OV	167772160000I64
		#define TDC_SHENQI_OV 1677721600000I64
		#define PS_PER_SEC	1000000000000I64
		#define CHANNEL_GPS	5
		#define MAX_TDC_NUM	(24*1024*1024)
		#define PS_PER_US	      1000000I64
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLSB_MFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDir();
	afx_msg void OnButtonLsb();
	afx_msg void OnButtonInl();
	afx_msg void OnButtonDnl();
	afx_msg void OnButtonRms();
	afx_msg void OnChangeEditRmsValue();
	afx_msg void OnChangeEditPrintf();
	afx_msg void OnChangeEdit_diff_rms();
	afx_msg void OnSynApdDiff();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSB_MFCDLG_H__835C8BCB_F99E_4D3A_9C2E_37241E42E950__INCLUDED_)
