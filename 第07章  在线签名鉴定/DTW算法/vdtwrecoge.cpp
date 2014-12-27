/*vdtwrecoge.c****************************************************************/

#include "vdtwrecoge.h"
#include "math.h"
double vdistance[DTWMAXNUM][DTWMAXNUM]; /*保存距离*/
double vdtwpath[DTWMAXNUM][DTWMAXNUM]; /*保存路径*/

/*****************************************************************************/
/* VectorAdd(mvector *A,mvector *B,mvector *C)
/* 向量加法，结果存放在C中
/*****************************************************************************/
void VectorAdd(mvector *A,mvector *B,mvector *C)
{
	if(A->num != B->num)
		return;
	int dim = A->num;
	for(int i = 0; i < dim; i++)
	{
		C->data[i] = A->data[i] + B->data[i];
	}
	C->num = dim;
}
/*****************************************************************************/
/*VectorInit(mvector *A,int dim) 向量初始化
/* dim 维数
/******************************************************************************/

void VectorInit(mvector *A,int dim)
{
	if((dim > MAX_DIM)||(A == NULL))
		return ;
	for(int i = 0; i < dim; i++)
	{
		A->data[i] = 0.0;
	}
	A->num = dim;

}

/*****************************************************************************/
/*VectorMul(mvector *A,double mul) 向量数乘
/* 
/*****************************************************************************/
void VectorMul(mvector *A,double mul)
{
	for(int i = 0; i<MAX_DIM; i++)
	{
		A->data[i] *= mul;

	}

}
#define SQUARE(x) x*x
/*****************************************************************************/
/* VectorDistance,用于求两个向量之间的距离，欧氏距离
/* A和B是待求距离的两个向量
/*****************************************************************************/
double VectorDistance(mvector *A,mvector *B)
{
	double total = 0.0;
	double *vec1 = A->data;
	double *vec2 = B->data;
	double temp;
	int dim = A->num;
	if(A->num != B->num)
		return -1.0;
	for(int i = 0; i < dim; i++)
	{	
		temp = vec1[i] - vec2[i];
		total += SQUARE(temp);
	}
	total /= dim;
	total = sqrt(total);
	return total;
}
#undef SQUARE


/*****************************************************************************/
/* DTWDistance，求两个数组之间的匹配距离
/* A,B分别为第一第二个数组，I，J为其数组长度，r为匹配窗口的大小
/* r的大小一般取为数组长度的1/10到1/30
/* 返回两个数组之间的匹配距离,如果返回－1.0，表明数组长度太大了
/*****************************************************************************/
double VDTWDistanceFun(mvector *A,int I,mvector *B,int J,int r)
{
	int i,j;
	double dist;
	int istart,imax;
	double g1,g2,g3;
	int pathsig=1;/*路径的标志*/
	int r2=r+ABS(I-J);/*匹配距离*/
	int dim = A->num;    //向量的维数
	if(A->num != B->num){
		return -1.0;
	}
	if((r2>I-1)||(r2>J-1)){
		return -1.0;
	}

	/*检查参数的有效性*/
	if(I>DTWMAXNUM||J>DTWMAXNUM){
		//printf("Too big number\n");
		return -1.0;
	}
	
	/*进行一些必要的初始化*/
	for(i=0;i<I;i++){
		for(j=0;j<J;j++){
			vdtwpath[i][j]=0;
			vdistance[i][j]=DTWVERYBIG;
		}
	}
	
	/*动态规划求最小距离*/
	/*这里我采用的路径是 -------
	                          . |
	                        .   |
	                      .     |
	                    .       |
	 有可能有更好的前进路径，我没有细加论证，不过算法的数量级是一样的
	 */
	vdistance[0][0]=(double)2*VectorDistance(&A[0],&B[0]);
	for(i=1;i<=r2;i++){
		vdistance[i][0]=vdistance[i-1][0]+VectorDistance(&A[i],&B[0]);
	}
	for(j=1;j<=r2;j++){
		vdistance[0][j]=vdistance[0][j-1]+VectorDistance(&A[0],&B[j]);
	}
	
	for(j=1;j<J;j++){
		istart=j-r2;
		if(j<=r2)
			istart=1;
		imax=j+r2;
		if(imax>=I)
			imax=I-1;

		
		for(i=istart;i<=imax;i++){
			g1=vdistance[i-1][j]+VectorDistance(&A[i],&B[j]);
			g2=vdistance[i-1][j-1]+2*VectorDistance(&A[i],&B[j]);
			g3=vdistance[i][j-1]+VectorDistance(&A[i],&B[j]);
			g2=MIN(g1,g2);
			g3=MIN(g2,g3);
			vdistance[i][j]=g3;
		}
	}
		
	dist=vdistance[I-1][J-1]/((double)(I+J));
	return dist;
}/*end DTWDistance*/

