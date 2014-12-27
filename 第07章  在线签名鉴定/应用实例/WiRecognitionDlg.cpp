// WiRecognitionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WiRecognition.h"
#include "WiRecognitionDlg.h"
#include "dtwrecoge.h"
#include "movement.h"
#include "dih.h"

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
// CWiRecognitionDlg dialog

CWiRecognitionDlg::CWiRecognitionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWiRecognitionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWiRecognitionDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	numOfTrain = 0;
	numOfTest = 0;
	currTrain = 0;
	currTest = 0;
	pressPos = 0;
	m_TestTrain = 0;
}

void CWiRecognitionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWiRecognitionDlg)
	DDX_Control(pDX, IDC_SCROLLBAR1, m_ctrlScroll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWiRecognitionDlg, CDialog)
	//{{AFX_MSG_MAP(CWiRecognitionDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_INPUT_TRAIN, OnInputTrain)
 	ON_BN_CLICKED(IDC_SHOW1, OnShow1)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_INPUT_TEST, OnInputTest)
	ON_BN_CLICKED(IDC_SHOW2, OnShow2)
	ON_WM_HSCROLL()
 	ON_BN_CLICKED(IDC_GENTEMP, OnGentemp)
	ON_BN_CLICKED(IDC_RECOGNITION, OnRecognition)
	ON_BN_CLICKED(IDC_SAVE_TEMP, OnSaveTemp)
	ON_BN_CLICKED(IDC_LOAD_TEMP, OnLoadTemp)
	ON_CBN_SELCHANGE(IDC_METHOD, OnSelchangeMethod)
	ON_BN_CLICKED(IDC_RADIO_TEST, OnRadioTest)
	ON_BN_CLICKED(IDC_RADIO_TRAIN, OnRadioTrain)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWiRecognitionDlg message handlers

BOOL CWiRecognitionDlg::OnInitDialog()
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
	m_ctrlScroll.SetScrollRange(0,RAWDATADIM);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWiRecognitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWiRecognitionDlg::OnPaint() 
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
HCURSOR CWiRecognitionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWiRecognitionDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	OnOK();
	DestroyWindow();
	
}

void CWiRecognitionDlg::OnInputTrain() 
{
	// TODO: Add your control notification handler code here

	wi.DelSampleSetPath (0);

	CAddSampleDlg FileDlg(TRUE, "", NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, 
		"TextFiles (*.pnt)|*.pnt|All Files(*.*)|*.*||",
		AfxGetMainWnd());

	if (FileDlg.DoModal () != IDOK)
		return;

	CString strFile;
	CString strInfo;
	POSITION pos = FileDlg.GetStartPosition();
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	pEdit->SetSel(0,-1);
	pEdit->ReplaceSel("");
	while( pos ) 
	{
		strFile =FileDlg.GetNextPathName( pos );//获取文件名
		wi.AddSampleSetPath (strFile, 0);
		strInfo = strFile+"\r\n";
		pEdit->SetSel(-1,-1);
		pEdit->ReplaceSel(strInfo);
		//pEdit->SetWindowText(strInfo);
	}	
	numOfTrain = wi.trainSetDataFilePath.GetSize();
	currTrain = 0;

	wi.RetrieveSample(&wi.trainSetDataFilePath,&wi.trainSampleArray);
	wi.PreProcSample(&wi.trainSampleArray,0);
	wi.GenVector(&wi.trainSampleArray);
	wi.GenVQVector(&wi.trainSampleArray);
	
}

