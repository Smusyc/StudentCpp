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
bool flag_coml=false;
QString text_unit,biautyexpr,text_undo;
std::vector<string> operators_count;
bool flag_log=false,equal_cicked=false;
int second_flag_log,second_flag_pow,tick,tick_for_calls=0,tick_for_count=0,flag_log_for_br=0;
vector<string> br_call,for_logs,oper_calls;

QString formatted(){
    vector<QString> form_stack;
    char checker;
    QString text,for_rad="";
    int brO=0,brC=0;
    second_flag_log=0;
    second_flag_pow=0;
    bool flag_power=false,flag_ln=false,flag_lg=false,flag_root=false,flag_radical=false,pi_bil=false;
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
                           for_rad+="Log(";
                          form_stack.push_back(")sp");
                      }else{
                           text+="Log<sub>";
                           for_rad+="Log<sub>";
                           form_stack.push_back("");
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
                      for_rad+="Ln(";
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
                        for_rad+=")";
                         form_stack.push_back(")");
                      continue;
                    }
                }
            }

            if(expr[i]==')'){
                ++brC;
                if(form_stack.size()>0&&form_stack[form_stack.size()-1]!="l"){
                    if(form_stack[form_stack.size()-1]==")sp"){
                        text+=")";
                        for_rad+=")";
                        --second_flag_log;
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }else if(form_stack[form_stack.size()-1]==""){
                        text+="";
                        for_rad+="";
                        --second_flag_log;
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }else if(form_stack[form_stack.size()-1]==")spp"){
                        text+=")";
                        for_rad+=")";
                        --second_flag_pow;
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }else if(form_stack[form_stack.size()-1]==")</sup>"){
                        text+=")</sup>";
                        for_rad+=")</sup>";
                        --second_flag_pow;
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }else if(form_stack[form_stack.size()-1]==")</span>"){
                        text+=")</span>";
                        for_rad+=")</span>";
                        flag_radical=false;
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }else{
                        text+=form_stack[form_stack.size()-1];
                        for_rad+=form_stack[form_stack.size()-1];
                        form_stack.erase(form_stack.begin()+(form_stack.size()-1));
                    }
                }else{
                    text+=")";
                    for_rad+=")";
                    form_stack.push_back("l");
                }
                continue;
            }
            if(expr[i]=='('){
                text+='(';
                for_rad+='(';
                brO++;
                form_stack.push_back(")");
                continue;
            }

            if(expr[i]=='d'){
                text+="sin";
                for_rad+="sin";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='f'){
                text+="cos";
                for_rad+="cos";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='g'){
                text+="arccos";
                for_rad+="arccos";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='h'){
                text+="arcsin";
                for_rad+="arcsin";
                brO++;
                form_stack.push_back(")");
                continue;

            }
            if(expr[i]=='j'){
                text+="arctg";
                for_rad+="arctg";
                brO++;
                form_stack.push_back(")");
            }
            if(expr[i]=='k'){
                text+="arcctg";
                for_rad+="arcctg";
                brO++;
               form_stack.push_back(")");
                continue;
            }
            if(expr[i]=='l'){
                text+="tg";
                for_rad+="tg";
                brO++;
               form_stack.push_back(")");
                continue;
            }
            if(expr[i]=='m'){
                text+="ctg";
                for_rad+="ctg";
                brO++;
                form_stack.push_back(")");
                continue;
            }
            if(expr[i]=='e'){
                text+="e";
               for_rad+="e";
                continue;
            }
            if(expr[i]=='i'){
                text+="i";
                for_rad+="i";
                continue;
            }
            if(expr[i]=='*'){
                text+="×";
                for_rad+="×";
                continue;
            }
            if(expr[i]=='+'){
                text+="+";
                for_rad+="+";
                continue;
            }
            if(expr[i]=='-'){
                text+="-";
                for_rad+="-";
                continue;
            }
            if(expr[i]=='/'){
                text+="/";
                for_rad+="/";
                continue;
            }
            if(expr[i]=='0'){
                text+="0";
                for_rad+="0";
                continue;
            }
            if(expr[i]=='1'){
                text+="1";
                for_rad+="1";
                continue;
            }
            if(expr[i]=='2'){
                text+="2";
                for_rad+="2";
                continue;
            }
            if(expr[i]=='3'){
                text+="3";
                for_rad+="3";
                continue;
            }
            if(expr[i]=='4'){
                text+="4";
                for_rad+="4";
                continue;
            }
            if(expr[i]=='5'){
                text+="5";
                for_rad+="5";
                continue;
            }
            if(expr[i]=='6'){
                text+="6";
                for_rad+="6";
                continue;
            }
            if(expr[i]=='7'){
                text+="7";
                for_rad+="7";
                continue;
            }
            if(expr[i]=='8'){
                text+="8";
                for_rad+="8";
                continue;
            }
            if(expr[i]=='9'){
                text+="9";
                for_rad+="9";
                continue;
            }
            if(expr[i]=='.'){
                text+=".";
                for_rad+=".";
                continue;
            }
            if(expr[i]==','){
                if(second_flag_log>1){
                    text+=",";
                    for_rad+=",";

                }else{
                    text+="</sub>";
                    for_rad+="</sub>";
                }
                continue;
            }
            if(expr[i]=='%'){
                text+="%";
                for_rad+="%";
                continue;
            }
            if(expr[i]=='!'){
                text+="!";
                for_rad+="!";
                continue;
            }
            if(expr[i]=='P'){
                text+="π";
                for_rad+="π";
                pi_bil=true;
                continue;
            }
            if(expr[i]=='['){
                text+="[";
                for_rad+="[";
                continue;
            }
            if(expr[i]==']'){
                text+="]";
                for_rad+="]";
                continue;
            }
            if(expr[i]=='^'){
                if(((expr.length()-1)-i)>=1){
                    if(expr[i+1]=='('){
                        ++second_flag_pow;
                        ++i;
                        brO++;
                        if(second_flag_pow>1){
                            text+="^(";
                            for_rad+="^(";
                            form_stack.push_back(")spp");
                        }else{
                            text+="<sup>(";
                            for_rad+="<sup>(";
                            form_stack.push_back(")</sup>");
                        }
                      continue;
                    }
                }
            }
            if(expr[i]=='#'){
                int step_back=for_rad.length(),br=0;
                bool flag_start=false,flag_start_br=false,marg=false;
                while(step_back>0){
                  if((br==0&&flag_start_br)||(marg&&br==0)){
                      break;
                  }
                    if(for_rad[step_back-1]=='('||for_rad[step_back-1]=='['||for_rad[step_back-1]=='<'){
                        br++;
                        flag_start=true;
                    }else
                    if(for_rad[step_back-1]==')'||for_rad[step_back-1]==']'||for_rad[step_back-1]=='>'){
                        br--;
                        flag_start=true;
                    }else
                    if(((for_rad.toStdString()[step_back-1]>='a'&&for_rad.toStdString()[step_back-1]<='z')||(for_rad.toStdString()[step_back-1]>='0'&&for_rad.toStdString()[step_back-1]<='9')||for_rad[step_back-1]=='!'||for_rad.toStdString()[step_back-1]=='i'||for_rad.toStdString()[step_back-1]=='e'||for_rad.toStdString()[step_back-1]=='.'||pi_bil||br<0)){
                        flag_start=true;
                        pi_bil=false;
                    }else if(((for_rad[step_back-1]=='/')||(for_rad[step_back-1]=='*')||(for_rad[step_back-1]=='-')||(for_rad[step_back-1]=='+'))&&br>=0){
                        break;
                    }else if(flag_start){
                        marg=true;
                    }
                    step_back--;
                    continue;
                }
                int min=for_rad.length()-step_back;
                step_back++;

                text.remove(text.length()-min,min);
                text+="<sup>";
                step_back--;
                for(step_back;step_back<for_rad.length();step_back++){
                    text+=for_rad[step_back];
                }
                text+="</sup>√<span style=\"text-decoration:overline\">(";
                form_stack.push_back(")</span>");
                flag_radical=true;
                for_rad=text;
                br_call.push_back("<span style=\"text-decoration:overline\">(");
                ++i;
                continue;
            }

    }
    return text;

}


