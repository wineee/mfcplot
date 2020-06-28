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
};
