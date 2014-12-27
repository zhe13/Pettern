// patternDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pattern.h"
#include "patternDlg.h"
#include "Afxwin.h"
#include "Afxdlgs.h"
#include "winuser.h"
#include "Store.h"
 #include <stdio.h>
//#define   _MBCS

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include<windows.h>
#include<math.h>

#define Startx 30
#define Starty 190
#define wid  192
#define lon 192
#define yu 3 //2 area
#define yu1 5 //dou dong

#define yu2  4 
int num,Time;

int xmax,ymax,xmin,ymin; //随时纪录书写过程中的书写范围

//存储书写笔迹的坐标序列，按笔划存储，每个笔划最多300个点
//每个字最多15个笔划
struct 
{
	int x;
	int y;
}store[15][300];

//备份的序列
struct 
{
	int x;
	int y;
}storeback[15][300];

struct
{	
	int total;//总的笔划数
	char zifu[2];//代表字符
	int dian[15];//每个笔划的点数
	struct{
		int relate;//相对前点特征
		int region;//全局位置特征
		int arc;//过渡带特征
	}detail[15][20];//15个笔划上的特征点，每个笔划20个特征点
}tez[2002];

struct
{
	int total;
	int dian[15];
	struct
	{
		int relate;
		int region;
		int arc;
	}detail[15][20];
}test;//意义同上，为测试点的结构

int queue[50];
int  queue1[40];
int zong;

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
// CPatternDlg dialog

