
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
END_MESSAGE_MAP()

// CmfcplotView 构造/析构

CmfcplotView::CmfcplotView() noexcept
{
	// TODO: 在此处添加构造代码

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

// CmfcplotView 绘图

void CmfcplotView::OnDraw(CDC* pDC)
{
	CmfcplotDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	//CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_LOMETRIC);     //设置映射模式；	
	pDC->SetWindowOrg(0, 0);               //设置屏幕窗口原点；
	pDC->SetViewportOrg(CPoint(rect.right / 2, rect.bottom / 2));  //设置视口原点
	
	CPen pen1(PS_DOT, 1, RGB(100, 100, 100));           //创建笔，并调整坐标颜色
	CPen* pOldPen = pDC->SelectObject(&pen1);           //更改笔并保存旧的笔

	pDC->MoveTo(0, 0);
//	pDC->LineTo(100, );

/*	for (int i = -900; i <= 900; i += 50)
	{
		pDC->MoveTo(i, 500);
		pDC->LineTo(i, -500);
	}
	for (int j = -500; j <= 500; j += 50)
	{
		pDC->MoveTo(-900, j);
		pDC->LineTo(900, j);
	}
	//pDC->TextOutW()
	pDC->TextOutW(10, 500, _T("y"));     //标记y轴
	pDC->TextOutW(870, 0, _T("x"));      //标记x轴
	pDC->TextOutW(0, 0, _T("0"));        //标记坐标原点
	pDC->TextOutW(-8, 510, _T("^"));
	pDC->TextOutW(900, 25, _T(">"));
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));//创建笔，并调整坐标颜色
	pOldPen = pDC->SelectObject(&pen);//更改笔并保存旧的笔
	pDC->MoveTo(-900, 0);    //横坐标
	pDC->LineTo(900, 0);
	pDC->MoveTo(0, -500);    //纵坐标
	pDC->LineTo(0, 500);*/
	
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
		msg.Format(_T("(%d,%d)"), point.x, point.y);
		pBar->SetPaneText(1, msg);
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
