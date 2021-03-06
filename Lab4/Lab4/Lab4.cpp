#include "pch.h"
#include<string>
#include "string.h"
#include <iostream>
#include<vector>
using namespace std;
enum CommandType {
	Infix, Prefix, Postfix
};
class Operand {
public:
	string value;
};
class ComplexOperand {

};
class Command {
private:
	string name;
	virtual string execute() = 0;
public:
	int priority;
	unsigned short operandCount;
	CommandType type;
	string Showname() {
		return name;
	}
	void Writename(string New_name) {
		name = New_name;
		return;
	}
};
/*enum CommandType{
	Infix, Prefix, Postfix
};
struct Command {
	string name;
	unsigned short operandCount;
	CommandType type;
	std::function<double(string,string)>execute;
};

int priority(string operation) {
	int answer;
	if (operation == "^" || operation == "/" || operation == "*" || operation == "ln" || operation == "log" || operation == "#") {
		answer=2;
	}
	if (operation=="+"||operation == "-") {
		answer=1;
	}
	if ((operation == "sin" || operation == "cos" || operation == "tg" || operation == "ctg" || operation == "log" || operation == "ln")) {
		answer = 3;
	}
	if (operation == "(") {
		answer = 4;
	}
	if (operation == ")") {
		answer = 0;
	}
	return answer;
}
string minnus(string str) {
	int result = 0;
	int t, i = 0;
	while (str[i] != 0) {
		if (str[i] == '$') {
			result++;
			str[i] = ' ';
		}
		++i;
	}
	t = stod(str);
	while (result != 0) {
		t *= (-1);
		--result;
	}
	return to_string(t);
}
/*double Logorithm(string token1, string token2) {
	return log(stod(token1)) / log(stod(token2));
}
double Plus (string operand1, string operand2){
	return stod(operand1) + stod(operand2);
};
double Multiply(string operand1, string operand2){
	return stod(operand1)*stod(operand2); 
};*/
/*if (operation == "^" || operation == "/" || operation == "*" || operation == "ln" || operation == "log" || operation == "#") {
		answer=2;
	}
	if (operation=="+"||operation == "-") {
		answer=1;
	}
	if ((operation == "sin" || operation == "cos" || operation == "tg" || operation == "ctg" || operation == "log" || operation == "ln")) {
		answer = 3;
	}
	if (operation == "(") {
		answer = 4;
	}
	if (operation == ")") {
		answer = 0;
	}*/

double calculate(vector<string>& opz) {

	class Plus : public Command
	{
	public:
		Plus() {
			Writename("+");
			operandCount = 2;
			priority = 1;
			type = CommandType::Infix;
		}
		string execute(string operand1, string operand2) {
			return to_string(stod(operand1) + stod(operand2));
		};
	};
	class Minus : public Command
	{
	public:
		Minus() {
			Writename("-");
			operandCount = 1;
			priority = 1;
			type = CommandType::Infix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			string operand2 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(stod(operand1) - stod(operand2));
		};
	};
	class Unar_Minus : public Command
	{
	public:
		Unar_Minus() {
			Writename("-");
			operandCount = 5;
			priority = 1;
			type = CommandType::Prefix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(stod(operand1)*(-1));
		};
	};
	class Multiply : public Command
	{
	public:
		Multiply() {
			Writename("*");
			operandCount = 5;
			priority = 2;
			type = CommandType::Infix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			string operand2 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(stod(operand1) * stod(operand2));
		}
	};
	class Share : public Command
	{
	public:
		Share() {
			Writename("/");
			operandCount = 2;
			priority = 2;
			type = CommandType::Infix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			string operand2 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(stod(operand1) / stod(operand2));
		};
	};
	class Power : public Command
	{
	public:
		Power() {
			Writename("^");
			operandCount = 2;
			priority = 2;
			type = CommandType::Infix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			string operand2 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(pow(stod(operand1), stod(operand2)));
		};
	};
	class Radical : public Command
	{
	public:
		Radical() {
			Writename("#");
			operandCount = 2;
			priority = 2;
			type = CommandType::Infix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			string operand2 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(pow(stod(operand1), 1 / stod(operand2)));
		};
	};
	class Logorithm : public Command
	{
	public:
		Logorithm() {
			Writename("log");
			operandCount = 2;
			priority = 2;
			type = CommandType::Prefix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			string operand2 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(log(stod(operand1)) / log(stod(operand2)));
		};
	};
	class Nlogorithm : public Command
	{
	public:
		Nlogorithm() {
			Writename("ln");
			operandCount = 1;
			priority = 2;
			type = CommandType::Prefix;
		}
		string execute(vector<Operand> &opz) {
			int i = opz.size() - 1;
			string operand1 = opz[i].value;
			opz.erase(opz.begin() + i);
			--i;
			return to_string(log(stod(operand1)));
		};
	};
	class OpenBarcket : public Command
	{
	public:
		OpenBarcket() {
			Writename("(");
			operandCount = 0;
			priority = 3;
			type = CommandType::Prefix;
		}
	};
	class CloseBarcket : public Command
	{
	public:
		CloseBarcket() {
			Writename(")");
			operandCount = 0;
			priority = 0;
			type = CommandType::Postfix;
		}
	};
	/*Command-абстрактный класс с методом execute. Его дочерние классы Multiply, Plus, Minus и т.д также унаследуют этод метод но уже со своими особенностями. Также там должна быть операция скобка.
Есть также два класса Operand хранящий обычные числа и ComplexOperand зранящий комплексные.
Также есть функция Calculate, которая будет иметь два вектора:с числами Operands и с операциями Commands. Строка считывается с определённого места- по её операциям
формируется вектор операций, а по числам -чисел. Всё это происходит в обратной польской записи. Если конец строки достигнут он также заканчивает и выводит результат.*/

	int main() {
		setlocale(LC_ALL, "Rus");
		cout << "Хотите считать информацию из фаила?(y/n)\n";
		char way;
		cin >> way;
		string expression;
		string unit_s;
		string unit_d;
		vector <string> varnames_v;
		vector<string> varvalues_v;
		int quanity_of_varibles;
		switch (way) {
		case 'y':

			//инициализация массива из пути документа
			break;
		case 'n':
			cout << "\nНапишите выражения\n";
			cin.get();
			getline(cin, expression);
			cout << "\nСколько у вас переменных?\n";
			cin >> quanity_of_varibles;
			if (quanity_of_varibles != 0) {
				cout << "Перечислите имена переменных\n";
				for (int i = 0; i < quanity_of_varibles; i++) {
					cin >> unit_s;
					varnames_v.push_back(unit_s);
				}
				cout << "\nНапишите их значения\n";
				for (int i = 0; i < quanity_of_varibles; i++) {
					cin >> unit_d;
					varvalues_v.push_back(unit_d);
				}
				if (varnames_v.size() != varvalues_v.size()) {
					cout << "Кол-ва переменных и их значений не совпадают.";
					return 0;
				}
			}
		}
		return 0;
	}
