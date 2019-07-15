#include<string>
#include "string.h"
#include <iostream>
#include<fstream>
#include<complex>
#include<algorithm>
#include<QtCore>
#include<vector>
#include<cmath>
#include <math.h>
#define PI 3.14159265
#define epsilon 0.00000000001
#define	FACTORIAL_INVALID_ARGUMENT 0
#define	LOGARITHM_INVALID_ARGUMENT 1
#define	DIVISION_INVALID_ARGUMENT 2
const char* errors[10] = {
    "Неправильный аргумент факториала",
    "Неправильный арумент логарифма",
    "Деление на ноль"
};
using namespace std;
typedef complex<double> Operand;
enum CommandType {
    Infix, Prefix, Postfix,None
};
bool is_zero(double a) {
    return !abs(a - DBL_EPSILON > 0);
}
bool is_zero(Operand a) {
    return (is_zero(a.imag()) && is_zero(a.real()));
}
class Expression_Unit;
class Command {
private:
    string name;
public:
    bool radian=false;
    virtual Operand execute(vector <Operand> &opz) = 0;
    unsigned short operandCount, priority;
    CommandType type;
    Command(string nameC){
        name=nameC;
    }
    ~Command(){
    }
    string showname() {
        return name;
    }
};
class Binary_Command :public Command {
protected:
    virtual Operand execute_bin(Operand a, Operand b) = 0;
public:
    Binary_Command(string nameC):Command (nameC) {
        operandCount = 2;
    }
    Operand execute(vector <Operand> &opz) {
        Operand operand1 = opz[opz.size() - 1];
        Operand operand2 = opz[opz.size() - 2];
        opz.erase(opz.begin() +(opz.size()-1));
        opz.erase(opz.begin() + (opz.size() - 1));
        return execute_bin(operand2, operand1);
    };
};
class Unary_Command :public Command {
protected:
    virtual Operand execute_un(Operand a) = 0;
public:
    Unary_Command(string nameC) :Command(nameC) {
        operandCount = 1;
    }
    Operand execute(vector <Operand> &opz) {
        Operand operand1 = opz[opz.size() - 1];
        opz.erase(opz.begin() + opz.size()-1);
        return execute_un(operand1);
    };
};
class Expression_Unit {
public:
    int place;
    string value;
    Operand operand;
    string type_unit;
    Command * command = 0;
    Expression_Unit() {
        type_unit = "";
    }
    void del() {
        if (command != 0) {
            delete command;
        }
    }
    //Expression_Unit(const Expression_Unit &) = default;
    //Expression_Unit& operator=(const Expression_Unit&) = default;
    /*~Expression_Unit(){
        if (command != 0) {
            delete command;
        }
    }*/
};
class Plus : public Binary_Command
{
public:
    Plus():Binary_Command("+") {
        priority = 1;
        type = CommandType::Infix;
    }
    Operand execute_bin(Operand operand1, Operand operand2) {
        return (operand1 + operand2);
    };
};
class Minus : public Binary_Command
{
public:
    Minus():Binary_Command("-") {
        priority = 1;
        type = CommandType::Infix;
    }
    Operand execute_bin(Operand operand1, Operand operand2) {
        return (operand1 - operand2);
    };
};
class Unar_Minus : public Unary_Command
{
public:
    Unar_Minus():Unary_Command("-"){
        priority = 5;
        type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
        return -operand1;
    };
};
class Multiply : public Binary_Command
{
public:
    Multiply():Binary_Command("*") {
        priority = 2;
        type = CommandType::Infix;
    }
    Operand execute_bin(Operand operand1, Operand operand2) {
        return operand1 * operand2;
    }
};
class Share : public Binary_Command
{
public:
    Share():Binary_Command("/") {
        priority = 2;
        type = CommandType::Infix;
    }
    Operand execute_bin(Operand operand1, Operand operand2) {
        if (is_zero(operand2)) {
            throw DIVISION_INVALID_ARGUMENT;
        }
        else {
            return  operand1 / operand2;
        }
    };
};
class Power : public Binary_Command
{
public:
    Power() :Binary_Command("^") {
        priority = 3;
        type = CommandType::Infix;
    }
    Operand execute_bin(Operand operand1, Operand operand2) {
        return pow(operand1,operand2);
    };
};
class Radical : public Binary_Command
{
public:
    Radical():Binary_Command("#") {
        priority = 3;
        type = CommandType::Infix;
    }
    Operand execute_bin(Operand operand1, Operand operand2){
        if (is_zero(operand2)) {
            cout << "Ошибка";
        }
        else {
            return pow(operand1, Operand(1, 0) / operand2);
        }
    };
};
class Logorithm : public Binary_Command
{
public:
    Logorithm():Binary_Command("Log") {
        priority = 5;
        type = CommandType::Infix;
    }
    Operand execute_bin(Operand operand1, Operand operand2) {
        return (log(operand2)/log(operand1));
    };
};
class Nlogorithm : public Unary_Command
{
public:
    Nlogorithm():Unary_Command("Ln") {
        priority = 5;
        type = CommandType::Infix;
    }
    Operand execute_un(Operand operand1) {
        return log(operand1);
    };
};
class Factorial : public Unary_Command
{
public:
    Factorial():Unary_Command("!") {
        priority = 5;
        type = CommandType::Postfix;
    }
    Operand execute_un(Operand operand1) {
        int number,result = 1;
        if (is_zero(operand1)|| is_zero(operand1.imag())) {
            throw FACTORIAL_INVALID_ARGUMENT;
        }
        bool flag=false;
        int x = (int)(operand1.real());
        if (!is_zero(operand1.real() - x)) {
            throw FACTORIAL_INVALID_ARGUMENT;
        }
            int i = 1;
            while(i != x) {
                if(x>i){
                    result *= i;
                    ++i;
                }
                else {
                    result *= i;
                    --i;
                }
            }
            result *= i;
        return Operand(result,0);
    };
};
class Sinus : public Unary_Command
{
public:
    Sinus():Unary_Command("sin") {
        priority = 3;
        type = CommandType::Prefix;
    };
    Operand execute_un(Operand operand1) {
        if (!radian) {
            return ((operand1*PI)/Operand(180,0));
        }
        else {
            return sin(operand1);
        }
    };
};
class ModuleOp : public Unary_Command
{
public:
    ModuleOp() :Unary_Command("[") {
        priority = 0;
        type = CommandType::None;
    };
    Operand execute_un(Operand operand1) {
        return abs(operand1);
    };
};
class ModuleCl : public Unary_Command
{
public:
    ModuleCl() :Unary_Command("]") {
        priority = 5;
        type = CommandType::Prefix;
    };
    Operand execute_un(Operand operand1) {
        return operand1;
    }
};
class Cosinus : public Unary_Command
{
public:
    Cosinus():Unary_Command("cos"){
            priority = 3;
            type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
        if (!radian) {
            return cos((operand1*PI) / Operand(180, 0));
        }
        else {
            return cos(operand1);
        }
    };
};
class ArcCosinus : public Unary_Command
{
public:
    ArcCosinus() :Unary_Command("arccos") {
        priority = 3;
        type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
            return ((acos(operand1)) *Operand(180, 0)/ PI);
    };
};
class ArcSinus : public Unary_Command
{
public:
    ArcSinus() :Unary_Command("arcsin") {
        priority = 3;
        type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
        return ((asin(operand1)) * Operand(180, 0) / PI);
    };
};
class ArcTangence : public Unary_Command
{
public:
    ArcTangence() :Unary_Command("arctg") {
        priority = 3;
        type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
        return ((atan(operand1)) * Operand(180, 0) / PI);
    };
};
class ArcCotangence : public Unary_Command
{
public:
    ArcCotangence() :Unary_Command("arcctg") {
        priority = 3;
        type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
        return ((Operand(1,0)/atan(operand1)) * Operand(180, 0) / PI);
    };
};
class Tangence : public Unary_Command
{
public:
    Tangence():Unary_Command("tg"){
            priority = 3;
            type = CommandType::Prefix;
        }
    Operand execute_un(Operand operand1) {
        if (!radian) {
            return (tan((operand1)*PI / Operand(180, 0)));
        }
        else {
            return (tan((operand1)));
        }
    };
};
class Cotangence : public Unary_Command {
public:
    Cotangence():Unary_Command("ctg") {
            priority = 3;
            type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
        if (!radian) {
            return (cos((operand1)*PI / Operand(180, 0)) / sin((operand1)*PI / Operand(180, 0)));
        }
        else {
            return (cos((operand1))/ sin((operand1)));
        }
    };
};
class Glogorithm : public Unary_Command
{
public:
    Glogorithm():Unary_Command("Lg") {
        priority = 5;
        type = CommandType::Infix;
    }
    Operand execute_un(Operand operand1) {
        if (is_zero(operand1)) {
            throw LOGARITHM_INVALID_ARGUMENT;
        }
        else {
            return (log((operand1)) / log(10));
        }
    };
};
class OpenBracket : public Unary_Command
{
public:
    OpenBracket():Unary_Command("(") {
        operandCount = 0;
        priority = 0;
        type = CommandType::None;
    }
    Operand execute_un(Operand operand1) {
        return operand1;
    }
};
class CloseBracket : public Unary_Command {
public:
    CloseBracket():Unary_Command(")") {
        priority = 4;
        type = CommandType::None;
    }
    Operand execute_un(Operand operand1) {
        return operand1;
    }
};

