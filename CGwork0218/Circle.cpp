#include "stdafx.h"
#include "CGwork0218.h"
#include "Circle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

void CCircle::DrawSharp(CDC *pDC)
{
	CPen penStroke;
	penStroke.CreatePen(PS_SOLID, 1, m_lPenColor);

	CPen* pOldPen = pDC->SelectObject(&penStroke);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

	CRect rect;
	rect.top = center.y - radious;
	rect.right = center.x + radious;
	rect.left = center.x - radious;
	rect.bottom = center.y + radious;

	pDC->Ellipse(rect);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pBrush);


}



//DEL void CCircle::change()
//DEL {
//DEL 
//DEL }

void CCircle::change(int pyx, int pyy, int xz)
{
	this->PingYi(pyx, pyy);
	double x;
	double y;


	x = this->GetX(this->center.x, this->center.y, 1);
	y = this->GetY(this->center.x, this->center.y, 1);
	this->center.x = x;
	this->center.y = y;
	this->XuanZhuan(xz);
	x = this->GetX(this->center.x, this->center.y, 1);
	y = this->GetY(this->center.x, this->center.y, 1);
	this->center.x = x;
	this->center.y = y;

}
