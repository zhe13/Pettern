/*Fisher.C
*recognition of handwritten numerals with Fishier Linear Classifier
*/
/*
*说明：一个数字16X16像素，每个像素是灰度值，
*归一化为-1到1的双精度浮点数
*
*struct Sample
*{
*	double data[RAWDATADIM];	//一个点的数据为8 byte
*	double feature[FEADIM];		//特征向量
*	int trueClass;	//真实类别
*	int classifiedClass[10]; //被识别的分类，对应位置1
*	int isClassified; // 1 for true and -1 for false
*};
*例如 6 对应的classifiedClass[10]为：-1-1-1-1-1-11-1-1-1
*
*/

#include <stdio.h>
#include "math.h"
#include "stdlib.h"

#define TRAININGSNUM	 7291	//训练样本数
#define TESTINGSNUM		 2007	//测试样本数
#define RAWDATADIM		 256	//每个数字的像数点数
#define FEADIM			 60	//提取的特征维数

#define SUCCESSFUL		 0
#define FAIL			 -1

struct Sample
{
	double data[RAWDATADIM];	//一个点的数据为8 byte
	double feature[FEADIM];		//特征向量
	int trueClass;	//真实类别
	int classifiedClass[10]; //被识别的分类，对应位置1
	int isClassified; // 1 for true and -1 for false
};

struct Sample trainingSample[TRAININGSNUM];	//训练样本
struct Sample testingSample[TESTINGSNUM];	//测试样本

int points[FEADIM][2];	//特征点
double dirToMap[FEADIM][1];	//映射向量
double meanC1, meanC2;	//第一类，第二类映射后的均值
int nC1, nC2;	//两类的训练样本数

/*******************************************************************
 *两个矩阵相乘
 *参数：A×B＝C
 *      A[m,n]，B[n,k]，C[m,k]
 */
void brmul(a, b, m, n, k, c)
int m, n, k;
double a[], b[], c[];
{
	int i, j, l, u;
	for (i=0; i<=m-1; i++)
		for (j=0; j<=k-1; j++)
		{ 
			u = i*k+j; 
			c[u] = 0.0;
			for (l=0; l<=n-1; l++)
				c[u] = c[u] + a[i*n+l]*b[l*k+j];
		}
		
	return;
}

/****************************************************************
 *矩阵求逆
 *参数：A：矩阵
 *      n：矩阵地维数
 */
int brinv(a, n)
int n;
double a[];
{ 
	int *is, *js, i, j, k, l, u, v;
	double d, p;
	is = (int *) malloc(n*sizeof(int));
	js = (int *) malloc(n*sizeof(int));

	for (k=0; k<=n-1; k++)
	{ 
		d=0.0;
		for (i=k; i<=n-1; i++)
			for (j=k; j<=n-1; j++)
			{ 
				l=i*n+j; 
				p=fabs(a[l]);
				if (p>d) 
				{ 
					d=p; 
					is[k]=i; 
					js[k]=j;
				}
			}

		if (d+1.0==1.0)
		{ 
			free(is); 
			free(js); 
			printf("err**not inv\n");
			return(0);
		}
		if (is[k]!=k)
			for (j=0; j<=n-1; j++)
			{ 
				u=k*n+j; 
				v=is[k]*n+j;
				p=a[u]; 
				a[u]=a[v]; 
				a[v]=p;
			}
        
		if (js[k]!=k)
			for (i=0; i<=n-1; i++)
			{ 
				u=i*n+k; 
				v=i*n+js[k];
				p=a[u]; 
				a[u]=a[v]; 
				a[v]=p;
			}
				
		l=k*n+k;
		a[l]=1.0/a[l];
		for (j=0; j<=n-1; j++)
			if (j!=k)
			{ 
				u=k*n+j; 
				a[u]=a[u]*a[l];
			}
				
		for (i=0; i<=n-1; i++)
			if (i!=k)
				for (j=0; j<=n-1; j++)
					if (j!=k)
					{ 
						u=i*n+j;
						a[u]=a[u]-a[i*n+k]*a[k*n+j];
					}
        
		for (i=0; i<=n-1; i++)
			if (i!=k)
			{ 
				u=i*n+k; 
				a[u]=-a[u]*a[l];
			}
	}
    
	for (k=n-1; k>=0; k--)
	{ 
		if (js[k]!=k)
			for (j=0; j<=n-1; j++)
			{ 
				u=k*n+j; 
				v=js[k]*n+j;
				p=a[u]; 
				a[u]=a[v]; 
				a[v]=p;
			}
        
		if (is[k]!=k)
			for (i=0; i<=n-1; i++)
			{ 
				u=i*n+k; 
				v=i*n+is[k];
				p=a[u]; 
				a[u]=a[v]; 
				a[v]=p;
			}
	}
	
	free(is); 
	free(js);
	return(1);
}

