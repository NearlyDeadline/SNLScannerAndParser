#include "table.h"
#include "Scanner.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::getline;

extern void split(const string& s, vector<string>& tokens, const string& delimiters = " ");

Table::Table(const std::string& filepath)
{
	CreateProductionsAndNonTerminals(filepath);
	CreateTerminals();
	InitializeTable();
}

void Table::CreateProductionsAndNonTerminals(const std::string& filepath)
{
	ifstream file;
	file.open(filepath);
	if (!file.is_open()) {
		return;
	}
	Production pro;//待加入的产生式
	vector<string> symbols;//所有文法符号
	string line;//文件中的一行
	int nonTerminalIndex = 0;//非终极符序号
	pair<map<string, int>::iterator, bool> insertPair;//若bool为false，说明非终极符已存在序号，无需增加，否则加1
	while (getline(file, line, '\n')/* && !line.empty()*/) {
		split(line, symbols, ",");
		pro.left = symbols.at(0);
		insertPair = nonTerminals.insert(map<string, int>::value_type(pro.left, nonTerminalIndex));
		if (insertPair.second)
			nonTerminalIndex++;
		for (size_t i = 1; i < symbols.size(); i++) {
			pro.right.push_back(symbols.at(i));
		}
		productions.push_back(pro);
		pro.left.erase();
		pro.right.clear();
	}
	file.close();
}

void Table::CreateTerminals(const int& count)
{
	Scanner* sc = new Scanner();
	for (int i = 0; i < count; i++) {
		terminals.insert(map<string, int>::value_type(sc->toString(i), i));
	}
	delete sc;
}

void Table::InitializeTable()
{
	table.reserve(nonTerminals.size);
	vector<int> line(terminals.size, -1);//一行，长度为终极符个数（列数），初始化为-1
	for (int i = 0; i < nonTerminals.size; i++) {
		table.push_back(line);
	}

}

std::vector<string> Table::GetFirst(const Production& pro)
{
	return std::vector<string>();
}

std::vector<string> Table::GetFollow(const Production& pro)
{
	return std::vector<string>();
}

std::vector<string> Table::GetPredict(const Production& pro)
{
	return std::vector<string>();
}

int Table::getProductionIndex(const std::string& nonTerminal, const std::string& terminal)
{
	return table.at(nonTerminals.find(nonTerminal)->second).at(terminals.find(terminal)->second);
}
