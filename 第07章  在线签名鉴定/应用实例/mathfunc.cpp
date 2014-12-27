#include "mathfunc.h"
#include "stdlib.h"
#include "malloc.h"
#include "memory.h"
#include "string.h"
//#include "wi.h"
#define TAPEDDATADIM 1024


void lowpassfilter(double *data,double threshold,unsigned long dataLen)
{
	int r=0;
	unsigned long i,mask=0xffffffff;
	while(mask&dataLen)
	{
		mask<<=1;
		r++;
	}
	unsigned long count = 1<<r;
	complex *com1,*com2;
	com1 = (complex *)malloc(sizeof(complex)*count);
	com2 = (complex *)malloc(sizeof(complex)*count);
	//Initiallize
	for (i = 0; i < count; i++)
	{
		com1[i].r = i>=dataLen?0:data[i];
		com1[i].i = 0.0;
	}

	fft(com1,com2, r);
	
	for(i = (int)((threshold/2)*count); i< count; i++)
	{
		com2[i].r = 0.0;
	}

	ifft (com2,com1, r);
	
	for(i = 0;i<dataLen;i++)
	{
		data[i] = com1[i].r;
	}

}


void  fft(complex *td, complex *fd, int r)
{
	// 付立叶变换点数
	long	count;
	
	// 循环变量
	int		i,j,k;
	
	// 中间变量
	int		bfsize,p;
	
	// 角度
	double	angle;
	
	complex *w,*x1,*x2,*x;
	
	// 计算付立叶变换点数
	count = 1 << r;
	
	// 分配运算所需存储器
	w = (complex *)malloc(sizeof(complex)*count/2);
	x1 = (complex *)malloc(sizeof(complex)*count);
	x2 = (complex *)malloc(sizeof(complex)*count);
	
	// 计算加权系数
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		w[i].r = cos(angle);
		w[i].i = sin(angle);
	}
	
	// 将时域点写入X1
	memcpy(x1, td, sizeof(complex) * count);
	
	// 采用蝶形算法进行快速付立叶变换
	for(k = 0; k < r; k++)
	{
		for(j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (r-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				x2[i + p].r = x1[i + p].r + x1[i + p + bfsize / 2].r;
				x2[i + p].i = x1[i + p].i + x1[i + p + bfsize / 2].i;
				x2[i + p + bfsize / 2].r = (x1[i + p].r - x1[i + p + bfsize / 2].r) * w[i * (1<<k)].r
										  -(x1[i + p].i - x1[i + p + bfsize / 2].i) * w[i * (1<<k)].i;
				x2[i + p + bfsize / 2].i = (x1[i + p].i - x1[i + p + bfsize / 2].i) * w[i * (1<<k)].r
										  +(x1[i + p].r - x1[i + p + bfsize / 2].r) * w[i * (1<<k)].i;
			}
		}
		x  = x1;
		x1 = x2;
		x2 = x;
	}
	
	// 重新排序
	for(j = 0; j < count; j++)
	{
		p = 0;
		for(i = 0; i < r; i++)
		{
			if (j&(1<<i))
			{
				p+=1<<(r-i-1);
			}
		}
		fd[j]=x1[p];
	}
	
	// 释放内存
	free(w);
	free(x1);
	free(x2);
}

void ifft(complex *fd, complex *td, int r)
{
	// 付立叶变换点数
	long 	count;
	
	// 循环变量
	int		i;
	
	complex  *x;
	
	// 计算付立叶变换点数
	count = 1 << r;
	
	// 分配运算所需存储器
	x = (complex *)malloc(sizeof(complex)*count);
	// 将频域点写入X
	memcpy(x, fd, sizeof(complex) * count);
	
	// 求共轭
	for(i = 0; i < count; i++)
	{
		x[i].r = x[i].r;
		x[i].i = -x[i].i;
	}
	
	// 调用快速付立叶变换
	fft(x, td, r);
	
	// 求时域点的共轭
	for(i = 0; i < count; i++)
	{
		td[i].r = td[i].r/count;
		td[i].i = -td[i].i/count;
	}
	
	// 释放内存
	free(x);
}


float MinFloat(float a,float b)
{
	if(a<=b)
		return a;
	else 
		return b;
}

float AbsFloat(float a)
{
	if(a<0)
		return -a;
	else
		return a;
}

int AbsInt(int a)
{
	if(a<0)
		return -a;
	else 
		return a;
}
