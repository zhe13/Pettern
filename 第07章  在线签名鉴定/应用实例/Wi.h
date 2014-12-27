// Wi.h: interface for the CWi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WI_H__4C7EAE8A_D523_47A7_BDB0_1FD3D8756BCB__INCLUDED_)
#define AFX_WI_H__4C7EAE8A_D523_47A7_BDB0_1FD3D8756BCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "movement.h"
#include "dih.h"
#include "dtwrecoge.h"
#include "vdtwrecoge.h"
#include "Clustering.h"
#include "hmm.h"
#include "nrutils.h"


#define MAXTRAINSETNUM		1000	//最多训练样本数
#define MAXTESTSETNUM		200		//最多测试样本数
#define CLASSNUM			2		//分类数
#define RAWDATADIM			2000	//原始数据维数
#define TAPEDDATADIM		1024
#define FEADIM				20		//最大特征维数
#define TRAINSETFLAG		0		//训练样本标志
#define TESTSETFLAG			1		//测试样本标志

#ifndef MYRECOGE_H
#define MYRECOGE_H
#define DTWRESULTNUM	300	/*定义动态时间弯折数组结果的长度*/
#endif

#define MAXTOTALPRESSURE 255
#define IMAGEHEIGHT	128
#define IMAGEWIDTH	256

#define STRUCTSAMPLELEN sizeof(struct CWi::Sample)

#define PI    3.14159265358979323846
#define ZERO 1.0
#define THRESHOLD 5.0  //阈值
#define SQUARE(x) x*x

#define VQ_M 16


#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct tagPenPoint{
	int		x;  //X坐标
	int		y;  //Y坐标
	int		pressure;  //压力
	DWORD	time;  //时间
}PenPoint; //数据文件中点的结构

typedef struct {
	int		length;
	int		method;		
	double	threshold;
}TempHeader; //识别方法中文件头结构

//定义了一些宏，表示所利用的方法
#define METHOD_PRES 0
#define METHOD_X	1
#define METHOD_Y	2
#define METHOD_XY   3
#define METHOD_MOVE 4
#define METHOD_DIH  5
#define METHOD_VEC  6
#define METHOD_HMM  7

typedef struct {
	double r, i;
} complex; //复数结构


class CWi : public CObject  
{
public:
	CWi();
	virtual ~CWi();

public:
	struct Sample
	{
		double pressTotal[RAWDATADIM]; //总的压力
		double pressTotal2[RAWDATADIM];
		double xLoc[RAWDATADIM];			//按时间顺序的坐标
		double yLoc[RAWDATADIM];			//按时间顺序的坐标
 		double xLoc2[RAWDATADIM];
		double yLoc2[RAWDATADIM];
		double pressA[RAWDATADIM];		//A点压力数据
		double pressB[RAWDATADIM];		//B点压力数据
		double pressC[RAWDATADIM];		//C点压力数据
		double press[TAPEDDATADIM];		//采样后的压力数据
		double direction[RAWDATADIM];  //方向
		double imgPixel[IMAGEWIDTH][IMAGEHEIGHT];

		double speed[RAWDATADIM]; //速度
		PenPoint point[RAWDATADIM]; //点
		mvector  dataVec[RAWDATADIM];
		struct   VQ_VECTOR  vq_vector[RAWDATADIM];
		int	   vq_feature[RAWDATADIM];

		int    effectDataNum;
		double width;
		double height;
		double maxPressTotal;
		//PenPoint point[RAWDATADIM];
		
		double feature[FEADIM];		//特征向量		
		int    trueClass;	//真实类别
		int    classifiedClass[CLASSNUM]; //被识别的分类，对应位置1
		int    isClassified; // 1 for true and -1 for false
	};

	CStringArray trainSetDataFilePath;	//训练样本集的文件路径
	CStringArray testSetDataFilePath;	//测试样本集的文件路径

	CPtrArray trainSampleArray;			//struct Sample 是元素
	CPtrArray testSampleArray;			//struct Sample 是元素
	double dtwtemplate[RAWDATADIM];
	double dtwtemplatex[RAWDATADIM];
	double dtwtemplatey[RAWDATADIM];

	mvector dtwtemplatev[RAWDATADIM];
	int		templenvec;
	double thresholdvec;

	struct   VQ_VECTOR  vq_vector[RAWDATADIM];
	int	   vq_feature[RAWDATADIM];

	double threshold;
	double thresholdx;
	double thresholdy;
	double thresholdxy;
	double thresholdhmm;
	int	   templenx;
	int    templeny;
	int	   templenxy;
	int    templen;
	FEAGURE_MV feat;
	DIHFQ  freq;
	double thresholdfeat;
	double thresholdfreq;

