//patternView.cpp

#include "stdafx.h"
#include "pattern.h"

#include "patternDoc.h"
#include "patternView.h"
#include "InputDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include<windows.h>
#include<math.h>

#define startX 8  //模拟面板的X起点
#define startY 8  //模拟面板的Y起点
#define stepX 11  //X方向每格的长度
#define stepY 15  //Y方向每格的长度
int disable=0;


/////////////////////////////////////////////////////////////////////////////
// CPatternView

IMPLEMENT_DYNCREATE(CPatternView, CView)

BEGIN_MESSAGE_MAP(CPatternView, CView)
	//{{AFX_MSG_MAP(CPatternView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatternView construction/destruction

CPatternView::CPatternView()
{
	// TODO: add construction code here
	mouseDown=0;

	//初始化，使得每个点皆为白点
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			bitgraph[i][j]=0;

	//初始化，使得坐标序列中的点皆为空点
	mytime=0;
	for(i=0;i<100;i++){
		mypoint[i].x=-1;
		mypoint[i].y=-1;
	}

	mytime=0;
	curvalue=-1;
	mytezheng=(TEZHENG *)malloc(sizeof(TEZHENG));
	mytezheng->value=-1;
	mytezheng->lenth=0;
	mytezheng->lenth1=0;
	for(i=0;i<15;i++)
		mytezheng->VHDerection[i]=-1;
	mytezheng->decon=0;

	//打开保存模板特征量的文件
	if(cf.Open("mydata.dat",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite)==NULL){
		AfxMessageBox("打开文件失败，\n您最好退出程序");
	}
}

CPatternView::~CPatternView()
{
	cf.Close();
}

BOOL CPatternView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPatternView drawing

void CPatternView::OnDraw(CDC* pDC)
{
	CPatternDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//画整个系统的背景
	//Erase the background
	// Create a pruple brush.
	CBrush Brush (RGB (128, 0 , 0) );
	// Select the brush into the device context .
	CBrush* pOldBrush = pDC->SelectObject (&Brush);
	// Get the area that needs to be erased .
	CRect rcClip;
	pDC->GetClipBox (&rcClip);
	//Paint the area.
	pDC-> PatBlt (rcClip.left , rcClip.top , rcClip.Width ( ) , rcClip.Height( ) , PATCOPY );
	//Unselect brush out of device context .
	
	pDC->SelectObject (pOldBrush );

	//四个模拟位图按钮
	CBitmap bitmapstudy,bitmaprecognize,bitmapclear,bitmaphelp; // Sequence is important
    CDC dcMemory1,dcMemory2,dcMemory3,dcMemory4;

    bitmapstudy.LoadBitmap(IDB_BITMAP_STUDY);
    dcMemory1.CreateCompatibleDC(pDC);
    dcMemory1.SelectObject(&bitmapstudy);
    pDC->BitBlt(220, 20, 50, 20, &dcMemory1, 0, 0, SRCCOPY);

	bitmaprecognize.LoadBitmap(IDB_BITMAP_RECOGNIZE);
    dcMemory2.CreateCompatibleDC(pDC);
    dcMemory2.SelectObject(&bitmaprecognize);
    pDC->BitBlt(220, 60, 50, 20, &dcMemory2, 0, 0, SRCCOPY);

	bitmapclear.LoadBitmap(IDB_BITMAP_CLEAR);
    dcMemory3.CreateCompatibleDC(pDC);
    dcMemory3.SelectObject(&bitmapclear);
    pDC->BitBlt(220, 100, 50, 20, &dcMemory3, 0, 0, SRCCOPY);

	bitmaphelp.LoadBitmap(IDB_BITMAP_HELP);
    dcMemory4.CreateCompatibleDC(pDC);
    dcMemory4.SelectObject(&bitmaphelp);
    pDC->BitBlt(220,140, 50, 20, &dcMemory4, 0, 0, SRCCOPY);

	//画板
	CBrush BrushBoard (RGB (255, 255 , 255) );
	// Select the brush into the device context .
	pOldBrush = pDC->SelectObject (&BrushBoard);
	//Paint the area.
	pDC-> PatBlt (8,8,176,240, PATCOPY );
	//Unselect brush out of device context 
    pDC->SelectObject (pOldBrush );
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetTextAlign(TA_CENTER|TA_TOP);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(245,175,"请您尽量");
	pDC->TextOut(245,200,"写慢一点");
	pDC->TextOut(245,225,"  呵呵！");
}