CPatternDlg::CPatternDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPatternDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPatternDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPatternDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatternDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_BUTTON4, m_escape);
	DDX_Control(pDX, IDC_BUTTON3, m_clear);
	DDX_Control(pDX, IDC_BUTTON1, m_recog);
	DDX_Control(pDX, IDC_BUTTON2, m_study);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPatternDlg, CDialog)
	//{{AFX_MSG_MAP(CPatternDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, OnEsp)
	ON_BN_CLICKED(IDC_BUTTON1, OnRecog)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON3, OnClear)
	ON_BN_CLICKED(IDC_BUTTON2, OnStudy)
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EXIT_MENU, OnExitMenu)
	ON_COMMAND(ID_ABOUT_MENU, OnAboutMenu)
	ON_COMMAND(ID_SAVE_MENU, OnSaveMenu1)
	ON_COMMAND(ID_OPEN_MENU, OnOpenMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatternDlg message handlers

BOOL CPatternDlg::OnInitDialog()
{
	CFile cf;
	
	CDialog::OnInitDialog();

	mouseDown=0;
	
	int i,j,k;

	//将每个笔划上坐标初始化为空
	for(i=0;i<15;i++)
	{
		for(j=0;j<300;j++)
		{
			store[i][j].x=-1;
			store[i][j].y=-1;
		}
	}

	for(i=0;i<15;i++)
	{
		for(j=0;j<300;j++)
		{
			storeback[i][j].x=-1;
			storeback[i][j].y=-1;
		}
	}

	for(i=0;i<10;i++)
	{
		tez[i].total=-1;

		for(j=0;j<15;j++) 
			tez[i].dian[j]=-1;

		for(j=0;j<15;j++)
		{
			for(k=0;k<20;k++)
			{
				tez[i].detail[j][k].relate=0;
				tez[i].detail[j][k].arc=0;
				tez[i].detail[j][k].region=0;
			}
		}
	}

	Time=0;
	num=0;
	zong=-1;//tez下标
	xmax=0;
	ymax=0;
	xmin=31;
	ymin=31;

	for(i=0;i<50;i++)
		queue[i]=-1;
	for(i=0;i<40;i++)
		queue1[i]=-1;

	test.total=-1;
	for(j=0;j<15;j++) 
		test.dian[j]=-1;

	for(j=0;j<15;j++)
	{
		for(k=0;k<20;k++)
		{
			test.detail[j][k].relate=0;
			test.detail[j][k].arc=0;
			test.detail[j][k].region=0;
		}
	}

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
	if(cf.Open("mydata.dat",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite)==NULL){
		AfxMessageBox("打开文件失败，\n您最好退出程序");}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPatternDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPatternDlg::OnPaint() 
{
	CPaintDC dc(this); 
	HBRUSH hB;
	hB=CreateSolidBrush(RGB(255,255,255));
	SelectObject(dc,hB);
	Rectangle(dc,Startx,Starty,Startx+wid-1,Starty+lon-1);
	DeleteObject(hB);

	if (IsIconic())
	{
		// device context for painting
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
HCURSOR CPatternDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPatternDlg::OnEsp() 
{
	OnOK();	
}

//识别函数
void CPatternDlg::OnRecog() 
{  
	int j1,k1,m1,n1,x,y,xmod,ymod;//xmod,ymod;
	int  flagok2=0;
	char s[20];
	DealData();

	//安次序检验,有点下标数
	for(j1=0;j1<=zong&&test.total>=0&&flagok2==0;j1++)
	{   	   
		if(tez[j1].total==test.total)       //如果总条数相等
		{      	
			for(k1=0;k1<=test.total;k1++)           
			{  
				if(test.dian[k1]!=tez[j1].dian[k1])  
					break;
			}
                  
			if(k1>test.total)   
			//每条得点数相同
			{   
				for(m1=0;m1<=test.total;m1++)           //每条
				{     
					for(n1=0;n1<=test.dian[m1];n1++)        //每点
					{
						xmod=2*(tez[j1].detail[m1][n1].region % 8);  //8等分
						ymod=2*((int)tez[j1].detail[m1][n1].region/8);
						x=test.detail[m1][n1].region % 16;
						y=(int)test.detail[m1][n1].region/16;    //   5/16					  										  
					  
						if(( test.detail[m1][n1].relate!=tez[j1].detail[m1][n1].relate
							&&(test.detail[m1][n1].relate-10*(int)(test.detail[m1][n1].relate/10))!=tez[j1].detail[m1][n1].relate
							&&(int)(test.detail[m1][n1].relate/10)!=tez[j1].detail[m1][n1].relate)
							||((tez[j1].detail[m1][n1].arc!=test.detail[m1][n1].arc)&&(test.total<4)&&(test.dian[m1]<4))
							||((x<xmod-3||x>xmod+3)||(y<ymod-3||y>ymod+3)))//shi为total+1
							break;
					}
					if(n1<=test.dian[m1])  
						break;	
				}
				if(m1>test.total)
				{
					flagok2=1;
					sprintf(s,"输入正确，可识别，为：%s, 在字库%d个",tez[j1].zifu,j1);
					AfxMessageBox(s);
					m_edit1.ReplaceSel(tez[j1].zifu); 
					OnClear();
				}
			}
		}
	}				 							 
	   
	if(flagok2==0)
	{ 
		AfxMessageBox("字库不足或输入不规范，无法识别，请学习");
		OnRecogch();
	}
}   
 
//学习函数  
void CPatternDlg::OnStudy() 
{     
	int j1,k1,m1,n1,k,m,xmod,ymod,x,y;//j1代表字典中的一个字,k 表示笔划,m 表示一个点
	CString z1;
	int i,j;
	int flagok1=0; //o无法识别，1可识别,已经识别出结果
	char s[30];
	Inputdialog inputdlg;

	//处理数据
    DealData();

	if(test.total==-1)
	{
		AfxMessageBox("没有笔迹输入，\n请重示");
	}

	for(j1=0;j1<=zong&&test.total!=-1;j1++)
	{    
		if(flagok1==1) 
			break;

		if(tez[j1].total==test.total&&flagok1==0)      //总笔划相等
		{      
			for(k1=0;k1<=test.total;k1++)
			{
				if(test.dian[k1]!=tez[j1].dian[k1])  
					break;
			}

			if(k1>test.total)      //每笔划点数相同下
			{  
				for(m1=0;m1<=test.total;m1++)
				{
					for(n1=0;n1<=test.dian[m1];n1++)
					{
						if(( test.detail[m1][n1].relate!=tez[j1].detail[m1][n1].relate
							&&(test.detail[m1][n1].relate % 10)!=tez[j1].detail[m1][n1].relate
							&&((int)(test.detail[m1][n1].relate/10))!=tez[j1].detail[m1][n1].relate)
							||(tez[j1].detail[m1][n1].arc!=test.detail[m1][n1].arc))//shi为total+1
							break;
						xmod=2*(tez[j1].detail[m1][n1].region % 8);  //8等分
						ymod=2*((int)tez[j1].detail[m1][n1].region/8);
						x=test.detail[m1][n1].region % 16;
						y=(int)test.detail[m1][n1].region/16;
						if((x<xmod-1||x>xmod+1)||(y<ymod-1||y>ymod+1))
							break;      //3/16
					}         //对一个笔划的判断,tezheng不等，跳出n
					if(n1<=test.dian[m1])  
						break;	//ci bihua不等，跳出m循环
				}

				if(m1>test.total&&k1>test.total)//当前库字与输入相符合
				{
					flagok1=1;
				    
					sprintf(s,"您输入的是：%s，数据已有",tez[j1].zifu); 
   					AfxMessageBox(s);
					m_edit1.ReplaceSel(tez[j1].zifu);
					OnClear();
				}
			}
		}
	}
    
	if(flagok1==0&&test.total>=0&&inputdlg.DoModal()==IDOK) //shuruzifu
	{	
		if(inputdlg.m_input1!=inputdlg.m_input2
			||inputdlg.m_input1==""||inputdlg.m_input1==" ")
		{
			AfxMessageBox("您的输入有误(不等或空格），\n请重新输入");
			for(i=0;i<50;i++)
				queue[i]=-1;
			for(i=0;i<40;i++)
				queue1[i]=-1;

			test.total=-1;
			for(j=0;j<15;j++) 
    			test.dian[j]=-1;

			for(j=0;j<15;j++)
			{
				for(k=0;k<20;k++)
				{
					test.detail[j][k].relate=0;
					test.detail[j][k].region=0;
				}
			}
		}
		else
		{
			zong++; 
			sprintf(tez[zong].zifu,"%s",inputdlg.m_input1);
			tez[zong].total=test.total;

			for(i=0;i<=test.total;i++)
			{
				tez[zong].dian[i]=test.dian[i];
				for(j=0;j<=test.dian[i];j++)
				{
					tez[zong].detail[i][j].relate=(test.detail[i][j].relate % 10);
					tez[zong].detail[i][j].arc=test.detail[i][j].arc;

			   		x=(int)(test.detail[i][j].region % 16)/2;
					y=(int)(test.detail[i][j].region/16)/2;
					tez[zong].detail[i][j].region=8*y+x;
				}
			}
			OnSaveMenu();
	
			if(zong>=2000) 
				AfxMessageBox("版本太低，容量受限，Sorry！");

			m_edit1.ReplaceSel(inputdlg.m_input1);
			OnClear();
		}//zong dang前库下标
	}
}

void CPatternDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	mouseDown=1;
	CWnd::OnLButtonDown(nFlags, point);
}

//鼠标左键抬起
void CPatternDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	mouseDown=0;

	if(store[num][Time-1].x>=0&&Time>0)
	{
		num++;
		Time=0;
	}
	if(num>=14) 
	{
		AfxMessageBox("写入有误（笔划太多）",NULL,NULL);
		OnClear();
	}

	CWnd::OnLButtonUp(nFlags, point);
}

//鼠标移动事件，模拟手写笔输入
void CPatternDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int x,y;
	CBrush Brush (RGB (0, 0 , 255) );
	CBrush* pOldBrush;
	CDC *pDC=GetDC();
	CRgn Rgn;
	Rgn.CreateRectRgn(Startx,Starty,Startx+wid-1,Starty+lon-1);
	pDC->SelectClipRgn(&Rgn);

	if((point.x>=Startx)&&(point.x<Startx+wid)&&(point.y>=Starty)
		&&(point.y<Starty+lon))
	{
		HCURSOR m_HCross;
		m_HCross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);
		SetCursor(m_HCross);
	}

	if((mouseDown==1)&&(point.x>=Startx)&&(point.x<Startx+wid)
		&&(point.y>=Starty)&&(point.y<Starty+lon))
	{
		// Select the brush into the device context .
		CBrush* pOldBrush = pDC->SelectObject (&Brush);
		pDC->Ellipse(point.x-4,point.y-4,point.x+4,point.y+4);
		pDC->SelectObject (pOldBrush );
		x=(int)(point.x-Startx)*32/wid;
		y= (int)(point.y-Starty)*32/lon;
		
		if(Time==0)
		{ 
			store[num][Time].x=x;
			store[num][Time].y=y;
			Time++;
			if(y>ymax) 
				ymax=y;
			if(y<ymin) 
				ymin=y;
			if(x>xmax) 
				xmax=x;
			if(x<xmin) 
				xmin=x;
		}
		               
		else
		{ 
			if(x!=store[num][Time-1].x||y!=store[num][Time-1].y)
			{
				store[num][Time].x=x;
				store[num][Time].y=y;
				Time++;
				if(y>ymax) 
					ymax=y;
				if(y<ymin) 
					ymin=y;
				if(x>xmax) 
					xmax=x;
				if(x<xmin) 
					xmin=x;
			}
		}
		
		if(Time>=300)
		{
			AfxMessageBox("当前笔划写入有误（太多）",NULL,NULL);
			OnClear();
		}
	}
	
	ReleaseDC(pDC );
	DeleteObject(pOldBrush);
	DeleteObject(Rgn);
	DeleteObject(Brush);
	
	CWnd::OnMouseMove(nFlags, point);
}

