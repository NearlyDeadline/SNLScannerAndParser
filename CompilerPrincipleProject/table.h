#pragma once
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

class Production {//����ʽ���ݽṹ
public:
	std::string left;//��
	std::vector<std::string> right;//�Ҳ�
	std::set<std::string> predict_set;//predict����
};

class Table {//LL1������
public:
	size_t get_production_index(const std::string& non_terminal, const std::string& terminal) const;
	//���ݵ�ǰ���ռ���non_terminal���������terminal������Ӧѡ��Ĳ���ʽ��ţ���0��ʼ��

	Table(const std::string& filepath);
	//���ݲ���ʽ�ļ�����predict��

	size_t operator()(const std::string& non_terminal, const std::string& terminal) const {
		return get_production_index(non_terminal, terminal);
	}
	//���غ�����������������ڴ����д

private:
	void read_productions_nonterminals(const std::string& filepath);
	//���ļ�filepath��ȡ���������ʽ�ͷ��ռ������ڴ��б���

	void create_terminals();
	//�Ӳ���ʽ����production��ȡ���Ƿ��ռ������ķ�����,��Ϊ�ռ��������ڴ汸��

	void initialize_table();
	//����LL(1)������

	std::set<std::string> get_first_set(const std::string & symbol) const;
	//����first���ϣ������ķ�����symbol������һ�������ռ������Ƶļ���

	std::set<std::string> get_first_set(const std::vector<std::string>& symbols) const;
	//����first����,���������ķ�����symbols,����һ�������ռ������Ƶļ���

	std::vector<std::set<std::string>> get_follow_sets() const;
	//����follow���ϣ�����ȫ�����ռ�����follow����

	std::set<std::string> get_predict_set(const Production& pro, const std::vector<std::set<std::string>>& first_sets, 
		const std::vector<std::set<std::string>>& follow_sets) const;
	//����predict���ϣ��������ʽpro���ķ�����First����first_sets���ķ�����Follow����follow_sets������һ�������ռ������Ƶļ���

	bool is_nonterminal(const std::string& ch) const;
	//�ж��ķ�����ch�Ƿ�Ϊ���ռ���

	bool is_terminal(const std::string& ch) const;
	//�ж��ķ�����ch�Ƿ�Ϊ�ռ���

	size_t get_first_terminal_index(const Production& pro) const;
	//���ز���ʽ�Ҳ��׸��ռ����±꣬��ȫΪ���ռ����򷵻�pro.size()

	size_t get_key_index(const std::unordered_map<std::string, int>& data, const std::string& key) const;
	//��������data�ʹ����ֵkey�����������ֵ���±꣬���Ҳ����򷵻�data.size()

	std::vector<std::vector<int>> table;//������
	std::vector<Production> productions;//�����ķ����в���ʽ
	std::unordered_map<std::string, int> nonterminals;//�����ķ����з��ռ���
	std::unordered_map<std::string, int> terminals;//�����ķ������ռ����������Token�����ķ�����ʽ���Եģ�
};
