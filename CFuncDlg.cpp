// CFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CFuncDlg.h"
#include "afxdialogex.h"


// CFuncDlg 对话框

IMPLEMENT_DYNAMIC(CFuncDlg, CDialogEx)

CFuncDlg::CFuncDlg(int cas, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NORMALFUNC_DIALOG, pParent)
	, m_strEquation(_T(""))
{
	m_cas = cas;	
}

CFuncDlg::~CFuncDlg()
{
}

void CFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EQUATION_EDIT, m_strEquation);
}


BEGIN_MESSAGE_MAP(CFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_1, &CFuncDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CFuncDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CFuncDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CFuncDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CFuncDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CFuncDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CFuncDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CFuncDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CFuncDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_PI, &CFuncDlg::OnBnClickedButtonPi)
	ON_BN_CLICKED(IDC_BUTTON_10, &CFuncDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON_E, &CFuncDlg::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CFuncDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CFuncDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CFuncDlg::OnBnClickedButtonDec)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CFuncDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CFuncDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON_SIN, &CFuncDlg::OnBnClickedButtonSin)
	ON_BN_CLICKED(IDC_BUTTON_COS, &CFuncDlg::OnBnClickedButtonCos)
	ON_BN_CLICKED(IDC_BUTTON_TAN, &CFuncDlg::OnBnClickedButtonTan)
	ON_BN_CLICKED(IDC_BUTTON_LOG, &CFuncDlg::OnBnClickedButtonLog)
	ON_BN_CLICKED(IDC_BUTTON_POW, &CFuncDlg::OnBnClickedButtonPow)
	ON_BN_CLICKED(IDC_BUTTON_2POW, &CFuncDlg::OnBnClickedButton2pow)
	ON_BN_CLICKED(IDC_BUTTON_SQRT, &CFuncDlg::OnBnClickedButtonSqrt)
	ON_BN_CLICKED(IDC_BUTTON_LN, &CFuncDlg::OnBnClickedButtonLn)
	ON_BN_CLICKED(IDC_BUTTON_ABS, &CFuncDlg::OnBnClickedButtonAbs)
	ON_BN_CLICKED(IDC_BUTTON_X, &CFuncDlg::OnBnClickedButtonX)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CFuncDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CFuncDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CFuncDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CFuncDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_FLOOR, &CFuncDlg::OnBnClickedButtonFloor)
	ON_BN_CLICKED(IDC_BUTTON_CEILING, &CFuncDlg::OnBnClickedButtonCeiling)
	ON_BN_CLICKED(IDC_BUTTON_ROUND, &CFuncDlg::OnBnClickedButtonRound)
	ON_BN_CLICKED(IDC_BUTTON_CUBIC, &CFuncDlg::OnBnClickedButtonCubic)
END_MESSAGE_MAP()


// CFuncDlg 消息处理程序


void CFuncDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "1";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "2";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "3";
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "4";
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "5";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "6";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "7";
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "8";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "9";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonPi()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "p";
	UpdateData(false);
}




void CFuncDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "0";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonE()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "e";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "+";
	UpdateData(false);
}




void CFuncDlg::OnBnClickedButtonDot()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += ".";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonDec()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "-";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonMul()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "*";
	UpdateData(false);
}





void CFuncDlg::OnBnClickedButtonDiv()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "/";
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButtonSin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "sin(";
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButtonCos()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "cos(";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonTan()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "tan(";
	UpdateData(false);
}




void CFuncDlg::OnBnClickedButtonLog()  //以10为底
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "lg(";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonPow()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "^";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButton2pow()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "^2";
	UpdateData(false);
}




void CFuncDlg::OnBnClickedButtonSqrt()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "sqrt(";
	UpdateData(false);
}




void CFuncDlg::OnBnClickedButtonLn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "ln(";
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButtonAbs()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "abs(";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonX()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_cas == 0) m_strEquation += "x";
	else m_strEquation += 't';
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation = "";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	int T = m_strEquation.GetLength();
	if (T > 0)
		m_strEquation = m_strEquation.Left(T - 1);
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "(";
	UpdateData(false);
}




void CFuncDlg::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += ")";
	UpdateData(false);
}



void CFuncDlg::OnBnClickedButtonFloor()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "floor(";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonCeiling()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "ceil(";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonRound()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "round(";
	UpdateData(false);
}


void CFuncDlg::OnBnClickedButtonCubic()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_strEquation += "^3";
	UpdateData(false);
}
