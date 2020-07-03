// CDelFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CDelFuncDlg.h"
#include "afxdialogex.h"


// CDelFuncDlg 对话框

IMPLEMENT_DYNAMIC(CDelFuncDlg, CDialogEx)

CDelFuncDlg::CDelFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEL, pParent)
	, m_id(0)
{

}

CDelFuncDlg::~CDelFuncDlg()
{
}

void CDelFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
}


BEGIN_MESSAGE_MAP(CDelFuncDlg, CDialogEx)
END_MESSAGE_MAP()


// CDelFuncDlg 消息处理程序