/*
*retrieveSample (s, n, dfname, cfname)

*funtion to retrieve data from binary data file
*s: 样本数组的头指针，trainingSample or testingSample
*n: number of samples
*dfname: file name of sample data
*cfname: file name of information on true class
*
*/
int retrieveSample (s, n, dfname, cfname)
struct Sample *s;
int n;
char *dfname, *cfname;
{
	FILE *fdf, *fcf;
	
	int sclass[10];

	int i, j;
	//open datafile
	if	((fdf = fopen (dfname, "rb")) == NULL)
	{
		printf ("Can't open file %s\n", dfname);
		return FAIL;
	}
	
	//open classfile
	if ((fcf = fopen (cfname, "rb")) == NULL)
	{
		printf ("Can't open file %s\n", cfname);
		return FAIL;
	}
	
	for (i = 0; i < n; i++)
	{
		fread (s[i].data, sizeof (double), RAWDATADIM, fdf);//retrieve gray data
		fread (sclass, sizeof (int), 10, fcf);
		for (j = 0; j < 10; j++)
		{
			(*(s + i)).classifiedClass[j] = -1; //initiate -1
			if (sclass[j] == 1)
				(*(s + i)).trueClass = j;  //load trueClass
		}
		(*(s + i)).isClassified = -1;//have not been classified

	}

	fclose (fdf);
	fclose (fcf);
	return SUCCESSFUL;
}

/*
int selPoints (serial1,serial2)
选取特征点
serial1:第一类序号
serial2:第二类序号
*/

int selPoints (serial1,serial2)

int serial1;
int serial2;

{
	double sumC1[RAWDATADIM], sumC2[RAWDATADIM],diff[RAWDATADIM];
	int i,j;
	int n1, n2;

	double uBound, lBound;
	int index;

	n1 = n2 = 0;
	for (i = 0; i < RAWDATADIM; i++)
	{
		sumC1[i] = 0;
		sumC2[i] = 0;
	}

	for (i = 0; i < TRAININGSNUM; i++)
	{
		if (trainingSample[i].trueClass == serial1)
		{
			n1++;
			for (j = 0; j < RAWDATADIM; j++)
				sumC1[j] += trainingSample[i].data[j];
		}
		else if(trainingSample[i].trueClass == serial2) 
		{
			n2++;
			for (j =0; j < RAWDATADIM; j++)
				sumC2[j] += trainingSample[i].data[j];
		}
	}

	if (n1 == 0 || n2 == 0)
		return FAIL;

	for (i = 0; i < RAWDATADIM; i++)
	{
		sumC1[i] = sumC1[i]/n1;
		sumC2[i] = sumC2[i]/n2;
		diff[i] = fabs(sumC1[i] - sumC2[i]);
	}
	
	//下面寻找第一类和第二类偏差最小的点为特征点

	lBound = 0; uBound = 3;
	//lBound指示当前一轮的最大值，uBound指示前一轮的最大值
	for (j = 0; j < FEADIM; j++)
	{
		for (i = 0; i < RAWDATADIM; i++)
			if (lBound < diff[i] && uBound > diff[i])
			{
				lBound = diff[i];//find the Maximum
				index = i;
			}
		uBound = lBound;
		lBound = 0;
		points[j][0] = index / ((int)sqrt (RAWDATADIM));
		points[j][1] = index % ((int)sqrt (RAWDATADIM));
	}
	return SUCCESSFUL;
}


/*
void genFeature (s,n)
特征提取
s:样本结构struct Sample的指针， trainingSample or testingSample
n:number of samples
*/
void genFeature (s,n)
struct Sample *s;
int n;

{
	int i, j, t;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < FEADIM; j++)
		{
			t = points[j][0] * (int)sqrt(RAWDATADIM) + points[j][1];
			s[i].feature[j] = s[i].data[t];
		}
	}
	return;
}


