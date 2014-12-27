//////////////////////////////////////////////////////////////////////////
//ar.h
//2001.10.2

#define MAXENTROPY      0
#define LEASTSQUARES    1

int AutoRegression(double *,int,int,double *,int);

int ARMaxEntropy(double *,int,int,double **,
	double *,double *,double *,double *
);

int ARLeastSquare(double *,int,int,double *);

int SolveLE(double **,double *,unsigned int);
