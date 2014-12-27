//////////////////////////////////////////////////////////////////////
// LikelyHood.cpp: 类CLikelyHood的接口
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FaceDetect.h"
#include "LikelyHood.h"

//////////////////////////////////////////////////////////////////////
// 构造函数/析构函数
//////////////////////////////////////////////////////////////////////

CLikelyHood::CLikelyHood()
{
	m_pLikeliHoodArray = NULL;
	m_pBinaryArray = NULL;

	bmean =  B_Mean;
	rmean =  R_Mean;
	brcov[0][0] =  Brcov00;
	brcov[0][1] =  Brcov01;
	brcov[1][0] =  Brcov10;
	brcov[1][1] =  Brcov11;
}

//////////////////////////////////////////////////////////////////////
//构造函数：
//参数：    source－输入图像数据
//          width－图像宽度
//          height－图像高度
//////////////////////////////////////////////////////////////////////
CLikelyHood::CLikelyHood(RGBQUAD ** source,int width,int height)
{
	int i;

	bmean =  B_Mean;
	rmean =  R_Mean;
	brcov[0][0] =  Brcov00;
	brcov[0][1] =  Brcov01;
	brcov[1][0] =  Brcov10;
	brcov[1][1] =  Brcov11;

	m_nWidth = width;
	m_nHeight= height;

	m_bLikeliHoodReady = false;
	m_bBinaryReady = false;

	//初始化各数组
	m_pSourceData = source;
	m_pLikeliHoodArray = new  double*[height];
	for(i=0;i <height; i++)
		m_pLikeliHoodArray[i] = new double[width];	
	m_pBinaryArray = new  BYTE*[height];
	for(i=0;i <height; i++)
		m_pBinaryArray[i] = new BYTE[width];	
}

////////////////////////////////////////////////////////////////////////
//析构函数
////////////////////////////////////////////////////////////////////////
CLikelyHood::~CLikelyHood()
{
	if(m_pLikeliHoodArray!=NULL)
	{
		for(int i=0;i<m_nHeight;i++)
			if(m_pLikeliHoodArray[i]!=NULL) delete m_pLikeliHoodArray[i];
		delete m_pLikeliHoodArray;
	}
	if(m_pBinaryArray!=NULL)
	{
		for(int i=0;i<m_nHeight;i++)
			if(m_pBinaryArray[i]!=NULL) delete m_pBinaryArray[i];
		delete m_pBinaryArray;
	}
}

//////////////////////////////////////////////////////////////////////////
//计算相似度
//////////////////////////////////////////////////////////////////////////
void CLikelyHood::CalLikeHood()
{
	int i,j;

	for(i=0; i<m_nHeight; i++)
	{
		for(j=0; j<m_nWidth; j++)
		{
			double x1,x2;
			TCbCr temp = CalCbCr(m_pSourceData[i][j].rgbRed,m_pSourceData[i][j].rgbGreen,m_pSourceData[i][j].rgbBlue);
			x1 = temp.Cb-bmean;
			x2 = temp.Cr-rmean;
			double t;
			t = x1*(x1*brcov[1][1]-x2*brcov[1][0])+x2*(-x1*brcov[0][1]+x2*brcov[0][0]);
			t /= (brcov[0][0]*brcov[1][1]-brcov[0][1]*brcov[1][0]);
			t /= (-2);
			m_pLikeliHoodArray[i][j] = exp(t);
		}
	}

	filter(m_pLikeliHoodArray,m_nWidth,m_nHeight);

	double max = 0.0;
	for(i=0; i<m_nHeight; i++)
		for(j=0; j<m_nWidth; j++)
			if(m_pLikeliHoodArray[i][j] > max) 
				max = m_pLikeliHoodArray[i][j];
	
	for(i=0; i<m_nHeight; i++)
	{
		for(j=0; j<m_nWidth; j++)
		{
			m_pLikeliHoodArray[i][j] /= max;
		}
	}

	m_bLikeliHoodReady = true;
}

///////////////////////////////////////////////////////////////////////////////
//计算Cb，Cr
///////////////////////////////////////////////////////////////////////////////
TCbCr CLikelyHood::CalCbCr(int R, int G, int B)
{
	TCbCr res;
	res.Cb =( 128 - 37.797 * R/255 - 74.203 * G/255 +   112 * B/255);
	res.Cr =( 128 + 112    * R/255 - 93.786 * G/255 -18.214 * B/255);
	return res;
}

