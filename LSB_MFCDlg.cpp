// LSB_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LSB_MFC.h"
#include "LSB_MFCDlg.h"
#include <math.h>
#define M_PI  3.14159265359
#define CHANNEL_GPS 5
#define CHANNEL_SYN 4

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
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSB_MFCDlg dialog

CLSB_MFCDlg::CLSB_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLSB_MFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLSB_MFCDlg)
	m_edit_dir = _T("");
	m_edit_printf = _T("");
	m_RMS = _T("");
	m_diff_rms = _T("");
	m_edit_syn_apd_diff = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLSB_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLSB_MFCDlg)
	DDX_Text(pDX, IDC_EDIT_DIR, m_edit_dir);
	DDX_Text(pDX, IDC_EDIT_PRINTF, m_edit_printf);
	DDX_Text(pDX, IDC_EDIT_RMS_VALUE, m_RMS);
	DDX_Text(pDX, IDC_EDIT_DIFF_RMS, m_diff_rms);
	DDX_Text(pDX, IDC_EDIT_SYN_APD_DIFF, m_edit_syn_apd_diff);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLSB_MFCDlg, CDialog)
	//{{AFX_MSG_MAP(CLSB_MFCDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDBUTTON_DIR, OnDir)
	ON_BN_CLICKED(ID_BUTTON_LSB, OnButtonLsb)
	ON_BN_CLICKED(IDC_BUTTON_INL, OnButtonInl)
	ON_BN_CLICKED(IDC_BUTTON_DNL, OnButtonDnl)
	ON_BN_CLICKED(IDC_BUTTON_RMS, OnButtonRms)
	ON_EN_CHANGE(IDC_EDIT_RMS_VALUE, OnChangeEditRmsValue)
	ON_EN_CHANGE(IDC_EDIT_PRINTF, OnChangeEditPrintf)
	ON_EN_CHANGE(IDC_EDIT_DIFF_RMS, OnChangeEdit_diff_rms)
	ON_BN_CLICKED(IDC_SYN_APD_DIFF, OnSynApdDiff)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSB_MFCDlg message handlers

BOOL CLSB_MFCDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLSB_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLSB_MFCDlg::OnPaint() 
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
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLSB_MFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
int CLSB_MFCDlg::GetFine(char* buf)
{
		int Fine;
		Fine = *(unsigned char *)(buf + 3) & 0x10;
		Fine = (Fine<<4) | *(unsigned char *)(buf + 7);
		return Fine;
}
char CLSB_MFCDlg::GetChannelNum(char* buf)
{
	unsigned char channel;
	channel = *(unsigned char *)(buf + 6);
	switch(channel)
	{
	case 0x40:
		return CHANNEL_GPS;
	case 0x41:
		return CHANNEL_SYN;
	case 0x42:
		return 1;
	case 0x43:
		return 2;
	case 0x44:
		return 3;
	case 0x45:
		return 4;
	}
}
void CLSB_MFCDlg::OnDir() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "TDC data files", NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_EXPLORER |OFN_NOCHANGEDIR,
		"TDC Data Files|*.txt;*.dat|", NULL);
	if (dlg.DoModal() != IDOK)
		return;
	m_edit_dir=dlg.GetPathName();

	UpdateData(FALSE);
}

