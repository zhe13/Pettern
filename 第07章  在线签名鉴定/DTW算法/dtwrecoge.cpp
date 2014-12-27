/*dtwrecoge.cpp**************************************************************/

#include "dtwrecoge.h"
double distance[DTWMAXNUM][DTWMAXNUM]; /*保存距离*/
double dtwpath[DTWMAXNUM][DTWMAXNUM]; /*保存路径*/

/*****************************************************************************/
/* DTWDistance，求两个数组之间的匹配距离
/* A,B分别为第一第二个数组，I，J为其数组长度，r为匹配窗口的大小

/* r的大小一般取为数组长度的1/10到1/30
/* 返回两个数组之间的匹配距离,如果返回－1.0，表明数组长度太大了
/*****************************************************************************/
double DTWDistanceFun(double *A,int I,double *B,int J,int r)
{
	int i,j;
	double dist;
	int istart,imax;
	int r2=r+ABS(I-J);/*匹配距离*/
	double g1,g2,g3;
	int pathsig=1;/*路径的标志*/

	/*检查参数的有效性*/
	if(I>DTWMAXNUM||J>DTWMAXNUM){
		//printf("Too big number\n");
		return -1.0;
	}
	
	/*进行一些必要的初始化*/
	for(i=0;i<I;i++){
		for(j=0;j<J;j++){
			dtwpath[i][j]=0;
			distance[i][j]=DTWVERYBIG;
		}
	}
	
	/*动态规划求最小距离*/
	/*这里我采用的路径是 -------
	                          . |
	                        .   |
	                      .     |
	                    .       |
	 */
	distance[0][0]=(double)2*ABS(A[0]-B[0]);
	for(i=1;i<=r2;i++){
		distance[i][0]=distance[i-1][0]+ABS(A[i]-B[0]);
	}
	for(j=1;j<=r2;j++){
		distance[0][j]=distance[0][j-1]+ABS(A[0]-B[j]);
	}
	
	for(j=1;j<J;j++){
		istart=j-r2;
		if(j<=r2)
			istart=1;
		imax=j+r2;
		if(imax>=I)
			imax=I-1;
		
		for(i=istart;i<=imax;i++){
			g1=distance[i-1][j]+ABS(A[i]-B[j]);
			g2=distance[i-1][j-1]+2*ABS(A[i]-B[j]);
			g3=distance[i][j-1]+ABS(A[i]-B[j]);
			g2=MIN(g1,g2);
			g3=MIN(g2,g3);
			distance[i][j]=g3;
		}
	}
		
	dist=distance[I-1][J-1]/((double)(I+J));
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
/* tt为样本之间距离的阀值，自行定义
/* rltdistance保存距离，第一次两个数组建立模板时可以随意赋予一个值，
/* 后面用前一次返回的值赋予该参数
/*****************************************************************************/
int DTWTemplate(double *A,int I,double *B,int J,double *temp,int turn,double tt,double *rltdistance)
{
	double dist;
	int i,j;
	int pathsig=1;
	dist=DTWDistanceFun(A,I,B,J,(int)(I/30));
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
			m=MIN(MIN(distance[i-1][j],distance[i-1][j-1]),distance[i][j-1]);
			if(m==distance[i-1][j]){
				dtwpath[i-1][j]=pathsig;
				i--;
			}
			else if(m==distance[i-1][j-1]){
				dtwpath[i-1][j-1]=pathsig;
				i--;
				j--;
			}
			else{
				dtwpath[i][j-1]=pathsig;
				j--;
			}
		}
		else if(i==0){
			dtwpath[0][j-1]=pathsig;
			j--;
		}
		else{/*j==0*/
			dtwpath[i-1][0]=pathsig;
			i--;
		}
	}
	dtwpath[0][0]=pathsig;
	dtwpath[I-1][J-1]=pathsig;
	
	/*建立模板*/
	for(i=0;i<I;i++){
		double ftemp=0.0;
		int ntemp=0;
		for(j=0;j<J;j++){
			if(dtwpath[i][j]==pathsig){
				ftemp+=B[j];
				ntemp++;
			}
		}
		ftemp/=((double)ntemp);
		temp[i]=(A[i]*turn+ftemp)/((double)(turn+1));/*注意这里的权值*/
	}
	
	return I;/*返回模板的长度*/
}//end DTWTemplate