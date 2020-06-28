#pragma once

// FuncData 命令目标

class FuncData : public CObject
{
public:
	CString m_Equation;
	double minX, maxX, stepX;//枚举范围
	double GetY(int x);
	//yang shi
	FuncData();
	FuncData(CString Equation);
	virtual ~FuncData();
};


