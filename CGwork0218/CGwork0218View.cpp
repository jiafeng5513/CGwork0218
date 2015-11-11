
// CGwork0218View.cpp : CCGwork0218View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CGwork0218.h"
#endif
#include "MainFrm.h"
#include "CGwork0218Doc.h"
#include "CGwork0218View.h"
#include "DlgRotate.h"
#include <math.h>
#include "Sharp.h"
#include "Line.h"
#include"Fill.h"
#include"Circle.h"
#include "MoveDialog.h"
#include"BGSMDialog.h"
#include"MoveCubeDialog.h"
#include"RoateCubeDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGwork0218View

IMPLEMENT_DYNCREATE(CCGwork0218View, CView)

BEGIN_MESSAGE_MAP(CCGwork0218View, CView)

	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_Move, &CCGwork0218View::OnMove)
	ON_COMMAND(ID_Rotate, &CCGwork0218View::OnRotate)
	ON_COMMAND(ID_Fill, &CCGwork0218View::OnFill)
	ON_COMMAND(ID_Polygon, &CCGwork0218View::OnPolygon)
	ON_COMMAND(ID_DrawPolygon, &CCGwork0218View::OnDrawpolygon)
	ON_COMMAND(ID_DrawLine, &CCGwork0218View::OnDrawline)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DrawLine2, &CCGwork0218View::OnDrawline2)
	ON_COMMAND(ID_FillPolygon, &CCGwork0218View::OnFillpolygon)
	ON_COMMAND(ID_ChooseColor, &CCGwork0218View::OnChoosecolor)
	ON_COMMAND(ID_PenColor, &CCGwork0218View::OnPencolor)
	ON_COMMAND(ID_NumberFill, &CCGwork0218View::OnNumberfill)
	ON_COMMAND(ID_DefaultMouse, &CCGwork0218View::OnDefaultmouse)
	ON_WM_SIZE()
	ON_COMMAND(ID_BGSM, &CCGwork0218View::OnBgsm)
	ON_COMMAND(ID_MoveCube, &CCGwork0218View::OnMovecube)
	ON_COMMAND(ID_RotateCube, &CCGwork0218View::OnRotatecube)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_COMMAND(ID_DrawCube, &CCGwork0218View::OnDrawcube)
	ON_COMMAND(ID_CubeT, &CCGwork0218View::OnCubet)
	ON_COMMAND(ID_CubeX, &CCGwork0218View::OnCubex)
	ON_COMMAND(ID_Bezier, &CCGwork0218View::OnBezier)
	ON_COMMAND(ID_BSize, &CCGwork0218View::OnBsize)
	ON_COMMAND(ID_Reset, &CCGwork0218View::OnReset)
END_MESSAGE_MAP()

// CCGwork0218View 构造/析构

CCGwork0218View::CCGwork0218View()
: bDrawMark(false)
, bMoveMark(false)
, MoveStart((0,0))
, MoveEnd((0,0))
, bRotateMark(false)
, RotateBase((0,0))
, bFillMark(false)
, ptNum(1)
, RotateAngle(0.0)
, m_bDrawMode(false)
, beflag(0)
, xzflag(0)
, beizerItem(NULL)
, cxClient(0)
, cyClient(0)
, m_cMovePoint(0)
, m_bIsChoosed(false)
, m_bStopDraw(false)
, m_bPointChoosed(false)
, m_bMakeSure(false)
, m_iItemOfEditPoint(0)
{
	// TODO:  在此处添加构造代码
	m_dsDrawSort = DsNull;
	m_startPoint.x = 0;
	m_startPoint.y = 0;
	m_endPoint.x = 0;
	m_endPoint.y = 0;
	m_bIsMouseDown = 0;

	m_lPenColor = RGB(0, 0, 255);
	m_iPenWidth = 1;
	m_lBkColor = RGB(255, 255, 255);
	m_lFillColor = RGB(255, 0, 0);

	m_LineType = BRDL;
	m_CircleType = MDC;
	m_FillType = EXTFLOODFILL;
	m_proFunc = TOUSHI;
	m_bDrawMode = true;
	isCubeInitialized = true;
}

CCGwork0218View::~CCGwork0218View()
{
}

BOOL CCGwork0218View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCGwork0218View 绘制

