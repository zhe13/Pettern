/************************************************************************
**      File:   hmm.h
**      功能：提供HMM的数据结构和定义
*/
#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
	int N;		/* 状态的个数；  Q={1,2,...,N} */
	int M; 		/* 观察值得个数; V={1,2,...,M}*/
	double	**A;	/* A[1..N][1..N]. a[i][j] 是从t时刻的状态i转移到t+1时刻
					的状态j的转移概率*/
	double	**B;	/* B[1..N][1..M]. b[j][k] 是在状态j观察到观察值k的概率 */
	double	*pi;	/* pi[1..N] pi[i] 是进入Markov链的状态分布 */
} HMM;

//关于HMM的文件存取、初始化、拷贝函数
void ReadHMM(FILE *fp, HMM *phmm);
void PrintHMM(FILE *fp, HMM *phmm);
void InitHMM(HMM *phmm, int N, int M, int seed);
void CopyHMM(HMM *phmm1, HMM *phmm2);
void FreeHMM(HMM *phmm);

//关于序列的存取，状态的计算等等
void ReadSequence(FILE *fp, int *pT, int **pO);
void PrintSequence(FILE *fp, int T, int *O);
void GenSequenceArray(HMM *phmm, int seed, int T, int *O, int *q);
int GenInitalState(HMM *phmm);
int GenNextState(HMM *phmm, int q_t);
int GenSymbol(HMM *phmm, int q_t);

//前向后向算法、BaumWelch算法
void Forward(HMM *phmm, int T, int *O, double **alpha, double *pprob);
void ForwardWithScale(HMM *phmm, int T, int *O, double **alpha,
        double *scale, double *pprob);
void Backward(HMM *phmm, int T, int *O, double **beta, double *pprob);
void BackwardWithScale(HMM *phmm, int T, int *O, double **beta,
        double *scale, double *pprob);
void BaumWelch(HMM *phmm, int T, int *O, double **alpha, double **beta,
        double **gamma, int *niter, 
	double *plogprobinit, double *plogprobfinal);

//Viterbi算法
double *** AllocXi(int T, int N);
void FreeXi(double *** xi, int T, int N);
void ComputeGamma(HMM *phmm, int T, double **alpha, double **beta,
        double **gamma);
void ComputeXi(HMM* phmm, int T, int *O, double **alpha, double **beta,
        double ***xi);
void Viterbi(HMM *phmm, int T, int *O, double **delta, int **psi,
        int *q, double *pprob);
void ViterbiLog(HMM *phmm, int T, int *O, double **delta, int **psi,
        int *q, double *pprob);

//随机数相关函数

int hmmgetseed(void);
void hmmsetseed(int seed);
double hmmgetrand(void);
 
#define MAX(x,y)        ((x) > (y) ? (x) : (y))
#define MIN(x,y)        ((x) < (y) ? (x) : (y))
 

