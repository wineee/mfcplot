// CSetXYrangeDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CSetXYrangeDlg.h"
#include "afxdialogex.h"


// CSetXYrangeDlg 对话框

IMPLEMENT_DYNAMIC(CSetXYrangeDlg, CDialogEx)

CSetXYrangeDlg::CSetXYrangeDlg(double Xmin, double Xmax, double Ymin, double Ymax, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SET_RANGE, pParent)
	, m_Xmin(Xmin)
	, m_Xmax(Xmax)
	, m_Ymin(Ymin)
	, m_Ymax(Ymax)
{

}

CSetXYrangeDlg::~CSetXYrangeDlg()
{
}

void CSetXYrangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, m_Xmin);
	DDX_Text(pDX, IDC_EDIT1, m_Xmax);
	DDX_Text(pDX, IDC_EDIT6, m_Ymin);
	DDX_Text(pDX, IDC_EDIT7, m_Ymax);
}


BEGIN_MESSAGE_MAP(CSetXYrangeDlg, CDialogEx)
END_MESSAGE_MAP()


// CSetXYrangeDlg 消息处理程序
