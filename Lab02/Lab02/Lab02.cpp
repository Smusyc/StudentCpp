#include "pch.h"
#include <iostream>
#include <string>
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS
#include<cmath>
#include<locale>
#include<fstream>
#include<functional>
using namespace std;
enum CommandType {	/*параметр объясняющий является ли элемент инфиксной, постфиксной или префиксной операцией. Такой
					 параметр есть у всех элементов строки element_expr, но заполнен он информацией только если элемент
					является операцией*/
	Infix, Prefix, Postfix
};
enum Command_Syntax {
	Bnar, Unar
};
enum ItemType {/*параметр объясняющий алгоритму каким типом элемент строки element_expr является
			   (Имя переменной, обычное число или операция)*/
	Varibles,Number,Operator
};
enum Sign {
	Minus
};
struct element_expression {
	ItemType Item;
	Sign Sign_of_Value;
	Command_Syntax Syntax; 
	CommandType Command;
	char CommandValue;//знаковое обозначение для операции, этот знак будет записан в строку element_epr
	int Preority;//Параметр объясняющий какой преоритет у операции. Это важная информаци для алгоритма польской записи.
	char Name_of_Varible;//имя переменной. Параметр пуст если элемент не является переменной.
	float NumberValue;//значение вещественного типа для числа
};
void expr_log(element_expression* element_expr, char* str, int& y, int& t, int& l, bool& f) {
	/*операция вычисления логорифма, которая используется	в мэйне при определённых условиях (П1.)*/
	char* cashNf = new char[5];
	char cashWf;
	int& k = l;
	++k;
	element_expr[k].Item = Operator;
	element_expr[k].Command = Infix;
	element_expr[k].CommandValue = '&';
	element_expr[k].Syntax = Bnar; 
	element_expr[k].Preority = 3;
	cashWf = 0;
	int& i = y;
	bool& r = f;
	if (str[i] == ' ') {
		++i;
	}
	else {
		r = true;
	}
	int& o = t;
		if (('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'z')) {
			if ('0' <= str[i] && str[i] <= '9') {
				o = 0;
				while ('0' <= str[i] && str[i] <= '9') {
					cashNf[o] = str[i];
					++o;
					++i;
				}
				cashNf[o] = 0;
				++k;
				element_expr[k].Item = Number;
				element_expr[k].NumberValue = atof(cashNf);
				cashNf[0] = 0;
			}
			else if ('a' <= str[i] && str[i] <= 'z') {
					cashWf = str[i];
					++i;
					++k;
				element_expr[k].Item = Varibles;
				element_expr[k].Name_of_Varible = cashWf;
				cashWf = 0;
			}
			else {
				r = true;
			}
			if (str[i] == ';') {
				++i;
			}
			else {
				r = true;
			}
			if ('0' <= str[i] && str[i] <= '9') {
				o = 0;
				while ('0' <= str[i] && str[i] <= '9') {
					cashNf[o] = str[i];
					++o;
					++i;
				}
				cashNf[o] = 0;
				++k;
				element_expr[k].Item = Number;
				element_expr[k].NumberValue = atof(cashNf);
				cashNf[0] = 0;
			}
			else if('a' <= str[i] && str[i] <= 'z') {
				cashWf = str[i];
				++i;
				++k;
				element_expr[k].Item = Varibles;
				element_expr[k].Name_of_Varible = cashWf;
				cashWf = 0;
			}
			else {
			r = true;
			}
		}
		else {
			r = true;
		}
		delete[]cashNf;
}

void expr_pow(element_expression* element_expr, char* str, int& y, int& t, int& l, bool& f) {/*операция вычисления степени, которая используется
																						 в мэйне при определённых условиях (П2.)*/
	char* cashNf = new char[5];
	char cashWf;
	int& k = l;
	++k;
	element_expr[k].Item = Operator;
	element_expr[k].Syntax = Bnar;
	element_expr[k].Command = Infix;
	element_expr[k].CommandValue = '^';
	element_expr[k].Preority = 3;
	int& i = y;
	bool& r = f;
	if (str[i] == ' ') {
		++i;
	}
	else {
		r = true;
	}
	int& o = t;
	if (('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'z')) {
		if ('0' <= str[i] && str[i] <= '9') {
			o = 0;
			while ('0' <= str[i] && str[i] <= '9') {
				cashNf[o] = str[i];
				++o;
				++i;
			}
			cashNf[o] = 0;
			++k;
			element_expr[k].Item = Number;
			element_expr[k].NumberValue = atof(cashNf);
			cashNf[0] = 0;
		}
		else if ('a' <= str[i] && str[i] <= 'z') {
			cashWf = str[i];
			++i;
			++k;
			element_expr[k].Item = Varibles;
			element_expr[k].Name_of_Varible = cashWf;
			cashWf = 0;
		}
		if (str[i] == ';') {
			++i;
		}
		else {
			r = true;
		}
		if ('0' <= str[i] && str[i] <= '9') {
			o = 0;
			while ('0' <= str[i] && str[i] <= '9') {
				cashNf[o] = str[i];
				++o;
				++i;
			}
			cashNf[o] = 0;
			++k;
			element_expr[k].Item = Number;
			element_expr[k].NumberValue = atof(cashNf);
			cashNf[0] = 0;
		}
		else if ('a' <= str[i] && str[i] <= 'z') {
			cashWf = str[i];
			++i;
			++k;
			element_expr[k].Item = Varibles;
			element_expr[k].Name_of_Varible = cashWf;
			cashWf = 0;
		}
		else {
			r = true;
		}
	}
	else {
		r = true;
	}
	delete[] cashNf;
}
void expr_sqrt(element_expression* element_expr, char* str, int& y, int& t, int& l, bool& f) {/*операция вычисления корня, которая используется
																						 в мэйне при определённых условиях (П3.)*/
	char* cashNf = new char[5];
	char cashWf;
	int& k = l;
	++k;
	element_expr[k].Item = Operator;
	element_expr[k].Command = Infix;
	element_expr[k].CommandValue = '#';
	element_expr[k].Syntax = Bnar;
	element_expr[k].Preority = 3;
	int& i = y;
	bool& r = f;
	if (str[i] == ' ') {
		++i;
	}
	else {
		r = true;
	}
	int& o = t;
	if (('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'z')) {
		if ('0' <= str[i] && str[i] <= '9') {
			o = 0;
			while ('0' <= str[i] && str[i] <= '9') {
				cashNf[o] = str[i];
				++o;
				++i;
			}
			cashNf[o] = 0;
			++k;
			element_expr[k].Item = Number;
			element_expr[k].NumberValue = atof(cashNf);
			cashNf[0] = 0;
		}
		else if ('a' <= str[i] && str[i] <= 'z') {
			cashWf = str[i];
			++i;
			++k;
			element_expr[k].Item = Varibles;
			element_expr[k].Name_of_Varible = cashWf;
			cashWf = 0;
		}
		if (str[i] ==';') {
			++i;
		}
		else {
			r = true;
		}
		if ('0' <= str[i] && str[i] <= '9') {
			o = 0;
			while ('0' <= str[i] && str[i] <= '9') {
				cashNf[o] = str[i];
				++o;
				++i;
			}
			cashNf[o] = 0;
			++k;
			element_expr[k].Item = Number;
			element_expr[k].NumberValue = atof(cashNf);
			cashNf[0] = 0;
		}
		else if ('a' <= str[i] && str[i] <= 'z') {
			cashWf = str[i];
			++i;
			++k;
			element_expr[k].Item = Varibles;
			element_expr[k].Name_of_Varible = cashWf;
			cashWf = 0;
		}
		else {
			r = true;
		}
	}
	else {
		r = true;
	}
	delete[]cashNf;
}
struct _floatstack {
	float* p;
	int i;
};
typedef struct _floatstack floatstack;
floatstack fs_create(int size) {
	floatstack result;
	result.i = 0;
	result.p = new float[size];
	return result;
} 
void fs_push(floatstack *fs, float value) {
	fs->p[fs->i] = value;
	fs->i += 1;
}

float fs_pop(floatstack *fs) {
	float cur = fs->p[fs->i - 1];
	fs->i -= 1;
	return cur;
}

float fs_front(floatstack *fs) {
	return fs->p[fs->i - 1];
}
void fs_remove(floatstack * fs) {
	delete[] fs->p;
}
void expr_lg(element_expression* element_expr, char* str, int& y, int& t, int& l, bool& f) {/*операция вычисления десятичного логорифма, которая используется
																						 в мэйне при определённых условиях (П4.)*/
	char* cashNF = new char[5];
	char cashWF;
	int& k = l;
	++k;
	element_expr[k].Item = Number;
	element_expr[k].NumberValue = 10;
	++k;
	element_expr[k].Item = Operator;
	element_expr[k].Command = Infix;
	element_expr[k].CommandValue = '#';
	element_expr[k].Syntax = Bnar;
	element_expr[k].Preority = 3;
	int& i = y;
	bool& r = f;
	r = false;
	if (str[i] == ' ') {
		++i;
	}
	else {
		r = true;
	}
	int& o = t;
	if (('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'z')) {
		if ('0' <= str[i] && str[i] <= '9') {
			o = 0;
			while ('0' <= str[i] && str[i] <= '9') {
				cashNF[o] = str[i];
				cashNF[o+1] = 0;
				++o;
				++i;
			}
			++k;
			element_expr[k].Item = Number;
			element_expr[k].NumberValue = atof(cashNF);
			cashNF[0] = 0;
		}
		else if ('a' <= str[i] && str[i] <= 'z') {
			cashWF = str[i];
			++i;
			++k;
			element_expr[k].Item = Varibles;
			element_expr[k].Name_of_Varible = cashWF;
			cashWF = 0;
		}
		++i;
	}
	else {
		r = true;
	}
	delete[]cashNF;
}
float calculate(element_expression* expr, int lenght) {
	int i = 0;
	float op1;
	float op2;
	float clone;
	floatstack fs = fs_create(lenght);
	for (i; i < lenght; ++i) {
		if (expr[i].Item == Number) {
			fs_push(&fs, expr[i].NumberValue);
		}
		else if (expr[i].Item == Operator) {
			switch (expr[i].CommandValue) {
			case'+':
				fs_push(&fs, fs_pop(&fs) + fs_pop(&fs));
				break;
			case'-':
				fs_push(&fs, -fs_pop(&fs) + fs_pop(&fs));
				break;
			case'*':
				fs_push(&fs, fs_pop(&fs)*fs_pop(&fs));
				break;
			case'/':
				fs_push(&fs, (1 / fs_pop(&fs)) * fs_pop(&fs));
				break;
			case'%':
				op2 = fs_pop(&fs);
				op1 = fs_pop(&fs);
				fs_push(&fs, (float)(((int)op1) % ((int)op2)));
				break;
			case'&':
				op2 = fs_pop(&fs);
				op1 = fs_pop(&fs);
				fs_push(&fs, log(op1) / log(op2));
				break;
			case'#':
				clone = 1 / fs_pop(&fs);
				fs_push(&fs, pow(fs_pop(&fs), clone));
				break;
			case'^':
				clone = fs_pop(&fs);
				fs_push(&fs, pow(fs_pop(&fs), clone));
				break;
			case'$':
				fs_push(&fs,(-1)*fs_pop(&fs));
			}
		}
	}
	float result;
	result = fs_pop(&fs);
	fs_remove(&fs);
	return result;
}
char* readstr(char* mmemory) {
	char* memory = mmemory;
	cin.getline(memory, 400);
	return memory;
}
bool read_out_of_a_file(string trace, char* &exp,char*&mn, char*&vn, char*&vv) {
	ifstream file(trace);
	if (file.is_open()){
		cout << "Вход прошёл успешно.";
		file.getline(exp,400);
		file.getline(mn, 400);
		file.getline(vn, 400);
		file.getline(vv, 400);
	}
	else {
		cout << "Ошибка при входе.";
		return 0;
	}
	return 1;
	file.close();
}
int main() {
	char* expres = new char[400];
	char* varn = new char[400];
	char* varv = new char[400];
	char* mnoj = new char[3];
	char* &exp = expres;
	char* &vn = varn;
	char* &vv = varv;
	char* &mn = mnoj;
	setlocale(LC_ALL,"Russian");
	cout << "Do you want to open a file? (y/n)";
	char a;
	cin >> a;
	bool check_file = 0;
	string trace;
	char* result = new char[400];
	switch (a) {
	case'y':
		cout << "Напишите путь к фаилу";
		cin >> trace;
		check_file=read_out_of_a_file(trace,expres,mnoj,varn,varv);
		if (strlen(expres)==0||check_file==0){
			cout << "Вводите информацию сами";
			break;
		}
		break;
	case'n':
		break;
	default:
		break;
	}
	const char* expres_c =expres;
	const char* varn_c = varn;
	const char* varv_c = varv;
	const char* mnoj_c = mnoj;
	char* str = new char[400];
	char*memory = new char[400];
	if (strlen(expres) != 0&&check_file != 0) {
		strcpy_s(str,400,expres);
	}
	else {
		cout << "Write an expression\n";
		cin >> str;
		//str = readstr(memory);
	}
	element_expression* element_expr = new element_expression[strlen(str)];
	char* cashN = new char[5];
	char* cashW = new char[8];
	int lenght = strlen(str);
	int i = 0;
	int& i_f = i;
	int o;
	int& o_f = o;
	int k = -1;
	int& k_f = k;
	bool r = false;
	bool& r_f = r;
	int stop;
	for (i = 0; i < strlen(str); ++i) {
		if ('0' <= str[i] && str[i] <= '9') {
			stop = i - 1;
			o = 0;
			while ((('0' <= str[i] && str[i] <= '9') || (str[i] == '.')) && (str[i] != 0)) {
				cashN[o] = str[i];
				++i;
				++o;
			}
			cashN[o] = 0;
			++k;
			element_expr[k].Item = Number;
			if ((stop >= 0) && ((str[stop] == '-') && (('0' <= str[stop + 1] || str[stop] <= '9') || ('a' <= str[stop + 1] || str[stop + 1] <= 'z') || (str[stop + 1] == '(')) && (('0' >= str[stop - 1] || str[stop - 1] >= '9') || (stop == 0)))) {
				element_expr[k].NumberValue = (-1)*atof(cashN);
			}
			else {
				element_expr[k].NumberValue = atof(cashN);
			}
			cashN[0] = 0;
		}
		if ('a' <= str[i] && str[i] <= 'z') {
			stop = i - 1;
			o = 0;
			while ('a' <= str[i] && str[i] <= 'z') {
				cashW[o] = str[i];
				cashW[o + 1] = 0;
				++o;
				++i;
			}
			if (cashW[0] == 'l'&&cashW[1] == 'o'&&cashW[2] == 'g') {//вот условие для использования логорифма (П1.)
				expr_log( element_expr, str, i_f, o_f, k_f, r_f);
				if (r) {
					cout << "Error of command";
					return 0;
				}
				cashW[0] = 0;
			}
			else if (cashW[0] == 'l'&&cashW[1] == 'g') {//вот условие для использования десятичного логорифма (П4.)
				expr_lg(element_expr, str, i_f, o_f, k_f, r_f);
				if (r) {
					cout << "Error of command";
					return 0;
				}
				cashW[0] = 0;
			}
			else if (cashW[0] == 's'&&cashW[1] == 'q'&&cashW[2] == 'r'&&cashW[3] == 't') {//вот условие для использования корня(П3.)
				expr_sqrt(element_expr, str, i_f, o_f, k_f, r_f);
				if (r) {
					cout << "Error of command";
					return 0;
				}

				cashW[0] = 0;
			}
			else if (cashW[0] == 'p'&&cashW[1] == 'o'&&cashW[2] == 'w') {
				expr_pow(element_expr, str, i_f, o_f, k_f, r_f);//вот условие для использования степени (П2.)
				if (r) {
					cout << "Error of command";
					return 0;
				}
				cashW[0] = 0;
			}
			else {
				++k;
				element_expr[k].Item = Varibles;
				if ((stop >= 0) && ((str[stop] == '-') && (('0' <= str[stop + 1] || str[stop] <= '9') || ('a' <= str[stop + 1] || str[stop + 1] <= 'z') || (str[stop + 1] == '(')) && ((('0' >= str[stop - 1]||str[stop - 1] >= '9')&&str[stop - 1] != '-') || (stop == 0)))) {
					element_expr[k].Sign_of_Value = Minus;
				}
				element_expr[k].Name_of_Varible = cashW[0];
			}
		}
		if ((str[i] == '+'&&i < strlen(str))) {
			++k;
			element_expr[k].Item = Operator;
			element_expr[k].CommandValue = '+';
			element_expr[k].Command = Infix;
			element_expr[k].Syntax = Bnar;
			element_expr[k].Preority = 1;
		}
		if ((str[i] == '(') && i < strlen(str)) {
			++k;
			element_expr[k].CommandValue = '(';
		}												//все эти операции не требуют таких заморочек как с логорифмом или степенной функцией
		if ((str[i] == ')') && i < strlen(str)) {
			++k;
			element_expr[k].CommandValue = ')';
		}
		if ((str[i] == '%') && i < strlen(str)) {
			++k;
			element_expr[k].Item = Operator;
			element_expr[k].CommandValue = '%';
			element_expr[k].Command = Infix;
			element_expr[k].Syntax = Bnar;
			element_expr[k].Preority = 2;
		}
		if ((i < strlen(str)&&(0 < i))&&(str[i] == '-') && (('0' <= str[i + 1] || str[i] <= '9') || ('a' <= str[i + 1] || str[i + 1] <= 'z')) && (('0' <= str[i - 1] || str[i - 1] <= '9')||('a' <= str[i - 1] || str[i - 1] <= 'z'))){
			++k;
			element_expr[k].Item = Operator;
			element_expr[k].CommandValue = '-';
			element_expr[k].Command = Infix;
			element_expr[k].Syntax = Bnar;
			element_expr[k].Preority = 1;
		}
		if ((str[i] == '*') && i < strlen(str)) {
			++k;
			element_expr[k].Item = Operator;
			element_expr[k].CommandValue = '*';
			element_expr[k].Command = Infix;
			element_expr[k].Syntax = Bnar;
			element_expr[k].Preority = 2;
		}
		if ((str[i] == '/') && i < strlen(str)) {
			++k;
			element_expr[k].Item = Operator;
			element_expr[k].CommandValue = '/';
			element_expr[k].Command = Infix;
			element_expr[k].Syntax = Bnar;
			element_expr[k].Preority = 2;
		}
	}
	int y = 0;
	int quanity_of_varibles;
	if (check_file == 1) {
		if (strlen(mnoj) != 0) {
			quanity_of_varibles = atoi(mnoj);
		}
		else {
			quanity_of_varibles = 0;
		}
	}
	else {
		cout << "\nHow much do you have varibles?\n";
		cin >> quanity_of_varibles;//кол-во переменных
	}
 		char* mnames_of_varibles = new char[quanity_of_varibles];//массив имён перменных
		float* mvalues_of_varibles = new float[quanity_of_varibles];//значения для каждой соответствующей имени переменной
		int alt = 0;
		o = 0;
		int fch = 0;
		if ((strlen(varv) != 0 || strlen(mnoj) != 0 ||strlen(varn))&&check_file == 1) {
			mnames_of_varibles = varn;
			while (varv[o] != '\0') {
				while ((('0' <= varv[o]) && (varv[o] <= '9')) && (varv[o] != ',') && (alt < 8 && varv[o] != '\0')) {
					cashN[alt] = varv[o];
					++o;
					++alt;
				}
				mvalues_of_varibles[fch] = atof(cashN);
				cashN[0] = 0;
				alt = 0;
				if (varv[o] != '\0') {
					++fch;
					++o;
				}
			}
		}
		else {
			if (quanity_of_varibles > 0) {
				if (quanity_of_varibles != 0) {
					for (i = 0; i < quanity_of_varibles; ++i) {
						cout << "Varible #" << i + 1 << ':';
						cin >> mnames_of_varibles[i];//заполнение
						cout << "\nValue of varibles #" << i + 1 << ':';
						cin >> mvalues_of_varibles[i];
					}
					bool chek = false;
					for (i = 0; i <= k; ++i) {
						for (o = 0; o < quanity_of_varibles; ++o) {//проверка на правильный ввод переменных
							if (element_expr[i].Item == Varibles) {
								if (element_expr[i].Name_of_Varible == mnames_of_varibles[o]) {
									if (element_expr->Sign_of_Value == Minus) {
										element_expr[i].NumberValue = (-1)*mvalues_of_varibles[o];
										element_expr[i].Item = Number;
										chek = true;
									}
									else {
										element_expr[i].NumberValue = mvalues_of_varibles[o];
										element_expr[i].Item = Number;
										chek = true;
									}
								}
							}
						}
					}
					if (chek == false) {
						cout << "Error of Varibles";
						return 0;
					}
				}
			}
		}
	i = -1;
	y = -1;
	o = 0;
	element_expression* new_element_expr = new element_expression[k+1];
	element_expression* stek_element_expr = new element_expression[k+1];
	for (o = 0; o <=k;++o) {
		if ((element_expr[o].Item == Number) || (element_expr[o].Command == Postfix)) {
			++i;
			new_element_expr[i] = element_expr[o];
		}
		if(element_expr[o].Command == Prefix){
			++y;
			stek_element_expr[y] = element_expr[o];
		}
		if (element_expr[o].CommandValue == '(') {
			++y;
			stek_element_expr[y] = element_expr[o];
			stek_element_expr[y].Item = Operator;
		}
		if (element_expr[o].CommandValue == ')') {
			while ((stek_element_expr[y].CommandValue != '(')&&(y>0)) {
					++i;
					new_element_expr[i] = stek_element_expr[y];
					--y;
					if (y < 0) {
						cout << "Error of Brackets";
						return 0;
					}
					--y;
					++o;
			}
		}
		if (element_expr[o].Syntax !=Unar) {
			if (element_expr[o].Item == Operator){
				if ((y >= 0) &&((element_expr[o].Command==Prefix)&&(element_expr[o].Preority <= stek_element_expr[y].Preority))) {
					++i;
					new_element_expr[i] = stek_element_expr[y];
					--y;
				}
				++y;
				stek_element_expr[y] = element_expr[o];
			}
		}
	}
	for (o = y; o >= 0; --o) {
		++i; 
		if (stek_element_expr[o].Item != Operator) {
			cout << "Error of Writing";
			return 0;
		}
		new_element_expr[i] = stek_element_expr[o];
	}
	cout <<"\nYour result:"<<calculate(new_element_expr,i+1);
	delete[]element_expr;
	delete[] result;
 	delete[]str;
	delete[]cashN;
	delete[]cashW;
	delete[]mnames_of_varibles;
	delete[]mvalues_of_varibles;
	delete[]new_element_expr;
	delete[]stek_element_expr;
	delete[]memory;
	delete[]expres_c;
	delete[]varn_c;
	delete[]varv_c;
	delete[]mnoj_c;
	return 0;
 } 