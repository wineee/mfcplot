// CSetXYrangeDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CSetXYrangeDlg.h"
#include "afxdialogex.h"


// CSetXYrangeDlg 对话框

IMPLEMENT_DYNAMIC(CSetXYrangeDlg, CDialogEx)

CSetXYrangeDlg::CSetXYrangeDlg(int Xmin, int Xmax, int Ymin, int Ymax, CWnd* pParent /*=nullptr*/)
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
//	ON_EN_CHANGE(IDC_EDIT1, &CSetXYrangeDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CSetXYrangeDlg 消息处理程序


//void CSetXYrangeDlg::OnEnChangeEdit1()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