/////////////////////////////////////////////////////////////////////////////
// CPatternView printing

BOOL CPatternView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPatternView diagnostics

#ifdef _DEBUG
void CPatternView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPatternDoc* CPatternView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatternDoc)));
	return (CPatternDoc*)m_pDocument;
}
#endif //_DEBUG

//接受新的数字类型，以加入模板文件中
void CPatternView::OnStudy(void)
{
	//输入数字值的对话框
	InputDialog inputdlg;
	cf.SeekToBegin();
	int nFileSize=cf.GetLength();
	int i=nFileSize/sizeof(TEZHENG);
	TEZHENG *temp;
	temp=(TEZHENG *)malloc(sizeof(TEZHENG));

	//计算当前画板中数字的特征值
	GetTeZheng();

	//首先判断当前的数字类型是否已经在模板中
	for(int j=0;j<i;j++){
		cf.Read((void *)temp,sizeof(TEZHENG));
		for(int k=0;k<15;k++){
			if(temp->VHDerection[k]!=mytezheng->VHDerection[k])
				break;
		}
		if((k==15)&&(temp->decon==mytezheng->decon)&&(temp->lenfirst==mytezheng->lenfirst)&&(temp->lenth1==mytezheng->lenth1)&&(temp->lenth==mytezheng->lenth)&&(temp->lenend==mytezheng->lenend)){
			char s[20];
			sprintf(s,"您输入的是：%d，数据已有",temp->value);
			AfxMessageBox(s);
			break;
		}
	}
	//说明该数字类型不在模板中
	if(j==i){
		if(inputdlg.DoModal()==IDOK){
			//判断数字输入对话框中的两个数字是否相同
			if(inputdlg.m_value1!=inputdlg.m_value2){
				AfxMessageBox("您的输入有误，\n请重新输入");
			}
			//相同，则将新的数字类型写入模板文件中
			else{
				GetTeZheng();
				try{
					mytezheng->value=inputdlg.m_value1;
					cf.SeekToEnd();
					cf.Write(&mytezheng->value,sizeof(signed char));
					cf.Write(mytezheng->VHDerection,sizeof(signed char)*15);
					cf.Write(&mytezheng->lenth1,sizeof(signed char));
					cf.Write(&mytezheng->lenth,sizeof(signed char));
					cf.Write(&mytezheng->decon,sizeof(signed char));
					cf.Write(&mytezheng->lenfirst,sizeof(signed char));
					cf.Write(&mytezheng->lenend,sizeof(signed char));
				}
				catch(CFileException *e){
					//Alert user to error
					e->Delete();
				}//end try-catch
			}//end if-else
		}//end if
	}//end if

	OnClear();

	return;
}

//识别功能
void CPatternView::OnRecognize(void)
{
	cf.SeekToBegin();
	int nFileSize=cf.GetLength();
	int i=nFileSize/sizeof(TEZHENG);
	TEZHENG *temp;
	temp=(TEZHENG *)malloc(sizeof(TEZHENG));
	//计算特征值
	GetTeZheng();

	//在模板文件中寻找，是否有与当前特征值相同的
	for(int j=0;j<i;j++){
		cf.Read((void *)temp,sizeof(TEZHENG));
		for(int k=0;k<15;k++){
			if(temp->VHDerection[k]!=mytezheng->VHDerection[k])
				break;
		}
		//找到识别结果
		if((k==15)&&(temp->decon==mytezheng->decon)&&(temp->lenfirst==mytezheng->lenfirst)&&(temp->lenth1==mytezheng->lenth1)&&(temp->lenth==mytezheng->lenth)&&(temp->lenend==mytezheng->lenend)){
			char s[20];
			sprintf(s,"您输入的是：%d",temp->value);
			AfxMessageBox(s);
			break;//搜索结束
		}
	}
	if(j==i){
		AfxMessageBox("抱歉，无法识别");
	}

	OnClear();

	return;
}

