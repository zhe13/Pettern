// bwView.cpp : implementation of the CBwView class
//

#include "stdafx.h"
#include "bw.h"

#include "bwDoc.h"
#include "bwView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBwView

IMPLEMENT_DYNCREATE(CBwView, CView)

BEGIN_MESSAGE_MAP(CBwView, CView)
	//{{AFX_MSG_MAP(CBwView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_BLACK, OnBlack)
	ON_COMMAND(ID_WHITE, OnWhite)
	ON_COMMAND(ID_REG, OnReg)
	ON_COMMAND(ID_THREE, OnThree)
	ON_COMMAND(ID_TWO, OnTwo)
	ON_COMMAND(ID_ONE, OnOne)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBwView construction/destruction

CBwView::CBwView()
{
	// TODO: add construction code here
	
	m_find.bak=0;
	m_find.depth=6;
	m_find.searchend=51;
	start=FALSE;
	draw=FALSE;
	comw=FALSE;
	manw=FALSE;
	msg=FALSE;
	pass=FALSE;
	tie=FALSE;
	wrong=FALSE;
	think=FALSE;
	play=FALSE;
	pointx=-1;
	pointy=-1;
	ManChoice=BLACK;
	ComChoice=WHITE;
	m_find.ComChoice=WHITE;
	m_find.ManChoice=BLACK;
	ManTurn=FALSE;
	ComTurn=FALSE;
	m_black.LoadBitmap(IDB_BLACK);
	m_white.LoadBitmap(IDB_WHITE);
	m_board.LoadBitmap(IDB_BOARD);
	m_last.LoadBitmap(IDB_LAST);
}

CBwView::~CBwView()
{
}

BOOL CBwView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBwView drawing

void CBwView::OnDraw(CDC* pDC)
{
	CBwDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//初始化棋盘
	CDC deMemory;
	int i,j,WhiteNum,BlackNum;
	CString wmsg,bmsg;
	deMemory.CreateCompatibleDC(pDC);
	deMemory.SelectObject(&m_board);
	pDC->BitBlt(0,0,570,330,&deMemory,0,0,SRCCOPY);
	//刷新棋盘
	switch(m_find.depth){
	case 4:pDC->TextOut(375,107,"1");break;
	case 5:pDC->TextOut(375,107,"2");break;
	case 6:pDC->TextOut(375,107,"3");break;
	}
	if(!start) pDC->TextOut(375,135,"请选择先后手");
	deMemory.SelectObject(&m_black);
	for(i=0;i<8;i++)
		for(j=0;j<8;j++){
			if(m_find.board[i][j]==1)
				pDC->BitBlt(10+30*j,10+30*i,31,31,&deMemory,0,0,SRCCOPY);
		}

	deMemory.SelectObject(&m_white);
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(m_find.board[i][j]==-1)
				pDC->BitBlt(10+30*j,10+30*i,31,31,&deMemory,0,0,SRCCOPY);			
		}
	}
	if(ComChoice==1){
		deMemory.SelectObject(&m_black);
	}
	else deMemory.SelectObject(&m_white);
	if(draw){
		if(pointx>=0&&pointy>=0)
			pDC->BitBlt(10+30*pointy,10+30*pointx,31,31,&deMemory,0,0,SRCCOPY);
	}
	WhiteNum=m_find.CountWhite();
	wmsg.Format("%d",WhiteNum);
	BlackNum=m_find.CountBlack();
	bmsg.Format("%d",BlackNum);
	pDC->TextOut(400,20,bmsg);
	pDC->TextOut(400,53,wmsg);
	if(msg){
		if(manw) pDC->TextOut(375,135,"恭喜，你赢了             ");
		if(comw) pDC->TextOut(375,135,"你输了，下次努力	        ");
		if(tie) pDC->TextOut(375,135,"不错哦，平局              ");
		if(pass) pDC->TextOut(375,135,"Passed, 任意点鼠标左键继续");
		if(wrong) pDC->TextOut(375,135,"错误                    ");
		if(think) pDC->TextOut(375,135,"思考中……请稍后        ");
		if(play) pDC->TextOut(375,135,"请下棋                   ");
	}
	else pDC->TextOut(400,300,"                                                ");
	CString final;
	final.Format("%d",m_find.outcome);
	if(m_find.preview) pDC->TextOut(320,240,final);
	else pDC->TextOut(320,240,"                ");
	
}