//清空画板
void CPatternDlg::OnClear() 
{
	int i,j,k;
	CDC *pDC=GetDC();
	pDC-> PatBlt (Startx,Starty,wid,lon, PATCOPY );
	ReleaseDC(pDC );
	mouseDown=0;

	for(i=0;i<15;i++){
		for(j=0;j<300;j++)
		{
			store[i][j].x=-1;
			store[i][j].y=-1;
		}
	}

	for(i=0;i<15;i++){
		for(j=0;j<300;j++)
		{
			storeback[i][j].x=-1;
			storeback[i][j].y=-1;
		}
	}

	Time=0;
	num=0;
	xmax=0;
	ymax=0;
	xmin=32;
	ymin=32;

	for(i=0;i<50;i++)
		queue[i]=-1;
	for(i=0;i<40;i++)
		queue1[i]=-1;

	test.total=-1;
	for(j=0;j<15;j++) 
		test.dian[j]=-1;
	for(j=0;j<15;j++)
	{
		for(k=0;k<20;k++)
		{
			test.detail[j][k].relate=0;
			test.detail[j][k].arc=0;
			test.detail[j][k].region=0;
		}
	}
   
	return;
}

//去除噪声
int CPatternDlg::Ridnoise(int j)         //返回k+1个特征点
{
	int i,k,ff;
	k=0;
	ff=test.total+1;      //ff,当前的处理条数,total为已存条数的最大下标

	queue1[0]=queue[0];
	for(i=1;i<j-1;i++)
	{ 
		if (abs(store[ff][queue[i]].x-store[ff][queue1[k]].x)<yu1+1+1
			&&(((store[ff][queue[i]].y-store[ff][queue1[k]].y)*(store[ff][queue[i]].y-store[ff][queue[i+1]].y))<0
			||abs(store[ff][queue[i]].y-store[ff][queue[i+1]].y)<yu2))
		{;}
		else
		{
			if (abs(store[ff][queue[i]].y-store[ff][queue1[k]].y)<yu1+1+1
				&&(((store[ff][queue[i]].x-store[ff][queue1[k]].x)*(store[ff][queue[i]].x-store[ff][queue[i+1]].x))<0||abs(store[ff][queue[i]].x-store[ff][queue[i+1]].x)<yu2))
			{;}    
			else
			{
				k++; 
				queue1[k]=queue[i];
			} 
		}
	}

	if( abs(store[ff][queue[j-1]].y-store[ff][queue1[k]].y)<2
		&&abs(store[ff][queue[j-1]].x-store[ff][queue1[k]].x)<2)
	{      
		queue1[k]=queue[j-1];
	}
	else
	{
		k++;
		queue1[k]=queue[j-1];
	}
  
	return k;
}

