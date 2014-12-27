/* ============================================= *\
 * File:		OnrDlg.cpp						 *
 * Description: 主对话框头文件                   *
 *				包括所有的函数                   *
\* ============================================= */

#include "stdafx.h"
#include "Onr.h"
#include "OnrDlg.h"

#include <fstream.h>
#include <time.h>
#include <stdlib.h>

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
	virtual BOOL OnInitDialog();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// COnrDlg dialog

COnrDlg::COnrDlg(CWnd* pParent) : CDialog(COnrDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(COnrDlg)
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COnrDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COnrDlg)
	DDX_Control(pDX, IDC_TRAINSPIN, m_Trainspin);
	DDX_Control(pDX, IDC_TESTSPIN, m_Testspin);
	DDX_Control(pDX, IDC_TRAININFO, m_TrainInfo);
	DDX_Control(pDX, IDC_INFOBOX, m_cInfoBox);
	DDX_Control(pDX, IDC_TESTWINDOW, m_TestWindow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COnrDlg, CDialog)
	//{{AFX_MSG_MAP(COnrDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TRAIN, OnTrain)
	ON_BN_CLICKED(IDC_CLASSIFY, OnClassify)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRAINSPIN, OnDeltaposTrainspin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TESTSPIN, OnDeltaposTestspin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// 初始化对话框
BOOL COnrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon((HICON)(LoadImage(AfxGetResourceHandle(), 
		MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, 0)), FALSE);

	// 设置滚动条的范围
	m_Testspin.SetRange(0,NN_NUMBERS-1);
	m_Trainspin.SetRange(0,NN_NUMBERS-1);
	m_Testspin.SetPos(0);
	m_Trainspin.SetPos(0);
	
	// 打开文件
	ifstream data("learn.dat", ios::nocreate);
	ifstream test("test.dat", ios::nocreate);

	// 检查文件的有效性
	if (!test || !data) 
	{
		MessageBox("No learning or test data present.", "Cannot run...",
			MB_OK | MB_ICONERROR);
	}

	// 读文件
	for(int i=0;i<NN_NUMBERS;i++) 
	{
		for(int j=0;j<NN_RESX * NN_RESY;j++) 
		{
			int onoff;
			test >> onoff;
			m_bTestData[i][j] = onoff;

			data >> onoff;
			m_bNumbers[i][j] = onoff;
		}
	}

	// 设置初始要画的数字指针
	m_ipDrawNum = &m_bNumbers[0][0];

	return true;
}

void COnrDlg::OnSysCommand(UINT nID, LPARAM lParam) {
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

void COnrDlg::OnPaint() 
{
	if (IsIconic())	{
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
	} else {
		CPaintDC dc(this);
		CDialog::OnPaint();

		// 这种方法画矩形可能有点迂回，不过的确可以工作
		CRect rect;

		m_TestWindow.GetClientRect(&rect);
		m_TestWindow.ClientToScreen(&rect);
		ScreenToClient(&rect);
		dc.FrameRect(&rect, &CBrush(RGB(0,0,0)));
		rect.DeflateRect(1,1);
		dc.FillSolidRect(rect, RGB(255,255,255));

		// 画数字
		DrawNumber(&dc, m_ipDrawNum, &rect);
	}
}

HCURSOR COnrDlg::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}

///////////////////////////////////////////////////////////
// 由于某些原因，如果采用"Maxinum Speed"优化将引起程序运行的
// 失败，所以先关掉优化，在该段代码结束后再打开优化功能
///////////////////////////////////////////////////////////

#pragma optimize( "", off )

//////////////////////////////////////////////////////////////////////////
//  训练数据
void COnrDlg::OnTrain() 
{
	srand((unsigned)time(NULL));			// 设置随机数
	m_cInfoBox.ResetContent();
	
	// 所有权值0初始化
	memset(&m_fWeights,0,sizeof(m_fWeights));

	// 产生一些带有随机噪声的训练数据
	m_cInfoBox.InsertString(-1, "Generating noisy data...");
	int num = 0;
	for (int i=0;i<NN_NUMBERS * NN_NOISY;i++) 
	{
		for(int j=0;j<NN_RESX * NN_RESY;j++) 
		{
			if (rand() % 100 < 7) 
			{
				m_iNoisy[i][j] = !m_bNumbers[num][j];
			} 
			else 
				m_iNoisy[i][j] = m_bNumbers[num][j];
		}
		
		if ((float)(i+1)/NN_NOISY == (i+1)/NN_NOISY && i != 0) 
			num++;
	}

	m_cInfoBox.InsertString(-1, "Learning...");

	RunNet(true);

	m_TrainInfo.SetWindowText("Complete...");
	m_cInfoBox.InsertString(-1,"Training Complete!");
	GetDlgItem(IDC_CLASSIFY)->EnableWindow(true);
}