	struct VQ_CENTER	vq_center[VQ_M];
	HMM	   hmm;
	
// Operations
public:
	void   AddSampleSetPath (CString strPath, int flag); //0 for trainset, 1 for testset
	void   DelSampleSetPath (int flag); //0 for trainset, 1 for testset
	
	void   ParseDataFromFile1 (CWi::Sample *s, CString filePath); //针对不同的格式读取文件
	void   ParseDataFromFile2 (CWi::Sample *s, CString filePath);
	void   ParseDataFromFile3 (CWi::Sample *s, CString filePath);
	void   RetrieveSample (CStringArray* samplePathArrayRef, 
							 CPtrArray* sampleArrayRef);
	void   ConstructTotal (CWi::Sample* s);//计算总压和坐标
	void   NormalizeSample (double* data, int dataLen);//归一化
	void   NormalizeSample (double *data, double& max, double& min, 
					int dataLen); //归一化算法
	void   NormalizeImage (CWi::Sample* s); //归一化图形
	void   FTSample (double* dataSource, double* dataDest);
	void   DiffSample (double* dataSource, double* dataDest, int dataLen);

	void   FilterNoise (CWi::Sample* s, int critical);//去噪
	void   ProjectionFeature(CWi::Sample* s, int num);
	void   ConstructImage (CPtrArray* sampleArrayRef);
	void   PreProcSample (CPtrArray* sampleArrayRef, int flag);
	void   SamplePress1(double *src,double *dst,int datalen,int inter);
	void   SamplePress2(double *src,double *dst,int datalen,int inter);
	void   Rotation(double *posX, double *posY,int dataLen,double rotAngle);//旋转图象
	void   MedianFilter(double *data,int dataLen); //中值滤波
 	
    void   lowpassfilter(double *data,double threshold,unsigned long dataLen);//低通滤波
	void   fft(complex *td, complex *fd, int r);//fft算法
    void   ifft(complex *fd, complex *td, int r); //逆fft算法

	double CalculateAverage(double *data,int dataLen);//计算平均值
	void   AverageNormalize(double *data,int dataLen,double value);//均值归一化
	int    WaveCrest(double *src,double *dst,int *pos,int datalen,int threshold);
	//一些求距离的函数
	double OriginalDistance(int sample1,int sample2);
	double WaveCrestPosDistance(int sample1,int sample2);
	double WaveCrestDistance(int sample1,int sample2);
	double XposDistance(int sample1,int sample2);
	double YposDistance(int sample1,int sample2);
	double XYposDistance(int sample1,int sample2);
	void   CalDirection(double *angle,double *xLoc,double *yLoc,int dataLen);
	void   Direction(int sample);
	//一些计算模板的函数
	double GenTemplatePress();
	int    RecogTemplatePress(double *distance,int index);
	double GenTemplateXpos();
	int    RecogTemplateXpos(double *distance,int index);
	double GenTemplateYpos();
	int    RecogTemplateYpos(double *distance,int index);
	double GenTemplateXY();
	int    RecogTemplateXY(double *distance,int index);
	int    RecogMovement(double *distance,int index);
	int	   RegDih(double *distance,int index);
	void   GenVector(CPtrArray* sampleArrayRef);
	double GenTemplateVector();
	int    RecogTemplateVec(double *distance,int index);
	void   SpeedCurve(CWi::Sample* s);
	void   GenVQVector(CPtrArray* sampleArrayRef);
	void   VQCluster();
	void   GenVQTemplate();
	void   GenHMM();
	int    RecogHMM(double *distance, int index);
	void   GenVQVector();

	//一些分类函数
	void   VQClassify(CWi::Sample *s);
	int	   VQClassify(struct VQ_VECTOR *vq, struct VQ_CENTER *vc);
	void   OnDirection();
	void   OnMovement();
	
	//保存各种格式的模板
	void   SaveTemplatePress(char * FileName);
	void   SaveTemplateXpos(char * FileName);
	void   SaveTemplateYpos(char * FileName);
	void   SaveTemplateXY(char * FileName);
	void   SaveMovement(char * FileName);
	void   SaveDih(char * FileName);
	void   SaveTemplateVec(char * FileName);
	void   SaveHMM(char * FileName);

	//装载各种格式的模板
	int   LoadTemplatePress(char * FileName);
	int   LoadTemplateXpos(char * FileName);
	int   LoadTemplateYpos(char * FileName);
	int   LoadTemplateXY(char * FileName);
	int   LoadMovement(char * FileName);
	int   LoadDih(char * FileName);
	int   LoadTemplateVec(char * FileName);
	int   LoadHMM(char * FileName);
	double PoHMM(CWi::Sample *s);
};

#endif // !defined(AFX_WI_H__4C7EAE8A_D523_47A7_BDB0_1FD3D8756BCB__INCLUDED_)