void CCGwork0218View::OnDraw(CDC* pDC)
{
	CCGwork0218Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

	if (m_dsDrawSort == DsPolygon){                      //==========如果是矩形画笔模式
		int size = pDoc->PointArray.GetSize();
		if (size<3)//当顶点数小于3时，清除获得的点
		{
			pDoc->PointArray.RemoveAll();
		}
		else//当顶点数大于3时，采用画直线方式绘制多边形
		{
			pDC->MoveTo(pDoc->PointArray[0]);
			for (int i = 0; i<size; i++)
			{
				pDC->LineTo(pDoc->PointArray[i]);
			}
			pDC->LineTo(pDoc->PointArray[0]);
		}
	}
	
	//if (xzflag == 1)
	//{
		//CRect rect;
		//this->GetClientRect(&rect);
		//pDC->SetMapMode(MM_ANISOTROPIC);
		//pDC->SetViewportOrg(rect.right / 2, rect.bottom / 2);
		//pDC->SetViewportExt(rect.right, rect.bottom);
		//pDC->SetWindowOrg(0, 0);
		//pDC->SetWindowExt((rect.right - rect.left), (rect.top - rect.bottom));
		//pDC->MoveTo(0, 0);
		//pDC->LineTo(0, rect.top - rect.bottom);
		//pDC->MoveTo(0, 0);
		//pDC->LineTo(0, rect.bottom - rect.top);
		//pDC->MoveTo(0, 0);
		//pDC->LineTo(rect.right - rect.left, 0);
		//pDC->LineTo(rect.left - rect.right, 0);
	//}
	POSITION pos = m_sharpList.GetHeadPosition();
	if (m_dsDrawSort == DsLine){
		while (pos != NULL)//====================================如果是直线画笔模式
		{
			CSharp* pSharp = m_sharpList.GetNext(pos);
			pSharp->DrawSharp(pDC);
		}
	}
	pos = m_fillList.GetHeadPosition();
	while (pos != NULL)//直线围成的多边形的填充重绘
	{
		CFill* pFill = m_fillList.GetNext(pos);
		pFill->DrawFill(pDC);

	}
	if (m_dsDrawSort == DsCube){//===============如果是立方体画笔模式,为立方体启用独立的重绘函数
		if (isCubeInitialized == true)
		{
			InitPoints();
			isCubeInitialized = false;
		}
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		// TODO:  在此处为本机数据添加绘制代码
		ASSERT_VALID(pDoc);
		HBRUSH hbrush;
		CPen pen;
		HPEN hPen;
		// TODO: add draw code for native data here
		pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hPen = (HPEN)pDC->SelectObject(pen);
		pDC->SetViewportOrg(cxClient / 2, cyClient / 2);
		//画坐标轴
		pDC->MoveTo(-cxClient / 2, 0);
		pDC->LineTo(cxClient / 2, 0);
		pDC->MoveTo(0, -cyClient / 2);
		pDC->LineTo(0, cyClient / 2);
		pen.DeleteObject();
		pDC->SelectObject(hPen);
		//选择投影方法
		if (m_proFunc==TOUSHI)
		{
			this->PerspectivePROJ();
		}
		else{
			this->ShadowTrans(-45);
		}
		for (int i = 0; i<4; i++)//纵深四条线
		{
			pDC->MoveTo(cpoints[i].x, cpoints[i].y);
			pDC->LineTo(cpoints[i + 4].x, cpoints[i + 4].y);
		}
		hbrush = (HBRUSH)pDC->SelectObject(GetStockObject(NULL_BRUSH));
		//远近八条线
		POINT front[5];
		POINT back[5];
		for (int i = 0; i < 4; i++)
		{
			front[i].x = cpoints[i].x;
			front[i].y = cpoints[i].y;
			back[i].x = cpoints[i + 4].x;
			back[i].y = cpoints[i + 4].y;
		}
		pDC->Polygon(front, 4);
		pDC->Polygon(back, 4);
	}
	if (m_dsDrawSort == DsBezier||m_dsDrawSort == DsBsize)//如果是曲线绘制模式
	{
		GetClientRect(&rect);

		if (m_eMouseStatus == MouseMove&&m_bStopDraw == false)
		{
			m_vInputPoint.push_back(m_cMovePoint);
		}

		CString str;
		CClientDC d(this);

		int i;

		if (m_bIsChoosed == true)
		{
			//if (m_bStopDraw == false)//让坐标值跟着鼠标走
			//{
			//	str.Format(_T("  X = %d, y = %d "), m_cMovePoint.x, m_cMovePoint.y);
				//d.TextOut(m_cMovePoint.x + 10, m_cMovePoint.y + 10, str);
			//}

			//判断用户选择的应用类型,并做相应的处理
			switch (m_eChooseType) {
			case Bezier:
				str.Format(_T("Bezier曲线"));
				d.TextOut(200, 10, str);
				for (i = 0; i<m_vInputPoint.size(); i++)
				{
					pDC->Ellipse(m_vInputPoint[i].x - 4, m_vInputPoint[i].y - 4,
						m_vInputPoint[i].x + 4, m_vInputPoint[i].y + 4);
				}
				DrawBezier(pDC);
				break;
			case BYangTiao:
				str.Format(_T("B样条曲线"));
				d.TextOut(200, 10, str);
				if (m_vInputPoint.size() >= 4)
				{
					for (i = 0; i<m_vInputPoint.size(); i++)
					{
						pDC->Ellipse(m_vInputPoint[i].x - 4, m_vInputPoint[i].y - 4,
							m_vInputPoint[i].x + 4, m_vInputPoint[i].y + 4);
					}
					for (i = 0; i<m_vInputPoint.size() - 3; i++)
					{
						DrawB(pDC, m_vInputPoint[i], m_vInputPoint[i + 1],
							m_vInputPoint[i + 2], m_vInputPoint[i + 3]);
					}
				}
				break;
			}
		}
		if (m_eMouseStatus == MouseMove&&m_bStopDraw == false)
		{
			m_vInputPoint.pop_back();
		}
	}
}

// CCGwork0218View 诊断

#ifdef _DEBUG
void CCGwork0218View::AssertValid() const
{
	CView::AssertValid();
}

void CCGwork0218View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGwork0218Doc* CCGwork0218View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGwork0218Doc)));
	return (CCGwork0218Doc*)m_pDocument;
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCGwork0218View 消息处理程序============================================================================
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//按下左键,根据所选的功能不同,实现不同的处理
void CCGwork0218View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	m_bIsMouseDown = 1;
	CView::OnLButtonDown(nFlags, point);
	if (m_dsDrawSort == DsNull){             //===============当没有选择任何画笔时
		return;
	}
		
	if (m_dsDrawSort == DsLine)                                //================当划线标志为真时
	{
		m_endPoint.x = m_startPoint.x = point.x;
		m_endPoint.y = m_startPoint.y = point.y;
	}
	
	if (m_dsDrawSort == DsPolygon)					//================当画多边形标志为真时
	{
		CClientDC dc(this);
		CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
		CBrush brush(RGB(0, 0, 0));
		CBrush *pOldBrush = dc.SelectObject(&brush);
		dc.Rectangle(rect);			//画以所选点为中心的小矩形表示一个点
		dc.SelectObject(pOldBrush);
		CCGwork0218Doc* pDoc = GetDocument();
		pDoc->PointArray.Add(point);//将所选点存入集合对象
	}
	if (m_dsDrawSort == DsMovePolygon)				   //=================当多边形平移标志为真时
	{
		if (ptNum == 1)				//当平移点个数为1时
		{
			CClientDC dc(this);
			CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
			CBrush brush(RGB(0, 0, 0));
			CBrush *pOldBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);		//画以所选点为中心的小矩形
			dc.SelectObject(pOldBrush);
			MoveStart = point;		//将所选点赋值给平移起点
			ptNum++;				//平移点个数增1
		}
		else						//当平移点个数为2时
		{
			CClientDC dc(this);
			CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
			CBrush brush(RGB(0, 0, 0));
			CBrush *pOldBrush = dc.SelectObject(&brush);
			dc.Rectangle(rect);		//画以所选点为中心的小矩形
			dc.SelectObject(pOldBrush);
			MoveEnd = point;			//将所选点赋值给平移终点
			ptNum = 1;				//将平移点个数赋值为1，实现平移循环
		}
	}
	if (m_dsDrawSort == DsRotatePolygon)				//=================当多边形旋转标志为真时
	{
		m_dsDrawSort = DsNull;
		CClientDC dc(this);
		CRect rect(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
		CBrush brush(RGB(0, 0, 0));
		CBrush *pOldBrush = dc.SelectObject(&brush);
		dc.Rectangle(rect);		//画以所选点为中心的小矩形
		dc.SelectObject(pOldBrush);
		RotateBase = point;	//将所选点赋值给旋转基点
	}
	if (m_dsDrawSort == DsFill2)					//==================当多边形填充标志为真时
	{
		m_dsDrawSort = DsNull;//将多边形填充标志设为假，使鼠标左击只执行一次
		Fill();		//调用多边形填充函数
	}
	if (m_dsDrawSort == DsBezier||m_dsDrawSort == DsBsize)//================当绘制曲线标志为真时
	{
		m_eMouseStatus = LButtonDown;
		if (m_bIsChoosed == true)
		{
			if (m_bStopDraw == false)
			{
				m_vInputPoint.push_back(point);
				InvalidateRect(&rect);
			}
			else
			{
				if (m_eChooseType != NHBYangTiao)
				{
					PointOnInputPoint(point);
					if (m_bPointChoosed)
					{
						m_vInputPoint[m_iItemOfEditPoint] = point;
						m_bMakeSure = !m_bMakeSure;
					}
				}
			}
		}

		CView::OnLButtonDown(nFlags, point);
	}
}

