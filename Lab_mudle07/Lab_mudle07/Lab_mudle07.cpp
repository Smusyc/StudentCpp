#include "pch.h"
#include <iostream>
#include<string>
#include <vector>
using namespace std;
enum TypeEnum { F, C };
class Base//базовыыйй класс который имеет только универсальную функцию Type() в с публичным доступом
{
public:
	Container* prev;
	string name;
	Base(string name_ini);
	Base(string name_ini, Container* prev_ini);
	//virtual bool Equal(Base& Cont_A)=0;
	virtual string toString() = 0;
	bool Equal(Base* obj);
	void setPrev(Container* prev_sp) {
		prev = prev_sp;
	}
	virtual char getType()=0;
	string name;
	~Base() {
	}
};
Base::Base(string name_ini) {
	name = name_ini;
}
Base::Base(string name_ini, Container* prev_ini) {
	prev = prev_ini;
	name = name_ini;
}
/*сделать коллекцию. 
титульный лист анотация код
вопросы по экзамену в мудле
сделать функции AddF и AddC и разложить по фаилам контейнерам*/
#define	CODE_INT 3
#define CODE_FLOAT 1
#define CODE_BOOL 2
class Data {
public:
	Data(float _float) {
		value.fl = _float;
		code = CODE_FLOAT;
	}
	Data(bool _bool) {
		value.bl = _bool;
		code = CODE_BOOL;
	}
	Data(int _intg) {
		value.intg = _intg;
		code = CODE_INT;
	}
	union memory {
		bool bl;
		float fl;
		int intg;
	};
	memory value;
	char code;
/*	void inicial() {
		if (code == "bl") {
			bool blValue;
			Code = code;
			cout << "Введите значение типа bool: ";
			cin >> blValue;
			cout << "\n";
			value.bl = blValue;
		}
		if (code == "fl") {
			float flValue;
			Code = code;
			cout << "Введите значение типа float: ";
			cin >> flValue;
			cout << "\n";
			value.fl = flValue;
		}
		if (code == "intg") {
			int intgValue;
			Code = code;
			cout << "Введите значение типа integer: ";
			cin >> intgValue;
			cout << "\n";
			value.intg = intgValue;
		}
	}*/
};
class File : public Base//класс File или Элемент по другому. Наследует функцию Base с её фунцией Type(),но теперь она выводит "File"
{
public:
	Data* data;
	File(string name_ini,Data* data_ini) :Base(name_ini){
		data = data_ini;
	}
	//trace = trace + name;
	string toString() {
		string s;
		s += "file[";
		s += name;
		s += "]";
		return s;
	}
	char getType() {
		return 'F';
	}
	~File(){
		delete prev;
	}
};

class Container : public Base
{
public:
	Container(string name_ini, Container* prev_ini) :Base(name_ini, prev_ini){}
	Container(string name_ini) :Base(name_ini) {}
	vector <Base*> elements;//elements-пустой указатель на указатель 
	//this->trace = this->name;
	char getType() {
		return 'C';
	}
	void Add(Base* item) {
		elements.push_back(item);
		item->setPrev(this);
	}
	/*virtual bool Equal(Container* A, Container* B) {
		if()
	}*/
	/*void move(Container* locat){
		string Command="";
		//Container* A;
		//Container* B;
		int number;
		while (Command!="Exit") {
			locat->ToString('n');
			cout << "Работа идёт...\n";
			cin >> Command;
			if (Command == "Prev") {
				locat = (Container*)location;
			}
			else if(Command=="AddC"){
				locat->AddC();
			}
			else if (Command=="AddF") {
				locat->AddF();
			}
			else if (Command == "ToString") {
				cout << "\nВведите номер элемента\n";
				cin >> number;
				
				if (number-1 <=(locat->index)) {
					locat->elements[number - 1]->ToString('r');
				}
				else {
					locat->elements[number - 1]->ToString();
				}
			}
			else if ("Entry") {
				cout << "\nВведите номер элемента\n";
				cin >> number;
				if (number - 1 <= (locat->index)) {
					locat = (Container*) elements[number - 1];
				}
			}
			/*else if ("Equal") {
				cout << "Введите номер элемента А";
				cin >> number;
				A =elementsC[number-1];
				cout << "Введите номер элемента В";
				cin >> number;
				B = elementsC[number - 1];
				if (Equal(A,B)) {
					cout << "Равны";
				}
				else {
					cout << "Неравны";
				}
			}
		}
	}*/
	/*void ToString(char unit)//метод вызываемый для элементов массива указателей с 0 по iй, вызывающий метод Type() для КОНТЕЙНЕРА
	{
		if (unit != 'n'&&unit != 'y') {
			cout << "Вывести всё содержимое этой структуры или толко состав этого элеиента?(y/n)\n";
			cin >> unit;
		}
			switch (unit) {
			case'y':cout << name<<"[ ";
				for (int i = 0; i < index; i++)
				{
					elements[i]->ToString('y');
				}
				for (int i = 0; i < index; i++)
				{
					elements[i]->ToString();
				}
				cout << "]   ";
				break;
			case'n':
				cout << name<<"[  ";
				for (int i = 0; i < index; i++)
				{
					cout << elements[i]->name;
					cout << ".c ";
				}

				for (int i = 0; i < index; i++)
				{
					cout << elements[i]->name;
					cout << ".f ";
				}
				cout << "  ]";
				break;
			}
		
	}*/
	string toString() {
		string s;
		s += name;
		s += "[";
		for (auto it = elements.begin(); it != elements.end();it++) {
			s += (*it)->toString();
			s += ',';
		}
		s += "]";
		return s;
	}
	~Container() {
		elements.erase(elements.begin(),elements.end());
	}
};
int main(){
	setlocale(LC_ALL, "Rus");
	string word = "root";
	Container* root = new Container(word);
	word = "File1";
	root->Add(new File(word,new Data(12)));
	cout << root->toString();
	system("pause");
}
/*про перегрузку операторов прочитать и про  >>  */