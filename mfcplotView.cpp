
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
#include "CFuncDlg.h"

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
	ON_COMMAND(ID_NORMAL_FUNC_MENU, &CmfcplotView::OnNormalFuncMenu)
	//ON_COMMAND(ID_BIGGER_MENU, &CmfcplotView::OnBiggerMenu)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_MOVE_MENU, &CmfcplotView::OnMoveMenu)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	CRect rect;
	GetClientRect(&rect);
	nTop = static_cast<int>(rect.bottom * 0.1);
	nButton = static_cast<int>(rect.bottom * 0.9);
	nLeft = static_cast<int>(rect.right * 0.1);
	nRight = static_cast<int>(rect.right * 0.9);
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
	return nLeft + static_cast<int>((x - m_Xmin) * (1.0 * nRight - nLeft) / (m_Xmax - m_Xmin));
}

double CmfcplotView::LPytoFPy(int y) {
	return m_Ymin + (1.0 * nButton - y) * (m_Ymax - m_Ymin) / (1.0 * nButton - nTop);
}

int CmfcplotView::FPytoLPy(double y) {
	return nButton - static_cast<int>((y - m_Ymin) * (1.0 * nButton - nTop) / (m_Ymax - m_Ymin));
}

// CmfcplotView 绘图

void CmfcplotView::OnDraw(CDC* pDC)
{
	CmfcplotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_Xmin = pDoc->m_Xmin;
	m_Xmax = pDoc->m_Xmax;
	m_Ymin = pDoc->m_Ymin;
	m_Ymax = pDoc->m_Ymax;
	// TODO: 在此处为本机数据添加绘制代码
	//CClientDC dc(this);
	
//	pDC->SetMapMode(MM_LOMETRIC);     //设置映射模式；	
	//pDC->SetWindowOrg(0, 0);               //设置屏幕窗口原点；
	CRect rect;
	GetClientRect(&rect);
	nTop = static_cast<int>(rect.bottom * 0.1);
	nButton = static_cast<int>(rect.bottom * 0.9);
	nLeft = static_cast<int>(rect.right * 0.1);
	nRight = static_cast<int>(rect.right * 0.9);
	pDC->MoveTo(nLeft, nTop);
	pDC->LineTo(nLeft, nButton);
	pDC->LineTo(nRight,nButton);
	pDC->LineTo(nRight,nTop);
	pDC->LineTo(nLeft, nTop);

	//double m_Xmin = 0, m_Xmax = 10, m_Ymin = 0, m_Ymax = 10;

	//x坐标
	int nX,nY;
	for (nX = nLeft; nX < nRight; nX += 50) {
		//pDC->TextOutW(nX-2, nButton+3, _T("11"));
		CRect textRect(nX - 25, nButton + 1, nX + 25, nButton + 20);
		CString xInfo;
		xInfo.Format(_T("%.2f"),LPxtoFPx(nX));
		pDC->DrawText(xInfo, &textRect, DT_SINGLELINE | DT_CENTER);
		                                    //单行,上下左右居中
	}
	if (nX-nRight <= 25) {
		CRect textRect(nRight, nButton + 1, nRight + 50, nButton + 20);
		CString xInfo;
		xInfo.Format(_T("%.2f"), LPxtoFPx(nRight));
		pDC->DrawText(xInfo, &textRect, DT_SINGLELINE | DT_LEFT);
	}

	//y坐标
	for (nY = nButton - 50; nY > nTop; nY -= 50) {
		CRect textRect(nLeft - 50, nY-10, nLeft - 1, nY + 10);
		CString yInfo;
		yInfo.Format(_T("%.2f"), LPytoFPy(nY));
		pDC->DrawText(yInfo, &textRect, DT_SINGLELINE | DT_CENTER);
	}
	if (nTop - nY <= 25) {
		CRect textRect(nLeft - 50, nTop - 10, nLeft - 1, nTop + 10);
		CString yInfo;
		yInfo.Format(_T("%.2f"), LPytoFPy(nY));
		pDC->DrawText(yInfo, &textRect, DT_SINGLELINE | DT_BOTTOM);
	}


	//  显示网格
	if (pDoc->m_WillShowGrid) {
		CPen pen1(PS_DOT, 1, RGB(100, 100, 100));           //创建笔，并调整坐标颜色
		CPen *pOldPen = (CPen *)pDC->SelectObject(&pen1);
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
		CPen pen2(PS_SOLID, 2, RGB(0, 0, 0));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen2);
		int oX = FPxtoLPx(0);
		int oY = FPytoLPy(0);
		bool showY = oX >= nLeft && oX <= nRight;
		bool showX = oY >= nTop && oY <= nButton;
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
		//pDC->Polygon(1,1,1,1,1,1);
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

	
	for (double i = -10; i <= 10; i += 0.1) {
		if (i == -10) pDC->MoveTo(FPxtoLPx(i), FPytoLPy(sin(i)));
		else pDC->LineTo(FPxtoLPx(i), FPytoLPy(sin(i)));
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


//void CmfcplotView::OnNcMouseMove(UINT nHitTest, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CView::OnNcMouseMove(nHitTest, point);
//}


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
		//	m_cursor = LoadCursor(NULL, IDC_SIZEALL);
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
		//绘制坐标轴
	
		this->OnDraw(&MemDC);
		//将内存中画好的图像直接拷贝到屏幕指定区域上
		pDC->BitBlt(rect.left, rect.top, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);

		//释放相关资源
		ReleaseDC(pDC);

	}
	else if (isMoving == 1) {
		::SetCursor(LoadCursor(NULL, IDC_HAND));
	}

	CView::OnMouseMove(nFlags, point);
}


void CmfcplotView::OnNormalFuncMenu()
{
	// TODO: 在此添加命令处理程序代码
	CFuncDlg dlg;
	if (dlg.DoModal() == IDOK) {

	}
}


//void CmfcplotView::OnBiggerMenu()
//{
//	// TODO: 在此添加命令处理程序代码
//	CmfcplotDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;

//	RedrawWindow();
//}




BOOL CmfcplotView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (isMoving) {
//		SetCursor(m_cursor);
//		return TRUE;
	//}
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
	CView::OnLButtonUp(nFlags, point);
}
