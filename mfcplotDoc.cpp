
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
END_MESSAGE_MAP()


// CmfcplotDoc 构造/析构

CmfcplotDoc::CmfcplotDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_WillShowGrid = true;
	m_WillShowAxis = true;
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
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
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


void CmfcplotDoc::OnNormalFuncMenu()
{
	// TODO: 在此添加命令处理程序代码
	CFuncDlg dlg;
	if (dlg.DoModal() == IDOK) 
	{
		if (m_FD) delete m_FD;
		m_FD = new NormalFD(dlg.m_strEquation,m_Xmin,m_Xmax,1000);
		if (m_FD->CalcList() == false) {
			AfxMessageBox(_T("请检查方程是否完整！"));
		}
		else {
			if (m_FD->minY < m_Ymin) m_Ymin = m_FD->minY;
			if (m_FD->maxY > m_Ymax) m_Ymax = m_FD->maxY;
		}
	}
	UpdateAllViews(NULL);
}
