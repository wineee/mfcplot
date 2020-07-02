#pragma once


// CTwoFuncDlg 对话框

class CTwoFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTwoFuncDlg)

public:
	CTwoFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTwoFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TWOFUNC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sEquationX;
	CString m_sEquationY;
	double m_Tmin;
	double m_Tmax;
	int m_stepT;
	int m_penType;
	COLORREF m_color;
	afx_msg void OnBnClickedButtonSetfunc();
	afx_msg void OnBnClickedButtonSetfunc2();
	afx_msg void OnBnClickedButtonColor();
	int m_penWidth;
};
