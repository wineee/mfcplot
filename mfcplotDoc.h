
// mfcplotDoc.h: CmfcplotDoc 类的接口
//

#include "FuncData.h"
#pragma once


class CmfcplotDoc : public CDocument
{
protected: // 仅从序列化创建
	CmfcplotDoc() noexcept;
	DECLARE_DYNCREATE(CmfcplotDoc)

// 特性
public:
	bool m_WillShowGrid;
	bool m_WillShowAxis;
	bool m_WillShowEdge;
	bool m_SingelMode;
	bool m_ForceXrange;
	bool m_ShowNearPoint;
	double m_Xmin, m_Xmax, m_Ymin, m_Ymax;
	//int nTop, nButton, nLeft, nRight;
	FuncData *m_FD;
	CObList m_List;
// 操作
public:
	
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CmfcplotDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnAxisMenu();
//	afx_msg void OnGridMenu();
//	afx_msg void OnUpdateGridMenu(CCmdUI* pCmdUI);
	afx_msg void OnGridMenu();
	afx_msg void OnSmallerMenu();
	afx_msg void OnBiggerMenu();
	afx_msg void OnNormalFuncMenu();
	afx_msg void OnUpdateEdgeMenu(CCmdUI* pCmdUI);
	afx_msg void OnEdgeMenu();
	afx_msg void OnMenuSetXyrange();
	afx_msg void OnFuncMode();
	afx_msg void OnUpdateFuncMode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAxisMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGridMenu(CCmdUI* pCmdUI);
//	afx_msg void OnMoveMenu();
//	afx_msg void OnUpdateMoveMenu(CCmdUI* pCmdUI);
	afx_msg void OnPolarFuncMenu();
	afx_msg void OnTwoFuncMenu();
	afx_msg void OnDataFuncMenu();
	afx_msg void OnFroceXrang();
	afx_msg void OnUpdateFroceXrang(CCmdUI* pCmdUI);
	afx_msg void OnDelallMenu();
	afx_msg void OnNearpointMenu();
	afx_msg void OnUpdateNearpointMenu(CCmdUI* pCmdUI);
	afx_msg void OnAutorangeMenu();
	afx_msg void OnDelfunconeMenu();
};
