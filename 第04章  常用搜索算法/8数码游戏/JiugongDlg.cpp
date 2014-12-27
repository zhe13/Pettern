// JiugongDlg.cpp : implementation file

#include "stdafx.h"
#include "Jiugong.h"
#include "JiugongDlg.h"

#include "DialogInput.h"
#include "stdlib.h"
#include "DlgWait.h"
#include "DlgDepth.h"

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
// CJiugongDlg dialog

CJiugongDlg::CJiugongDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJiugongDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJiugongDlg)
	m_stringState = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJiugongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJiugongDlg)
	DDX_Control(pDX, IDC_BUTTON_SHOW, m_bshow);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_bsearch);
	DDX_Control(pDX, IDC_BUTTON_UP, m_bup);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_bright);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_bleft);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_bdown);
	DDX_Text(pDX, IDC_EDIT_STATE, m_stringState);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJiugongDlg, CDialog)
	//{{AFX_MSG_MAP(CJiugongDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_INIT, OnButtonInputInit)
	ON_BN_CLICKED(IDC_BUTTON_INPUT_OBJ, OnButtonInputObj)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, OnButtonShow)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_RADIO_MAC, OnRadioMac)
	ON_BN_CLICKED(IDC_RADIO_MAN, OnRadioMan)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, OnButtonAuto)
	ON_BN_CLICKED(IDC_BUTTON_DEPTH, OnButtonDepth)
	ON_BN_CLICKED(IDC_BUTTON_HUIFU, OnButtonHuifu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJiugongDlg message handlers

BOOL CJiugongDlg::OnInitDialog()
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
	
	CenterWindow();
	// TODO: Add extra initialization here
	CWnd *pWnd0 = (CWnd *)GetDlgItem(IDC_PIC_INIT);
	pDCInit=pWnd0->GetDC();
	CWnd *pWnd1=(CWnd *)GetDlgItem(IDC_PIC_OBJ);
	pDCObj=pWnd1->GetDC();
	CWnd *pWnd2=(CWnd *)GetDlgItem(IDC_PIC_PROCESS);
	pDCCur=pWnd2->GetDC();

	m_bleft.EnableWindow(false);
	m_bup.EnableWindow(false);
	m_bright.EnableWindow(false);
	m_bdown.EnableWindow(false);
	m_bsearch.EnableWindow(false);
	m_bshow.EnableWindow(false);

	m_stringState.Format("请选择\"人工\"或\"机器\"");
	UpdateData(false);

	m_binitdown=false;
	m_bobjdown=false;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJiugongDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJiugongDlg::OnPaint() 
{
	DrawJiuGong(pDCInit,m_jiugong.StateInit.state);
	DrawJiuGong(pDCObj,m_jiugong.StateObj.state);

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
HCURSOR CJiugongDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CJiugongDlg::OnButtonDown() 
{
	// TODO: Add your control notification handler code here
	Beep(1000,50);
	JGState *tempstate;
	tempstate=(JGState *)malloc(sizeof(JGState));
	if(m_nstep==0){
		m_jiugong.CopyJG(&m_jiugong.StateInit,&m_jiugong.StateCur);
		if(m_jiugong.Compare(&m_jiugong.StateCur,&m_jiugong.StateObj)==true){
			m_stringState.Format("起始状态和目标状态相同，不需移动");
			UpdateData(false);
		}
		else{
			if(m_jiugong.MoveDown(&m_jiugong.StateCur,tempstate)==true){
				m_nstep++;
				if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
					m_stringState.Format("您走了第 1 步，已经找到目标状态");
					UpdateData(false);
				}
				else{
					m_stringState.Format("您走了第 1 步，请继续走");
					UpdateData(false);
				}
				m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
			}
			else{
				m_stringState.Format("您已经不能相下移动，请重新走步");
				UpdateData(false);
			}
		}
	}
	else{
		if(m_jiugong.MoveDown(&m_jiugong.StateCur,tempstate)==true){
			m_nstep++;
			if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
				m_stringState.Format("您走了第 %d 步，已经找到目标状态",m_nstep);
				UpdateData(false);
			}
			else{
				m_stringState.Format("您走了第 %d 步，请继续走",m_nstep);
				UpdateData(false);
			}
			m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
		}
		else{
			m_stringState.Format("您已经不能相下移动，请重新走步");
			UpdateData(false);
		}
	}
	DrawJiuGong(pDCCur,(&m_jiugong.StateCur)->state);	
}

