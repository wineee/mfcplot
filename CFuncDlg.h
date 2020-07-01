#pragma once


// CFuncDlg 对话框

class CFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFuncDlg)

public:
	CFuncDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFuncDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NORMALFUNC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strEquation;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonPi();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButtonE();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDot();
	afx_msg void OnBnClickedButtonDec();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonSin();
	afx_msg void OnBnClickedButtonCos();
	afx_msg void OnBnClickedButtonTan();
	afx_msg void OnBnClickedButtonLog();
	afx_msg void OnBnClickedButtonPow();
	afx_msg void OnBnClickedButton2pow();
	afx_msg void OnBnClickedButtonSqrt();
	afx_msg void OnBnClickedButtonLn();
	afx_msg void OnBnClickedButtonAbs();
	afx_msg void OnBnClickedButtonX();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonFloor();
	afx_msg void OnBnClickedButtonCeiling();
	afx_msg void OnBnClickedButtonRound();
	afx_msg void OnBnClickedButtonCubic();
};