//清空画板
void CPatternView::OnClear(void)
{
	CDC *pDC=GetDC();

	CBrush BrushBoard (RGB (255, 255 , 255) );
	CBrush pOldBrush;
	pDC-> PatBlt (8,8,176,240, PATCOPY );

	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			bitgraph[i][j]=0;

	mouseDown=0;
	mytime=0;
	for(i=0;i<100;i++){
		mypoint[i].x=-1;
		mypoint[i].y=-1;
	}
	
	curvalue=-1;
	mytezheng->value=-1;
	mytezheng->lenth=0;
	mytezheng->lenth1=0;
	for(i=0;i<15;i++)
		mytezheng->VHDerection[i]=-1;
	mytezheng->decon=0;

	return;
}

void CPatternView::OnMyHelp(void)
{
	return;
}

///////////////////////////////////////////////////////////////////////////
//从输入的序列钟提取特征
void CPatternView::GetTeZheng()
{
	int p,q;
	int i=0;
	//从第一个点到最后一个点
	for(int j=0;j<mytime-1;j++){
		if(i==0){
			mytezheng->lenth1++;
		}
		if(i>=13){
			AfxMessageBox("内存溢出，呵呵",NULL,NULL);
			return;
		}
		
		//判断两个相邻点的距离
		p=(mypoint[j+1].x-mypoint[j].x)*(mypoint[j+1].x-mypoint[j].x);
		q=(mypoint[j+1].y-mypoint[j].y)*(mypoint[j+1].y-mypoint[j].y);
		//如果不是8连接，则为断裂点或者是写的太快
		if((p>1)||(q>1)){
			mytezheng->decon=1;
			j++;
			i++;
			if(j+1>mytime-1){
				AfxMessageBox("您可能写得太快了，呵呵",NULL,NULL);
				return;
			}
			if(mypoint[j+1].x>mypoint[j].x)
				mytezheng->VHDerection[i]=1;
			else if(mypoint[j+1].y>mypoint[j].y)
				mytezheng->VHDerection[i]=2;
			else if(mypoint[j+1].x<mypoint[j].x)
				mytezheng->VHDerection[i]=3;
			else
				mytezheng->VHDerection[i]=4;
				
			mytezheng->lenth=1;	
		}

		//尽量保持目前的方向
		else{
			if(j==0){
				if(mypoint[1].x>mypoint[0].x)
					mytezheng->VHDerection[0]=1;
				else if(mypoint[1].y>mypoint[0].y)
					mytezheng->VHDerection[0]=2;
				else if(mypoint[1].x<mypoint[0].x)
					mytezheng->VHDerection[0]=3;
				else
					mytezheng->VHDerection[0]=4;
				
				mytezheng->lenth=1;
			}//end if
			else{
				switch(mytezheng->VHDerection[i]){
				case 1:
					if(mypoint[j+1].x<=mypoint[j].x){
						i++;
						mytezheng->lenth=1;
						if(mypoint[j+1].y>mypoint[j].y)
							mytezheng->VHDerection[i]=2;
						else if(mypoint[j+1].y<mypoint[j].y)
							mytezheng->VHDerection[i]=4;
						else
							mytezheng->VHDerection[i]=3;
					}
					else
						mytezheng->lenth++;
					break;
				case 2:
					if(mypoint[j+1].y<=mypoint[j].y){
						i++;
						mytezheng->lenth=1;
						if(mypoint[j+1].x<mypoint[j].x)
							mytezheng->VHDerection[i]=3;
						else if(mypoint[j+1].x>mypoint[j].x)
							mytezheng->VHDerection[i]=1;
						else
							mytezheng->VHDerection[i]=4;
					}
					else
						mytezheng->lenth++;
					break;
				case 3:
					if(mypoint[j+1].x>=mypoint[j].x){
						i++;
						mytezheng->lenth=1;
						if(mypoint[j+1].y<mypoint[j].y)
							mytezheng->VHDerection[i]=4;
						else if(mypoint[j+1].y>mypoint[j].y)
							mytezheng->VHDerection[i]=2;
						else
							mytezheng->VHDerection[i]=1;
					}
					else
						mytezheng->lenth++;
					break;
				case 4:
					if(mypoint[j+1].y>=mypoint[j].y){
						i++;
						mytezheng->lenth=1;
						if(mypoint[j+1].x>mypoint[j].x)
							mytezheng->VHDerection[i]=1;
						else if(mypoint[j+1].x<mypoint[j].x)
							mytezheng->VHDerection[i]=3;
						else
							mytezheng->VHDerection[i]=2;
					}
					else
						mytezheng->lenth++;
					break;
				default:
					break;
				}//end switch
			}//end else
		}//end else
	}//end for
	for(p=0;p<4;p++){
		for(q=p+1;q<mytime;q++){
			if(mypoint[p]==mypoint[q])
				break;
		}
		if(q<mytime)
			break;
	}
	if(p>=4)
		mytezheng->lenfirst=2;
	else
		mytezheng->lenfirst=1;

	for(p=mytime-1;p>mytime-6;p--){
		for(q=p-1;q>=0;q--){
			if(mypoint[p]==mypoint[q])
				break;
		}
		if(q>=0)
			break;
	}
	if(p<=mytime-6)
		mytezheng->lenend=2;
	else
		mytezheng->lenend=1;

	if((mytezheng->lenth)>0&&(mytezheng->lenth)<=4)
		mytezheng->lenth=1;
	else
		mytezheng->lenth=2;

	if(mytezheng->lenth1>=4)
		mytezheng->lenth1=2;
	else
		mytezheng->lenth1=1;
}//end fuction GetTeZheng()