void CJiugongDlg::OnButtonInputInit() 
{
	// TODO: Add your control notification handler code here
	CDialogInput inputdlg;
	if(inputdlg.DoModal()==IDOK){
		m_jiugong.StateInit.state[0][0]=inputdlg.m_int00;
		m_jiugong.StateInit.state[0][1]=inputdlg.m_int01;
		m_jiugong.StateInit.state[0][2]=inputdlg.m_int02;
		m_jiugong.StateInit.state[1][0]=inputdlg.m_int10;
		m_jiugong.StateInit.state[1][1]=inputdlg.m_int11;
		m_jiugong.StateInit.state[1][2]=inputdlg.m_int12;
		m_jiugong.StateInit.state[2][0]=inputdlg.m_int20;
		m_jiugong.StateInit.state[2][1]=inputdlg.m_int21;
		m_jiugong.StateInit.state[2][2]=inputdlg.m_int22;
		if(CheckData(m_jiugong.StateInit.state)==false){
			MessageBox("数据不符合规范，\n请重新输入!!!","警告");
			return;
		}
		DrawJiuGong(pDCInit,m_jiugong.StateInit.state);
		DrawJiuGong(pDCCur,m_jiugong.StateInit.state);
		m_nstep=0;
		m_binitdown=true;
		if(m_binitdown==true&&m_bobjdown==true){
			m_bsearch.EnableWindow(true);
			m_bshow.EnableWindow(true);
		}
	}
}

void CJiugongDlg::OnButtonInputObj() 
{
	// TODO: Add your control notification handler code here
	CDialogInput inputdlg;
	if(inputdlg.DoModal()==IDOK){
		m_jiugong.StateObj.state[0][0]=inputdlg.m_int00;
		m_jiugong.StateObj.state[0][1]=inputdlg.m_int01;
		m_jiugong.StateObj.state[0][2]=inputdlg.m_int02;
		m_jiugong.StateObj.state[1][0]=inputdlg.m_int10;
		m_jiugong.StateObj.state[1][1]=inputdlg.m_int11;
		m_jiugong.StateObj.state[1][2]=inputdlg.m_int12;
		m_jiugong.StateObj.state[2][0]=inputdlg.m_int20;
		m_jiugong.StateObj.state[2][1]=inputdlg.m_int21;
		m_jiugong.StateObj.state[2][2]=inputdlg.m_int22;
		if(CheckData(m_jiugong.StateObj.state)==false){
			MessageBox("数据不符合规范，\n请重新输入!!!","警告");
			return;
		}
		DrawJiuGong(pDCObj,m_jiugong.StateObj.state);
		m_nstep=0;
		m_bobjdown=true;
		if(m_binitdown==true&&m_bobjdown==true){
			m_bsearch.EnableWindow(true);
			m_bshow.EnableWindow(true);
		}
	}
}

