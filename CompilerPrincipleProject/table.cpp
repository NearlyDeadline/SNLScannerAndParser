#include "table.h"
#include <fstream>
#include <iostream>
#include <algorithm>

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
		for (const string& symbol : i.right) {
			if (!is_nonterminal(symbol)) {
				insert_pair = terminals.insert(unordered_map<string, int>::value_type(symbol, terminal_index));
				if (insert_pair.second)
					terminal_index++;
			}
		}
	}
	terminals.insert(unordered_map<string, int>::value_type("#", terminal_index++));
}

void Table::initialize_table()
{
	vector<set<string>> first_sets(nonterminals.size());
	for (auto i : nonterminals) {
		first_sets.at(i.second) = get_first_set(i.first);
	}
	vector<set<string>> follow_sets = get_follow_sets();//保存文法所有非终极符相应的follow集

	std::ofstream test("follow.txt");
	int i = 0;
	for (auto follow_set : follow_sets) {
		test << "非终极符序号" << i++ << "的follow集合有：";
		for (auto symbol : follow_set) {
			test << symbol << " ";
		}
		test << "\n";
	}
	test.close();

	vector<int> each_line(terminals.size(), 0);
	size_t line_count = nonterminals.size();
	for (size_t i = 0; i < line_count; i++)
		table.push_back(each_line);
	int production_index = 1;
	test.open("predict.txt");
	for (Production& pro : productions) {
		pro.predict_set = get_predict_set(pro, first_sets, follow_sets);
		test << "产生式编号为" << production_index << "的predict集是：";
		for (const string& terminal : pro.predict_set) {
			table.at(nonterminals.find(pro.left)->second).at(terminals.find(terminal)->second) = production_index;
			test << terminal << ", ";
		}
		test << "\n";
		production_index++;
	}
	test.close();
}

set<string> Table::get_first_set(const std::string & symbol) const
{
	set<string> result;
	if (is_terminal(symbol))//若为终极符,结果为本身
		result.insert(symbol);
	else if (is_nonterminal(symbol)) {//若为非终极符,则需要遍历一遍所有左部为它的产生式
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
						if (temp.find("$") != temp.end()) {//当前非终极符推导出了空串，删除空串并加入结果
							temp.erase("$");
							for (const string& sym : temp) {
								result.insert(sym);
							}
						}
						else {//当前非终极符未推导出空串，加入结果，直接退出循环
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
	else if (symbol.empty())//传了个空串进来
		result.insert("$");
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
		if (temp.find("$") == temp.end()) {//这个符号不能推导空串，加入当前符号的first集后退出
			can_deduct_empty = false;
			for (const string &i : temp)
				result.insert(i);
			break;
		}
		else {//这个符号能推导空串，把first集去掉空串，加入结果，然后判断下一个符号
			temp.erase("$");
			for (const string& i : temp)
				result.insert(i);
		}
	}
	if (can_deduct_empty)//全部符号中都能推导出空串
		result.insert("$");
	return result;
}

vector<set<string>> Table::get_follow_sets() const
{
	vector<set<string>> prev(nonterminals.size(), set<string>());
	const string start_symbol = "Program";//文法开始符，加入#
	prev.at(nonterminals.find(start_symbol)->second).insert("#");
	vector<set<string>> result;
	do {
		result.assign(prev.begin(), prev.end());
		prev = iterate_follow_sets(prev);
	} while (is_different(result, prev));//如果result和prev有任一处不同，则代表未收敛，停止判断不同，执行下一次迭代
	return result;
}

vector<set<string>> Table::iterate_follow_sets(const vector<set<string>>& prev) const
{
	vector<set<string>> result(prev);
	vector<string>::const_iterator B_index;
	for (auto B : nonterminals) {
		for (const Production& pro : productions) {
			B_index = std::find(pro.right.begin(), pro.right.end(), B.first);
			if (B_index != pro.right.end()) {//找到了 A->xBy，需要求y的first集
				B_index++;
				if (B_index == pro.right.end()) {//y为空串
					set<string> follow_set_A = result.at(nonterminals.find(pro.left)->second);
					for (const string& symbol : follow_set_A)//插入follow(A)
						result.at(B.second).insert(symbol);
				}
				else {//y不为空串，求y的first集
					vector<string> y;
					for (vector<string>::const_iterator i = B_index; i != pro.right.end(); i++)
						y.push_back(*i);
					set<string> first_set_y = get_first_set(y);
					if (first_set_y.find("$") != first_set_y.end()) {//first集含有空串
						first_set_y.erase("$");
						for (const string& symbol : first_set_y)
							result.at(B.second).insert(symbol);
						set<string> follow_set_A = result.at(nonterminals.find(pro.left)->second);
						for (const string& symbol : follow_set_A)//插入follow(A)
							result.at(B.second).insert(symbol);
					}
					else {//不含空串，加入first集即可
						for (const string& symbol : first_set_y)
							result.at(B.second).insert(symbol);
					}
				}
			}
		}
	}
	return result;
}

bool Table::is_different(const vector<set<string>>& lhs, const vector<set<string>>& rhs) const
{
	bool result = false;
	if (lhs.size() != rhs.size())
		result = true;
	else {
		size_t length = lhs.size();
		for (size_t i = 0; i < length; i++) {
			if (is_different(lhs.at(i), rhs.at(i))) {//任一对follow集不相同，向量整体就不相同
				result = true;
				break;
			}
		}
	}
	return result;
}

bool Table::is_different(const std::set<std::string>& lhs, const std::set<std::string>& rhs) const
{
	bool result = false;
	if (lhs.size() != rhs.size())//两个set判断相等，只需保证大小相同的条件下，lhs的元素均在rhs中出现即可
		result = true;
	else {
		for (const string& symbol : lhs) {
			if (rhs.find(symbol) == rhs.end()) {//rhs中没找到lhs的某个元素
				result = true;
				break;
			}
		}
	}
	return result;
}

set<string> Table::get_predict_set(const Production& pro, const vector<set<string>>& first_sets, const vector<set<string>>& follow_sets) const
{
	set<string> result;
	set<string> first_set_right = get_first_set(pro.right);
	if (first_set_right.find("$") == first_set_right.end()) {//右部无法推导空串，结果即为右部first集
		result = first_set_right;
	}
	else {//右部可推导空串，将右部first集去除空串后加入结果，再加入左部的follow集
		first_set_right.erase("$");
		result = first_set_right;
		for (const string& symbol : follow_sets.at(nonterminals.find(pro.left)->second))
			result.insert(symbol);
	}
	return result;
}

bool Table::is_nonterminal(const std::string& symbol) const
{
	return nonterminals.find(symbol) != nonterminals.end();
}

bool Table::is_terminal(const std::string& symbol) const
{
	return terminals.find(symbol) != terminals.end();
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

size_t Table::get_key_index(const std::unordered_map<std::string, int>& data, const std::string& key) const//弃用
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
