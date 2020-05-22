#include "driver.h"

void driver()
{
    Table table = CreatTable();//生成语法分析表
    Stringshed anashed;//生成一个语法分析栈
    anashed.push("#");
    anashed.push("Program");
    ifstream  tokenList("F:\\编译原理课设\\CompilerPrincipleProject\\correct_tokenlist.txt");//此处打开张磊的TokenList
    string input = "";
    string lineno = "";
    string concrete = "";
    gettoken(lineno, input,concrete,tokenList);//获得非终极符，和对应的行号
    int con = 1;
    int countt = 1;
    while (con == 1 && anashed.shedpoint != -1)//无错误产生且分析栈栈非空
    {
        if (isVN(anashed.gethead()) == 1)//非终结符
        {
            int pnum = table.get_production_index(anashed.gethead(), input);
            if (pnum != 0)
            {
                pridict(pnum, anashed);
                cout << countt << "使用产生式" << pnum << endl;countt++;
            }
            else
            {
                con = 0;
                cout << "there exsit a error in line:" << lineno << ",concrete:"<<concrete<<",cause:no matchable produce exp" << endl;
            }
        }
        else if (isVT(anashed.gethead()))//终结符
        {
            if (anashed.gethead() == input)
            {
                anashed.pop();
                gettoken(lineno, input, concrete,tokenList);
            }
            else
            {
                con = 0;
                cout << "there exsit a error in line:" << lineno << ",concrete:" << concrete << ",cause:fail to match VT" << endl;
            }
        }

    }
    if (anashed.shedpoint == -1 && input == "eend")
    {
        cout << "legal sentence!" << endl;
    }
    else
    {
        cout << "error:there exists shed that was not empty!" << endl;
    }
    tokenList.close();
}

Table CreatTable()
{
    Table table("F:\\编译原理课设\\CompilerPrincipleProject\\productions.txt");
    return table;

}
int isVN(string s)
{
    if (s == "Program"     ||s == "ProgramHead"   ||s == "ProgramName"  ||s == "DeclarePart"     ||s == "TypeDecpart"||
        s == "TypeDec"     ||s == "TypeDecList"   ||s == "TypeDecMore"  ||s == "TypeId"          ||s == "TypeDef"|| 
        s == "BaseType"    ||s == "StructureType" ||s == "ArrayType"    ||s == "Low"             ||s == "Top"||
        s == "RecType"     ||s == "FieldDecList"  ||s == "FieldDecMore" ||s == "IdList"          ||s == "IdMore"||
        s == "VarDecpart"  ||s == "VarDec"        ||s == "VarDecList"   ||s == "VarDecMore"      ||s == "VarIdList"||
        s == "VarIdMore"   ||s == "ProcDecpart"   ||s == "ProcDec"      ||s == "ProcDecMore"     ||s == "ProcName"||
        s == "ParamList"   ||s == "ParamDecList"  ||s == "ParamMore"    ||s == "Param"           ||s == "FormList"||
        s == "FidMore"     ||s == "ProcDecPart"   ||s == "ProcBody"     ||s == "ProgramBody"     ||s == "StmList" || 
        s == "StmMore"     ||s == "Stm"           ||s == "AssCall"      ||s == "AssignmentRest"  ||s == "ConditionalStm" || 
        s == "LoopStm"     ||s == "InputStm"      ||s == "Invar"        ||s == "OutputStm"       ||s == "ReturnStm" || 
        s == "CallStmRest" ||s == "ActParamList"  ||s == "ActParamMore" ||s == "RelExp"          ||s == "OtherRelE" ||
        s == "Exp"         ||s == "OtherTerm"     ||s == "Term"         ||s == "OtherFactor"     ||s == "Factor" || 
        s == "Variable"    ||s == "VariMore"      ||s == "FieldVar"     ||s == "FieldVarMore"    ||s == "CmpOp" || 
        s == "AddOp"       ||s == "MultOp")
        return 1;
    else
        return 0;
}