void CJiugongDlg::OnButtonLeft() 
{
	// TODO: Add your control notification handler code here
	Beep(1000,50);
	JGState *tempstate;
	tempstate=(JGState *)malloc(sizeof(JGState));
	if(m_nstep==0){
		m_jiugong.CopyJG(&m_jiugong.StateInit,&m_jiugong.StateCur);
		if(m_jiugong.Compare(&m_jiugong.StateCur,&m_jiugong.StateObj)==true){
			m_stringState.Format("起始状态和目标状态相同，不需移动");
			UpdateData(false);
		}
		else{
			if(m_jiugong.MoveLeft(&m_jiugong.StateCur,tempstate)==true){			
				m_nstep++;
				if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
					m_stringState.Format("您走了第 1 步，已经找到目标状态");
					UpdateData(false);
				}
				else{
					m_stringState.Format("您走了第 1 步，请继续走");
					UpdateData(false);
				}
				m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
			}
			else{
				m_stringState.Format("您已经不能相左移动，请重新走步");
				UpdateData(false);
			}
		}
	}
	else{
		if(m_jiugong.MoveLeft(&m_jiugong.StateCur,tempstate)==true){
			m_nstep++;
			if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
				m_stringState.Format("您走了第 %d 步，已经找到目标状态",m_nstep);
				UpdateData(false);
			}
			else{
				m_stringState.Format("您走了第 %d 步，请继续走",m_nstep);
				UpdateData(false);
			}
			m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
		}
		else{
			m_stringState.Format("您已经不能相左移动，请重新走步");
			UpdateData(false);
		}
	}
	DrawJiuGong(pDCCur,(&m_jiugong.StateCur)->state);
}

void CJiugongDlg::OnButtonRight() 
{
	// TODO: Add your control notification handler code here
	Beep(1000,50);
	JGState *tempstate;
	tempstate=(JGState *)malloc(sizeof(JGState));
	if(m_nstep==0){
		m_jiugong.CopyJG(&m_jiugong.StateInit,&m_jiugong.StateCur);
		if(m_jiugong.Compare(&m_jiugong.StateCur,&m_jiugong.StateObj)==true){
			m_stringState.Format("起始状态和目标状态相同，不需移动");
			UpdateData(false);
		}
		else{
			if(m_jiugong.MoveRight(&m_jiugong.StateCur,tempstate)==true){
				m_nstep++;
				if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
					m_stringState.Format("您走了第 1 步，已经找到目标状态");
					UpdateData(false);
				}
				else{
					m_stringState.Format("您走了第 1 步，请继续走");
					UpdateData(false);
				}
				m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
			}
			else{
				m_stringState.Format("您已经不能相右移动，请重新走步");
				UpdateData(false);
			}
		}
	}
	else{
		if(m_jiugong.MoveRight(&m_jiugong.StateCur,tempstate)==true){
			m_nstep++;
			if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
				m_stringState.Format("您走了第 %d 步，已经找到目标状态",m_nstep);
				UpdateData(false);
			}
			else{
				m_stringState.Format("您走了第 %d 步，请继续走",m_nstep);
				UpdateData(false);
			}
			m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
		}
		else{
			m_stringState.Format("您已经不能相右移动，请重新走步");
			UpdateData(false);
		}
	}
	DrawJiuGong(pDCCur,(&m_jiugong.StateCur)->state);
}

void CJiugongDlg::OnButtonSearch() 
{
	if(m_binitdown==false||m_bobjdown==false){
		MessageBox("初始状态或者目标状态没有输入!!!","错误警告");
		m_bsearch.EnableWindow(false);
		m_bshow.EnableWindow(false);
		return;
	}

	m_stringState.Format("搜索中，请耐心等待......");
	UpdateData(false);
	CDlgWait dlgwait;
	dlgwait.Create(IDD_DIALOG_WAIT);
	dlgwait.ShowWindow(SW_SHOW);
	dlgwait.CenterWindow();
	dlgwait.BeginWaitCursor();
	dlgwait.UpdateWindow();

	if(m_jiugong.ComputeJO(&(m_jiugong.StateInit))!=m_jiugong.ComputeJO(&(m_jiugong.StateObj))){
		m_stringState.Format("很抱歉，两个状态之间不可达，请重新输入");
		UpdateData(false);
		MessageBox("两个状态之间不可达，\n请重新输入!!!","提示");
		return;
	}

	if(m_jiugong.Search()==true){
		m_stringState.Format("搜索成功，总共需要走 %d 步",m_jiugong.ResultList.GetCount()-1);
		UpdateData(false);
	}
	else{
		m_stringState.Format("因为某些原因，搜索失败，请重新输入");
		UpdateData(false);
	}

	m_nstep=0;
	dlgwait.DestroyWindow();
}

