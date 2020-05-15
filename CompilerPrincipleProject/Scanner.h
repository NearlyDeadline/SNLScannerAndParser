#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include<string>
#include<fstream> 
#define BUFLEN 256

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
	string Sem;   //������Ϣ
	LexType Lex; //�ʷ���Ϣ
}reservedWords[21] = { {"program",PROGRAM},{"type",TYPE},{"var",VAR},
	{"procedure",PROCEDURE},{"begin",BEGIN},{"end",END1},{"array",ARRAY},
	{"of",OF},{"record",RECORD},{"if",IF},{"then",THEN},{"else",ELSE},{"fi",FI},
	{"while",WHILE},{"do",DO},{"endwh",ENDWH},{"read",READ},{"write",WRITE},
	{"return",RETURN1},{"integer",INTEGER},{"char",CHAR1} };//������



struct Token {			//token�Ľṹ
	int Lineshow;
	struct Word word;
};


typedef struct node			//tokenList�Ľڵ�
{
	Token Token;      //����
	struct node* nextToken; //ָ����һ�����ʵ�ָ��
	struct node* preToken;
} ListNode;

typedef enum				//״̬������
{
	START, INASSIGN, INRANGE, INCOMMENT, INNUM, INID, INCHAR, DONE
}StateType;

class Scanner {
public:
	Scanner() {
		//Init();
	}
	bool IsSeparater(char ch);

	bool IsOperator(char ch);

	bool IsKeyWord(string ch);

	bool IsFilter(char ch);

	bool IsLetter(char ch);

	bool IsDigit(char ch);

	Token TokenList[10000];
	LexType GetTokenType(string charList);
	string toString(int lextype);
	//void Init();
	void getTokenList(FILE* fpin);
	//void ungetNextChar();
	//int getNextChar();
	Word reservedLookup(string s);
	//void ChainToFile(ListNode * filehead);
	void printTokenList();
};
