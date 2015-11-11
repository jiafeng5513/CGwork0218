#include "stdafx.h"
#include "Line.h"
#include "Sharp.h"
#include"CGwork0218View.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::DrawSharp(CDC *pDC)
{
	CPen penStroke;
	penStroke.CreatePen(PS_SOLID, 1, m_lPenColor);

	CPen* pOldPen = pDC->SelectObject(&penStroke);

	pDC->MoveTo(startpoint);
	pDC->LineTo(endpoint);
	pDC->SelectObject(pOldPen);
}



//DEL void CLine::change()
//DEL {
//DEL 
//DEL }

void CLine::change(int pyx, int pyy, int xz)
{
	this->PingYi(pyx, pyy);
	double x;
	double y;


	x = this->GetX(this->startpoint.x, this->startpoint.y, 1);
	y = this->GetY(this->startpoint.x, this->startpoint.y, 1);
	this->startpoint.x = x;
	this->startpoint.y = y;
	this->XuanZhuan(xz);
	x = this->GetX(this->startpoint.x, this->startpoint.y, 1);
	y = this->GetY(this->startpoint.x, this->startpoint.y, 1);
	this->startpoint.x = x;
	this->startpoint.y = y;
	this->PingYi(pyx, pyy);



	x = this->GetX(this->endpoint.x, this->endpoint.y, 1);
	y = this->GetY(this->endpoint.x, this->endpoint.y, 1);
	this->endpoint.x = x;
	this->endpoint.y = y;
	this->XuanZhuan(xz);
	x = this->GetX(this->endpoint.x, this->endpoint.y, 1);
	y = this->GetY(this->endpoint.x, this->endpoint.y, 1);
	this->endpoint.x = x;
	this->endpoint.y = y;

}