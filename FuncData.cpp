// FuncData.cpp: 实现文件
//

#include "pch.h"
#include "mfcplot.h"
#include "FuncData.h"


// FuncData

#define MAXNUM 100
#define MAXOPT 100

bool IsOpt(char c) {
	return  c == '+' || c == '-' || c == '*' || c == '/';
}

bool IsNum(char c) {
	return c >= '0' && c <= '9';
}

double GetNum(CString& Eq, int& i, int radix)
{
	double x = 0;
	while (i < Eq.GetLength() && IsNum(Eq[i]))
	{
		x = x * radix + Eq[i] - '0';
		i++;
	}
	double rad = 1.0 / radix;
	if (i < Eq.GetLength() && Eq[i] == '.')
	{
		i++;
		while (i < Eq.GetLength() && IsNum(Eq[i]))
		{
			x = x + (Eq[i] - '0') * rad;
			rad = rad / radix;
			i++;
		}
	}
	return x;
}



bool Calc2(double& ans, double num1, char opt, double num2)
{
	switch (opt)
	{
	case '+': ans = num1 + num2; return true;
	case '-': ans = num1 - num2; return true;
	case '*': ans = num1 * num2; return true;
	case '/':
		if (fabs(num2) < 1e-14) return false;
		ans = num1 / num2; return true;
	}
}

bool Greater(char opt1, char opt2) {
	//if (opt2 == '(') return false;
	return  (opt1 == '*' || opt1 == '/') &&
		(opt2 == '+' || opt2 == '-');
}

//return -1---ʧ 0---0 1---ɹ
bool GetOutSta(double* num, int& ntop, char* opt, int& otop) {
	double tmp;
	if (otop < 1 || ntop < 2 || !IsOpt(opt[otop]))
		return -1;
	if (!Calc2(tmp, num[ntop - 1], opt[otop], num[ntop]))
		return 0;
	otop--;
	ntop--;
	num[ntop] = tmp;
	return 1;
}

bool MyCalculator::Calc(CString Equation, CString& ans, int radix)
{
	double num[MAXNUM];
	int ntop = 0;
	char opt[MAXOPT];
	int otop = 0;
	int Len = Equation.GetLength();

	for (int i = 0; i < Len; )
	{
		if (Equation[i] == '(')
		{
			opt[++otop] = Equation[i++];
			if (i >= Len) return FALSE;
		}

		bool flag = false;
		if (Equation[i] == '-')
		{
			flag = true;
			i++;
			if (i >= Len) return FALSE;
		}
		if (!IsNum(Equation[i]))
			return FALSE;
		num[++ntop] = GetNum(Equation, i, radix) * (flag ? -1 : 1);
		if (i >= Len) break;

		if (Equation[i] == ')')
		{
			while (otop > 0 && opt[otop] != '(')
			{
				INT cas = GetOutSta(num, ntop, opt, otop);
				if (cas == -1) return FALSE;
				if (cas == 0) {
					ans = _T("0쳣");
					return TRUE;
				}
			}
			if (otop == 0) return FALSE;
			otop--;
			i++;
			if (i >= Len) break;
		}

		if (!IsOpt(Equation[i]))
			return FALSE;
		while (otop > 0 && opt[otop] != '(' && !Greater(Equation[i], opt[otop]))
		{
			INT cas = GetOutSta(num, ntop, opt, otop);
			if (cas == -1) return FALSE;
			if (cas == 0) {
				ans = _T("0쳣");
				return TRUE;
			}
		}
		opt[++otop] = Equation[i++];
		if (i >= Len) return FALSE;
	}
	//return 0;
	while (otop) {
		INT cas = GetOutSta(num, ntop, opt, otop);
		if (cas == -1) return FALSE;
		if (cas == 0) {
			ans = _T("0쳣");
			return TRUE;
		}
	}
	if (ntop != 1) return FALSE;
	ans.Format(_T("%g"), num[ntop]);
	if (radix != 10) {
		ConvertRad(ans, 10, radix);
	}
	return TRUE;
}

FuncData::FuncData(CString Equation) {
	m_Equation = Equation;

}

FuncData::FuncData()
{
}

FuncData::~FuncData()
{
}


// FuncData 成员函数
