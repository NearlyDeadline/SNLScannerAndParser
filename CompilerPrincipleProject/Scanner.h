#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include<string>
#include<fstream> 
#include<vector>

using namespace std;
typedef enum
{
	ENDFILE, ERROR,
	PROGRAM, PROCEDURE, TYPE, VAR, IF,
	THEN, ELSE, FI, WHILE, DO, ENDWH,
	BEGIN, END1, READ, WRITE, ARRAY, OF,
	RECORD, RETURN1,
	INTEGER, CHAR1,
	ID, INTC, CHARC,
	ASSIGN, EQ, LT, PLUS, MINUS,
	TIMES, OVER, LPAREN, RPAREN, DOT,
	COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN,
	UNDERANGE
}LexType;

static struct Word {
	string Sem;   //语义信息
	LexType Lex; //词法信息
	Word(string sem, LexType lex) {
		Sem = sem;
		Lex = lex;
	}
	Word(){}
}reservedWords[21] = { {"program",PROGRAM},{"type",TYPE},{"var",VAR},
	{"procedure",PROCEDURE},{"begin",BEGIN},{"end",END1},{"array",ARRAY},
	{"of",OF},{"record",RECORD},{"if",IF},{"then",THEN},{"else",ELSE},{"fi",FI},
	{"while",WHILE},{"do",DO},{"endwh",ENDWH},{"read",READ},{"write",WRITE},
	{"return",RETURN1},{"integer",INTEGER},{"char",CHAR1} };//保留字



struct Token {			//token的结构
	int Lineshow;
	struct Word word;
	Token(int lineshow, struct Word w) {
		Lineshow = lineshow;
		word = w;
	}
	Token(){}
};


typedef enum				//状态的类型
{
	START, INASSIGN, INRANGE, INCOMMENT, INNUM, INID, INCHAR, DONE
}StateType;

class Scanner {
public:
	Scanner(const string& codeFile) {
		this->codeFile = codeFile;
	}
	bool IsSeparater(char ch);

	bool IsOperator(char ch);

	bool IsKeyWord(string ch);

	bool IsFilter(char ch);

	bool IsLetter(char ch);

	bool IsDigit(char ch);

	vector<Token*> TokenList;//TokenList的结构

	LexType GetTokenType(string charList);
	string toString(int lextype);
	void getTokenList();
	Word reservedLookup(string s);
	void printTokenList(const string& tokenListFile);
	string codeFile;
};
