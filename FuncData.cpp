// FuncData.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "FuncData.h"
#include "CalculatorFunc.h"

const double inf = 1e14;
// FuncData


FuncData::FuncData()
{
	minX = maxX = stepX = 0;
	maxY = minY = 0;
	m_penType = PS_SOLID;
	m_penWidth = 1;
	m_color = RGB(0, 0, 0);
}

FuncData::~FuncData()
{
}

FuncData::FuncData(CString Equation, double min_X, double max_X, int step_X, COLORREF color, int penWidth, int penType) :
	m_Equation(Equation), minX(min_X), maxX(max_X), stepX(step_X), m_color(color), m_penWidth(penWidth),m_penType(penType)
{
	maxY = minY = 0;
}

// FuncData 成员函数



//

NormalFD::NormalFD()
{

}

NormalFD::NormalFD(CString Equation, double min_X, double max_X, int step_X, COLORREF color, int penWidth, int penType) :
	FuncData(Equation, min_X, max_X, step_X, color, penWidth, penType)
{

}

//
double NormalFD::GetY(double xVal, bool& succ)
{
	return  CalcEquation(m_Equation, succ, 'x', xVal);
}

bool NormalFD::CalcList()
{
	vetPoint.clear();
	double detx = (maxX - minX) / stepX;
	bool succ = true;
	minY = inf; maxY = -inf;
	for (double tmp_x = minX; tmp_x <= maxX; tmp_x += detx) {
		double tmp_y = this->GetY(tmp_x, succ);
		if (tmp_y > maxY) maxY = tmp_y;
		if (tmp_y < minY) minY = tmp_y;
		vetPoint.emplace_back(std::make_pair(tmp_x, tmp_y));
		if (!succ) return false;
	}
	return true;
}


PolarFD::PolarFD()
{

}

PolarFD::PolarFD(CString Equation, double min_T, double max_T, int step_T, COLORREF color, int penWidth, int penType) :
	FuncData(Equation, min_T, max_T, step_T, color, penWidth, penType)
{

}

//
double PolarFD::GetY(double thVal, bool& succ)
{
	return  CalcEquation(m_Equation, succ, 'x', thVal);
}

bool PolarFD::CalcList()
{
	vetPoint.clear();
	double detth = (maxX - minX) / stepX;
	bool succ = true;
	minY = inf; maxY = -inf;
	for (double tmp_th = minX; tmp_th <= maxX; tmp_th += detth) {
		double tmp_r = this->GetY(tmp_th, succ);
		//double
		double tmp_x = tmp_r * cos(tmp_th);
		double tmp_y = tmp_r * sin(tmp_th);
		if (tmp_y > maxY) maxY = tmp_y;
		if (tmp_y < minY) minY = tmp_y;
		vetPoint.emplace_back(std::make_pair(tmp_x, tmp_y));
		if (!succ) return false;
	}
	return true;
}
///////////////////////////


TwoFD::TwoFD()
{

}

TwoFD::TwoFD(CString Equation_X, CString Equation_Y, double min_T, double max_T, int step_T, COLORREF color, int penWidth, int penType) :
	FuncData(Equation_X, min_T, max_T, step_T, color, penWidth, penType)
{
	m_EquationY = Equation_Y;
}

double TwoFD::GetX(double tVal, bool& succ)
{
	return  CalcEquation(m_Equation, succ, 'x', tVal);
}


double TwoFD::GetY(double tVal, bool& succ)
{
	return  CalcEquation(m_EquationY, succ, 'x', tVal);
}

bool TwoFD::CalcList()
{
	vetPoint.clear();
	double detT = (maxX - minX) / stepX;
	bool succ = true;
	minY = inf; maxY = -inf;
	for (double tmp_T = minX; tmp_T <= maxX; tmp_T += detT) {
		double tmp_x = this->GetX(tmp_T, succ);
		double tmp_y = this->GetY(tmp_T, succ);
		if (tmp_y > maxY) maxY = tmp_y;
		if (tmp_y < minY) minY = tmp_y;
		//if (tmp_x)
		vetPoint.emplace_back(std::make_pair(tmp_x, tmp_y));
		if (!succ) return false;
	}
	return true;
}

DataFD::DataFD()
{

}

DataFD::DataFD(vector<double> &vetX, vector<double> &vetY)
{
	minY = inf; maxY = -inf;
	for (int i = 0; i < vetX.size(); i++) {
		if (vetY[i] > maxY) maxY = vetY[i];
		if (vetY[i] < minY) minY = vetY[i];
		vetPoint.emplace_back(std::make_pair(vetX[i], vetY[i]));
	}
}

bool DataFD::CalcList() {
	return true;
}

double DataFD::GetY(double xVal, bool& succ) {
	for (auto dot : vetPoint)
		if (dot.first == xVal)
			return dot.second;
	return inf;
}