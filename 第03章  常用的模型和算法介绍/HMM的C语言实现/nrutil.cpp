//nrutil.cpp
#include "StdAfx.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

//报告错误
void nrerror(char *error_text)
{
	printf("Numerical Recipes run-time error...\n");
	printf("%s\n",error_text);
	printf("...now exiting to system...\n");
	exit(1);
}

/*****************************************************************************
 * 函数名称：vector
 * 功能：申请一个实数数组
 * 参数：nl：数组的最低下标
 *       nh：数组的最高下标
 * 返回：数组地址
 */
float *vector(long nl,long nh)
{
	float *v;

	v=(float *)calloc((unsigned) (nh-nl+1),sizeof(float));
	if (!v) nrerror("allocation failure in vector()");
	return v-nl;
}

/*****************************************************************************
 * 函数名称：ivector
 * 功能：申请一个整数数组
 * 参数：nl：数组的最低下标
 *       nh：数组的最高下标
 * 返回：数组地址
 */
int *ivector(long nl,long nh)
{
	int *v;

	v=(int *)calloc((unsigned) (nh-nl+1),sizeof(int));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl;
}

/*****************************************************************************
 * 函数名称：cvector
 * 功能：申请一个无符号字符数组
 * 参数：nl：数组的最低下标
 *       nh：数组的最高下标
 * 返回：数组地址
 */
unsigned char *cvector(long nl,long nh)
{
	unsigned char *v;

	v=(unsigned char *)calloc((unsigned) (nh-nl+1),sizeof(unsigned char));
	if (!v) nrerror("allocation failure in cvector()");
	return v-nl;
}

/*****************************************************************************
 * 函数名称：lvector
 * 功能：申请一个长整数型数组
 * 参数：nl：数组的最低下标
 *       nh：数组的最高下标
 * 返回：数组地址
 */
unsigned long *lvector(long nl,long nh)
{
	unsigned long *v;

	v=(unsigned long *)calloc((unsigned) (nh-nl+1),sizeof(unsigned long));
	if (!v) nrerror("allocation failure in lvector()");
	return v-nl;
}

/*****************************************************************************
 * 函数名称：dvector
 * 功能：申请一个双精度实数数组
 * 参数：nl：数组的最低下标
 *       nh：数组的最高下标
 * 返回：数组地址
 */
double *dvector(long nl,long nh)
{
	double *v;

	v=(double *)calloc((unsigned) (nh-nl+1),sizeof(double));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl;
}

/*****************************************************************************
 * 函数名称：matrix
 * 功能：申请一个实数二维数组（矩阵）
 * 参数：nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 返回：数组地址
 */
float **matrix(long nrl,long nrh,long ncl,long nch)
{
	int i;
	float **m;

	m=(float **) calloc((unsigned) (nrh-nrl+1),sizeof(float*));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(float *) calloc((unsigned) (nch-ncl+1),sizeof(float));
		if (!m[i]) nrerror("allocation failure 2 in matrix()");
		m[i] -= ncl;
	}
	return m;
}

/*****************************************************************************
 * 函数名称：dmatrix
 * 功能：申请一个双精度实数二维数组（矩阵）
 * 参数：nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 返回：数组地址
 */
double **dmatrix(long nrl,long nrh,long ncl,long nch)
{
	int i;
	double **m;

	m=(double **) calloc((unsigned) (nrh-nrl+1),sizeof(double*));
	if (!m) nrerror("allocation failure 1 in dmatrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(double *) calloc((unsigned) (nch-ncl+1),sizeof(double));
		if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
		m[i] -= ncl;
	}
	return m;
}

/*****************************************************************************
 * 函数名称：imatrix
 * 功能：申请一个整数二维数组（矩阵）
 * 参数：nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 返回：数组地址
 */
int **imatrix(long nrl,long nrh,long ncl,long nch)
{
	int i,**m;

	m=(int **)calloc((unsigned) (nrh-nrl+1),sizeof(int*));
	if (!m) nrerror("allocation failure 1 in imatrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(int *)calloc((unsigned) (nch-ncl+1),sizeof(int));
		if (!m[i]) nrerror("allocation failure 2 in imatrix()");
		m[i] -= ncl;
	}
	return m;
}

/*****************************************************************************
 * 函数名称：cmatrix
 * 功能：申请一个无符号字符型二维数组（矩阵）
 * 参数：nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 返回：数组地址
 */
unsigned char **cmatrix(long nrl,long nrh,long ncl,long nch)
{
	int i;
	unsigned char **m;

	m=(unsigned char **) calloc((unsigned) (nrh-nrl+1),sizeof(unsigned char*));
	if (!m) nrerror("allocation failure 1 in dmatrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(unsigned char *) calloc((unsigned) (nch-ncl+1),sizeof(unsigned char));
		if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
		m[i] -= ncl;
	}
	return m;
}

