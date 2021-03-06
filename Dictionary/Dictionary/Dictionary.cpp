#include "pch.h";
#include <iostream>
#include <string.h>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
using namespace std;
template<class T>
class List {
		struct Element {
			Element* next;
			Element* prev;
			T data;
		};
		Element* head = nullptr;
public:
		void addFirst() {
			Element* temp = new Element;
			temp->data;
			temp->next = NULL;
			temp->prev = NULL;
			if (head == NULL) {
				head = temp;
				return;
			}
			temp->next = head;
			head->prev = temp;
			head = temp;
			return;
		}
		void clear() {
			while (head != nullptr) {
				// Сначала высвобождаем всю память, выделенную
				// под поля структуры
				Element* temp = head;
				delete head;
				head = temp;
				// После этого можно высвободить память самого элемента списка
				delete temp;
			}
		}
		friend ostream& operator<<(ostream& os, List& obj) {
			while (obj.head != nullptr)
			{
				os <<"\n"<< obj.head->data;
				// Помним, что указатель - это просто адрес, т.е. число
				// В этой строчке мы сохраняем в переменную адрес следующего элемента
				obj.head = obj.head->next;
			}
			return os;
		}
};
class Transfer {
public:
	Transfer() {
		cout << "\nПараметр строка\n";
		cin >> value;
	}
	string value;
	vector<Transfer*> Blank;
	friend ostream& operator<<(ostream& os, Transfer& obj) {
		os << obj.value << '--->';
		int size = obj.Blank.size();
		for (i = 0; i < size; ++i)
			os << Transfer->value << ', ';
		return os;
	}
	friend istream& operator>>(istream& os, Transfer& obj) {

	}
};
int main() {
	setlocale(LC_ALL,"Rus");
	List<string> List_1;
	//List<Transfer> List_2;
	string command="";
	cout << "Готов к работе. Команды:\naddFirst-добавить элемент\n Cout-вывести содержимое\n Exit-выйти "<<endl;
	while (command != "Exit") {
		cin >> command;
		if (command=="addFirst") {
			List_1.addFirst();
			command = "";
		}
		else if (command=="Cout") {
			cout << List_1;
			command = "";
		}
	}
	// Как удалить весь список
	List_1.clear();
	return 0;
}
