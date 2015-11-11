#if !defined(AFX_SHARP_H__1EACE4B6_B622_4AC8_B3FB_1C13AF260D7B__INCLUDED_)
#define AFX_SHARP_H__1EACE4B6_B622_4AC8_B3FB_1C13AF260D7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "afx.h"
#endif // _MSC_VER > 1000
#define pi 3.14
#include <math.h>

class CSharp : public CObject
{
public:
	long m_lPenColor;
	double f[3][3];
public:
	virtual void change(int pyx, int pyy, int xz);
	virtual void DrawSharp(CDC *pDC);
	CSharp();
	virtual ~CSharp();
	void XuanZhuan(double th);
	double GetY(double x, double y, double d);
	double GetX(double x, double y, double d);
	void PingYi(double dx, double dy);

};
#endif // !defined(AFX_SHARP_H__1EACE4B6_B622_4AC8_B3FB_1C13AF260D7B__INCLUDED_)