void CLSB_MFCDlg::OnButtonLsb() 
{
	// TODO: Add your control notification handler code here
	//时间测量数据
	//随机数数据
	//稳相算法数据
	//发射端 接收端指示
	FILE *fptdc,*fprnd,*fpps,*fp,*fprco;
	char psfilepath[256];
	char rndfilepath[256];
	char tdcfilepath[256];
	char rcofilepath[256];
	
	fp = fopen(m_edit_dir,"rb");
	sprintf(writefilepath,m_edit_dir.Left(m_edit_dir.GetLength()-4));
	strcpy(rcofilepath,writefilepath);
	strcat(rcofilepath,"_解帧数据.dat");
	strcpy(tdcfilepath,writefilepath);
	strcat(tdcfilepath,"_时间测量数据.dat");
	strcpy(rndfilepath,writefilepath);
	strcat(rndfilepath,"_随机数.dat");
	strcpy(psfilepath,writefilepath);
	strcat(psfilepath,"_稳相数据.dat");
    char frame[2048];
	fprco = fopen(rcofilepath,"wb");
	fptdc = fopen(tdcfilepath,"wb");
	fprnd = fopen(rndfilepath,"wb");
	fpps = fopen(psfilepath,"wb");
	while(fread(frame, 1, 2048,fp) == 2048)
	{
		fwrite(frame + 8, 1, 2032, fprco);
	}
	fclose(fp);
	fclose(fprco);
	fprco = fopen(rcofilepath,"rb");
	unsigned char *buffer, temp_buf[7];
	buffer = (unsigned char *)malloc(8);
	unsigned char time;
	unsigned char dac_cnt=0, dac_cnt_rd=0;
	double half_voltage_V[6], PM_voltage, expected_algrithm_out,offset_voltage;
	short count_apd1[6], count_apd2[6];
	while(fread(buffer,1,8,fprco) ==8)
	{
		
		time = *(buffer+1);
		if((time >> 4) == 0xB)
		{//稳相数据
			if((*(buffer+3) & 0xF0) == 0xF0){
			//APD计数值
				dac_cnt_rd = (char)(((*(buffer+5) & 0xF0) >> 4)-1);
				half_voltage_V[dac_cnt_rd]	= ((*(buffer+2) | (*(buffer+3) & 0x0F) << 8)-2048) * 5.0/4096.0;
				count_apd2[dac_cnt_rd]  = *(buffer+4) | (*(buffer+5) & 0x0F) << 8;
				count_apd1[dac_cnt_rd]  = *(buffer+6) | (*(buffer+7) & 0x0F) << 8;

				fprintf(fpps,"通道%d:\t%f\t%d\t%d\t\n",dac_cnt_rd+1,half_voltage_V[dac_cnt_rd],count_apd1[dac_cnt_rd],count_apd2[dac_cnt_rd]);
				if(dac_cnt_rd == 4){
				//计算预期输出
					float sin_x = (float)(count_apd2[2] - count_apd2[0]);
					float cos_x = (float)(count_apd2[3] - count_apd2[1]);
					//半波电压值
					PM_voltage = fabs(half_voltage_V[1] - half_voltage_V[0])*2.0;//
					////偏移电压值
					offset_voltage = half_voltage_V[1];
					double atan_x = atan(sin_x/cos_x);
					fprintf(fpps,"%f\t", atan_x);
					atan_x = atan_x/M_PI;
					fprintf(fpps,"%f\t", atan_x);
					if(sin_x >= 0 && cos_x < 0){
						atan_x	= atan_x + 1;
					}
					else if(sin_x < 0 && cos_x < 0){
						atan_x	= atan_x - 1;
					}
					fprintf(fpps,"%f\t", atan_x);

					//0-pi/2
					expected_algrithm_out = -1*atan_x*PM_voltage + offset_voltage;
					fprintf(fpps,"%f\t", atan_x*PM_voltage*4096.0/5.0);
					fprintf(fpps,"%f\t", 2048+1*expected_algrithm_out*4096.0/5.0);
					fprintf(fpps,"VC计算结果：%f\t反正切值：%f\t计算结果%f\t压差：%f\n",PM_voltage,atan_x,expected_algrithm_out,expected_algrithm_out-half_voltage_V[4]);
					
					fprintf(fpps,"模拟逻辑计算结果：");
					float tan_x = sin_x/cos_x;
					float atan_x_div_pi = 0;
					//double atan_x = 0;
					fprintf(fpps,"sin_x/cos_x:%f,sinx:%f\tcosx:%f\t\n", tan_x, sin_x, cos_x);

					if(fabs(tan_x) > 1){
						atan_x	= M_PI/4 + atan((fabs(tan_x)-1)/(fabs(tan_x)+1));
						atan_x_div_pi = 1.0+4.0*atan((fabs(tan_x)-1)/(fabs(tan_x)+1))/M_PI;
					}
					else{
						atan_x = atan(fabs(sin_x/cos_x));
						atan_x_div_pi = 4.0*atan(fabs(sin_x/cos_x))/M_PI;
					}

					float temp_voltage = PM_voltage * atan_x_div_pi/4.0;
					fprintf(fpps,"绝对值:%f\t\n", temp_voltage*4096.0/5.0);
					fprintf(fpps,"atan_x【0,pi/2】:%f\t%f\t%f\t\n", atan_x,atan_x_div_pi,temp_voltage);
					
					if(tan_x < 0){
						atan_x	= -1*atan_x;
						atan_x_div_pi = -1*atan_x_div_pi;
					//	temp_voltage = -1.0*temp_voltage;
					}
					fprintf(fpps,"调整符号:%f\t%f\t:%f\t\n", atan_x,atan_x_div_pi,temp_voltage);
				
					if(sin_x >= 0 && cos_x < 0){
						temp_voltage = PM_voltage - temp_voltage;
					}
					else if(sin_x < 0 && cos_x < 0){
						temp_voltage = -1.0*(PM_voltage - temp_voltage);
					}
					else if(sin_x > 0 && cos_x > 0){
						temp_voltage = temp_voltage;
					}
					else if(sin_x < 0 && cos_x > 0){
						temp_voltage = -1.0*temp_voltage;
					}

					if(sin_x >= 0 && cos_x < 0){
						atan_x	= atan_x + M_PI;
						atan_x_div_pi = atan_x_div_pi + 4.0;
					//	temp_voltage = temp_voltage + PM_voltage*4;
					}
					else if(sin_x < 0 && cos_x < 0){
						atan_x	= atan_x - M_PI;
						atan_x_div_pi = atan_x_div_pi - 4.0;
					//	temp_voltage = temp_voltage - PM_voltage*4;
					}
					fprintf(fpps,"绝对值:%f\t\n", temp_voltage*4096.0/5.0);
					fprintf(fpps,"十六进制:%f\t\n", (-1.0*temp_voltage+2.5)*4096/5.0);
					temp_voltage = -1.0*temp_voltage + offset_voltage;
					fprintf(fpps,"十六进制:%f\t\n", (temp_voltage+2.5)*4096/5.0);
					fprintf(fpps,"atan_x扩展到[-pi,pi]:%f\t%f\t,%f\t,%f\t\n", atan_x,atan_x/M_PI,atan_x_div_pi/4.0, temp_voltage);
					double expected_algrithm_out2 = -1*atan_x_div_pi/4.0*PM_voltage + offset_voltage;
					fprintf(fpps,"模拟逻辑计算结果：%f\t反正切值：%f\t计算结果%f\t压差：%f\n",PM_voltage,atan_x,expected_algrithm_out2,expected_algrithm_out2-expected_algrithm_out);
					
				}
			}
			else{
			//稳相算法输出结果
				int poc_num = ((*(buffer+4) & 0x0F) << 4) | (*(buffer+7) & 0xF0) >> 4;
				int dac_value = *(buffer+6) | (*(buffer+7) & 0x0F) << 8;
				fprintf(fpps,"逻辑计算结果：POC:%d\tPM电压%d\t%f\t\n",poc_num,dac_value,(dac_value-2048)*5.0/4096.0);
			}
		}
		else if(time == 0xff)
		{//时间测量数据
				fwrite(buffer,1,8,fptdc);
		}
		else if((time >> 4) == 0xA)
		{//随机数数据
			temp_buf[0] = *(buffer+0);
			temp_buf[1] = *(buffer+3);
			temp_buf[2] = *(buffer+2);
			temp_buf[3] = *(buffer+5);
			temp_buf[4] = *(buffer+4);
			temp_buf[5] = *(buffer+7);
			temp_buf[6] = *(buffer+6);
			fwrite(temp_buf,1,7,fprnd);
		}
		
	}
	free(buffer);

	fclose(fptdc);
	fclose(fprnd);
	fclose(fpps);

	FILE *fpfine_cnt;
	fptdc = fopen(tdcfilepath,"rb");
	char fine_cntfilepath[256];
	strcpy(fine_cntfilepath,writefilepath);
	strcat(fine_cntfilepath,"_fine_cnt.txt");
	fpfine_cnt = fopen(fine_cntfilepath,"wb");
	int a[6][400];
	unsigned short fine;
	unsigned char channel;
	int i = 0,j = 0;
	int cnt_total[6];
	char *buf;
	buf = (char*)malloc(9);//////////////
	memset(buf,0,sizeof(char)*8);
	memset(a,0,sizeof(int)*400*6);
	memset(b,0,sizeof(float)*400*6);
	memset(cnt_total,0,sizeof(int)*6);
	
	while(fread(buf,8,1,fptdc) == 1)
	{
		channel = GetChannelNum(buf);
	
		fine = GetFine(buf);
		a[channel][fine]++;
		cnt_total[channel]++;

	}


	bool judge = 1;
	int cnt_max[6];


	for(j = 0; j < 6; j++)
	{
		judge = 1;
		for(i = 399; i >= 0; i--)
		{
			if(judge)
			{
				if(a[j][i] == 0)
				{
					
					cnt_max[j] = i;
					N[j] = cnt_max[j];
					continue;
				}
				judge = 0;
			}
		
				b[j][i] = (a[j][i] * 6250*1.0 /cnt_total[j] );
				fprintf(fpfine_cnt,"%5d\t%5d\t%.2f\n",i,a[j][i],b[j][i]);
			
			
		}
		LSB[j] = float(6250*1.0 / cnt_max[j]);
		fprintf(fpfine_cnt,"%.2f\n" ,LSB[j]);
	}


	
	fclose(fptdc);
	fclose(fpfine_cnt);
	m_edit_printf.Format(m_edit_printf+"%s\r\n\r\n","LSB finished!");	
	UpdateData(FALSE);
}

