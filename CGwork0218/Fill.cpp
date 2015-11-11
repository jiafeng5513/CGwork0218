#include "stdafx.h"
#include "Fill.h"
#include"CGwork0218View.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CFill::CFill()
{
}


CFill::~CFill()
{
}

void CFill::DrawFill(CDC *pDC)
{
	CBrush   brush(m_lFillColor), *pOldBrush;
	pOldBrush = (CBrush   *)pDC->SelectObject(&brush);
	long bkcolor = GetSysColor(COLOR_WINDOW);
	pDC->ExtFloodFill(fillPoint.x, fillPoint.y, bkcolor, FLOODFILLSURFACE);
	pDC->SelectObject(pOldBrush);
}

void CFill::change(int pyx, int pyy, int xz)
{
	PingYi(pyx, pyy);
	double x;
	double y;


	x = this->GetX(this->fillPoint.x, this->fillPoint.y, 1);
	y = this->GetY(this->fillPoint.x, this->fillPoint.y, 1);
	this->fillPoint.x = x;
	this->fillPoint.y = y;
	this->XuanZhuan(xz);
	x = this->GetX(this->fillPoint.x, this->fillPoint.y, 1);
	y = this->GetY(this->fillPoint.x, this->fillPoint.y, 1);
	this->fillPoint.x = x;
	this->fillPoint.y = y;


}