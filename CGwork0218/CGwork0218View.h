
// CGwork0218View.h : CCGwork0218View 类的接口
//

//#pragma once
#include "atltypes.h"
#include "stdlib.h"
#include "math.h"
#include <list>
#include <vector>
#include"CGwork0218Doc.h"
#include "Beizer.h"
#include "afxtempl.h"
#include"Fill.h"
#include "vssym32.h"
struct MYPOINT//圆
{
	int x;
	int y;     //半径
};

struct EDGE {//边表的节点
	int ymin;
	int ymax;
	double xmin;
	double fm;

	EDGE * next;
	EDGE * pre;
};

struct ThPoint{/*这里定义一个存储三维点的结构*/
	double x;
	double y;
	double z;
};
// 画笔类型
enum DRAWSORT{ DsNull, DsLine,DsPolygon, DsMovePolygon,DsRotatePolygon,DsCircle,DsFill,DsFill2,DsFill3,DsBezier,DsBsize,DsCube};
// 画线算法
enum LINETYPE{ DDA, MDA, BRDL };
// 画圆算法
enum CIRCLETYPE{ MDC, BRDC };
// 投影算法
enum ProFunction{TOUSHI,XIEJIAO};
// 曲线操作类型
enum ChooseType{ Bezier, BYangTiao, NHSanCiYangTiao, NHBezier, NHBYangTiao };
// 画曲线时鼠标的状态
enum MouseStatus{ LButtonDown, LButtonUp, RButtonDown, RButtonUp, MouseMove };

using namespace std;

class CCGwork0218View : public CView
{
protected: // 仅从序列化创建
	CCGwork0218View();
	DECLARE_DYNCREATE(CCGwork0218View)

// 特性
public:
	CCGwork0218Doc* GetDocument() const;
	enum FILLTYPE{ FEEDFILL, EXTFLOODFILL };//填充方式
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CCGwork0218View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 用于标记是否处于多边形绘制模式
	bool bDrawMark;
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMove();
	// 多边形平移的实现函数
	void Move(CPoint start, CPoint end);
	afx_msg void OnRotate();
	// 多边形旋转的实现函数
	void Rotate(CPoint ptBase, double angle);
	afx_msg void OnFill();
	// 多边形填充的实现含数
	void Fill();
	// 移动标记
	bool bMoveMark;
	// 移动的起点
	CPoint MoveStart;
	// 移动的终止点
	CPoint MoveEnd;
	// 旋转操作标记
	bool bRotateMark;
	// 旋转中心
	CPoint RotateBase;
	// 填充标记
	bool bFillMark;
	// 平移的步长
	int ptNum;
	// 多边形填充颜色
	COLORREF clr;
	// 旋转角度
	double RotateAngle;
	// 画笔光标
	HCURSOR DrawCur;

	DRAWSORT m_dsDrawSort;		//画图类型
	LINETYPE m_LineType;		//画线算法
	CIRCLETYPE m_CircleType;	//画圆算法
	ProFunction m_proFunc;      //投影算法
	bool m_bDrawMode;
	bool isCubeInitialized;     //是否需要对正方体的角点坐标做初始化操作
	POINT m_startPoint;//前点
	POINT m_endPoint;  //后点

	bool m_bIsMouseDown;//鼠标是否在移动

	list<MYPOINT> m_listpoint;

	int m_iPenWidth;  //画笔宽度
	long m_lPenColor; //画笔颜色
	long m_lBkColor;  //背景颜色
	long m_lFillColor;//填充颜色

