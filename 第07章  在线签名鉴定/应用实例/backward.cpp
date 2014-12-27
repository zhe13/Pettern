//backward.cpp 
//Purpose: Backward algorithm for computing the probabilty
//              of observing a sequence given a HMM model parameter.

#include <stdio.h>
#include "hmm.h"
static char rcsid[] = "Hidden Markov Model";

void Backward(HMM *phmm, int T, int *O, double **beta, double *pprob)
{
        int     i, j;   /* state indices */
        int     t;      /* time index */
        double sum;
 
 
        /* 1. Initialization */
 
        for (i = 0; i < phmm->N; i++)
                beta[T-1][i] = 1.0;
 
        /* 2. Induction */
 
        for (t = T - 2; t >= 0; t--) {
                for (i = 0; i < phmm->N; i++) {
                        sum = 0.0;
                        for (j = 0; j < phmm->N; j++)
                                sum += phmm->A[i][j] *
                                        (phmm->B[j][O[t+1]-1])*beta[t+1][j];
                        beta[t][i] = sum;
 
                }
        }
 
        /* 3. Termination */
        *pprob = 0.0;
        for (i = 0; i < phmm->N; i++)
                *pprob += beta[0][i];
 
}

void BackwardWithScale(HMM *phmm, int T, int *O, double **beta, 
	double *scale, double *pprob)
{
        int     i, j;   /* state indices */
        int     t;      /* time index */
	double sum;
 
 
        /* 1. Initialization */
 
        for (i = 0; i < phmm->N; i++)
                beta[T-1][i] = 1.0/scale[T-1]; 
 
        /* 2. Induction */
 
        for (t = T - 2; t >= 0; t--) {
                for (i = 0; i < phmm->N; i++) {
			sum = 0.0;
                        for (j = 0; j < phmm->N; j++)
                        	sum += phmm->A[i][j] * 
					(phmm->B[j][O[t+1]-1])*beta[t+1][j];
                        beta[t][i] = sum/scale[t];
 
                }
        }
 
}
