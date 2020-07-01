#pragma once

/*class CalculatorFunc
{
	//CString a;
};*/

bool IsNum(char c);
bool IsOpt(char c);
int cPriority(char c);
double Calc(double num1, char opt, double num2);
double GetNum(CString& Eq, int& i, char xKey = 'x', double xVal = 0);
double CalcEquation(CString m_sEquation, bool& succ, char xKey = 'x', double xVal = 0);
double Get_Equation_Num(CString& Eq, int& i, bool& succ, char xKey = 'x', double xVal = 0);

