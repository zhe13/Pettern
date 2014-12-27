// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
	m_hDrawDib=NULL;
	m_pDib=NULL;
}

CDib::~CDib()
{
	Close();
}

void CDib::Draw(CDC *pDC,int nWidth, int nHeight)
{
	if(m_pDib!=NULL)
	{
	ASSERT(IsValid());
	DrawDibRealize(m_hDrawDib,pDC->GetSafeHdc(),TRUE);
	DrawDibDraw(m_hDrawDib,pDC->GetSafeHdc(),
				0,  //desktop left
				0,  //desktop top
				nWidth,
				nHeight,
				(BITMAPINFOHEADER *)m_pDib,
				(LPVOID) GetBits(),
				0,  //source left
				0,  //source top
				((BITMAPINFOHEADER *)m_pDib)->biWidth,
				((BITMAPINFOHEADER *)m_pDib)->biHeight,
				DDF_BACKGROUNDPAL);
	}
}

CSize CDib::GetSize()
{
	return CSize(((BITMAPINFOHEADER *)m_pDib)->biWidth,
				 ((BITMAPINFOHEADER *)m_pDib)->biHeight);	
}

LONG CDib::GetWidth()
{
	return ((BITMAPINFOHEADER *)m_pDib)->biWidth;
}

LONG CDib::GetHeight()
{
	return	((BITMAPINFOHEADER *)m_pDib)->biHeight;
}

void CDib::Close()
{
	if(m_hDrawDib!=NULL)
	{
		DrawDibClose(m_hDrawDib);
		m_hDrawDib=NULL;
	}

	if(m_pDib!=NULL)
	{
		delete m_pDib;
		m_pDib=NULL;
	}
}

BOOL CDib::Open(const char * pzFileName)
{
//	BITMAPFILEHEADER bmpFileHeader;
	CFile file;
	int nBmpFileHeaderSize;

	Close();

	//drawdibopen initialize the diradib library and 
	//returns a handle for all drawdib operations
	if(!(m_hDrawDib=DrawDibOpen()))
		goto exit;

 	//open and read the DIB file header
	nBmpFileHeaderSize=sizeof(BITMAPFILEHEADER);

	if(!file.Open(pzFileName,CFile::modeRead | CFile::typeBinary))
		goto exit;

	if(file.Read((void *)&bmpFileHeader,nBmpFileHeaderSize)!=(UINT)nBmpFileHeaderSize)
		goto failure;

	//validate the DIB file header by checking the first
	//two characters for the signature "BM"
	if(bmpFileHeader.bfType!=*((WORD *)"BM"))
		goto failure;

	//allocate a big chuck of global memory to store the DIB
	m_pDib=(BYTE *)new char [bmpFileHeader.bfSize-nBmpFileHeaderSize];

	//allocate memory fail
	if(!m_pDib)
		goto failure;

	//read the dib into the buffer at a time using ReadHuge
	file.ReadHuge(m_pDib,bmpFileHeader.bfSize-nBmpFileHeaderSize);

	if(((BITMAPINFOHEADER *)m_pDib)->biSizeImage==0)
	{
		//the application that create this bitmap didn't fill
		//in the biSizeImage field. Let's fill it
		//in even though the DrawDib * functions don't need it.
		BITMAPINFOHEADER *pDib=(BITMAPINFOHEADER *)m_pDib;

		//scan lines must be DWord aligned, hence the strange bit stuff
		pDib->biSizeImage=((((pDib->biWidth*pDib->biBitCount)+31)&~31)>>3)*pDib->biHeight;
	}

	m_pDibBits=GetBits();

	file.Close();
	return TRUE;

failure:
	file.Close();
exit:
	Close();
	return FALSE;
}

BOOL CDib::Save(const char * pzFileName)
{
//	BITMAPFILEHEADER bmpFileHeader;
	CFile file;
	int nBmpFileHeaderSize;

 	//open and read the DIB file header
	nBmpFileHeaderSize=sizeof(BITMAPFILEHEADER);

	if(!file.Open(pzFileName,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		goto exit;

	file.Write(&bmpFileHeader,nBmpFileHeaderSize); 

	//allocate memory fail
	if(!m_pDib)
		goto failure;

	//read the dib into the buffer at a time using ReadHuge
	file.WriteHuge(m_pDib,bmpFileHeader.bfSize-nBmpFileHeaderSize);

	file.Close();
	return TRUE;

failure:
	file.Close();
exit:
	return FALSE;
}

BYTE * CDib::GetBits()
{
	//the size of the color map is determined by the number
	//of RGBQUAD structures presend.
	//it also depends on the bit_depth of the Dib
	DWORD dwNumColors,dwColorTableSize;
	BITMAPINFOHEADER *lpDib=(BITMAPINFOHEADER *)m_pDib;

	WORD wBitCount=lpDib->biBitCount;

	if(lpDib->biSize>=36)
		dwNumColors=lpDib->biClrUsed;
	else
		dwNumColors=0;

	if(dwNumColors==0)
	{
		if(wBitCount!=24)
			dwNumColors=1L<<wBitCount;
		else 
			dwNumColors=0;
	}

	dwColorTableSize=dwNumColors*sizeof(RGBQUAD);

	return m_pDib+lpDib->biSize+dwColorTableSize;
}

int CDib::GetBiBitCount()
{
	if(m_pDib!=NULL)
		return ((BITMAPINFOHEADER *)m_pDib)->biBitCount; 
	return 0;
}
