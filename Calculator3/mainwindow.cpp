#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include<string.h>
#include<string.h>
#include "string.h"
#include <iostream>
#include<fstream>
#include<complex>
#include<algorithm>
#include<vector>
#include<cmath>
#include <QKeyEvent>
#include <math.h>
#define PI 3.14159265
#define epsilon 0.00000000001
#define ex 2.71828182845904523536
#define	FACTORIAL_INVALID_ARGUMENT 0
#define	LOGARITHM_INVALID_ARGUMENT 1
#define	DIVISION_INVALID_ARGUMENT 2
#define BRACKETS_INVALID_lINC 3
#define OPERATOR_INVALID_lINC 4
const char* errors[10] = {
    "Неправильный аргумент факториала",
    "Неправильный арумент логарифма",
    "Деление на ноль",
    "Несогласованные скобки",
    "Ошибка в записи операций"
};
using namespace std;
typedef complex<double> Operand;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
using::std::string;
using::std::vector;
static string expr;
QString text_unit,biautyexpr;
std::vector<unsigned int> operators_count;
bool flag_log=false;
int second_flag_log;
vector<string> br_call;

QString formatted()

{
    vector<QString> form_stack;
    char checker;
    QString text = "<p align=\"right\">";
    int brO=0,brC=0;
    second_flag_log=0;
    bool flag_power=false,flag_ln=false,flag_lg=false,flag_root=false;
    for (unsigned int i = 0; i < expr.length(); i++){
        checker=expr[i];
            if(expr[i]=='a'){
                if(((expr.length()-1)-i)>=2){
                    if(expr[i+1]=='('&&expr[i+2]=='('){
                        i+=1;
                        brO++;
                      flag_log=true;
                      ++second_flag_log;
                      if(second_flag_log>1){
                           text+="Log(";
                          //text+="(";
                          //form_stack.push_back(")sp");
                          form_stack.push_back(")sp");
                      }else{
                           text+="Log<sub>";
                           form_stack.push_back("");
                          //form_stack.push_back(")");
                      }
                      continue;
                    }
                }
            }
            if(expr[i]=='b'){
                if(((expr.length()-1)-i)>=1){
                    if(expr[i+1]=='('){
                        ++i;
                        brO++;
                      text+="Ln(";
                      form_stack.push_back(")");
                      continue;
                    }
                }
            }
            if(expr[i]=='c'){
                if(((expr.length()-1)-i)>=1){
                    if(expr[i+1]=='('){
                        ++i;
                        brO++;
                      text+="Lg(";
                      form_stack.push_back(")");
                      continue;
                    }
                }
            }
            /*if(expr[i]==')'&&form_stack[form_stack.size()-1]==")sp"){
                ++brC;
                expr+=')';
                expr+=')';
                continue;
            }*/
            if(expr[i]==')'){
                ++brC;
                if(form_stack.size()>0){
                    if(form_stack[form_stack.size()-1]==")sp"){
                        text+=")";
                        --second_flag_log;
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }else if(form_stack[form_stack.size()-1]==""){
                        text+="";
                        --second_flag_log;
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }else{
                        text+=form_stack[form_stack.size()-1];
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }
                }
                continue;
            }
            if(expr[i]=='('){
                text+='(';
                brO++;
                form_stack.push_back(")");
                continue;
            }

            if(expr[i]=='d'){
                text+="sin";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='f'){
                text+="cos";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='g'){
                text+="arccos";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='h'){
                text+="arcsin";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='j'){
                text+="arctg";
                brO++;
                form_stack.push_back(")");
            }
            if(expr[i]=='k'){
                text+="arcctg";
                brO++;
               form_stack.push_back(")");
                continue;
            }
            if(expr[i]=='l'){
                text+="tg";
                brO++;
               form_stack.push_back(")");
                continue;
            }
            if(expr[i]=='m'){
                text+="ctg";
                brO++;
                form_stack.push_back(")");
                continue;
            }
            if(i!=0){
               if(expr[i]=='i'&&expr[i-1]=='P'){
                  text+="P";
                  continue;
               }
            }
            if(expr[i]=='e'){
                text+="e";
                continue;
            }
            if(expr[i]=='i'){
                text+="i";
                continue;
            }
            if(expr[i]=='*'){
                text+="?";
                continue;
            }
            if(expr[i]=='+'){
                text+="+";
                continue;
            }
            if(expr[i]=='-'){
                text+="-";
                continue;
            }
            if(expr[i]=='/'){
                text+="/";
                continue;
            }
            if(expr[i]=='0'){
                text+="0";
                continue;
            }
            if(expr[i]=='1'){
                text+="1";
                continue;
            }
            if(expr[i]=='2'){
                text+="2";
                continue;
            }
            if(expr[i]=='3'){
                text+="3";
                continue;
            }
            if(expr[i]=='4'){
                text+="4";
                continue;
            }
            if(expr[i]=='5'){
                text+="5";
                continue;
            }
            if(expr[i]=='6'){
                text+="6";
                continue;
            }
            if(expr[i]=='7'){
                text+="7";
                continue;
            }
            if(expr[i]=='8'){
                text+="8";
                continue;
            }
            if(expr[i]=='9'){
                text+="9";
                continue;
            }
            if(expr[i]=='.'){
                text+=".";
                continue;
            }
            if(expr[i]==','){
                if(second_flag_log>1){
                    text+=",";

                }else{
                    text+="</sub>";
                }
                continue;
            }
            if(expr[i]=='%'){
                text+="%";
                continue;
            }
            if(expr[i]=='!'){
                text+="!";
                continue;
            }
            if(expr[i]=='P'){
                text+="?";
                continue;
            }
            if(expr[i]=='['){
                text+="[";
                continue;
            }
            if(expr[i]=='['){
                text+="]";
                continue;
            }
            if(expr[i]=='^'){
                if(((expr.length()-1)-i)>=1){
                    if(expr[i+1]=='('){
                        ++i;
                        brO++;
                      text+="<sup>(";
                      form_stack.push_back(")</sup>");
                      continue;
                    }
                }
            }
            if(expr[i]=='#'){
                if(((expr.length()-1)-i)>=1){
                    if(expr[i+1]=='('){
                        ++i;
                        brO++;
                      text+="v<span style=\"text-decoration: overline\">(";
                      form_stack.push_back(")</span>");
                      continue;
                    }
                }

            }

    }
    /*if(form_stack.size()>0){
        for(int step=(form_stack.size()-1);step>0;--step){
            text+=form_stack[form_stack.size()-1];
        }
    }*/
    text+="</p>";
    return text;
}