///////////////////////////////////////////////////////////////////////////////
//滤波
///////////////////////////////////////////////////////////////////////////////
void CLikelyHood::filter(double** source,int m_nWidth,int m_nHeight)
{
	int i,j;
	double **temp;
	//申请一个临时二维数组
	temp = new  double*[m_nHeight+2];
	for(i=0;i <=m_nHeight+1; i++)
		temp[i] = new double[m_nWidth+2];
	
	//边界均设为0
	for(i=0; i<=m_nHeight+1; i++)
	{
		temp[i][0] = 0;
		temp[i][m_nWidth+1] = 0;
	}
	for(j=0; j<=m_nWidth+1; j++)
	{
		temp[0][j] = 0;
		temp[m_nHeight+1][j] = 0;
	}

	//将原数组的值赋予临时数组
	for(i=0; i<m_nHeight; i++)
		for(j=0; j<m_nWidth; j++)
			temp[i+1][j+1] = source[i][j];

	//均值滤波
	for(i=0; i<m_nHeight; i++)
	{
		for(j=0; j<m_nWidth; j++)
		{
			source[i][j] = 0;
			for(int k=0;k<=2;k++)
			for(int l=0;l<=2;l++)
			source[i][j] += temp[i+k][j+l];
		
			source[i][j] /= 9;
		}
	}

	if(temp!=NULL)
	{
		for(int i=0;i<=m_nHeight+1;i++)
			if(temp[i]!=NULL) delete temp[i];
		delete temp;
	}
}

//////////////////////////////////////////////////////////////////////////
//二值化图像
//////////////////////////////////////////////////////////////////////////
bool CLikelyHood::CalBinary()
{
	if(!m_bLikeliHoodReady) 
		return false;
	int i,j;
	BYTE **temp;
	temp = new  BYTE*[m_nHeight];
	for(i=0;i <m_nHeight; i++)
	{
		temp[i] = new BYTE[m_nWidth];	
		for(j=0; j<m_nWidth; j++) 
			temp[i][j] = 0;
	}

	double min = 10000000000000000.0;
	int index = -1;
	for(int k=5;k>=0;k--)
	{
		double sum = 0;
		for(i=0; i<m_nHeight; i++)
		for(j=0; j<m_nWidth; j++)
		{
			if(m_pLikeliHoodArray[i][j]>k*0.1+0.05)
				m_pBinaryArray[i][j] = 1;
			else
				m_pBinaryArray[i][j] = 0;
			sum += (m_pBinaryArray[i][j]-temp[i][j]);
		}
		
		if(sum < min)
		{
			min = sum;
			index = 6-k;
		}

	    for(i=0; i<m_nHeight; i++)
	    for(j=0; j<m_nWidth; j++)
		temp[i][j] = m_pBinaryArray[i][j];
	}

	double optimalThreshold = (7-index)*0.1;
	for(i=0; i<m_nHeight; i++)
	for(j=0; j<m_nWidth; j++)
	{
		if(m_pLikeliHoodArray[i][j]>optimalThreshold)
			m_pBinaryArray[i][j] = 1;
		else
			m_pBinaryArray[i][j] = 0;
	}

	if(temp!=NULL)
	{
		for(int i=0;i<=m_nHeight-1;i++)
			if(temp[i]!=NULL) delete temp[i];
		delete temp;
	}

	m_bBinaryReady = true;

	return true;
}

