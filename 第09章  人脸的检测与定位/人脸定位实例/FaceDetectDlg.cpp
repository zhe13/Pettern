// FaceDetectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FaceDetect.h"
#include "FaceDetectDlg.h"
#include "ReplaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "AddSampleDlg.h"

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
// CFaceDetectDlg dialog

CFaceDetectDlg::CFaceDetectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFaceDetectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFaceDetectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaceDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaceDetectDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFaceDetectDlg, CDialog)
	//{{AFX_MSG_MAP(CFaceDetectDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BINARY, OnBtnBinary)
	ON_BN_CLICKED(IDC_BTN_EDGE, OnBtnEdge)
	ON_BN_CLICKED(IDC_BTN_FACEHAIR, OnBtnFacehair)
	ON_BN_CLICKED(IDC_BTN_HISTOGRAM_FACE, OnBtnHistogramFace)
	ON_BN_CLICKED(IDC_BTN_HISTOGRAM_H, OnBtnHistogramH)
	ON_BN_CLICKED(IDC_BTN_HISTOGRAM_HAIR, OnBtnHistogramHair)
	ON_BN_CLICKED(IDC_BTN_HISTOGRAM_V, OnBtnHistogramV)
	ON_BN_CLICKED(IDC_BTN_LIKEHOOD, OnBtnLikehood)
	ON_BN_CLICKED(IDC_BTN_MARK_EYE, OnBtnMarkEye)
	ON_BN_CLICKED(IDC_BTN_MARK_FACE_1, OnBtnMarkFace1)
	ON_BN_CLICKED(IDC_BTN_MARK_FACE_2, OnBtnMarkFace2)
	ON_BN_CLICKED(IDC_BTN_MARK_MOUSE, OnBtnMarkMouse)
	ON_BN_CLICKED(IDC_BTN_MARK_NOSE, OnBtnMarkNose)
	ON_BN_CLICKED(IDC_BTN_OPENFILE, OnBtnOpenfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectDlg message handlers

BOOL CFaceDetectDlg::OnInitDialog()
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
	CWnd *pWnd0= GetDlgItem(IDC_BMPSHOW);
	pDCShow = pWnd0->GetDC();

	m_pMainDib = new CDib();

	m_tOriPixelArray = NULL;
	m_tResPixelArray = NULL;

	m_pResMap = NULL;

	m_nWndWidth = 0;
	m_nWndHeight= 0;
	m_sFileName = "";

	m_bSelectByMan = false;
	m_bLBottonDown = false;

	m_ManLeft = -1;
	m_ManRight = -1;
	m_ManTop = -1;
	m_ManBottom = -1;

	m_bFaceOK = false;
	m_bShowFace = false;
	m_rFaceRegion.left = m_rFaceRegion.right = m_rFaceRegion.top = m_rFaceRegion.bottom = 0;

	m_bManualMarkFacial = false;
	m_bLeftEyeOK = m_bRightEyeOK = m_bLeftNostrilOK = m_bRightNostrilOK =
	m_bLeftEyeLeftCornerOK = m_bLeftEyeRightCornerOK = m_bRightEyeLeftCornerOK = 
	m_bRightEyeRightCornerOK = m_bLeftMouthCornerOK = m_bRightMouthCornerOK = false;

	m_bMidMouthOK = m_bMidNoseOK = false;

	m_LeftEye = m_RightEye = m_LeftEyeLeftCorner = m_LeftEyeRightCorner = 
	m_LeftNostril = m_RightNostril = m_RightEyeLeftCorner = m_RightEyeRightCorner =
	m_LeftMouthCorner = m_RightMouthCorner = m_MidMouth = m_MidNose = CPoint(-1,-1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFaceDetectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFaceDetectDlg::OnPaint() 
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

		if(m_tResPixelArray==NULL) return;
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFaceDetectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

////////////////////////////////////////////////////////////////////////////////
// 画十字形标记
// 参数：  pDC－CDC指针
//         point－要画的点的坐标
//         crColor－标记得颜色
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::DrawCross(CDC *pDC, CPoint point, COLORREF crColor)
{
	CPen pen,*oldPen;
	pen.CreatePen(PS_SOLID,1,crColor);
	oldPen = (CPen*)pDC->SelectObject(&pen);
	pDC->MoveTo(point.x-7,point.y);
	pDC->LineTo(point.x+7,point.y);
	pDC->MoveTo(point.x,point.y-7);
	pDC->LineTo(point.x,point.y+7);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

////////////////////////////////////////////////////////////////////////////////
// 拷贝位图
// 参数：  dest－目标位图指针
//         source－源位图指针
////////////////////////////////////////////////////////////////////////////////
bool CFaceDetectDlg::CopyBitMap(RGBQUAD **dest, RGBQUAD **source)
{
	if(source==NULL || dest==NULL) 
		return false;
	for(int i=0; i<m_nWndHeight; i++)
		for(int j=0; j<m_nWndWidth; j++)
			dest[i][j]=source[i][j];
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////
// 生成新的位图
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::MakeBitMap()
{
	CClientDC ClientDC(pDCShow->GetWindow());
	if(m_pResMap!=NULL) delete m_pResMap;

	m_pResMap=new CBitmap();
	m_pResMap->CreateCompatibleBitmap(&ClientDC,m_nWndWidth,m_nWndHeight);

	CDC  dc;
	dc.CreateCompatibleDC(&ClientDC);
	dc.SelectObject(m_pResMap);

	for(int i=0; i<m_nWndHeight; i++)
	for(int j=0; j<m_nWndWidth; j++)
	dc.SetPixelV(j,i,RGB(m_tResPixelArray[i][j].rgbRed,m_tResPixelArray[i][j].rgbGreen,m_tResPixelArray[i][j].rgbBlue));

	if(m_bFaceOK && m_bShowFace)
	{
		CBrush Pen;
		Pen.CreateSolidBrush(RGB(255,0,0));
		dc.FrameRect(m_rFaceRegion,&Pen);
	 	Pen.DeleteObject();
	}

	if(m_bLeftEyeOK)					DrawCross(&dc,m_LeftEye,RGB(255,0,0));
	if(m_bRightEyeOK)					DrawCross(&dc,m_RightEye,RGB(255,0,0));
	if(m_bLeftEyeLeftCornerOK)			DrawCross(&dc,m_LeftEyeLeftCorner,RGB(255,0,255));
	if(m_bLeftEyeRightCornerOK)			DrawCross(&dc,m_LeftEyeRightCorner,RGB(255,255,0));
	if(m_bRightEyeLeftCornerOK)			DrawCross(&dc,m_RightEyeLeftCorner,RGB(255,0,255));
	if(m_bRightEyeRightCornerOK)		DrawCross(&dc,m_RightEyeRightCorner,RGB(255,255,0));
	if(m_bLeftNostrilOK)				DrawCross(&dc,m_LeftNostril,RGB(0,255,0));
	if(m_bRightNostrilOK)				DrawCross(&dc,m_RightNostril,RGB(0,255,0));
	if(m_bMidNoseOK)					DrawCross(&dc,m_MidNose,RGB(0,255,0));
	if(m_bLeftMouthCornerOK)			DrawCross(&dc,m_LeftMouthCorner,RGB(0,0,255));
	if(m_bRightMouthCornerOK)			DrawCross(&dc,m_RightMouthCorner,RGB(0,0,255));
	if(m_bMidMouthOK)					DrawCross(&dc,m_MidMouth,RGB(0,0,255));

	dc.DeleteDC();

	MyDraw();
}

////////////////////////////////////////////////////////////////////////////////////
//读原图的数据
////////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::LoadOriPixel(CDib *pDib)
{
	BYTE	*colorTable;
	colorTable = (BYTE *)pDib->m_pDibBits;
	int byteBitCount  = pDib->GetBiBitCount()/8;

	m_tOriPixelArray  = new RGBQUAD*[m_nWndHeight];
	m_tResPixelArray  = new RGBQUAD*[m_nWndHeight];
	for(int l=0 ; l<m_nWndHeight; l++)
	{
		m_tOriPixelArray[l] = new RGBQUAD[m_nWndWidth];
		m_tResPixelArray[l] = new RGBQUAD[m_nWndWidth];
	}

	int count = 0;
	for(int i=m_nWndHeight-1; i>=0; i--)
	{
		for(int j=0; j<m_nWndWidth; j++)
		{
			m_tOriPixelArray[i][j].rgbBlue =colorTable[count++];
			m_tOriPixelArray[i][j].rgbGreen=colorTable[count++];
			m_tOriPixelArray[i][j].rgbRed  =colorTable[count++];
			m_tOriPixelArray[i][j].rgbReserved = 0;
			m_tResPixelArray[i][j]=m_tOriPixelArray[i][j];
			count += byteBitCount-3;
		}
		count += (4-(m_nWndWidth*byteBitCount)%4)%4;
	}

	method1 = new CLikelyHood(m_tOriPixelArray,m_nWndWidth,m_nWndHeight);
	method2 = new CHairFace(m_tOriPixelArray,m_nWndWidth,m_nWndHeight);
}

////////////////////////////////////////////////////////////////////////////////
// 给位图赋值
// 参数：  target－目标位图指针
//         Val－要赋予的值
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::SetPixelArray(RGBQUAD **target, int Val)
{
	for(int i=0; i<m_nWndHeight; i++)
	for(int j=0; j<m_nWndWidth; j++)
	{
		target[i][j].rgbRed =  target[i][j].rgbBlue = target[i][j].rgbGreen = Val;
	}
}

////////////////////////////////////////////////////////////////////////////////
// 边界检测
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::DoLOG(int left, int right, int top, int bottom, RGBQUAD **source, RGBQUAD **target)
{
	int i,j;

	double **result;					 
	result = new double*[m_nWndHeight];
	for(int l=0 ; l<m_nWndHeight; l++)
	{
		result[l] = new double[m_nWndWidth];
		for(j=0; j<m_nWndWidth; j++)
			result[l][j] = source[l][j].rgbRed;
	}
	
	for(i=0; i<m_nWndHeight; i++)
	for(j=0; j<m_nWndWidth; j++)
	{
		double r,g,temp;
		temp = source[i][j].rgbGreen+source[i][j].rgbRed+source[i][j].rgbBlue;
		r = (double)source[i][j].rgbRed/temp;
		g = (double)source[i][j].rgbGreen/temp;
		if(g<0.398 && g > 0.246 && r<0.664 && r>0.233 && r>g && g>=0.5*(1-r))
		{
			target[i][j].rgbRed = 255;  //face
		}
		else target[i][j].rgbRed = 0;
	}
	
	for(i=top+2; i<bottom-2; i++)
	for(j=left+2; j<right-2; j++)
	{
		result[i][j] =  
			     (0-2.0/24.0)*((unsigned char)target[i-2][j-2].rgbRed) + 
                 (0-4.0/24.0)*((unsigned char)target[i-2][j-1].rgbRed) + 
			     (0-4.0/24.0)*((unsigned char)target[i-2][j].rgbRed)   +
			     (0-4.0/24.0)*((unsigned char)target[i-2][j+1].rgbRed) +
			     (0-2.0/24.0)*((unsigned char)target[i-2][j+2].rgbRed) +
				 (0-4.0/24.0)*((unsigned char)target[i-1][j-2].rgbRed) + 
				 (8.0/24.0)  *((unsigned char)target[i-1][j].rgbRed)   +
				 (0-4.0/24.0)*((unsigned char)target[i-1][j+2].rgbRed) +
				 (0-4.0/24.0)*((unsigned char)target[i][j-2].rgbRed)   + 
				 (8.0/24.0)  *((unsigned char)target[i][j-1].rgbRed)   + 
				 (1.0)       *((unsigned char)target[i][j].rgbRed)     +
				 (8.0/24.0)  *((unsigned char)target[i][j+1].rgbRed)   +
				 (0-4.0/24.0)*((unsigned char)target[i][j+2].rgbRed)   +
				 (0-4.0/24.0)*((unsigned char)target[i+1][j-2].rgbRed) + 
				 (8.0/24.0)  *((unsigned char)target[i+1][j].rgbRed)   +
				 (0-4.0/24.0)*((unsigned char)target[i+1][j+2].rgbRed) +
				 (0-2.0/24.0)*((unsigned char)target[i+2][j-2].rgbRed) + 
				 (0-4.0/24.0)*((unsigned char)target[i+2][j-1].rgbRed) + 
				 (0-4.0/24.0)*((unsigned char)target[i+2][j].rgbRed)   +
				 (0-4.0/24.0)*((unsigned char)target[i+2][j+1].rgbRed) +
				 (0-2.0/24.0)*((unsigned char)target[i+2][j+2].rgbRed);
	}

	SetPixelArray(target,255);

	for(i=top+1; i<bottom-1; i++)
	for(j=left+1; j<right-1; j++)
	{
		int positive = 0;   
		int negtive  = 0;
		for(int m=-1;m<=1;m++)
		for(int n=-1;n<=1;n++)
		if(m!=0 || n!=0)
		{
			if(result[i+m][j+n]<-5)negtive++;
			if(result[i+m][j+n]>=5)positive++;
		}
		if(positive>2 && negtive>2) 
		{
			target[i][j].rgbBlue = target[i][j].rgbGreen = target[i][j].rgbRed = 0;
		}

	}

	if(result!=NULL)
	{
		for (int i=0 ;i<m_nWndHeight;i++)
			if(result[i]!=NULL) delete result[i];
		delete result;
	}
}

////////////////////////////////////////////////////////////////////////////////
// 二值化
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnBinary() 
{
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	
	if(!method1->CalBinary())
	{
		AfxMessageBox("请先计算相似度！");
		SetCursor(LoadCursor(NULL,IDC_ARROW));	
		return;
	}
	
	m_bShowFace = false;
	for(int i=0; i<m_nWndHeight; i++)
	for(int j=0; j<m_nWndWidth;  j++)
	{
		m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
		m_tResPixelArray[i][j].rgbRed  = (int)(method1->m_pBinaryArray[i][j]*255);
	}
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));	
	MyDraw();
}

////////////////////////////////////////////////////////////////////////////////
// 边缘提取
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnEdge() 
{
	if(!m_bFaceOK)
	{
		AfxMessageBox("请先确定脸部区域");
		return;
	}
	//左右眼的水平区域
	int nLeft,nRight,nTop,nBottom;

	nLeft	= m_rFaceRegion.left-5  > 0 ? m_rFaceRegion.left-5:0;
	nRight	= m_rFaceRegion.right+5 < m_nWndWidth? m_rFaceRegion.right+5:m_nWndWidth-1;
	nTop	= m_rFaceRegion.top-5   > 0 ? m_rFaceRegion.top-5:0;
	nBottom = m_rFaceRegion.bottom+5< m_nWndHeight?m_rFaceRegion.bottom+5:m_nWndHeight-1;
	//边缘检查
	DoLOG(nLeft,nRight,nTop,nBottom,m_tOriPixelArray,m_tResPixelArray);
	MakeBitMap();	
}

////////////////////////////////////////////////////////////////////////////////
// 求取头发和脸部区域
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnFacehair() 
{
	m_bShowFace = false;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	method2->MarkHairFace();
	for(int i=0; i<m_nWndHeight; i++)
	for(int j=0; j<m_nWndWidth;  j++)
	{
		switch(method2->m_pBinaryArray[i][j])
		{
		case 0:
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	0;
			m_tResPixelArray[i][j].rgbRed  = 255;
			break;
		case 1:
			m_tResPixelArray[i][j].rgbBlue = 255;
			m_tResPixelArray[i][j].rgbGreen=m_tResPixelArray[i][j].rgbRed=0;
			break;
		case 2:
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 0;
			break;
		}
	}
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));	
}

