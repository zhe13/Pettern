/*
**   File：Viterbi.cpp
**   功能：给定HMM和观察序列，求最可能的状态
*/

#include "StdAfx.h"
#include <math.h>
#include "hmm.h"
#include "nrutil.h"

#define VITHUGE  100000000000.0

/**************************************************************************
** 函数名称：Viterbi
** 功能：Viterbi算法
** 参数：phmm：HMM结构指针
**       T：观察值的个数
**       O：观察序列
**       delta，psi为中间变量
**       q：求得的最佳状态序列
**       pprob：概率
**/
void Viterbi(HMM *phmm, int T, int *O, double **delta, int **psi, 
	int *q, double *pprob)
{
	int 	i, j;	/* 状态下标 */
	int  	t;	/* 时间下标 */	

	int	maxvalind;
	double	maxval, val;

	/* 1. 初始化  */
	
	for (i = 1; i <= phmm->N; i++) 
	{
		delta[1][i] = phmm->pi[i] * (phmm->B[i][O[1]]);
		psi[1][i] = 0;
	}	

	/* 2. 递归 */
	
	for (t = 2; t <= T; t++) 
	{
		for (j = 1; j <= phmm->N; j++) 
		{
			maxval = 0.0;
			maxvalind = 1;	
			for (i = 1; i <= phmm->N; i++) 
			{
				val = delta[t-1][i]*(phmm->A[i][j]);
				if (val > maxval) {
					maxval = val;	
					maxvalind = i;	
				}
			}
			
			delta[t][j] = maxval*(phmm->B[j][O[t]]);
			psi[t][j] = maxvalind; 

		}
	}

	/* 3. 终止 */

	*pprob = 0.0;
	q[T] = 1;
	for (i = 1; i <= phmm->N; i++) 
	{
		if (delta[T][i] > *pprob) 
		{
			*pprob = delta[T][i];	
			q[T] = i;
		}
	}

	/* 4. Path (state sequence) backtracking */

	for (t = T - 1; t >= 1; t--)
		q[t] = psi[t+1][q[t+1]];

}

/**************************************************************************
** 函数名称：ViterbiLog
** 功能：Viterbi算法
** 参数：phmm：HMM结构指针
**       T：观察值的个数
**       O：观察序列
**       delta，psi为中间变量
**       q：求得的最佳状态序列
**       pprob：概率
**/
void ViterbiLog(HMM *phmm, int T, int *O, double **delta, int **psi,
        int *q, double *pprob)
{
	int     i, j;   /* 状态下标 */
	int     t;      /* 时间下标 */
 
	int     maxvalind;
	double  maxval, val;
	double  **biot;

	/* 0. 预处理 */

	for (i = 1; i <= phmm->N; i++) 
		phmm->pi[i] = log(phmm->pi[i]);
	for (i = 1; i <= phmm->N; i++) 
		for (j = 1; j <= phmm->N; j++) 
		{
			phmm->A[i][j] = log(phmm->A[i][j]);
		}

	biot = dmatrix(1, phmm->N, 1, T);
	for (i = 1; i <= phmm->N; i++) 
		for (t = 1; t <= T; t++) 
		{
			biot[i][t] = log(phmm->B[i][O[t]]);
		}
 
	/* 1. 初始化  */
 
	for (i = 1; i <= phmm->N; i++) 
	{
		delta[1][i] = phmm->pi[i] + biot[i][1];
		psi[1][i] = 0;
	}
 
	/* 2. 递归 */
 
	for (t = 2; t <= T; t++) 
	{
		for (j = 1; j <= phmm->N; j++) 
		{
			maxval = -VITHUGE;
			maxvalind = 1;
			for (i = 1; i <= phmm->N; i++) 
			{
				val = delta[t-1][i] + (phmm->A[i][j]);
				if (val > maxval) 
				{
					maxval = val;
					maxvalind = i;
				}
			}
 
			delta[t][j] = maxval + biot[j][t]; 
			psi[t][j] = maxvalind;
 
		}
	}
 
	/* 3. 终止 */
 
	*pprob = -VITHUGE;
	q[T] = 1;
	for (i = 1; i <= phmm->N; i++) 
	{
		if (delta[T][i] > *pprob) 
		{
			*pprob = delta[T][i];
			q[T] = i;
		}
	}
 
 
	/* 4. 回溯 */

	for (t = T - 1; t >= 1; t--)
		q[t] = psi[t+1][q[t+1]];

}
