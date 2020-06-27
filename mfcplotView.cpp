
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
	pDC->MoveTo(1, 1);
	for (int i = 1; i <= 1000; i+=1)
		pDC->LineTo(i,i);
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
