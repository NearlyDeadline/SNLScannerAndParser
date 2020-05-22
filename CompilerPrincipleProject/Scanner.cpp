#include"Scanner.h"

//判断是否为数字
bool Scanner::IsDigit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

//判断是否为字母
bool Scanner::IsLetter(char ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

//过滤符
bool Scanner::IsFilter(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
}

//关键字
bool Scanner::IsKeyWord(string ch)
{
	for (int i = 0; i < 21; i++)
	{
		if (ch == reservedWords[i].Sem)
		{
			return true;
		}
	}
	return false;
}

//运算符
bool Scanner::IsOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '=');
}

//分隔符
bool Scanner::IsSeparater(char ch)
{
	return (ch == ';' || ch == ',' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '.' || ch == '\'' || ch == ':');
}

//char转string中间函数，不必在意
string convert(char ch) {
	string s = "";
	s += ch;
	return s;
}


//得到Token的类型（）
LexType Scanner::GetTokenType(string charList)
{
	LexType tokenType;
	if (charList == "+") {
		tokenType = PLUS;
	}
	else if (charList == "-") {
		tokenType = MINUS;
	}
	else if (charList == "*") {
		tokenType = TIMES;
	}
	else if (charList == "/") {
		tokenType = OVER;
	}
	else if (charList == "(") {
		tokenType = LPAREN;
	}
	else if (charList == ")") {
		tokenType = RPAREN;
	}
	else if (charList == ".") {
		tokenType = DOT;
	}
	else if (charList == "[") {
		tokenType = LMIDPAREN;
	}
	else if (charList == "]") {
		tokenType = RMIDPAREN;
	}
	else if (charList == ";") {
		tokenType = SEMI;
	}
	else if (charList == ":") {
		tokenType = COLON;
	}
	else if (charList == ",") {
		tokenType = COMMA;
	}
	else if (charList == "<") {
		tokenType = LT;
	}
	else if (charList == "=") {
		tokenType = EQ;
	}
	else if (charList == ":=") {
		tokenType = ASSIGN;
	}
	else if (charList == "..") {
		tokenType = UNDERANGE;
	}
	else if (charList == "EOF") {
		tokenType = ENDFILE;
	}
	else if (charList == "'") {
		tokenType = CHARC;
	}
	else {
		tokenType = ERROR;
	}
	return tokenType;
}

//保留字查找
Word Scanner::reservedLookup(string s)
{
	for (int i = 0; i < 21; i++)
	{
		if (reservedWords[i].Sem == s)
			return reservedWords[i];
	}
}


