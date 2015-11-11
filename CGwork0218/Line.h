// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__16EE9E27_6AD7_409B_B1A1_3D6F4536CA7B__INCLUDED_)
#define AFX_LINE_H__16EE9E27_6AD7_409B_B1A1_3D6F4536CA7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Sharp.h"

class CLine : public CSharp
{
public:
	POINT startpoint;
	POINT endpoint;
public:
	virtual void change(int pyx, int pyy, int xz);
	virtual void DrawSharp(CDC *pDC);
	CLine();
	virtual ~CLine();

};

#endif // !defined(AFX_LINE_H__16EE9E27_6AD7_409B_B1A1_3D6F4536CA7B__INCLUDED_)
