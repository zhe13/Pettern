//////////////////////////////////////////////////////////////////////
// LikelyHood.h: 类CLikelyHood的接口
//////////////////////////////////////////////////////////////////////

#ifndef __LIKELYHOOD_H
#define __LIKELYHOOD_H

#include <math.h>
#include "Dib.h"

#define 	B_Mean  117.4361;
#define 	R_Mean  156.5599;
#define 	Brcov00 160.1301;
#define 	Brcov01 12.1430 ;
#define 	Brcov10 12.1430 ;
#define 	Brcov11 299.4574;

typedef struct TCbCr
{
	double Cb;
	double Cr;
}CbCr;

class CLikelyHood : public CObject  
{
public:
	CLikelyHood();
	CLikelyHood(RGBQUAD **source,int width,int height);
	virtual ~CLikelyHood();
public:
	void CalLikeHood();
	bool CalBinary();
	void filter(double** source,int m_nWidth,int m_nHeight);
	int  CalParameter(CString DirectPath);
	TCbCr CalCbCr(int R,int G,int B);
public:
	double bmean;
	double rmean;
	double brcov[2][2];

	int	m_nWidth;	//图像宽度
	int m_nHeight;	//图像高度
	RGBQUAD **m_pSourceData;	//原始数据
	double  **m_pLikeliHoodArray;	//相似度数组（二维）
	BYTE    **m_pBinaryArray;	//二值化数组（二维）

	bool m_bBinaryReady;	//标志位，判断是否完成二值化
private:
	bool m_bLikeliHoodReady;	//标志位，判断是否计算好相似度
};

#endif // #ifndef __LIKELYHOOD_H
