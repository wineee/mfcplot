
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
	bool m_WillShowGrid; //是否显示网格
	bool m_WillShowAxis; //是否显示坐标轴
	bool m_WillShowEdge; //是否显示边框
	bool m_SingelMode;   //单函数模式添加函数自动删除上一个函数
	bool m_ForceXrange;	 //普通函数x范围是否固定，不固定的话随显示范围变化
	bool m_ShowNearPoint;//鼠标接近函数线时是否显示其坐标
	double m_Xmin, m_Xmax, m_Ymin, m_Ymax;//显示范围
	FuncData* m_FD;//临时变量
	CObList m_List;//记录所有函数信息
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
	afx_msg void OnAxisMenu();//坐标轴
	afx_msg void OnGridMenu();//网格
	afx_msg void OnEdgeMenu();//边框
	afx_msg void OnSmallerMenu();//显示范围缩小 0.8
	afx_msg void OnBiggerMenu();//显示范围放大 1.25
	afx_msg void OnNormalFuncMenu();//增加普通函数
	afx_msg void OnMenuSetXyrange();//设置显示范围
	afx_msg void OnFuncMode();//单/多函数模式
	afx_msg void OnPolarFuncMenu();//增加极坐标函数
	afx_msg void OnTwoFuncMenu();//增加参数方程函数
	afx_msg void OnDataFuncMenu();//增加数据点型函数
	afx_msg void OnFroceXrang();//普通函数x范围是否固定
	afx_msg void OnNearpointMenu();//是否显示最近点
	afx_msg void OnAutorangeMenu();//自动调整显示范围，正好显示完整函数图像
	afx_msg void OnDelfunconeMenu();//删除一个函数
	afx_msg void OnDelallMenu();//删除所有函数
	afx_msg void OnUpdateEdgeMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFuncMode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAxisMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGridMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFroceXrang(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNearpointMenu(CCmdUI* pCmdUI);
};
