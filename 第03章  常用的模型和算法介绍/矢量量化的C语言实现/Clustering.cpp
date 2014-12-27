#include "stdafx.h"
#include "Clustering.h"
#include "stdio.h"
#include "math.h"

/******************************************************************************
/*	Name:		LBGCluster
/*	Function:	Clustering input vectors using LBG algorithm
/*				Using Euclidean distance
/*	Parameter:	X -- Input vecters
/*				N -- Number of input vectors
/*				Y -- Clustering result
/*				M -- Number of clustering center
/*	Return:		0 -- Correct
/*				1 -- Error
/*
/******************************************************************************/
int LBGCluster(VQ_VECTOR *X, int N, VQ_CENTER *Y, int M)
{
	if(N<M)			 return -1;
	int		L=1000, m=1, nCenter, i, j, k;//L,迭代的次数
	int		nDimension = X[0].nDimension;
	double  D0, D;
	struct  VQ_CENTERINFO
	{
		double*	  Data;
		int		  nDimension;
		double*   SumData;
		int		  Num;
	};
	VQ_CENTERINFO	*Center = (VQ_CENTERINFO*)malloc(M*sizeof(VQ_CENTERINFO));
	if(Center == NULL)		return -1;
	double			*Distance = (double*)malloc(N*sizeof(double));
	if(Distance == NULL)	return -1;

	for( i=0; i<M; i++)
	{
		Center[i].nDimension = nDimension;
		Center[i].Data = (double*)malloc(sizeof(double)*nDimension);
		Center[i].SumData = (double*)malloc(sizeof(double)*nDimension);
		if( Center[i].Data == NULL || Center[i].SumData == NULL )
		{
			AfxMessageBox( "Memory used up!" );
			return -1;
		}
		for( j=0; j<nDimension; j++ )
		{
			Center[i].Data[j] = X[i*N/M].Data[j];
			Center[i].SumData[j] = 0;
		}
		Center[i].Num = 0;
	}

	D0=1;         D=1e+10;	
	while(m<L && fabs(D0-D)/D0>1e-5)
	{
		for(i=0; i<M; i++)
		{
			for( j=0;	j<nDimension; j++ )
				Center[i].SumData[j] = 0;
			Center[i].Num = 0;
		}
		D0 = D;			D = 0;		m++;
		for(i=0; i<N; i++)
		{
			Distance[i] = 1e+10;
			for(int j=0; j<M; j++)
			{
				double  Dist = 0;
				for( k=0; k<nDimension; k++ )
					Dist += (X[i].Data[k]-Center[j].Data[k])*(X[i].Data[k]-Center[j].Data[k]);
				if(  Dist < Distance[i])
				{			
					nCenter = j;
					Distance[i] = Dist;
				}
			}
			X[i].nCluster = nCenter;
			for( k=0; k<nDimension; k++ )
				Center[nCenter].SumData[k] += X[i].Data[k];
			Center[nCenter].Num++;
			D += Distance[i];
		}
		for(i=0; i<M; i++)
		{
			if(Center[i].Num != 0)
				for( k=0; k<nDimension; k++ )
					Center[i].Data[k] = Center[i].SumData[k]/Center[i].Num;
			else
			{	
				int MaxNum=0;
				for( k=1; k<M; k++)
					MaxNum = Center[i].Num > Center[MaxNum].Num ? i: MaxNum;
				int   Num = Center[MaxNum].Num/2;
				for( k=0; k<nDimension; k++ )
					Center[MaxNum].SumData[k] = 0;
				Center[MaxNum].Num = 0;
				for(k=0; k<N; k++)
				{	
					if(X[k].nCluster != MaxNum)		continue;
					if(Center[i].Num < Num)
					{   
						X[k].nCluster = i;
						for( m=0; m<nDimension; m++)
							Center[i].SumData[m] += X[k].Data[m];
						Center[i].Num++;
					}
					else
					{
						for( m=0; m<nDimension; m++ )
							Center[MaxNum].SumData[m] += X[k].Data[m];
						Center[MaxNum].Num++;
					}
				}
				for( m=0; m<nDimension; m++ )
					Center[i].Data[m] = Center[i].SumData[m] / Center[i].Num;
				if(MaxNum < i)
					for( m=0; m<nDimension; m++ )
						Center[MaxNum].Data[m] = Center[MaxNum].SumData[m] / Center[MaxNum].Num;
			}
		}
	}
	for(i=0; i<M; i++)
	{
		for( m=0; m<nDimension; m++ )
			Y[i].Data[m] = Center[i].Data[m];
		Y[i].Num = Center[i].Num;
	}
	for( i=0; i<M; i++ )
	{
		free( Center[i].Data );
		free( Center[i].SumData );
	}
	free(Center);
	free(Distance);
	return 0;
}

