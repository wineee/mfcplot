// FuncData.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "FuncData.h"
#include "CalculatorFunc.h"

const double inf = 1e14;
// FuncData
inline double Pow2(double x) { return x * x; }

//IMPLEMENT_SERIAL(FuncData, CObject, 0)


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

bool FuncData::GetNearest(pair<double, double> NowPoint, pair<double, double> &CmpPoint) {
	if (NowPoint.first < minX || NowPoint.second > maxX) return false;
	double detx = (maxX - minX) / stepX;
	bool ok = false;
	for (auto dot : vetPoint)
	 if (abs(dot.first - NowPoint.first) <= detx+0.1)
	  if (Pow2(dot.first - NowPoint.first) + Pow2(dot.second - NowPoint.second) < \
		  Pow2(NowPoint.first - CmpPoint.first) + Pow2(NowPoint.second - CmpPoint.second)) {
		CmpPoint = dot;
		ok = true;
 	  }
	return ok;
}

CString FuncData::GetEquation2() {
	return _T("NULL");
}



IMPLEMENT_SERIAL(NormalFD, FuncData, 0)
IMPLEMENT_SERIAL(PolarFD, FuncData, 0)
IMPLEMENT_SERIAL(TwoFD, FuncData, 0)
IMPLEMENT_SERIAL(DataFD, FuncData, 0)

NormalFD::NormalFD()
{
	FuncCas = CAS_NORMAL;
}

NormalFD::NormalFD(CString Equation, double min_X, double max_X, int step_X, COLORREF color, int penWidth, int penType) :
	FuncData(Equation, min_X, max_X, step_X, color, penWidth, penType)
{
	FuncCas = CAS_NORMAL;
}

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

bool NormalFD::GetNearest(pair<double, double> NowPoint, pair<double, double> &CmpPoint)
{
	if (NowPoint.first < minX || NowPoint.second > maxX) return false;
	bool succ;
	double nY = GetY(NowPoint.first,succ);
	if (Pow2(nY - NowPoint.second) < Pow2(NowPoint.first - CmpPoint.first) + Pow2(NowPoint.second - CmpPoint.second)) {
		CmpPoint = std::make_pair(NowPoint.first, nY);
		return true;
	}
	return false;
}

void NormalFD::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		 ar <<  FuncCas <<  m_Equation << minX << maxX << maxY << minY << stepX << m_penWidth << m_penType << m_color;
	}
	else {
		 ar >> FuncCas >> m_Equation >> minX >> maxX >> maxY >> minY >> stepX >> m_penWidth >> m_penType >> m_color;
		 this->CalcList();
	}
}


PolarFD::PolarFD()
{
	FuncCas = CAS_POLAR;
}

PolarFD::PolarFD(CString Equation, double min_T, double max_T, int step_T, COLORREF color, int penWidth, int penType) :
	FuncData(Equation, inf, -inf, step_T, color, penWidth, penType)
{
	FuncCas = CAS_POLAR;
	maxth = max_T;
	minth = min_T;
}

//
double PolarFD::GetY(double thVal, bool& succ)
{
	return  CalcEquation(m_Equation, succ, 't', thVal);
}

bool PolarFD::CalcList()
{
	vetPoint.clear();
	double detth = (maxth - minth) / stepX;
	bool succ = true;
	minY = inf; maxY = -inf;
	for (double tmp_th = minth; tmp_th <= maxth; tmp_th += detth) {
		double tmp_r = this->GetY(tmp_th, succ);
		//double
		double tmp_x = tmp_r * cos(tmp_th);
		double tmp_y = tmp_r * sin(tmp_th);
		if (tmp_x > maxX) maxX = tmp_x;
		if (tmp_x < minX) minX = tmp_x;
		if (tmp_y > maxY) maxY = tmp_y;
		if (tmp_y < minY) minY = tmp_y;
		vetPoint.emplace_back(std::make_pair(tmp_x, tmp_y));
		if (!succ) return false;
	}
	return true;
}