////////////////////////////////////////////////////////////////////////////////
// 脸部区域直方图
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnHistogramFace() 
{
	if(!method2->m_bBinaryOK)
	{
		AfxMessageBox("请先计算二值化图！");
		return;
	}

	m_bShowFace = false;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	for(int j=0; j<m_nWndWidth;  j++)	
	{
		int count = 0;
		for(int i=0; i<m_nWndHeight; i++)
		{
			if(method2->m_pBinaryArray[i][j] == 0) count++;
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 255;
		}
		for(i=m_nWndHeight-1; i>=m_nWndHeight-count;i--)
		{
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 0;
		}
	}

	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));			
}

////////////////////////////////////////////////////////////////////////////////
// 水平方向直方图
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnHistogramH() 
{
	if(!method1->m_bBinaryReady)
	{
		AfxMessageBox("请先计算二值图");
		return;
	}
	m_bShowFace = false;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	for(int j=0; j<m_nWndWidth;  j++)	
	{
		int count = 0;
		for(int i=0; i<m_nWndHeight; i++)
		{
			if(method1->m_pBinaryArray[i][j] == 1) count++;
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 255;
		}
		for(i=m_nWndHeight-1; i>=m_nWndHeight-count;i--)
		{
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 0;
		}
	}
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));		
}