/////////////////////////////////////////////////////////////////////////////
// CPatternView message handlers
//模拟按钮事件
//通过判断鼠标左键按下事件发生在哪个区域来判断该触发哪个事情
void CPatternView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	mouseDown=1;
	
	if((point.x>=220)&&(point.x<270)&&(point.y>=20)&&(point.y<40)){
		OnStudy();
	}

	if((point.x>=220)&&(point.x<270)&&(point.y>=60)&&(point.y<80)){
		OnRecognize();
	}

	if((point.x>=220)&&(point.x<270)&&(point.y>=100)&&(point.y<120)){
		OnClear();
	}

	if((point.x>=220)&&(point.x<270)&&(point.y>=140)&&(point.y<160)){
		OnMyHelp();
	}

	CView::OnLButtonDown(nFlags, point);
}

//鼠标移动事件，模拟手写笔输入
void CPatternView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDC *pDC=GetDC();
	CRgn Rgn;

	//限制在输入区域的范围内
	Rgn.CreateRectRgn(startX,startY,startX+stepX*16-1,startY+stepY*16-1);
	pDC->SelectClipRgn(&Rgn);
	if((point.x>=startX)&&(point.x<startX+stepX*16)&&(point.y>=startY)&&(point.y<startY+stepY*16)){
		HCURSOR m_HCross;
		m_HCross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);
		::SetCursor(m_HCross);
	}
	int i=(point.x-startX)/stepX;
	int j=(point.y-startY)/stepY;
	if((mouseDown==1)&&(point.x>=startX)&&(point.x<startX+stepX*16)&&(point.y>=startY)&&(point.y<startY+stepY*16)){
		CBrush Brush (RGB (0, 0 , 0) );
		// Select the brush into the device context .
		CBrush* pOldBrush = pDC->SelectObject (&Brush);
		pDC->Ellipse(point.x-6,point.y-6,point.x+6,point.y+6);
		pDC->SelectObject (pOldBrush );
		//保存数据
	
		if(mytime>=100){
			AfxMessageBox("内存溢出(画图时)",NULL,NULL);
			OnClear();
		}

		if(mytime==0){
			mypoint[mytime].x=i;
			mypoint[mytime].y=j;
			oldpoint=mypoint[mytime];
			mytime++;
		}
		//在输入过程中动态的去除直角点
		else{
			if((i!=oldpoint.x)||(j!=oldpoint.y)){
				int k,n;
				if(mytime<2){
					k=0;
					n=0;
				}
				else{
					k=(i-mypoint[mytime-2].x)*(i-mypoint[mytime-2].x);
					n=(j-mypoint[mytime-2].y)*(j-mypoint[mytime-2].y);
				}
				if((k==1)&&(n==1)){
					mypoint[mytime-1].x=i;
					mypoint[mytime-1].y=j;
					oldpoint=mypoint[mytime-1];
				}
				//disable=1;
				else{
					mypoint[mytime].x=i;
					mypoint[mytime].y=j;
					oldpoint=mypoint[mytime];
					mytime++;
				}
			}
		}
		bitgraph[i][j]=1;
	}

	CView::OnMouseMove(nFlags, point);
}

//鼠标左键抬起
void CPatternView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//设置mouseDown为false
	mouseDown=0;
	CView::OnLButtonUp(nFlags, point);
}
