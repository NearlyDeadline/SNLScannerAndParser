#pragma once

#include <string>
#include <vector>
#include <map>

class Production {//产生式数据结构
public:
	std::string left;//左部
	std::vector<std::string> right;//右部
};

class Table {//LL1分析表
public:
	int getProductionIndex(const std::string& nonTerminal, const std::string& terminal);
	//根据当前非终极符nonTerminal和输入符号terminal，返回应选择的产生式序号（从0开始）
	Table(const std::string& filepath);
	//根据产生式文件构造predict集
	int operator()(const std::string& nonTerminal, const std::string& terminal) {
		return getProductionIndex(nonTerminal, terminal);
	}
	//重载函数调用运算符，便于代码编写
private:
	void CreateProductionsAndNonTerminals(const std::string& filepath);//从文件读取，保存产生式和非终极符到内存中备用
	void CreateTerminals(const int& count = 42);//根据Scanner.h中的枚举，保存Token化后的所有终极符到内存中备用
	void InitializeTable();//创建LL(1)分析表
	std::vector<string> GetFirst(const Production& pro);//计算first集合，传入产生式，返回一个保存终极符名称的向量
	std::vector<string> GetFollow(const Production& pro);//计算follow集合，传入产生式，返回一个保存终极符名称的向量
	std::vector<string> GetPredict(const Production& pro);//计算predict集合，传入产生式，返回一个保存终极符名称的向量
	std::vector<std::vector<int>> table;//分析表
	std::vector<Production> productions;//保存文法所有产生式
	std::map<std::string, int> nonTerminals;//保存文法所有非终极符
	std::map<std::string, int> terminals;//保存文法所有终极符（相对于Token化的文法产生式而言的）
};