////////////////////////////////////////////////////////////////////////////////
// 头发的直方图
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnHistogramHair() 
{
	if(!method2->m_bBinaryOK)
	{
		AfxMessageBox("请先计算二值图！");
		return;
	}
	m_bShowFace = false;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	for(int j=0; j<m_nWndWidth;  j++)	
	{
		int count = 0;
		for(int i=0; i<m_nWndHeight; i++)
		{
			if(method2->m_pBinaryArray[i][j] == 1) count++;
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 255;
		}
		for(i=m_nWndHeight-1; i>=m_nWndHeight-count;i--)
		{
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 0;
		}
	}
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));					
}

////////////////////////////////////////////////////////////////////////////////
// 垂直方向的直方图
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnHistogramV() 
{
	if(!method1->m_bBinaryReady)
	{
		AfxMessageBox("请先计算二值图");
		return;
	}

	m_bShowFace = false;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	for(int i=0; i<m_nWndHeight; i++)		
	{
		int count = 0;
		for(int j=0; j<m_nWndWidth;  j++)
		{
			if(method1->m_pBinaryArray[i][j] == 1) count++;
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 255;
		}
		for(j=0; j<count;  j++)
		{
			m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
			m_tResPixelArray[i][j].rgbRed  = 0;
		}
	}
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));			
}

////////////////////////////////////////////////////////////////////////////////
// 计算相似度
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnLikehood() 
{
	m_bShowFace = false;
	SetCursor(LoadCursor(NULL,IDC_WAIT));

	method1->CalLikeHood();
	for(int i=0; i<m_nWndHeight; i++)
	for(int j=0; j<m_nWndWidth;  j++)
	{
		m_tResPixelArray[i][j].rgbBlue = m_tResPixelArray[i][j].rgbGreen =	
		m_tResPixelArray[i][j].rgbRed  = (int)(method1->m_pLikeliHoodArray[i][j]*255);
	}
	MakeBitMap();

	SetCursor(LoadCursor(NULL,IDC_ARROW));	
}

