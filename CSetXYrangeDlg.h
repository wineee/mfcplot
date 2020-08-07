#pragma once


// CSetXYrangeDlg 对话框

class CSetXYrangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetXYrangeDlg)

public:
	CSetXYrangeDlg(double Xmin, double Xmax, double Ymin, double Ymax, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetXYrangeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SET_RANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_Xmin;
	double m_Xmax;
	double m_Ymin;
	double m_Ymax;
};
