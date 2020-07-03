
// mfcplotDoc.cpp: CmfcplotDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mfcplot.h"
#endif

#include "mfcplotDoc.h"
#include <utility>
#include <propkey.h>
#include "CFuncDlg.h"
#include "CNormalFuncDlg.h"
#include "CPolarFuncDlg.h"
#include "CSetXYrangeDlg.h"
#include "CTwoFuncDlg.h"
#include "CDataFuncDlg.h"
#include "CDelFuncDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CmfcplotDoc

IMPLEMENT_DYNCREATE(CmfcplotDoc, CDocument)

BEGIN_MESSAGE_MAP(CmfcplotDoc, CDocument)
	ON_COMMAND(ID_AXIS_MENU, &CmfcplotDoc::OnAxisMenu)
	//ON_COMMAND(ID_GRID_MENU, &CmfcplotDoc::OnGridMenu)
	//ON_UPDATE_COMMAND_UI(ID_GRID_MENU, &CmfcplotDoc::OnUpdateGridMenu)
	ON_COMMAND(ID_GRID_MENU, &CmfcplotDoc::OnGridMenu)
	ON_COMMAND(ID_SMALLER_MENU, &CmfcplotDoc::OnSmallerMenu)
	ON_COMMAND(ID_BIGGER_MENU, &CmfcplotDoc::OnBiggerMenu)
	ON_COMMAND(ID_NORMAL_FUNC_MENU, &CmfcplotDoc::OnNormalFuncMenu)
	ON_UPDATE_COMMAND_UI(ID_EDGE_MENU, &CmfcplotDoc::OnUpdateEdgeMenu)
	ON_COMMAND(ID_EDGE_MENU, &CmfcplotDoc::OnEdgeMenu)
	ON_COMMAND(ID_Menu_SET_XYRANGE, &CmfcplotDoc::OnMenuSetXyrange)
	ON_COMMAND(ID_FUNC_MODE, &CmfcplotDoc::OnFuncMode)
	ON_UPDATE_COMMAND_UI(ID_FUNC_MODE, &CmfcplotDoc::OnUpdateFuncMode)
	ON_UPDATE_COMMAND_UI(ID_AXIS_MENU, &CmfcplotDoc::OnUpdateAxisMenu)
	ON_UPDATE_COMMAND_UI(ID_GRID_MENU, &CmfcplotDoc::OnUpdateGridMenu)
	//ON_COMMAND(ID_MOVE_MENU, &CmfcplotDoc::OnMoveMenu)
	//ON_UPDATE_COMMAND_UI(ID_MOVE_MENU, &CmfcplotDoc::OnUpdateMoveMenu)
	ON_COMMAND(ID_POLAR_FUNC_MENU, &CmfcplotDoc::OnPolarFuncMenu)
	ON_COMMAND(ID_TWO_FUNC_MENU, &CmfcplotDoc::OnTwoFuncMenu)
	ON_COMMAND(ID_DATA_FUNC_MENU, &CmfcplotDoc::OnDataFuncMenu)
	ON_COMMAND(ID_FROCE_XRANG, &CmfcplotDoc::OnFroceXrang)
	ON_UPDATE_COMMAND_UI(ID_FROCE_XRANG, &CmfcplotDoc::OnUpdateFroceXrang)
	ON_COMMAND(ID_DELALL_MENU, &CmfcplotDoc::OnDelallMenu)
	ON_COMMAND(ID_NEARPOINT_MENU, &CmfcplotDoc::OnNearpointMenu)
	ON_UPDATE_COMMAND_UI(ID_NEARPOINT_MENU, &CmfcplotDoc::OnUpdateNearpointMenu)
	ON_COMMAND(ID_AUTORANGE_MENU, &CmfcplotDoc::OnAutorangeMenu)
	ON_COMMAND(ID_DELFUNCONE_MENU, &CmfcplotDoc::OnDelfunconeMenu)
END_MESSAGE_MAP()


// CmfcplotDoc 构造/析构

CmfcplotDoc::CmfcplotDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_WillShowGrid = true;
	m_WillShowAxis = true;
	m_WillShowEdge = true;
	m_SingelMode = true;
	m_ForceXrange = false;
	m_ShowNearPoint = false;
	m_Xmin = -10;
	m_Xmax = 10;
	m_Ymin = -1;
	m_Ymax = 1;
	//int nTop, nButton, nLeft, nRight;

}

CmfcplotDoc::~CmfcplotDoc()
{
}

BOOL CmfcplotDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CmfcplotDoc 序列化