enum CommandType {
    Infix, Prefix, Postfix,None
};
bool is_zero(double a) {
    return !(abs(a - DBL_EPSILON) > 0);
}
bool is_zero(Operand a) {
    return (is_zero(a.imag()) && is_zero(a.real()));
}
class Expression_Unit;class Command {
public:    string name;
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
        if(opz.size()>=operandCount){
            Operand operand1 = opz[opz.size() - 1];
            Operand operand2 = opz[opz.size() - 2];
            opz.erase(opz.begin() +(opz.size()-1));
            opz.erase(opz.begin() + (opz.size() - 1));
            return execute_bin(operand2, operand1);
        }else{
            throw OPERATOR_INVALID_lINC;
        }
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
         if(opz.size()>=operandCount){
            Operand operand1 = opz[opz.size() - 1];
            opz.erase(opz.begin() + opz.size()-1);
            return execute_un(operand1);
         }else{
             throw OPERATOR_INVALID_lINC;
         }
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
        return result2;
        for (int Length_del = v_expr.size(), i = 0; i < Length_del; ++i) {
            v_expr[i].del();
        }

}
QString result_of_expr(string exp) {
    string result;
    if(exp==""){
        return QString::fromStdString("0");
    }
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
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="(";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("(");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("(");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();
         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_clB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        if(tick_for_calls>0){
            while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                    operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }
                    step+=2;
                }
            }
            //tick_for_er--;
     tick=operators_count.size();
     int check_for_br=0;
     for(tick;tick>0;--tick){
         if(operators_count[tick-1]=="a(("||operators_count[tick-1]=="^(2)"||operators_count[tick-1]=="#("||operators_count[tick-1]=="(2)#("||operators_count[tick-1]=="^("||operators_count[tick-1]=="),("||operators_count[tick-1]=="("||operators_count[tick-1]=="a("||operators_count[tick-1]=="b("||operators_count[tick-1]=="c("||operators_count[tick-1]=="d("||operators_count[tick-1]=="f("||operators_count[tick-1]=="g("||operators_count[tick-1]=="h("||operators_count[tick-1]=="j("||operators_count[tick-1]=="k("||operators_count[tick-1]=="l("){
             check_for_br+=1;
             if(check_for_br>0){
                 break;
             }
         }else
         if(operators_count[tick-1]==")"||operators_count[tick-1]=="))"){
             if(operators_count[tick-1]=="))"){
                 check_for_br-=2;
             }else{
                 check_for_br-=1;
             }
         }
     }
     if(br_call.size()>0&&tick>0){
         if(operators_count[tick-1]=="a(("&&check_for_br>0){
             if(oper_calls.size()==0){
                 tick_for_calls=1;
             }
             expr+="),(";
             br_call.push_back("),(");
             if(tick_for_calls<oper_calls.size()){
                 for(int l=oper_calls.size();l>tick_for_calls;--l){
                     oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
                 }
                 oper_calls.push_back("),(");
                 tick_for_calls=oper_calls.size();

             }else{
                 oper_calls.push_back("),(");
                 tick_for_calls=oper_calls.size();

             }
             while(operators_count.size()>0){
                 operators_count.erase(operators_count.begin()+operators_count.size()-1);
         }

             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                     operators_count.erase(operators_count.begin()+operators_count.size()-1);
                         }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             tick_for_calls=oper_calls.size();
             tick_for_count=operators_count.size();
             tick=operators_count.size();
         }else if(operators_count[tick-1]==""){
             if(tick_for_calls<oper_calls.size()){
                 for(int l=oper_calls.size();l>tick_for_calls;--l){
                     oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
                 }
                 oper_calls.push_back("");
                 tick_for_calls=oper_calls.size();

             }else{
                 oper_calls.push_back("");
                 tick_for_calls=oper_calls.size();

             }
             while(operators_count.size()>0){
                 operators_count.erase(operators_count.begin()+operators_count.size()-1);
         }

             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                     operators_count.erase(operators_count.begin()+operators_count.size()-1);
                         }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             tick_for_calls=oper_calls.size();
             tick_for_count=operators_count.size();
             tick=tick_for_calls;
         }else if(operators_count[tick-1]=="),("){
             if(oper_calls.size()==0){
                 tick_for_calls=1;
             }
                   expr+="))";
                   if(tick_for_calls<oper_calls.size()){
                       for(int l=oper_calls.size();l>tick_for_calls;--l){
                           oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
                       }
                       oper_calls.push_back("))");
                       tick_for_calls=oper_calls.size();

                   }else{
                       oper_calls.push_back("))");
                       tick_for_calls=oper_calls.size();

                   }
                   while(operators_count.size()>0){
                       operators_count.erase(operators_count.begin()+operators_count.size()-1);
               }

                   for(int i=0;i<tick_for_calls;++i){
                       if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                           operators_count.push_back(oper_calls[i]);
                           if(check){
                               step=1;
                               check=false;
                           }
                       }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                           if(check){
                               step=1;
                               check=false;
                           }
                           while(operators_count.size()>0){
                           operators_count.erase(operators_count.begin()+operators_count.size()-1);
                               }
                       }else{
                           if(operators_count.size()>0){
                               check=true;
                               operators_count.erase(operators_count.begin()+operators_count.size()-1);
                           }
                           }
                           step+=2;
                       }
                   tick_for_calls=oper_calls.size();
                   tick_for_count=operators_count.size();
                   tick=tick_for_calls;
         }else if(operators_count[tick-1]=="("||operators_count[tick-1]=="#("||operators_count[tick-1]=="(2)#("||operators_count[tick-1]=="^(2)"||operators_count[tick-1]=="^("||operators_count[tick-1]=="("||operators_count[tick-1]=="b("||operators_count[tick-1]=="c("||operators_count[tick-1]=="d("||operators_count[tick-1]=="f("||operators_count[tick-1]=="g("||operators_count[tick-1]=="h("||operators_count[tick-1]=="j("||operators_count[tick-1]=="k("){
             if(oper_calls.size()==0){
                 tick_for_calls=1;
             }
             expr+=")";
             if(tick_for_calls<oper_calls.size()){
                 for(int l=oper_calls.size();l>tick_for_calls;--l){
                     oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
                 }
                 oper_calls.push_back(")");
                 tick_for_calls=oper_calls.size();

             }else{
                 oper_calls.push_back(")");
                 tick_for_calls=oper_calls.size();

             }
             while(operators_count.size()>0){
                 operators_count.erase(operators_count.begin()+operators_count.size()-1);
         }

             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                     operators_count.erase(operators_count.begin()+operators_count.size()-1);
                         }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             tick_for_calls=oper_calls.size();
             tick_for_count=operators_count.size();
             tick=tick_for_calls;
         }else{
             if(oper_calls.size()==0){
                 tick_for_calls=1;
             }
             expr+=")";
             if(tick_for_calls<oper_calls.size()){
                 for(int l=oper_calls.size();l>tick_for_calls;--l){
                     oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
                 }
                 oper_calls.push_back(")");
                 tick_for_calls=oper_calls.size();

             }else{
                 oper_calls.push_back(")");
                 tick_for_calls=oper_calls.size();

             }
             while(operators_count.size()>0){
                 operators_count.erase(operators_count.begin()+operators_count.size()-1);
         }

             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                     operators_count.erase(operators_count.begin()+operators_count.size()-1);
                         }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             tick_for_calls=oper_calls.size();
             tick_for_count=operators_count.size();
             //tick=br_call.size()-1;
             tick=tick_for_count;
         }

     }else{
         if(oper_calls.size()==0){
             tick_for_calls=1;
         }
               expr+=")";
               if(tick_for_calls<oper_calls.size()){
                   for(int l=oper_calls.size();l>tick_for_calls;--l){
                       oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
                   }
                   oper_calls.push_back(")");
                   tick_for_calls=oper_calls.size();
               }else{
                   oper_calls.push_back(")");
                   tick_for_calls=oper_calls.size();
               }
               while(operators_count.size()>0){
                   operators_count.erase(operators_count.begin()+operators_count.size()-1);
           }

               for(int i=0;i<tick_for_calls;++i){
                   if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                       operators_count.push_back(oper_calls[i]);
                       if(check){
                           step=1;
                           check=false;
                       }
                   }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                       if(check){
                           step=1;
                           check=false;
                       }
                       while(operators_count.size()>0){
                       operators_count.erase(operators_count.begin()+operators_count.size()-1);
                           }
                   }else{
                       if(operators_count.size()>0){
                           check=true;
                           operators_count.erase(operators_count.begin()+operators_count.size()-1);
                       }
                       }
                       step+=2;
                   }
               tick_for_calls=oper_calls.size();
               tick_for_count=operators_count.size();
               tick=tick_for_calls;
     }

     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_opmB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="[";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("[");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("[");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_clmB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
     expr+="]";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("]");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("]");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_factB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
     expr+="!";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("!");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("!");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));
}
void MainWindow::on_clearB_2_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

    if(operators_count.size()>0){
        unsigned int count=(operators_count[operators_count.size()-1]).length();
        text_unit=QString::fromStdString(expr);
        text_unit.remove(text_unit.length()-count,count);
        expr=text_unit.toStdString();
        ui->exprText->setText(formatted());
        ui->result->setText(result_of_expr(expr));
        if((operators_count[operators_count.size()-1]=="a(("||operators_count[operators_count.size()-1]=="(2)#("||operators_count[operators_count.size()-1]=="^(2)"||operators_count[operators_count.size()-1]=="^("||operators_count[operators_count.size()-1]=="#("||operators_count[operators_count.size()-1]=="("||operators_count[operators_count.size()-1]=="b("||operators_count[operators_count.size()-1]=="c("||operators_count[operators_count.size()-1]=="d("||operators_count[operators_count.size()-1]=="f("||operators_count[operators_count.size()-1]=="g("||operators_count[operators_count.size()-1]=="h("||operators_count[operators_count.size()-1]=="j("||operators_count[operators_count.size()-1]=="k(")&&br_call.size()>0){
            br_call.erase(br_call.begin()+br_call.size()-1);
        }
        if(tick_for_calls<oper_calls.size()){
            for(int l=oper_calls.size();l>tick_for_calls;--l){
                oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
            }
            oper_calls.push_back("R");
            tick_for_calls=oper_calls.size();
        }else{
            oper_calls.push_back("R");
            tick_for_calls=oper_calls.size();
        }
            bool check=false;
            int step=0;
            tick_for_calls=oper_calls.size();
            if(tick_for_calls>0){
                while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                //expr="";
                for(int i=0;i<tick_for_calls;++i){
                    if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                        operators_count.push_back(oper_calls[i]);
                        if(check){
                            step=1;
                            check=false;
                        }
                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                        if(check){
                            step=1;
                            check=false;
                        }
                        while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                            }
                    }else{
                        if(operators_count.size()>0){
                            check=true;
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                            step+=2;
                        }
                        }
                    }
                }
                //tick_for_er--;
         tick_for_calls=oper_calls.size();
        /*if(tick_for_count>0){
            tick_for_count--;
        }*/
}
}
void MainWindow::on_eigthB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="8";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("8");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("8");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_nineB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="9";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("9");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("9");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_plusB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
     expr+="+";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("+");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("+");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_fourB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="4";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("4");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("4");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_fiveB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="5";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("5");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("5");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_sixB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="6";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("6");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("6");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_sevenB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="7";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("7");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("7");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}
