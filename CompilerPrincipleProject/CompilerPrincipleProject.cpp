// CompilerPrincipleProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "table.h"
#include "Scanner.h"

void split(const string& s, vector<string>& tokens, const string& delimiters = " ")
//分割字符串，s为待分割字符串，tokens为保存分割后的字符串的向量，delimiters为分隔符
{
	tokens.clear();
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}

int main()
{
	/*
	以下为LL(1)分析表示例代码：
	！！！
	确保项目 -> 属性 -> 生成事件 -> 生成后事件 -> 命令行中存在如下命令：
	xcopy $(ProjectDir)productions.txt $(TargetDir)
	否则将无法找到文法产生式文件
	！！！
	
	使用如下的方式构造LL(1)分析表，参数为文法产生式文件的路径名称，这里使用相对路径。
	Table table("productions.txt");
	
	使用如下的方式选择相应的文法产生式，传入的第一个参数为当前非终极符，第二个参数为当前输入符号。
	std::cout << table("Program", "PROGRAM");
	*/
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