void CLSB_MFCDlg::OnButtonInl() 
{
	// TODO: Add your control notification handler code here
	FILE *fpinl;
	FILE *fpinf;
	char inlfilepath[256];
	char inffilepath[256];
	strcpy(inlfilepath, writefilepath);
	strcat(inlfilepath,"_INL.txt");
	strcpy(inffilepath,writefilepath);
	strcat(inffilepath,"_inf.dat");
	fpinl = fopen(inlfilepath,"wb");
	fpinf = fopen(inffilepath,"wb");
	float c[6][400];
	float INL[6][400];
	int i;
	int j;
	
	memset(c, 0,  sizeof(float)*6*400);
	memset(INL, 0 ,sizeof(float)*6*400);
	for(j = 0; j < 6; j++)
	{
		for(i = 0; i < N[j]; i++)
		{
			c[j][i+1] = b[j][i] + c[j][i];
			INL[j][i] = (c[j][i+1] - i*LSB[j])/LSB[j];
			fprintf(fpinl, "%d\t%.2f\n",i, INL[j][i]);
		}
	}
/////////////////////////////////////////////////
	for(j = 0; j<6; j++)
	{
		if(j == 5)
		{
			N[j] = N[j-4];
		}
		if(j == 0 )
		{
			N[j] = N[j+1];
		}
		for(i = 1; i < N[j]+2; i++)
		{
			if(j == 5)
			{
				c[j][i] = c[j-4][i];
			}
			if(j == 0)
			{
				c[j][i] = c[j+1][i];
			}
			fprintf(fpinf,"%f,",c[j][i]);
		}
		fprintf(fpinf,"\n");           ///////  42 的细计数给了40  和 41 。
	}
////////////////////////////////////////////////////        40 GPS 5; 41 0; 42 1; 43 2; 44 3; 45  4;
	fclose(fpinl);
	fclose(fpinf);
	m_edit_printf.Format(m_edit_printf+"%s\r\n\r\n","INL finished!");
	UpdateData(FALSE);
	
}