//读取源文件，获得Token，保存在TokenList里
void Scanner::getTokenList()
{
	FILE* fpin = nullptr;
	auto er = fopen_s(&fpin, this->codeFile.c_str(), "r");
	if (er != 0) {
		cout << "源代码文件无法打开" << endl;
		return;
	}
	int Lineshow = 1;//确定起始行数

	Token* temptoken;//Tokenlist的生成节点

	char ch = fgetc(fpin);
	string arr = "";
	while (ch != EOF) {

		//判断过滤符
		if (IsFilter(ch))
		{
			if (ch == '\n')
				Lineshow += 1;
			ch = fgetc(fpin);
		}

		//判断标识符或关键字
		else if (IsLetter(ch))
		{
			arr = "";
			arr = arr + ch;
			ch = fgetc(fpin);
			while (IsLetter(ch) || IsDigit(ch))
			{
				arr = arr + ch;
				ch = fgetc(fpin);
			}
			if (IsKeyWord(arr))//关键字
			{
				temptoken = new Token(Lineshow,reservedLookup(arr));
				TokenList.push_back(temptoken);
			}
			else//标识符
			{
				temptoken = new Token(Lineshow,Word(arr, ID));
				TokenList.push_back(temptoken);
			}
		}

		//判断运算符
		else if (IsOperator(ch))
		{
			LexType Lex = GetTokenType(convert(ch));
			temptoken = new Token(Lineshow, Word(convert(ch), Lex));
			TokenList.push_back(temptoken);
			ch = fgetc(fpin);
		}

		//判断分隔符
		else if (IsSeparater(ch))
		{
			arr = "";
			//去掉注释
			if (ch == '{')
			{
				while (ch != '}')
				{
					ch = fgetc(fpin);
					if (ch == '\n')
						Lineshow += 1;
				}
				ch = fgetc(fpin);
			}
			//判断数组下标限界符
			else if (ch == '.')
			{
				arr += ch;
				if ((ch = fgetc(fpin)) == '.')
				{

					arr += ch;
					temptoken = new Token(Lineshow, Word(arr, GetTokenType(arr)));
					TokenList.push_back(temptoken);
					ch = fgetc(fpin);
				}
				else
				{
					temptoken = new Token(Lineshow, Word(arr, GetTokenType(arr)));
					TokenList.push_back(temptoken);
				}
			}
			//判断字符串
			else if (ch == '\'')
			{
				char tempchar = ch;
				while ((ch = fgetc(fpin)) != '\'')
				{
					arr += ch;
				}
				temptoken = new Token(Lineshow, Word(arr, GetTokenType(convert(tempchar))));
				TokenList.push_back(temptoken);
				ch = fgetc(fpin);
			}
			//判断双字符分解符
			else if (ch == ':')
			{
				arr += ch;
				if ((ch = fgetc(fpin)) == '=')
				{
					arr += ch;
					temptoken = new Token(Lineshow, Word(arr, GetTokenType(arr)));
					TokenList.push_back(temptoken);
					ch = fgetc(fpin);
				}
				else
				{
					temptoken = new Token(Lineshow, Word(arr, GetTokenType(arr)));
					TokenList.push_back(temptoken);
				}
			}
			else
			{
				temptoken = new Token(Lineshow, Word(convert(ch), GetTokenType(convert(ch))));
				TokenList.push_back(temptoken);
				ch = fgetc(fpin);
			}
		}

		//判断无符号整数
		else if (IsDigit(ch))
		{
			arr = "";
			arr += ch;
			ch = fgetc(fpin);
			while (IsDigit(ch) || IsLetter(ch))
			{
				arr += ch;
				ch = fgetc(fpin);
			}
			int count = 0; //判断字符串是否都由数字组成
			for (int i = 0; i < arr.length(); i++)
			{
				count++;
				if (IsLetter(arr[i]))
				{
					temptoken = new Token(Lineshow, Word(arr, ERROR));
					TokenList.push_back(temptoken);
					break;
				}
			}
			if (count == arr.length()) {
				temptoken = new Token(Lineshow, Word(arr, INTC));
				TokenList.push_back(temptoken);
			}
		}

		//未知符号
		else
		{
			temptoken = new Token(Lineshow, Word(convert(ch), GetTokenType(convert(ch))));
			TokenList.push_back(temptoken);
			ch = fgetc(fpin);
		}
	}
	temptoken = new Token(Lineshow, Word(convert(ch), ENDFILE));
	TokenList.push_back(temptoken);
}


//将LexType以string形式返回
string Scanner::toString(int lextype) {
	switch (lextype) {
	case 0:return "ENDFILE";
	case 1:return "ERROR";
		/*保留字*/
	case 2:return "PROGRAM";
	case 3:return "PROCEDURE";
	case 4:return "TYPE";
	case 5:return "VAR";
	case 6:return "IF";
	case 7:return "THEN";
	case 8:return "ELSE";
	case 9:return "FI";
	case 10:return "WHILE";
	case 11:return "DO";
	case 12:return "ENDWH";
	case 13:return "BEGIN";
	case 14:return "END";
	case 15:return "READ";
	case 16:return "WRITE";
	case 17:return "ARRAY";
	case 18:return "OF";
	case 19:return "RECORD";
	case 20:return "RETURN";
	case 21:return "INTEGER";
	case 22:return "CHAR";
		/*多字符单词符号*/
	case 23:return "ID";
	case 24:return "INTC";
	case 25:return "CHARC";

		/*特殊符号*/
	case 26:return "ASSIGN";
	case 27:return "EQ";
	case 28:return "LT";
	case 29:return "PLUS";
	case 30:return "MINUS";
	case 31:return "TIMES";
	case 32:return "OVER";
	case 33:return "LPAREN";
	case 34:return "RPAREN";
	case 35:return "DOT";
	case 36:return "COLON";
	case 37:return "SEMI";
	case 38:return "COMMA";
	case 39:return "LMIDPAREN";
	case 40:return "RMIDPAREN";
	case 41:return "UNDERANGE";
	}
}


//打印TokenList的内容，最后有空格行！！
void Scanner::printTokenList(const string& tokenListFile) {
	int i = 0;
	ofstream mycout0(tokenListFile);	//输出的文件位置
	if (!mycout0)
	{
		cout << "文件不能打开" << endl;
		return;
	}
	while (TokenList.at(i)->word.Lex != ENDFILE)
	{
		mycout0 << setw(4) << std::left << TokenList.at(i)->Lineshow << std::left << setw(25) << toString(TokenList.at(i)->word.Lex) << TokenList.at(i)->word.Sem << endl;
		i++;
	}
	mycout0 << TokenList.at(i)->Lineshow << " " << toString(TokenList.at(i)->word.Lex) << " " << TokenList.at(i)->word.Sem << endl;
	mycout0.close();
}