/////////////////////////////////////////////////////////////////////////////
// CBwView printing

BOOL CBwView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	CClientDC dc(this);
	return DoPreparePrinting(pInfo);
}

void CBwView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBwView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBwView diagnostics

#ifdef _DEBUG
void CBwView::AssertValid() const
{
	CView::AssertValid();
}

void CBwView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBwDoc* CBwView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBwDoc)));
	return (CBwDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBwView message handlers

void CBwView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonDown(nFlags, point);
	int tb[8][8];
	CClientDC dc(this);
	CDC dcMem;
	int chessx,chessy;
	int WhiteNum,BlackNum;
	int i,j;
	for(i=0;i<8;i++)for(j=0;j<8;j++) tb[i][j]=m_find.board[i][j];
	WhiteNum=m_find.CountWhite();
	BlackNum=m_find.CountBlack();
	CPoint newpoint;
	if(ManTurn){
		chessx=(int)((point.y-10)/30);
		chessy=(int)((point.x-10)/30);
		if(m_find.search(tb,ManChoice)){
			if(m_find.decide(chessx,chessy,ManChoice)){
				ManTurn=FALSE;
				ComTurn=TRUE;
				m_find.SaveBoard(tb);	
				m_find.newboard(tb,chessx,chessy,ManChoice);
				for(i=0;i<8;i++)for(j=0;j<8;j++) m_find.board[i][j]=tb[i][j];
				OnDraw(&dc);
			}
			else{
				msg=TRUE;
				wrong=TRUE;
				OnDraw(&dc);
				wrong=FALSE;
				msg=FALSE;
			}
		}
		else{
			if(m_find.search(tb,ComChoice)){
				ManTurn=FALSE;
				ComTurn=TRUE;
				msg=TRUE;
				pass=TRUE;
				OnDraw(&dc);
				pass=FALSE;
				msg=FALSE;
			}
			else{
				ManTurn=FALSE;
				ComTurn=FALSE;
			}
		}
	}//ManTurn
	if(ComTurn){
		if(m_find.search(tb,ComChoice)){
			msg=TRUE;
			think=TRUE;
			OnDraw(&dc);
			m_find.select(ComChoice);
			think=FALSE;
			msg=FALSE;
			OnDraw(&dc);
			draw=TRUE;
			pointx=m_find.stepx;
			pointy=m_find.stepy;
			OnDraw(&dc);//画落子
			m_find.newboard(tb,pointx,pointy,ComChoice);
			for(i=0;i<8;i++)for(j=0;j<8;j++) m_find.board[i][j]=tb[i][j];
			double temp=1;
			OnDraw(&dc);//画新棋盘
			draw=FALSE;
			msg=TRUE;
			play=TRUE;
			OnDraw(&dc);
			play=FALSE;
			msg=FALSE;

			ManTurn=TRUE;
			ComTurn=FALSE;
			if((m_find.search(tb,ComChoice)==TRUE)&&(m_find.search(tb,ManChoice)==FALSE))
			{
				msg=TRUE;
				pass=TRUE;
				OnDraw(&dc);
				pass=FALSE;
				msg=FALSE;
			}
		}//if(m_find.search(tb,ComChoice))
	
		else{
			if(m_find.search(tb,ManChoice)){
				ManTurn=TRUE;
				ComTurn=FALSE;
				msg=TRUE;
				pass=TRUE;
				OnDraw(&dc);
				pass=FALSE;
				msg=FALSE;
			}
			else{
				ManTurn=FALSE;
				ComTurn=FALSE;
			}
		}
	}
	//
	if(!m_find.search(tb,ManChoice)&&!m_find.search(tb,ManChoice)){
		ManTurn=FALSE;
		ComTurn=FALSE;
	}
	if(ManTurn==FALSE&&ComTurn==FALSE&&start==TRUE){
		msg=TRUE;
		if(ComChoice==1){
			if(BlackNum-WhiteNum>0){
				comw=TRUE;
				OnDraw(&dc);
			}
			else if(BlackNum==WhiteNum){
				tie=TRUE;
				OnDraw(&dc);
			}
			else{
				manw=TRUE;
				OnDraw(&dc);
			}
		}
		else
		{
			if(BlackNum-WhiteNum<0){
				comw=TRUE;
				OnDraw(&dc);
			}
			else if(BlackNum==WhiteNum){
				tie=TRUE;
				OnDraw(&dc);
			}
			else{
				manw=TRUE;
				OnDraw(&dc);
			}
		}

	start=FALSE;
	}
}
void CBwView::OnBlack() 
{

	int i,j;
	CClientDC dc(this);
	for(i=0;i<8;i++) for(j=0;j<8;j++)
		m_find.board[i][j]=EMPTY;
	m_find.board[3][3]=WHITE;
	m_find.board[4][4]=WHITE;
	m_find.board[3][4]=BLACK;
	m_find.board[4][3]=BLACK;
	m_find.depth=6;
	m_find.preview=FALSE;
	m_find.bak=0;
	draw=FALSE;
	comw=FALSE;
	manw=FALSE;
	msg=FALSE;
	pass=FALSE;
	tie=FALSE;
	wrong=FALSE;
	think=FALSE;
	play=FALSE;
	pointx=-1;
	pointy=-1;
	ManChoice=BLACK;
	ComChoice=WHITE;
	m_find.ComChoice=WHITE;
	m_find.ManChoice=BLACK;
	OnDraw(&dc);
	ManTurn=TRUE;
	ComTurn=FALSE;
	start=TRUE;
	dc.TextOut(375,132,"请下棋                   ");
}