/******************************************************************************
/*	Name:		LBGClusterCor
/*	Function:	Clustering input vectors using LBG algorithm
/*				Using correlation distance
/*	Parameter:	X -- Input vecters
/*				N -- Number of input vectors
/*				Y -- Clustering result
/*				M -- Number of clustering center
/*	Return:		0 -- Correct
/*				1 -- Error
/*
/******************************************************************************/
int LBGClusterCor(VQ_VECTOR *X, int N, VQ_CENTER *Y, int M)
{
	if(N<M)			 return -1;
	int		L=1000, m=1, nCenter, i, j, k;
	int		nDimension = X[0].nDimension;
	double  SumCor0, SumCor;
	struct  VQ_CENTERINFO
	{
		double*	  Data;
		int		  nDimension;
		double*   SumData;
		int		  Num;
	};
	VQ_CENTERINFO	*Center = (VQ_CENTERINFO*)malloc(M*sizeof(VQ_CENTERINFO));
	if(Center == NULL)		return -1;
	double			*Correlation = (double*)malloc(N*sizeof(double));
	if(Correlation == NULL)	return -1;

	for( i=0; i<M; i++)
	{
		Center[i].nDimension = nDimension;
		Center[i].Data = (double*)malloc(sizeof(double)*nDimension);
		Center[i].SumData = (double*)malloc(sizeof(double)*nDimension);
		if( Center[i].Data == NULL || Center[i].SumData == NULL )
		{
			AfxMessageBox( "Memory used up!" );
			return -1;
		}	
		for( j=0; j<nDimension; j++ )
		{
			Center[i].Data[j] = X[i*N/M].Data[j];
			Center[i].SumData[j] = 0;
		}
		Center[i].Num = 0;
	}

	SumCor0=0.001;         SumCor=0.1;	
	while(m<L && fabs(SumCor0-SumCor)/SumCor0>1e-20)
	{
		for(i=0; i<M; i++)
		{
			for( j=0;	j<nDimension; j++ )
				Center[i].SumData[j] = 0;
			Center[i].Num = 0;
		}
		SumCor0 = SumCor;			SumCor = 0;		m++;
		for(i=0; i<N; i++)
		{
			Correlation[i] = 0;
			for(int j=0; j<M; j++)
			{
				double  Cor = GetCorrelation( X[i].Data, Center[j].Data, nDimension);
				if(  Cor > Correlation[i])
				{			
					nCenter = j;
					Correlation[i] = Cor;
				}
			}
			X[i].nCluster = nCenter;
			for( k=0; k<nDimension; k++ )
				Center[nCenter].SumData[k] += X[i].Data[k];
			Center[nCenter].Num++;
			SumCor += Correlation[i];
		}
		for(i=0; i<M; i++)
		{
			if(Center[i].Num != 0)
				for( k=0; k<nDimension; k++ )
					Center[i].Data[k] = Center[i].SumData[k]/Center[i].Num;
			else
			{	
				int MaxNum=0;
				for( k=1; k<M; k++)
					MaxNum = Center[i].Num > Center[MaxNum].Num ? i: MaxNum;
				int   Num = Center[MaxNum].Num/2;
				for( k=0; k<nDimension; k++ )
					Center[MaxNum].SumData[k] = 0;
				Center[MaxNum].Num = 0;
				for(k=0; k<N; k++)
				{	
					if(X[k].nCluster != MaxNum)		continue;
					if(Center[i].Num < Num)
					{   
						X[k].nCluster = i;
						for( m=0; m<nDimension; m++)
							Center[i].SumData[m] += X[k].Data[m];
						Center[i].Num++;
					}
					else
					{
						for( m=0; m<nDimension; m++ )
							Center[MaxNum].SumData[m] += X[k].Data[m];
						Center[MaxNum].Num++;
					}
				}
				for( m=0; m<nDimension; m++ )
					Center[i].Data[m] = Center[i].SumData[m] / Center[i].Num;
				if(MaxNum < i)
					for( m=0; m<nDimension; m++ )
						Center[MaxNum].Data[m] = Center[MaxNum].SumData[m] / Center[MaxNum].Num;
			}
		}
	}
	for(i=0; i<M; i++)
	{
		for( m=0; m<nDimension; m++ )
			Y[i].Data[m] = Center[i].Data[m];
		Y[i].Num = Center[i].Num;
	}
	for( i=0; i<M; i++ )
	{
		free( Center[i].Data );
		free( Center[i].SumData );
	}
	free(Center);
	free(Correlation);
	return 0;
}

