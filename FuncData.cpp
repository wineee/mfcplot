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
}

FuncData::~FuncData()
{
}

FuncData::FuncData(CString Equation, double min_X, double max_X, int step_X) :
	m_Equation(Equation), minX(min_X), maxX(max_X), stepX(step_X)
{

}

// FuncData 成员函数



//

NormalFD::NormalFD()
{

}

NormalFD::NormalFD(CString Equation, double min_X, double max_X, int step_X) :
	FuncData(Equation, min_X, max_X, step_X)
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