//得到arc特征
int CPatternDlg::Getarc(int j)
{
	int x1,x2,y1,y2,x3,y3,t1,smax,ci,vct,are;
	float s; 
	smax=0;ci=0;vct=0;
	 
	int kk;
	kk=test.total;
  
	x1=store[kk][queue1[j-1]].x;
	y1=store[kk][queue1[j-1]].y;
	x3=store[kk][queue1[j]].x;
	y3=store[kk][queue1[j]].y;
	are=abs(x1-x3);
	if(abs(y1-y3)>are) 
		are=abs(y1-y3);
	 
	for(t1=queue1[j-1]+1;t1<queue1[j];t1++)
	{
		y2=store[kk][t1].y;
		x2=store[kk][t1].x;
		s=(x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2)/are;

		if(s>=yu||s<=-yu)
		{
			if(s*smax==0)
			{
				if(s>0)
					vct=1;
				else
					vct=-1;
			}
		 
			if(s*smax<=0)
			{
				ci++;
				smax=s;
			}

			if(abs(smax)<abs(s)) 
				smax=s;
		}
	}
	 
	ci=vct*ci;

	return ci;
}

//保存特征点
void CPatternDlg::Save(int k)//此条共k+1个点
{     
	int i,j,m,l,tat;
	float value;
	test.total++; //特征总条数加一
	tat=test.total;//没有排序
	test.dian[test.total]=k;//k+1 points,初值为-1，定义此条值

	for(j=0;j<=k;j++)
	{   
		m=(int)((store[tat][queue1[j]].x-xmin)*16/(xmax-xmin+1));
		l=(int)((store[tat][queue1[j]].y-ymin)*16/(ymax-ymin+1));
		test.detail[tat][j].region=16*l+m;

		if(j==0)
		{
			test.detail[tat][j].relate=10;
			test.detail[tat][j].arc=0;
		}

		if(j>0)
		{
			if((store[tat][queue1[j]].x-store[tat][queue1[j-1]].x)>5.67*abs(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y))
			{
				test.detail[test.total][j].relate=1;
				test.detail[test.total][j].arc=Getarc(j);
			}
			else 
			{
				if((store[tat][queue1[j]].x-store[tat][queue1[j-1]].x)<-5.67*abs(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y))
				{
					test.detail[test.total][j].relate=9;
					test.detail[test.total][j].arc=Getarc(j);
				}
				else
				{
					if(5.67*abs(store[tat][queue1[j]].x-store[tat][queue1[j-1]].x)<(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y))
					{
						test.detail[test.total][j].relate=7;
						test.detail[test.total][j].arc=Getarc(j);
					}
					else 
					{
						if(-5.67*abs(store[tat][queue1[j]].x-store[tat][queue1[j-1]].x)>(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y))
						{
							test.detail[test.total][j].relate=3;
							test.detail[test.total][j].arc=Getarc(j);
						}
						else
						{
							value=(float)(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)/(store[tat][queue1[j]].x-store[tat][queue1[j-1]].x);

							if(value<2.747&&value>0.364&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)>0)
							{
								test.detail[test.total][j].relate=6;
								test.detail[test.total][j].arc=Getarc(j);
							}

							if(value<2.747&&value>0.364&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)<0)
							{
								test.detail[test.total][j].relate=4;
								test.detail[test.total][j].arc=Getarc(j);
							}
            
							if(value>-2.747&&value<-0.364&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)>0)
							{
								test.detail[test.total][j].relate=8;
								test.detail[test.total][j].arc=Getarc(j);
							}

							if(value>-2.747&&value<-0.364&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)<0)
							{
								test.detail[test.total][j].relate=2;
								test.detail[test.total][j].arc=Getarc(j);
							}

							if(value<=5.61&&value>=2.747&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)>0)
							{
								test.detail[test.total][j].relate=76;
								test.detail[test.total][j].arc=Getarc(j);
							}
							
							if(value<=5.61&&value>=2.747&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)<0)
							{
								test.detail[test.total][j].relate=34;
								test.detail[test.total][j].arc=Getarc(j);
							}

							if(value>=-5.61&&value<=-2.747&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)>0)
							{
								test.detail[test.total][j].relate=78;
								test.detail[test.total][j].arc=Getarc(j);
							}

							if(value>=-5.61&&value<=-2.747&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)<0)
							{
								test.detail[test.total][j].relate=32;
								test.detail[test.total][j].arc=Getarc(j);
							}

							if(value<=0.364&&value>=0.1782&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)>0)
							{
								test.detail[test.total][j].relate=16;
								test.detail[test.total][j].arc=Getarc(j);
							}

							if(value<=0.364&&value>=0.1782&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)<0)
							{
								test.detail[test.total][j].relate=94;
								test.detail[test.total][j].arc=Getarc(j);
							}
           
							if(value>=-0.364&&value<=-0.1782&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)>0)
							{
								test.detail[test.total][j].relate=98;
								test.detail[test.total][j].arc=Getarc(j);
							}
           
							if(value>=-0.364&&value<=-0.1782&&(store[tat][queue1[j]].y-store[tat][queue1[j-1]].y)<0)
							{
								test.detail[test.total][j].relate=12;
								test.detail[test.total][j].arc=Getarc(j);
							}
						}
					}
				}
			}
		}
	}
			  
	for(i=0;i<50;i++)
		queue[i]=-1;
	for(i=0;i<40;i++)
		queue1[i]=-1;		      //must
}