void CmfcplotDoc::Serialize(CArchive& ar)
{
	m_List.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		ar <<  m_WillShowGrid << m_WillShowAxis << m_WillShowEdge << m_SingelMode << m_ForceXrange << m_ShowNearPoint \
			<< m_Xmin << m_Xmax << m_Ymin << m_Ymax;
	}
	else
	{
		// TODO:  在此添加加载代码
		ar >> m_WillShowGrid >> m_WillShowAxis >> m_WillShowEdge >> m_SingelMode >> m_ForceXrange >> m_ShowNearPoint \
			>> m_Xmin >> m_Xmax >> m_Ymin >> m_Ymax;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CmfcplotDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CmfcplotDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CmfcplotDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CmfcplotDoc 诊断

#ifdef _DEBUG
void CmfcplotDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CmfcplotDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CmfcplotDoc 命令


void CmfcplotDoc::OnAxisMenu()
{
	// TODO: 在此添加命令处理程序代码
	m_WillShowAxis = !m_WillShowAxis;
	
	this->UpdateAllViews(NULL);
}

void CmfcplotDoc::OnGridMenu()
{
	// TODO: 在此添加命令处理程序代码
	m_WillShowGrid = !m_WillShowGrid;
	this->UpdateAllViews(NULL);
}



void CmfcplotDoc::OnSmallerMenu()
{
	// TODO: 在此添加命令处理程序代码
	double detx = (m_Xmax - m_Xmin) * 0.125;
	m_Xmax += detx;
	m_Xmin -= detx;
	double dety = (m_Ymax - m_Ymin) * 0.125;
	m_Ymax += dety;
	m_Ymin -= dety;
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnBiggerMenu()
{
	// TODO: 在此添加命令处理程序代码
    double detx = (m_Xmax - m_Xmin) * 0.1;
	m_Xmax -= detx;
	m_Xmin += detx;
	double dety = (m_Ymax - m_Ymin) * 0.1;
	m_Ymax -= dety;
	m_Ymin += dety;
	UpdateAllViews(NULL);
}



void CmfcplotDoc::OnUpdateEdgeMenu(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_WillShowEdge);
	
}


void CmfcplotDoc::OnEdgeMenu()
{
	// TODO: 在此添加命令处理程序代码
	m_WillShowEdge = !m_WillShowEdge;
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnMenuSetXyrange()
{
	// TODO: 在此添加命令处理程序代码
	CSetXYrangeDlg dlg(m_Xmin, m_Xmax, m_Ymin, m_Ymax, nullptr);
	if (dlg.DoModal()) {
		if (dlg.m_Xmin >= dlg.m_Xmax || dlg.m_Ymin >= dlg.m_Ymax)
			AfxMessageBox(_T("输入不合法！"));
		else {
			m_Xmin = dlg.m_Xmin;
			m_Xmax = dlg.m_Xmax;
			m_Ymin = dlg.m_Ymin;
			m_Ymax = dlg.m_Ymax;
			UpdateAllViews(NULL);
		}
	}
}


void CmfcplotDoc::OnFuncMode()
{
	// TODO: 在此添加命令处理程序代码
	m_SingelMode = !m_SingelMode;
	if (m_SingelMode == true) {
		this->OnDelallMenu();
	}
}


void CmfcplotDoc::OnUpdateFuncMode(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_SingelMode);
}


void CmfcplotDoc::OnUpdateAxisMenu(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_WillShowAxis);
}


void CmfcplotDoc::OnUpdateGridMenu(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_WillShowGrid);
}

