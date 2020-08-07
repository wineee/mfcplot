#pragma once


// CNormalFuncDlg 对话框

class CNormalFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNormalFuncDlg)

public:
	CNormalFuncDlg(int Xmin,int Xmax, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNormalFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NORMALFUNC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sEquation;
	double m_Xmin;
	double m_Xmax;
	int m_stepX;
	COLORREF m_color;
	afx_msg void OnBnClickedButtonSetfunc();
	afx_msg void OnBnClickedButtonColor();
	int m_penWidth;
	int m_penType;
};
