// CNormalFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CNormalFuncDlg.h"
#include "afxdialogex.h"
#include "CFuncDlg.h"


// CNormalFuncDlg 对话框

IMPLEMENT_DYNAMIC(CNormalFuncDlg, CDialogEx)

CNormalFuncDlg::CNormalFuncDlg(int Xmin, int Xmax, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NORMALFUNC, pParent)
	, m_sEquation(_T(""))
	, m_Xmin(Xmin)
	, m_Xmax(Xmax)
	, m_stepX(1000)
	, m_penWidth(1)
	, m_penType(0)
{
	m_color = RGB(0, 0, 0);
	m_penType = PS_SOLID;
}

CNormalFuncDlg::~CNormalFuncDlg()
{
}

void CNormalFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FUNC, m_sEquation);
	DDX_Text(pDX, IDC_EDIT2, m_Xmin);
	DDX_Text(pDX, IDC_EDIT3, m_Xmax);
	DDX_Text(pDX, IDC_EDIT4, m_stepX);
	DDX_Text(pDX, IDC_EDIT1, m_penWidth);
	DDX_CBIndex(pDX, IDC_COMBO_LINETYPE, m_penType);
}


BEGIN_MESSAGE_MAP(CNormalFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SETFUNC, &CNormalFuncDlg::OnBnClickedButtonSetfunc)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CNormalFuncDlg::OnBnClickedButtonColor)
END_MESSAGE_MAP()


// CNormalFuncDlg 消息处理程序


void CNormalFuncDlg::OnBnClickedButtonSetfunc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CFuncDlg dlg;
	if (dlg.DoModal() == IDOK) {
		m_sEquation = dlg.m_strEquation;
	}
	UpdateData(false);
}


void CNormalFuncDlg::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_color = dlg.GetColor();
	}
}