/*

    QString text = "<p align=\"right\">";



    for (unsigned int i = 0; i < expr.length(); i++)

    {

        if ((i == 0 || i > 0 && (expr[i - 1] == '.' || (expr[i - 1] >= '0' && expr[i - 1] <= '9'))) && expr[i] == '2' && expr[i + 1] == '#') continue;

        if (i>0&&(expr[i] == 'P'&&expr[i+1] == 'i')){
            text += "?";
}
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

                        if (!(text[here] == '.' ||( text[here] >= '0' && text[here] <= '9'))

                        && text[here] != 'e' && text[here] != "?") break;

                    }

                    while (--here >= 0);

                }



                if (expr[i] == 'a')

                {

                    text.insert(here + 1, "Log<sup>");

                    text += "</sup>";

                }

                else

                {

                    text.insert(here + 1, "Log<sub>");

                    text += "</sub>";

                }
                if (expr[i] == 'b')

                {

                    text.insert(here + 1, "<sup>");

                    text += "</sup>";

                }

                else

                {

                    text.insert(here + 1, "Ln<sub>");

                    text += "</sub>";

                }

                if (expr[i] == 'c')

                {

                    text.insert(here + 1, "<sup>");

                    text += "</sup>";

                }

                else

                {

                    text.insert(here + 1, "Lg<sub>");

                    text += "</sub>";

                }
                if (expr[i] == 'd')

                {
                    text.insert(here + 1, "sin<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'f')

                {
                    text.insert(here + 1, "cos<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'g')

                {
                    text.insert(here + 1, "arccos<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'h')

                {
                    text.insert(here + 1, "arcsin<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'j')

                {
                    text.insert(here + 1, "arctg<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'k')

                {
                    text.insert(here + 1, "arcctg<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'l')

                {
                    text.insert(here + 1, "tg<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'm')

                {
                    text.insert(here + 1, "ctg<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'i')

                {
                    text.insert(here + 1, "i<sub>");
                    text += "</sub>";
                }
                if (expr[i] == 'e')

                {
                    text.insert(here + 1, "e<sub>");
                    text += "</sub>";
                }

            }

            if (expr[i] == '^' || expr[i] == '#')

            {

                unsigned int here = i;

                if (expr[i] == '^')

                {

                    if (i + 1 < expr.length()) text += "<sup>";

                    else {text += "^"; break;}

                }

                else

                {

                    if (i + 1 < expr.length()) text += "v<span style=\"text-decoration: overline\">";

                    else {text += "v"; break;}

                }

                if (expr[++i] == '+' || expr[i] == '-') text += expr[i];

                else i--;

                if (expr[++i] == '(')

                {

                    int tmp = 0;

                    do {

                        if (expr[i] == '(') tmp++;

                        if (expr[i] == ')') tmp--;

                        if (expr[i] == 'p') text += "?";

                        else text += expr[i];

                    }

                    while (++i < expr.length() && tmp);

                }

                else

                {

                    do {

                        if (!(expr[i] == '.' ||(expr[i] >= '0' && expr[i] <= '9'))

                        && expr[i] != 'e' && expr[i] != 'p') break;

                        if (expr[i] == 'p') text += "?";

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

    for (int i = 0; i < paren_difference(); i++) text+= ')';

    text += "</span>";
    return text;

}
*/

