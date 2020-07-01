
// mfcplotView.h: CmfcplotView 类的接口
//

#pragma once


class CmfcplotView : public CView
{
protected: // 仅从序列化创建
	CmfcplotView() noexcept;
	DECLARE_DYNCREATE(CmfcplotView)

// 特性
public:
	CmfcplotDoc* GetDocument() const;

// 操作
public:
	double m_Xmin, m_Xmax, m_Ymin, m_Ymax;
	int nTop, nButton, nLeft, nRight;
	//HCURSOR m_cursor;
	int isMoving;//0不拖动 1拖动模式 2正在拖动

	double  tmp_Xmin, tmp_Xmax, tmp_Ymin, tmp_Ymax;
	CPoint m_posStart;

	double LPxtoFPx(int x);
	int FPxtoLPx(double x);
	double LPytoFPy(int y);
	int FPytoLPy(double y); 

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CmfcplotView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnNormalFuncMenu();
//	afx_msg void OnBiggerMenu();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMoveMenu();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // mfcplotView.cpp 中的调试版本
inline CmfcplotDoc* CmfcplotView::GetDocument() const
   { return reinterpret_cast<CmfcplotDoc*>(m_pDocument); }
#endif