/*
int Fisher (serial1,serial2)

serial1第一类的序号，serial2第二类的序号
1、返回投影向量double dirToMap[FEADIM][1]，把多维空间映射到一维空间
2、计算meanC1,meanC2，即两类的均值
3、计算nC1,nC2，两类的样本个数
*/
int Fisher (serial1, serial2)
int serial1;
int serial2;

{
	struct Sample *s;
	double meanVector1[FEADIM], meanVector2[FEADIM], diffVector[FEADIM];
	double sumC1[FEADIM], sumC2[FEADIM];

	double SW[FEADIM][FEADIM];//样本总类内离散度矩阵
	double tempMtrx[FEADIM][FEADIM];
	double tempV1[FEADIM][1];
	double tempV2[1][FEADIM];
	double tempV[1][1];

	int i, j, k;
	int flag;

	s = trainingSample;

	nC1 = nC2 = 0;//初始化
	
	for (j = 0; j < FEADIM; j++)
	{
		sumC1[j] = 0;
		sumC2[j] = 0;
		for (k = 0; k < FEADIM; k++)
			SW[j][k] = 0;
	}

	for (i = 0; i < TRAININGSNUM; i++)
	{
		if (s[i].trueClass == serial1)
		{
			++nC1;//第一类样本数增1
			for (j = 0; j < FEADIM; j++)
			{
				sumC1[j] += s[i].feature[j]; 
			}
		}
		if (s[i].trueClass == serial2) 
		{
			++nC2;//第二类样本数增1
			for (j = 0; j < FEADIM; j++)
			{
				sumC2[j] += s[i].feature[j]; 
			}
		}
	}

	if (nC1 == 0 || nC2 == 0)//某一类没有样本，返回错误
	{
		return FAIL;
	}

	for (j = 0; j < FEADIM; j++)
	{
		meanVector1[j] = sumC1[j]/nC1;
		meanVector2[j] = sumC2[j]/nC2;
		diffVector[j] = meanVector1[j] - meanVector2[j];
	}

	for (i = 0; i < TRAININGSNUM; i++)
	{
		if (s[i].trueClass == serial1 || s[i].trueClass == serial2)
		{
			if (s[i].trueClass == serial1)
				for (j = 0; j < FEADIM; j++)
				{
					tempV1[j][0]  = s[i].feature[j] - meanVector1[j];
					tempV2[0][j] = tempV1[j][0];
				}
			if (s[i].trueClass == serial2) 
				for (j = 0; j < FEADIM; j++)
				{
					tempV1[j][0] = s[i].feature[j] - meanVector2[j];
					tempV2[0][j] = tempV1[j][0];
				}

		//向量求积，得一个样本的离散度矩阵
		//	tempMtrx[FEADIM][FEADIM] = tempV1 * tempV2 
		
			brmul(tempV1,tempV2,FEADIM,1,FEADIM,tempMtrx);
		
			for (j = 0; j < FEADIM; j++)
				for (k = 0; k < FEADIM; k++)
					SW[j][k] =SW[j][k] + tempMtrx[j][k];
		}

	}

	//归一化SW矩阵，以免求逆后数字太小而引起舍入误差的增加
	for (j = 0; j <FEADIM; j++)
		for (k = 0; k < FEADIM; k++)
			SW[j][k] = SW[j][k] / (nC1 + nC2);


	//下面求dirToMap, meanC1, meanC2
	//dirToMap = SW- * (meanVector1 - meanVector2)
	//meanC1 = T(dirToMap) * meanVector1
	//meanC2 = T(dirToMap) * meanVector2
	for (j = 0; j < FEADIM; j++)
		tempV1[j][0] = diffVector[j];
	
	//矩阵求逆
	flag = brinv(SW,FEADIM);
	if (flag != 1)
		return FAIL;

	brmul(SW, tempV1, FEADIM, FEADIM, 1, dirToMap);//得到dirToMap

	for (j = 0; j < FEADIM; j++)
	{
		tempV2[0][j] = dirToMap[j][0];//转置
		tempV1[j][0] = meanVector1[j];
	}
	brmul(tempV2, tempV1, 1, FEADIM, 1, tempV);
	meanC1 = tempV [0][0];//得到meanC1

	for (j = 0; j < FEADIM; j++)
	{
		tempV1[j][0] = meanVector2[j];
	}
	brmul(tempV2, tempV1, 1, FEADIM, 1, tempV);
	meanC2 = tempV[0][0];//得到meanC2

	return SUCCESSFUL;
}


