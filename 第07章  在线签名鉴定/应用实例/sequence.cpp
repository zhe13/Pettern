//sequence.cpp
//date:2001.10.11

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "nrutils.h"
#include "hmm.h"

static char rcsid[] = "Hidden Markov Model";

void GenSequenceArray(HMM *phmm, int seed, int T, int *O, int *q)
{
        int     t = 0;
        int     q_t, o_t;

	hmmsetseed(seed); 
 
        q[0] = GenInitalState(phmm);
        O[0] = GenSymbol(phmm, q[0]);
 
        for (t = 1; t < T; t++) {
                q[t] = GenNextState(phmm, q[t-1]);
                O[t] = GenSymbol(phmm, q[t]);
        }
}

int GenInitalState(HMM *phmm)
{
        double val, accum;
        int i, q_t;
 
        val = hmmgetrand();
        accum = 0.0;
        q_t = phmm->N;
        for (i = 0; i < phmm->N; i++) {
                if (val < phmm->pi[i] + accum) {
                        q_t = i+1;
                        break;
                }
                else {
                                accum += phmm->pi[i];
                }
        }
 
        return q_t;
}

int GenNextState(HMM *phmm, int q_t)
{
        double val, accum;
        int j, q_next;
 
        val = hmmgetrand();
        accum = 0.0;
        q_next = phmm->N;
        for (j = 0; j < phmm->N; j++) {
                if ( val < phmm->A[q_t-1][j] + accum ) {
                        q_next = j+1;
                        break;
                }
                else
                        accum += phmm->A[q_t-1][j];
        }
 
        return q_next;
}
int GenSymbol(HMM *phmm, int q_t)
{
        double val, accum;
        int j, o_t;
 
        val = hmmgetrand();
        accum = 0.0;
        o_t = phmm->M;
        for (j = 0; j < phmm->M; j++) {
                if ( val < phmm->B[q_t-1][j] + accum ) {
                       o_t = j+1;
                       break;
                }
                else
                        accum += phmm->B[q_t-1][j];
        }
 
        return o_t;
}
 
void ReadSequence(FILE *fp, int *pT, int **pO)
{
        int *O;
        int i;
 
        fscanf(fp, "T= %d\n", pT);
        O = ivector(1,*pT);
        for (i=0; i <= (*pT)-1; i++)
                fscanf(fp,"%d", &O[i]);
        *pO = O;
}
 
void PrintSequence(FILE *fp, int T, int *O)
{
        int i;
 
        fprintf(fp, "T= %d\n", T);
        for (i=0; i <= T-1; i++) 
                fprintf(fp,"%d ", O[i]);
	printf("\n");
 
}

