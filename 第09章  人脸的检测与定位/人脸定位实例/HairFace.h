//////////////////////////////////////////////////////////////////////
// HairFace.h: 类CHairFace接口
//////////////////////////////////////////////////////////////////////

#ifndef __HAIRFACE_H
#define __HAIRFACE_H

class CHairFace : public CObject  
{
public:
	RGBQUAD ** m_pSourceData;	//原始图像数据
	int	  m_nWidth;	//宽度
	int   m_nHeight;	//高度
	BYTE  **m_pBinaryArray;	//二值化数组
	bool  m_bBinaryOK;	//标志位，是否完成二值化
public:
	void MarkHairFace();
	CHairFace(RGBQUAD ** source,int width,int height);
	virtual ~CHairFace();

};

#endif // #ifndef __HAIRFACE_H
