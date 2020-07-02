#pragma once
#include <vector>
using std::vector;

// CDataFuncDlg 对话框

class CDataFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataFuncDlg)

public:
	CDataFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDataFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATAFUNC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_penWidth;
	int m_penType;
	COLORREF m_color;
	vector<double> vetX, vetY;
	afx_msg void OnBnClickedButtonColor();
	afx_msg void OnBnClickedButtonReaddata();
};
