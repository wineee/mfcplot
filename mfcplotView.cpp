
// mfcplotView.cpp: CmfcplotView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mfcplot.h"
#endif

#include "mfcplotDoc.h"
#include "mfcplotView.h"
#include <vector>
using std::vector;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcplotView

IMPLEMENT_DYNCREATE(CmfcplotView, CView)

BEGIN_MESSAGE_MAP(CmfcplotView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_MOVE_MENU, &CmfcplotView::OnMoveMenu)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//ON_UPDATE_COMMAND_UI(ID_EDGE_MENU, &CmfcplotView::OnUpdateEdgeMenu)
ON_UPDATE_COMMAND_UI(ID_MOVE_MENU, &CmfcplotView::OnUpdateMoveMenu)
ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CmfcplotView 构造/析构

CmfcplotView::CmfcplotView() noexcept
{
	// TODO: 在此处添加构造代码
	isMoving = false;
	//下面这个没什么用，防止编译警告
	tmp_Xmin = m_Xmin = -10;
	tmp_Xmax = m_Xmax = 10;
	tmp_Ymin = m_Ymin = -1;
	tmp_Ymax = m_Ymax = 1;
}

CmfcplotView::~CmfcplotView()
{
}

BOOL CmfcplotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

//


double CmfcplotView::LPxtoFPx(int x) {
	return m_Xmin + (1.0 * x - nLeft) * (m_Xmax - m_Xmin) / (1.0 * nRight - nLeft);
}

int CmfcplotView::FPxtoLPx(double x) {
	return nLeft + (int)round((x - m_Xmin) * (1.0 * nRight - nLeft) / (m_Xmax - m_Xmin));
}

double CmfcplotView::LPytoFPy(int y) {
	return m_Ymin + (1.0 * nButton - y) * (m_Ymax - m_Ymin) / (1.0 * nButton - nTop);
}

int CmfcplotView::FPytoLPy(double y) {
	return nButton - (int)round((y - m_Ymin) * (1.0 * nButton - nTop) / (m_Ymax - m_Ymin));
}

// CmfcplotView 绘图

