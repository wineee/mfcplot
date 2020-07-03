// CTwoFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CTwoFuncDlg.h"
#include "afxdialogex.h"
#include "CFuncDlg.h"


// CTwoFuncDlg 对话框

IMPLEMENT_DYNAMIC(CTwoFuncDlg, CDialogEx)

CTwoFuncDlg::CTwoFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TWOFUNC, pParent)
	, m_sEquationX(_T(""))
	, m_sEquationY(_T(""))
	, m_Tmin(0)
	, m_Tmax(10)
	, m_stepT(1000)
	, m_penWidth(1)
{
	m_color = RGB(0, 0, 0);
}

CTwoFuncDlg::~CTwoFuncDlg()
{
}

void CTwoFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FUNC, m_sEquationX);
	DDX_Text(pDX, IDC_EDIT_FUNC2, m_sEquationY);
	DDX_Text(pDX, IDC_EDIT2, m_Tmin);
	DDX_Text(pDX, IDC_EDIT3, m_Tmax);
	DDX_Text(pDX, IDC_EDIT4, m_stepT);
	DDX_CBIndex(pDX, IDC_COMBO_LINETYPE, m_penType);
	DDX_Text(pDX, IDC_EDIT1, m_penWidth);
}


BEGIN_MESSAGE_MAP(CTwoFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SETFUNC, &CTwoFuncDlg::OnBnClickedButtonSetfunc)
	ON_BN_CLICKED(IDC_BUTTON_SETFUNC2, &CTwoFuncDlg::OnBnClickedButtonSetfunc2)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CTwoFuncDlg::OnBnClickedButtonColor)
END_MESSAGE_MAP()


// CTwoFuncDlg 消息处理程序


void CTwoFuncDlg::OnBnClickedButtonSetfunc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CFuncDlg dlg(1);
	if (dlg.DoModal() == IDOK) {
		m_sEquationX = dlg.m_strEquation;
	}
	UpdateData(false);

}


void CTwoFuncDlg::OnBnClickedButtonSetfunc2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CFuncDlg dlg(1);
	if (dlg.DoModal() == IDOK) {
		m_sEquationY = dlg.m_strEquation;
	}
	UpdateData(false);
}



void CTwoFuncDlg::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_color = dlg.GetColor();
	}
}