	afx_msg void OnPolygon();
	afx_msg void OnDrawpolygon();
	afx_msg void OnDrawline();
	// //画直线的执行函数(Bresenham算法)
	void DrawLine(POINT p1, POINT p2, CDC* pDC);
	// 画圆的实现算法(Bres算法)
	void DrawCircle(POINT pc, int r, CDC* pDC);
	// 画圆算法的辅助子函数
	void CirPort(int x0, int y0, int x, int y, CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int beflag;
	int xzflag;
	CTypedPtrList<CObList, CSharp*> m_sharpList;
	CTypedPtrList<CObList,CFill*> m_fillList;
	CBeizer *beizerItem;
	int GetDist(POINT p1, POINT p2);
	void DrawFill(CPoint point, CDC* pDC);
	void Seedfill(int x, int y, int oldcolor, int newcolor, CDC* pDC);
	void Fill(CPoint point, CDC* pDC);
	// 填充方式
	FILLTYPE m_FillType;
	afx_msg void OnDrawline2();
	afx_msg void OnFillpolygon();
	afx_msg void OnChoosecolor();
	afx_msg void OnPencolor();
	afx_msg void OnNumberfill();
	// 使用边表的多边形扫描转换算法
	void Polygonfill(CDC* pDC, CArray<CPoint, CPoint>* points, COLORREF color);
	// 边表ET排序函数
	void SortET(EDGE* pEDGE);
	// 活跃边表AET的排序函数
	void SortAET(EDGE* pEDGE);
	// 获取边表
	EDGE* GetET(CArray <CPoint, CPoint>* points);
	// 画像素点并过滤掉象限平分线上面的点
	void setPixel(CDC* pDC, int x, int y, COLORREF color);
	// 过滤像素点的放置以形成指定的填充字符
	void setnumberlinepixel(CDC* pDC, int i, int xetrl, int xl, int xr, int y, COLORREF color);
	afx_msg void OnDefaultmouse();
	// 客户端界面的窗口尺寸
	int cxClient;
	int cyClient;
	ThPoint points[8];
	ThPoint cpoints[8];
		
	void TransPointToMarix(ThPoint & tp, double a[1][4]);

	void TransMarixToPoint(double  a[1][4], ThPoint & tp);
	// 立方体的平移算法
	void MoveTrans(double x, double y, double z);

	void MutiTransMarix(double a[1][4], double b[4][4], double MutiResult[1][4]);
	// 立方体的斜交投影算法(将三维坐标转化为二维在屏幕显示)
	void ShadowTrans(int degree);
	// 立方体旋转算法,旋转中心可以是x,y或z轴,degree旋转的度数,rc旋转中心	
	void RotateTrans(double degree, CString rc);

	// 立方体的比例变换算法
	void BigerOrSmallerTrans(double timeX, double timeY, double timeZ);

	// 透视投影(Perspective projection)
	void PerspectivePROJ();

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBgsm();

	afx_msg void OnMovecube();

	afx_msg void OnRotatecube();
	// 给坐标点做初始化
	void InitPoints();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDrawcube();
	afx_msg void OnCubet();
	afx_msg void OnCubex();
	// 存放用户输入的曲线控制点
	vector<CPoint> m_vInputPoint;
	// 存放控制顶点（拟合时用）
	vector<CPoint> m_vControlPoint;
	// 存放用高斯消元法求解矩阵时的系数（拟合时用）
	vector<double> m_vXiShu;
	// 移动鼠标的的点,帮助用户预览曲线形状
	CPoint m_cMovePoint;
	// 用户是否选择应用
	bool m_bIsChoosed;
	// 用户是否停止画图（单击右键）
	bool m_bStopDraw;
	// 用户是否选中控制顶点
	bool m_bPointChoosed;
	// 在停止画图并移动选中控制的顶点时
	bool m_bMakeSure;
	// 户选中要移动的控制顶点在栈中的位置
	int m_iItemOfEditPoint;
	// 用户选择的应用类型
	ChooseType m_eChooseType;
	// 记录当前鼠标状态
	MouseStatus m_eMouseStatus;
	// 当前窗口的坐标信息
	RECT rect;
	afx_msg void OnBezier();
	afx_msg void OnBsize();
	// 绘制三次均匀B样条曲线
	void DrawB(CDC* pDC, CPoint point1, CPoint point2, CPoint point3, CPoint point4);
	// 绘制Bezier曲线
	void DrawBezier(CDC* pDC);
	// 求阶乘
	int JieCheng(int n);
	// 求组合数
	double C(int n, int i);
	// 求一个数u的n次方
	double N(double u, int n);
	// 判断点是否在控制顶点
	void PointOnInputPoint(CPoint CheckedPoint);
	afx_msg void OnReset();
};

#ifndef _DEBUG  // CGwork0218View.cpp 中的调试版本
inline CCGwork0218Doc* CCGwork0218View::GetDocument() const
   { return reinterpret_cast<CCGwork0218Doc*>(m_pDocument); }
#endif