////////////////////////////////////////////////////////////////////////////////
// 标记眼睛区域
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnMarkEye() 
{
	int i,j;
	if(!m_bFaceOK)
	{
		AfxMessageBox("请先确定脸部区域");
		return;
	}
	//左右眼的水平区域
	CPoint LeftEyeAreaH(-1,-1),RightEyeAreaH(-1,-1);
	CPoint LeftEyeAreaV(-1,-1),RightEyeAreaV(-1,-1);

	int nLeft,nRight,nTop,nBottom;

	nLeft	= m_rFaceRegion.left-5  > 0 ? m_rFaceRegion.left-5:0;
	nRight	= m_rFaceRegion.right+5 < m_nWndWidth? m_rFaceRegion.right+5:m_nWndWidth-1;
	nTop	= m_rFaceRegion.top-5   > 0 ? m_rFaceRegion.top-5:0;
	nBottom = m_rFaceRegion.bottom+5< m_nWndHeight?m_rFaceRegion.bottom+5:m_nWndHeight-1;
	//边缘检查
	DoLOG(nLeft,nRight,nTop,nBottom,m_tOriPixelArray,m_tResPixelArray);

	///////////////////////////////////
	//确认两个眼睛的水平区域
    //////////////////////////////////
	int nSlidWinWidth  = (m_rFaceRegion.right - m_rFaceRegion.left)/6/2;
	int nSlidWinHeight = (m_rFaceRegion.bottom - m_rFaceRegion.top)/15/2;
	int nMidFaceH = (m_rFaceRegion.right+m_rFaceRegion.left)/2;
	int nMidFaceV = (m_rFaceRegion.bottom+m_rFaceRegion.top)/2;

	int *tempArray = new int[m_nWndWidth]; 
	for(i = 0; i<m_nWndWidth; i++) tempArray[i] = 0;

	for(i=nMidFaceV-nSlidWinHeight; i > m_rFaceRegion.top+6*nSlidWinHeight; i--)
	for(j=m_rFaceRegion.left+nSlidWinWidth; j<m_rFaceRegion.right-nSlidWinWidth; j++)
	{
		int count = 0;
		for(int p= -nSlidWinHeight ;p<nSlidWinHeight;p++)
		for(int q= -nSlidWinWidth ;q<nSlidWinWidth;q++)
		{
			if(m_tResPixelArray[i+p][j+q].rgbRed == 0)	count++;
		}
		if(count >= nSlidWinWidth*nSlidWinHeight/3)
		{
			m_tResPixelArray[i][j].rgbRed = 255;
			tempArray[j] ++;
		}
	}

	MakeBitMap();
	AfxMessageBox("眼睛的区域鉴别");

	CList<CPoint,CPoint&> myList1(sizeof(CPoint));
	CList<CPoint,CPoint&> myList2(sizeof(CPoint));
	int flag = 0;
	CPoint tPoint(-1,-1);
	for(i = 0; i<m_nWndWidth; i++)
	{
		if(tempArray[i] > 0 && flag ==0)
		{
			tPoint.x = i;
			flag = 1;
		}
		if(tempArray[i] == 0 && flag ==1)
		{
			tPoint.y = i;
			myList1.AddTail(tPoint);
			flag = 0;
		}
	}
	delete tempArray;
	//去掉长度太小的候选者	
	for(i=0; i<myList1.GetCount();i++)
	{
		CPoint temp(-1,-1);
		temp = myList1.GetAt(myList1.FindIndex(i));
		int minVal = (m_rFaceRegion.right - m_rFaceRegion.left)/20;
		if((temp.y-temp.x)>=minVal)
			myList2.AddTail(temp);
	}
	myList1.RemoveAll();
    //合并相邻很紧的区域
	bool quit = 1;
	while(quit)
	{
		bool doJoin = false;
		for(int i=0; i<myList2.GetCount()-1;i++)
		{
			CPoint temp1(-1,-1),temp2(-1,-1);
			temp1 = myList2.GetAt(myList2.FindIndex(i));
			temp2 = myList2.GetAt(myList2.FindIndex(i+1));
			if((temp2.x-temp1.y)<=(m_rFaceRegion.right - m_rFaceRegion.left)/40)
			{
				temp1.y = temp2.y;
				myList2.RemoveAt(myList2.FindIndex(i));
				myList2.RemoveAt(myList2.FindIndex(i));
				if(i == 0)			myList2.AddHead(temp1);
				else			    myList2.InsertAfter(myList2.FindIndex(i-1),temp1);
				doJoin = true;
				break;
			}	
		}
		if(!doJoin)	quit = 0;
	}

	//没有找到眼睛区域
	if(myList2.GetCount()<2) 
	{
		CPoint t=myList2.GetHead();
		if((t.y-t.x)>(m_rFaceRegion.right - m_rFaceRegion.left)/2)
		{
			LeftEyeAreaH.x = t.x; 
			LeftEyeAreaH.y = t.x+(t.y-t.x)/3; 
			RightEyeAreaH.x = t.y-(t.y-t.x)/3;
			RightEyeAreaH.y = t.y; 
		}
		else
		{
			AfxMessageBox("确认眼睛位置失败，请手动标定");
			return;
		}
	}
	//仅有两个区域
	else if(myList2.GetCount()==2)
	{
		LeftEyeAreaH = myList2.GetHead();
		RightEyeAreaH = myList2.GetTail();
	}
	else  //多于两个区域
	{
		int ldis = -100000;
		int rdis = 100000;	
		for(i=0; i<myList2.GetCount();i++)
		{
			CPoint temp(-1,-1);
			temp = myList2.GetAt(myList2.FindIndex(i));
			//右眼
			if((temp.x+temp.y)/2 > nMidFaceH)
			{
				if(((temp.x+temp.y)/2-nMidFaceH)<rdis)
				{
					rdis = (temp.x+temp.y)/2-nMidFaceH;
					RightEyeAreaH = temp;
				}
			}
			//左眼
			else
			{
				if(((temp.x+temp.y)/2-nMidFaceH)>ldis)
				{
					ldis = (temp.x+temp.y)/2-nMidFaceH;
					LeftEyeAreaH = temp;
				}
			}
		}
	}
	myList2.RemoveAll();
	///////////////////////////////////
	//确认两个眼睛的垂直区域
    //////////////////////////////////
	//左眼
	if(LeftEyeAreaH != CPoint(-1,-1))
	{
		int *tArray = new int[m_nWndHeight]; 
		int i,j;
		for(i = 0; i<m_nWndHeight; i++) tArray[i] = 0;

		for(i=nMidFaceV-nSlidWinHeight; i > m_rFaceRegion.top+6*nSlidWinHeight; i--)
		for(j=LeftEyeAreaH.x; j<=LeftEyeAreaH.y;j++)
		if(m_tResPixelArray[i][j].rgbRed == 255 && m_tResPixelArray[i][j].rgbGreen == 0)
			tArray[i] ++;

		CList<CPoint,CPoint&> myListA(sizeof(CPoint));
		CList<CPoint,CPoint&> myListB(sizeof(CPoint));
		int flag = 0;
		CPoint tPoint(-1,-1);
		for(i = nMidFaceV-nSlidWinHeight; i > m_rFaceRegion.top+6*nSlidWinHeight; i--)
		{
			if(tArray[i] > 0 && flag ==0)
			{
				tPoint.x = i;
				flag = 1;
			}
			if(tArray[i] == 0 && flag ==1)
			{
				tPoint.y = i;
				myListA.AddTail(tPoint);
				flag = 0;
			}
		}
		delete tArray;
		//去掉长度太小的候选者	
		for(i=0; i<myListA.GetCount();i++)
		{
			CPoint temp(-1,-1);
			temp = myListA.GetAt(myListA.FindIndex(i));
			int minVal = (m_rFaceRegion.bottom - m_rFaceRegion.top)/100;
			if((temp.x-temp.y)>=minVal)
				myListB.AddTail(temp);
		}
		myListA.RemoveAll();
		//合并相邻很紧的区域
		bool quit = 1;
		while(quit)
		{
			bool doJoin = false;
			for(int i=0; i<myListB.GetCount()-1;i++)
			{
				CPoint temp1(-1,-1),temp2(-1,-1);
				temp1 = myListB.GetAt(myListB.FindIndex(i));
				temp2 = myListB.GetAt(myListB.FindIndex(i+1));
				if((temp1.y-temp2.x)<=(m_rFaceRegion.bottom - m_rFaceRegion.top)/100)
				{
					temp1.y = temp2.y;
					myListB.RemoveAt(myListB.FindIndex(i));
					myListB.RemoveAt(myListB.FindIndex(i));
					if(i == 0)			myListB.AddHead(temp1);
					else			    myListB.InsertAfter(myListB.FindIndex(i-1),temp1);
					doJoin = true;
					break;
				}	
			}
			if(!doJoin)	quit = 0;
		}
		if(myListB.GetCount()==0)
		{
			AfxMessageBox("无法确定左眼的位置");
		}
		else
		{
			LeftEyeAreaV = myListB.GetHead();
			
			double sumX = 0.0;
			double sumY = 0.0;
			int sum = 0;
			m_LeftEyeLeftCorner.x = 100000;
			m_LeftEyeRightCorner.x = -1;

			for(i=LeftEyeAreaV.x; i>= LeftEyeAreaV.y;i--)
			for(j=LeftEyeAreaH.x; j<=LeftEyeAreaH.y;j++)
			if(m_tResPixelArray[i][j].rgbGreen == 0)
			{
				if(j<m_LeftEyeLeftCorner.x)	
				{
					m_LeftEyeLeftCorner.x = j;
					m_LeftEyeLeftCorner.y = i;
				}
				if(j>m_LeftEyeRightCorner.x)
				{
					m_LeftEyeRightCorner.x = j;
					m_LeftEyeRightCorner.y = i;
				}
				sumX += j;
				sumY += i;
				sum++;
			}

			m_LeftEye.x = (int)(sumX/sum);
			m_LeftEye.y = (int)(sumY/sum);	

			m_bLeftEyeOK = TRUE;	
			m_bLeftEyeLeftCornerOK = TRUE;
			m_bLeftEyeRightCornerOK =TRUE;
		}
		myListB.RemoveAll();
	}
	//右眼
	if(RightEyeAreaH != CPoint(-1,-1))
	{
		int *tArray = new int[m_nWndHeight]; 
		int i,j;
		for(i = 0; i<m_nWndHeight; i++) tArray[i] = 0;

		for(i=nMidFaceV-nSlidWinHeight; i > m_rFaceRegion.top+6*nSlidWinHeight; i--)
		for(j=RightEyeAreaH.x; j<=RightEyeAreaH.y;j++)
		if(m_tResPixelArray[i][j].rgbRed == 255 && m_tResPixelArray[i][j].rgbGreen == 0)
			tArray[i] ++;

		CList<CPoint,CPoint&> myListA(sizeof(CPoint));
		CList<CPoint,CPoint&> myListB(sizeof(CPoint));
		int flag = 0;
		CPoint tPoint(-1,-1);
		for(i = nMidFaceV-nSlidWinHeight; i > m_rFaceRegion.top+6*nSlidWinHeight; i--)
		{
			if(tArray[i] > 0 && flag ==0)
			{
				tPoint.x = i;
				flag = 1;
			}
			if(tArray[i] == 0 && flag ==1)
			{
				tPoint.y = i;
				myListA.AddTail(tPoint);
				flag = 0;
			}
		}
		delete tArray;
		//去掉长度太小的候选者	
		for(i=0; i<myListA.GetCount();i++)
		{
			CPoint temp(-1,-1);
			temp = myListA.GetAt(myListA.FindIndex(i));
			int minVal = (m_rFaceRegion.bottom - m_rFaceRegion.top)/100;
			if((temp.x-temp.y)>=minVal)
				myListB.AddTail(temp);
		}
		myListA.RemoveAll();
		//合并相邻很紧的区域
		bool quit = 1;
		while(quit)
		{
			bool doJoin = false;
			for(int i=0; i<myListB.GetCount()-1;i++)
			{
				CPoint temp1(-1,-1),temp2(-1,-1);
				temp1 = myListB.GetAt(myListB.FindIndex(i));
				temp2 = myListB.GetAt(myListB.FindIndex(i+1));
				if((temp1.y-temp2.x)<=(m_rFaceRegion.bottom - m_rFaceRegion.top)/50)
				{
					temp1.y = temp2.y;
					myListB.RemoveAt(myListB.FindIndex(i));
					myListB.RemoveAt(myListB.FindIndex(i));
					if(i == 0)			myListB.AddHead(temp1);
					else			    myListB.InsertAfter(myListB.FindIndex(i-1),temp1);
					doJoin = true;
					break;
				}	
			}
			if(!doJoin)	quit = 0;
		}
		if(myListB.GetCount()==0)
		{
			AfxMessageBox("无法确定右眼的位置");
		}
		else
		{
			if(myListB.GetCount()==1)
				RightEyeAreaV = myListB.GetHead();
			else
			{
				CPoint tt =  myListB.GetHead();
				int index = myListB.GetCount();
				while(tt.y > LeftEyeAreaV.x && index > 0)
				{
					index --;
					tt = myListB.GetAt(myListB.FindIndex(myListB.GetCount()-index)); 
				}
				RightEyeAreaV = tt;		
			}
			
			double sumX = 0.0;
			double sumY = 0.0;
			int sum = 0;
			m_RightEyeLeftCorner.x = 100000;
			m_RightEyeRightCorner.x = -1;

			for(i=RightEyeAreaV.x; i>=RightEyeAreaV.y;i--)
			for(j=RightEyeAreaH.x; j<=RightEyeAreaH.y;j++)
			if(m_tResPixelArray[i][j].rgbGreen == 0)
			{
				if(j<m_RightEyeLeftCorner.x)	
				{
					m_RightEyeLeftCorner.x = j;
					m_RightEyeLeftCorner.y = i;
				}
				if(j>m_RightEyeRightCorner.x)
				{
					m_RightEyeRightCorner.x = j;
					m_RightEyeRightCorner.y = i;
				}
				sumX += j;
				sumY += i;
				sum++;
			}
			m_RightEye.x = (int)(sumX/sum);
			m_RightEye.y = (int)(sumY/sum);
			
			m_bRightEyeOK = TRUE;
			m_bRightEyeLeftCornerOK = TRUE;
			m_bRightEyeRightCornerOK =TRUE;

		}
		myListB.RemoveAll();
	}
	CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
	MakeBitMap();		
}