///////////////////////////////////////////////////////////////////////////
// 画数字
void COnrDlg::DrawNumber(CDC *dc, int *cell, CRect *rect) 
{
	// 下面的计算主要是使得数字画在矩形筐的正中央
	CPoint tl;
	tl.x = rect->Width()/2 - (NN_RESX*10)/2;
	tl.y = rect->Height()/2 - (NN_RESY*10)/2;

	tl.Offset(rect->TopLeft());
	int ix = tl.x;
	
	// 产生一些围绕数字的红色虚线
	CPen pen;
	if (pen.CreatePen(PS_DOT, 1, RGB(127,0,0))) 
	{
		CPen *pOldPen = dc->SelectObject(&pen);

		CPoint pt1 = rect->TopLeft();
		CPoint pt2 = rect->BottomRight();
		dc->MoveTo(tl.x-5, tl.y-2);
		dc->LineTo(tl.x+NN_RESX*10+5, tl.y-2);
		dc->MoveTo(tl.x-5, tl.y+10*NN_RESY+1);
		dc->LineTo(tl.x+NN_RESX*10+5, tl.y+10*NN_RESY+1);
		dc->MoveTo(tl.x-2, tl.y-7);
		dc->LineTo(tl.x-2, tl.y+NN_RESY*10+7);
		dc->MoveTo(tl.x+NN_RESX*10+2, tl.y-7);
		dc->LineTo(tl.x+NN_RESX*10+2, tl.y+NN_RESY*10+7);

		dc->SelectObject(pOldPen);
	}

	// 显示一些文本
	CRect format(tl.x+1, tl.y+NN_RESY*10+2,
				 tl.x+NN_RESX*10-1, tl.y+NN_RESY*10+18);
	if (m_bDisplayString) 
	{
		CFont fnt;
		if (fnt.CreatePointFont(80,"Arial")) 
		{
			CFont* pOldFont = dc->SelectObject(&fnt);

			dc->SetTextColor(RGB(0,0,127));
			dc->DrawText(m_Str,format,DT_CENTER);
			dc->SelectObject(pOldFont);
		}	
	}

	// 画数字
	for(int i=0;i<NN_RESX*NN_RESY;i++) 
	{
		if ((*cell) == 1) 
		{
			dc->FillSolidRect(tl.x,tl.y,10,10,RGB(0,0,0));
		}
		tl.x += 10;
		if (tl.x == ix + 10*NN_RESX) 
		{
			tl.x = ix;
			tl.y += 10;
		}
		cell++;
	}
}

//////////////////////////////////////////////////////////////////////////////////
// 识别
void COnrDlg::OnClassify() 
{
	int pos = (BYTE)m_Testspin.GetPos();
	
	m_ipDrawNum = &m_bTestData[pos][0];
	InvalidateNumber();

	float d[NN_NUMBERS];
	for(int j=0;j<NN_NUMBERS;j++) 
	{
		d[j] = 0;
		for(int k=0;k<NN_RESX * NN_RESY;k++) 
		{
			d[j] += m_fWeights[j][k]*m_bTestData[pos][k];
		}
	}
	
	int bestind = 0;
	for(j=1;j<NN_NUMBERS;j++) 
		if (d[j] > d[bestind]) 
			bestind = j;

	// 计算画文本的区域
	CRect size;
	m_TestWindow.GetClientRect(&size);
	int x = size.Width()/2  - (NN_RESX*10)/2;
	int y = size.Height()/2 - (NN_RESY*10)/2;
	CRect format(x,size.Height()-y+1, size.Width()-x, size.Height()-5);
	
	m_bDisplayString = true;
	GetText(m_Str, bestind+1);
}