/*
classifier (s)
s: certain testing sample
classifying using
dirToMap ,meanC1,meanC2, feature
分类时把多类问题转化为两类问题，可能性最大的类作为判决结果
如：0类和1类比较，可能性大的再和3类比较，依次类推
*/
int classifier (s)
struct Sample *s;
{
	
	int serial1;
	int serial2;

	int flag;//成功与否的标识
	double critical;//判决临界值
	double tempV[1][1];
	double tempV1[FEADIM][1],tempV2[1][FEADIM];
	int count, j;
	
	serial1 =0;//第一类初始化为0

	for (count = 1; count < 10; count++)
	{
		serial2 = count;

		//选出特征点
		flag = selPoints (serial1, serial2);
		if (flag == FAIL)
			return FAIL;

		//提取特征
		genFeature (trainingSample, TRAININGSNUM);
		genFeature (testingSample, TESTINGSNUM);

		//计算分类器
		if (Fisher (serial1, serial2) != SUCCESSFUL)
			return FAIL;


		//开始判别

		if (nC1 ==0 || nC2 ==0)
			return FAIL;

		critical = (meanC1 * nC1 + meanC2 * nC2) / (nC1 + nC2);

		for (j = 0; j < FEADIM; j++)
		{
			tempV2[0][j] = dirToMap[j][0];//转置
			tempV1[j][0] = (*s).feature[j];
		}

		brmul(tempV2, tempV1, 1, FEADIM, 1, tempV);
	
		if (tempV[0][0] < critical)
			serial1 = serial2;
	}
				
	(*s).isClassified = 1;
	(*s).classifiedClass[serial1] = 1;

	return SUCCESSFUL;
}


/*
void ftestingSample (resultf)
char *resultf：结果输出文件名，
调用classifier ()，作判决，输出结果
*/
void ftestingSample (resultf)

char *resultf;
{
	struct Sample *s;
	FILE *rf;
	
	int flag;
	int i, j, k, tempClass;
	int rightNum, errorNum;
	double ratio;
		
	s = testingSample;

	if	((rf = fopen (resultf, "a")) == NULL)
	{
		printf ("Can't open file %s\n", resultf);
		return;
	}

	errorNum = 0;
	for (i = 899; i < TESTINGSNUM; i++)
	{	
		flag = classifier (s + i);//判第i个样本分类
		if (flag == FAIL)
			return;
			
		fprintf (rf, "Sample %d (%d):\n", i, s[i].trueClass);
		fprintf (rf, "Classified to :");
		
		printf ("Sample %d (%d):\n", i, s[i].trueClass);
		printf ("Classified to :");

		k = 0;

		for (j = 0; j < 10; j++)
		{
			if (s[i].classifiedClass[j] == 1)
			{
				k++;
				tempClass = j;
				fprintf (rf, "%d ", j);
				printf ("%d ", j);
			}
		}
		
		if (k !=1 || tempClass != s[i].trueClass)
		{
			fprintf (rf, "\nError\n\n");
			printf ("Error\n");
			errorNum++;
		}	
		else
		{
			fprintf (rf, "\n\n\n");
			printf ("\n");
		}	
	}
	
	//统计			
	rightNum = TESTINGSNUM - errorNum;
	ratio =  (double)rightNum/(double)TESTINGSNUM;
	fprintf (rf, "\n\nStatistics\n");
	fprintf (rf, "------------------------------------------\n\n");
	fprintf (rf,"Right :%d		Error:%d	Ratio:%f\n",
		rightNum, errorNum, ratio);

	fclose (rf);
	return;
}


void main (void)
{
	char *dfname1 = "D:\\usps\\trainData.bina";
	char *cfname1 = "D:\\usps\\trainDataResult.bina";
	char *dfname2 = "D:\\usps\\testData.bina";
	char *cfname2 = "D:\\usps\\testDataResult.bina";
	char *resultf = "D:\\usps\\result.txt";

	int flag;

	//提取数据
	flag = retrieveSample (
		trainingSample, TRAININGSNUM, dfname1, cfname1);
	if (flag != SUCCESSFUL) return;
	
	flag = retrieveSample (
		testingSample, TESTINGSNUM, dfname2, cfname2);
	if (flag != SUCCESSFUL) return;

	//测试样本
	ftestingSample (resultf);
}