void CWiRecognitionDlg::OnShow1() 
{
	// TODO: Add your control notification handler code here
	CString strTitle;
	CWnd *pWnd = (CWnd *)GetDlgItem(IDC_PICTURE1);
	HWND hWnd = pWnd->m_hWnd;
	HDC hDC = ::GetDC(hWnd);
	if(m_TestTrain == 1)
	{
		if(numOfTrain== 0)
			return;
		CWi::Sample* s =(CWi::Sample*)wi.trainSampleArray.GetAt(currTrain);
		DrawPicture(s,hDC);
		strTitle.Format("%s","笔迹鉴别");
		strTitle = strTitle+" "+"["+wi.trainSetDataFilePath.GetAt(currTrain)+"]";
		SetWindowText(strTitle);
	}
	else
	{	
		if(numOfTest == 0)
			return;
		CWi::Sample* s =(CWi::Sample*)wi.testSampleArray.GetAt(currTest);
		DrawPicture(s,hDC);
		strTitle.Format("%s","笔迹鉴别");
		strTitle = strTitle+" "+"["+wi.testSetDataFilePath.GetAt(currTest)+"]";
		SetWindowText(strTitle);
	}

}

void CWiRecognitionDlg::DrawPicture(CWi::Sample* s,HDC hDC)
{
	if(s == NULL)
		return;
	int i,j;
	for(i = 0; i<IMAGEWIDTH;i++)
		for(j=0;j<IMAGEHEIGHT;j++){
			::SetPixel(hDC,i,j,RGB(s->imgPixel[i][j],s->imgPixel[i][j],s->imgPixel[i][j]));

		}
}

void CWiRecognitionDlg::OnPrev() 
{
	// TODO: Add your control notification handler code here
	if(m_TestTrain == 1)
	{
		if(currTrain>=1)
			currTrain--;
		else 
			currTrain = 0;
	}
	else
	{
		if(currTest>=1)
			currTest--;
		else 
			currTest = 0;
	}
	OnShow1();
	OnShow2();
}

void CWiRecognitionDlg::OnNext() 
{
	// TODO: Add your control notification handler code here
	if(m_TestTrain == 1)
	{
		currTrain++;
		if(currTrain >= numOfTrain)
			currTrain = numOfTrain-1;
	}
	else
	{
		currTest++;
		if(currTest >= numOfTest)
			currTest = numOfTest-1;
	}
	OnShow1();
	OnShow2();
}

void CWiRecognitionDlg::OnInputTest() 
{
	// TODO: Add your control notification handler code here
	
	wi.DelSampleSetPath (1);

	CAddSampleDlg FileDlg(TRUE, "", NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, 
		"TextFiles (*.pnt)|*.pnt|All Files(*.*)|*.*||",
		AfxGetMainWnd());

	if (FileDlg.DoModal () != IDOK)
		return;

	CString strFile,strInfo;
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
	pEdit->SetSel(0,-1);
	pEdit->ReplaceSel("");
	POSITION pos = FileDlg.GetStartPosition();
	while( pos ) 
	{
		strFile =FileDlg.GetNextPathName( pos );//获取文件名
		wi.AddSampleSetPath (strFile, 1);		//添加测试样本集
		strInfo = strFile+"\r\n";
		pEdit->SetSel(-1,-1);
		pEdit->ReplaceSel(strInfo);

	}	
	numOfTest = wi.testSetDataFilePath.GetSize();
	currTest = 0;
	wi.RetrieveSample(&wi.testSetDataFilePath,&wi.testSampleArray);
	wi.PreProcSample(&wi.testSampleArray,0);
	wi.GenVector(&wi.testSampleArray);
	wi.GenVQVector(&wi.testSampleArray);
}

void CWiRecognitionDlg::OnShow2() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWnd = (CWnd *)GetDlgItem(IDC_PICTURE2);
	HWND hWnd = pWnd->m_hWnd;
	HDC hDC = ::GetDC(hWnd);
	if(m_TestTrain == 1)
	{
		if(numOfTrain == 0)
			return;
		CWi::Sample* s =(CWi::Sample*)wi.trainSampleArray.GetAt(currTrain);
		DrawPress(s,hDC);
	}
	else
	{
		if(numOfTest == 0)
			return;
		CWi::Sample* s =(CWi::Sample*)wi.testSampleArray.GetAt(currTest);
		DrawPress(s,hDC);
	}

	
}

