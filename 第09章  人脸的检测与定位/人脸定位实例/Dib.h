// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H__3E3EC543_A4C5_11D0_B4B0_0000B43BAF07__INCLUDED_)
#define AFX_DIB_H__3E3EC543_A4C5_11D0_B4B0_0000B43BAF07__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vfw.h>
#pragma comment(lib,"vfw32.lib")

class CDib : public CObject  
{
public:
	CDib();
	virtual ~CDib();

//Attributes
public:
	BYTE    *GetBits();
	CSize	 GetSize();
	LONG	 GetWidth();
	LONG	 GetHeight();
	int      GetBiBitCount();
	BOOL     IsValid()  { return(m_hDrawDib!=NULL); }
	operator HDRAWDIB() { return m_hDrawDib; }

//operations
public:
	BOOL Open(const char *pzFileName);
	BOOL Save(const char *pzFileName);
	void Draw(CDC *pDC,int nWidth, int nHeight);
	void Close();

//public parameters
	BYTE		*m_pDibBits;
//implementation
public:
	BYTE		*m_pDib;
	HDRAWDIB	m_hDrawDib;

	BITMAPFILEHEADER bmpFileHeader;
};
#endif // !defined(AFX_DIB_H__3E3EC543_A4C5_11D0_B4B0_0000B43BAF07__INCLUDED_)