void CJiugongDlg::OnButtonShow() 
{
	if(m_binitdown==false||m_bobjdown==false){
		MessageBox("初始状态或者目标状态没有输入!!!","错误警告");
		m_bsearch.EnableWindow(false);
		m_bshow.EnableWindow(false);
		return;
	}

	if(m_nstep==0&&m_jiugong.ResultList.IsEmpty()==false){
		DrawJiuGong(pDCCur,((JGState *)(m_jiugong.ResultList.GetHead()))->state);
		m_stringState.Format("总共需要走 %d 步,当前是起始状态",m_jiugong.ResultList.GetCount()-1);
		UpdateData(false);
		m_nstep++;
	}
	else if(m_nstep<(m_jiugong.ResultList.GetCount()-1)){
		POSITION tempindex;
		tempindex=m_jiugong.ResultList.FindIndex(m_nstep);
		DrawJiuGong(pDCCur,((JGState *)(m_jiugong.ResultList.GetAt(tempindex)))->state);
		m_stringState.Format("总共需要走 %d 步,当前是第 %d 步",m_jiugong.ResultList.GetCount()-1,m_nstep);
		UpdateData(false);
		m_nstep++;
		Beep(1000,50);
	}
	else{
		m_stringState.Format("总共需要走 %d 步,已经走到目标状态",m_jiugong.ResultList.GetCount()-1);
		UpdateData(false);
		DrawJiuGong(pDCCur,((JGState *)(m_jiugong.ResultList.GetTail()))->state);
		Beep(1000,50);
	}
}

void CJiugongDlg::OnButtonUp() 
{
	// TODO: Add your control notification handler code here
	Beep(1000,50);
	JGState *tempstate;
	tempstate=(JGState *)malloc(sizeof(JGState));
	if(m_nstep==0){
		m_jiugong.CopyJG(&m_jiugong.StateInit,&m_jiugong.StateCur);
		if(m_jiugong.Compare(&m_jiugong.StateCur,&m_jiugong.StateObj)==true){
			m_stringState.Format("起始状态和目标状态相同，不需移动");
			UpdateData(false);
		}
		else{
			if(m_jiugong.MoveUp(&m_jiugong.StateCur,tempstate)==true){
				m_nstep++;
				if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
					m_stringState.Format("您走了第 1 步，已经找到目标状态");
					UpdateData(false);
				}
				else{
					m_stringState.Format("您走了第 1 步，请继续走");
					UpdateData(false);
				}
				m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
			}
			else{
				m_stringState.Format("您已经不能相上移动，请重新走步");
				UpdateData(false);
			}
		}
	}
	else{
		if(m_jiugong.MoveUp(&m_jiugong.StateCur,tempstate)==true){
			m_nstep++;
			if(m_jiugong.Compare(tempstate,&m_jiugong.StateObj)==true){
				m_stringState.Format("您走了第 %d 步，已经找到目标状态",m_nstep);
				UpdateData(false);
			}
			else{
				m_stringState.Format("您走了第 %d 步，请继续走",m_nstep);
				UpdateData(false);
			}
			m_jiugong.CopyJG(tempstate,&m_jiugong.StateCur);
		}
		else{
			m_stringState.Format("您已经不能相上移动，请重新走步");
			UpdateData(false);
		}
	}
	DrawJiuGong(pDCCur,(&m_jiugong.StateCur)->state);	
}

void CJiugongDlg::OnRadioMac() 
{
	// TODO: Add your control notification handler code here
	m_bleft.EnableWindow(false);
	m_bup.EnableWindow(false);
	m_bright.EnableWindow(false);
	m_bdown.EnableWindow(false);
	m_bsearch.EnableWindow();
	m_bshow.EnableWindow();
	m_stringState.Format("当前选择的是机器搜索状态");
	UpdateData(false);
	m_nstep=0;
	DrawJiuGong(pDCCur,m_jiugong.StateInit.state);
}

