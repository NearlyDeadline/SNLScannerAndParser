#include "table.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::string;
using std::vector;
using std::pair;
using std::unordered_map;
using std::getline;
using std::set;

extern void split(const string& s, vector<string>& tokens, const string& delimiters = " ");

Table::Table(const std::string& filepath)
{
	read_productions_nonterminals(filepath);
	create_terminals();
	initialize_table();
}

void Table::read_productions_nonterminals(const std::string& filepath)
{
	ifstream file;
	file.open(filepath);
	if (!file.is_open()) {
		return;
	}
	Production pro;//待加入的产生式
	vector<string> symbols;//所有文法符号
	string line;//文件中的一行
	int nonterminal_index = 0;//非终极符序号
	pair<unordered_map<string, int>::iterator, bool> insert_pair;//若bool为false，说明非终极符已存在序号，无需增加，否则加1
	while (getline(file, line, '\n')/* && !line.empty()*/) {
		split(line, symbols, ",");
		pro.left = symbols.at(0);
		insert_pair = nonterminals.insert(unordered_map<string, int>::value_type(pro.left, nonterminal_index));
		if (insert_pair.second)
			nonterminal_index++;
		for (size_t i = 1; i < symbols.size(); i++) {
			pro.right.push_back(symbols.at(i));
		}
		productions.push_back(pro);
		pro.left.erase();
		pro.right.clear();
	}
	file.close();
}

void Table::create_terminals()
{
	int terminal_index = 0;//终极符序号
	pair<unordered_map<string, int>::iterator, bool> insert_pair;//若bool为false，说明终极符已存在序号，无需增加，否则加1
	for (const Production& i : productions) {
		for (const string& ch : i.right) {
			if (!is_nonterminal(ch)) {
				insert_pair = terminals.insert(unordered_map<string, int>::value_type(ch, terminal_index));
				if (insert_pair.second)
					terminal_index++;
			}
		}
	}
	terminals.insert(unordered_map<string, int>::value_type("#", terminal_index++));
}

void Table::initialize_table()
{
	int line_count = nonterminals.size();
	table.reserve(line_count);
	vector<int> line(terminals.size(), 0);//一行，长度为终极符个数（列数），初始化为0,代表无可用文法产生式
	for (int i = 0; i < line_count; i++) {
		table.push_back(line);
	}
	vector<set<string>> first_sets;
	first_sets.reserve(nonterminals.size());
	for (auto i : nonterminals) {
		first_sets.push_back(get_first_set(i.first));
	}
	vector<set<string>> follow_sets = get_follow_sets();//保存文法所有非终极符相应的follow集

	for (Production& pro : productions)
		pro.predict_set = get_predict_set(pro, first_sets, follow_sets);
	/*
	std::ofstream test("test.txt");

	for (auto i : first_sets) {
		for (const string& j : i) {
			test << j << " ";
		}
		test << "\n";
	}

	test.close();
	std::ifstream strs("test.txt");
	string str;
	test.open("test2.txt");
	for (auto i : nonterminals) {
		getline(strs, str, '\n');
		test << "序号为"<< i.second << "的非终极符" << i.first << "的首部为：" << str << "\n";
	}
	strs.close();
	test.close();
	*/
	
}

set<string> Table::get_first_set(const std::string & symbol) const
{
	set<string> result;
	if (is_terminal(symbol))//若为终极符,结果为本身
		result.insert(symbol);
	else if (is_nonterminal(symbol)){//若为非终极符,则需要遍历一遍所有左部为它的产生式
		for (const Production& pro : productions) {
			if (pro.left == symbol) {
				if (is_terminal(pro.right.at(0)))//右部第一个文法符号为终极符或空串,则加入
					result.insert(pro.right.at(0));
				else {//右侧第一个文法符号为非终极符,需要遍历所有非终极符
					int length = pro.right.size();//右部长度
					int first_terminal_index = get_first_terminal_index(pro);//右部首个终极符下标
					set<string> temp;
					bool can_deduct_empty = true;
					for (int i = 0; i < first_terminal_index; i++) {
						temp = get_first_set(pro.right.at(i));
						if (temp.find("$") != temp.end()) {//当前非终极符推导出了空串
							temp.erase("$");
							for (const string& sym : temp) {
								result.insert(sym);
							}
						}
						else {//当前非终极符未推导出空串
							can_deduct_empty = false;
							for (const string& sym : temp) {
								result.insert(sym);
							}
							break;
						}
					}
					if (can_deduct_empty) {//全部非终极符都能推导出空串
						if (first_terminal_index == length)//产生式右部全部是非终极符
							result.insert("$");
						else
							result.insert(pro.right.at(first_terminal_index));
					}
				}
			}
		}
	}
	return result;
}

set<string> Table::get_first_set(const std::vector<std::string>& symbols) const
{
	set<string> result;
	set<string> temp;
	size_t length = symbols.size();
	bool can_deduct_empty = true;
	for (size_t i = 0; i < length; i++) {
		temp = get_first_set(symbols.at(i));
		if (temp.find("$") == temp.end()) {
			can_deduct_empty = false;
			for (const string &i : temp)
				result.insert(i);
			break;
		}
		else {
			temp.erase("$");
			for (const string& i : temp)
				result.insert(i);
		}
	}
	if (can_deduct_empty)
		result.insert("$");
	return result;
}

vector<set<string>> Table::get_follow_sets() const
{
	vector<set<string>> result;
	return result;
}

set<string> Table::get_predict_set(const Production& pro, const vector<set<string>>& first_sets, const vector<set<string>>& follow_sets) const
{
	return set<string>();
}

bool Table::is_nonterminal(const std::string& ch) const
{
	return nonterminals.find(ch) != nonterminals.end();
}

bool Table::is_terminal(const std::string& ch) const
{
	return terminals.find(ch) != terminals.end();
}

size_t Table::get_first_terminal_index(const Production& pro) const
{
	size_t length = pro.right.size();
	for (size_t i = 0; i < length; i++) {
		if (is_terminal(pro.right.at(i)))
			return i;
	}
	return length;
}

size_t Table::get_key_index(const std::unordered_map<std::string, int>& data, const std::string& key) const
{
	size_t i = 0;
	auto target = data.find(key);
	for (auto it = data.begin(); it != data.end() && it != target; it++, i++);
	return i;
}

size_t Table::get_production_index(const std::string& nonterminal, const std::string& terminal) const
{
	return table.at(nonterminals.find(nonterminal)->second).at(terminals.find(terminal)->second);
}