void CmfcplotView::OnDraw(CDC* pDC)
{
	CmfcplotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_Xmin = pDoc->m_Xmin;//极值保存在Doc中
	m_Xmax = pDoc->m_Xmax;
	m_Ymin = pDoc->m_Ymin;
	m_Ymax = pDoc->m_Ymax;
	
	CRect rect;
	GetClientRect(&rect);//获得视图区

	nTop = (int)round(rect.bottom * 0.1);  //函数图像不会占据整个视图区
	nButton = (int)round(rect.bottom * 0.9);
	nLeft = (int)round(rect.right * 0.1);
	nRight = (int)round(rect.right * 0.9);

	if (pDoc->m_WillShowEdge) {//画边框
		pDC->MoveTo(nLeft, nTop);
		pDC->LineTo(nLeft, nButton);
		pDC->LineTo(nRight, nButton);
		pDC->LineTo(nRight, nTop);
		pDC->LineTo(nLeft, nTop);
	}

	//画x坐标信息
	int nX,nY;
	bool BIGX = abs(m_Xmin) > 100 || abs(m_Xmax) > 100;//x坐标值比较大时，标注更稀
	for (nX = nLeft; nX < nRight; nX += (BIGX ? 100 : 50)) { //每隔100/50像素一个标注
		CRect textRect(nX - (BIGX ? 50 : 25), nButton + 1, nX + (BIGX ? 50 : 25), nButton + 20);//显示区域
		CString xInfo;
		xInfo.Format(_T("%.2f"),LPxtoFPx(nX));
		pDC->DrawText(xInfo, &textRect, DT_SINGLELINE | DT_CENTER);
		                                    //单行,上下左右居中显示
	}
	if (nX - nRight <= (BIGX ? 50 : 25)) {//最后一个x坐标，与前一个标注距离太近则不显示
		CRect textRect(nRight, nButton + 1, nRight + 50, nButton + 20);
		CString xInfo;
		xInfo.Format(_T("%.2f"),m_Xmax);
		pDC->DrawText(xInfo, &textRect, DT_SINGLELINE | DT_LEFT | DT_TOP);
	}

	//y坐标
	for (nY = nButton - 50; nY > nTop; nY -= 50) {
		CRect textRect(nLeft - 200, nY-10, nLeft - 3, nY + 10);
		CString yInfo;
		yInfo.Format(_T("%.2f"), LPytoFPy(nY));
		pDC->DrawText(yInfo, &textRect, DT_SINGLELINE | DT_RIGHT);
	}
	if (nTop - nY <= 25) {
		CRect textRect(nLeft - 200, nTop - 10, nLeft - 3, nTop + 10);
		CString yInfo;
		yInfo.Format(_T("%.2f"),m_Ymax);
		pDC->DrawText(yInfo, &textRect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
	}


	//  显示网格
	if (pDoc->m_WillShowGrid) {
		CPen pen(PS_DOT, 1, RGB(100, 100, 100));           //创建笔，虚线，并调整坐标颜色灰色
		CPen *pOldPen = (CPen *)pDC->SelectObject(&pen);
		for (nX = nLeft+50; nX < nRight; nX += 50) {
			pDC->MoveTo(nX, nTop);
			pDC->LineTo(nX, nButton);
		}
		for (nY = nButton - 50; nY > nTop; nY -= 50) {
			pDC->MoveTo(nLeft, nY);
			pDC->LineTo(nRight, nY);
		}
		pDC->SelectObject(pOldPen);
	}

	// 显示坐标轴
	if (pDoc->m_WillShowAxis) {
		CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		int oX = FPxtoLPx(0);
		int oY = FPytoLPy(0);
		bool showY = oX >= nLeft && oX <= nRight;
		bool showX = oY >= nTop && oY <= nButton;//判断x,y轴是否在范围内
		if (showX) {
			pDC->MoveTo(nLeft - 10, oY);
			pDC->LineTo(nRight + 10, oY);
		}
		if (showY) {
			pDC->MoveTo(oX, nButton + 10);
			pDC->LineTo(oX, nTop - 10);
		}
		if (showX && showY) {
			pDC->TextOutW(oX + 1, oY + 1, _T("O"));
		}
		if (showX) {
			pDC->MoveTo(nRight + 10, oY);
			pDC->LineTo(nRight + 5, oY + 5);
			pDC->MoveTo(nRight + 10, oY);
			pDC->LineTo(nRight + 5, oY - 5);
			pDC->TextOutW(nRight + 10, oY, _T("X轴"));
		}
		if (showY) {
			pDC->MoveTo(oX, nTop - 10);
			pDC->LineTo(oX - 5, nTop - 5);
			pDC->MoveTo(oX, nTop - 10);
			pDC->LineTo(oX + 5, nTop - 5);
			pDC->TextOutW(oX + 5, nTop - 10, _T("Y轴"));
		}
		pDC->SelectObject(pOldPen);
	}

	
	POSITION p = pDoc->m_List.GetHeadPosition();

	int showTop = nTop;
	while (p != nullptr) {
		bool shouldMov = true;//一段曲线第一个点MoveTo，其他都是LineTo
		FuncData* tmpFD = (FuncData*)pDoc->m_List.GetNext(p);
		CPen pen(tmpFD->m_penType, tmpFD->m_penWidth, tmpFD->m_color);
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);

		if (tmpFD->FuncCas == CAS_NORMAL) {//动态X坐标模式下，普通函数x范围与视图不同时自动同步
			if (pDoc->m_ForceXrange && isMoving!=2)
				if (tmpFD->minX != m_Xmin || tmpFD->maxX != m_Xmax) {
					tmpFD->minX = m_Xmin;
					tmpFD->maxX = m_Xmax;
					tmpFD->CalcList();
				}
		}

		for (auto dot : tmpFD->vetPoint) {
			if (dot.first < m_Xmin || dot.first > m_Xmax || dot.second < m_Ymin || dot.second > m_Ymax || dot.second != dot.second) {
				shouldMov = true;
				continue;
			}
			if (shouldMov) {
				pDC->MoveTo(FPxtoLPx(dot.first), FPytoLPy(dot.second));
				shouldMov = false;
			}
			else
				pDC->LineTo(FPxtoLPx(dot.first), FPytoLPy(dot.second));
		}

		pDC->MoveTo(nRight+5, showTop);//显示图例
		pDC->LineTo(rect.right, showTop);
		showTop += 5;
		if (tmpFD->FuncCas == CAS_NORMAL)
		    pDC->TextOutW(nRight + 5, showTop, _T("f(x)=")+tmpFD->m_Equation);
		else if (tmpFD->FuncCas == CAS_POLAR)
			pDC->TextOutW(nRight + 5, showTop, _T("r(t)=") + tmpFD->m_Equation);
		else if (tmpFD->FuncCas == CAS_TWO) {
			pDC->TextOutW(nRight + 5, showTop, _T("x(t)=") + tmpFD->m_Equation);
			showTop += 20;
			pDC->TextOutW(nRight + 5, showTop, _T("y(t)=") + tmpFD->GetEquation2());
		} else if (tmpFD->FuncCas == CAS_DATA)
			pDC->TextOutW(nRight + 5, showTop, _T("y(t)=") + tmpFD->m_Equation);
		showTop += 25;
		pDC->SelectObject(pOldPen);
	}
}