/*********************************************************************
/*	Name:		GetCorrelation
/*	Function:	Calculate correlation of two vectors
/*	Parameter:	X -- Vector one
/*				Y -- Vector two
/*				nDimension -- Dimension of the vectors
/*	Return:		Correlation of two vectors
/*	
/*********************************************************************/
double	GetCorrelation( double* X, double*	Y, int nDimension )
{
	double	Correlation=0, DX=0, DY=0;
	for(int i=0; i<nDimension; i++ )
	{
		Correlation += X[i]*Y[i];
		DX += X[i]*X[i];
		DY += Y[i]*Y[i];
	}
	return  Correlation/sqrt( DX*DY );
}

/******************************************************************************
/*	Name:		MaxCluster
/*	Function:	Clustering input vectors using Maximum algorithm
/*	Parameter:	X -- Input vecters
/*				N -- Number of input vectors
/*				Y -- Clustering result
/*				M -- Number of clustering center
/*	Return:		0 -- Correct
/*				1 -- Error
/*
/******************************************************************************/
int MaxCluster(VQ_VECTOR *X, int N, VQ_CENTER *Y, int M)
{
	if(N<M)			 return -1;
	int		m=1;
	struct  VQ_CENTERINFO
	{
		double*	  Data;
		int		  nDimension;
		double*   SumData;
		int		  Num;
	};
	VQ_CENTERINFO	*Center = (VQ_CENTERINFO*)malloc(M*sizeof(VQ_CENTERINFO));
	if(Center == NULL)		return -1;
	double			*Distance = (double*)malloc(N*sizeof(double));
	if(Distance == NULL)	return -1;

	int		nDimension = X[0].nDimension;
	int		i, j, k;
	for(i=0; i<M; i++)
	{
		for( k=0; k<nDimension; k++ )
			Center[i].SumData[k] = 0;
		Center[i].Num = 0;
	}
	double*	SumData = (double*)malloc(sizeof(double)*nDimension);
	for( k=0; k<nDimension; k++ )
		SumData[k]= 0;
	for(i=0; i<N; i++)
		for( k=0; k<nDimension; k++ )
			SumData[k] += X[i].Data[k];	
	for( k=0; k<nDimension; k++ )
		SumData[k]	/= N;	
	
	int  l=0;
	double L=0, Dist;
	for(i=0; i<N; i++)
	{
		Dist = 0;
		for( k=0; k<nDimension; k++ )
			Dist += (X[i].Data[k]-SumData[k])*(X[i].Data[k]-SumData[k]);
		if(Dist > L)
		{
			L = Dist;
			l = i;
		}
	}
	for( k=0; k<nDimension; k++ )
		Center[0].Data[k] = X[l].Data[k];
	for(m=1; m<M; m++)
	{
		double  MaxMinDist = -1;
		int		MaxMin = -1;
		for( j=0; j<N; j++)
		{
			double MinDist = 1e+10;
			for(int k=0; k<m; k++)
			{
				Dist = 0;
				for( k=0; k<nDimension; k++ )
					Dist += (X[j].Data[k] - Center[k].Data[k])*(X[j].Data[k] - Center[k].Data[k]);
				MinDist = min(Dist , MinDist);
			}
			if(MinDist > MaxMinDist)
			{
				MaxMinDist = MinDist;
				MaxMin  = j;
			}
		}
		for( k=0; k<nDimension; k++ )
			Center[m].Data[k] = X[MaxMin].Data[k];
	}
	for(i=0; i<N; i++)
	{	int		Min = -1;
		double  MinDist = 1e+10;
		for(m=0; m<M; m++)
		{
			Dist = 0;
			for( k=0; k<nDimension; k++ )
				Dist += (X[i].Data[k] - Center[m].Data[k])*(X[i].Data[k] - Center[m].Data[k]);
			if(Dist < MinDist)
			{
				MinDist = Dist;
				Min = m;
			}
		}
		X[i].nCluster = Min;
		if(Min<0 || Min>=M)
			return -1;
		for( k=0; k<nDimension; k++ )
			Center[Min].SumData[k] += X[i].Data[k];
		Center[Min].Num++;
	}
	for(m=0; m<M; m++)
		for( k=0; k<nDimension; k++ )
			Center[m].Data[k] = Center[m].SumData[k] / Center[m].Num;
	for(i=0; i<M; i++)
	{
		for( k=0; k<nDimension; k++ )
			Y[i].Data[k] = Center[i].Data[k];
		Y[i].Num = Center[i].Num;
	}
	free( SumData );
	for( i=0; i<M; i++ )
	{
		free( Center[i].Data );
		free( Center[i].SumData );
	}
	free(Center);
	free(Distance);
	return 0;
}


