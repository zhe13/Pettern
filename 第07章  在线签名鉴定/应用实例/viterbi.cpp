//viterbi.cpp

#include <math.h>
#include "hmm.h"
#include "nrutils.h"
static char rcsid[] = "Hidden Markov Model";

#define VITHUGE  100000000000.0

void Viterbi(HMM *phmm, int T, int *O, double **delta, int **psi, 
	int *q, double *pprob)
{
	int 	i, j;	/* state indices */
	int  	t;	/* time index */	

	int	maxvalind;
	double	maxval, val;

	/* 1. Initialization  */
	
	for (i = 0; i < phmm->N; i++) {
		delta[0][i] = phmm->pi[i] * (phmm->B[i][O[0]-1]);
		psi[0][i] = 0;
	}	

	/* 2. Recursion */
	
	for (t = 1; t < T; t++) {
		for (j = 0; j < phmm->N; j++) {
			maxval = 0.0;
			maxvalind = 0;	
			for (i = 0; i < phmm->N; i++) {
				val = delta[t-1][i]*(phmm->A[i][j]);
				if (val > maxval) {
					maxval = val;	
					maxvalind = i;	
				}
			}
			
			delta[t][j] = maxval*(phmm->B[j][O[t]-1]);
			psi[t][j] = maxvalind; 

		}
	}

	/* 3. Termination */

	*pprob = 0.0;
	q[T-1] = 0;
	for (i = 0; i < phmm->N; i++) {
        if (delta[T-1][i] > *pprob) {
			*pprob = delta[T-1][i];	
			q[T-1] = i;
		}
	}

	/* 4. Path (state sequence) backtracking */

	for (t = T - 2; t >= 0; t--)
		q[t] = psi[t+1][q[t+1]];

}


void ViterbiLog(HMM *phmm, int T, int *O, double **delta, int **psi,
        int *q, double *pprob)
{
        int     i, j;   /* state indices */
        int     t;      /* time index */
 
        int     maxvalind;
        double  maxval, val;
	double  **biot;

	/* 0. Preprocessing */

	for (i = 0; i < phmm->N; i++) 
		phmm->pi[i] = log(phmm->pi[i]);
	for (i = 0; i < phmm->N; i++) 
		for (j = 0; j < phmm->N; j++) {
			phmm->A[i][j] = log(phmm->A[i][j]);
		}

	biot = dmatrix(1, phmm->N, 1, T);
	for (i = 0; i < phmm->N; i++) 
		for (t = 0; t < T; t++) {
			biot[i][t] = log(phmm->B[i][O[t]-1]);
		}
 
        /* 1. Initialization  */
 
        for (i = 0; i < phmm->N; i++) {
                delta[0][i] = phmm->pi[i] + biot[i][0];
                psi[0][i] = 0;
        }
 
        /* 2. Recursion */
 
        for (t = 1; t < T; t++) {
                for (j = 0; j < phmm->N; j++) {
                        maxval = -VITHUGE;
                        maxvalind = 0;
                        for (i = 0; i < phmm->N; i++) {
                                val = delta[t-1][i] + (phmm->A[i][j]);
                                if (val > maxval) {
                                        maxval = val;
                                        maxvalind = i;
                                }
                        }
 
                        delta[t][j] = maxval + biot[j][t]; 
                        psi[t][j] = maxvalind;
 
                }
        }
 
        /* 3. Termination */
 
        *pprob = -VITHUGE;
        q[T-1] = 0;
        for (i = 0; i < phmm->N; i++) {
                if (delta[T-1][i] > *pprob) {
                        *pprob = delta[T-1][i];
                        q[T-1] = i;
                }
        }
 
 
	/* 4. Path (state sequence) backtracking */

	for (t = T - 2; t >= 0; t--)
		q[t] = psi[t+1][q[t+1]];

}
 

