// JiuG.cpp: implementation of the CJiuG class.

#include "stdafx.h"
#include "Jiugong.h"
#include "JiuG.h"
#include "math.h"//计算估价函数是会用到abs()，如果用错位数，则不用包含
#include "stdlib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJiuG::CJiuG()
{
	m_ndepth=100;//设置默认的深度为100，可以在程序中改动
}

CJiuG::~CJiuG()
{

}

/////////////////////////////////////////////////////////////////////
//左移
bool CJiuG::MoveLeft(JGState *src,JGState *result)
{
	int x,y,tempx,tempy;
	for(x=0;x<3;x++){
		for(y=0;y<3;y++){
			if(src->state[x][y]==0){
				tempx=x;
				tempy=y;
			}
		}
	}

	if(tempy==0)
		return false;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			result->state[i][j]=src->state[i][j];
		}
	}
	
	result->state[tempx][tempy] = src->state[tempx][tempy-1];
	result->state[tempx][tempy-1] = 0;
	result->curdistance=src->curdistance+1;
	result->prestate=src;
	result->nextstate=NULL;

	return true;
}

////////////////////////////////////////////////////////////////////
//右移
bool CJiuG::MoveRight(JGState *src,JGState *result)
{
	int x,y,tempx,tempy;
	for(x=0;x<3;x++){
		for(y=0;y<3;y++){
			if(src->state[x][y]==0){
				tempx=x;
				tempy=y;
			}
		}
	}

	if(tempy==2)
		return false;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			result->state[i][j]=src->state[i][j];
		}
	}

	result->state[tempx][tempy]=src->state[tempx][tempy+1];
	result->state[tempx][tempy+1]=0;
	result->curdistance=src->curdistance+1;
	result->prestate=src;
	result->nextstate=NULL;

	return true;
}

///////////////////////////////////////////////////////////////////
//上移，上面的左移，右移，下面的下移，结构一样
bool CJiuG::MoveUp(JGState *src,JGState *result)
{
	int x,y,tempx,tempy;
	//寻找空格位置
	for(x=0;x<3;x++){
		for(y=0;y<3;y++){
			if(src->state[x][y]==0){
				tempx=x;
				tempy=y;
			}
		}
	}

	//判断是否可移
	if(tempx==0)
		return false;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			result->state[i][j]=src->state[i][j];
		}
	}

	result->state[tempx][tempy]=src->state[tempx-1][tempy];
	result->state[tempx-1][tempy]=0;
	result->curdistance=src->curdistance+1;//深度加一
	result->prestate=src;//设置前趋节点
	result->nextstate=NULL;

	return true;
}

////////////////////////////////////////////////////////////////////
//下移
bool CJiuG::MoveDown(JGState *src,JGState *result)
{
	int x,y,tempx,tempy;
	for(x=0;x<3;x++){
		for(y=0;y<3;y++){
			if(src->state[x][y]==0){
				tempx=x;
				tempy=y;
			}
		}
	}

	if(tempx==2)
		return false;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			result->state[i][j]=src->state[i][j];
		}
	}

	result->state[tempx][tempy]=result->state[tempx+1][tempy];
	result->state[tempx+1][tempy]=0;
	result->curdistance=src->curdistance+1;
	result->prestate=src;
	result->nextstate=NULL;

	return true;
}

