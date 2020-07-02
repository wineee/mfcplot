// CPolarFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CPolarFuncDlg.h"
#include "afxdialogex.h"


// CPolarFuncDlg 对话框

IMPLEMENT_DYNAMIC(CPolarFuncDlg, CDialogEx)

CPolarFuncDlg::CPolarFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_POLARFUNC, pParent)
	, m_sEquation(_T(""))
	, m_Thetamin(-3.14)
	, m_Thetamax(3.14)
	, m_StepTheta(1000)
	, m_penWidth(1)
	, m_penType(0)
{
	m_color = RGB(0, 0, 0);
}

CPolarFuncDlg::~CPolarFuncDlg()
{
}

void CPolarFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FUNC, m_sEquation);
	DDX_Text(pDX, IDC_EDIT2, m_Thetamin);
	DDX_Text(pDX, IDC_EDIT3, m_Thetamax);
	DDX_Text(pDX, IDC_EDIT4, m_StepTheta);
	DDX_Text(pDX, IDC_EDIT1, m_penWidth);
	DDX_CBIndex(pDX, IDC_COMBO_LINETYPE, m_penType);
}


BEGIN_MESSAGE_MAP(CPolarFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CPolarFuncDlg::OnBnClickedButtonColor)
END_MESSAGE_MAP()


// CPolarFuncDlg 消息处理程序


void CPolarFuncDlg::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_color = dlg.GetColor();
	}
}