void CJiugongDlg::OnRadioMan() 
{
	// TODO: Add your control notification handler code here
	m_bleft.EnableWindow();
	m_bup.EnableWindow();
	m_bright.EnableWindow();
	m_bdown.EnableWindow();
	m_bsearch.EnableWindow(false);
	m_bshow.EnableWindow(false);
	m_stringState.Format("当前选择的是人工游戏状态");
	UpdateData(false);
	m_nstep=0;
	DrawJiuGong(pDCCur,m_jiugong.StateInit.state);
}

///////////////////////////////////////////////////////////////////////
//画九宫图
void CJiugongDlg::DrawJiuGong(CDC *pDC,int state[3][3])
{
	//To Draw the JiuGong
	CBitmap bitmap[9];
    CDC dcMemory;
	CRect rc;
	int width;
	int height;
    bitmap[0].LoadBitmap(IDB_BITMAP_NULL);
	bitmap[1].LoadBitmap(IDB_BITMAP1);
	bitmap[2].LoadBitmap(IDB_BITMAP2);
	bitmap[3].LoadBitmap(IDB_BITMAP3);
	bitmap[4].LoadBitmap(IDB_BITMAP4);
	bitmap[5].LoadBitmap(IDB_BITMAP5);
	bitmap[6].LoadBitmap(IDB_BITMAP6);
	bitmap[7].LoadBitmap(IDB_BITMAP7);
	bitmap[8].LoadBitmap(IDB_BITMAP8);
    dcMemory.CreateCompatibleDC(pDC);
	
	pDC->GetWindow()->GetWindowRect(&rc);
	width = rc.Width();
	height = rc.Height();
  	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(state[i][j]>=0&&state[i][j]<9){
				dcMemory.SelectObject(&bitmap[state[i][j]]);
				pDC->BitBlt((j*2+1)*width/6-8,(i*2+1)*height/6-8,16,16,&dcMemory,0,0,SRCCOPY);
			}//end if
		}//end for
	}//end for
}

///////////////////////////////////////////////////////////////////
//检查数据的有效性
bool CJiugongDlg::CheckData(int state[3][3])
{
	int count[9];
	int i,j;
	for(i=0;i<9;i++){
		count[i]=0;
	}

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(state[i][j]<0||state[i][j]>8)
				return false;
			count[state[i][j]]++;
		}
	}

	for(i=0;i<9;i++){
		if(count[i]==0)
			return false;
	}

	return true;
}


void CJiugongDlg::OnButtonAuto() 
{
	// TODO: Add your control notification handler code here
	if(m_binitdown==false||m_bobjdown==false){
		MessageBox("初始状态或者目标状态没有输入!!!","错误警告");
		m_bsearch.EnableWindow(false);
		m_bshow.EnableWindow(false);
		return;
	}
	m_bleft.EnableWindow(false);
	m_bup.EnableWindow(false);
	m_bright.EnableWindow(false);
	m_bdown.EnableWindow(false);
	m_bsearch.EnableWindow(false);
	m_bshow.EnableWindow(false);
	m_nstep=0;
	if(m_jiugong.ResultList.GetCount()==0){
		MessageBox("无解或还没有搜索","警告");
	}

	for(int i=0;i<=m_jiugong.ResultList.GetCount();i++){
		OnButtonShow();
		Sleep(1000);
	}
	
	m_bsearch.EnableWindow();
	m_bshow.EnableWindow();
}

void CJiugongDlg::OnButtonDepth() 
{
	// TODO: Add your control notification handler code here
	CDlgDepth depthdlg;
	if(depthdlg.DoModal()==IDOK){
		if(depthdlg.m_depth<25||depthdlg.m_depth>200){
			MessageBox("深度太大或太小!!!","警告");
			return;
		}
		else
			m_jiugong.m_ndepth=depthdlg.m_depth;
	}
}

void CJiugongDlg::OnButtonHuifu() 
{
	// TODO: Add your control notification handler code here
	DrawJiuGong(pDCInit,m_jiugong.StateInit.state);
	DrawJiuGong(pDCObj,m_jiugong.StateObj.state);
}
