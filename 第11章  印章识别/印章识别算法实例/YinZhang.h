// YinZhang.h
// 印章图像处理的一些接口
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YINZHANG_H_INCLUDED_)
#define AFX_YINZHANG_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CYinZhang  
{
public:
	void FeatureExtract();
	void EroseBackground(RGBQUAD& refer);
	BYTE** ImageArray;	//图像数组（灰度化及二值化）
	void LoadImage(CString &FilePathName);//装载图像
	RGBQUAD** m_tResPixelArray;	//变化后图像数据（RGB格式）
	RGBQUAD** m_tOriPixelArray;	//原始图像数据（RGB格式）
	double GlobalMass;		//总体质量
	double GlobalCentroidX;	//总体质心
	double GlobalCentroidY;
	double PrintMass;		//印章质量
	double PrintCentroidX;	//印章质心
	double PrintCentroidY;
	double CentroidDistance;	//质心距
	long ImageWidth;	//图像宽度
	long ImageHeight;	//图像高度
	CYinZhang();
	virtual ~CYinZhang();

};

#endif // !defined(AFX_YINZHANG_H_INCLUDED_)