void MainWindow::on_threeB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="3";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("3");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("3");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_twoB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="2";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("2");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("2");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}


void MainWindow::on_oneB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

     expr+="1";
     equal_cicked=false;
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("1");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("1");
         tick_for_calls=oper_calls.size();
     }
     while(operators_count.size()>0){
         operators_count.erase(operators_count.begin()+operators_count.size()-1);
 }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();

         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                     }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));

}

void MainWindow::on_pointB_clicked()
{
    if(expr.size()>0&&isdigit(expr[expr.size()-1])&&!equal_cicked){
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
    expr+=".";
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back(".");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back(".");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    for(int l=0;l<operators_count.size();++l){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
            }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}
}
void MainWindow::on_zeroB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    expr+="0";
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("0");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("0");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
        operators_count.erase(operators_count.begin()+operators_count.size()-1);
            }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                    operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                    expr="";
                }else{
                    if(operators_count.size()>0){

                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
            }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_recipB_clicked()
{
    if(!((isdigit(expr[expr.size()-1])||isalpha(expr[expr.size()-1])||(expr[expr.size()-1]=='P')||(expr[expr.size()-1]=='e')||(expr[expr.size()-1]=='i')||(expr[expr.size()-1]=='!')||(expr[expr.size()-1]==')')))){
}else{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    expr+="^(-1)";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("^(-1)");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("^(-1)");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    for(int l=0;l<operators_count.size();++l){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }else{
                    if(operators_count.size()>0){

                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
    }
}

void MainWindow::on_multB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    expr+="*";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("*");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("*");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    for(int l=0;l<operators_count.size();++l){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_divisB_clicked()
{
    expr+="/";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("/");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("/");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_minusB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }

    expr+="-";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("-");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("-");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_sinB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="d(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("d(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("d(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_cosB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="f(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("f(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("f(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_tgB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="l(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("l(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("l(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_ctgB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="c(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("c(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("c(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_arcsinB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="h(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("h(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("h(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_arccosB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="g(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("g(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("g(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_arctgB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="j(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("j(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("j(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_arcctgB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="k(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("k(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("k(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_piB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="P";
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("P");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("P");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_eB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    expr+="e";
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("e");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("e");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_copmB_clicked()
{
    if(expr.size()==0||(!isdigit(expr[expr.size()-1])&&(expr[expr.size()-1])!='e'&&expr[expr.size()-1]!='P'&&(expr[expr.size()-1])!=')')){
        expr+="1i";
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
        if(equal_cicked){
            equal_cicked=false;
            on_allclearB_clicked();
        }

        if(tick_for_calls<oper_calls.size()){
            for(int l=oper_calls.size();l>tick_for_calls;--l){
                oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
            }
            oper_calls.push_back("1i");
            tick_for_calls=oper_calls.size();
        }else{
            oper_calls.push_back("1i");
            tick_for_calls=oper_calls.size();
        }
            bool check=false;
            int step=0;
            tick_for_calls=oper_calls.size();
            while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
        }
            if(tick_for_calls>0){
                //expr="";
                for(int i=0;i<tick_for_calls;++i){
                    if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                        operators_count.push_back(oper_calls[i]);
                        if(check){
                            step=1;
                            check=false;
                        }
                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                        if(check){
                            step=1;
                            check=false;
                        }
                        while(operators_count.size()>0){
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }else{
                        if(operators_count.size()>0){
                            check=true;
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                    }
                        step+=2;
                    }
                }
                //tick_for_er--;
        tick_for_calls=oper_calls.size();
        tick_for_count=operators_count.size();
    }else if(expr.size()>0&&expr[expr.size()-1]==')'){
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
        expr+="*1i";
        if(tick_for_calls<oper_calls.size()){
            for(int l=oper_calls.size();l>tick_for_calls;--l){
                oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
            }
            oper_calls.push_back("*1i");
            tick_for_calls=oper_calls.size();
        }else{
            oper_calls.push_back("*1i");
            tick_for_calls=oper_calls.size();
        }
            bool check=false;
            int step=0;
            tick_for_calls=oper_calls.size();
            while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
        }
            if(tick_for_calls>0){
                //expr="";
                for(int i=0;i<tick_for_calls;++i){
                    if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                        operators_count.push_back(oper_calls[i]);
                        if(check){
                            step=1;
                            check=false;
                        }
                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                        if(check){
                            step=1;
                            check=false;
                        }
                        while(operators_count.size()>0){
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }else{
                        if(operators_count.size()>0){
                            check=true;
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                    }
                        step+=2;
                    }
                }
                //tick_for_er--;
        tick_for_calls=oper_calls.size();
        tick_for_count=operators_count.size();
    }
    else{
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
        expr+="i";
        if(tick_for_calls<oper_calls.size()){
            for(int l=oper_calls.size();l>tick_for_calls;--l){
                oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
            }
            oper_calls.push_back("i");
            tick_for_calls=oper_calls.size();
        }else{
            oper_calls.push_back("i");
            tick_for_calls=oper_calls.size();
        }
            bool check=false;
            int step=0;
            tick_for_calls=oper_calls.size();
            while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
        }
            if(tick_for_calls>0){
                //expr="";
                for(int i=0;i<tick_for_calls;++i){
                    if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                        operators_count.push_back(oper_calls[i]);
                        if(check){
                            step=1;
                            check=false;
                        }
                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                        if(check){
                            step=1;
                            check=false;
                        }
                        while(operators_count.size()>0){
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }else{
                        if(operators_count.size()>0){
                            check=true;
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                    }
                        step+=2;
                    }
                }
        tick_for_calls=oper_calls.size();
        tick_for_count=operators_count.size();
    }
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_logB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    expr+="a((";
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    br_call.push_back("a((");
    equal_cicked=false;
    flag_log=true;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("a((");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("a((");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
        operators_count.erase(operators_count.begin()+operators_count.size()-1);
            }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                    operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                    expr="";
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_lgB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    expr+="c(";
    equal_cicked=false;
     br_call.push_back("c(");
     if(tick_for_calls<oper_calls.size()){
         for(int l=oper_calls.size();l>tick_for_calls;--l){
             oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
         }
         oper_calls.push_back("c(");
         tick_for_calls=oper_calls.size();
     }else{
         oper_calls.push_back("c(");
         tick_for_calls=oper_calls.size();
     }
         bool check=false;
         int step=0;
         tick_for_calls=oper_calls.size();
         while(operators_count.size()>0){
             operators_count.erase(operators_count.begin()+operators_count.size()-1);
     }
         if(tick_for_calls>0){
             //expr="";
             for(int i=0;i<tick_for_calls;++i){
                 if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                     operators_count.push_back(oper_calls[i]);
                     if(check){
                         step=1;
                         check=false;
                     }
                 }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                     if(check){
                         step=1;
                         check=false;
                     }
                     while(operators_count.size()>0){
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                 }
                 }else{
                     if(operators_count.size()>0){
                         check=true;
                         operators_count.erase(operators_count.begin()+operators_count.size()-1);
                     }
                 }
                     step+=2;
                 }
             }
             //tick_for_er--;
     tick_for_calls=oper_calls.size();
     tick_for_count=operators_count.size();
     ui->exprText->setText(formatted());
     ui->result->setText(result_of_expr(expr));}

void MainWindow::on_lnB_clicked()
{
    if(equal_cicked){
        equal_cicked=false;
        on_allclearB_clicked();
    }
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    expr+="b(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("b(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("b(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}

void MainWindow::on_powtwoB_clicked()
{
    if(expr.size()!=0){
        if(!((isdigit(expr[expr.size()-1])||isalpha(expr[expr.size()-1])||(expr[expr.size()-1]=='P')||(expr[expr.size()-1]=='e')||(expr[expr.size()-1]=='i')||(expr[expr.size()-1]=='!')||(expr[expr.size()-1]==')')))){

    }else{
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
    expr+="^(2)";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("^(2)");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("^(2)");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
    }
    }
}

void MainWindow::on_powB_clicked()
{
    if(expr.size()!=0){
        if(!((isdigit(expr[expr.size()-1])||isalpha(expr[expr.size()-1])||(expr[expr.size()-1]=='P')||(expr[expr.size()-1]=='e')||(expr[expr.size()-1]=='i')||(expr[expr.size()-1]=='!')||(expr[expr.size()-1]==')')))){

    }else{
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
    expr+="^(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("^(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("^(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
    }
    }
}

void MainWindow::on_radicaltwoB_clicked()
{
    if(expr.size()!=0){
    if((isdigit(expr[expr.size()-1])||isalpha(expr[expr.size()-1])||(expr[expr.size()-1]=='P')||(expr[expr.size()-1]=='e')||(expr[expr.size()-1]=='i')||(expr[expr.size()-1]=='!')||(expr[expr.size()-1]==')'))){

    }else{
        if(equal_cicked){
            equal_cicked=false;
            on_allclearB_clicked();
        }

        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
    expr+="(2)#(";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("(2)#(");
        tick_for_calls=oper_calls.size();
    }else{
        oper_calls.push_back("(2)#(");
        tick_for_calls=oper_calls.size();
    }
        bool check=false;
        int step=0;
        tick_for_calls=oper_calls.size();
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
    }
    }else{
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }
        expr+="(2)#(";
        equal_cicked=false;
        if(tick_for_calls<oper_calls.size()){
            for(int l=oper_calls.size();l>tick_for_calls;--l){
                oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
            }
            oper_calls.push_back("(2)#(");
            tick_for_calls=oper_calls.size();

        }else{
            oper_calls.push_back("(2)#(");
            tick_for_calls=oper_calls.size();

        }
            bool check=false;
            int step=0;
            tick_for_calls=oper_calls.size();
            while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
        }
            if(tick_for_calls>0){
                //expr="";
                for(int i=0;i<tick_for_calls;++i){
                    if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                        operators_count.push_back(oper_calls[i]);
                        if(check){
                            step=1;
                            check=false;
                        }
                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                        if(check){
                            step=1;
                            check=false;
                        }
                        while(operators_count.size()>0){
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }else{
                            check=true;
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                        step+=2;
                    }
                }
                //tick_for_er--;
        tick_for_calls=oper_calls.size();
        tick_for_count=operators_count.size();
        ui->exprText->setText(formatted());
        ui->result->setText(result_of_expr(expr));
    }

}

void MainWindow::on_radicalB_clicked()
{
    if(expr.size()!=0){
    if((!isdigit(expr[expr.size()-1])&&!isalpha(expr[expr.size()-1])&&(expr[expr.size()-1]!='P')&&(expr[expr.size()-1]!='e')&&(expr[expr.size()-1]!='i')&&(expr[expr.size()-1]!='!')&&(expr[expr.size()-1]!=')'))){

    }else{
        if(oper_calls.size()==0){
            tick_for_calls=1;
        }

        expr+="#(";
        equal_cicked=false;
        if(tick_for_calls<oper_calls.size()){
            for(int l=oper_calls.size();l>tick_for_calls;--l){
                oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
            }
            oper_calls.push_back("#(");
            tick_for_calls=oper_calls.size();

        }else{
            oper_calls.push_back("#(");
            tick_for_calls=oper_calls.size();

        }
            bool check=false;
            int step=0;
            tick_for_calls=oper_calls.size();
            while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
        }
            if(tick_for_calls>0){
                //expr="";
                for(int i=0;i<tick_for_calls;++i){
                    if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                        operators_count.push_back(oper_calls[i]);
                        if(check){
                            step=1;
                            check=false;
                        }
                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                        if(check){
                            step=1;
                            check=false;
                        }
                        while(operators_count.size()>0){
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }else{
                        if(operators_count.size()>0){
                            check=true;
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                        }
                    }
                        step+=2;
                    }
                }
                //tick_for_er--;
        tick_for_calls=oper_calls.size();
        tick_for_count=operators_count.size();
        ui->exprText->setText(formatted());
        ui->result->setText(result_of_expr(expr));
    }
    }
}

void MainWindow::on_procB_clicked()
{
    if(oper_calls.size()==0){
        tick_for_calls=1;
    }
    expr+="/100";
    equal_cicked=false;
    if(tick_for_calls<oper_calls.size()){
        for(int l=oper_calls.size();l>tick_for_calls;--l){
            oper_calls.erase(oper_calls.begin()+oper_calls.size()-1);
        }
        oper_calls.push_back("/100");
        tick_for_calls=oper_calls.size();

    }else{
        oper_calls.push_back("/100");
        tick_for_calls=oper_calls.size();

    }
        bool check=false;
        int step=0;
        while(operators_count.size()>0){
            operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }
        if(tick_for_calls>0){
            //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                    if(check){
                        step=1;
                        check=false;
                    }
                    while(operators_count.size()>0){
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                }
                    step+=2;
                }
            }
            //tick_for_er--;
    tick_for_calls=oper_calls.size();
    tick_for_count=operators_count.size();
    ui->exprText->setText(formatted());
    ui->result->setText(result_of_expr(expr));
}
void MainWindow::on_allclearB_clicked()
{
    while(operators_count.size()>0){
        operators_count.erase(operators_count.begin()+operators_count.size()-1);
}
    oper_calls.push_back("M");
    tick_for_calls=oper_calls.size();
    ui->exprText->setText("");
    expr="";
    ui->result->setText("0");
    /*for(int i=operators_count.size();i>0;--i){
        operators_count.erase(operators_count.begin()+operators_count.size()-1);
    }*/
    for(int i=br_call.size();i>0;--i){
        br_call.erase(br_call.begin()+br_call.size()-1);
    }
}
void MainWindow::on_equalB_clicked()
{
    if((ui->result->text())!="Неправильный аргумент факториала"&&(ui->result->text())!="Неправильный арумент логарифма"&&(ui->result->text())!= "Деление на ноль"&&(ui->result->text())!="Несогласованные скобки"&&(ui->result->text())!="Ошибка в записи операций"&&!equal_cicked){
    expr=(ui->result->text()).toStdString();
    oper_calls.push_back(expr+"W");
    ui->exprText->setText(formatted());
     ui->result->setText("");
     equal_cicked=true;
      tick_for_calls=oper_calls.size();
    }
}
void MainWindow::on_Undo_clicked()
{
        bool check=false;
        int step=0;
        if(tick_for_calls>0){
            tick_for_calls--;
        }
        if(tick_for_calls>=0){
            while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
        }
                    //expr="";
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                                        if(check){
                                            step=1;
                                            check=false;
                                        }
                                        while(operators_count.size()>0){
                                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                                    }
                                        expr="";

                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='W')){
                        QString change=QString::fromStdString(oper_calls[i]);
                        change.remove(change.length()-1,1);
                        expr=change.toStdString();
                        while(operators_count.size()>0){
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                        operators_count.push_back(expr);
                    }
                    else{
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                    }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }
                    step+=2;
                }
            expr="";
            for(int o=0;o<operators_count.size();++o){
                expr+=operators_count[o];
            }
            }
            //tick_for_er--;
        //tick_for_er++;
        ui->exprText->setText(formatted());
        ui->result->setText(result_of_expr(expr));

}
void MainWindow::on_Redo_clicked()
{
        bool check=false;
        int step=0;
        if(tick_for_calls<oper_calls.size()){
            tick_for_calls++;
        }
        if(tick_for_calls<=oper_calls.size()){
            //expr="";
            while(operators_count.size()>0){
                operators_count.erase(operators_count.begin()+operators_count.size()-1);
        }
            for(int i=0;i<tick_for_calls;++i){
                if((oper_calls[i])[(oper_calls[i].length()-1)]!='R'){
                    if(((oper_calls[i])[(oper_calls[i].length()-1)]=='M')){
                                        if(check){
                                            step=1;
                                            check=false;
                                        }
                                        while(operators_count.size()>0){
                                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                                    }
                                        expr="";

                    }else if(((oper_calls[i])[(oper_calls[i].length()-1)]=='W')){
                        QString change=QString::fromStdString(oper_calls[i]);
                        change.remove(change.length()-1,1);
                        expr=change.toStdString();
                        while(operators_count.size()>0){
                            operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                        operators_count.push_back(expr);
                    }
                    else{
                    operators_count.push_back(oper_calls[i]);
                    if(check){
                        step=1;
                        check=false;
                    }
                    }
                }else{
                    if(operators_count.size()>0){
                        check=true;
                        operators_count.erase(operators_count.begin()+operators_count.size()-1);
                    }
                    }
                    step+=2;
                }
            expr="";
            for(int o=0;o<operators_count.size();++o){
                expr+=operators_count[o];
            }
            }
            //tick_for_er--;
        //tick_for_er++;
        ui->exprText->setText(formatted());
        ui->result->setText(result_of_expr(expr));
}


void MainWindow::keyPressEvent(QKeyEvent *pressed)

{
switch (pressed->key())

    {

    case Qt::Key_0:on_zeroB_clicked(); break;

    case Qt::Key_1:on_oneB_clicked(); break;

    case Qt::Key_2:on_twoB_clicked(); break;

    case Qt::Key_3:on_threeB_clicked(); break;

    case Qt::Key_4:on_fourB_clicked(); break;

    case Qt::Key_5:on_fiveB_clicked(); break;

    case Qt::Key_6:on_sixB_clicked(); break;

    case Qt::Key_7:on_sevenB_clicked(); break;

    case Qt::Key_8:on_eigthB_clicked(); break;

    case Qt::Key_9:on_nineB_clicked(); break;

    case Qt::Key_Period:on_pointB_clicked(); break;

    case Qt::Key_AsciiCircum:on_powB_clicked(); break;

    case Qt::Key_ParenLeft:on_opB_clicked(); break;

    case Qt::Key_ParenRight:on_clB_clicked(); break;

    case Qt::Key_Backspace:on_clearB_2_clicked(); break;

    case Qt::Key_P:on_piB_clicked(); break;

    case Qt::Key_Enter:on_equalB_clicked(); break;

    case Qt::Key_E:on_eB_clicked(); break;

    case Qt::Key_U:on_Undo_clicked(); break;

    case Qt::Key_R:on_Redo_clicked(); break;

    case Qt::Key_Exclam:on_factB_clicked(); break;

    case Qt::Key_Percent:on_procB_clicked(); break;

    case Qt::Key_NumberSign:on_radicalB_clicked(); break;

    case Qt::Key_BracketLeft:on_opmB_clicked(); break;

    case Qt::Key_BracketRight:on_clmB_clicked(); break;

    case Qt::Key_I:on_copmB_clicked(); break;

    case Qt::Key_Plus:on_plusB_clicked(); break;

    case Qt::Key_Minus:on_minusB_clicked(); break;

    case Qt::Key_Slash:on_divisB_clicked(); break;

    case Qt::Key_Asterisk:on_multB_clicked(); break;




    }
}