void CWiRecognitionDlg::DrawPress(CWi::Sample *s,HDC hDC)
{
	int i,j,begin;
	
	if(s == NULL)
		return;
	if(pressPos>RAWDATADIM-IMAGEWIDTH)
		begin = RAWDATADIM-IMAGEWIDTH;
	else
		begin = pressPos;
	int num;
	int *pos =(int *)malloc(sizeof(int)*s->effectDataNum);
	num = wi.WaveCrest(s->pressTotal2,s->pressTotal,pos,s->effectDataNum,5);
	for(i = 0;i<IMAGEWIDTH;i++)
	{
		for(j=0;j<128;j++)
		{	
			if(((int)s->pressA[begin+i]-80)/2 == j)
				::SetPixel(hDC,i,IMAGEHEIGHT-j,RGB(255,0,0));
			else if(((int)s->pressB[begin+i]-80)/2 == j)
				::SetPixel(hDC,i,IMAGEHEIGHT-j,RGB(0,255,0));
			else if(((int)s->pressC[begin+i]-80)/2 == j)
				::SetPixel(hDC,i,IMAGEHEIGHT-j,RGB(0,0,255));
			else if(((int)s->pressTotal2[begin+i]-20)/2 == j)
			{
				::SetPixel(hDC,i,IMAGEHEIGHT-j,RGB(0,0,0));
				for(int t=0;t<num;t++)
				{
					if(pos[t]==begin+i)
						SetPixel(hDC,i,IMAGEHEIGHT-j,RGB(255,0,0));
				}

			}
			else
				::SetPixel(hDC,i,IMAGEHEIGHT-j,RGB(255,255,255));
			
		}

	}

}

void CWiRecognitionDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	int ScrollPos=pScrollBar->GetScrollPos();

	switch( nSBCode ){
		case SB_LINELEFT:
			ScrollPos -= 2;
			break;
		case SB_LINERIGHT:
			ScrollPos+= 2;
			break;
		case SB_PAGELEFT:
			ScrollPos -= IMAGEWIDTH;
			break;	
		case SB_PAGERIGHT:
			ScrollPos += IMAGEWIDTH;
			break;	
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			if(nPos % 2)
				++nPos;
			ScrollPos = nPos;
		break;
	
	}
	
	if(ScrollPos < 0 )
		 ScrollPos = 0;
	if( ScrollPos> RAWDATADIM )
		 ScrollPos = RAWDATADIM;

	pressPos = ScrollPos;
	pScrollBar->SetScrollPos((int)ScrollPos);  
	OnShow2();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CWiRecognitionDlg::OnGentemp() 
{
	// TODO: Add your control notification handler code here
	if(m_Method == 0)
		wi.GenTemplatePress();
	else if(m_Method == 1)
		wi.GenTemplateXpos();
	else if(m_Method == 2)
		wi.GenTemplateYpos();
	else if(m_Method == 3)
		wi.GenTemplateXY();
	else if(m_Method == 4)
		wi.OnMovement();
	else if(m_Method == 5)
		wi.OnDirection();
	else if(m_Method == 6)
		wi.GenTemplateVector();
	else if(m_Method == 7)
		wi.GenVQTemplate();
	CString msg;
	msg.Format("threhold: %f",wi.threshold);
	MessageBox(msg);
}

