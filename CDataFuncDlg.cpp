// CDataFuncDlg.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "CDataFuncDlg.h"
#include "afxdialogex.h"


// CDataFuncDlg 对话框

IMPLEMENT_DYNAMIC(CDataFuncDlg, CDialogEx)

CDataFuncDlg::CDataFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DATAFUNC, pParent)
	, m_penWidth(1)
	, m_penType(0)
{
	m_color = RGB(0, 0, 0);
}

CDataFuncDlg::~CDataFuncDlg()
{
}

void CDataFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_penWidth);
	DDX_CBIndex(pDX, IDC_COMBO_LINETYPE, m_penType);
}


BEGIN_MESSAGE_MAP(CDataFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CDataFuncDlg::OnBnClickedButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_READDATA, &CDataFuncDlg::OnBnClickedButtonReaddata)
END_MESSAGE_MAP()


// CDataFuncDlg 消息处理程序


void CDataFuncDlg::OnBnClickedButtonColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		m_color = dlg.GetColor();
	}
}


void CDataFuncDlg::OnBnClickedButtonReaddata()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;
	filter = "文本文档(*.txt)|*.txt||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	if (dlg.DoModal() == IDOK)
	{
		CStdioFile file;
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CString tmp;
		file.ReadString(tmp);
		int cnt = _ttoi(tmp);
		for (int i = 0; i < cnt; i++) {
			file.ReadString(tmp);
			int tmpx = _ttoi(tmp);
			vetX.emplace_back(tmpx);
			file.ReadString(tmp);
			int tmpy = _ttoi(tmp);
			vetY.emplace_back(tmpy);
		}
	}

}