////////////////////////////////////////////////////////////////////////////////
// 第一种方法标记脸部区域
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnMarkFace1() 
{
	if(!method1->m_bBinaryReady)
	{
		AfxMessageBox("请先计算二值化图！");
		return;
	}
	m_bShowFace = true;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	int *temp = new int[m_nWndWidth];
	int max = 0;
	int pos = -1;
	for(int j=0; j<m_nWndWidth;  j++)	
	{
		int count = 0;
		for(int i=0; i<m_nWndHeight; i++)
		{
			if(method1->m_pBinaryArray[i][j] == 1) count++;
		}
		temp[j] = count;
		if(count > max)
		{
			max = count;
			pos = j;
		}
	}
	int left,right,l,top,bottom;
	for(l=pos; l>=0; l--)
	{
		if(temp[l]<max*0.2||l==0)
		{
			left = l;
			break;
		}
	}
	for(l=pos; l<m_nWndWidth; l++)
	{
		if(temp[l]<max*0.3||l==m_nWndWidth-1)
		{
			right = l;
			break;
		}
	}
	for(int i=0; i<m_nWndHeight; i++)
	{
		int count = 0;
		for(l = left;l<=right;l++)
		{
			if(method1->m_pBinaryArray[i][l] == 1) count++;
		}
		if(count>=(right-left)*0.5)
		{
			top = i;
			break;
		}
	}
	bottom = (int)(top+(right-left)*1.5)>=m_nWndHeight? m_nWndHeight-1:(int)(top+(right-left)*1.5);

	CopyBitMap(m_tResPixelArray,m_tOriPixelArray);

	for(i=top;i<=bottom;i++)
	{
		m_tResPixelArray[i][left].rgbBlue=255;
		m_tResPixelArray[i][left].rgbGreen = m_tResPixelArray[i][left].rgbRed = 0;
		m_tResPixelArray[i][right].rgbBlue=255;
		m_tResPixelArray[i][right].rgbGreen = m_tResPixelArray[i][right].rgbRed = 0;
	}
	for(j=left;j<=right;j++)
	{
		m_tResPixelArray[top][j].rgbBlue=255;
		m_tResPixelArray[top][j].rgbGreen = m_tResPixelArray[top][j].rgbRed = 0;
		m_tResPixelArray[bottom][j].rgbBlue=255;
		m_tResPixelArray[bottom][j].rgbGreen = m_tResPixelArray[bottom][j].rgbRed = 0;
	}
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));			

	if(m_bFaceOK)
	{
		ReplaceDlg dlg;
		if(dlg.DoModal()==IDOK)
		{
			CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
			CRect rect(left,top,right,bottom);
			m_rFaceRegion = rect;
			MakeBitMap();
		}
	}
	else
	{
		m_bFaceOK = true;
		CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
		CRect rect(left,top,right,bottom);
		m_rFaceRegion = rect;
		MakeBitMap();
	}
}