int OPZ(const vector<Expression_Unit> &From, vector<Expression_Unit> &To) {
    vector<Expression_Unit> cash;
    int lenght_From = From.size(),un_i,lenght_cash = cash.size();
    for (int i = 0; i < lenght_From; ++i) {
        lenght_cash = cash.size();
        if (From[i].type_unit == "nu" ||(From[i].type_unit == "co" && From[i].command->type == Postfix)) {
            if (From[i].type_unit == "nu") {
                To.push_back(From[i]);
            }
            else if (From[i].command->type == Postfix) {
                To.push_back(From[i]);
            }
        }
        if (From[i].type_unit == "co") {
            if (From[i].command->type == Prefix&& From[i].command->operandCount == 1) {
                cash.push_back(From[i]);
                lenght_cash = cash.size();
            }
        }
        if (From[i].type_unit == "co") {
            if (From[i].command->showname() == "(") {
                cash.push_back(From[i]);
                lenght_cash = cash.size();
            }
        }
        if (From[i].type_unit == "co") {
            if (From[i].command->showname() == "[") {
                cash.push_back(From[i]);
                lenght_cash = cash.size();
            }
        }
        if (From[i].type_unit == "co") {
            if (From[i].command->showname() == ")") {
                lenght_cash = cash.size();
                un_i = lenght_cash;
                    if (lenght_cash > 0) {
                        while (cash[un_i-1].command->showname() != "(") {
                            if (cash[un_i-1].type_unit == "nu") {
                                To.push_back(cash[un_i-1]);
                                cash.erase(cash.begin() + (un_i-1));
                            }
                            else if (From[i].type_unit == "co") {
                                To.push_back(cash[un_i-1]);
                                cash.erase(cash.begin() + (un_i-1));
                            }
                            lenght_cash = cash.size();
                            if (lenght_cash == 0) {
                                cout << "\nОшбика";
                                return 0;
                            }
                            --un_i;
                        }
                        cash.erase(cash.begin() +(un_i-1));
                    }
                lenght_cash = cash.size();
            }
            if (From[i].command->showname() == "]") {
                lenght_cash = cash.size();
                un_i = lenght_cash;
                if (lenght_cash > 0) {
                    while (cash[un_i - 1].command->showname() != "[") {
                        if (cash[un_i - 1].type_unit == "nu") {
                            To.push_back(cash[un_i - 1]);
                            cash.erase(cash.begin() + (un_i - 1));
                        }
                        else if (From[i].type_unit == "co") {
                            To.push_back(cash[un_i - 1]);
                            cash.erase(cash.begin() + (un_i - 1));
                        }
                        lenght_cash = cash.size();
                        if (lenght_cash == 0) {
                            cout << "\nОшбика";
                            return 0;
                        }
                        --un_i;
                    }
                }
                lenght_cash = cash.size();
            }
        }
        if (From[i].type_unit == "co" && From[i].command->operandCount == 2  ) {
                if (lenght_cash > 0) {
                    un_i = lenght_cash;
                    while ((cash[un_i-1].command->type == Prefix) || (From[i].command->priority < cash[un_i-1].command->priority)|| (From[i].command->priority == cash[un_i-1].command->priority&&From[i].place > cash[un_i-1].place)) {
                        To.push_back(cash[un_i-1]);
                        cash.erase(cash.begin() + (un_i-1));
                        lenght_cash = cash.size();
                        if (lenght_cash == 0) {
                            break;
                        }
                        --un_i;
                    }
                    cash.push_back(From[i]);
                    lenght_cash = cash.size();
                }
                else {
                    cash.push_back(From[i]);
                    lenght_cash = cash.size();
                }
        }
    }
    lenght_cash = cash.size();
    un_i = lenght_cash;
    while (un_i>0) {
            if (cash[un_i-1].type_unit == "nu") {
                cout << "Ошибка ввода\n";
                return 0;
            }
            else if (cash[un_i-1].type_unit == "co") {
                To.push_back(cash[un_i-1]);
            }
            --un_i;
    }
    for (int k = 0; k < lenght_cash; ++k) {
        cash.erase(cash.begin() + 0);
    }
    return 1;
}
int paren_difference(string expr)
{

    int pd = 0;

    for (auto p = expr.begin(); p < expr.end(); p++)

        (*p == '(') ? pd++ :

        (*p == ')') ? pd-- : 0;

    return pd;

}
QString formatted(string expr)