//进一步处理数据，提取特征
void  CPatternDlg::DealData()
{  
	int i,j,k,num1,Time1;
	Inorder();
	for(num1=0;store[num1][0].x>-1;num1++)        //第几条线
	{
		for(Time1=0,j=0;store[num1][Time1].x>-1;Time1++) 
		{       
			if(Time1==0)
			{
				queue[j]=Time1;j++;
			}
			
			if(Time1>0&&store[num1][Time1+1].x==-1)
			{
				queue[j]=Time1;j++;
			}
        
			if(Time1>0&&store[num1][Time1+1].x!=-1)
			{
				if((store[num1][Time1+1].x-store[num1][Time1].x)*(store[num1][Time1-1].x-store[num1][Time1].x)>0||(store[num1][Time1+1].y-store[num1][Time1].y)*(store[num1][Time1-1].y-store[num1][Time1].y)>0)
				{
					queue[j]=Time1;j++;
				}

				if (store[num1][Time1-1].x-store[num1][Time1].x==0)//&&(store[num1][Time1+1].x-store[num1][Time1].x!0))
				{
					for(i=1;store[num1][Time1-1-i].x==store[num1][Time1-1].x&&(Time1-1-i)>=0;i++){;}
					
					if((store[num1][Time1+1].x-store[num1][Time1].x)*(store[num1][Time1-1-i].x-store[num1][Time1].x)>0)
					{
						queue[j]=Time1;j++;
					}
				}

				if (store[num1][Time1-1].y-store[num1][Time1].y==0)//&&(store[num1][Time1+1].y-store[num1][Time1].y)<0)
				{
					for(i=1;store[num1][Time1-1-i].y==store[num1][Time1-1].y&&(Time1-1-i)>=0;i++){;}
					
					if((store[num1][Time1+1].y-store[num1][Time1].y)*(store[num1][Time1-1-i].y-store[num1][Time1].y)>0)
					{
						queue[j]=Time1;j++;
					}
				}
			}
		}
			
		k=Ridnoise(j);    //共j点，0到j-1
		Save(k);
	}
}