/////////////////////////////////////////////////////////////////////////
//功能：训练参数
//参数：DirectPath－Bmp文件路径
/////////////////////////////////////////////////////////////////////////
int CLikelyHood::CalParameter(CString DirectPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	BOOL  FINDOVER=TRUE;
	hFind = FindFirstFile(DirectPath+"\\*.bmp", &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	int filenum = 0;
	while(FINDOVER)
	{
		CString m_sOpenFileName=DirectPath+FindFileData.cFileName;
		filenum ++;
		FINDOVER=FindNextFile(hFind,&FindFileData);
	}
	FindClose(hFind);

	double **CrList,**CbList;
	CrList = new double*[filenum];
	CbList = new double*[filenum];

	int* mapLength = new int[filenum];

	FINDOVER=TRUE;
	BOOL FileOK=true;
	int index = 0;
	hFind = FindFirstFile(DirectPath+"\\*.bmp", &FindFileData);
	while(FINDOVER && FileOK)
	{
		CString m_sOpenFileName=DirectPath+"\\"+FindFileData.cFileName;
		CDib * dib;
		dib = new CDib();
		if(!dib->Open(m_sOpenFileName))
		{
			AfxMessageBox(m_sOpenFileName+": Invalid File Format! It must be BMP File");
			FileOK = false;
		}
		if(FileOK)
		{
			int m_nBitMapWidth = dib->GetWidth();
			int m_nBitMapHeight= dib->GetHeight();
			CrList[index] = new double[m_nBitMapWidth*m_nBitMapHeight];
			CbList[index] = new double[m_nBitMapWidth*m_nBitMapHeight];
			mapLength[index] = m_nBitMapWidth*m_nBitMapHeight;

			BYTE	*colorTable;
			colorTable = (BYTE *)dib->m_pDibBits;
			int byteBitCount  = dib->GetBiBitCount()/8;
			int count = 0;
			double **tempCr,**tempCb;
			tempCr = new  double*[m_nBitMapHeight];
			tempCb = new  double*[m_nBitMapHeight];
			for(int i=0;i <m_nBitMapHeight; i++)
			{
				tempCr[i] = new double[m_nBitMapWidth];	
				tempCb[i] = new double[m_nBitMapWidth];	
			}

			for(i=m_nBitMapHeight-1; i>=0; i--)
			{
				for(int j=0; j<m_nBitMapWidth; j++)
				{
					TCbCr temp = CalCbCr(colorTable[count+2],colorTable[count+1],colorTable[count]);
					tempCr[i][j] = temp.Cr;
					tempCb[i][j] = temp.Cb;
					//int q = m_nBitMapWidth*(m_nBitMapHeight-1-i)+j;
					//CrList[index][q]= temp.Cr;
					//CbList[index][q]= temp.Cb;
					count += byteBitCount;
				}
				count += (4-(m_nBitMapWidth*byteBitCount)%4)%4;
			}
			filter(tempCr,m_nBitMapWidth,m_nBitMapHeight);
			filter(tempCb,m_nBitMapWidth,m_nBitMapHeight);
			for(i=0 ; i<m_nBitMapHeight; i++)
			{
				for(int j=0; j<m_nBitMapWidth; j++)
				{
					int q = m_nBitMapWidth*i+j;
					CrList[index][q]= tempCr[i][j];
					CbList[index][q]= tempCb[i][j];
				}
			}
			for(i=0;i<m_nBitMapHeight;i++)
			{
				delete tempCr[i];
				delete tempCb[i];
			}
			delete tempCr;
			delete tempCb;

			index++;
		}
		delete dib;
		FINDOVER=FindNextFile(hFind,&FindFileData);
	}
	FindClose(hFind);

	double avgCr = 0;
	double avgCb = 0;
	double cov00,cov01,cov10,cov11;
	cov00 = cov01 = cov10 = cov11 = 0.0;
	int totallen = 0;
	
	if(FileOK)
	{
		for(int i=0;i<filenum;i++)
		{
			totallen+=mapLength[i];
			for(int j=0;j<mapLength[i];j++)
			{
				avgCr += CrList[i][j];
				avgCb += CbList[i][j];
			}
		}
		avgCr /= totallen;
		avgCb /= totallen;

		for(i=0;i<filenum;i++)
		{
			for(int j=0;j<mapLength[i];j++)
			{
				cov11 += (CrList[i][j]-avgCr)*(CrList[i][j]-avgCr);
				cov00 += (CbList[i][j]-avgCb)*(CbList[i][j]-avgCb);
				cov01 += (CrList[i][j]-avgCr)*(CbList[i][j]-avgCb);
			}
		}
		cov00 /= totallen;
		cov01 /= totallen;
		cov10 = cov01;
		cov11 /= totallen;
	}

	for(int i=0;i<filenum;i++)
	{
		if(CrList[i]!=NULL) delete CrList[i];
		if(CbList[i]!=NULL) delete CbList[i];
	}
	delete mapLength;
	if(!FileOK) return 1;

	if((cov00*cov11-cov01*cov01) == 0) return 2;

	bmean =  avgCb;
	rmean =  avgCr;
	brcov[0][0] =  cov00;
	brcov[0][1] =  cov01;
	brcov[1][0] =  cov10;
	brcov[1][1] =  cov11;
	return 3;
}