void CmfcplotDoc::OnNormalFuncMenu()
{
	// TODO: 在此添加命令处理程序代码
	//CFuncDlg dlg;
	CNormalFuncDlg dlg(m_Xmin, m_Xmax, nullptr);
	//	
	if (dlg.DoModal() == IDOK)
	{
		if (m_SingelMode) {
			if (m_FD) delete m_FD;
			m_List.RemoveAll();
		}
		m_FD = new NormalFD(dlg.m_sEquation, dlg.m_Xmin, dlg.m_Xmax, dlg.m_stepX, dlg.m_color, dlg.m_penWidth, dlg.m_penType);
		if (m_FD->CalcList() == false) {
			AfxMessageBox(_T("请检查方程是否完整！"));
		}
		else {
			if (m_FD->minY < m_Ymin) m_Ymin = m_FD->minY;
			if (m_FD->maxY > m_Ymax) m_Ymax = m_FD->maxY;
			m_List.AddTail(m_FD);
		}

	}
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnPolarFuncMenu()
{
	// TODO: 在此添加命令处理程序代码
	CPolarFuncDlg  dlg;
	//	
	if (dlg.DoModal() == IDOK)
	{
		if (m_SingelMode) {
			if (m_FD) delete m_FD;
			m_List.RemoveAll();
		}
		m_FD = new PolarFD(dlg.m_sEquation, dlg.m_Thetamin, dlg.m_Thetamax, dlg.m_StepTheta, dlg.m_color, dlg.m_penWidth, dlg.m_penType);
		if (m_FD->CalcList() == false) {
			AfxMessageBox(_T("请检查方程是否完整！"));
		}
		else {
			if (m_FD->minY < m_Ymin) m_Ymin = m_FD->minY;
			if (m_FD->maxY > m_Ymax) m_Ymax = m_FD->maxY;
			if (m_FD->minX < m_Xmin) m_Xmin = m_FD->minX;
			if (m_FD->maxX > m_Xmax) m_Xmax = m_FD->maxX;
			m_List.AddTail(m_FD);
		}

	}
	UpdateAllViews(NULL);

}


void CmfcplotDoc::OnTwoFuncMenu()
{
	// TODO: 在此添加命令处理程序代码
	CTwoFuncDlg  dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (m_SingelMode) {
			if (m_FD) delete m_FD;
			m_List.RemoveAll();
		}
		m_FD = new TwoFD(dlg.m_sEquationX, dlg.m_sEquationY, dlg.m_Tmin, dlg.m_Tmax, dlg.m_stepT, dlg.m_color, dlg.m_penWidth, dlg.m_penType);
		if (m_FD->CalcList() == false) {
			AfxMessageBox(_T("请检查方程是否完整！"));
		}
		else {
			if (m_FD->minY < m_Ymin) m_Ymin = m_FD->minY;
			if (m_FD->maxY > m_Ymax) m_Ymax = m_FD->maxY;
			if (m_FD->minX < m_Xmin) m_Xmin = m_FD->minX;
			if (m_FD->maxX > m_Xmax) m_Xmax = m_FD->maxX;
			m_List.AddTail(m_FD);
		}
		
	}
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnDataFuncMenu()
{
	// TODO: 在此添加命令处理程序代码
	CDataFuncDlg dlg;
	if (dlg.DoModal()) {
		if (m_SingelMode) {
			if (m_FD) delete m_FD;
			m_List.RemoveAll();
		}
		m_FD = new DataFD(dlg.vetX, dlg.vetY, dlg.m_color, dlg.m_penWidth, dlg.m_penType);
		CString str;
		//str.Format("%d", dlg)
		if (m_FD->minY < m_Ymin) m_Ymin = m_FD->minY;
		if (m_FD->maxY > m_Ymax) m_Ymax = m_FD->maxY;
		if (m_FD->minX < m_Xmin) m_Xmin = m_FD->minX;
		if (m_FD->maxX > m_Xmax) m_Xmax = m_FD->maxX;
		m_List.AddTail(m_FD);
		//AfxMessageBox(m_FD->m_Equation);
	}
	
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnFroceXrang()
{
	// TODO: 在此添加命令处理程序代码
	m_ForceXrange = !m_ForceXrange;
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnUpdateFroceXrang(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ForceXrange);
}


void CmfcplotDoc::OnNearpointMenu()
{
	// TODO: 在此添加命令处理程序代码
	m_ShowNearPoint = !m_ShowNearPoint;
}


void CmfcplotDoc::OnUpdateNearpointMenu(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_ShowNearPoint);
}

void CmfcplotDoc::OnDelallMenu()
{
	// TODO: 在此添加命令处理程序代码
	POSITION p = m_List.GetHeadPosition();
	while (p != nullptr) {
		FuncData* tmpFD = (FuncData*)m_List.GetNext(p);
		delete tmpFD;
	}
	m_List.RemoveAll();
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnAutorangeMenu()
{
	// TODO: 在此添加命令处理程序代码
	double miX = -10, maX = 10, miY = -1, maY = 1;
	POSITION p = m_List.GetHeadPosition();
	bool flag = true;
	while (p) {
		FuncData* tmpFD = (FuncData*)m_List.GetNext(p);
		if (flag) {
			miY = tmpFD->minY;
			maY = tmpFD->maxY;
			miX = tmpFD->minX;
			maX = tmpFD->maxX;
			flag = false;
		}
		else {
			if (tmpFD->minY < miY) miY = tmpFD->minY;
			if (tmpFD->maxY > maY) maY = tmpFD->maxY;
			if (tmpFD->minX < miX) miX = tmpFD->minX;
			if (tmpFD->maxX > maX) maX = tmpFD->maxX;
		}
	}
	if (miX == maX) {
		miX -= 0.5;
		maX += 0.5;
	}
	if (miY == maY) {
		miY += 0.5;
		maY -= 0.5;
	}
	m_Xmin = miX;
	m_Xmax = maX;
	m_Ymin = miY;
	m_Ymax = maY;
	UpdateAllViews(NULL);
}


void CmfcplotDoc::OnDelfunconeMenu()
{
	// TODO: 在此添加命令处理程序代码
	int cnt = 0, id = 0;
	CDelFuncDlg dlg;
	if (dlg.DoModal()) {
		id = dlg.m_id;
	}
	POSITION p = m_List.GetHeadPosition(),tmpp;
	while (p) {
		tmpp = p;
		FuncData* tmpFD = (FuncData*)m_List.GetNext(p);
		cnt++;
		if (cnt == id) {
			delete tmpFD;
			m_List.RemoveAt(tmpp);
		}
	}
	UpdateAllViews(NULL);
}
