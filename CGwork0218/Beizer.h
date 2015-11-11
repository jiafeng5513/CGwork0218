#if !defined(AFX_BEIZER_H__43BA6275_DB12_4033_92AD_6E3167913AEF__INCLUDED_)
#define AFX_BEIZER_H__43BA6275_DB12_4033_92AD_6E3167913AEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sharp.h"

class CBeizer : public CSharp
{
public:
	CArray<CPoint, CPoint> pointarray;
	int rate;
public:
	virtual void change(int pyx, int pyy, int xz);
	void DrawKJ(CDC *pDC);
	float decas(float *p, float t, int n);
	virtual void DrawSharp(CDC *pDC);
	CBeizer();
	virtual ~CBeizer();

};

#endif // !defined(AFX_BEIZER_H__43BA6275_DB12_4033_92AD_6E3167913AEF__INCLUDED_)

