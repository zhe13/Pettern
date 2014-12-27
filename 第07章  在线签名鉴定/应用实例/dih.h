//dih.h
#ifndef dih_h
#define dih_h

#include<math.h>
#define DUANBILENGTH 30.0

struct dihfrequency{
	double f0;
	double f1;
	double f2;
	double f3;
};

typedef struct dihfrequency DIHFQ;
typedef struct dihfrequency* PDIHFQ;

//////////////////////////////////////////////////////////////////////////////////
//计算方向，x[]，y[]，dire[]分别是x,y坐标，方向数组，length是数组长度
void dih_compute_direction(double x[],double y[],int dire[],int length);

//////////////////////////////////////////////////////////////////////////////////
//计算频率
//dire[]是方向数组，temp保存结果
void dih_compute_frequency(int dire[],int length,PDIHFQ temp);

////////////////////////////////////////////////////////////////////////////////////
//计算频率，加上距离修正
void dih_compute_frequency_dist(int dire[],double x[],double y[],int length,PDIHFQ temp);

/////////////////////////////////////////////////////////////////////////////////////////
//计算频率，加上压力修正
void dih_compute_frequency_pressure(int dire[],double pressure[],int length,PDIHFQ temp);

/////////////////////////////////////////////////////////////////////////////////////////
//同时加上压力和频率修正
void dih_compute_frequency_dp(int dire[],double pressure[],double x[],double y[],int length,PDIHFQ temp);

//////////////////////////////////////////////////////////////////////////////////////////
//计算距离
double dih_dist_compute(PDIHFQ fq1,PDIHFQ fq2);

#endif