CPatternDlg::OnRecogch()                                 //清空获取的特征
{
	int i,j,k;

	for(i=0;i<50;i++)
		queue[i]=-1;
	for(i=0;i<40;i++)
		queue1[i]=-1;

	test.total=-1;
	for(j=0;j<15;j++) 
    	test.dian[j]=-1;

	for(j=0;j<15;j++)
	{
		for(k=0;k<20;k++)
		{
			test.detail[j][k].relate=0;
			test.detail[j][k].arc=0;
			test.detail[j][k].region=0;
		}
	}
	
	return(1);
}

void CPatternDlg::OnExitMenu() 
{
	// TODO: Add your command handler code here
	OnEsp();
}

void CPatternDlg::OnAboutMenu() 
{  
	CAboutDlg cabout;	

	// TODO: Add your command handler code here
	if(cabout.DoModal()==1)
	{;}
}

void CPatternDlg::OnSaveMenu() 
{
	// TODO: Add your command handler code here
	CFile cf;	
	int k,j;
	
	if(cf.Open("mydata.dat",CFile::modeReadWrite)==NULL)
	{
		AfxMessageBox("打开文件失败，\n您最好退出程序");
	}
	else 
	{       
		cf.SeekToEnd();
		cf.Write(&tez[zong].zifu, sizeof(char)*2);
		cf.Write(&tez[zong].total, sizeof(int));
		for(j=0;j<=tez[zong].total;j++)
		{
			cf.Write(&tez[zong].dian[j], sizeof(int));
		}
		   
		for(j=0;j<=tez[zong].total;j++)
		{
			for(k=0;k<=tez[zong].dian[j];k++)
			{
				cf.Write(&tez[zong].detail[j][k].relate,sizeof(int));
				cf.Write(&tez[zong].detail[j][k].region, sizeof(int));
				cf.Write(&tez[zong].detail[j][k].arc, sizeof(int));
			}
		}
			
		cf.Close( );
	}
}		

