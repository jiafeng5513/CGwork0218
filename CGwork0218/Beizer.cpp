#include "stdafx.h"
#include "Beizer.h"
#include "CGwork0218.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CBeizer::CBeizer()
{
	this->rate = 200;

}

CBeizer::~CBeizer()
{

}

void CBeizer::DrawSharp(CDC *pDC)
{
	CPen penStroke;
	penStroke.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	CPen* pOldPen = pDC->SelectObject(&penStroke);

	int i, k;
	float t, x, y;
	float px[100], py[100];
	int n = this->pointarray.GetSize();
	k = this->rate;

	for (i = 0; i<n; i++)
	{

		px[i] = this->pointarray[i].x;
		py[i] = this->pointarray[i].y;
	}
	n = n - 1;
	pDC->MoveTo(this->pointarray[0]);
	for (i = 0; i <= k; i++)
	{
		t = (float)i / k;
		x = decas(px, t, n);      y = decas(py, t, n);
		if (i == 0)
			pDC->MoveTo(x, y);
		else
			pDC->LineTo(x, y);

	}
	penStroke.DeleteObject();
	penStroke.CreatePen(PS_SOLID, 1, m_lPenColor);
	pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(pointarray[0]);
	for (i = 0; i<pointarray.GetSize(); i++)
	{


		pDC->LineTo(pointarray[i]);
	}
	pDC->SelectObject(pOldPen);

}

float CBeizer::decas(float *p, float t, int n)
{
	int i, r;
	float q[100];
	for (i = 0; i <= n; i++)   q[i] = p[i];
	for (r = 1; r <= n; r++)
	{
		for (i = 0; i <= n - r; i++)
		{
			q[i] = (1 - t)*q[i] + t*q[i + 1];
		}
	}
	return(q[0]);

}

void CBeizer::DrawKJ(CDC *pDC)
{
	CPen penStroke;
	penStroke.CreatePen(PS_SOLID, 1, m_lPenColor);

	CPen* pOldPen = pDC->SelectObject(&penStroke);
	pDC->MoveTo(pointarray[0]);
	for (int i = 1; i<pointarray.GetSize(); i++)
	{
		pDC->LineTo(pointarray[i]);

	}
	pDC->SelectObject(pOldPen);
}

//DEL void CBeizer::change()
//DEL {
//DEL 
//DEL }

void CBeizer::change(int pyx, int pyy, int xz)
{
	this->PingYi(pyx, pyy);
	double x;
	double y;
	for (int i = 0; i<this->pointarray.GetSize(); i++)
	{

		x = this->GetX(pointarray[i].x, pointarray[i].y, 1);
		y = this->GetY(pointarray[i].x, pointarray[i].y, 1);
		pointarray[i].x = x;
		pointarray[i].y = y;
	}
	this->XuanZhuan(xz);
	for (int i = 0; i<this->pointarray.GetSize(); i++)
	{

		x = this->GetX(pointarray[i].x, pointarray[i].y, 1);
		y = this->GetY(pointarray[i].x, pointarray[i].y, 1);
		pointarray[i].x = x;
		pointarray[i].y = y;
	}
}