// CompilerPrincipleProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "table.h"
#include "Scanner.h"
#include <fstream>
#include <iostream>
using std::ifstream;
using std::string;
using std::getline;
using std::vector;

void split(const string& s, vector<string>& tokens, const string& delimiters = " ") {
	tokens.clear();
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}
void CreateProductions(string filepath = "productions.txt") {
	ifstream file;
	file.open(filepath);
	if (!file.is_open()) {
		return;
	}
	Production pro;
	vector<string> str;
	vector<string> lines;
	string text;
	while (file >> text) {
		split(text, lines, "\n");
		for (auto i : lines) {
			split(i, str, ",");
			pro.left = str[0];
			for (size_t i = 1; i < str.size(); i++) {
				pro.right.push_back(str[i]);
			}
			productions.push_back(pro);
			pro.right.clear();
		}
	}
	file.close();
}
int main()
{
	FILE* fp = nullptr;
	fopen_s(&fp,"source1.txt", "r");
	Scanner scanner = Scanner();
	scanner.getTokenList(fp);
	scanner.printTokenList();
	fclose(fp);
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件