//按下右键,根据所选的功能不同,实现不同的处理
void CCGwork0218View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (bDrawMark = TRUE)						//当画多边形标志为真时
	{
		bDrawMark = FALSE;					//将画多边形标志设为假，使鼠标右击只执行一次
		Invalidate();						//调用OnDraw()函数
	}
	if (bMoveMark == TRUE)						//当多边形平移标志为真时
	{
		bMoveMark = FALSE;					//将多边形平移标志设为假，使鼠标右击只执行一次
		Move(MoveStart, MoveEnd);			//调用多边形平移函数
		Invalidate();						//调用OnDraw()函数
	}
	if (bRotateMark == TRUE)					//当多边形旋转标志为真时
	{
		bRotateMark = FALSE;					//将多边形旋转标志设为假，使鼠标右击只执行一次
		DlgRotate dlg;
		if (dlg.DoModal() == IDOK)				//调用旋转对话框，设定旋转角度，调用多边形旋转函数
		{
			RotateAngle = dlg.m_RotateAngle;
			Rotate(RotateBase, RotateAngle);
		}
		Invalidate();						//调用OnDraw()函数
	}
	if (m_dsDrawSort == DsBezier || m_dsDrawSort == DsBsize){//当画曲线函数为真的时候
		m_eMouseStatus = RButtonDown;
		m_bStopDraw = true;
		InvalidateRect(&rect);
	}
	CView::OnRButtonDown(nFlags, point);
}

//鼠标移动
void CCGwork0218View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CMainFrame* pMnFrm = (CMainFrame*)AfxGetMainWnd();
	CString str;
	str.Format(_T("X=%d,Y=%d"),point.x,point.y);//在状态栏显示鼠标位置
	CStatusBar* pSttb = &(pMnFrm->m_wndStatusBar);
	CRect rect;
	GetClientRect(rect);
	pSttb->SetPaneInfo(1, ID_SEPARATOR, SBPS_NORMAL, rect.Width() / 7);
	pSttb->SetPaneText(1, str);

	//====================================================================
	CDC *pDC = GetDC();
	if (m_dsDrawSort == DsNull)
		return;
	if (!m_bIsMouseDown&&m_dsDrawSort != DsBezier&&m_dsDrawSort != DsBsize)
		return;
	pDC->SetROP2(R2_NOTXORPEN);
	switch (m_dsDrawSort)
	{
	case DsLine://画直线
		DrawLine(m_startPoint, m_endPoint, pDC);
		DrawLine(m_startPoint, point, pDC);
		break;
	case DsBezier://画曲线
	case DsBsize:
		m_cMovePoint = point;
		m_eMouseStatus = MouseMove;
		if (m_bStopDraw == true)
		{
			if (m_bPointChoosed == true && m_bMakeSure == false)
			{
				m_vInputPoint[m_iItemOfEditPoint].x = point.x;
				m_vInputPoint[m_iItemOfEditPoint].y = point.y;
				InvalidateRect(&rect);
			}
			return;
		}
		InvalidateRect(&rect);
		break;
	}
	m_endPoint = point;
	//===================================================================
	CView::OnMouseMove(nFlags, point);
}

//抬起左键
void CCGwork0218View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_bIsMouseDown = 0;
	if (m_dsDrawSort == DsNull)
		return;

	CDC *pDC = GetDC();
	switch (m_dsDrawSort)
	{
		case DsLine:
		{
			DrawLine(m_startPoint, point, GetDC());
			CLine* pLineItem = new CLine();
			pLineItem->startpoint = m_startPoint;
			pLineItem->endpoint = point;
			pLineItem->m_lPenColor = this->m_lPenColor;
			m_sharpList.AddTail(pLineItem);
			break;
		}
		case DsFill:
		{
			 CFill *fillItem = new CFill();
			 fillItem->fillPoint = point;
			 fillItem->m_lFillColor = m_lFillColor;
			 m_listpoint.clear();
			 DrawFill(point, pDC);
			 m_fillList.AddTail(fillItem);
		     break;
		}
	}
	CView::OnLButtonUp(nFlags, point);
}

//光标变形
BOOL CCGwork0218View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (bDrawMark == TRUE)									//当画多边形标志为真时，显示画笔光标
	{
		::SetCursor(DrawCur);
		return TRUE;
	}
	else												//当画多边形标志为假时，显示视图类默认光标
	{
		return CView::OnSetCursor(pWnd, nHitTest, message);
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

/*==========================================================================================================*/
// 工具条->默认鼠标指针
void CCGwork0218View::OnDefaultmouse()
{
	// TODO:  在此添加命令处理程序代码
	m_dsDrawSort = DsNull;
}

// 工具条->绘制多边形
void CCGwork0218View::OnPolygon()
{
	// TODO:  在此添加命令处理程序代码
	m_dsDrawSort = DsPolygon;
	DrawCur = AfxGetApp()->LoadCursor(IDC_DRAWCUR);		//加载画笔光标
	bDrawMark = TRUE;										//画多边形标志设为真，实现相应的鼠标响应函数
	bMoveMark = FALSE;
	bRotateMark = FALSE;
	bFillMark = FALSE;
	CCGwork0218Doc* pDoc = GetDocument();
	pDoc->PointArray.RemoveAll();
}

// 菜单栏->绘制多边形
void CCGwork0218View::OnDrawpolygon()
{
	// TODO:  在此添加命令处理程序代码
	DrawCur = AfxGetApp()->LoadCursor(IDC_DRAWCUR);		//加载画笔光标
	bDrawMark = TRUE;										//画多边形标志设为真，实现相应的鼠标响应函数
	bMoveMark = FALSE;
	bRotateMark = FALSE;
	bFillMark = FALSE;
	m_dsDrawSort = DsPolygon;
	CCGwork0218Doc* pDoc = GetDocument();
	pDoc->PointArray.RemoveAll();
}

// 工具条->移动多边形
void CCGwork0218View::OnMove()
{
	// TODO:  在此添加命令处理程序代码
	bMoveMark = TRUE;										//多边形平移标志设为真，实现相应的鼠标响应函数
	bDrawMark = FALSE;
	bRotateMark = FALSE;
	bFillMark = FALSE;
	m_dsDrawSort = DsMovePolygon;
}

// 工具条->旋转多边形
void CCGwork0218View::OnRotate()
{
	// TODO:  在此添加命令处理程序代码
	bRotateMark = TRUE;									//多边形旋转标志设为真，实现相应的鼠标响应函数
	bDrawMark = FALSE;
	bMoveMark = FALSE;
	bFillMark = FALSE;
	m_dsDrawSort = DsRotatePolygon;
}

// 工具条->填充多边形
void CCGwork0218View::OnFill()
{
	// TODO:  在此添加命令处理程序代码
	bFillMark = TRUE;									//多边形填充标志设为真，实现相应的鼠标响应函数
	bDrawMark = FALSE;
	bMoveMark = FALSE;
	bRotateMark = FALSE;
	m_dsDrawSort = DsFill2;
}

// 菜单->绘制直线
void CCGwork0218View::OnDrawline()
{
	// TODO:  在此添加命令处理程序代码
	//功能:按下这个菜单项之后,切换为划线模式,只需要拖动鼠标,就能画出线
	if (m_bDrawMode)
	{
		if (m_dsDrawSort != DsLine)
		{
			m_dsDrawSort = DsLine;
		}
		else
			m_dsDrawSort = DsNull;
		m_bIsMouseDown = 0;
	}
}

// 工具条->绘制直线
void CCGwork0218View::OnDrawline2()
{
	// TODO:  在此添加命令处理程序代码
	//功能:按下这个菜单项之后,切换为划线模式,只需要拖动鼠标,就能画出线
	if (m_bDrawMode)
	{
		if (m_dsDrawSort != DsLine)
		{
			m_dsDrawSort = DsLine;
		}
		else
			m_dsDrawSort = DsNull;
		m_bIsMouseDown = 0;
	}
}

// 菜单->填充多边形
void CCGwork0218View::OnFillpolygon()
{
	// TODO:  在此添加命令处理程序代码
	if (m_dsDrawSort != DsFill)
	{
		m_dsDrawSort = DsFill;
	}
}

// 菜单->选择填充颜色
void CCGwork0218View::OnChoosecolor()
{
	// TODO:  在此添加命令处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal())//调用公用颜色对话框
	{
		m_lFillColor = dlg.GetColor();//将所选颜色赋值给当前填充颜色

	}
}

// 菜单->选择画笔颜色
void CCGwork0218View::OnPencolor()
{
	// TODO:  在此添加命令处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal())//调用公用颜色对话框
	{
		m_lPenColor = dlg.GetColor();//将所选颜色赋值给当前画笔颜色

	}
}

// 菜单->学号填充多边形
void CCGwork0218View::OnNumberfill()
{
	// TODO:  在此添加命令处理程序代码
	CCGwork0218Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->PointArray.GetSize() >= 3){
		Polygonfill(this->GetDC(), &(pDoc->PointArray), m_lFillColor);
	}
	
}

