#pragma once
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

class Production {//产生式数据结构
public:
	std::string left;//左部
	std::vector<std::string> right;//右部
	std::set<std::string> predict_set;//predict集合
};

class Table {//LL1分析表
public:
	size_t get_production_index(const std::string& non_terminal, const std::string& terminal) const;
	//根据当前非终极符non_terminal和输入符号terminal，返回应选择的产生式序号（从0开始）

	Table(const std::string& filepath);
	//根据产生式文件构造predict集

	size_t operator()(const std::string& non_terminal, const std::string& terminal) const {
		return get_production_index(non_terminal, terminal);
	}
	//重载函数调用运算符，便于代码编写

private:
	void read_productions_nonterminals(const std::string& filepath);
	//从文件filepath读取，保存产生式和非终极符到内存中备用

	void create_terminals();
	//从产生式集合production读取不是非终极符的文法符号,作为终极符放入内存备用

	void initialize_table();
	//创建LL(1)分析表

	std::set<std::string> get_first_set(const std::string & symbol) const;
	//计算first集合，传入文法符号symbol，返回一个保存终极符名称的集合

	std::set<std::string> get_first_set(const std::vector<std::string>& symbols) const;
	//计算first集合,传入许多个文法符号symbols,返回一个保存终极符名称的集合

	std::vector<std::set<std::string>> get_follow_sets() const;
	//计算follow集合，返回全部非终极符的follow集合

	std::set<std::string> get_predict_set(const Production& pro, const std::vector<std::set<std::string>>& first_sets, 
		const std::vector<std::set<std::string>>& follow_sets) const;
	//计算predict集合，传入产生式pro，文法所有First集合first_sets，文法所有Follow集合follow_sets，返回一个保存终极符名称的集合

	bool is_nonterminal(const std::string& ch) const;
	//判断文法符号ch是否为非终极符

	bool is_terminal(const std::string& ch) const;
	//判断文法符号ch是否为终极符

	size_t get_first_terminal_index(const Production& pro) const;
	//返回产生式右部首个终极符下标，若全为非终极符则返回pro.size()

	size_t get_key_index(const std::unordered_map<std::string, int>& data, const std::string& key) const;
	//输入数组data和待查键值key，返回这个键值的下标，若找不到则返回data.size()

	std::vector<std::vector<int>> table;//分析表
	std::vector<Production> productions;//保存文法所有产生式
	std::unordered_map<std::string, int> nonterminals;//保存文法所有非终极符
	std::unordered_map<std::string, int> terminals;//保存文法所有终极符（相对于Token化的文法产生式而言的）
};
