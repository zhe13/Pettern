// YinZhang.cpp
// 印章图像处理的一些接口
//
//////////////////////////////////////////////////////////////////////

#include "YinZhang.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CYinZhang::CYinZhang()
{
	m_tOriPixelArray = NULL;//原始位图数据
	m_tResPixelArray = NULL;//参考位图数据
}

CYinZhang::~CYinZhang()
{

}

////////////////////////////////////////////////////////////////////
//功能：装载图像
//参数：FilePathName－图像文件路径名
void CYinZhang::LoadImage(CString &FilePathName)
{
	int i,j;
	//检测是否为空，不为空则要释放内存
	if(m_tOriPixelArray !=NULL)
	{
		for(i=0; i<ImageHeight; i++)
		{
			delete m_tOriPixelArray[i];
			delete m_tResPixelArray[i];
			delete ImageArray[i];
		}
	}

	m_dib->Open(FilePathName);
	ImageWidth = m_dib->GetWidth();
	ImageHeight = m_dib->GetHeight();

	BYTE	*colorTable;
	colorTable = (BYTE *)m_dib->m_pDibBits;
	int byteBitCount  = m_dib->GetBiBitCount()/8;

	m_tOriPixelArray  = new RGBQUAD*[ImageHeight];
	m_tResPixelArray  = new RGBQUAD*[ImageHeight];
	ImageArray = new BYTE*[ImageHeight];
	for(int l=0 ; l<ImageHeight; l++)
	{
		m_tOriPixelArray[l] = new RGBQUAD[ImageWidth];
		m_tResPixelArray[l] = new RGBQUAD[ImageWidth];
		ImageArray[l] = new BYTE[ImageWidth];
	}

	int count = 0;
	for(i=ImageHeight-1; i>=0; i--)
	{
		for(j=0; j<ImageWidth; j++)
		{
			m_tOriPixelArray[i][j].rgbBlue =colorTable[count++];
			m_tOriPixelArray[i][j].rgbGreen=colorTable[count++];
			m_tOriPixelArray[i][j].rgbRed  =colorTable[count++];
			m_tOriPixelArray[i][j].rgbReserved = 0;
			m_tResPixelArray[i][j]=m_tOriPixelArray[i][j];
			ImageArray[i][j] = (BYTE)(((unsigned int)m_tOriPixelArray[i][j].rgbBlue
								+(unsigned int)m_tOriPixelArray[i][j].rgbGreen
								+(unsigned int)m_tOriPixelArray[i][j].rgbRed)/3);
			count += byteBitCount-3;
		}
		count += (4-(ImageWidth*byteBitCount)%4)%4;
	}
}

/////////////////////////////////////////////////////////////////////////////
//  去除背景
//  这里简单的采用了从原图像中提取红色部分的方案
//  参数：refer－预先设定的红色图像印章聚类的中心值
void CYinZhang::EroseBackground(RGBQUAD &refer)
{
	//定义阈值，可以适当的变动
	unsigned char threR = 50;
	unsigned char threG = 50;
	unsigned char threB = 50;
	BOOL rIn, gIn, bIn;	//用来标志R,G,B分量是否在阈值范围内
	unsigned char temp;

	int i,j;
	for(i=0; i<ImageHeight; i++)
	{
		for(j=0; j<ImageWidth; j++)
		{
			//先判断R分量
			if((m_tOriPixelArray[i][j].rgbRed > refer.rgbRed) 
				&& (m_tOriPixelArray[i][j].rgbRed-refer.rgbRed<threR))
				rIn = true;
			else if((refer.rgbRed > m_tOriPixelArray[i][j].rgbRed)
				&& (refer.rgbRed-m_tOriPixelArray[i][j].rgbRed<threR))
				rIn = true;
			else
				rIn = false;

			//判断G分量
			if((m_tOriPixelArray[i][j].rgbGreen > refer.rgbGreen) 
				&& (m_tOriPixelArray[i][j].rgbGreen-refer.rgbGreen<threG))
				gIn = true;
			else if((refer.rgbGreen > m_tOriPixelArray[i][j].rgbGreen)
				&& (refer.rgbGreen-m_tOriPixelArray[i][j].rgbGreen<threG))
				gIn = true;
			else
				gIn = false;

			//判断B分量
			if((m_tOriPixelArray[i][j].rgbBlue > refer.rgbBlue) 
				&& (m_tOriPixelArray[i][j].rgbBlue-refer.rgbBlue<threB))
				bIn = true;
			else if((refer.rgbBlue> m_tOriPixelArray[i][j].rgbBlue)
				&& (refer.rgbBlue-m_tOriPixelArray[i][j].rgbBlue<threB))
				bIn = true;
			else
				bIn = false;

			if(rIn && gIn && bIn)
				ImageArray[i][j] = (BYTE)1;
			else
				ImageArray[i][j] = (BYTE)0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//提取特征
void CYinZhang::FeatureExtract()
{
	GlobalCentroid = (double)ImageWidth*(double)ImageHeight;
	GlobalCentroidX = (double)ImageWidth/2.0;
	GlobalCentroidY = (double)ImageHeight/2.0;

	int i,j;
	PrintCentroidX = 0.0;
	PrintCentroidY = 0.0;
	PrintMass = 0.0;
	double tempX = 0.0;
	double tempY = 0.0;

	for(i=0; i<ImageHeight; i++)
	{
		for(j=0; j<ImageWidth; j++)
		{
			PrintMass += (double)ImageArray[i][j];
			tempX += (double)j*(double)ImageArray[i][j];
			tempY += (double)i*(double)ImageArray[i][j];
		}
	}

	PrintCentroidX = tempX/PrintMass;
	PrintCentroidY = tempY/PrintMass;

	CentroidDistance = sqrt((PrintCentroidX-GlobalCentroidX)*(PrintCentroidX-GlobalCentroidX)
		+(PrintCentroidY-GlobalCentroidY)*(PrintCentroidY-GlobalCentroidY));
}