void CPatternDlg::OnOpenMenu() 
{
	CFile cf;	
	char s[20];
	int j,k;
	int nFileSize;
	int tt;

	if(cf.Open("mydata.dat",CFile::modeReadWrite)==NULL)
	{
		AfxMessageBox("打开文件失败，\n您最好退出程序");
	}
	else 
	{     
		cf.SeekToBegin(); 
		nFileSize=cf.GetLength( ); 
	    for(zong=0,tt=0;tt<nFileSize-1;zong++)                //最后减一
		{  
			cf.Read(&tez[zong].zifu, sizeof(char)*2);
			tt=tt+sizeof(char)*2;
						
			cf.Read(&tez[zong].total, sizeof(int));

			tt=tt+sizeof(int);
			for(j=0;j<=tez[zong].total;j++)
			{
				cf.Read(&tez[zong].dian[j], sizeof(int));
				tt=tt+sizeof(int);}
		   
				for(j=0;j<=tez[zong].total;j++)
				{
					for(k=0;k<=tez[zong].dian[j];k++)
					{
						cf.Read(&tez[zong].detail[j][k].relate,sizeof(int));
						cf.Read(&tez[zong].detail[j][k].region, sizeof(int));
						cf.Read(&tez[zong].detail[j][k].arc, sizeof(int));
						tt=tt+sizeof(int)*3;
					}
				}
		}
		zong--;
	}
	
	cf.Close( );
	sprintf(s,"读入正确，共有字 %d",zong);
	AfxMessageBox(s);
}

void CPatternDlg::OnSaveMenu1()
{
	AfxMessageBox("Save OK");
}

void CPatternDlg::Inorder()
{
	int i,j,k,num1,Time1;
	int  xxbegin,xxend,yybegin,yyend,total;
   
	for(num1=0;store[num1][0].x>-1;num1++)        //第几条线
	{
		xxbegin=store[num1][0].x;
		yybegin=store[num1][0].y;
		for(Time1=0,j=0;store[num1][Time1].x>-1;Time1++) 
		{;}
		total=Time1;
		xxend=store[num1][Time1-1].x;
		yyend=store[num1][Time1-1].y;
		
		for(Time1=0;store[num1][Time1].x>-1;Time1++) 
		{
			storeback[0][total-Time1-1].x=store[num1][Time1].x;
			storeback[0][total-Time1-1].y=store[num1][Time1].y;
		}
   
		if(abs(xxbegin-xxend)>2*abs(yybegin-yyend)&&(xxbegin>xxend))
		{
			for(j=0;j<total;j++)
			{
				store[num1][j].x=storeback[0][j].x;
				store[num1][j].y=storeback[0][j].y;
			}
		}
		
		if(abs(xxbegin-xxend)<=2*abs(yybegin-yyend)&&(yybegin>yyend))
		{
			for(j=0;j<total;j++)
			{
				store[num1][j].x=storeback[0][j].x;
				store[num1][j].y=storeback[0][j].y;
			}
		}
	}
}