// 多边形平移的实现函数
void CCGwork0218View::Move(CPoint start, CPoint end)
{
	int XInc = end.x - start.x;
	int YInc = end.y - start.y;
	CCGwork0218Doc* pDoc = GetDocument();
	int size = pDoc->PointArray.GetSize();
	for (int i = 0; i<size; i++)
	{
		pDoc->PointArray[i].x = pDoc->PointArray[i].x + XInc;
		pDoc->PointArray[i].y = pDoc->PointArray[i].y + YInc;
	}
}

// 多边形旋转的实现函数
void CCGwork0218View::Rotate(CPoint ptBase, double angle)
{
	angle = 3.1415926*angle / 180;
	CCGwork0218Doc* pDoc = GetDocument();
	int size = pDoc->PointArray.GetSize();
	for (int i = 0; i<size; i++)
	{
		int XInc = pDoc->PointArray[i].x - ptBase.x;
		int YInc = pDoc->PointArray[i].y - ptBase.y;
		pDoc->PointArray[i].x = ptBase.x + (int)(XInc*cos(angle) + YInc*sin(angle) + 0.5);
		pDoc->PointArray[i].y = ptBase.y + (int)(YInc*cos(angle) - XInc*sin(angle) + 0.5);
	}
}

// 画直线的实现函数(Bresenham算法)
void CCGwork0218View::DrawLine(POINT p1, POINT p2, CDC* pDC)
{
	int i;

	if (p1.x == p2.x)
	{
		//为竖线
		if (p1.y <= p2.y)
		{
			for (i = p1.y; i <= p2.y; i++)
				pDC->SetPixel(p1.x, i, m_lPenColor);
		}
		else
		{
			for (i = p2.y; i <= p1.y; i++)
				pDC->SetPixel(p1.x, i, m_lPenColor);
		}

		return;
	}

	//为横线
	if (p1.y == p2.y)
	{
		if (p1.x <= p2.x)
		{
			for (i = p1.x; i <= p2.x; i++)
				pDC->SetPixel(i, p1.y, m_lPenColor);
		}
		else
		{
			for (i = p2.x; i <= p1.x; i++)
				pDC->SetPixel(i, p1.y, m_lPenColor);
		}

		return;
	}

	//为斜线
	float m = (p2.y - p1.y)*1.0 / (p2.x - p1.x);
	float p;

	p = 2 * m - 1;
	if (m>0 && m <= 1)
	{
		if (p1.x<p2.x)
		{
			while (p1.x <= p2.x)
			{
				pDC->SetPixel(p1.x++, p1.y, m_lPenColor);
				if (p >= 0)
				{
					p += 2 * m - 2;
					p1.y++;
				}
				else
					p += 2 * m;
			}
		}
		else
		{
			while (p2.x <= p1.x)
			{
				pDC->SetPixel(p2.x++, p2.y, m_lPenColor);
				if (p >= 0)
				{
					p += 2 * m - 2;
					p2.y++;
				}
				else
					p += 2 * m;
			}
		}

		return;
	}

	p = -2 * m - 1;
	if (m<0 && m >= -1)
	{
		if (p1.x<p2.x)
		{
			while (p1.x <= p2.x)
			{
				pDC->SetPixel(p1.x++, p1.y, m_lPenColor);
				if (p >= 0)
				{
					p += -2 * m - 2;
					p1.y--;
				}
				else
					p += -2 * m;
			}
		}
		else
		{
			while (p2.x <= p1.x)
			{
				pDC->SetPixel(p2.x++, p2.y, m_lPenColor);
				if (p >= 0)
				{
					p += -2 * m - 2;
					p2.y--;
				}
				else
					p += -2 * m;
			}
		}

		return;
	}

	p = 2 / m - 1;
	if (m>1)
	{
		if (p1.y<p2.y)
		{
			while (p1.y <= p2.y)
			{
				pDC->SetPixel(p1.x, p1.y++, m_lPenColor);
				if (p >= 0)
				{
					p += 2 / m - 2;
					p1.x++;
				}
				else
					p += 2 / m;
			}
		}
		else
		{
			while (p2.y <= p1.y)
			{
				pDC->SetPixel(p2.x, p2.y++, m_lPenColor);
				if (p >= 0)
				{
					p += 2 / m - 2;
					p2.x++;
				}
				else
					p += 2 / m;
			}
		}

		return;
	}

	p = -2 / m - 1;
	if (p1.y<p2.y)
	{
		while (p1.y <= p2.y)
		{
			pDC->SetPixel(p1.x, p1.y++, m_lPenColor);
			if (p >= 0)
			{
				p += -2 / m - 2;
				p1.x--;
			}
			else
				p += -2 / m;
		}
	}
	else
	{
		while (p2.y <= p1.y)
		{
			pDC->SetPixel(p2.x, p2.y++, m_lPenColor);
			if (p >= 0)
			{
				p += -2 / m - 2;
				p2.x--;
			}
			else
				p += -2 / m;
		}
	}
}

// 填充算法分流
void CCGwork0218View::DrawFill(CPoint point, CDC* pDC)
{
	switch (m_FillType)
	{
	case FEEDFILL:
		this->Seedfill(point.x, point.y, this->m_lPenColor, this->m_lFillColor, pDC);
		break;
	case EXTFLOODFILL:
		Fill(point, pDC);
		break;
	default:
		break;
	}
}