////////////////////////////////////////////////////////////////////////////////
// 第二种方法标记脸部区域
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnMarkFace2() 
{
	if(!method2->m_bBinaryOK)
	{
		AfxMessageBox("请先计算二值化图");
		return;
	}
	m_bShowFace = true;
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	int *numR,*numB, i, j, left,right,top,bottom;
	int maxnumR = 0, maxnumB = 0;

	numR = new int[m_nWndWidth];
	numB = new int[m_nWndWidth];
	for(j=0;j<m_nWndWidth ;j++)
	{
		int countR = 0, countB = 0;
		for(i=0;i<m_nWndHeight;i++)
		{
			if(method2->m_pBinaryArray[i][j] == 0)
				countR++;
			if(method2->m_pBinaryArray[i][j] == 1)
				countB++;
		}
		if(countR > maxnumR) maxnumR = countR;
		numR[j] = countR;
		if(countB > maxnumB) maxnumB = countB;
		numB[j] = countB;
	}
	CList<CPoint,CPoint> myListR(sizeof(CPoint));
	CList<CPoint,CPoint> myListB(sizeof(CPoint));
	CPoint tempR,tempB;
	int flagR = 0,flagB = 0;
	for(j=0;j<m_nWndWidth ;j++)
	{
		if(flagR == 0)
		{
			if(numR[j]>maxnumR/2)
			{
				flagR = 1;
				tempR.x = j;				
			}
		}
		else
		{
			if(numR[j]<=maxnumR/2 || j==m_nWndWidth-1)
			{
				flagR = 0;
				tempR.y = j;
				myListR.AddTail(tempR);
			}
		}
		if(flagB == 0)
		{
			if(numB[j]>maxnumB/5)
			{
				flagB = 1;
				tempB.x = j;
			}
		}
		else
		{
			if(numB[j]<=maxnumB/5 || j==m_nWndWidth-1)
			{
				flagB = 0;
				tempB.y = j;
				if(myListB.GetCount() > 1 && (tempB.x-myListB.GetTail().y)<20)
					myListB.SetAt(myListB.GetTailPosition(),CPoint(myListB.GetTail().x,j));
				else
				myListB.AddTail(tempB);
			}
		}

	}	
	if(numR!=NULL)delete numR;
	if(numB!=NULL)delete numB;

	int *hairmark, k;
	hairmark = new int[m_nWndWidth];
	for(j=0;j<m_nWndWidth ;j++) hairmark[j]=0;

	for(k=0;k<myListB.GetCount();k++)
	{
		CPoint temp = myListB.GetAt(myListB.FindIndex(k));
		if((temp.y-temp.x)>m_nWndWidth/10)
		{
			for(int t = temp.x;t<=temp.y;t++)
			hairmark[t] = 1;
		}
	}

	for(k=0;k<myListR.GetCount();k++)
	{
		CPoint temp = myListR.GetAt(myListR.FindIndex(k));
		int templeft=-1;
		int tempright=-1;

		if((temp.y-temp.x)>m_nWndWidth/10)
		{
			for(int t=temp.x;t<=temp.y;t++)
			{
				if(hairmark[t]==1)
				{
					int endpos=t+(temp.y-temp.x)/5;
					if(endpos > temp.y)endpos = temp.y;
					int yes = 1;
					for(int q=t;q<=endpos;q++)
						if(hairmark[q]==0) yes = 0;
					if(yes == 1)
					{
						templeft = t;
						break;
					}
				}
			}
			for(int p=temp.y;p>=temp.x;p--)
			{
				if(hairmark[p]==1)
				{
					int beginpos=p-(temp.y-temp.x)/5;
					if(beginpos < temp.x)beginpos = temp.x;
					int yes = 1;
					for(int q=p;q>=beginpos;q--)
						if(hairmark[q]==0) yes = 0;
					if(yes == 1)
					{
						tempright = p;
						break;
					}
				}
			}
		}
		if(templeft!=-1 && tempright!=-1)
		{
			left = templeft;
			right = tempright;
			break;
		}
	}
	if(hairmark !=NULL) delete hairmark;
	myListR.RemoveAll();
	myListB.RemoveAll();

	if(left-m_nWndWidth/50>0) left-=(int)m_nWndWidth/50;
	else left = 0;
	if(right+m_nWndWidth/40>m_nWndWidth) right=m_nWndWidth-1;
	else right += m_nWndWidth/40;

	for(i=0; i<m_nWndHeight; i++)
	{
		int count = 0;
		for(int l = left;l<=right;l++)
		{
			if(method2->m_pBinaryArray[i][l] == 0) count++;
		}
		if(count>=(right-left)*0.5)
		{
			top = i;
			break;
		}
	}
	bottom = (int)(top+(right-left)*1.5)>=m_nWndHeight? m_nWndHeight-1:(int)(top+(right-left)*1.5);

	CopyBitMap(m_tResPixelArray,m_tOriPixelArray);

	for(i=top;i<=bottom;i++)
	{
		m_tResPixelArray[i][left].rgbBlue=255;
		m_tResPixelArray[i][left].rgbGreen = m_tResPixelArray[i][left].rgbRed = 0;
		m_tResPixelArray[i][right].rgbBlue=255;
		m_tResPixelArray[i][right].rgbGreen = m_tResPixelArray[i][right].rgbRed = 0;
	}
	for(j=left;j<=right;j++)
	{
		m_tResPixelArray[top][j].rgbBlue=255;
		m_tResPixelArray[top][j].rgbGreen = m_tResPixelArray[top][j].rgbRed = 0;
		m_tResPixelArray[bottom][j].rgbBlue=255;
		m_tResPixelArray[bottom][j].rgbGreen = m_tResPixelArray[bottom][j].rgbRed = 0;
	}
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));			

	if(m_bFaceOK)
	{
		ReplaceDlg dlg;
		if(dlg.DoModal()==IDOK)
		{
			CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
			CRect rect(left,top,right,bottom);
			m_rFaceRegion = rect;
			MakeBitMap();
		}
	}
	else
	{
		m_bFaceOK = true;
		CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
		CRect rect(left,top,right,bottom);
		m_rFaceRegion = rect;
		MakeBitMap();
	}
}