void CLSB_MFCDlg::OnButtonDnl() 
{
	// TODO: Add your control notification handler code here
	FILE *fpdnl;
	char dnlfilepath[256];
	strcpy(dnlfilepath, writefilepath);
	strcat(dnlfilepath,"_DNL.txt");
	fpdnl = fopen(dnlfilepath,"wb");
	float c[6][400];
	float DNL[6][400];
	int i,j;
	
	memset(c, 0,  sizeof(float)*6*400);
	memset(DNL, 0 ,sizeof(float)*6*400);
	for(j = 0; j < 6; j++)
	{
		for(i = 0; i < N[j]; i++)
		{
			c[j][i+1] = b[j][i] + c[j][i];
			DNL[j][i] =(c[j][i+1] - c[j][i] - LSB[j])/LSB[j];
			fprintf(fpdnl, "%d\t%.2f\n",i, DNL[j][i]);
		}
	}
	
	fclose(fpdnl);
	m_edit_printf.Format(m_edit_printf+"%s\r\n\r\n","DNL finished!");
	UpdateData(FALSE);
	
}


int CLSB_MFCDlg::QSHENQIGetCoarse(char *pdata)
{
	int Coarse;
	
	Coarse = *(unsigned char *)(pdata+3) & 0x0F;
	Coarse = (Coarse << 8) | *(unsigned char *)(pdata + 2);
	Coarse = (Coarse << 8) | *(unsigned char *)(pdata + 5);
	Coarse = (Coarse << 8) | *(unsigned char *)(pdata + 4);
	return Coarse;
}

