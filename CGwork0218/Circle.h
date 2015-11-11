#if !defined(AFX_CIRCLE_H__6F7CC62A_0E2C_44CE_B354_C283C3520484__INCLUDED_)
#define AFX_CIRCLE_H__6F7CC62A_0E2C_44CE_B354_C283C3520484__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sharp.h"

class CCircle : public CSharp
{
public:
	POINT center;
	long radious;
public:
	virtual void change(int pyx, int pyy, int xz);
	virtual void DrawSharp(CDC *pDC);
	CCircle();
	virtual ~CCircle();

};

#endif // !defined(AFX_CIRCLE_H__6F7CC62A_0E2C_44CE_B354_C283C3520484__INCLUDED_)