///////////////////////////////////////////////////////////////////
//比较两个状态是否相等
bool CJiuG::Compare(JGState *src1,JGState *src2)
{
	for(int i=0;i<=2;i++){
		for(int j=0;j<=2;j++){
			if(src1->state[i][j]!=src2->state[i][j])
				return false;
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////
//计算估价函数，采用了每一步移到正确的位置需要的步数
int CJiuG::ComputeFn(JGState *cur,JGState *dest)
{
	int xcur[9],ycur[9],xdest[9],ydest[9];//保存9个坐标
	int i,j;
	int result=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			xcur[cur->state[i][j]]=i;
			ycur[cur->state[i][j]]=j;
			xdest[dest->state[i][j]]=i;
			ydest[dest->state[i][j]]=j;
		}
	}

	for(i=1;i<9;i++){
		result=result+abs(xcur[i]-xdest[i])+abs(ycur[i]-ydest[i]);
	}

	return result;
	/*int result=0;//注释掉的部分是采用了错位数来计算
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(cur->state[i][j]!=dest->state[i][j])
				result++;
		}
	}

	return result;*/
}


///////////////////////////////////////////////////////////////////
//搜索最优解，这是程序的核心部分
bool CJiuG::Search()
{
	int MAXDEPTH=m_ndepth;
	FreeList(&OpenList);
	FreeList(&CloseList);
	FreeList(&ResultList);
	JGState *newstate,*pstart;
	int i,k;
	newstate=(JGState *)malloc(sizeof(JGState));
	CopyJG(&StateInit,newstate);
	newstate->curdistance=0;
	newstate->nextstate=NULL;
	newstate->prestate=NULL;
	pstart=newstate;
	curstep=pstart;
	//如果初始状态和末态相同，搜索成功退出
	if(Compare(&StateInit,&StateObj)==true){
		ResultList.AddTail((void *)newstate);
		return true;
	}
	
	//将起始结点加入Open表中
	OpenList.AddHead((void *)newstate);
	
	//搜索
	while(true){
		JGState *pmin;
		int nmin;
		int nindex=0;
		//Open表为空，失败退出
		if(OpenList.IsEmpty())
			return false;
		i=OpenList.GetCount();
		nmin=100000000;
		//搜索Open表中估计值最小的节点
		for(k=0;k<i;k++){
			JGState *ptemp;
			ptemp=(JGState *)OpenList.GetAt(OpenList.FindIndex(k));
			int ntemp=ptemp->curdistance+ComputeFn(ptemp,&StateObj);
			if(ntemp<nmin){
				nmin=ntemp;
				pmin=ptemp;
				nindex=k;
			}
		}
	
		//将估价函数最小的节点从Open表删除，加入到Close表中
		OpenList.RemoveAt(OpenList.FindIndex(nindex));
		CloseList.AddTail((void *)pmin);

		newstate=(JGState *)malloc(sizeof(JGState));

		//move to left，用了搜索深度控制。下面的右移，上移，下移程序结构相同
		//可以将相同的部分写成函数，我没有这样做
		if((MoveLeft(pmin,newstate)==true)&&(newstate->curdistance<=MAXDEPTH)){
			if((Compare(newstate,&StateObj)==false)){
				//不是目标节点，则看是否可以加入到Open表中
				bool inopen=false;
				bool inclose=false;
				JGState *ptemp;
				//检查是否在Open表中
				i=OpenList.GetCount();
				if(i==0)
					inopen=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)OpenList.GetAt(OpenList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inopen=true;
							if(ptemp->curdistance>newstate->curdistance)
								CopyJG(newstate,ptemp);
							break;
						}
					}
				}
				//检查是否在Close表中
				i=CloseList.GetCount();
				if(i==0)
					inclose=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)CloseList.GetAt(CloseList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inclose=true;
							break;
						}
					}
				}
				if((inopen==false)&&(inclose==false))
					OpenList.AddHead(newstate);
			}//end if
			else{
				//找到目标结点
				JGState *newstate1;
				ResultList.AddHead((void *)newstate);
				newstate=newstate->prestate;
				//回溯，得到ResultList
				while(newstate!=pstart){
					newstate1=(JGState *)malloc(sizeof(JGState));
					CopyJG(newstate,newstate1);
					ResultList.AddHead(newstate1);
					newstate=newstate->prestate;
				}
				newstate1=(JGState *)malloc(sizeof(JGState));
				CopyJG(newstate,newstate1);
				ResultList.AddHead(newstate1);
				return true;
			}//end else
		}//end if 
		else{
			free(newstate);
		}//end move left

		newstate=(JGState *)malloc(sizeof(JGState));

		//move to right
		if(MoveRight(pmin,newstate)==true&&(newstate->curdistance<=MAXDEPTH)){
			if((Compare(newstate,&StateObj)==false)){
				//不是目标节点，则看是否可以加入到Open表中
				bool inopen=false;
				bool inclose=false;
				JGState *ptemp;
				i=OpenList.GetCount();
				if(i==0)
					inopen=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)OpenList.GetAt(OpenList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inopen=true;
							if(ptemp->curdistance>newstate->curdistance)
								CopyJG(newstate,ptemp);
							break;
						}
					}
				}
				i=CloseList.GetCount();
				if(i==0)
					inclose=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)CloseList.GetAt(CloseList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inclose=true;
							break;
						}
					}
				}
				if((inopen==false)&&(inclose==false))
					OpenList.AddHead(newstate);
			}//end if
			else{
				//找到目标结点
				JGState *newstate1;
				ResultList.AddHead((void *)newstate);
				newstate=newstate->prestate;
				while(newstate!=pstart){
					newstate1=(JGState *)malloc(sizeof(JGState));
					CopyJG(newstate,newstate1);
					ResultList.AddHead(newstate1);
					newstate=newstate->prestate;
				}
				newstate1=(JGState *)malloc(sizeof(JGState));
				CopyJG(newstate,newstate1);
				ResultList.AddHead(newstate1);
				return true;
			}//end else
		}//end if 
		else{
			free(newstate);
		}//end move right

		newstate=(JGState *)malloc(sizeof(JGState));

		//move to up
		if(MoveUp(pmin,newstate)==true&&(newstate->curdistance<=MAXDEPTH)){
			if((Compare(newstate,&StateObj)==false)){
				//不是目标节点，则看是否可以加入到Open表中
				bool inopen=false;
				bool inclose=false;
				JGState *ptemp;
				i=OpenList.GetCount();
				if(i==0)
					inopen=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)OpenList.GetAt(OpenList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inopen=true;
							if(ptemp->curdistance>newstate->curdistance)
								CopyJG(newstate,ptemp);
							break;
						}
					}
				}
				i=CloseList.GetCount();
				if(i==0)
					inclose=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)CloseList.GetAt(CloseList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inclose=true;
							break;
						}
					}
				}
				if((inopen==false)&&(inclose==false))
					OpenList.AddHead(newstate);
			}//end if
			else{
				//找到目标结点
				JGState *newstate1;
				ResultList.AddHead((void *)newstate);
				newstate=newstate->prestate;
				while(newstate!=pstart){
					newstate1=(JGState *)malloc(sizeof(JGState));
					CopyJG(newstate,newstate1);
					ResultList.AddHead(newstate1);
					newstate=newstate->prestate;
				}
				newstate1=(JGState *)malloc(sizeof(JGState));
				CopyJG(newstate,newstate1);
				ResultList.AddHead(newstate1);
				return true;
			}//end else
		}//end if 
		else{
			free(newstate);
		}//end move up

		newstate=(JGState *)malloc(sizeof(JGState));

		//move to down
		if(MoveDown(pmin,newstate)==true&&(newstate->curdistance<=MAXDEPTH)){
			if((Compare(newstate,&StateObj)==false)){
				//不是目标节点，则看是否可以加入到Open表中
				bool inopen=false;
				bool inclose=false;
				JGState *ptemp;
				i=OpenList.GetCount();
				if(i==0)
					inopen=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)OpenList.GetAt(OpenList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inopen=true;
							if(ptemp->curdistance>newstate->curdistance)
								CopyJG(newstate,ptemp);
							break;
						}
					}
				}
				i=CloseList.GetCount();
				if(i==0)
					inclose=false;
				else{
					for(k=0;k<i;k++){
						ptemp=(JGState *)CloseList.GetAt(CloseList.FindIndex(k));
						if(Compare(newstate,ptemp)==true){
							inclose=true;
							break;
						}
					}
				}
				if((inopen==false)&&(inclose==false))
					OpenList.AddHead(newstate);
			}//end if
			else{
				//找到目标结点
				JGState *newstate1;
				ResultList.AddHead((void *)newstate);
				newstate=newstate->prestate;
				while(newstate!=pstart){
					newstate1=(JGState *)malloc(sizeof(JGState));
					CopyJG(newstate,newstate1);
					ResultList.AddHead(newstate1);
					newstate=newstate->prestate;
				}
				newstate1=(JGState *)malloc(sizeof(JGState));
				CopyJG(newstate,newstate1);
				ResultList.AddHead(newstate1);
				return true;
			}//end else
		}//end if 
		else{
			free(newstate);
		}//end move down
	}
}