/*****************************************************************************
 * 函数名称：submatrix
 * 功能：求一个二维矩阵的子矩阵
 * 参数：a：二维矩阵的首地址
 *       oldrl：数组的行最低下标
 *       oldrh：数组的行最高下标
 *       oldcl：数组的列最低下标
 *       oldch：数组的列最高下标
 *       newrl：新数组的行最低下标
 *       newcl：新数组的列最低下标
 * 返回：数组地址
 */
float **submatrix(float **a,long oldrl,long oldrh,long oldcl,long oldch,long newrl,long newcl)
{
	int i,j;
	float **m;

	m=(float **) calloc((unsigned) (oldrh-oldrl+1),sizeof(float*));
	if (!m) nrerror("allocation failure in submatrix()");
	m -= newrl;

	for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+oldcl-newcl;

	return m;
}

/*****************************************************************************
 * 函数名称：convert_matrix
 * 功能：将一个实数一维数组转化为二维数组（矩阵）
 * 参数：a：原一维数组
 *       nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 返回：二维数组地址
 */
float **convert_matrix(float *a,long nrl,long nrh,long ncl,long nch)
{
	int i,j,nrow,ncol;
	float **m;

	nrow=nrh-nrl+1;
	ncol=nch-ncl+1;
	m = (float **) calloc((unsigned) (nrow),sizeof(float*));
	if (!m) nrerror("allocation failure in convert_matrix()");
	m -= nrl;
	for(i=0,j=nrl;i<=nrow-1;i++,j++) m[j]=a+ncol*i-ncl;
	return m;
}

/*****************************************************************************
 * 函数名称：free_vector
 * 功能：释放一个实数一维数组
 * 参数：nl：数组的行最低下标
 *       nh：数组的行最高下标
 * 无返回值
 */
void free_vector(float *v,long nl,long nh)
{
	free((char*) (v+nl));
}

/*****************************************************************************
 * 函数名称：free_dvector
 * 功能：释放一个整型一维数组
 * 参数：nl：数组的行最低下标
 *       nh：数组的行最高下标
 * 无返回值
 */
void free_ivector(int *v,long nl,long nh)
{
	free((char*) (v+nl));
}

/*****************************************************************************
 * 函数名称：free_vector
 * 功能：释放一个无符号字符型一维数组
 * 参数：nl：数组的行最低下标
 *       nh：数组的行最高下标
 * 无返回值
 */
void free_cvector(unsigned char *v,long nl,long nh)
{
	free((char*) (v+nl));
}

/*****************************************************************************
 * 函数名称：free_vector
 * 功能：释放一个长整型一维数组
 * 参数：nl：数组的行最低下标
 *       nh：数组的行最高下标
 * 无返回值
 */
void free_lvector(unsigned long *v,long nl,long nh)
{
	free((char*) (v+nl));
}

/*****************************************************************************
 * 函数名称：free_vector
 * 功能：释放一个双精度一维数组
 * 参数：nl：数组的行最低下标
 *       nh：数组的行最高下标
 * 无返回值
 */
void free_dvector(double *v,long nl,long nh)
{
	free((char*) (v+nl));
}

/*****************************************************************************
 * 函数名称：free_matrix
 * 功能：释放一个实数二维数组（矩阵）
 * 参数：m：原数组地址
 *       nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 无返回值
 */
void free_matrix(float **m,long nrl,long nrh,long ncl,long nch)
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

/*****************************************************************************
 * 函数名称：free_dmatrix
 * 功能：释放一个双精度二维数组（矩阵）
 * 参数：m：原数组地址
 *       nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 无返回值
 */
void free_dmatrix(double **m,long nrl,long nrh,long ncl,long nch)
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

/*****************************************************************************
 * 函数名称：free_imatrix
 * 功能：释放一个整型二维数组（矩阵）
 * 参数：m：原数组地址
 *       nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 无返回值
 */
void free_imatrix(int **m,long nrl,long nrh,long ncl,long nch)
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

/*****************************************************************************
 * 函数名称：free_cmatrix
 * 功能：释放一个无符号字符二维数组（矩阵）
 * 参数：m：原数组地址
 *       nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 无返回值
 */
void free_cmatrix(unsigned char **m,long nrl,long nrh,long ncl,long nch)
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

/*****************************************************************************
 * 函数名称：free_submatrix
 * 功能：释放一个子二维数组（矩阵）
 * 参数：b：原数组地址
 *       nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 无返回值
 */
void free_submatrix(float **b,long nrl,long nrh,long ncl,long nch)
{
	free((char*) (b+nrl));
}
/*****************************************************************************
 * 函数名称：free_convert_matrix
 * 功能：释放转化后的二维数组（矩阵）
 * 参数：b：原数组地址
 *       nrl：数组的行最低下标
 *       nrh：数组的行最高下标
 *       ncl：数组的列最低下标
 *       nch：数组的列最高下标
 * 无返回值
 */
void free_convert_matrix(float **b,long nrl,long nrh,long ncl,long nch)
{
	free((char*) (b+nrl));
}
