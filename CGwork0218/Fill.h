#if !defined(AFX_FILL_H__974E0493_2204_4567_A458_B943AE064938__INCLUDED_)
#define AFX_FILL_H__974E0493_2204_4567_A458_B943AE064938__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Sharp.h"
class CFill : public CSharp
{
public:
	POINT fillPoint;
	long m_lFillColor;
public:
	void change(int pyx, int pyy, int xz);
	void DrawFill(CDC *Pdc);
	CFill();
	virtual ~CFill();

};

#endif // !defined(AFX_FILL_H__974E0493_2204_4567_A458_B943AE064938__INCLUDED_)