/******************************************************************************
/*	Name:		DumpClusterData
/*	Function:	Dump clustering result to a text file for debugging
/*	Parameter:	FileName -- Dump text file name
/*				X -- Input vecters
/*				N -- Number of input vectors
/*				Y -- Clustering result
/*				M -- Number of clustering center
/*	Return:		0 -- Correct
/*				1 -- Error
/*
/******************************************************************************/
int DumpClusterData(CString FileName, VQ_VECTOR *X, int N, VQ_CENTER *Y, int M)
{
	int		i, j, k;
	int		nDimension = X[0].nDimension;
	FILE *fp = fopen(FileName, "wt");
	for( i=0; i<M; i++)
	{
		fprintf(fp, "Center%02d: ", i);
		for(  k=0; k<nDimension; k++ )
			fprintf( fp, "%5.1f ", Y[i].Data[k] );
		fprintf( fp, "Num=%03d\n", Y[i].Num);
		for( j=0; j<N; j++)
		{	if(X[j].nCluster != i)		continue;
			double Distance = 0;
			for( k=0; k<nDimension; k++)
				Distance += (X[j].Data[k]- Y[i].Data[k])*(X[j].Data[k]-Y[i].Data[k]);
			Distance = sqrt( Distance );
			for( k=0; k<nDimension; k++ )
				fprintf(fp, "  %03d  ", (int)X[j].Data[k] );
			fprintf( fp, " D=%5.1f\n", Distance);
		}
	}
	fclose(fp);
	return 0;
}

