#pragma once

#include <string>
#include <vector>

class Production {//����ʽ���ݽṹ
public:
	std::string left;//��
	std::vector<std::string> right;//�Ҳ�
};

extern std::vector<Production> productions;//�����ķ����в���ʽ

class Table {//LL1������
public:
	int getProductionIndex(std::string nonTerminal, std::string terminal);
	//���ݵ�ǰ���ռ���nonTerminal���������terminal������Ӧѡ��Ĳ���ʽ��ţ���0��ʼ��
};
