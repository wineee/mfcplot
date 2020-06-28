// CFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CFuncDlg.h"
#include "afxdialogex.h"


// CFuncDlg 对话框

IMPLEMENT_DYNAMIC(CFuncDlg, CDialogEx)

CFuncDlg::CFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NORMALFUNC_DIALOG, pParent)
{

}

CFuncDlg::~CFuncDlg()
{
}

void CFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFuncDlg, CDialogEx)
END_MESSAGE_MAP()


// CFuncDlg 消息处理程序
