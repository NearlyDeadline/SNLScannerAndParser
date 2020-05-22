#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include "table.h"

using namespace std;

class Stringshed
{
public:
    string  shed[100];
    int     shedpoint;
public:
    Stringshed()
    {
        shedpoint = -1;
        for (int i = 1;i < 100;i++)
            shed[i] = "";
    }
    void push(string s)
    {
        shedpoint++;
        shed[shedpoint] = s;
    }
    void pop()//没有进行检查栈顶指针的检查
    {
        shedpoint--;
    }
    void print()
    {
        cout << "shedpoint:" << shedpoint << endl;
        cout << "shed:" << endl;
        for (int i = shedpoint;i >= 0;i--)
            cout << shed[i] << endl;
    }
    string  gethead()//没有进行栈顶指针的检查
    {
        return shed[shedpoint];
    }
};

extern void split(const string& s, vector<string>& tokens, const string& delimiters);
void driver(const Table& table, const string& tokenListFile);
void gettoken(string&, string& s,string &concrete, ifstream& tokenList);//还有一个文件
int isVT(string s);
int isVN(string s);
void predict(int pnum, Stringshed& shed);
void process1(Stringshed& shed);
void process2(Stringshed& shed);
void process3(Stringshed& shed);
void process4(Stringshed& shed);
void process5(Stringshed& shed);
void process6(Stringshed& shed);
void process7(Stringshed& shed);
void process8(Stringshed& shed);
void process9(Stringshed& shed);
void process10(Stringshed& shed);
void process11(Stringshed& shed);
void process12(Stringshed& shed);
void process13(Stringshed& shed);
void process14(Stringshed& shed);
void process15(Stringshed& shed);
void process16(Stringshed& shed);
void process17(Stringshed& shed);
void process18(Stringshed& shed);
void process19(Stringshed& shed);
void process20(Stringshed& shed);
void process21(Stringshed& shed);
void process22(Stringshed& shed);
void process23(Stringshed& shed);
void process24(Stringshed& shed);
void process25(Stringshed& shed);
void process26(Stringshed& shed);
void process27(Stringshed& shed);
void process28(Stringshed& shed);
void process29(Stringshed& shed);
void process30(Stringshed& shed);
void process31(Stringshed& shed);
void process32(Stringshed& shed);
void process33(Stringshed& shed);
void process34(Stringshed& shed);
void process35(Stringshed& shed);
void process36(Stringshed& shed);
void process37(Stringshed& shed);
void process38(Stringshed& shed);
void process39(Stringshed& shed);
void process40(Stringshed& shed);
void process41(Stringshed& shed);
void process42(Stringshed& shed);
void process43(Stringshed& shed);
void process44(Stringshed& shed);
void process45(Stringshed& shed);
void process46(Stringshed& shed);
void process47(Stringshed& shed);
void process48(Stringshed& shed);
void process49(Stringshed& shed);
void process50(Stringshed& shed);
void process51(Stringshed& shed);
void process52(Stringshed& shed);
void process53(Stringshed& shed);
void process54(Stringshed& shed);
void process55(Stringshed& shed);
void process56(Stringshed& shed);
void process57(Stringshed& shed);
void process58(Stringshed& shed);
void process59(Stringshed& shed);
void process60(Stringshed& shed);
void process61(Stringshed& shed);
void process62(Stringshed& shed);
void process63(Stringshed& shed);
void process64(Stringshed& shed);
void process65(Stringshed& shed);
void process66(Stringshed& shed);
void process67(Stringshed& shed);
void process68(Stringshed& shed);
void process69(Stringshed& shed);
void process70(Stringshed& shed);
void process71(Stringshed& shed);
void process72(Stringshed& shed);
void process73(Stringshed& shed);
void process74(Stringshed& shed);
void process75(Stringshed& shed);
void process76(Stringshed& shed);
void process77(Stringshed& shed);
void process78(Stringshed& shed);
void process79(Stringshed& shed);
void process80(Stringshed& shed);
void process81(Stringshed& shed);
void process82(Stringshed& shed);
void process83(Stringshed& shed);
void process84(Stringshed& shed);
void process85(Stringshed& shed);
void process86(Stringshed& shed);
void process87(Stringshed& shed);
void process88(Stringshed& shed);
void process89(Stringshed& shed);
void process90(Stringshed& shed);
void process91(Stringshed& shed);
void process92(Stringshed& shed);
void process93(Stringshed& shed);
void process94(Stringshed& shed);
void process95(Stringshed& shed);
void process96(Stringshed& shed);
void process97(Stringshed& shed);
void process98(Stringshed& shed);
void process99(Stringshed& shed);
void process100(Stringshed& shed);
void process101(Stringshed& shed);
void process102(Stringshed& shed);
void process103(Stringshed& shed);
void process104(Stringshed& shed);