void CWiRecognitionDlg::OnRecognition() 
{
	// TODO: Add your control notification handler code here
	double retval;
	CString msg,strFile;
	double distance  = 0.0;
	int num = wi.testSetDataFilePath.GetSize();
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
	pEdit->SetSel(0,-1);
	pEdit->ReplaceSel("");

	for(int i = 0;i<num;i++)
	{
		if(m_Method == 0)
			retval = wi.RecogTemplatePress(&distance,i);
		else if(m_Method == 1)
			retval = wi.RecogTemplateXpos(&distance,i);
		else if(m_Method == 2)
			retval = wi.RecogTemplateYpos(&distance,i);
		else if(m_Method == 3)
			retval = wi.RecogTemplateXY(&distance,i);
		else if(m_Method == 4)
			retval = wi.RecogMovement(&distance,i);
		else if(m_Method == 5)
			retval = wi.RegDih(&distance,i);
		else if(m_Method == 6)
			retval = wi.RecogTemplateVec(&distance,i);
		else if(m_Method == 7)
			retval = wi.RecogHMM(&distance, i);

		strFile = wi.testSetDataFilePath.GetAt(i);
		if(retval == -1)
		{
			msg.Format("distance=%f Fail!   ",distance);
			msg+=strFile;
			msg+="\r\n";
			pEdit->SetSel(-1,-1);
			pEdit->ReplaceSel(msg);
   
		}
		else if(retval == 1)
		{
			msg.Format("distance=%f Success!",distance);
			msg+=strFile;
			msg+="\r\n";
			pEdit->SetSel(-1,-1);
			pEdit->ReplaceSel(msg);

		}
	
	}
}

void CWiRecognitionDlg::OnSaveTemp() 
{
	// TODO: Add your control notification handler code here
	CFileDialog *dlg;	     	//保存文件对话框
	dlg= new CFileDialog(FALSE,"tmp","*.tmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Template Files(*.tmp)|*.tmp|All Files(*.*)|*.*||");
	char SaveAsName[256];
	if ( dlg->DoModal()==IDOK)
	{				
		strncpy(SaveAsName,dlg->GetPathName(),strlen(dlg->GetPathName()));
		SaveAsName[strlen(dlg->GetPathName())]=0;

		if(m_Method == 0)
			wi.SaveTemplatePress(SaveAsName);
		else if(m_Method == 1)
			wi.SaveTemplateXpos(SaveAsName);
		else if(m_Method == 2)
			wi.SaveTemplateYpos(SaveAsName);
		else if(m_Method == 3)
			wi.SaveTemplateXY(SaveAsName);
		else if(m_Method == 4)
			wi.SaveMovement(SaveAsName);
		else if(m_Method == 5)
			wi.SaveDih(SaveAsName);
		else if(m_Method == 6)
			wi.SaveTemplateVec(SaveAsName);
		else if(m_Method == 7)
			wi.SaveHMM(SaveAsName);
		
	}
}

void CWiRecognitionDlg::OnLoadTemp() 
{
	// TODO: Add your control notification handler code here
	CFileDialog *dlg;	//打开文件对话框
	dlg= new CFileDialog(TRUE,"tmp","*.tmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Template Files(*.tmp)|*.tmp|All Files(*.*)|*.*||");
 	char OpenName[256];
	int retval;
 	if ( dlg->DoModal()==IDOK)
	{				
		strncpy(OpenName,dlg->GetPathName(),strlen(dlg->GetPathName()));
		OpenName[strlen(dlg->GetPathName())]=0;

		if(m_Method == 0)
			retval = wi.LoadTemplatePress(OpenName);
		else if(m_Method == 1)
			retval = wi.LoadTemplateXpos(OpenName);
		else if(m_Method == 2)
			retval = wi.LoadTemplateYpos(OpenName);
		else if(m_Method == 3)
			retval = wi.LoadTemplateXY(OpenName);
		else if(m_Method == 4)
			retval = wi.LoadMovement(OpenName);
		else if(m_Method == 5)
			retval = wi.LoadDih(OpenName);
		else if(m_Method == 6)
			retval = wi.LoadTemplateVec(OpenName);
		else if(m_Method == 7)
			retval = wi.LoadHMM(OpenName);
	}
	
	if(retval == -1)
		MessageBox("Load Template Error!");
}

void CWiRecognitionDlg::OnSelchangeMethod() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_METHOD);
	m_Method = pBox->GetCurSel();
	
}


void CWiRecognitionDlg::OnRadioTest() 
{
	// TODO: Add your control notification handler code here
	m_TestTrain = 0;
	OnShow1();
	OnShow2();
}

void CWiRecognitionDlg::OnRadioTrain() 
{
	// TODO: Add your control notification handler code here
	m_TestTrain = 1;
	OnShow1();
	OnShow2();
}