int CLSB_MFCDlg::QSHENQIGetFine(char *pdata)
{
	int Fine;
	Fine = *(unsigned char *)(pdata + 3) & 0x10;
	Fine = (Fine << 4) | *(unsigned char *)(pdata + 7);
	
	return Fine;
}
__int64 CLSB_MFCDlg::QSHENQITDCTime(char *pdata)
{
	__int64 tm;
	
	unsigned short fine;
	unsigned char channel;
	
	tm = QSHENQIGetCoarse(pdata);
	tm *= 6250;
	
    channel = GetChannelNum(pdata);
	fine = QSHENQIGetFine(pdata);
	
	tm = tm - __int64(FineNUM[channel][fine]);////////////////////////
	
	return tm;
}

int CLSB_MFCDlg::TimeAscend(__int64 time1, __int64 time2)
{
	__int64 time;
	__int64 diff;
	if(time2 >= time1)
	{
		time = time2;
	}
	else
	{
	
			time = time2 + TDC_SHENQI_OV;
		
	}
	diff = time - time1;
	if(diff < 1000000000000)//30ms
	{ 
		return 1; //ascend
	}
	if(diff > 1600721600000)//120ms
	{
		return 0; //descend
	}
	return -1; //well, two adjacent events should be in 30ms.
}
void CLSB_MFCDlg::TimeSortSub(int start,int end, __int64 *pTime, unsigned char *pChannel)
{
	int i,j;
	unsigned char channel;
	__int64 time;
	int cmp;
	for(i = start; i < end - 1; i++)
		for(j = i + 1; j < end; j++){
			if(pChannel[i] == 0xFF || pChannel[j] == 0xFF){
				continue;
			}
			cmp = TimeAscend(pTime[i],pTime[j]);
			
			if(cmp == 0)
			{
				time = pTime[i]; pTime[i] = pTime[j]; pTime[j] = time;
				channel = pChannel[i]; pChannel[i] = pChannel[j]; pChannel[j] = channel;
			}
			else if(cmp == -1){
				pChannel[i] = 0xFF;
				pChannel[j] = 0xFF;
			}
		}
}
void CLSB_MFCDlg::TimeSort(int cnt, __int64 *pTime, unsigned char *pChannel)
{
	
#define SORT_RANGE 20	
	
	int idx1,idx2;
	idx1 = 0;
	while(idx1 < cnt - 1){
		idx2 = idx1 + SORT_RANGE; 
		if(idx2 >= cnt){
			idx2 = cnt -1;
		}
		TimeSortSub(idx1,idx2,pTime,pChannel);
		idx1 += SORT_RANGE/2;
	}
}