////////////////////////////////////////////////////////////////////////////////
// 标记嘴巴
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnMarkMouse() 
{
	int i,j;
	if(!(m_bLeftEyeOK&&m_bRightEyeOK))
	{
		AfxMessageBox("请先确定眼睛");
		return;
	}
	//左右眼的水平区域
	int nLeft,nRight,nTop,nBottom;

	nLeft	= m_rFaceRegion.left-5  > 0 ? m_rFaceRegion.left-5:0;
	nRight	= m_rFaceRegion.right+5 < m_nWndWidth? m_rFaceRegion.right+5:m_nWndWidth-1;
	nTop	= m_rFaceRegion.top-5   > 0 ? m_rFaceRegion.top-5:0;
	nBottom = m_rFaceRegion.bottom+5< m_nWndHeight?m_rFaceRegion.bottom+5:m_nWndHeight-1;

	SetPixelArray(m_tResPixelArray,0);
	for(i=nTop; i<=nBottom; i++)
	for(j=nLeft; j<=nRight; j++)
	{
		BYTE R,G,B;
		double temp,dlta;
		R = m_tOriPixelArray[i][j].rgbRed;
		G = m_tOriPixelArray[i][j].rgbGreen;
		B = m_tOriPixelArray[i][j].rgbBlue;
		if((R==G) && (G==B)) temp = 0;
		else temp = 0.5*(2*R-G-B)/sqrt((R-G)*(R-G)+(R-B)*(G-B));
		dlta = acos(temp);
		if(dlta < 0.2)
		{
			m_tResPixelArray[i][j].rgbRed = 255;  
		}
		else m_tResPixelArray[i][j].rgbRed = 0;
	}

	MakeBitMap();
	AfxMessageBox("嘴的肤色鉴定");
	//双目斜角
	double tanThta;
	if(m_RightEye.y == m_LeftEye.y) tanThta = 0;
	else tanThta = (m_RightEye.y - m_LeftEye.y)/(m_RightEye.x - m_LeftEye.x);
	//双目距离
	int EyesDis = (m_RightEye.x-m_LeftEye.x)*(m_RightEye.x-m_LeftEye.x);
	EyesDis += (m_RightEye.y-m_LeftEye.y)*(m_RightEye.y-m_LeftEye.y);
	EyesDis = (int)sqrt(EyesDis);
	//双目平均高度
	int EyeV    = (m_RightEye.y + m_LeftEye.y)/2;
	//可能的嘴的区域
	int MouthUp   = (EyeV+1.0*EyesDis) > nBottom ? nBottom:(int)(EyeV+1.0*EyesDis);
	int MouthDown = (EyeV+1.5*EyesDis) > nBottom ? nBottom:(int)(EyeV+1.5*EyesDis);


	int* Y_Arry = new int[MouthDown-MouthUp];
	for(i =0 ;i < MouthDown-MouthUp ;i++) Y_Arry[i] = 0;
	int* X_Arry = new int[EyesDis];
	for(i =0 ;i < EyesDis ;i++) X_Arry[i] = 0;
	for(i = MouthUp ; i < MouthDown; i++)
	for(j = m_LeftEye.x; j< m_RightEye.x; j++)
	{
		if(m_tResPixelArray[i][j].rgbRed == 255)
		{
			Y_Arry[i-MouthUp] ++;
			X_Arry[j-m_LeftEye.x] ++;
		}
	}
	
	int maxY = 0;
	for(i =0 ;i < MouthDown-MouthUp ;i++)
	{
		if(Y_Arry[i]>maxY)
		{
			maxY = Y_Arry[i];
			m_MidMouth.y =  i+MouthUp - (MouthDown-MouthUp)/10;
		}
	}
	m_LeftMouthCorner.y  =(int)(m_MidMouth.y - tanThta*EyesDis/2);
	m_RightMouthCorner.y =(int)(m_MidMouth.y + tanThta*EyesDis/2);
	for(i =0 ;i < EyesDis ;i++)
	{
		if(X_Arry[i]>0)
		{
			m_LeftMouthCorner.x = i+m_LeftEye.x;
			break;
		}
	}
	for(i = EyesDis -1; i >=0 ;i--)
	{
		if(X_Arry[i]>0)
		{
			m_RightMouthCorner.x = m_LeftEye.x+i;
			break;
		}
	}

	//唇中点较薄
	int min = 1000000;
	for(i = (int)(3*EyesDis/7+0.5) ; i <= (int)(4*EyesDis/7+0.5);i++)
	{
		if(X_Arry[i]<min)
		{
			min = X_Arry[i];
			m_MidMouth.x = m_LeftEye.x+i;
		}
	}
	m_MidMouth.x = (int)(m_MidMouth.x+(m_LeftEye.x+EyesDis/2))/2;

	m_bMidMouthOK = TRUE;
	m_bLeftMouthCornerOK = TRUE;
	m_bRightMouthCornerOK = TRUE;
	
	CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
	MakeBitMap();	
}

