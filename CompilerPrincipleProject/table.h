#pragma once

#include <string>
#include <vector>

class Production {//产生式数据结构
public:
	std::string left;//左部
	std::vector<std::string> right;//右部
};

extern std::vector<Production> productions;//保存文法所有产生式

class Table {//LL1分析表
public:
	int getProductionIndex(std::string nonTerminal, std::string terminal);
	//根据当前非终极符nonTerminal和输入符号terminal，返回应选择的产生式序号（从0开始）
};