void CLSB_MFCDlg::OnButtonRms() 
{
	// TODO: Add your control notification handler code here
	char recvfilepath[256];
	char recvtimefilepath[256];
	char recvfixfilepath[256];
	char inffilepath[265];
	char recvtimetxtfilepath[256];
	char recvfixtxtfilepath[256];
	strcpy(recvfilepath, writefilepath);
	strcat(recvfilepath,"_ff.dat");
	strcpy(recvtimetxtfilepath, writefilepath);
	strcat(recvtimetxtfilepath,"_ff_time_txt.txt");
	strcpy(recvtimefilepath, writefilepath);
	strcat(recvtimefilepath,"_ff_time.dat");
	strcpy(recvfixfilepath, writefilepath);
	strcat(recvfixfilepath,"_ff_fix.dat");
	strcpy(recvfixtxtfilepath, writefilepath);
	strcat(recvfixtxtfilepath,"_ff_fix_txt.txt");
	strcpy(inffilepath, writefilepath);
	strcat(inffilepath,"_inf.dat");

	FILE *fp,*fptime,*fpfixed,*fpinf,*fptimetxt,*fpfixtxt;
	fp = fopen(recvfilepath,"rb");
	fpinf = fopen(inffilepath,"rb");
	fptime = fopen(recvtimefilepath,"wb");
	fpfixed = fopen(recvfixfilepath,"wb");
	fptimetxt = fopen(recvtimetxtfilepath,"w");
	int i = 0;
	int cnt = 0;
	char *buf;
	double finedata=0;
	buf = (char*)malloc(1024*1024);

	//读取csv文件
	int j=0;
	while(!feof(fpinf))
	{

		fscanf(fpinf,"%lf,",&finedata);
		if (finedata>-0.09 && finedata<0.09)
		{
			fscanf(fpinf,"%c,",buf);
			j=0;
			i++;
		}
		else
		{
			FineNUM[i][j]=finedata;
			j++;
		}

	}
	free(buf);
	fclose(fpinf);
	

	char buffer[8];
	
	unsigned char *ptr;

	unsigned char channel;
	__int64 time;

	FILE *fp3;
	char recvnumfilepath[256];
	strcpy(recvnumfilepath,writefilepath);
	strcat(recvnumfilepath,"_recv_num.txt");
	fp3 = fopen(recvnumfilepath,"w");

	fprintf(fp3,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n","secs","apd0","apd1","apd2","apd3","syn","sumcnt");

	int apdcnt0 = 0, apdcnt1 = 0, apdcnt2 = 0, apdcnt3 = 0, syncnt = 0, sumcnt = 0;
	int seccnt = 1;

	i = 0;
	ptr = (unsigned char *)malloc(9*1024*12800);
	while(fread(buffer,1,8,fp) == 8)
	{
		if((GetChannelNum(buffer) == 0xFF))
		{
			continue;
		}
		if(feof(fp))
		{
			break;
		}

		channel = GetChannelNum(buffer);
	
		if (channel == 0 )
		{
			apdcnt0 ++;
		}
		else if (channel == 1)
		{
			apdcnt1++;
		}
		else if (channel == 2)
		{
			apdcnt2++;
		}
		else if (channel == 3)
		{
			apdcnt3 ++;
		}
		else if (channel == 4)
		{
			syncnt++;
		}

		if (channel >= 0 && channel<4)
			sumcnt++;

		if(channel == 0xFF){
			time = QSHENQITDCTime(buffer);
		}
		else{
			time = QSHENQITDCTime(buffer);
		}
		memcpy(ptr+9*i,&channel,1);
		memcpy(ptr+9*i+1,&time,8);
		i++;

		if(channel == 5)
		{
		
				fwrite(ptr,1,9*i,fptime);
				fprintf(fp3,"%3d\t%6d\t%6d\t%6d\t%6d\t%6d\t%6d\n",seccnt,apdcnt0,apdcnt1,apdcnt2,apdcnt3,syncnt,sumcnt);
				seccnt++;
				apdcnt0 = 0, apdcnt1 = 0, apdcnt2 = 0, apdcnt3 = 0, syncnt = 0, sumcnt = 0;
			i = 0;
		}
	}
	fclose(fptime);
	fptime = fopen(recvtimefilepath,"rb");
	unsigned char buf1[9];
	__int64 time1;
	while(fread(buf1,1,9,fptime)==9)
	{
		time1 = *(__int64*)(buf1 + 1);
		fprintf(fptimetxt,"%d\t%15I64d\n",buf1[0],time1);
	}
	fclose(fptimetxt);
	fclose(fp);
	fclose(fpinf);
	fclose(fptime);
	fclose(fp3);
	free(ptr);
	fptime = fopen(recvtimefilepath,"rb");
	fpfixed = fopen(recvfixfilepath,"wb");
	fpfixtxt = fopen(recvfixtxtfilepath,"w");
	

	__int64 *pTime;
	unsigned char *pChannel;
	unsigned char buffer1[9];
	
	cnt = 0;
	
	i = 0;
	j = 0;
	
	__int64 last_time = 0;
	__int64 time_addon = 0;
	
	__int64 last_gps_time = 0;
	int last_gps_pos = 0;
	
	pTime = (__int64 *)malloc(sizeof(__int64)*MAX_TDC_NUM);
	pChannel = (unsigned char *)malloc(sizeof(unsigned char)*MAX_TDC_NUM);
	
	cnt = 0;
	while(fread(buffer1,1,9,fptime) == 9)
	{
		if(buffer1[0] > 7){
			continue;
		}
		pChannel[cnt] = buffer1[0];
		pTime[cnt] = *(__int64 *)(buffer1 + 1);
		cnt ++;
		if(cnt >= MAX_TDC_NUM)
		{
			break;
		}
	}

//////////////////////////////////////////
	
	TimeSort(cnt,pTime,pChannel);
///////////////////////////////////MASK_DROP_OUTORDER
	j = 0;
	for(i = 0; i < cnt; i++)
	{
		if(pChannel[i] != 0xFF)
		{
			pChannel[j] = pChannel[i];
			pTime[j] = pTime[i];
			j++;
		}
	}
	cnt = j;

	////////////////
	for(i = cnt - 1; i >= 0; i--)
	{
		if(pChannel[i] == CHANNEL_GPS)
		{
			cnt = i + 1;
			break;
		}
		}
	//////////////////////MASK_DROP_GPS_BEFORE
	for(i = 0; i < cnt; i++)
	{
		if(pChannel[i] == CHANNEL_GPS)
		{
			memmove(pChannel,pChannel+i,cnt - i);
			memmove(pTime,pTime+i,(cnt-i)*sizeof(__int64));
			cnt = cnt -i;
			break;
		}
		}
	////////////////////////////////////////MASK_DROP_GPS_AFTER
	int gps_ov;
	for(i = 0; i < cnt; i++)
	{
		if(pTime[i] < last_time)
		{
			time_addon += TDC_SHENQI_OV;
		}
		last_time = pTime[i];
		pTime[i] += time_addon;
		if(pChannel[i] == CHANNEL_GPS)
		{
			__int64 temp;
			for(j = 0; j < 200; j++){ //well, we search max 200s*1.67S.
				temp = ((pTime[i] + j*TDC_SHENQI_OV - last_gps_time) % PS_PER_SEC);
				if(temp > PS_PER_SEC/2 ){
					temp -= PS_PER_SEC;
				}
				if((temp < 500000000)  && (temp > -500000000)) //50us
				{
					time_addon += j*TDC_SHENQI_OV;
					pTime[i] += j*TDC_SHENQI_OV;
					break;
				}
			}
			if(j){ // data lost found
				for(j = last_gps_pos; j < i; j++){//remove data for last second
					pChannel[j] = 0xFF;
				}
			}
			gps_ov = (int)(last_gps_time / TDC_SHENQI_OV);
			gps_ov -= 10*1000/167;
			if(gps_ov < 0){
				gps_ov = 0;
			}
			//recover time using GPS
			__int64 gps_error;
			gps_error = (last_gps_time /PS_PER_SEC + 1) * 100* PS_PER_US;
			for(j = gps_ov; j < 40*1000/167 + gps_ov; j++){ //well, we search max 40s.
				temp = ((last_time + j*TDC_SHENQI_OV) % PS_PER_SEC);
				if(temp > PS_PER_SEC/2 ){
					temp -= PS_PER_SEC;
				}
				if((temp < gps_error)  && (temp > -1*gps_error)) 
				{
					time_addon = j*TDC_SHENQI_OV;
					pTime[i] = last_time + time_addon;
					if(pTime[i] < last_gps_time){
						continue;
					}
					break;
				}
			}
			if(j == 40*1000/167 + gps_ov){
				pChannel[i] = 0xFF;
			}
			else{
				last_gps_time = pTime[i];
				last_gps_pos = i;
			}
		}
		}
	for(i = 0; i < cnt; i++)
	{
		if(pChannel[i] == 0xFF){
			continue;
		}
		fwrite(&pChannel[i],1,1,fpfixed);
		fwrite(&pTime[i],1,8,fpfixed);
	}
	fclose(fptime);
	fclose(fpfixed);
	free(pTime);
	free(pChannel);
	fpfixed = fopen(recvfixfilepath,"rb");
	while(fread(buf1,1,9,fpfixed)==9)
	{
		time1 = *(__int64*)(buf1 + 1);
		fprintf(fpfixtxt,"%d\t%15I64d\n",buf1[0],time1);
	}
	fclose(fpfixed);
	fclose(fpfixtxt);
	double RMS[6];
	int cnt_recv[6];
	__int64 time_recv[6][10000];
	memset(time_recv, 0, sizeof(__int64)*6*10000);
	memset(cnt_recv,0,sizeof(int)*6);
	fpfixed = fopen(recvfixfilepath,"rb");
	while(fread(buf1,1,9,fpfixed)==9)
	{
		channel = buf1[0];
		time_recv[channel][cnt_recv[channel]] = *(__int64*)(buf1 + 1);
		cnt_recv[channel]++;
		if(cnt_recv[channel]>9999)
		{
			break;
		}
	}
	fclose(fpfixed);//////////时间恢复
	double sum[5], mul[5];
	memset(sum,0,sizeof(double)*5);
	memset(mul,0,sizeof(double)*5);
	double diff;
	char recvrmsfilepath[256];
	strcpy(recvrmsfilepath, writefilepath);
	strcat(recvrmsfilepath,"_rms.txt");
	fp = fopen(recvrmsfilepath,"w");
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < cnt_recv[i] - 1; j ++)
		{
			diff = time_recv[i][j+1] - time_recv[i][j];
			sum[i] += diff;
			mul[i] += diff*diff;
		}
		if(cnt_recv[i] - 1 > 1)
		{
			RMS[i] = sqrt(mul[i]/(cnt_recv[i]-1) - sum[i]*sum[i]/((cnt_recv[i]-1)*(cnt_recv[i]-1)));
			fprintf(fp,"%.2f\n",RMS[i]);
		}
		
		m_RMS.Format(m_RMS+"%.2lf\r\n",RMS[i]); 
	
		UpdateData(FALSE);
	}          //////////////////单通道的rms
	__int64 diff1;
	for(i = 1; i < cnt_recv[1]-1; i++)
	
	{
		diff = double(time_recv[1][i] - time_recv[2][i]);
		sum[0] += diff;
		mul[0] += diff*diff;
		RMS[0] = sqrt(mul[0]/(cnt_recv[1]-1) - sum[0]*sum[0]/((cnt_recv[1]-1)*(cnt_recv[1]-1)));
		
	}
		fprintf(fp,"%.2f\n",RMS[0]);
		m_diff_rms.Format(m_diff_rms + "%.2f\r\n",RMS[0]);
		fclose(fp);/////////////// 42 he 43的rms
		UpdateData(FALSE);


	
}