////////////////////////////////////////////////////////////////////////////////
// 标记鼻子
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnMarkNose() 
{
	int i,j;
	if(!(m_bLeftEyeOK&&m_bRightEyeOK))
	{
		AfxMessageBox("请先确定眼睛");
		return;
	}
	//左右眼的水平区域
	int nLeft,nRight,nTop,nBottom;

	nLeft	= m_rFaceRegion.left-5  > 0 ? m_rFaceRegion.left-5:0;
	nRight	= m_rFaceRegion.right+5 < m_nWndWidth? m_rFaceRegion.right+5:m_nWndWidth-1;
	nTop	= m_rFaceRegion.top-5   > 0 ? m_rFaceRegion.top-5:0;
	nBottom = m_rFaceRegion.bottom+5< m_nWndHeight?m_rFaceRegion.bottom+5:m_nWndHeight-1;

	SetPixelArray(m_tResPixelArray,0);
	for(i=nTop; i<=nBottom; i++)
	for(j=nLeft; j<=nRight; j++)
	{
		double Y;
		Y = 0.30*m_tOriPixelArray[i][j].rgbRed+0.59*m_tOriPixelArray[i][j].rgbGreen
			+0.11*m_tOriPixelArray[i][j].rgbBlue;
		if(Y<100)
		{
			m_tResPixelArray[i][j].rgbRed = 255;  
		}
		else m_tResPixelArray[i][j].rgbRed = 0;
	}

	MakeBitMap();
	AfxMessageBox("鼻子的肤色鉴定");
	//双目斜角
	double tanThta;
	if(m_RightEye.y == m_LeftEye.y) tanThta = 0;
	else tanThta = (m_RightEye.y - m_LeftEye.y)/(m_RightEye.x - m_LeftEye.x);
	//双目距离
	int EyesDis = (m_RightEye.x-m_LeftEye.x)*(m_RightEye.x-m_LeftEye.x);
	EyesDis += (m_RightEye.y-m_LeftEye.y)*(m_RightEye.y-m_LeftEye.y);
	EyesDis = (int)sqrt(EyesDis);
	//双目平均高度
	int EyeV    = (m_RightEye.y + m_LeftEye.y)/2;
	//可能的鼻子的区域
	int NoseUp   = (EyeV+0.5*EyesDis) > nBottom ? nBottom:(int)(EyeV+0.5*EyesDis);
	int NoseDown = (EyeV+0.8*EyesDis) > nBottom ? nBottom:(int)(EyeV+0.8*EyesDis);

	int* Y_Arry = new int[NoseDown-NoseUp];
	for(i =0 ;i < NoseDown-NoseUp ;i++) Y_Arry[i] = 0;

	int* X_Arry = new int[EyesDis];
	for(i =0 ;i < EyesDis ;i++) X_Arry[i] = 0;

	for(i = NoseUp ; i < NoseDown; i++)
	for(j = m_LeftEye.x+EyesDis/5; j< m_RightEye.x-EyesDis/5; j++)
	{
		if(m_tResPixelArray[i][j].rgbRed == 255)
		{
			Y_Arry[i-NoseUp] ++;
			X_Arry[j-m_LeftEye.x] ++;
		}
	}
	
	int maxY = 0;
	for(i =0 ;i < NoseDown-NoseUp ;i++)
	{
		if(Y_Arry[i]>maxY)
		{
			maxY = Y_Arry[i];
			m_MidNose.y =  i+NoseUp;
		}
	}
	m_LeftNostril.y  =(int)(m_MidNose.y - tanThta*EyesDis/2);
	m_RightNostril.y =(int)(m_MidNose.y + tanThta*EyesDis/2);
	for(i =0 ;i < EyesDis ;i++)
	{
		if(X_Arry[i]>0)
		{
			m_LeftNostril.x = i+m_LeftEye.x;
			break;
		}
	}
	for(i = EyesDis-1; i >=0 ;i--)
	{
		if(X_Arry[i]>0)
		{
			m_RightNostril.x = i+m_LeftEye.x;
			break;
		}
	}
	//唇中点较薄
	int min = 1000000;
	for(i = (int)(EyesDis/3+0.5) ; i <= (int)(2*EyesDis/3+0.5);i++)
	{
		if(X_Arry[i]<min)
		{
			min = X_Arry[i];
			m_MidNose.x = m_LeftEye.x+i;
		}
	}
	m_MidNose.x = (m_MidNose.x+(m_LeftEye.x+EyesDis/2))/2;

	m_bMidNoseOK = TRUE;
	m_bLeftNostrilOK = TRUE;
	m_bRightNostrilOK = TRUE;
	
	CopyBitMap(m_tResPixelArray,m_tOriPixelArray);
	MakeBitMap();		
}

////////////////////////////////////////////////////////////////////////////////
// 打开文件
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::OnBtnOpenfile() 
{
	CAddSampleDlg FileDlg(TRUE, "", NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, 
		"BMP人脸图像(*.bmp)|*.bmp|所有文件(*.*)|*.*||",
		AfxGetMainWnd());

	CString strFile;
	if (FileDlg.DoModal () != IDOK)
		return;

	POSITION pos = FileDlg.GetStartPosition();
	strFile = FileDlg.GetNextPathName(pos);
	m_pMainDib->Open(strFile);
	
	m_nWndWidth = m_pMainDib->GetWidth();
	m_nWndHeight= m_pMainDib->GetHeight();
	m_sFileName = strFile;

	m_rFaceRegion.left = m_rFaceRegion.right = m_rFaceRegion.top = m_rFaceRegion.bottom = 0;

	m_bLeftEyeOK = m_bRightEyeOK = m_bLeftNostrilOK = m_bRightNostrilOK =
	m_bLeftEyeLeftCornerOK = m_bLeftEyeRightCornerOK = m_bRightEyeLeftCornerOK = 
	m_bRightEyeRightCornerOK = m_bLeftMouthCornerOK = m_bRightMouthCornerOK = false;

	m_bMidMouthOK = m_bMidNoseOK = false;

	m_LeftEye = m_RightEye = m_LeftEyeLeftCorner = m_LeftEyeRightCorner = 
	m_LeftNostril = m_RightNostril = m_RightEyeLeftCorner = m_RightEyeRightCorner =
	m_LeftMouthCorner = m_RightMouthCorner = m_MidMouth = m_MidNose = CPoint(-1,-1);

	SetCursor(LoadCursor(NULL,IDC_WAIT));
	//获取像素的值
	LoadOriPixel(m_pMainDib);
	MakeBitMap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));	
}

////////////////////////////////////////////////////////////////////////////////
// 画图
////////////////////////////////////////////////////////////////////////////////
void CFaceDetectDlg::MyDraw()
{
	CRect rc;
	pDCShow->GetWindow()->GetClientRect(&rc);
	pDCShow->Rectangle(&rc);
	CDC dc;
	CBitmap *pOldBitmap;
	dc.CreateCompatibleDC(pDCShow);
	pOldBitmap=dc.SelectObject(m_pResMap);
	pDCShow->StretchBlt(0,0,m_nWndWidth,m_nWndHeight,&dc,0,0,m_nWndWidth,m_nWndHeight,SRCCOPY);
	dc.SelectObject(pOldBitmap);
	dc.DeleteDC();
}
