/*
**      File:   backward.cpp
**      功能：给定观察值序列和HMM模型，利用前向后向算法
**            求取其概率
*/

#include "StdAfx.h"
#include <stdio.h>
#include "hmm.h"

/***************************************************************************
** 函数名称：Backward
** 功能：后向算法估计参数
** 参数：phmm：指向HMM的指针
**       T：观察值序列的长度
**       O：观察值序列
**       beta：运算中用到的临时数组
**       pprob：返回值，所要求的概率
**/
void Backward(HMM *phmm, int T, int *O, double **beta, double *pprob)
{
	int     i, j;   /* 状态 */
	int     t;      /* 时间下标 */
	double sum;
 
 
	/* 1. 初始化 */
 
	for (i = 1; i <= phmm->N; i++)
		beta[T][i] = 1.0;
 
	/* 2. 递归 */
 
	for (t = T - 1; t >= 1; t--) 
	{
		for (i = 1; i <= phmm->N; i++) 
		{
			sum = 0.0;
			for (j = 1; j <= phmm->N; j++)
				sum += phmm->A[i][j] * (phmm->B[j][O[t+1]])*beta[t+1][j];
			beta[t][i] = sum;
 
		}
	}
 
	/* 3. 终止 */
	*pprob = 0.0;
	for (i = 1; i <= phmm->N; i++)
		*pprob += beta[1][i];
}

/***************************************************************************
** 函数名称：BackwardWithScale
** 功能：后向算法估计参数（带比例因子修正）
** 参数：phmm：指向HMM的指针
**       T：观察值序列的长度
**       O：观察值序列
**       beta：运算中用到的临时数组
**       scale：比例因子数组
**       pprob：返回值，所要求的概率
**/
void BackwardWithScale(HMM *phmm, int T, int *O, double **beta, 
	double *scale, double *pprob)
{
	int     i, j;   /* 状态指示 */
	int     t;      /* 时间下标 */
	double sum;
 
 
	/* 1. 初始化 */
	for (i = 1; i <= phmm->N; i++)
		beta[T][i] = 1.0/scale[T]; 
 
	/* 2. 递归 */
	for (t = T - 1; t >= 1; t--) 
	{
		for (i = 1; i <= phmm->N; i++) 
		{
			sum = 0.0;
			for (j = 1; j <= phmm->N; j++)
				sum += phmm->A[i][j] * (phmm->B[j][O[t+1]])*beta[t+1][j];
			beta[t][i] = sum/scale[t];
		}
	}
}
