#include "stdafx.h"
#include "Sharp.h"
#include"CGwork0218View.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CSharp::CSharp()
{
}


CSharp::~CSharp()
{
}
void CSharp::DrawSharp(CDC *pDC)
{

}
void CSharp::PingYi(double dx, double dy)
{
	f[0][0] = 1; f[0][1] = 0; f[0][2] = 0;
	f[1][0] = 0; f[1][1] = 1; f[1][2] = 0;
	f[2][0] = dx; f[2][1] = dy; f[2][2] = 1;
}

double CSharp::GetX(double x, double y, double d)
{
	double xx;
	xx = x*f[0][0] + y*f[1][0] + d*f[2][0];
	return(xx);
}

double CSharp::GetY(double x, double y, double d)
{
	double yy;
	yy = x*f[0][1] + y*f[1][1] + d*f[2][1];
	return(yy);

}

void CSharp::XuanZhuan(double th)
{
	f[0][0] = cos(th / 180 * pi); f[0][1] = sin(th / 180 * pi); f[0][2] = 0;
	f[1][0] = -sin(th / 180 * pi); f[1][1] = cos(th / 180 * pi); f[1][2] = 0;
	f[2][0] = 0; f[2][1] = 0; f[2][2] = 1;
}

//DEL void CSharp::change()
//DEL {
//DEL 
//DEL }

void CSharp::change(int pyx, int pyy, int xz)
{

}