// CmfcplotView 打印

BOOL CmfcplotView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmfcplotView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmfcplotView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CmfcplotView 诊断

#ifdef _DEBUG
void CmfcplotView::AssertValid() const
{
	CView::AssertValid();
}

void CmfcplotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmfcplotDoc* CmfcplotView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmfcplotDoc)));
	return (CmfcplotDoc*)m_pDocument;
}
#endif //_DEBUG


// CmfcplotView 消息处理程序
bool tmp_redraw = false;

void CmfcplotView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CStatusBar* pBar = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	if (pBar) {
		CString msg;
		if (point.x >= nLeft && point.x <= nRight && point.y >= nTop && point.y <= nButton)
			msg.Format(_T("(%.1f,%.1f)"), LPxtoFPx(point.x), LPytoFPy(point.y));
		else
			msg = _T("(NaN,NaN)");
		pBar->SetPaneText(1, msg);
	}

	if (isMoving==2) {
		::SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		CmfcplotDoc* pDoc = GetDocument();
		double detx = LPxtoFPx(point.x) - LPxtoFPx(m_posStart.x);
		pDoc->m_Xmin = tmp_Xmin - detx;
		pDoc->m_Xmax = tmp_Xmax - detx;
		double dety = LPytoFPy(point.y) - LPytoFPy(m_posStart.y);
		pDoc->m_Ymin = tmp_Ymin - dety;
		pDoc->m_Ymax = tmp_Ymax - dety;
		//RedrawWindow();
		CDC* pDC = GetDC();
		//创建一个内存中的显示设备
		CDC MemDC;
		MemDC.CreateCompatibleDC(NULL);
		//创建一个内存中的图像
		CBitmap MemBitmap;
		CRect rect;
		GetClientRect(&rect);
		MemBitmap.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
		//指定内存显示设备在内存中的图像上画图
		MemDC.SelectObject(&MemBitmap);
		//先用一种颜色作为内存显示设备的背景色
		MemDC.FillSolidRect(rect.left, rect.top, rect.right, rect.bottom, RGB(144, 144, 144));
		this->OnDraw(&MemDC);
		//将内存中画好的图像直接拷贝到屏幕指定区域上
		pDC->BitBlt(rect.left, rect.top, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);

		//释放相关资源
		ReleaseDC(pDC);

	}
	else if (isMoving == 1) {
		::SetCursor(LoadCursor(NULL, IDC_HAND));
	}

	CmfcplotDoc* pDoc = GetDocument();
	if (GetDocument()->m_ShowNearPoint && isMoving != 2) {
		
		pair<double, double> nearDot(1e14, 1e14);
		pair<double, double> nowDot = std::make_pair(LPxtoFPx(point.x), LPytoFPy(point.y));//当前函数坐标
		POSITION p = pDoc->m_List.GetHeadPosition();
		COLORREF tmpcolor = RGB(0, 0, 0);
		while (p != nullptr) {
			FuncData* tmpFD = (FuncData*)pDoc->m_List.GetNext(p);
			if (tmpFD->GetNearest(nowDot, nearDot)) {
				tmpcolor = tmpFD->m_color;//枚举函数，找最近的
			}
		}
		int nX = FPxtoLPx(nearDot.first);
		int nY = FPytoLPy(nearDot.second);

        CDC* pDC = GetDC();
		if (tmp_redraw) {//标记有输出，刷新
			CDC MemDC;
			MemDC.CreateCompatibleDC(NULL);
			CBitmap MemBitmap;
			CRect rect;
			GetClientRect(&rect);
			MemBitmap.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
			MemDC.SelectObject(&MemBitmap);
			MemDC.FillSolidRect(rect.left, rect.top, rect.right, rect.bottom, RGB(255, 255, 255));
			this->OnDraw(&MemDC);
			pDC->BitBlt(rect.left, rect.top, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);
		}
		if (abs(nX - point.x) < 5 && abs(nY - point.y) < 5) {
			tmp_redraw = true;//输出了，标记一下
			CString msg;
			msg.Format(_T("(%.2f,%.2f)"), nearDot.first, nearDot.second);
			CRect textrect(nX, nY - 10, nX + 100, nY + 10);
			COLORREF oldcolor = pDC->SetTextColor(tmpcolor);
			pDC->DrawText(msg, &textrect, DT_SINGLELINE | DT_CENTER);
			pDC->SetTextColor(oldcolor);
		}
		
		ReleaseDC(pDC);
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL CmfcplotView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isMoving) {
//		SetCursor(m_cursor);
		return TRUE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CmfcplotView::OnMoveMenu()
{
	// TODO: 在此添加命令处理程序代码
	if (isMoving) {
		isMoving = 0;
	}
	else {
		isMoving = 1;
		//m_cursor = LoadCursor(NULL, IDC_HAND);
		::SetCursor(LoadCursor(NULL, IDC_HAND));
	}
}



void CmfcplotView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SetCapture();
	if (isMoving == 1) {
	//	m_cursor = LoadCursor(NULL, IDC_SIZEALL);
		isMoving = 2;
		m_posStart = point;
		CmfcplotDoc* pDoc = GetDocument();
		tmp_Xmin = pDoc->m_Xmin;
		tmp_Xmax = pDoc->m_Xmax;
		tmp_Ymin = pDoc->m_Ymin;
		tmp_Ymax = pDoc->m_Ymax;
		::SetCursor(LoadCursor(NULL, IDC_SIZEALL));
	}
	CView::OnLButtonDown(nFlags, point);
}


void CmfcplotView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isMoving == 2) {
		isMoving = 1;
		//m_cursor = LoadCursor(NULL, IDC_HAND);
		::SetCursor(LoadCursor(NULL, IDC_HAND));
		CmfcplotDoc* pDoc = GetDocument();
		double detx = LPxtoFPx(point.x) - LPxtoFPx(m_posStart.x);
		pDoc->m_Xmin = tmp_Xmin - detx;
		pDoc->m_Xmax = tmp_Xmax - detx;
		double dety = LPytoFPy(point.y) - LPytoFPy(m_posStart.y);
		pDoc->m_Ymin = tmp_Ymin - dety;
		pDoc->m_Ymax = tmp_Ymax - dety;
		RedrawWindow();
	}
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}


void CmfcplotView::OnUpdateMoveMenu(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(isMoving!=0);
}


void CmfcplotView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString msg;
	msg.Format(_T("(%.4f,%.4f)"), LPxtoFPx(point.x), LPytoFPy(point.y));
	AfxMessageBox(msg);
	CView::OnLButtonDblClk(nFlags, point);
}
