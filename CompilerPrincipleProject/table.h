#pragma once

#include <string>
#include <vector>
#include <map>

class Production {//����ʽ���ݽṹ
public:
	std::string left;//��
	std::vector<std::string> right;//�Ҳ�
};

class Table {//LL1������
public:
	int getProductionIndex(const std::string& nonTerminal, const std::string& terminal);
	//���ݵ�ǰ���ռ���nonTerminal���������terminal������Ӧѡ��Ĳ���ʽ��ţ���0��ʼ��
	Table(const std::string& filepath);
	//���ݲ���ʽ�ļ�����predict��
	int operator()(const std::string& nonTerminal, const std::string& terminal) {
		return getProductionIndex(nonTerminal, terminal);
	}
	//���غ�����������������ڴ����д
private:
	void CreateProductionsAndNonTerminals(const std::string& filepath);//���ļ���ȡ���������ʽ�ͷ��ռ������ڴ��б���
	void CreateTerminals(const int& count = 42);//����Scanner.h�е�ö�٣�����Token����������ռ������ڴ��б���
	void InitializeTable();//����LL(1)������
	std::vector<string> GetFirst(const Production& pro);//����first���ϣ��������ʽ������һ�������ռ������Ƶ�����
	std::vector<string> GetFollow(const Production& pro);//����follow���ϣ��������ʽ������һ�������ռ������Ƶ�����
	std::vector<string> GetPredict(const Production& pro);//����predict���ϣ��������ʽ������һ�������ռ������Ƶ�����
	std::vector<std::vector<int>> table;//������
	std::vector<Production> productions;//�����ķ����в���ʽ
	std::map<std::string, int> nonTerminals;//�����ķ����з��ռ���
	std::map<std::string, int> terminals;//�����ķ������ռ����������Token�����ķ�����ʽ���Եģ�
};
