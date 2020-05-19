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
	Production pro;//������Ĳ���ʽ
	vector<string> symbols;//�����ķ�����
	string line;//�ļ��е�һ��
	int nonterminal_index = 0;//���ռ������
	pair<unordered_map<string, int>::iterator, bool> insert_pair;//��boolΪfalse��˵�����ռ����Ѵ�����ţ��������ӣ������1
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
	int terminal_index = 0;//�ռ������
	pair<unordered_map<string, int>::iterator, bool> insert_pair;//��boolΪfalse��˵���ռ����Ѵ�����ţ��������ӣ������1
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
	vector<set<string>> follow_sets = get_follow_sets();//�����ķ����з��ռ�����Ӧ��follow��

	std::ofstream test("follow.txt");
	int i = 0;
	for (auto follow_set : follow_sets) {
		test << "���ռ������" << i++ << "��follow�����У�";
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
		test << "����ʽ���Ϊ" << production_index << "��predict���ǣ�";
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
	if (is_terminal(symbol))//��Ϊ�ռ���,���Ϊ����
		result.insert(symbol);
	else if (is_nonterminal(symbol)) {//��Ϊ���ռ���,����Ҫ����һ��������Ϊ���Ĳ���ʽ
		for (const Production& pro : productions) {
			if (pro.left == symbol) {
				if (is_terminal(pro.right.at(0)))//�Ҳ���һ���ķ�����Ϊ�ռ�����մ�,�����
					result.insert(pro.right.at(0));
				else {//�Ҳ��һ���ķ�����Ϊ���ռ���,��Ҫ�������з��ռ���
					int length = pro.right.size();//�Ҳ�����
					int first_terminal_index = get_first_terminal_index(pro);//�Ҳ��׸��ռ����±�
					set<string> temp;
					bool can_deduct_empty = true;
					for (int i = 0; i < first_terminal_index; i++) {
						temp = get_first_set(pro.right.at(i));
						if (temp.find("$") != temp.end()) {//��ǰ���ռ����Ƶ����˿մ���ɾ���մ���������
							temp.erase("$");
							for (const string& sym : temp) {
								result.insert(sym);
							}
						}
						else {//��ǰ���ռ���δ�Ƶ����մ�����������ֱ���˳�ѭ��
							can_deduct_empty = false;
							for (const string& sym : temp) {
								result.insert(sym);
							}
							break;
						}
					}
					if (can_deduct_empty) {//ȫ�����ռ��������Ƶ����մ�
						if (first_terminal_index == length)//����ʽ�Ҳ�ȫ���Ƿ��ռ���
							result.insert("$");
						else
							result.insert(pro.right.at(first_terminal_index));
					}
				}
			}
		}
	}
	else if (symbol.empty())//���˸��մ�����
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
		if (temp.find("$") == temp.end()) {//������Ų����Ƶ��մ������뵱ǰ���ŵ�first�����˳�
			can_deduct_empty = false;
			for (const string &i : temp)
				result.insert(i);
			break;
		}
		else {//����������Ƶ��մ�����first��ȥ���մ�����������Ȼ���ж���һ������
			temp.erase("$");
			for (const string& i : temp)
				result.insert(i);
		}
	}
	if (can_deduct_empty)//ȫ�������ж����Ƶ����մ�
		result.insert("$");
	return result;
}

vector<set<string>> Table::get_follow_sets() const
{
	vector<set<string>> prev(nonterminals.size(), set<string>());
	const string start_symbol = "Program";//�ķ���ʼ��������#
	prev.at(nonterminals.find(start_symbol)->second).insert("#");
	vector<set<string>> result;
	do {
		result.assign(prev.begin(), prev.end());
		prev = iterate_follow_sets(prev);
	} while (is_different(result, prev));//���result��prev����һ����ͬ�������δ������ֹͣ�жϲ�ͬ��ִ����һ�ε���
	return result;
}

vector<set<string>> Table::iterate_follow_sets(const vector<set<string>>& prev) const
{
	vector<set<string>> result(prev);
	vector<string>::const_iterator B_index;
	for (auto B : nonterminals) {
		for (const Production& pro : productions) {
			B_index = std::find(pro.right.begin(), pro.right.end(), B.first);
			if (B_index != pro.right.end()) {//�ҵ��� A->xBy����Ҫ��y��first��
				B_index++;
				if (B_index == pro.right.end()) {//yΪ�մ�
					set<string> follow_set_A = result.at(nonterminals.find(pro.left)->second);
					for (const string& symbol : follow_set_A)//����follow(A)
						result.at(B.second).insert(symbol);
				}
				else {//y��Ϊ�մ�����y��first��
					vector<string> y;
					for (vector<string>::const_iterator i = B_index; i != pro.right.end(); i++)
						y.push_back(*i);
					set<string> first_set_y = get_first_set(y);
					if (first_set_y.find("$") != first_set_y.end()) {//first�����пմ�
						first_set_y.erase("$");
						for (const string& symbol : first_set_y)
							result.at(B.second).insert(symbol);
						set<string> follow_set_A = result.at(nonterminals.find(pro.left)->second);
						for (const string& symbol : follow_set_A)//����follow(A)
							result.at(B.second).insert(symbol);
					}
					else {//�����մ�������first������
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
			if (is_different(lhs.at(i), rhs.at(i))) {//��һ��follow������ͬ����������Ͳ���ͬ
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
	if (lhs.size() != rhs.size())//����set�ж���ȣ�ֻ�豣֤��С��ͬ�������£�lhs��Ԫ�ؾ���rhs�г��ּ���
		result = true;
	else {
		for (const string& symbol : lhs) {
			if (rhs.find(symbol) == rhs.end()) {//rhs��û�ҵ�lhs��ĳ��Ԫ��
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
	if (first_set_right.find("$") == first_set_right.end()) {//�Ҳ��޷��Ƶ��մ��������Ϊ�Ҳ�first��
		result = first_set_right;
	}
	else {//�Ҳ����Ƶ��մ������Ҳ�first��ȥ���մ�����������ټ����󲿵�follow��
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

size_t Table::get_key_index(const std::unordered_map<std::string, int>& data, const std::string& key) const//����
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
