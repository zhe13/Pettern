//forward.cpp
//      Purpose: Foward algorithm for computing the probabilty 
//		of observing a sequence given a HMM model parameter.
#include <stdio.h>
#include "hmm.h"
static char rcsid[] = "Hidden Markov Model";

void Forward(HMM *phmm, int T, int *O, double **alpha, double *pprob)
{
        int     i, j;   /* state indices */
        int     t;      /* time index */
 
        double sum;     /* partial sum */
 
        /* 1. Initialization */
 
        for (i = 0; i < phmm->N; i++)
                alpha[0][i] = phmm->pi[i]* phmm->B[i][O[0]-1];
 
        /* 2. Induction */
 
        for (t = 0; t < T-1; t++) {
                for (j = 0; j < phmm->N; j++) {
                        sum = 0.0;
                        for (i = 0; i < phmm->N; i++)
                                sum += alpha[t][i]* (phmm->A[i][j]);
 
                        alpha[t+1][j] = sum*(phmm->B[j][O[t+1]-1]);
                }
        }
 
        /* 3. Termination */
        *pprob = 0.0;
        for (i = 0; i < phmm->N; i++)
                *pprob += alpha[T-1][i];
 
}

void ForwardWithScale(HMM *phmm, int T, int *O, double **alpha, 
	double *scale, double *pprob)
/*  pprob is the LOG probability */
{
	int	i, j; 	/* state indices */
	int	t;	/* time index */

	double sum;	/* partial sum */

	/* 1. Initialization */

	scale[0] = 0.0;	
	for (i = 0; i < phmm->N; i++) {
		alpha[0][i] = phmm->pi[i]* (phmm->B[i][O[0]-1]);
		scale[0] += alpha[0][i];
	}
	for (i = 0; i < phmm->N; i++) 
		alpha[0][i] /= scale[0]; 
	
	/* 2. Induction */

	for (t = 0; t < T - 1; t++) {
		scale[t+1] = 0.0;
		for (j = 0; j < phmm->N; j++) {
			sum = 0.0;
			for (i = 0; i < phmm->N; i++) 
				sum += alpha[t][i]* (phmm->A[i][j]); 

			alpha[t+1][j] = sum*(phmm->B[j][O[t+1]-1]);
			scale[t+1] += alpha[t+1][j];
		}
		for (j = 0; j < phmm->N; j++) 
			alpha[t+1][j] /= scale[t+1]; 
	}

	/* 3. Termination */
	*pprob = 0.0;

	for (t = 0; t < T; t++)
		*pprob += log(scale[t]);
	
}
