#pragma once
#include <vector>
#include <utility>
using std::pair;
using std::vector;
// FuncData 命令目标

class FuncData : public CObject
{
public:
	CString m_Equation;
	double minX, maxX;
	double maxY, minY;
	int stepX;//枚举步数
	int m_penWidth;
	int m_penType;
	COLORREF m_color;
	virtual double GetY(double xVal, bool& succ) = 0;
	virtual bool CalcList() = 0;
	//yang shi
	vector<pair<double,double> > vetPoint;
	FuncData();
	FuncData(CString Equation,double minX,double maxX,int stepX,COLORREF color, int penWidth,int penType);
	virtual ~FuncData();
};


class NormalFD : public FuncData
{
public:
	virtual double GetY(double xVal, bool& succ);
	virtual bool CalcList();

	NormalFD();
	NormalFD(CString Equation, double minX, double maxX, int stepX, COLORREF color, int penWidth,int penType);

};

class PolarFD : public FuncData
{
public:
	virtual double GetY(double sVal, bool& succ);
	virtual bool CalcList();

	PolarFD();
	PolarFD(CString Equation, double minTh, double maxTh, int stepTh, COLORREF color, int penWidth, int penType);
};

class TwoFD : public FuncData
{
public:
	CString m_EquationY;
	double GetX(double tVal, bool& succ);
	virtual double GetY(double tVal, bool& succ);
	virtual bool CalcList();

	TwoFD();
	TwoFD(CString Equation_X, CString Equation_Y,double minX, double maxX, int stepX, COLORREF color, int penWidth, int penType);
};

class DataFD : public FuncData
{
public:
	virtual double GetY(double tVal, bool& succ);
	virtual bool CalcList();
	DataFD();
	DataFD(vector<double> &vetX, vector<double> &vetY);
};