// 实现工具条上的填充按键功能
void CCGwork0218View::Fill()
{
	CCGwork0218Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int size = pDoc->PointArray.GetSize();
	CPoint *pt = new CPoint[size];
	for (int i = 0; i<size; i++)
	{
		pt[i] = pDoc->PointArray.GetAt(i);
	}
	CClientDC dc(this);
	CBrush brush(m_lFillColor);
	CBrush *pOldBrush = dc.SelectObject(&brush);
	dc.Polygon(pt, size);
	dc.SelectObject(pOldBrush);
	delete pt;
}

// 种子填充
void CCGwork0218View::Seedfill(int x, int y, int oldcolor, int newcolor, CDC* pDC)
{
	//if (pDC->GetPixel(x, y) == oldcolor)
	if (pDC->GetPixel(x, y) != oldcolor&&pDC->GetPixel(x, y) != newcolor)
	{
		pDC->SetPixelV(x, y, newcolor);
		Seedfill(x, y + 1, oldcolor, newcolor, pDC);
		Seedfill(x, y - 1, oldcolor, newcolor, pDC);
		Seedfill(x - 1, y, oldcolor, newcolor, pDC);
		Seedfill(x + 1, y, oldcolor, newcolor, pDC);
	}
}

// 范洪填充
void CCGwork0218View::Fill(CPoint point, CDC* pDC)
{
	CBrush   brush(m_lFillColor), *pOldBrush;
	pOldBrush = (CBrush   *)pDC->SelectObject(&brush);
	long bkcolor = GetSysColor(COLOR_WINDOW);
	HDC h = ::GetDC(m_hWnd);//当前窗口的句柄
	COLORREF clr = COLORREF(GetPixel(h, point.x, point.y));//获取当前鼠标颜色
	pDC->ExtFloodFill(point.x, point.y, clr, FLOODFILLSURFACE);
	pDC->SelectObject(pOldBrush);
}

//==============================================使用边表的多边形扫描转换算法==============================================
// 执行多边形扫描转换算法
void CCGwork0218View::Polygonfill(CDC* pDC, CArray<CPoint, CPoint>* points, COLORREF color)
{
	EDGE * pET = GetET(points);
	EDGE * pAET = NULL;
	int i = 0;//i 是 限定循环的基数10
	int xetrl;
	int y = pET->ymin;
	int ymax = pET->ymax;
	while (y<ymax)
	{
		while (pET != NULL&&pET->ymin == y)
		{
			EDGE * p = pET;
			pET = pET->next;
			p->next = NULL;
			if (pAET == NULL)
			{
				pAET = p;
			}
			else
			{
				pAET->next = p;
				p->pre = pAET;
				pAET = p;
			}
			if (ymax<pAET->ymax)
			{
				ymax = pAET->ymax;

			}
		}
		while (pAET->pre != NULL)
			pAET = pAET->pre;
		SortAET(pAET);
		EDGE* pFill = pAET;
		/*
		while (pFill!=NULL)
		{

		for(int i = (int) pFill->xmin  ;i<=(int)pFill->next->xmin;i++)
		{
		setPixel(pDC,i,y,color);         ///////////////////////////////////////////////
		}
		pFill=pFill->next->next;
		}
		*/
		while (pFill != NULL)
		{
			if (i == 10) i = 0;
			if (i == 0)xetrl = (int)pFill->xmin;
			setnumberlinepixel(pDC, i, xetrl, (int)pFill->xmin, (int)pFill->next->xmin, y, color);
			pFill = pFill->next->next;
			i++;
		}

		pFill = pAET;
		while (pFill != NULL)
		{
			if (pFill->ymax == y)
			{
				if (pFill->pre != NULL)
				{
					pFill->pre->next = pFill->next;
				}
				else
					pAET = pFill->next;
				if (pFill->next != NULL)
				{
					pFill->next->pre = pFill->pre;
				}
				EDGE* pdelet = pFill;
				pFill = pFill->next;
				delete pdelet;

			}
			else pFill = pFill->next;
		}
		if (pAET != NULL)
		{
			pFill = pAET;
			while (pFill != NULL)
			{
				pFill->xmin += pFill->fm;
				pFill = pFill->next;

			}
			SortAET(pAET);
			while
				(pAET->next != NULL)
			{
				pAET = pAET->next;
			}

		}
		y++;

	}
}