int isVT(string s)
{
    if (s == "PROGRAM"   || s == "ID"         || s == "$"      ||  s == "TYPE"        || s == "EQ" ||
        s == "SEMI"      || s == "INTEGER"    || s == "CHAR"   ||  s == "ARRAY"      || s == "LMIDPAREN"||
        s == "UNDERANGE" || s == "RMIDPAREN"  || s == "OF"     ||  s == "INTC"       || s == "RECORD"||
        s == "END"       || s == "COMMA"      || s == "VAR"    ||  s == "PROCEDURE"  || s == "LPAREN"||
        s == "RPAREN"    || s == "BEGIN"      || s == "ASSIGN" ||  s == "IF"         || s == "THEN"||
        s == "ELSE"      || s == "FI"         || s == "WHILE"  ||  s == "DO"         || s == "ENDWH"||
        s == "READ"      || s == "WRITE"      || s == "RETURN" ||  s == "DOT"        || s == "LT"||
        s == "PLUS"      || s == "MINUS"      || s == "TIMES"  ||  s == "OVER"       || s == "#")
        return 1;
    else
        return 0;
}
void pridict(int k, Stringshed& shed)
{
    if (k == 1)process1(shed);if (k == 2)process2(shed);if (k == 3)process3(shed);if (k == 4)process4(shed);if (k == 5)process5(shed);
    if (k == 6)process6(shed);if (k == 7)process7(shed);if (k == 8)process8(shed);if (k == 9)process9(shed);if (k == 10)process10(shed);
    if (k == 11)process11(shed);if (k == 12)process12(shed);if (k == 13)process13(shed);if (k == 14)process14(shed);if (k == 15)process15(shed);
    if (k ==16 )process16(shed);if (k == 17)process17(shed);if (k ==18 )process18(shed);if (k == 19)process19(shed);if (k ==20 )process20(shed);
    if (k == 21)process21(shed);if (k == 22)process22(shed);if (k == 23)process23(shed);if (k == 24)process24(shed);if (k == 25)process25(shed);
    if (k == 26)process26(shed);if (k == 27)process27(shed);if (k == 28)process28(shed);if (k == 29)process29(shed);if (k == 30)process30(shed);
    if (k == 31)process31(shed);if (k == 32)process32(shed);if (k == 33)process33(shed);if (k == 34)process34(shed);if (k == 35)process35(shed);
    if (k == 36)process36(shed);if (k == 37)process37(shed);if (k == 38)process38(shed);if (k == 39)process39(shed);if (k == 40)process40(shed);
    if (k == 41)process41(shed);if (k == 42)process42(shed);if (k == 43)process43(shed);if (k == 44)process44(shed);if (k == 45)process45(shed);
    if (k == 46)process46(shed);if (k == 47)process47(shed);if (k == 48)process48(shed);if (k == 49)process49(shed);if (k == 50)process50(shed);
    if (k == 51)process51(shed);if (k == 52)process52(shed);if (k == 53)process53(shed);if (k == 54)process54(shed);if (k == 55)process55(shed);
    if (k == 56)process56(shed);if (k == 57)process57(shed);if (k == 58)process58(shed);if (k == 59)process59(shed);if (k == 60)process60(shed);
    if (k == 61)process61(shed);if (k == 62)process62(shed);if (k == 63)process63(shed);if (k == 64)process64(shed);if (k == 65)process65(shed);
    if (k == 66)process66(shed);if (k == 67)process67(shed);if (k == 68)process68(shed);if (k == 69)process69(shed);if (k == 70)process70(shed);
    if (k == 71)process71(shed);if (k == 72)process72(shed);if (k == 73)process73(shed);if (k == 74)process74(shed);if (k == 75)process75(shed);
    if (k == 76)process76(shed);if (k == 77)process77(shed);if (k == 78)process78(shed);if (k == 79)process79(shed);if (k == 80)process80(shed);
    if (k == 81)process81(shed);if (k == 82)process82(shed);if (k ==83)process83(shed);if (k == 84)process84(shed);if (k == 85)process85(shed);
    if (k == 86)process86(shed);if (k == 87)process87(shed);if (k == 88)process88(shed);if (k == 89)process89(shed);if (k == 90)process90(shed);
    if (k == 91)process91(shed);if (k == 92)process92(shed);if (k == 93)process93(shed);if (k == 94)process94(shed);if (k == 95)process95(shed);
    if (k == 96)process96(shed);if (k == 97)process97(shed);if (k == 98)process98(shed);if (k == 99)process99(shed);if (k == 100)process100(shed);
    if (k == 101)process101(shed);if (k == 102)process102(shed);if (k == 103)process103(shed);if (k == 104)process104(shed);

}