void CLSB_MFCDlg::OnChangeEditRmsValue() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLSB_MFCDlg::OnChangeEditPrintf() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLSB_MFCDlg::OnChangeEdit_diff_rms() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CLSB_MFCDlg::OnSynApdDiff() 
{
	// TODO: Add your control notification handler code here
	char recvfixfilepath[256];
	strcpy(recvfixfilepath, writefilepath);
	strcat(recvfixfilepath,"_ff_fix.dat");
	char recvsyn_apd_filepath[256];
	strcpy(recvsyn_apd_filepath, writefilepath);
	strcat(recvsyn_apd_filepath,"_ff_syn_apd.txt");
	FILE *fpfixed;
	FILE *fpsyn_apd;
	fpfixed = fopen(recvfixfilepath,"rb");
	fpsyn_apd = fopen(recvsyn_apd_filepath,"w");
int *syn_apd_diff_cnt;
	 	syn_apd_diff_cnt = (int*)malloc(4*100000000);
	 	memset(syn_apd_diff_cnt,0,100000000*4);
	 	__int64 syn_apd_diff;
	 	__int64 last_syn=0;
	 	__int64 *apd;
		unsigned char buffer[9];
		bool first_syn = false;
		while(fread(buffer,1,9,fpfixed)==9)
		{
		
			if(buffer[0]==CHANNEL_SYN)
			{
				last_syn = *(__int64*)(buffer + 1);
				first_syn = true;
				continue;
			}
			if(!first_syn)
			{
				continue;
			}
			if(buffer[0] == 1 || buffer[0] == 2)
			{
				syn_apd_diff = *(__int64*)(buffer + 1) - last_syn;
				if(syn_apd_diff > 99*1000000 || syn_apd_diff < 98*1000000)
				{
					continue;
				}
				syn_apd_diff = syn_apd_diff/100;
				syn_apd_diff_cnt[syn_apd_diff]++;
			}

		}

		int i;
		for(i = 980000; i <990000; i++ )
		{
			fprintf(fpsyn_apd,"%d\t%d\n",i,syn_apd_diff_cnt[i]);
		}
		fclose(fpsyn_apd);
		fclose(fpfixed);
		free(syn_apd_diff_cnt);
		m_edit_syn_apd_diff.Format("%s\r\n\r\n","SYN_APD count finished!");	
		UpdateData(FALSE);
		
		
}