{

    QString text = "<p align=\"right\">";
    for (int i = 0; i < expr.size(); i++)
    {
        if ((i == 0 || i > 0 && !isdigit(expr[i - 1])) && expr[i] == '2' && expr[i + 1] == '#') continue;
        if (expr[i] == 'p') text += "π";
        else if (expr[i] == '^' || expr[i] == '#' || expr[i] == '&')
        {
            if (expr[i] == '#' || expr[i] == '&')
            {
                int here = text.length() - 1;
                if (text[here] == ')')
                {
                    int tmp = 0;
                    do {
                        if (text[here] == '(') tmp++;
                        if (text[here] == ')') tmp--;
                    }
                    while (--here >= 0 && tmp);
                }
                else
                {
                    do {
                        if (!(text[here] == '.' || text[here] >= '0' && text[here] <= '9')
                            && text[here] != 'e' && text[here] != "π") break;
                    }
                    while (--here >= 0);
                }
                if (expr[i] == '#')
                {
                    text.insert(here + 1, "<sup>");
                    text += "</sup>";
                }
                else
                {
                    text.insert(here + 1, "log<sub>");
                    text += "</sub>";
                }
            }
            if (expr[i] == '^' || expr[i] == '#')
            {
                unsigned int here = i;
                if (expr[i] == '^')
                {
                    if (i + 1 < expr.length()) text += "<sup>";
                    else { text += "^"; break; }
                }
                else
                {
                    if (i + 1 < expr.length()) text += "√<span style=\"text-decoration: overline\">";
                    else { text += "√"; break; }
                }
                if (expr[++i] == '+' || expr[i] == '-') text += expr[i];
                else i--;
                if (expr[++i] == '(')
                {
                    int tmp = 0;
                    do {
                        if (expr[i] == '(') tmp++;
                        if (expr[i] == ')') tmp--;
                        if (expr[i] == 'p') text += "π";
                        else text += expr[i];
                    }
                    while (++i < expr.length() && tmp);
                }
                else
                {
                    do {
                        if (!(expr[i] == '.' || expr[i] >= '0' && expr[i] <= '9')

                            && expr[i] != 'e' && expr[i] != 'p') break;

                        if (expr[i] == 'p') text += "π";

                        else text += expr[i];

                    }

                    while (++i < expr.length());

                }

                i--;

                if (expr[here] == '^') text += "</sup>";

                else text += "</span>";

            }

        }

        else text += expr[i];

    }



    text += "<span style=\"color: #CCCCCC\">";

    for (int i = 0; i < paren_difference(expr); i++) text += ')';

    text += "</span>";
    return text;
}
Operand Compute(vector<Expression_Unit> &To) {
    vector<Operand> stack;
    int Lenght_Commands = To.size(),k, Final_elem_Val,pl1=0,pl2=0,pl3=0;
    try {
        for (int i = 0; i < Lenght_Commands; ++i) {
            if (To[i].type_unit == "nu") {
                stack.push_back(To[i].operand);
            }
            else {
                stack.push_back(To[i].command->execute(stack));
            }

        }
    }
    catch (int e) {
        cout << errors[e];
        return Operand(0,0);
    }
    return stack[0];
}
double Calculate() {
    string expression;
    string unit_s;
    string unit_d;
    vector<Expression_Unit> v_expr;
    vector <string> varnames_v;
    vector<Operand> varvalues_v;
    int quanity_of_varibles;
    fstream input;
        getline(cin, expression, '\n');
        varnames_v.push_back("Pi");
        varvalues_v.push_back(Operand(PI,0));
        int lenght_expr = expression.length(), i = 0, OpenBr = 0, CloseBr = 0, quanity_of_minuses=0;
        bool flag_number = false,flag_trig=false, flag_word = false, flag_oper = false, flag_unarM = false, Check_OpenBr = false;
        for (i; i < lenght_expr; ++i) {
            if (expression[i] == '+') {
                if (!flag_oper) {
                    Plus* inunitp = new Plus();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitp;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_word = false;
                    flag_trig = false;
                    flag_number = false;
                    flag_unarM = false;
                }
                else {
                    cout << "Ошибка в вводе";
                    return 0;
                }
            }
            if (expression[i] == '-') {
                if (flag_number || flag_word) {
                Minus* inunitm = new Minus();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitm;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_trig = false;
                    flag_word = false;
                    flag_number = false;
                    flag_unarM = false;
                }
                else {
                    Unar_Minus* inunitm = new Unar_Minus();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitm;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_word = false;
                    flag_number = false;
                    flag_unarM = true;
                }
            }
            if (expression[i] == '*') {
                Multiply* inunitmu=new Multiply();
                if (!flag_oper||!flag_unarM) {
                    v_expr.emplace_back();
                    v_expr.back().command = inunitmu;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_trig = false;
                    flag_word = false;
                    flag_number = false;
                    flag_unarM = false;
                }
                else {
                    cout << "Ошибка в вводе";
                    return 0;
                }
            }
            if (expression[i] == '/') {
                Share* inunits = new Share();
                if (!flag_oper || !flag_unarM){
                    v_expr.emplace_back();
                    v_expr.back().command = inunits;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_trig = false;
                    flag_word = false;
                    flag_number = false;
                    flag_unarM = false;
                }
                else {
                    cout << "Ошибка в вводе";
                    return 0;
                }
            }
            if (expression[i] == '^') {
                Power* inunitpa = new Power();
                if (!flag_oper || !flag_unarM) {
                    v_expr.emplace_back();
                    v_expr.back().command = inunitpa;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_word = false;
                    flag_trig = false;
                    flag_number = false;
                    flag_unarM = false;
                }
                else {
                    cout << "Ошибка в вводе";
                    return 0;
                }
            }
            if (expression[i] == '#') {
                Radical* inunitr = new Radical();
                if (!flag_oper || !flag_unarM) {
                    v_expr.emplace_back();
                    v_expr.back().command = inunitr;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_trig = false;
                    flag_word = false;
                    flag_number = false;
                    flag_unarM = false;
                }
                else {
                    cout << "Ошибка в вводе";
                    return 0;
                }
            }
            if (expression[i] == 'L'&&expression[i + 1] == 'n'&&expression[i + 2] == ' ') {
                Nlogorithm* inunitL = new Nlogorithm();
                v_expr.emplace_back();
                v_expr.back().command = inunitL;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_word = false;
                flag_trig = false;
                flag_number = false;
                flag_unarM = false;
                i += 2;
            }
            if (expression[i] == 't'&&expression[i + 1] == 'g'&&expression[i + 2] == '(') {
                bool flag = true;
                Tangence* inunitTg = new Tangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 2;
            }
            if (expression[i] == 'a'&&expression[i + 1] == 'r'&&expression[i + 2] == 'c'&&expression[i + 3] == 's'&&expression[i + 4] == 'i'&&expression[i + 5] == 'n'&&expression[i + 6] == '(') {
                bool flag = true;
                ArcSinus* inunitTg = new ArcSinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 6;
            }
            if (expression[i] == 'a'&&expression[i + 1] == 'r'&&expression[i + 2] == 'c'&&expression[i + 3] == 'c'&&expression[i + 4] == 'o'&&expression[i + 5] == 's'&& expression[i + 6] == '(') {
                bool flag = true;
                ArcCosinus* inunitTg = new ArcCosinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 6;
            }
            if (expression[i] == 'a'&&expression[i + 1] == 'r'&&expression[i + 2] == 'c'&&expression[i + 3] == 'c'&&expression[i + 4] == 't'&&expression[i + 5] == 'g' &&expression[i + 6] == '(') {
                bool flag = true;
                ArcCotangence* inunitTg = new ArcCotangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 6;
            }
            if (expression[i] == 'a'&&expression[i + 1] == 'r'&&expression[i + 2] == 'c'&&expression[i + 3] == 't'&&expression[i + 4] == 'g'&&expression[i + 5] == '(') {
                bool flag = true;
                ArcTangence* inunitTg = new ArcTangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 5;
            }
            if (expression[i] == 'c'&&expression[i + 1] == 't'&&expression[i + 2] == 'g'&&expression[i + 3] == '(') {
                bool flag = true;
                Cotangence* inunitCt = new Cotangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitCt;
                v_expr.back().type_unit = "co";
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 3;
            }
            if (expression[i] == 'c'&&expression[i + 1] == 'o'&&expression[i + 2] == 's'&&expression[i + 3] == '(') {
                bool flag = true;
                Cosinus* inunitCo = new Cosinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitCo;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 3;
            }
            if (expression[i] == 's'&&expression[i + 1] == 'i'&&expression[i + 2] == 'n'&&expression[i + 3] == '(') {
                bool flag = true;
                Sinus* inunitSi = new Sinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitSi;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
                i += 3;
            }
            if (expression[i] == '!') {
                Factorial* inunitFa = new Factorial();
                v_expr.emplace_back();
                v_expr.back().command = inunitFa;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = false;
                flag_word = false;
                flag_number = true;
                flag_unarM = false;
            }
            if (expression[i] == '(') {
                OpenBracket* inunitBo = new OpenBracket();
                v_expr.emplace_back();
                v_expr.back().command = inunitBo;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                Check_OpenBr = true;
                ++OpenBr;
                flag_oper = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
            }
            if (expression[i] == '[') {
                ModuleOp* inunitMoO = new ModuleOp();
                v_expr.emplace_back();
                v_expr.back().command = inunitMoO;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                Check_OpenBr = true;
                ++OpenBr;
                flag_oper = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;
            }
            if (expression[i] == ')') {
                if (Check_OpenBr) {
                    CloseBracket* inunitBo = new CloseBracket();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitBo;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    ++CloseBr;
                    flag_oper = false;
                    flag_word = false;
                    flag_number = false;
                    flag_unarM = false;
                }
                else {
                    cout << "Ошибка в вводе";
                    return 0;
                }
                if (expression[i] == ']') {
                    if (Check_OpenBr) {
                        ModuleCl* inunitMoC = new ModuleCl();
                        v_expr.emplace_back();
                        v_expr.back().command = inunitMoC;
                        v_expr.back().type_unit = "co";
                        v_expr.back().place = i;
                        ++CloseBr;
                        flag_oper = false;
                        flag_word = false;
                        flag_number = false;
                        flag_unarM = false;
                    }
                    else {
                        cout << "Ошибка в вводе";
                        return 0;
                    }
                }
            }
            if (expression[i] == 'L'&&expression[i + 1] == 'o'&&expression[i + 2] == 'g'&&expression[i + 3] == ' ') {
                Logorithm* inunitLog = new Logorithm();
                v_expr.emplace_back();
                v_expr.back().command = inunitLog;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                /*v_expr.emplace_back();
                v_expr.back().command = inunitp;
                v_expr.back().type_unit = "co";
                flag_oper = true;
                flag_word = false;
                flag_number = false;
                flag_unarM = false;*/
                flag_oper = true;
                flag_word = false;
                flag_trig = false;
                flag_number = false;
                flag_unarM = false;
                i += 3;
            }
            if (isalpha(expression[i])) {
                string cash = "";
                while (isalpha(expression[i])) {
                    cash += expression[i];
                    ++i;
                }
                int j = 0;
                bool check_name = false;
                quanity_of_varibles = varnames_v.size();
                if (cash == "Pi"&&flag_trig) {
                    int seek = (v_expr.size()-1);
                    while(v_expr[seek].command->showname()!="tg"&& v_expr[seek].command->showname() != "ctg" && v_expr[seek].command->showname() != "sin" && v_expr[seek].command->showname() != "cos"){
                        --seek;
                    }
                    if (v_expr[seek].command->showname() != "tg" || v_expr[seek].command->showname() != "ctg" || v_expr[seek].command->showname() != "sin" || v_expr[seek].command->showname() != "cos") {
                        v_expr[seek].command->radian = true;
                    }
                    flag_trig = false;
                }
                if (quanity_of_varibles==varvalues_v.size()) {
                    for (j; j < (quanity_of_varibles); ++j) {
                        if (varnames_v[j] == cash) {
                            check_name = true;
                            break;
                        }
                    }
                }
                if (check_name) {
                    v_expr.emplace_back();
                    v_expr.back().operand = varvalues_v[j];
                    v_expr.back().type_unit = "nu";
                    if (flag_trig){
                        int lenght = v_expr.size();
                        v_expr[lenght - 2].command->radian = true;
                    }
                    --i;
                }
                else {
                    cout << "Ошибка";
                    return 0;
                }
                flag_oper = false;
                flag_trig = false;
                flag_word = true;
                flag_number = false;
                flag_unarM = false;
                ////////
                //////
                /////
                ///////
                //////////
            }
            if (isdigit(expression[i])) {
                string cash = "";
                while (isdigit(expression[i]) || expression[i] == '.' || expression[i] == ',') {
                    if (expression[i] == '.') {
                        expression[i] = ',';
                    }
                        cash += expression[i];
                        ++i;
                }
                if (expression[i] == 'i') {
                    v_expr.emplace_back();
                    v_expr.back().operand=Operand(0,stod(cash));
                    v_expr.back().type_unit = "nu";
                }
                else {
                    v_expr.emplace_back();
                    v_expr.back().operand = Operand(stod(cash),0);
                    v_expr.back().type_unit = "nu";
                    --i;
                }
                quanity_of_minuses = 0;
                flag_oper = false;
                flag_word = false;
                flag_number = true;
                flag_unarM = false;
            }
        }
        //vector<Command*> Commands;
        //vector<Operand> Operands;
        vector <Expression_Unit> To;
        OPZ(v_expr,To);
        //reverse(To.begin(), To.end());
        //reverse(Commands.begin(), Commands.end());
        //reverse(Operands.begin(), Operands.end());
        //cout << Compute(To);
        Operand result1=(Compute(To));
        string result2 = "";
            if (is_zero(result1.real())) {
                result2 += "0";
            }
            else {
                result2 += to_string(result1.real());
            }
        if (is_zero(result1.imag())) {

        }
        else {
            string taker="";
            if (result1.imag() > 0) {
                taker += "+";
                taker += to_string(result1.imag());
                result2 += taker;
            }
            else {
                taker += "-";
                taker += to_string(result1.imag());
                result2 += taker;
            }
        }
        cout <<'\n'<<result2<<'\n';
        for (int Length_del = v_expr.size(), i = 0; i < Length_del; ++i) {
            v_expr[i].del();
        }

}