/*****************************************************************************/
/* DTWTemplate，进行建立模板的工作
/* 其中A为已经建立好的模板，我们在以后加入训练样本的时候，
/* 以已建立好的模板作为第一个参数，I为模板的长度，在这个模板中不再改变
/* B为新加入的训练样本，J为B的长度，turn为训练的次数，在第一次
/* 用两个数组建立模板时，r为1，这是出于权值的考虑
/* temp保存匹配最新训练后的模板，建议temp[DTWMAXNUM]，函数返回最新训练后模板的长度
/* 如果函数返回-1，表明训练样本之间距离过大，需要重新选择训练样本，
/* tt为样本之间距离的阈值，自行定义
/* rltdistance保存距离，第一次两个数组建立模板时可以随意赋予一个值，
/* 后面用前一次返回的值赋予该参数
/*****************************************************************************/
int VDTWTemplate(mvector *A,int I,mvector *B,int J,mvector *temp,int turn,double tt,double *rltdistance)
{
	double dist;
	int i,j;
	int pathsig=1;
	int dim = A->num;
	dist=VDTWDistanceFun(A,I,B,J,(int)(I/30));
	if(dist>tt){
		printf("\nSample doesn't match!\n");
		return -1;
	}
		
	if(turn==1)
		*rltdistance=dist;
	else{
		*rltdistance=((*rltdistance)*(turn-1)+dist)/turn;
	}
	/*寻找路径,这里我采用了逆向搜索法*/
	i=I-1;
	j=J-1;
	while(j>=1||i>=1){
		double m;
		if(i>0&&j>0){
			m=MIN(MIN(vdistance[i-1][j],vdistance[i-1][j-1]),vdistance[i][j-1]);
			if(m==vdistance[i-1][j]){
				vdtwpath[i-1][j]=pathsig;
				i--;
			}
			else if(m==vdistance[i-1][j-1]){
				vdtwpath[i-1][j-1]=pathsig;
				i--;
				j--;
			}
			else{
				vdtwpath[i][j-1]=pathsig;
				j--;
			}
		}
		else if(i==0){
			vdtwpath[0][j-1]=pathsig;
			j--;
		}
		else{/*j==0*/
			vdtwpath[i-1][0]=pathsig;
			i--;
		}
	}
	vdtwpath[0][0]=pathsig;
	vdtwpath[I-1][J-1]=pathsig;
	
	/*建立模板*/
	for(i=0;i<I;i++){
		mvector ftemp;
		VectorInit(&ftemp,dim);
		int ntemp=0;
		for(j=0;j<J;j++){
			if(vdtwpath[i][j]==pathsig){
				VectorAdd(&ftemp,&B[j],&ftemp);
				ntemp++;
			}
		}
		VectorMul(&ftemp,1.0/(double)ntemp);
		//temp[i]=(A[i]*turn+ftemp)/((double)(turn+1));/*注意这里的权值*/
		VectorMul(&A[i],turn);
		VectorAdd(&ftemp,&A[i],&temp[i]);
		VectorMul(&temp[i],1.0/(double)(turn+1));
	}
	
	
	return I;/*返回模板的长度*/
}//end DTWTemplate