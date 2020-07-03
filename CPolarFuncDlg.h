#pragma once


// CPolarFuncDlg 对话框

class CPolarFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPolarFuncDlg)

public:
	CPolarFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPolarFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POLARFUNC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sEquation;
	double m_Thetamin;
	double m_Thetamax;
	int m_StepTheta;
	int m_penWidth;
	COLORREF m_color;
	afx_msg void OnBnClickedButtonColor();
	int m_penType;
	afx_msg void OnBnClickedButtonSetfunc();
};