bool flag_coml=false;
enum CommandType {
    Infix, Prefix, Postfix,None
};
bool is_zero(double a) {
    return !(abs(a - DBL_EPSILON) > 0);
}
bool is_zero(Operand a) {
    return (is_zero(a.imag()) && is_zero(a.real()));
}
class Expression_Unit;
class Command {
public:
    string name;
public:
    bool radian=false;
    virtual Operand execute(vector <Operand> &opz) = 0;
    unsigned short operandCount, priority;
    CommandType type;
    Command(string nameC){
        name=nameC;
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
        type = CommandType::Prefix;
    }
    Operand execute_bin(Operand operand1, Operand operand2){
        if (is_zero(operand1)) {
            throw FACTORIAL_INVALID_ARGUMENT;
        }
        else {
            return pow(operand2, Operand(1, 0) / operand1);
        }
    };
};
class Logorithm : public Binary_Command
{
public:
    Logorithm():Binary_Command("a") {
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
    Nlogorithm():Unary_Command("b") {
        priority = 5;
        type = CommandType::Prefix;
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
        if (is_zero(operand1)) {
            throw FACTORIAL_INVALID_ARGUMENT;
        }
        bool flag=false;
        int x = (int)(operand1.real());
            int i;
            if(x>0){
                i=1;
            }else{
                i=-1;
            }
            while(i != x) {
                if(x>0){
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
    Sinus():Unary_Command("d") {
        priority = 3;
        type = CommandType::Prefix;
    };
    Operand execute_un(Operand operand1) {
        if (!radian) {
            return sin((operand1*PI)/Operand(180,0));
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
    Cosinus():Unary_Command("f"){
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
    ArcCosinus() :Unary_Command("g") {
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
    ArcSinus() :Unary_Command("h") {
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
    ArcTangence() :Unary_Command("j") {
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
    ArcCotangence() :Unary_Command("k") {
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
    Tangence():Unary_Command("l"){
            priority = 3;
            type = CommandType::Prefix;
        }
    Operand execute_un(Operand operand1) {
        if (!radian) {
            return (sin((operand1)*PI / Operand(180, 0)) / cos((operand1)*PI / Operand(180, 0)));
        }
        else {
            return (sin((operand1))/ cos((operand1)));
        }
    };
};
class Cotangence : public Unary_Command {
public:
    Cotangence():Unary_Command("m") {
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
    Glogorithm():Unary_Command("c") {
        priority = 5;
        type = CommandType::Prefix;
    }
    Operand execute_un(Operand operand1) {
        if (is_zero(operand1)) {
            throw LOGARITHM_INVALID_ARGUMENT;
        }
        else {
            return (log((operand1))/log(10));
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
                                throw BRACKETS_INVALID_lINC;

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
                            throw BRACKETS_INVALID_lINC;
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
        while (un_i > 0) {
                if (cash[un_i - 1].type_unit == "nu") {
                    throw BRACKETS_INVALID_lINC;
                }
                else if (cash[un_i - 1].type_unit == "co") {
                    To.push_back(cash[un_i - 1]);
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
/*QString formatted(string expr)

{

    QString text = "<p align=\"right\">";
    for (int i = 0; i < expr.size(); i++)
    {
        if ((i == 0 || i > 0 && !isdigit(expr[i - 1])) && expr[i] == '2' && expr[i + 1] == '#') continue;
        if (expr[i] == 'p') text += "?";
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
                            && text[here] != 'e' && text[here] != "?") break;
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
                    if (i + 1 < expr.length()) text += "v<span style=\"text-decoration: overline\">";
                    else { text += "v"; break; }
                }
                if (expr[++i] == '+' || expr[i] == '-') text += expr[i];
                else i--;
                if (expr[++i] == '(')
                {
                    int tmp = 0;
                    do {
                        if (expr[i] == '(') tmp++;
                        if (expr[i] == ')') tmp--;
                        if (expr[i] == 'p') text += "?";
                        else text += expr[i];
                    }
                    while (++i < expr.length() && tmp);
                }
                else
                {
                    do {
                        if (!(expr[i] == '.' || expr[i] >= '0' && expr[i] <= '9')

                            && expr[i] != 'e' && expr[i] != 'p') break;

                        if (expr[i] == 'p') text += "?";

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
}*/
Operand Compute(vector<Expression_Unit> &To) {
    vector<Operand> stack;
    int Lenght_Commands = To.size(), k, Final_elem_Val, pl1 = 0, pl2 = 0, pl3 = 0,count_com=0;
        for (int i = 0; i < Lenght_Commands; ++i) {
            if (To[i].type_unit == "nu") {
                stack.push_back(To[i].operand);
            }
            else {
                    stack.push_back(To[i].command->execute(stack));
            }

        }
    return stack[0];
}
string Calculate(string expression) {
    string unit_s;
    string unit_d;
    vector<Expression_Unit> v_expr;
    vector <string> varnames_v;
    vector<Operand> varvalues_v;
    int quanity_of_varibles;
    fstream input;
        varnames_v.push_back("Pi");
        varvalues_v.push_back(Operand(PI,0));
        int lenght_expr = expression.length(), i = 0, OpenBr = 0, CloseBr = 0, OpenBrM=0,CloseBrM=0, quanity_of_minuses=0;
        bool flag_number = false,flag_ClBr = false, flag_trig = false, flag_word = false, flag_oper = false, flag_postfix = false, flag_prefix = false, Check_OpenBr = false;
        for (i; i < lenght_expr; ++i) {
            if (expression[i] == '+') {
                if (flag_number||flag_word||flag_postfix) {
                    Plus* inunitp = new Plus();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitp;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_word = false;
                    flag_trig = false;
                    flag_ClBr=false;
                    flag_number = false;
                    flag_postfix = false;
                    flag_prefix = false;
                }
                else {
                    throw OPERATOR_INVALID_lINC;
                }
            }
            if (expression[i] == '-') {
                if (flag_number || flag_word||flag_postfix) {
                Minus* inunitm = new Minus();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitm;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_postfix = false;
                    flag_word = false;
                    flag_ClBr=false;
                    flag_number = false;
                    flag_prefix = false;
                }
                else {
                    Unar_Minus* inunitm = new Unar_Minus();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitm;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = false;
                    flag_word = false;
                    flag_ClBr=false;
                    flag_postfix = false;
                    flag_number = false;
                    flag_prefix = true;
                }
            }
            if (expression[i] == '*') {
                Multiply* inunitmu=new Multiply();
                if (flag_number||flag_postfix||flag_word) {
                    v_expr.emplace_back();
                    v_expr.back().command = inunitmu;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_ClBr=false;
                    flag_word = false;
                    flag_postfix = false;
                    flag_number = false;
                    flag_prefix = false;
                }
                else {
                    throw OPERATOR_INVALID_lINC;
                }
            }
            if (expression[i] == '/') {
                Share* inunits = new Share();
                if (flag_number||flag_postfix||flag_word){
                    v_expr.emplace_back();
                    v_expr.back().command = inunits;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_ClBr=false;
                    flag_word = false;
                    flag_postfix = false;
                    flag_number = false;
                    flag_prefix = false;
                }
                else {
                    throw OPERATOR_INVALID_lINC;
                }
            }
            if (expression[i] == '^') {
                Power* inunitpa = new Power();
                if (flag_number||flag_postfix||flag_word) {
                    v_expr.emplace_back();
                    v_expr.back().command = inunitpa;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_word = false;
                    flag_postfix = false;
                    flag_number = false;
                    flag_ClBr=false;
                    flag_prefix = false;
                }
                else {
                    throw OPERATOR_INVALID_lINC;
                }
            }
            if (expression[i] == '#') {
                if (flag_number||flag_postfix||flag_word) {
                Radical* inunitr = new Radical();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitr;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    flag_oper = true;
                    flag_word = false;
                    flag_ClBr=false;
                    flag_postfix = false;
                    flag_number = false;
                    flag_prefix = false;
                }
                    else {
                        throw OPERATOR_INVALID_lINC;
                    }
            }
            if (expression[i] == 'a'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                            Logorithm* inunitL = new Logorithm();
                            v_expr.emplace_back();
                            v_expr.back().command = inunitL;
                            v_expr.back().type_unit = "co";
                            v_expr.back().place = i;
                            flag_oper = true;
                            flag_word = false;
                            Check_OpenBr = true;
                            flag_ClBr=false;
                            flag_postfix = false;
                            flag_number = false;
                            flag_prefix = true;
                         //	++OpenBr;
            }
            if (expression[i] == 'b'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                Nlogorithm* inunitL = new Nlogorithm();
                v_expr.emplace_back();
                v_expr.back().command = inunitL;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_word = false;
                flag_ClBr=false;
                Check_OpenBr = true;
                flag_postfix = false;
                flag_number = false;
                flag_prefix = true;
                //++OpenBr;
            }
            if (expression[i] == 'c'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                Glogorithm* inunitL = new Glogorithm();
                v_expr.emplace_back();
                v_expr.back().command = inunitL;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_word = false;
                flag_ClBr=false;
                Check_OpenBr = true;
                flag_postfix = false;
                flag_number = false;
                flag_prefix = true;
                //++OpenBr;
            }
            if (expression[i] == 'l'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                Tangence* inunitTg = new Tangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_postfix = false;
                flag_ClBr=false;
                flag_word = false;
                flag_number = false;
                flag_prefix = true;
                Check_OpenBr = true;
            }
            if (expression[i] == 'h'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                ArcSinus* inunitTg = new ArcSinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_ClBr=false;
                flag_word = false;
                flag_number = false;
                Check_OpenBr = true;
                flag_postfix = false;
                flag_prefix = true;
                //++OpenBr;
            }
            if (expression[i] == 'g'&& expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                ArcCosinus* inunitTg = new ArcCosinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_ClBr=false;
                flag_number = false;
                flag_postfix = false;
                flag_prefix = true;
                Check_OpenBr = true;
                //++OpenBr;
            }
            if (expression[i] == 'k'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                ArcCotangence* inunitTg = new ArcCotangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_postfix = false;
                flag_ClBr=false;
                flag_number = false;
                flag_prefix = true;
                Check_OpenBr = true;
                //++OpenBr;

            }
            if (expression[i] == 'j'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                ArcTangence* inunitTg = new ArcTangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitTg;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_ClBr=false;
                flag_word = false;
                flag_postfix = false;
                flag_number = false;
                flag_prefix = true;
                //++OpenBr;
                Check_OpenBr = true;
            }
            if (expression[i] == 'm'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                Cotangence* inunitCt = new Cotangence();
                v_expr.emplace_back();
                v_expr.back().command = inunitCt;
                v_expr.back().type_unit = "co";
                flag_oper = true;
                flag_trig = true;
                flag_word = false;
                flag_ClBr=false;
                flag_number = false;
                flag_prefix = true;
                Check_OpenBr = true;
                flag_postfix = false;
                //++OpenBr;
            }
            if (expression[i] == 'd'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                Sinus* inunitSi = new Sinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitSi;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_postfix = false;
                flag_ClBr=false;
                flag_word = false;
                flag_number = false;
                flag_prefix = true;
                Check_OpenBr = true;
                //++OpenBr;
            }
            if (expression[i] == 'f'&&expression[i + 1] == '(') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                bool flag = true;
                Cosinus* inunitSi = new Cosinus();
                v_expr.emplace_back();
                v_expr.back().command = inunitSi;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_trig = true;
                flag_postfix = false;
                flag_ClBr=false;
                flag_word = false;
                flag_number = false;
                flag_prefix = true;
                Check_OpenBr = true;
                //++OpenBr;
            }
            if (expression[i] == '!') {
                if(flag_number||flag_postfix||flag_word){
                 Factorial* inunitFa = new Factorial();
                v_expr.emplace_back();
                v_expr.back().command = inunitFa;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                flag_oper = true;
                flag_word = false;
                flag_ClBr=false;
                flag_postfix = true;
                flag_number = true;
                flag_prefix = false;
                }else{
                    throw OPERATOR_INVALID_lINC;
                }
            }
            if(expression[i] == ','){
                flag_oper = false;
                flag_word = false;
                flag_ClBr=false;
                flag_postfix = false;
                flag_number = false;
                flag_prefix = false;
            }
            if (expression[i] == '(') {
                if ((flag_number||flag_postfix||flag_word)&&i!=0) {
                    throw OPERATOR_INVALID_lINC;
                }
                OpenBracket* inunitBo = new OpenBracket();
                v_expr.emplace_back();
                v_expr.back().command = inunitBo;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                Check_OpenBr = true;
                ++OpenBr;
                flag_oper = true;
                flag_word = false;
                flag_postfix = false;
                flag_ClBr=false;
                flag_number = false;
                flag_prefix = false;
            }
            if (expression[i] == '[') {
                if ((flag_number||flag_postfix||flag_word)&&i!=0) {
                    throw OPERATOR_INVALID_lINC;
                }
                ModuleOp* inunitMoO = new ModuleOp();
                v_expr.emplace_back();
                v_expr.back().command = inunitMoO;
                v_expr.back().type_unit = "co";
                v_expr.back().place = i;
                Check_OpenBr = true;
                ++OpenBrM;
                flag_oper = true;
                flag_word = false;
                flag_ClBr=false;
                flag_postfix = false;
                flag_number = false;
                flag_prefix = false;
            }
            if (expression[i] == ')') {
                if(flag_number||flag_postfix||flag_word){
                if (Check_OpenBr) {
                    CloseBracket* inunitBo = new CloseBracket();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitBo;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    ++CloseBr;
                    /*if (!flag_postfix&&!flag_number&&) {
                        throw OPERATOR_INVALID_lINC;
                    }*/
                    flag_ClBr = true;
                    flag_oper = false;
                    flag_word = false;
                    flag_postfix = true;
                    flag_number = false;
                    flag_prefix = false;
                }
                else {
                    throw BRACKETS_INVALID_lINC;
                }
                }else{
                    throw OPERATOR_INVALID_lINC;

                }
            }
            if (expression[i] == ']') {
                if(flag_number||flag_postfix||flag_word){
                if (Check_OpenBr) {
                    ModuleCl* inunitMoC = new ModuleCl();
                    v_expr.emplace_back();
                    v_expr.back().command = inunitMoC;
                    v_expr.back().type_unit = "co";
                    v_expr.back().place = i;
                    ++CloseBrM;
                    /*if (flag_postfix && !flag_number && !flag_word) {
                        throw OPERATOR_INVALID_lINC;
                    }*/
                    flag_oper = false;
                    flag_ClBr = true;
                    flag_word = false;
                    flag_postfix = true;
                    flag_number = false;
                    flag_prefix = false;
                }
                else {
                    throw BRACKETS_INVALID_lINC;
                }
                }else{
                    throw OPERATOR_INVALID_lINC;

                }
            }

            if (isalpha(expression[i])&&expression[i]!='i') {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                string cash = "";
                while (isalpha(expression[i])&&expression[i]!='i') {
                    cash += expression[i];
                    ++i;
                }
                int j = 0;
                bool check_name = false;
                quanity_of_varibles = varnames_v.size();
                if (cash == "P"&&flag_trig) {
                    int seek = (v_expr.size() - 1);
                    while (v_expr[seek].type_unit=="nu"||(v_expr[seek].command->showname() != "l"&& v_expr[seek].command->showname() != "m" && v_expr[seek].command->showname() != "d" && v_expr[seek].command->showname() != "f")) {
                        --seek;
                    }
                    if (v_expr[seek].type_unit=="co"&&(v_expr[seek].command->showname() != "l" || v_expr[seek].command->showname() != "m" || v_expr[seek].command->showname() != "d" || v_expr[seek].command->showname() != "f")) {
                        v_expr[seek].command->radian = true;
                        v_expr.emplace_back();
                        v_expr.back().operand = Operand(PI, 0);
                        v_expr.back().type_unit = "nu";
                        flag_word=true;
                    }
                    flag_trig = false;
                }
                else if(cash=="P"){
                    v_expr.emplace_back();
                    v_expr.back().operand = Operand(PI, 0);
                    v_expr.back().type_unit = "nu";
                    flag_word = true;
                }
                if (cash == "e") {
                    v_expr.emplace_back();
                    v_expr.back().operand = Operand(ex, 0);
                    v_expr.back().type_unit = "nu";
                    flag_word=true;
                    flag_word = true;
                }
                if (quanity_of_varibles==varvalues_v.size()) {
                    for (j; j < (quanity_of_varibles); ++j) {
                        if (varnames_v[j] == cash) {
                            check_name = true;
                            break;
                        }
                    }
                }
/*				if (check_name) {
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
                }*/
                flag_oper = false;
                flag_ClBr=false;
                flag_postfix = false;
                flag_number = false;
                flag_prefix = false;
                --i;
            }
            if (isdigit(expression[i])) {
                if((flag_number||flag_postfix||flag_word)&&i!=0){
                    throw OPERATOR_INVALID_lINC;
                }
                if(i>0){
                    if(expression[i-1]=='i'){
                         throw OPERATOR_INVALID_lINC;
                    }
                }
                string cash = "";
                while (isdigit(expression[i]) || expression[i] == '.') {
                        cash += expression[i];
                        ++i;
                }
                if (expression[i] == 'i') {
                    v_expr.emplace_back();
                    v_expr.back().operand=Operand(0,stod(cash));
                    flag_number = true;
                    flag_coml=true;
                    v_expr.back().type_unit = "nu";
                }
                else {
                    v_expr.emplace_back();
                    v_expr.back().operand = Operand(stod(cash),0);
                    v_expr.back().type_unit = "nu";
                }
                quanity_of_minuses = 0;
                flag_oper = false;
                flag_word = false;
                flag_ClBr=false;
                flag_postfix = false;
                flag_number = true;
                flag_prefix = false;
                --i;
            }
        }
        vector <Expression_Unit> To;
        if ((OpenBr != CloseBr) || (OpenBrM != CloseBrM)) {
            throw BRACKETS_INVALID_lINC;
        }
        OPZ(v_expr, To);
        //reverse(To.begin(), To.end());
        //reverse(Commands.begin(), Commands.end());
        //reverse(Operands.begin(), Operands.end());
        //cout << Compute(To);
        Operand result1=(Compute(To));
        string result2 = "";
        if(!flag_coml){
            result2+=to_string(result1.real());
        }else{
            string taker="";
             result2+=to_string(result1.real());
             if (result1.imag() > 0) {
                 taker += "+";
                 taker += to_string(result1.imag());
                 result2 += taker;
                 result2 += "i";
             }
             else if(result1.imag() < 0){
                 taker += to_string(result1.imag());
                 result2 += taker;
                 result2 += "i";
             }
        }
          /*  if (is_zero(result1.real())) {
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
                result2 += "i";
            }
            else {
                taker += "-";
                taker += to_string(result1.imag());
                result2 += taker;
                result2 += "i";
            }
        }*/
        return result2;
        for (int Length_del = v_expr.size(), i = 0; i < Length_del; ++i) {
            v_expr[i].del();
        }

}
QString result_of_expr(string exp) {
    string result;
    flag_coml=false;
    try {
        result=Calculate(exp);
    }
    catch (int e) {
        return errors[e];
    }
    return QString::fromStdString(result);
}


void MainWindow::on_opB_clicked()
{
    expr+="(";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    br_call.push_back("(");
    operators_count.push_back(1);
}

void MainWindow::on_clB_clicked()
{
     expr+=")";
//ui->exprText->setText(formatted());
     // ui->exprText->insert(")");
     if(br_call.size()>0){
         if(br_call[br_call.size()-1]=="sp("){
             expr+=",(";
              operators_count.push_back(3);
              operators_count.push_back(1);
              //ui->exprText->insert(",(");
             br_call.erase(br_call.begin()+br_call.size()-1);
             //br_call.push_back("(");
         }else if(br_call[br_call.size()-1]=="a("){
             expr+=")";
             //--second_flag_log;
             operators_count.push_back(2);
             br_call.erase(br_call.begin()+br_call.size()-1);
         }else{
             formatted();
             operators_count.push_back(1);
              br_call.erase(br_call.begin()+br_call.size()-1);
         }
         ui->exprText->setText(formatted());
     }
     unsigned int count=1;
}

void MainWindow::on_opmB_clicked()
{
     expr+="[";
     unsigned int count=1;
     ui->exprText->setText(formatted());
     operators_count.push_back(1);
}

void MainWindow::on_clmB_clicked()
{
     expr+="]";
     unsigned int count=1;
     ui->exprText->setText(formatted());
     operators_count.push_back(1);
}

void MainWindow::on_factB_clicked()
{
     expr+="!";
     unsigned int count=1;
     ui->exprText->setText(formatted());
     operators_count.push_back(1);
}
void MainWindow::on_clearB_2_clicked()
{
    text_unit=QString::fromStdString(expr);
  if(text_unit.length()>0){
    unsigned int count=operators_count[operators_count.size()-1];
    text_unit.remove(text_unit.length()-1,count);
    expr=text_unit.toStdString();
    ui->exprText->setText(formatted());
    operators_count.erase(operators_count.begin()+(operators_count.size()-1));
  }
}
void MainWindow::on_eigthB_clicked()
{
    expr+="8";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_nineB_clicked()
{
    expr+="9";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_plusB_clicked()
{
    expr+="+";
    unsigned int count=1;
ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_fourB_clicked()
{
    expr+="4";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_fiveB_clicked()
{
    expr+="5";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_sixB_clicked()
{
    expr+="6";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_sevenB_clicked()
{
    expr+="7";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}
void MainWindow::on_threeB_clicked()
{
    expr+="3";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_twoB_clicked()
{
    expr+="2";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}


void MainWindow::on_oneB_clicked()
{
    expr+="1";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_pointB_clicked()
{
    expr+=".";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_zeroB_clicked()
{
    expr+="0";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_recipB_clicked()
{
    expr+="^(-1)";
    unsigned int count=5;
    ui->exprText->setText(formatted());
    operators_count.push_back(5);
}

void MainWindow::on_multB_clicked()
{
    expr+="*";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_divisB_clicked()
{
    expr+="/";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_minusB_clicked()
{
    expr+="-";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_sinB_clicked()
{
    expr+="d(";
    unsigned int count=4;
    ui->exprText->setText(formatted());
    br_call.push_back("d(");
    operators_count.push_back(2);
}

void MainWindow::on_cosB_clicked()
{
    expr+="f(";
    unsigned int count=4;
    ui->exprText->setText(formatted());
    br_call.push_back("f(");
    operators_count.push_back(2);
}

void MainWindow::on_tgB_clicked()
{
    expr+="l(";
    unsigned int count=3;
    ui->exprText->setText(formatted());
    br_call.push_back("l(");
    operators_count.push_back(2);
}

void MainWindow::on_ctgB_clicked()
{
    expr+="c(";
    unsigned int count=4;
    ui->exprText->setText(formatted());
    operators_count.push_back(2);
}

void MainWindow::on_arcsinB_clicked()
{
    expr+="h(";
    unsigned int count=7;
    ui->exprText->setText(formatted());
    br_call.push_back("h(");
    operators_count.push_back(2);
}

void MainWindow::on_arccosB_clicked()
{
    expr+="g(";
    unsigned int count=7;
    ui->exprText->setText(formatted());
    br_call.push_back("g(");
    operators_count.push_back(2);
}

void MainWindow::on_arctgB_clicked()
{
    expr+="j(";
    unsigned int count=6;
    ui->exprText->setText(formatted());
    br_call.push_back("j(");
    operators_count.push_back(2);
}

void MainWindow::on_arcctgB_clicked()
{
    expr+="k(";
    unsigned int count=7;
    ui->exprText->setText(formatted());
    br_call.push_back("k(");
    operators_count.push_back(2);
}

void MainWindow::on_piB_clicked()
{
    expr+="P";
   unsigned int count=2;
   ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_eB_clicked()
{
    expr+="e";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_copmB_clicked()
{
    expr+="i";
    unsigned int count=1;
    ui->exprText->setText(formatted());
    operators_count.push_back(1);
}

void MainWindow::on_logB_clicked()
{
    expr+="a((";
    flag_log=true;
    unsigned int count=4;
    /*if(second_flag_log>1){
        ui->exprText->insert("Log(");
    }else{
        ui->exprText->insert("Log((");
    }*/
     ui->exprText->insert("Log((");
     br_call.push_back("a(");
     br_call.push_back("sp(");
    operators_count.push_back(3);
}

void MainWindow::on_lgB_clicked()
{
    expr+="c(";
    unsigned int count=3;
    ui->exprText->setText(formatted());
     br_call.push_back("c(");
    operators_count.push_back(2);
}

void MainWindow::on_lnB_clicked()
{
    expr+="b(";
    unsigned int count=3;
    ui->exprText->setText(formatted());
     br_call.push_back("b(");
    operators_count.push_back(2);
}

void MainWindow::on_powtwoB_clicked()
{
    expr+="^(2)";
    unsigned int count=4;
    ui->exprText->setText(formatted());
    operators_count.push_back(4);
}

void MainWindow::on_powB_clicked()
{
    expr+="^(";
    unsigned int count=2;
    ui->exprText->setText(formatted());
         br_call.push_back("(");
    operators_count.push_back(2);
}

void MainWindow::on_radicaltwoB_clicked()
{
    expr+="(2)#(";
    unsigned int count=5;
    ui->exprText->setText(formatted());
    br_call.push_back("(");
    operators_count.push_back(5);
}

void MainWindow::on_radicalB_clicked()
{
    expr+="#(";
    unsigned int count=2;
    ui->exprText->setText(formatted());
    br_call.push_back("(");
    operators_count.push_back(2);
}

void MainWindow::on_procB_clicked()
{
    expr+="/100";
    ui->exprText->setText(formatted());
    unsigned int count=4;
    operators_count.push_back(4);
}
void MainWindow::on_allclearB_clicked()
{
    ui->exprText->setText("");
    expr="";
     ui->result->setText("");
}
void MainWindow::on_equalB_clicked()
{
    ui->result->setText(result_of_expr(expr));
  //  ui->exprText->setText(ui->result->text());
 //   ui->result->setText("");
    ui->exprText->setText(formatted());
}

/*void check_result()
{
    Ui::MainWindow::ui->result->setText(result_of_expr(expr));
    ui->exprText->setText(formatted());
}*/
void MainWindow::keyPressEvent(QKeyEvent *pressed)

{
switch (pressed->key())

    {

    case Qt::Key_0: on_zeroB_clicked(); break;

    case Qt::Key_1: on_oneB_clicked(); break;

    case Qt::Key_2: on_twoB_clicked(); break;

    case Qt::Key_3: on_threeB_clicked(); break;

    case Qt::Key_4: on_fourB_clicked(); break;

    case Qt::Key_5: on_fiveB_clicked(); break;

    case Qt::Key_6: on_sixB_clicked(); break;

    case Qt::Key_7: on_sevenB_clicked(); break;

    case Qt::Key_8: on_eigthB_clicked(); break;

    case Qt::Key_9: on_nineB_clicked(); break;

    case Qt::Key_Comma:

    case Qt::Key_Period: on_pointB_clicked(); break;



    case Qt::Key_P: on_piB_clicked(); break;

    case Qt::Key_E: on_eB_clicked(); break;



    case Qt::Key_Plus: on_plusB_clicked(); break;

    case Qt::Key_Minus: on_minusB_clicked(); break;

    case Qt::Key_Slash: on_divisB_clicked(); break;

    case Qt::Key_Asterisk: on_multB_clicked(); break;



    case Qt::Key_AsciiCircum: on_powtwoB_clicked(); break;

    }
}