void PolarFD::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << FuncCas << m_Equation << minX << maxX << maxY << minY << stepX << m_penWidth << m_penType << m_color\
			<< minth << maxth;
	}
	else {
		ar >> FuncCas >> m_Equation >> minX >> maxX >> maxY >> minY >> stepX >> m_penWidth >> m_penType >> m_color\
			>> minth >> maxth;
		this->CalcList();
	}
}
///////////////////////////


TwoFD::TwoFD()
{
	FuncCas = CAS_TWO;

}

TwoFD::TwoFD(CString Equation_X, CString Equation_Y, double min_T, double max_T, int step_T, COLORREF color, int penWidth, int penType) :
	FuncData(Equation_X, inf, -inf, step_T, color, penWidth, penType)
{
	m_EquationY = Equation_Y;
	maxT = max_T;
	minT = min_T;
	FuncCas = CAS_TWO;
}

double TwoFD::GetX(double tVal, bool& succ)
{
	return  CalcEquation(m_Equation, succ, 't', tVal);
}


double TwoFD::GetY(double tVal, bool& succ)
{
	return  CalcEquation(m_EquationY, succ, 't', tVal);
}

bool TwoFD::CalcList()
{
	vetPoint.clear();
	double detT = (maxT - minT) / stepX;
	bool succ = true;
	minY = inf; maxY = -inf;
	for (double tmp_T = minT; tmp_T <= maxT; tmp_T += detT) {
		double tmp_x = this->GetX(tmp_T, succ);
		double tmp_y = this->GetY(tmp_T, succ);
		if (tmp_y > maxY) maxY = tmp_y;
		if (tmp_y < minY) minY = tmp_y;
		if (tmp_x > maxX) maxX = tmp_x;
		if (tmp_x < minX) minX = tmp_x;
		vetPoint.emplace_back(std::make_pair(tmp_x, tmp_y));
		if (!succ) return false;
	}
	return true;
}

CString TwoFD::GetEquation2() {
	return m_EquationY;
}

void TwoFD::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << FuncCas << m_Equation << minX << maxX << maxY << minY << stepX << m_penWidth << m_penType << m_color \
			<< minT << maxT << m_EquationY;
	}
	else {
		ar >> FuncCas >> m_Equation >> minX >> maxX >> maxY >> minY >> stepX >> m_penWidth >> m_penType >> m_color\
		   >> minT >> maxT >> m_EquationY;
		this->CalcList();
	}
}

int DataFD::DataFD_Cnt = 0;

DataFD::DataFD()
{
	FuncCas = CAS_DATA;
}

DataFD::DataFD(vector<double> &vetX, vector<double> &vetY, COLORREF color, int penWidth, int penType)
{
	minY = inf; maxY = -inf;
	minX = inf; maxY = -inf;
	for (int i = 0; i < vetX.size(); i++) {
		if (vetY[i] > maxY) maxY = vetY[i];
		if (vetY[i] < minY) minY = vetY[i];
		if (vetX[i] > maxX) maxX = vetX[i];
		if (vetX[i] < minX) minX = vetX[i];
		vetPoint.emplace_back(std::make_pair(vetX[i], vetY[i]));
	}
	stepX = -1;
	m_color = color;
	m_penType = penType;
	m_penWidth = penWidth;
	DataFD_Cnt++;
	FuncCas = CAS_DATA;
	m_Equation = _T("DataFunc");
	for (int i = 0; i < DataFD_Cnt; i++)
		m_Equation += _T("I");
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

void DataFD::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << FuncCas << m_Equation << minX << maxX << maxY << minY  << m_penWidth << m_penType << m_color;
		int n = vetPoint.size();
		ar << n;
		for (int i = 0; i < n; i++)
			ar << vetPoint[i].first << vetPoint[i].second;
	}
	else {
		ar >> FuncCas >> m_Equation >> minX >> maxX >> maxY >> minY  >> m_penWidth >> m_penType >> m_color;
		int n;
		ar >> n;
		for (int i = 0; i < n; i++) {
			double tmpX, tmpY;
			ar >> tmpX >> tmpY;
			vetPoint.push_back(std::make_pair(tmpX, tmpY));
		}
	}
}