/*
**      File:   nrutil.c
*/

#include <malloc.h>
#include <stdio.h>
#include "nrutils.h"
static char rcsid[] = "Hidden Markov Model";


void nrerror(char *text)
//char *text;
{
	//void exit();

	fprintf(stderr,"Numerical Recipes run-time error...\n");
	fprintf(stderr,"%s\n",text);
	fprintf(stderr,"...now exiting to system...\n");
	//exit(1);
	return;
}

float *vector(int nl,int nh)
//int nl,nh;
{
	float *v;

	v=(float *)calloc((unsigned) (nh-nl+1),sizeof(float));
	if (!v) nrerror("allocation failure in vector()");
	return v-nl+1;
}

int *ivector(int nl,int nh)
//int nl,nh;
{
	int *v;

	v=(int *)calloc((unsigned) (nh-nl+1),sizeof(int));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl+1;
}

double *dvector(int nl,int nh)
//int nl,nh;
{
	double *v;

	v=(double *)calloc((unsigned) (nh-nl+1),sizeof(double));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl+1;
}



float **matrix(int nrl,int nrh,int ncl,int nch)
//int nrl,nrh,ncl,nch;
{
	int i;
	float **m;

	m=(float **) calloc((unsigned) (nrh-nrl+1),sizeof(float*));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m = m-nrl+1;

	for(i=nrl-1;i<=nrh-1;i++) {
		m[i]=(float *) calloc((unsigned) (nch-ncl+1),sizeof(float));
		if (!m[i]) nrerror("allocation failure 2 in matrix()");
		m[i] =m[i]- ncl+1;
	}
	return m;
}

double **dmatrix(int nrl,int nrh,int ncl,int nch)
//int nrl,nrh,ncl,nch;
{
	int i;
	double **m;

	m=(double **) calloc((unsigned) (nrh-nrl+1),sizeof(double*));
	if (!m) nrerror("allocation failure 1 in dmatrix()");
	m = m-nrl+1;

	for(i=nrl-1;i<=nrh-1;i++) {
		m[i]=(double *) calloc((unsigned) (nch-ncl+1),sizeof(double));
		if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
		m[i] =m[i]- ncl+1;
	}
	return m;
}

int **imatrix(int nrl,int nrh,int ncl,int nch)
//int nrl,nrh,ncl,nch;
{
	int i,**m;

	m=(int **)calloc((unsigned) (nrh-nrl+1),sizeof(int*));
	if (!m) nrerror("allocation failure 1 in imatrix()");
	m = m-nrl+1;

	for(i=nrl-1;i<=nrh-1;i++) {
		m[i]=(int *)calloc((unsigned) (nch-ncl+1),sizeof(int));
		if (!m[i]) nrerror("allocation failure 2 in imatrix()");
		m[i] =m[i]- ncl+1;
	}
	return m;
}



float **submatrix(float **a,int oldrl,int oldrh,int oldcl,int oldch,int newrl,int newcl)
//float **a;
//int oldrl,oldrh,oldcl,oldch,newrl,newcl;
{
	int i,j;
	float **m;

	m=(float **) calloc((unsigned) (oldrh-oldrl+1),sizeof(float*));
	if (!m) nrerror("allocation failure in submatrix()");
	m = m-newrl+1;

	for(i=oldrl-1,j=newrl-1;i<=oldrh-1;i++,j++) m[j]=a[i]+oldcl-newcl;

	return m;
}



void free_vector(float *v,int nl,int nh)
//float *v;
//int nl,nh;
{
	free((char*) (v+nl-1));
}

void free_ivector(int *v,int nl,int nh)
//int *v,nl,nh;
{
	free((char*) (v+nl-1));
}

void free_dvector(double *v,int nl,int nh)
//double *v;
//int nl,nh;
{
	free((char*) (v+nl-1));
}



void free_matrix(float **m,int nrl,int nrh,int ncl,int nch)
//float **m;
//int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh-1;i>=nrl-1;i--) free((char*) (m[i]+ncl-1));
	free((char*) (m+nrl-1));
}

void free_dmatrix(double **m,int nrl,int nrh,int ncl,int nch)
//double **m;
//int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh-1;i>=nrl-1;i--) free((char*) (m[i]+ncl-1));
	free((char*) (m+nrl-1));
}

void free_imatrix(int **m,int nrl,int nrh,int ncl,int nch)
//int **m;
//int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh-1;i>=nrl-1;i--) free((char*) (m[i]+ncl-1));
	free((char*) (m+nrl-1));
}



void free_submatrix(float **b,int nrl,int nrh,int ncl,int nch)
//float **b;
//int nrl,nrh,ncl,nch;
{
	free((char*) (b+nrl-1));
}



float **convert_matrix(float *a,int nrl,int nrh,int ncl,int nch)
//float *a;
//int nrl,nrh,ncl,nch;
{
	int i,j,nrow,ncol;
	float **m;

	nrow=nrh-nrl+1;
	ncol=nch-ncl+1;
	m = (float **) calloc((unsigned) (nrow),sizeof(float*));
	if (!m) nrerror("allocation failure in convert_matrix()");
	m =m- nrl+1;
	for(i=0,j=nrl-1;i<=nrow-1;i++,j++) m[j]=a+ncol*i-ncl+1;
	return m;
}



void free_convert_matrix(float **b,int nrl,int nrh,int ncl,int nch)
//float **b;
//int nrl,nrh,ncl,nch;
{
	free((char*) (b+nrl-1));
}
