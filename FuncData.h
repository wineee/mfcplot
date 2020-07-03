#pragma once
#include <vector>
#include <utility>
using std::pair;
using std::vector;
// FuncData 命令目标

#define CAS_NORMAL			1
#define CAS_POLAR			2
#define CAS_TWO				3
#define CAS_DATA			4

class FuncData : public CObject
{
//	DECLARE_SERIAL(FuncData)
public:
	int FuncCas;            //函数类型
	CString m_Equation;		//函数表达式
	double minX, maxX;		//x极值
	double maxY, minY;		//y极值
	int stepX;				//可以理解为样本点的数量
	int m_penWidth;			//画笔宽度
	int m_penType;			//画笔类型
	COLORREF m_color;		//画笔颜色
	vector<pair<double, double> > vetPoint;			 //储存所有样本点
	virtual double GetY(double xVal, bool& succ) = 0;//得到未知数为xVal时函数值，succ表示计算是否成功
	virtual bool CalcList() = 0;					 //计算vetPoint
	virtual bool GetNearest(pair<double,double> NowPoint, pair<double, double> &CmpPoint);//获取本函数与NowPoint最近的点
	virtual CString GetEquation2();					 //为了得到参数方程第二个函数式
	FuncData();
	FuncData(CString Equation,double minX,double maxX,int stepX,COLORREF color, int penWidth,int penType);//构造函数
	virtual ~FuncData();
};


class NormalFD : public FuncData
{
	DECLARE_SERIAL(NormalFD)
public:
	virtual double GetY(double xVal, bool& succ);
	virtual bool CalcList();
	virtual bool GetNearest(pair<double, double> NowPoint, pair<double, double> &CmpPoint);
	virtual void Serialize(CArchive& ar);
	NormalFD();
	NormalFD(CString Equation, double minX, double maxX, int stepX, COLORREF color, int penWidth,int penType);

};

class PolarFD : public FuncData
{
	DECLARE_SERIAL(PolarFD)
public:
	virtual double GetY(double sVal, bool& succ);
	virtual bool CalcList();
	virtual void Serialize(CArchive& ar);
	double maxth, minth;   //自变量θ取值范围
	PolarFD();
	PolarFD(CString Equation, double minTh, double maxTh, int stepTh, COLORREF color, int penWidth, int penType);
};

class TwoFD : public FuncData
{
	DECLARE_SERIAL(TwoFD)
public:
	CString m_EquationY;
	double maxT, minT;
	double GetX(double tVal, bool& succ);
	virtual double GetY(double tVal, bool& succ);
	virtual bool CalcList();
	virtual CString GetEquation2();
	virtual void Serialize(CArchive& ar);
	TwoFD();
	TwoFD(CString Equation_X, CString Equation_Y,double minX, double maxX, int stepX, COLORREF color, int penWidth, int penType);
};

class DataFD : public FuncData
{
	DECLARE_SERIAL(DataFD)
public:
	static int DataFD_Cnt;  //记录数据点类型函数数量
	virtual double GetY(double tVal, bool& succ);
	virtual bool CalcList();
	//virtual bool GetNearest(pair<double, double> NowPoint, pair<double, double> CmpPoint);
	virtual void Serialize(CArchive& ar);
	DataFD();
	DataFD(vector<double> &vetX, vector<double> &vetY, COLORREF color, int penWidth, int penType);
};