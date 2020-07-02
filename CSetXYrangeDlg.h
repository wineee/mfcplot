#pragma once


// CSetXYrangeDlg 对话框

class CSetXYrangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetXYrangeDlg)

public:
	CSetXYrangeDlg(int Xmin, int Xmax, int Ymin, int Ymax, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetXYrangeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SET_RANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_Xmin;
//	afx_msg void OnEnChangeEdit1();
	int m_Xmax;
	int m_Ymin;
	int m_Ymax;
};