///////////////////////////////////////////////////////////////////
//释放内存
void CJiuG::FreeList(CPtrList *list)
{
	if(list->IsEmpty())
		return;
	int i=list->GetCount();
	JGState *p;
	for(int j=0;j<i;j++){
		p=(JGState *)list->GetHead();
		list->RemoveHead();
		free(p);
	}
}

void CJiuG::CopyJG(JGState *src,JGState *dest)
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			dest->state[i][j]=src->state[i][j];
		}
	}
	dest->curdistance=src->curdistance;
	dest->prestate=src->prestate;
	dest->nextstate=src->nextstate;
}

//////////////////////////////////////////////////////////////////
//计算逆序奇偶性，以判断有无解，基于我对九宫问题解是否可达的证明
//返回0为偶，返回1为奇
int CJiuG::ComputeJO(JGState *jo)
{
	int result=0;
	int i,j;
	int k=0;
	int temp[8];
	//除去0，将其余8个数依次加入到数组中
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(jo->state[i][j]!=0){
				temp[k]=jo->state[i][j];
				k++;
			}
		}
	}
	//判断奇偶性
	for(i=0;i<7;i++){
		for(j=i+1;j<8;j++){
			if(temp[i]>temp[j])
				result++;
		}
	}

	result=result%2;
	return result;
}