void CBwView::OnWhite() 
{
	// TODO: Add your command handler code here
	int i,j;
	CPoint point;
	point.x=0;point.y=0;
	CClientDC dc(this);
	for(i=0;i<8;i++) for(j=0;j<8;j++)
		m_find.board[i][j]=EMPTY;
	m_find.board[3][3]=WHITE;
	m_find.board[4][4]=WHITE;
	m_find.board[3][4]=BLACK;
	m_find.board[4][3]=BLACK;
	m_find.preview=FALSE;
	m_find.depth=6;
	draw=FALSE;
	comw=FALSE;
	manw=FALSE;
	msg=FALSE;
	pass=FALSE;
	tie=FALSE;
	wrong=FALSE;
	think=FALSE;
	play=FALSE;
	m_find.bak=0;
	pointx=-1;
	pointy=-1;
	ManChoice=WHITE;
	ComChoice=BLACK;
	m_find.ComChoice=BLACK;
	m_find.ManChoice=WHITE;
	OnDraw(&dc);
	ManTurn=FALSE;
	ComTurn=TRUE;
	start=TRUE;
	OnLButtonDown(1,point);	
}

void CBwView::OnReg() 
{
	// TODO: Add your command handler code here
	int i,j,bak=m_find.bak;
	CClientDC dc(this);
	if(bak>0){
		for(i=0;i<8;i++)for(j=0;j<8;j++)
			m_find.board[i][j]=m_find.save[bak][i][j];
		bak--;
		m_find.bak=bak;
		m_find.preview=FALSE;
		ManTurn=TRUE;
		OnDraw(&dc);
	}
}


void CBwView::OnThree() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	m_find.depth=7;
	m_find.searchend=51;
	dc.TextOut(375,107,"3");
}



void CBwView::OnTwo() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	m_find.depth=5;
	m_find.searchend=53;
	dc.TextOut(375,107,"2");
}

void CBwView::OnOne() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	m_find.depth=4;
	m_find.searchend=55;
	dc.TextOut(375,107,"1");
}