void gettoken(string& lineno, string& input,string& concrete,ifstream& tokenList)//需要修改读取文件的方式
{
    //void split(const string& s, vector<string>& tokens, const string& delimiters = " ")
    string s = "";
    vector<string> vec;
    if (input == "#")
    {
        input = "eend";
        return;
    }
    if (tokenList.eof() != 1)
    {
        getline(tokenList, s);
        split(s, vec," ");
        input = vec[1];
        lineno= vec[0];
        if (vec.size() == 3)
            concrete=vec[2];
    }
    else
    {
        input = "#";return;
    }
    
}
void process1(Stringshed& shed)
{
    shed.pop();
    shed.push("ProgramBody");
    shed.push("DeclarePart");
    shed.push("ProgramHead");

}
void process2(Stringshed& shed)
{
    shed.pop();
    shed.push("ProgramName");
    shed.push("PROGRAM");
}
void process3(Stringshed& shed)
{
    shed.pop();
    shed.push("ID");
}
void process4(Stringshed& shed)
{
    shed.pop();
    shed.push("ProcDecpart");
    shed.push("VarDecpart");
    shed.push("TypeDecpart");
}
void process5(Stringshed& shed)
{
    shed.pop();
}
void process6(Stringshed& shed)
{
    shed.pop();
    shed.push("TypeDec");
}
void process7(Stringshed& shed)
{
    shed.pop();
    shed.push("TypeDecList");
    shed.push("TYPE");
}
void process8(Stringshed& shed)
{
    shed.pop();
    shed.push("TypeDecMore");
    shed.push("SEMI");
    shed.push("TypeDef");
    shed.push("EQ");
    shed.push("TypeId");
}
void process9(Stringshed& shed)
{
    shed.pop();
}
void process10(Stringshed& shed)
{
    shed.pop();
    shed.push("TypeDecList");
}
void process11(Stringshed& shed)
{
    shed.pop();
    shed.push("ID");
}
void process12(Stringshed& shed)
{
    shed.pop();
    shed.push("BaseType");
}
void process13(Stringshed& shed)
{
    shed.pop();
    shed.push("StructureType");
}
void process14(Stringshed& shed)
{
    shed.pop();
    shed.push("ID");
}
void process15(Stringshed& shed)
{
    shed.pop();
    shed.push("INTEGER");
}
void process16(Stringshed& shed)
{
    shed.pop();
    shed.push("CHAR");
}
void process17(Stringshed& shed)
{
    shed.pop();
    shed.push("ArrayType");
}
void process18(Stringshed& shed)
{
    shed.pop();
    shed.push("RecType");
}
void process19(Stringshed& shed)
{
    shed.pop();
    shed.push("BaseType");
    shed.push("OF");
    shed.push("RMIDPAREN");
    shed.push("Top");
    shed.push("UNDERANGE");
    shed.push("Low");
    shed.push("LMIDPAREN");
    shed.push("ARRAY");
}
void process20(Stringshed& shed)
{
    shed.pop();
    shed.push("INTC");
}
void process21(Stringshed& shed)
{
    shed.pop();
    shed.push("INTC");
}
void process22(Stringshed& shed)
{
    shed.pop();
    shed.push("END");
    shed.push("FieldDecList");
    shed.push("RECORD");
}
void process23(Stringshed& shed)
{
    shed.pop();
    shed.push("FieldDecMore");
    shed.push("SEMI");
    shed.push("IdList");
    shed.push("BaseType");
}
void process24(Stringshed& shed)
{
    shed.pop();
    shed.push("FieldDecMore");
    shed.push("SEMI");
    shed.push("IdList");
    shed.push("ArrayType");
}
void process25(Stringshed& shed)
{
    shed.pop();
}
void process26(Stringshed& shed)
{
    shed.pop();
    shed.push("FieldDecList");
}
void process27(Stringshed& shed)
{
    shed.pop();
    shed.push("IdMore");
    shed.push("ID");
}
void process28(Stringshed& shed)
{
    shed.pop();
}
void process29(Stringshed& shed)
{
    shed.pop();
    shed.push("IdList");
    shed.push("COMMA"); 
}
void process30(Stringshed& shed)
{
    shed.pop();
}
void process31(Stringshed& shed)
{
    shed.pop();
    shed.push("VarDec");
}
void process32(Stringshed& shed)
{
    shed.pop();
    shed.push("VarDecList");
    shed.push("VAR");
}
void process33(Stringshed& shed)
{
    shed.pop();
    shed.push("VarDecMore");
    shed.push("SEMI");
    shed.push("VarIdList");
    shed.push("TypeDef");
}
void process34(Stringshed& shed)
{
    shed.pop();
}
void process35(Stringshed& shed)
{
    shed.pop();
    shed.push("VarDecList");
}
void process36(Stringshed& shed)
{
    shed.pop();
    shed.push("VarIdMore");
    shed.push("ID");
}
void process37(Stringshed& shed)
{
    shed.pop();
}
void process38(Stringshed& shed)
{
    shed.pop();
    shed.push("VarIdList");
    shed.push("COMMA");
}
void process39(Stringshed& shed)
{
    shed.pop();
}
void process40(Stringshed& shed)
{
    shed.pop();
    shed.push("ProcDec");
}
void process41(Stringshed& shed)
{
    shed.pop();
    shed.push("ProcDecMore");
    shed.push("ProcBody");
    shed.push("ProcDecPart");
    shed.push("SEMI");
    shed.push("RPAREN");
    shed.push("ParamList");
    shed.push("LPAREN");
    shed.push("ProcName");
    shed.push("PROCEDURE");
}
void process42(Stringshed& shed)
{
    shed.pop();
}
void process43(Stringshed& shed)
{
    shed.pop();
    shed.push("ProcDec");
}
void process44(Stringshed& shed)
{
    shed.pop();
    shed.push("ID");
}
void process45(Stringshed& shed)
{
    shed.pop();
}
void process46(Stringshed& shed)
{
    shed.pop();
    shed.push("ParamDecList");
}
void process47(Stringshed& shed)
{
    shed.pop();
    shed.push("ParamMore");
    shed.push("Param");
}
void process48(Stringshed& shed)
{
    shed.pop();
}
void process49(Stringshed& shed)
{
    shed.pop();
    shed.push("ParamDecList");
    shed.push("SEMI");
}
void process50(Stringshed& shed)
{
    shed.pop();
    shed.push("FormList");
    shed.push("TypeDef"); 
}
void process51(Stringshed& shed)
{
    shed.pop();
    shed.push("FormList");
    shed.push("TypeDef");
    shed.push("VAR");
}
void process52(Stringshed& shed)
{
    shed.pop();
    shed.push("FidMore");
    shed.push("ID");
}
void process53(Stringshed& shed)
{
    shed.pop();
}
void process54(Stringshed& shed)
{
    shed.pop();
    shed.push("FormList");
    shed.push("COMMA");
}
void process55(Stringshed& shed)
{
    shed.pop();
    shed.push("DeclarePart");
}
void process56(Stringshed& shed)
{
    shed.pop();
    shed.push("ProgramBody");
}
void process57(Stringshed& shed)
{
    shed.pop();
    shed.push("END");
    shed.push("StmList");
    shed.push("BEGIN");
}
void process58(Stringshed& shed)
{
    shed.pop();
    shed.push("StmMore");
    shed.push("Stm");
}
void process59(Stringshed& shed)
{
    shed.pop();
}
void process60(Stringshed& shed)
{
    shed.pop();
    shed.push("StmList");
    shed.push("SEMI");
}
void process61(Stringshed& shed)
{
    shed.pop();
    shed.push("ConditionalStm");
}
void process62(Stringshed& shed)
{
    shed.pop();
    shed.push("LoopStm");
}
void process63(Stringshed& shed)
{
    shed.pop();
    shed.push("InputStm");
}
void process64(Stringshed& shed)
{
    shed.pop();
    shed.push("OutputStm");
}
void process65(Stringshed& shed)
{
    shed.pop();
    shed.push("ReturnStm");
}
void process66(Stringshed& shed)
{
    shed.pop();
    shed.push("AssCall");
    shed.push("ID");
}
void process67(Stringshed& shed)
{
    shed.pop();
    shed.push("AssignmentRest");
}
void process68(Stringshed& shed)
{
    shed.pop();
    shed.push("CallStmRest");
}
void process69(Stringshed& shed)
{
    shed.pop();
    shed.push("Exp");
    shed.push("ASSIGN");
    shed.push("VariMore");
}
void process70(Stringshed& shed)
{
    shed.pop();
    shed.push("FI");
    shed.push("StmList");
    shed.push("ELSE");
    shed.push("StmList");
    shed.push("THEN");
    shed.push("RelExp");
    shed.push("IF");
}
void process71(Stringshed& shed)
{
    shed.pop();
    shed.push("ENDWH");
    shed.push("StmList");
    shed.push("DO");
    shed.push("RelExp");
    shed.push("WHILE");
}
void process72(Stringshed& shed)
{
    shed.pop();
    shed.push("RPAREN");
    shed.push("Invar");
    shed.push("LPAREN");
    shed.push("READ");
}
void process73(Stringshed& shed)
{
    shed.pop();
    shed.push("ID");
}
void process74(Stringshed& shed)
{
    shed.pop();
    shed.push("RPAREN");
    shed.push("Exp");
    shed.push("LPAREN");
    shed.push("WRITE");
}
void process75(Stringshed& shed)
{
    shed.pop();
    shed.push("RPAREN");
    shed.push("Exp");
    shed.push("LPAREN");
    shed.push("RETURN");
}
void process76(Stringshed& shed)
{
    shed.pop();
    shed.push("RPAREN");
    shed.push("ActParamList");
    shed.push("LPAREN");
}
void process77(Stringshed& shed)
{
    shed.pop();
}
void process78(Stringshed& shed)
{
    shed.pop();
    shed.push("ActParamMore");
    shed.push("Exp");  
}
void process79(Stringshed& shed)
{
    shed.pop();
}
void process80(Stringshed& shed)
{
    shed.pop();
    shed.push("ActParamList");
    shed.push("COMMA");
}
void process81(Stringshed& shed)
{
    shed.pop();
    shed.push("OtherRelE");
    shed.push("Exp");
}
void process82(Stringshed& shed)
{
    shed.pop();
    shed.push("Exp");
    shed.push("CmpOp");
}
void process83(Stringshed& shed)
{
    shed.pop();
    shed.push("OtherTerm");
    shed.push("Term");
}
void process84(Stringshed& shed)
{
    shed.pop();
}
void process85(Stringshed& shed)
{
    shed.pop();
    shed.push("Exp");
    shed.push("AddOp");
}
void process86(Stringshed& shed)
{
    shed.pop();
    shed.push("OtherFactor");
    shed.push("Factor");
}
void process87(Stringshed& shed)
{
    shed.pop();
}
void process88(Stringshed& shed)
{
    shed.pop();
    shed.push("Term");
    shed.push("MultOp");
}
void process89(Stringshed& shed)
{
    shed.pop();
    shed.push("RPAREN");
    shed.push("Exp");
    shed.push("LPAREN");
}
void process90(Stringshed& shed)
{
    shed.pop();
    shed.push("INTC");
}
void process91(Stringshed& shed)
{
    shed.pop();
    shed.push("Variable");
}
void process92(Stringshed& shed)
{
    shed.pop();
    shed.push("VariMore");
    shed.push("ID");
}
void process93(Stringshed& shed)
{
    shed.pop();
}
void process94(Stringshed& shed)
{
    shed.pop();
    shed.push("RMIDPAREN");
    shed.push("Exp");
    shed.push("LMIDPAREN");
}
void process95(Stringshed& shed)
{
    shed.pop();
    shed.push("FieldVar");
    shed.push("DOT");
}
void process96(Stringshed& shed)
{
    shed.pop();
    shed.push("FieldVarMore");
    shed.push("ID");
}
void process97(Stringshed& shed)
{
    shed.pop();
}
void process98(Stringshed& shed)
{
    shed.pop();
    shed.push("RMIDPAREN");
    shed.push("Exp");
    shed.push("LMIDPAREN");
}
void process99(Stringshed& shed)
{
    shed.pop();
    shed.push("LT");
}
void process100(Stringshed& shed)
{
    shed.pop();
    shed.push("EQ");
}
void process101(Stringshed& shed)
{
    shed.pop();
    shed.push("PLUS");
}
void process102(Stringshed& shed)
{
    shed.pop();
    shed.push("MINUS");
}
void process103(Stringshed& shed)
{
    shed.pop();
    shed.push("TIMES");
}
void process104(Stringshed& shed)
{
    shed.pop();
    shed.push("OVER");
}