/////////////////////////////////////////////////////////////////////////////
// 运行网络
// 参数：training－为真时表示网络出于训练状态
void COnrDlg::RunNet(bool training) 
{
	// 检测带有噪声的数据
	float d[NN_NUMBERS];
	int cycles = 0;//初始化循环次数为0
	bool correct;

	do 
	{
		correct = true;
		for(int i=0;i<NN_NUMBERS * NN_NOISY;i++) 
		{
			for(int j=0;j<NN_NUMBERS;j++) 
			{
				d[j] = 0;
				for(int k=0;k<NN_RESX * NN_RESY;k++) 
				{
					d[j] += m_fWeights[j][k]*m_iNoisy[i][k];
				}
			}
			
			int bestind = 0;
			for(j=1;j<NN_NUMBERS;j++) 
				if (d[j] > d[bestind]) 
					bestind = j;
			
			int realval = (int)(i/NN_NOISY);
			if (bestind == realval) continue;
			
			if (training) 
			{
				CString result;
				result.Format("Guessed %d instead of %d.",bestind, realval);
				m_TrainInfo.SetWindowText(result);
				correct = false;
				
				for(j=0;j<NN_RESX * NN_RESY;j++) 
				{
					m_fWeights[bestind][j] -= m_iNoisy[i][j];
					m_fWeights[realval][j] += m_iNoisy[i][j];
				}
			}
		}
		
		SetDlgItemInt(IDC_ITERATE, ++cycles);
	} while (!correct && cycles <= NN_MAXITER);
	
	//如果循环次数太大还每得到结果则退出
	if (cycles >= NN_MAXITER) 
	{
		MessageBox("Training has timed-out.",
			"Error in Training", MB_OK | MB_ICONINFORMATION);
		return;
	}
}

//恢复系统优化
#pragma optimize( "", on )

////////////////////////////////////////////////////////////////////////
// 处理训练数据的滚动条
void COnrDlg::OnDeltaposTrainspin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int iPos = pNMUpDown->iPos;
	int iDelta = pNMUpDown->iDelta;
	
	m_bDisplayString = false;

	if ((iPos == 0 && iDelta == -1) || (iPos == NN_NUMBERS-1 && iDelta == 1)) 
	{
		if (iDelta == -1) 
		{
			m_ipDrawNum = &m_bNumbers[0][0];
			InvalidateNumber();
		} 
		else 
		{
			m_ipDrawNum = &m_bNumbers[NN_NUMBERS-1][0];
			InvalidateNumber();
		}
	} 
	else 
	{
		m_ipDrawNum = &m_bNumbers[iPos+iDelta][0];
		InvalidateNumber();
	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////////
// 处理测试数据的滚动条
void COnrDlg::OnDeltaposTestspin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int iPos = pNMUpDown->iPos;
	int iDelta = pNMUpDown->iDelta;

	m_bDisplayString = false;

	if ((iPos == 0 && iDelta == -1) || (iPos == NN_NUMBERS-1 && iDelta == 1)) 
	{
		if (iDelta == -1) 
		{
			m_ipDrawNum = &m_bTestData[0][0];
			InvalidateNumber();
		} 
		else 
		{
			m_ipDrawNum = &m_bTestData[NN_NUMBERS-1][0];
			InvalidateNumber();
		}
	} 
	else 
	{
		m_ipDrawNum = &m_bTestData[iPos+iDelta][0];
		InvalidateNumber();
	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////
// 得到数字相对应的文本
void COnrDlg::GetText(CString &str, int num) {
	switch (num) {
	case 1:
		str = "Result:1"; 
		break;
	case 2:
		str = "Result:2"; 
		break;
	case 3:
		str = "Result:3"; 
		break;
	case 4:
		str = "Result:4"; 
		break;
	case 5:
		str = "Result:5"; 
		break;
	case 6:
		str = "Result:6"; 
		break;
	case 7:
		str = "Result:7"; 
		break;
	case 8:
		str = "Result:8"; 
		break;
	case 9:
		str = "Result:9"; 
		break;
	default:
		str = "Undetermined";
	}
}

///////////////////////////////////////////////////////////////////////////////
// 强制重画
void COnrDlg::InvalidateNumber() 
{
	CRect rect;
	
	m_TestWindow.GetClientRect(&rect);
	m_TestWindow.ClientToScreen(&rect);
	ScreenToClient(&rect);

	InvalidateRect(rect, false);
}
