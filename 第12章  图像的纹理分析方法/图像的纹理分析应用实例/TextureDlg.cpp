// TextureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Texture.h"
#include "TextureDlg.h"
#include "AddSampleDlg.h"
#include "nrutil.h"

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
// CTextureDlg dialog

CTextureDlg::CTextureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureDlg)
	m_dCorrelation = 0.0;
	m_dEnergy = 0.0;
	m_dEntropy = 0.0;
	m_dInertiaQuadrature = 0.0;
	m_dLocalCalm = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTextureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureDlg)
	DDX_Text(pDX, IDC_EDIT_CORRELATION, m_dCorrelation);
	DDX_Text(pDX, IDC_EDIT_ENERGY, m_dEnergy);
	DDX_Text(pDX, IDC_EDIT_ENTROPY, m_dEntropy);
	DDX_Text(pDX, IDC_EDIT_INERTIA_QUADRATURE, m_dInertiaQuadrature);
	DDX_Text(pDX, IDC_EDIT_LOCAL_CALM, m_dLocalCalm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTextureDlg, CDialog)
	//{{AFX_MSG_MAP(CTextureDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN_FILE, OnBtnOpenFile)
	ON_BN_CLICKED(IDC_BTN_COMPUTE_TEXTURE, OnBtnComputeTexture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureDlg message handlers

BOOL CTextureDlg::OnInitDialog()
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
	CWnd *pWnd0= GetDlgItem(IDC_PIC);
	pDCShow = pWnd0->GetDC();

	m_pResMap = NULL;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTextureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTextureDlg::OnPaint() 
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
HCURSOR CTextureDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////
// 建立一个内存位图
void CTextureDlg::MakeBitmap()
{
	CClientDC ClientDC(pDCShow->GetWindow());
	if(m_pResMap!=NULL) delete m_pResMap;

	m_pResMap=new CBitmap();
	m_pResMap->CreateCompatibleBitmap(&ClientDC,m_grayShow.ImageWidth,m_grayShow.ImageHeight);

	CDC  dc;
	dc.CreateCompatibleDC(&ClientDC);
	dc.SelectObject(m_pResMap);

	for(int i=0; i<m_grayShow.ImageHeight; i++)
		for(int j=0; j<m_grayShow.ImageWidth; j++)
			dc.SetPixelV(j,i,RGB(m_grayShow.m_tResPixelArray[i][j].rgbRed,m_grayShow.m_tResPixelArray[i][j].rgbGreen,m_grayShow.m_tResPixelArray[i][j].rgbBlue));

	dc.DeleteDC();

	MyDraw();
}

///////////////////////////////////////////////////////////////////////////////////
// 画图
void CTextureDlg::MyDraw()
{
	CRect rc;
	pDCShow->GetWindow()->GetClientRect(&rc);
	pDCShow->Rectangle(&rc);
	CDC dc;
	CBitmap *pOldBitmap;
	dc.CreateCompatibleDC(pDCShow);
	pOldBitmap=dc.SelectObject(m_pResMap);
	pDCShow->StretchBlt(0,0,m_grayShow.ImageWidth,m_grayShow.ImageHeight,&dc,0,0,m_grayShow.ImageWidth,m_grayShow.ImageHeight,SRCCOPY);
	dc.SelectObject(pOldBitmap);
	dc.DeleteDC();
}

/////////////////////////////////////////////////////////////////////////////////////
// 打开文件
void CTextureDlg::OnBtnOpenFile() 
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
	m_grayShow.LoadImage(strFile);
	
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	//获取像素的值
	MakeBitmap();
	SetCursor(LoadCursor(NULL,IDC_ARROW));	
}

////////////////////////////////////////////////////////////////////////////////////
// 计算纹理特征
void CTextureDlg::OnBtnComputeTexture() 
{
	double dEnergy			  = 0.0;
	double dEntropy			  = 0.0;
	double dInertiaQuadrature = 0.0;
	double dLocalCalm		  = 0.0;
	double dCorrelation		  = 0.0;
	double dEnergy1			  = 0.0;
	double dEntropy1		  = 0.0;
	double dInertiaQuadrature1= 0.0;
	double dLocalCalm1		  = 0.0;
	double dCorrelation1	  = 0.0;
	unsigned char** arLocalImage;
	arLocalImage = cmatrix(0, m_grayShow.FilterWindowWidth-1, 0, m_grayShow.FilterWindowWidth-1);
	int rolltimeH = m_grayShow.ImageHeight/m_grayShow.FilterWindowWidth;
	int rolltimeW = m_grayShow.ImageWidth /m_grayShow.FilterWindowWidth;
	int i,j;
	int p,q;

	//将图像分成若干个窗口，计算其纹理均值
	for(i=0; i< rolltimeH; i++)
	{
		for(j=0; j<rolltimeW; j++)
		{
			//首先赋值给子窗口
			for(p=0; p<m_grayShow.FilterWindowWidth; p++)
			{
				for(q=0; q<m_grayShow.FilterWindowWidth; q++)
				{
					arLocalImage[p][q] = m_grayShow.ImageArray[i*m_grayShow.FilterWindowWidth+p][j*m_grayShow.FilterWindowWidth+q];
				}
			}
			m_grayShow.ComputeMatrix(arLocalImage, m_grayShow.FilterWindowWidth);
			m_grayShow.ComputeFeature(dEnergy1, dEntropy1, dInertiaQuadrature1, dCorrelation1, dLocalCalm1, m_grayShow.PMatrixH, m_grayShow.GrayLayerNum);
			dEnergy              += dEnergy1;
			dEntropy             += dEntropy1;
			dInertiaQuadrature   += dInertiaQuadrature1;
			dCorrelation         += dCorrelation1;
			dLocalCalm           += dLocalCalm1;
		}
	}
	dEnergy              /= (rolltimeH*rolltimeW);
	dEntropy             /= (rolltimeH*rolltimeW);
	dInertiaQuadrature   /= (rolltimeH*rolltimeW);
	dCorrelation         /= (rolltimeH*rolltimeW);
	dLocalCalm           /= (rolltimeH*rolltimeW);
	m_dEnergy			 =  dEnergy;
	m_dEntropy			 =  dEntropy;
	m_dInertiaQuadrature =  dInertiaQuadrature;
	m_dCorrelation		 =  dCorrelation;
	m_dLocalCalm		 =  dLocalCalm;
	UpdateData(false);
}
