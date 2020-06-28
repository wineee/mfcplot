
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
	afx_msg void OnNormalFuncMenu();
};

#ifndef _DEBUG  // mfcplotView.cpp 中的调试版本
inline CmfcplotDoc* CmfcplotView::GetDocument() const
   { return reinterpret_cast<CmfcplotDoc*>(m_pDocument); }
#endif