// 边表ET排序函数
void CCGwork0218View::SortET(EDGE* pEDGE)
{
	EDGE * p1 = pEDGE;
	EDGE* p2 = NULL;
	while (p1 != NULL)
	{
		p2 = p1->next;
		while (p2 != NULL)
		{
			if ((p2->ymin < p1->ymin) || ((p2->xmin <  p1->xmin) && (p2->ymin < p1->ymin)))
			{
				int cid;
				double cdd;
				cid = p1->ymax; p1->ymax = p2->ymax; p2->ymax = cid;
				cid = p1->ymin; p1->ymin = p2->ymin; p2->ymin = cid;
				cdd = p1->xmin; p1->xmin = p2->xmin; p2->xmin = cdd;
				cdd = p1->fm; p1->fm = p2->fm; p2->fm = cdd;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}

// 活跃边表AET的排序函数
void CCGwork0218View::SortAET(EDGE* pEDGE)
{
	EDGE * p1 = pEDGE;
	EDGE * p2 = NULL;
	while (p1 != NULL)
	{
		p2 = p1->next;
		while (p2 != NULL)
		{
			if (p1->xmin>p2->xmin)
			{
				int cid; double cdd;
				cid = p1->ymax; p1->ymax = p2->ymax; p2->ymax = cid;
				cid = p1->ymin; p1->ymin = p2->ymin; p2->ymin = cid;
				cdd = p1->xmin; p1->xmin = p2->xmin; p2->xmin = cdd;
				cdd = p1->fm; p1->fm = p2->fm; p2->fm = cdd;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}

// 获取边表
EDGE* CCGwork0218View::GetET(CArray <CPoint, CPoint>* points)
{
	EDGE * pHead = NULL;
	EDGE * p = NULL;
	for (int i = 0; i<points->GetSize(); i++)
	{
		CPoint point1 = (CPoint)points->GetAt(i);
		CPoint point2;//=(CPoint)points->GetAt(i+1);

		if (i == points->GetSize() - 1)
		{
			point2 = (CPoint)points->GetAt(0);

		}
		else{ point2 = (CPoint)points->GetAt(i + 1); }
		if (point1.y == point2.y)
			continue;
		EDGE* edge = new EDGE();
		edge->fm = (double)(point2.x - point1.x) / (point2.y - point1.y);
		if (point1.y>point2.y)
		{
			edge->ymax = point1.y;
			edge->ymin = point2.y;
			edge->xmin = point2.x;
		}
		else
		{
			edge->ymax = point2.y;
			edge->ymin = point1.y;
			edge->xmin = point1.x;
		}
		edge->next = NULL;
		edge->pre = NULL;
		if (p == NULL)
		{
			pHead = edge;
			p = edge;

		}
		else
		{
			p->next = edge;
			edge->pre = p;
			p = edge;
		}
	}

	p = pHead;
	EDGE * pNext = NULL;
	while (p != NULL)
	{
		if (p->next == NULL)
		{
			pNext = pHead;
		}
		else
			pNext = p->next;
		if (p->ymin != pNext->ymin && p->ymax != pNext->ymax)
		{
			if (p->ymax>pNext->ymax)
			{
				p->ymin++;
				p->xmin += p->fm;
			}
			else{
				pNext->ymin++;
				pNext->xmin += pNext->fm;
			}

		}
		p = p->next;
	}
	SortET(pHead);
	return pHead;
}

// 画像素点并过滤掉象限平分线上面的点
void CCGwork0218View::setPixel(CDC* pDC, int x, int y, COLORREF color)
{
	if (x % 10 == y % 10)
	{
		pDC->SetPixel(x, y, color);
	}
}

// 过滤像素点的放置以形成指定的填充字符
void CCGwork0218View::setnumberlinepixel(CDC* pDC, int i, int xetrl, int xl, int xr, int y, COLORREF color)
{
	int j = 0;// 循环基数30 其中，20/30 属于数字的表示
	int x = xetrl;
	while (x<xr)
	{
		if (j == 30){
			j = 0;
		}
		if (x>xl)
			switch (i)

		{
			case 0:
				if (j != 3 && j != 4 && j != 8 && j != 9 && j != 10 && j != 12 && j != 13 && j != 14 && j != 18 && j != 19 && j<20)
					pDC->SetPixel(x, y, color);
				break;
			case 1:
				if (j == 0 || j == 2 || j == 7 || j == 10 || j == 11 || j == 15 || j == 17)
					pDC->SetPixel(x, y, color);
				break;
			case 2:
				if (j != 1 && j != 3 && j != 4 && j != 8 && j != 9 && j != 10 && j != 12 && j != 13 && j != 14 && j != 18 && j != 19 && j<20)
					pDC->SetPixel(x, y, color);
				break;
			case 3:
				if (j == 0 || j == 2 || j == 5 || j == 11 || j == 15 || j == 17)
					pDC->SetPixel(x, y, color);
				break;
			case 4:
				if (j != 3 && j != 4 && j != 8 && j != 9 && j != 13 && j != 14 && j != 18 && j != 19 && j<20)
					pDC->SetPixel(x, y, color);
				break;
		}

		j++;
		x++;
	}
}
//====================================立方体绘制功能========================================================================================

// 矩阵的乘法
void CCGwork0218View::MutiTransMarix(double a[1][4], double b[4][4], double MutiResult[1][4])
{
	for (int i = 0; i<4; i++) MutiResult[0][i] = 0;
	for (int i = 0; i<1; i++)
	for (int j = 0; j<4; j++)
	for (int k = 0; k<4; k++)
		MutiResult[i][j] += a[i][k] * b[k][j];
}

// 将坐标转化为矩阵形式(向量)
void CCGwork0218View::TransPointToMarix(ThPoint & tp, double a[1][4])
{
	a[0][0] = tp.x;
	a[0][1] = tp.y;
	a[0][2] = tp.z;
	a[0][3] = 1;
}

// 将矩阵(向量)转化为三维坐标形式
void CCGwork0218View::TransMarixToPoint(double  a[1][4], ThPoint & tp)
{
	tp.x = a[0][0];
	tp.y = a[0][1];
	tp.z = a[0][2];
}

// 立方体的平移算法
void CCGwork0218View::MoveTrans(double x, double y, double z)
{
	double a[8][4], result[1][4];
	double moveMarix[4][4] =
	{
		{ 1, 0, 0, 0 }, { 0, 1, 0, 0 },
		{ 0, 0, 1, 0 }, { x, y, z, 1 }
	};

	for (int i = 0; i<8; i++)
	{
		TransPointToMarix(points[i], a + i);
		MutiTransMarix(a + i, moveMarix, result);
		TransMarixToPoint(result, points[i]);
	}
	ShadowTrans(-45);
}

// 立方体的斜交投影算法(将三维坐标转化为二维在屏幕显示)
void CCGwork0218View::ShadowTrans(int degree)
{
	double a[8][4], result[1][4];
	ThPoint pts[8];
	for (int i = 0; i<8; i++)
	{
		pts[i].x = points[i].x;
		pts[i].y = points[i].y;
		pts[i].z = points[i].z;
	}
	double shadowMarix[4][4] =
	{
		{ 1, 0, 0, 0 }, { 0, 1, 0, 0 },
		{ cos(degree), sin(degree), 0, 0 }, { 0, 0, 0, 1 }
	};

	for (int i = 0; i<8; i++)
	{
		TransPointToMarix(pts[i], a + i);
		MutiTransMarix(a + i, shadowMarix, result);
		TransMarixToPoint(result, pts[i]);
	}
	for (int i = 0; i<8; i++)
	{
		cpoints[i].x = (int)pts[i].x;
		cpoints[i].y = (int)pts[i].y;
	}
}

// 透视投影(Perspective projection)
void CCGwork0218View::PerspectivePROJ()
{
	//以z=0为投影平面,计算时采用的是通常意义上的左手坐标系
	//在计算完成值后,会进行坐标变换
	//定义投影中心
	double x0 = 140;
	double y0 = 140;
	double z0 = -140;
	double d = -z0;
	for (int i = 0; i < 8; i++)
	{
		cpoints[i].x = x0 + (d*(points[i].x - x0) / (points[i].z + d));
		cpoints[i].y = y0 + (d*(points[i].y - x0) / (points[i].z + d));
	}
}

// 立方体旋转算法,旋转中心可以是x,y或z轴,degree旋转的度数,rc旋转中心
void CCGwork0218View::RotateTrans(double degree, CString rc)
{
	double a[8][4], result[1][4];
	int i = 0;

	if (rc == "z")
	{
		double xRotateMarix[4][4] =
		{
			{ cos(degree*3.14 / 180), sin(degree*3.14 / 180), 0, 0 },
			{ -sin(degree*3.14 / 180), cos(degree*3.14 / 180), 0, 0 },
			{ 0, 0, 1, 0 }, { 0, 0, 0, 1 },
		};
		for (i = 0; i<8; i++)
		{
			TransPointToMarix(points[i], a + i);
			MutiTransMarix(a + i, xRotateMarix, result);
			TransMarixToPoint(result, points[i]);
		}
	}
	else if (rc == "x")
	{
		double yRotateMarix[4][4] =
		{
			{ 1, 0, 0, 0 },
			{ 0, cos(degree*3.14 / 180), sin(degree*3.14 / 180), 0 },
			{ 0, -sin(degree*3.14 / 180), cos(degree*3.14 / 180), 0 },
			{ 0, 0, 0, 1 }
		};
		for (int i = 0; i<8; i++)
		{
			TransPointToMarix(points[i], a + i);
			MutiTransMarix(a + i, yRotateMarix, result);
			TransMarixToPoint(result, points[i]);
		}

	}
	else if (rc == "y")
	{
		double zRotateMarix[4][4] =
		{
			{ cos(degree*3.14 / 180), 0, -sin(degree*3.14 / 180), 0 },
			{ 0, 1, 0, 0 },
			{ sin(degree*3.14 / 180), 0, cos(degree*3.14 / 180), 0 },
			{ 0, 0, 0, 1 }
		};
		for (i = 0; i<8; i++)
		{
			TransPointToMarix(points[i], a + i);
			MutiTransMarix(a + i, zRotateMarix, result);
			TransMarixToPoint(result, points[i]);
		}

	}
	ShadowTrans(-45);
}

// 立方体的比例变换算法
void CCGwork0218View::BigerOrSmallerTrans(double timeX, double timeY, double timeZ)
{
	double a[8][4], result[1][4];
	double bsMarix[4][4] =
	{
		{ timeX, 0, 0, 0 }, { 0, timeY, 0, 0 },
		{ 0, 0, timeZ, 0 }, { 0, 0, 0, 1 }
	};
	for (int i = 0; i<8; i++)
	{
		TransPointToMarix(points[i], a + i);
		MutiTransMarix(a + i, bsMarix, result);
		TransMarixToPoint(result, points[i]);
	}
	ShadowTrans(-45);
}

// 获取绘图区域的大小
void CCGwork0218View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	cxClient = cx;
	cyClient = cy;
}

// 工具条->缩放工具
void CCGwork0218View::OnBgsm()
{
	// TODO:  在此添加命令处理程序代码
	BGSMDialog B_dlg;
	if (IDOK == B_dlg.DoModal())
	{
		BigerOrSmallerTrans(B_dlg.m_sx, B_dlg.m_sy, B_dlg.m_sz);
	}
	Invalidate();
	UpdateWindow();
}

// 工具条->平移工具
void CCGwork0218View::OnMovecube()
{
	// TODO:  在此添加命令处理程序代码
	MoveCubeDialog M_dlg;
	if (IDOK == M_dlg.DoModal())
	{
		MoveTrans(M_dlg.m_dx, M_dlg.m_dy, M_dlg.m_dz);
	}
	Invalidate();
	UpdateWindow();
}

// 工具条->旋转工具
void CCGwork0218View::OnRotatecube()
{
	// TODO:  在此添加命令处理程序代码
	RoateCubeDialog BT_dlg;
	if (IDOK == BT_dlg.DoModal())
	{
		RotateTrans(BT_dlg.m_degree, BT_dlg.m_rc);
	}
	Invalidate();
	UpdateWindow();
}

// 给坐标点做初始化
void CCGwork0218View::InitPoints()
{
	int a = 100;//初始边长
	//左手屏幕坐标系,z轴正方向朝屏幕里面
	points[0].x = 0; points[0].y = a; points[0].z = a;//0 a a
	points[1].x = a; points[1].y = a; points[1].z = a;//a a a 
	points[2].x = a; points[2].y = 0; points[2].z = a;//a 0 a
	points[3].x = 0; points[3].y = 0; points[3].z = a;//0 0 a
	points[4].x = 0; points[4].y = a; points[4].z = 0;//0 a 0
	points[5].x = a; points[5].y = a; points[5].z = 0;//a a 0
	points[6].x = a; points[6].y = 0; points[6].z = 0;//a 0 0
	points[7].x = 0; points[7].y = 0; points[7].z = 0;//0 0 0 
	
	cpoints[0].x = 0; cpoints[0].y = a; cpoints[0].z = a;//0 a a
	cpoints[1].x = a; cpoints[1].y = a; cpoints[1].z = a;//a a a 
	cpoints[2].x = 0; cpoints[2].y = 0; cpoints[2].z = a;//0 0 a
	cpoints[3].x = a; cpoints[3].y = 0; cpoints[3].z = a;//a 0 a
	cpoints[4].x = 0; cpoints[4].y = a; cpoints[4].z = 0;//0 a 0
	cpoints[5].x = a; cpoints[5].y = a; cpoints[5].z = 0;//a a 0
	cpoints[6].x = 0; cpoints[6].y = 0; cpoints[6].z = 0;//0 0 0 
	cpoints[7].x = a; cpoints[7].y = 0; cpoints[7].z = 0;//a 0 0
}

// 键盘平移立方体
// 其中down向下平移一个单位，up向上平移一个单位，
// left向左平移一个单位，right向右平移一个单位
void CCGwork0218View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	switch (nChar)
	{
	case VK_DOWN:
		MoveTrans(0, 1, 0);
		break;
	case VK_UP:
		MoveTrans(0, -1, 0);
		break;
	case VK_LEFT:
		MoveTrans(-1, 0, 0);
		break;
	case VK_RIGHT:
		MoveTrans(1, 0, 0);
		break;
	}
	Invalidate();
	UpdateWindow();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


// 键盘缩放和旋转(需要关闭输入法)
// 其中x以x轴为旋转中心旋转一度，y以y轴为旋转中心旋转一度，
// z以z轴为旋转中心旋转一度，b变大,s缩小
void CCGwork0218View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnChar(nChar, nRepCnt, nFlags);
	switch (nChar)
	{
	case 'x':
		RotateTrans(1, CString("x"));
		break;
	case 'y':
		RotateTrans(1, CString("y"));
		break;
	case 'z':
		RotateTrans(1, CString("z"));
		break;
	case 'b':
		BigerOrSmallerTrans(1.1, 1.1, 1.1);
		break;
	case 's':
		BigerOrSmallerTrans(0.9, 0.9, 0.9);
		break;
	}
	Invalidate();
	UpdateWindow();
	CView::OnChar(nChar, nRepCnt, nFlags);
}

// 工具条->立方体画笔工具
void CCGwork0218View::OnDrawcube()
{
	// TODO:  在此添加命令处理程序代码
	m_dsDrawSort = DsCube;
	Invalidate();
	UpdateWindow();
}

// 工具条->透视投影算法
void CCGwork0218View::OnCubet()
{
	// TODO:  在此添加命令处理程序代码
	m_proFunc = TOUSHI;
	Invalidate();
	UpdateWindow();
	isCubeInitialized = true;
}

// 工具条->斜交投影算法
void CCGwork0218View::OnCubex()
{
	// TODO:  在此添加命令处理程序代码
	m_proFunc = XIEJIAO;
	Invalidate();
	UpdateWindow();
	isCubeInitialized = true;
}
/*==============================曲线的绘制==============================================*/

// 工具条->绘制Bezier曲线
void CCGwork0218View::OnBezier()
{
	m_dsDrawSort =DsBezier;//切换为Bezier曲线画笔
	// TODO:  在此添加命令处理程序代码
	m_eChooseType = Bezier;
	m_bIsChoosed = true;
	m_bStopDraw = false;
	while (m_vInputPoint.size() != 0)
	{
		m_vInputPoint.pop_back();
	}
	while (m_vControlPoint.size() != 0)
	{
		m_vControlPoint.pop_back();
	}
	while (m_vXiShu.size() != 0)
	{
		m_vXiShu.pop_back();
	}
}

// 工具条->绘制B样条曲线
void CCGwork0218View::OnBsize()
{
	m_dsDrawSort = DsBsize;//切换为B样条画笔
	// TODO:  在此添加命令处理程序代码
	m_eChooseType = BYangTiao;
	m_bIsChoosed = true;
	m_bStopDraw = false;
	while (m_vInputPoint.size() != 0)
	{
		m_vInputPoint.pop_back();
	}
	while (m_vControlPoint.size() != 0)
	{
		m_vControlPoint.pop_back();
	}
	while (m_vXiShu.size() != 0)
	{
		m_vXiShu.pop_back();
	}
}

// 绘制三次均匀B样条曲线
void CCGwork0218View::DrawB(CDC* pDC, CPoint point1, CPoint point2, CPoint point3, CPoint point4)
{
	int x1, y1, x2, y2, x3, y3, x4, y4;//传递4个点坐标值
	x1 = point1.x;
	y1 = point1.y;
	x2 = point2.x;
	y2 = point2.y;
	x3 = point3.x;
	y3 = point3.y;
	x4 = point4.x;
	y4 = point4.y;

	pDC->SetPixel(x1, y1, (COLORREF)0x000000FF);		//用红颜色描这4个坐标点
	pDC->SetPixel(x2, y2, (COLORREF)0x000000FF);
	pDC->SetPixel(x3, y3, (COLORREF)0x000000FF);
	pDC->SetPixel(x4, y4, (COLORREF)0x000000FF);
	pDC->MoveTo(x1, y1);		//描这4个坐标点的连线
	pDC->LineTo(x2, y2);
	pDC->LineTo(x3, y3);
	pDC->LineTo(x4, y4);

	double x = 0, y = 0, ax, ay, s1, s2, s3, u;
	pDC->SetPixel(x1, y1, RGB(255, 0, 0));
	ax = (x1 + 4 * x2 + x3) / 6.0;
	ay = (y1 + 4 * y2 + y3) / 6.0;
	for (u = 0; u <= 1; u = u + 0.001)
	{
		s1 = u;
		s2 = s1*s1;
		s3 = s1*s1*s1;
		x = ax + ((x3 - x1) / 2.0)*s1 + ((x1 - 2 * x2 + x3) / 2.0)*s2 + ((x4 - 3 * x3 + 3 * x2 - x1) / 6.0)*s3;
		y = ay + ((y3 - y1) / 2.0)*s1 + ((y1 - 2 * y2 + y3) / 2.0)*s2 + ((y4 - 3 * y3 + 3 * y2 - y1) / 6.0)*s3;
		if (u == 0)
		{
			pDC->MoveTo((int)ax, (int)ay);
		}
		pDC->LineTo((int)x, (int)y);
		if (u == 0 || u == 1)
		{
			pDC->Ellipse(x - 3, y - 3, x + 3, y + 3);
		}
	}

	return;
}

// 绘制Bezier曲线
void CCGwork0218View::DrawBezier(CDC* pDC)
{
	int iNumber = m_vInputPoint.size();
	pDC->MoveTo(m_vInputPoint[0]);
	if (iNumber == 1)
	{
		pDC->SetPixel(m_vInputPoint[0], (COLORREF)0x000000FF);
		return;
	}
	for (int i = 0; i<iNumber - 1; i++)
	{
		pDC->SetPixel(m_vInputPoint[i], (COLORREF)0x000000FF);
		pDC->SetPixel(m_vInputPoint[i + 1], (COLORREF)0x000000FF);
		pDC->LineTo(m_vInputPoint[i + 1]);
	}
	double u, x, y;
	pDC->SetPixel(m_vInputPoint[0], RGB(255, 0, 0));
	pDC->MoveTo(m_vInputPoint[0]);
	for (u = 0; u <= 1; u = u + 0.001)
	{
		x = 0; y = 0;
		for (int i = 0; i<iNumber; i++)
		{
			x += C(iNumber - 1, i)*N(u, i)*N((1 - u), (iNumber - 1 - i))*m_vInputPoint[i].x;
			y += C(iNumber - 1, i)*N(u, i)*N((1 - u), (iNumber - 1 - i))*m_vInputPoint[i].y;
		}
		pDC->LineTo((int)x, (int)y);
	}

	return;
}

// 求阶乘
int CCGwork0218View::JieCheng(int n)
{
	if (n == 1 || n == 0)
	{
		return 1;
	}
	else
	{
		return n*JieCheng(n - 1);
	}
}

// 求组合数
double CCGwork0218View::C(int n, int i)
{
	return ((double)JieCheng(n)) / ((double)(JieCheng(i)*JieCheng(n - i)));
}

// 求一个数u的n次方
double CCGwork0218View::N(double u, int n)
{
	double sum = 1.0;
	if (n == 0)
	{
		return 1;
	}
	for (int i = 0; i<n; i++)
	{
		sum *= u;
	}
	return sum;
}

// 判断点是否在控制顶点
void CCGwork0218View::PointOnInputPoint(CPoint CheckedPoint)
{
	double dDistence;

	int i;
	for (i = 0; i<m_vInputPoint.size(); i++)
	{
		dDistence = (CheckedPoint.x - m_vInputPoint[i].x)*(CheckedPoint.x - m_vInputPoint[i].x) +
			(CheckedPoint.y - m_vInputPoint[i].y)*(CheckedPoint.y - m_vInputPoint[i].y) - 4 * 4;
		if (dDistence <= 0)
		{
			m_iItemOfEditPoint = i;
			m_bPointChoosed = true;
			return;
		}
	}
	m_bPointChoosed = false;
	return;
}

//工具条->重置
void CCGwork0218View::OnReset()
{
	// 将所有的参数初始化
	m_dsDrawSort = DsNull;
	m_sharpList.RemoveAll();
	m_fillList.RemoveAll();
	//bDrawMark = false;
	//bMoveMark = false;
	//MoveStart=(0, 0);
	//MoveEnd=(0, 0);
	//bRotateMark = false;
	//RotateBase=(0, 0);
	//bFillMark = false;
	//ptNum=1;
	//RotateAngle = 0.0;
	//m_bDrawMode = false;
	//beflag = 0;
	//xzflag = 0;
	//beizerItem = NULL;
	//cxClient = 0;
	//cyClient = 0;
	//m_cMovePoint = 0;
	//m_bIsChoosed = false;
	//m_bStopDraw = false;
	//m_bPointChoosed = false;
	//m_bMakeSure = false;
	//m_iItemOfEditPoint = 0;
	//m_dsDrawSort = DsNull;
	//m_startPoint.x = 0;
	//m_startPoint.y = 0;
	//m_endPoint.x = 0;
	//m_endPoint.y = 0;
	//m_bIsMouseDown = 0;
	//m_lPenColor = RGB(0, 0, 255);
	//m_iPenWidth = 1;
	//m_lBkColor = RGB(255, 255, 255);
	//m_lFillColor = RGB(255, 0, 0);
	//m_LineType = BRDL;
	//m_CircleType = MDC;
	//m_FillType = EXTFLOODFILL;
	//m_proFunc = TOUSHI;
	//m_bDrawMode = true;
	//isCubeInitialized = true;
	Invalidate();
	UpdateWindow();
}
